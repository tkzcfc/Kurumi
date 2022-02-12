#include "GTools.h"
#include "unzip/unzip.h"
#include "cocostudio/CocoStudio.h"
#include "mugen/platform/GPlatformDefine.h"

#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

bool GTools::isInRect(Node* InNode, float InX, float InY)
{
	CC_ASSERT(InNode != NULL);
	if (InNode == NULL)
		return false;
	Rect rect;
	rect.size = InNode->getContentSize();
	return isScreenPointInRect(Vec2(InX, InY), Camera::getDefaultCamera(), InNode->getWorldToNodeTransform(), rect, NULL);
}

std::string GTools::getBasename(const std::string& path)
{
	size_t found = path.find_last_of("/\\");

	if (std::string::npos != found)
	{
		return path.substr(0, found);
	}
	else
	{
		return path;
	}
}

bool GTools::decompressZip(const std::string &zip, const std::string outDir, std::string& errorStr, void(*percentCall)(int, int, void*), void* data/* = NULL*/)
{
	std::string rootPath = outDir;

	if (rootPath.empty())
	{
		// Find root path for zip file
		size_t pos = zip.find_last_of("/\\");
		if (pos == std::string::npos)
		{
			errorStr = cocos2d::StringUtils::format("no root path specified for zip file %s\n", zip.c_str());
			return false;
		}
		rootPath = zip.substr(0, pos + 1);
	}
	if (rootPath.back() != '/' && rootPath.back() != '\\')
	{
		rootPath.push_back('/');
	}


	// Open the zip file
	unzFile zipfile = cocos2d::unzOpen(cocos2d::FileUtils::getInstance()->getSuitableFOpen(zip).c_str());
	if (!zipfile)
	{
		errorStr = cocos2d::StringUtils::format("can not open downloaded zip file %s\n", zip.c_str());
		return false;
	}

	// Get info about the zip file
	cocos2d::unz_global_info global_info;
	if (cocos2d::unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
	{
		errorStr = cocos2d::StringUtils::format("can not read file global info of %s\n", zip.c_str());
		cocos2d::unzClose(zipfile);
		return false;
	}

	// Buffer to hold data read from the zip file
	char readBuffer[BUFFER_SIZE];
	// Loop to extract all files.
	uLong i;
	for (i = 0; i < global_info.number_entry; ++i)
	{
		// Get info about current file.
		cocos2d::unz_file_info fileInfo;
		char fileName[MAX_FILENAME];
		if (cocos2d::unzGetCurrentFileInfo(zipfile,
			&fileInfo,
			fileName,
			MAX_FILENAME,
			NULL,
			0,
			NULL,
			0) != UNZ_OK)
		{
			errorStr = cocos2d::StringUtils::format("can not read compressed file info\n");
			cocos2d::unzClose(zipfile);
			return false;
		}
		const std::string fullPath = rootPath + fileName;

		// Check if this entry is a directory or a file.
		const size_t filenameLength = strlen(fileName);
		if (fileName[filenameLength - 1] == '/')
		{
			//There are not directory entry in some case.
			//So we need to create directory when decompressing file entry
			if (!cocos2d::FileUtils::getInstance()->createDirectory(GTools::getBasename(fullPath)))
			{
				// Failed to create directory
				errorStr = cocos2d::StringUtils::format("can not create directory %s\n", fullPath.c_str());
				cocos2d::unzClose(zipfile);
				return false;
			}
		}
		else
		{
			// Create all directories in advance to avoid issue
			std::string dir = GTools::getBasename(fullPath);
			if (!cocos2d::FileUtils::getInstance()->isDirectoryExist(dir)) {
				if (!cocos2d::FileUtils::getInstance()->createDirectory(dir)) {
					// Failed to create directory
					errorStr = cocos2d::StringUtils::format("can not create directory %s\n", fullPath.c_str());
					cocos2d::unzClose(zipfile);
					return false;
				}
			}
			// Entry is a file, so extract it.
			// Open current file.
			if (cocos2d::unzOpenCurrentFile(zipfile) != UNZ_OK)
			{
				errorStr = cocos2d::StringUtils::format("can not extract file %s\n", fileName);
				cocos2d::unzClose(zipfile);
				return false;
			}

			// Create a file to store current file.
			FILE *out = fopen(cocos2d::FileUtils::getInstance()->getSuitableFOpen(fullPath).c_str(), "wb");
			if (!out)
			{
				errorStr = cocos2d::StringUtils::format("can not create decompress destination file %s (errno: %d)\n", fullPath.c_str(), errno);
				cocos2d::unzCloseCurrentFile(zipfile);
				cocos2d::unzClose(zipfile);
				return false;
			}

			// Write current file content to destinate file.
			int error = UNZ_OK;
			do
			{
				error = cocos2d::unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
				if (error < 0)
				{
					errorStr = cocos2d::StringUtils::format("can not read zip file %s, error code is %d\n", fileName, error);
					fclose(out);
					cocos2d::unzCloseCurrentFile(zipfile);
					cocos2d::unzClose(zipfile);
					return false;
				}

				if (error > 0)
				{
					fwrite(readBuffer, error, 1, out);
				}
			} while (error > 0);

			fclose(out);
		}

		cocos2d::unzCloseCurrentFile(zipfile);

		// Goto next entry listed in the zip file.
		if ((i + 1) < global_info.number_entry)
		{
			if (cocos2d::unzGoToNextFile(zipfile) != UNZ_OK)
			{
				errorStr = cocos2d::StringUtils::format("can not read next file for decompressing\n");
				cocos2d::unzClose(zipfile);
				return false;
			}
		}

		if (percentCall != NULL)
		{
			percentCall(i + 1, global_info.number_entry, data);
		}
	}

	cocos2d::unzClose(zipfile);
	return true;
}

void GTools::decompressZipAsync(const std::string& zip, const std::string outDir,bool removeFile, const std::function<void(bool, std::string)>& result, const std::function<void(int, int)>& percent)
{
	struct AsyncData
	{
		std::string zipFile;
		std::string outDir;
		std::string error;
		bool succeed;
		std::function<void(bool, std::string)> resultCall;
		std::function<void(int, int)> percentCall;
		bool removeFile;
	};

	AsyncData* asyncData = new AsyncData;
	asyncData->zipFile = zip;
	asyncData->outDir = outDir;
	asyncData->succeed = false;
	asyncData->resultCall = std::move(result);
	asyncData->percentCall = std::move(percent);
	asyncData->removeFile = removeFile;


	std::function<void(void*)> decompressFinished = [](void* param) {
		auto dataInner = reinterpret_cast<AsyncData*>(param);
		if (dataInner->succeed)
		{
			if (dataInner->resultCall)
			{
				dataInner->resultCall(true, "");
			}
		}
		else
		{
			//std::string errorMsg = cocos2d::StringUtils::format("Unable to decompress file : %s\nerror: %s", dataInner->zipFile.c_str(), dataInner->error.c_str());

			if (dataInner->resultCall)
			{
				dataInner->resultCall(false, dataInner->error);
			}
		}
		delete dataInner;
	};

	cocos2d::AsyncTaskPool::getInstance()->enqueue(cocos2d::AsyncTaskPool::TaskType::TASK_OTHER, std::move(decompressFinished), (void*)asyncData, [asyncData]() {
		void(*zipPercent)(int, int, void*) = NULL;
		if (asyncData->percentCall != nullptr)
		{
			zipPercent = [](int now, int total, void* data) 
			{
				auto dataInner = reinterpret_cast<AsyncData*>(data);
				cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread(std::bind(dataInner->percentCall, now, total));
			};
		}

		// Decompress all compressed files
		if (GTools::decompressZip(asyncData->zipFile, asyncData->outDir, asyncData->error, zipPercent, (void*)asyncData))
		{
			asyncData->succeed = true;
			if (asyncData->removeFile)
			{
				GTools::removeFile(asyncData->zipFile);
			}
		}
	});
}

bool GTools::removeFile(const std::string& filepath)
{
	auto fileUtils = cocos2d::FileUtils::getInstance();
	if (fileUtils->isFileExist(filepath))
	{
		return fileUtils->removeFile(filepath);
	}
	return true;
}

bool GTools::copyFile(const std::string& filepath, const std::string& newFilepath)
{
	auto fileUtils = cocos2d::FileUtils::getInstance();

	if (false == fileUtils->isAbsolutePath(filepath) || false == fileUtils->isAbsolutePath(newFilepath))
		return false;

	if (!fileUtils->isFileExist(filepath))
	{
		return false;
	}

	Data d;
	fileUtils->getContents(filepath, &d);
	return fileUtils->writeDataToFile(d, newFilepath);
}




/// 粒子特效类型更改
static void __changeParticleSystemPositionType(Node* root, int type)
{
	if (root == NULL)
		return;

	auto particleSys = dynamic_cast<ParticleSystem*>(root);
	if (particleSys)
	{
		particleSys->setPositionType((ParticleSystem::PositionType)type);
	}

	auto& child = root->getChildren();
	for (auto& it : child)
	{
		__changeParticleSystemPositionType(it, type);
	}
}



void GTools::changeParticleSystemPositionType(Node* root, int type)
{
	CC_ASSERT(type >= (int)ParticleSystem::PositionType::FREE || type <= (int)ParticleSystem::PositionType::GROUPED);
	if (root == NULL)
		return;

	auto armature = dynamic_cast<cocostudio::Armature*>(root);
	if (armature)
	{
		auto& boneDic = armature->getBoneDic();
		for (auto& it : boneDic)
		{
			__changeParticleSystemPositionType(it.second->getDisplayRenderNode(), type);
		}
	}

	auto& child = root->getChildren();
	for (auto& it : child)
	{
		changeParticleSystemPositionType(it, type);
	}
}

uint32_t GTools::U32_OR(uint32_t src, uint32_t dst)
{
	return src | dst;
}

uint32_t GTools::U32_AND(uint32_t src, uint32_t dst)
{
	return src & dst;
}

uint32_t GTools::U32_BIT_SET(uint32_t b, uint32_t flag)
{
	G_BIT_SET(b, flag);
	return b;
}

uint32_t GTools::U32_BIT_GET(uint32_t b, uint32_t flag)
{
	return G_BIT_GET(b, flag);
}

uint32_t GTools::U32_BIT_REMOVE(uint32_t b, uint32_t flag)
{
	G_BIT_REMOVE(b, flag);
	return b;
}

bool GTools::U32_BIT_EQUAL(uint32_t b, uint32_t flag)
{
	return G_BIT_EQUAL(b, flag);
}

bool GTools::U32_BIT_NO_EQUAL(uint32_t b, uint32_t flag)
{
	return G_BIT_NO_EQUAL(b, flag);
}

uint32_t GTools::U32_L_SHIFT(uint32_t src, uint32_t move)
{
	return src << move;
}