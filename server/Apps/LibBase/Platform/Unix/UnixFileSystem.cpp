#include "GFileSystem.h"

#if G_TARGET_PLATFORM != G_PLATFORM_WIN32

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>


bool GFileSystem::isFileExist(const std::string& filename)
{
	if (filename.empty())
	{
		return false;
	}

	struct stat sts;
	return (stat(filename.c_str(), &sts) != -1) ? true : false;
}

bool GFileSystem::isDirectoryExist(const std::string& path)
{
	struct stat st;
	if (stat(path.c_str(), &st) == 0)
	{
		return S_ISDIR(st.st_mode);
	}
	return false;
}

bool GFileSystem::createDirectory(const std::string& dirPath)
{
	G_ASSERT(!dirPath.empty());
	
	if (isDirectoryExist(dirPath))
		return true;

	// Split the path
	size_t start = 0;
	size_t found = dirPath.find_first_of("/\\", start);
	std::string subpath;
	std::vector<std::string> dirs;

	if (found != std::string::npos)
	{
		while (true)
		{
			subpath = dirPath.substr(start, found - start + 1);
			if (!subpath.empty())
				dirs.push_back(subpath);
			start = found + 1;
			found = dirPath.find_first_of("/\\", start);
			if (found == std::string::npos)
			{
				if (start < dirPath.length())
				{
					dirs.push_back(dirPath.substr(start));
				}
				break;
			}
		}
	}

	DIR *dir = NULL;

	// Create path recursively
	subpath = "";
	for (const auto& iter : dirs)
	{
		subpath += iter;
		dir = opendir(subpath.c_str());

		if (!dir)
		{
			// directory doesn't exist, should create a new one

			int ret = mkdir(subpath.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
			if (ret != 0 && (errno != EEXIST))
			{
				// current directory can not be created, sub directories can not be created too
				// should return
				return false;
			}
		}
		else
		{
			// directory exists, should close opened dir
			closedir(dir);
		}
	}
	return true;
}

bool GFileSystem::removeDirectory(const std::string& dirPath)
{
	std::string command = "rm -r ";
	// Path may include space.
	command += "\"" + dirPath + "\"";
	if (system(command.c_str()) >= 0)
		return true;
	else
		return false;
}

bool GFileSystem::removeFile(const std::string &filepath)
{
	if (remove(filepath.c_str())) {
		return false;
	}
	else {
		return true;
	}
}

bool GFileSystem::renameFile(const std::string &oldfullpath, const std::string &newfullpath)
{
	G_ASSERT(!oldfullpath.empty());
	G_ASSERT(!newfullpath.empty());

	int errorCode = rename(oldfullpath.c_str(), newfullpath.c_str());

	if (0 != errorCode)
	{
		LOG(ERROR) << "Fail to rename file " << oldfullpath.c_str() << " to " << newfullpath.c_str() << " !Error code is " << errorCode;
		return false;
	}
	return true;
}

int64_t GFileSystem::getFileSize(const std::string& path)
{
	if (!isFileExist(path))
		return 0LL;

	struct stat info;
	// Get data associated with "crt_stat.c":
	int result = stat(path.c_str(), &info);

	// Check if statistics are valid:
	if (result != 0)
	{
		// Failed
		return 0LL;
	}
	else
	{
		return (int64_t)(info.st_size);
	}
}

uint8_t* GFileSystem::readFile(const std::string& filename, uint32_t& outSize)
{
	outSize = 0;

	if (!isFileExist(filename))
		return NULL;

	FILE *fp = fopen(filename.c_str(), "rb");
	if (!fp)
		return NULL;

#if defined(_MSC_VER)
	auto descriptor = _fileno(fp);
#else
	auto descriptor = fileno(fp);
#endif
	struct stat statBuf;
	if (fstat(descriptor, &statBuf) == -1) {
		fclose(fp);
		// ReadFailed
		return NULL;
	}
	size_t size = statBuf.st_size;

	uint8_t* buffer = (uint8_t*)malloc(size);
	size_t readsize = fread(buffer, 1, size, fp);
	fclose(fp);

	if (readsize < size) {
		free(buffer);
		return NULL;
	}

	outSize = (uint32_t)size;
	return buffer;
}

std::string GFileSystem::readStringFromFile(const std::string& filename)
{
	std::string content;
	readStringFromFile(filename, content);
	return content;
}

bool GFileSystem::readStringFromFile(const std::string& filename, std::string& outData)
{
	uint32_t len = 0;
	auto data = readFile(filename, len);
	if (data == NULL)
		return false;

	outData.assign((const char*)data, len);

	free(data);
	return true;
}

bool GFileSystem::writeFile(const std::string& path, uint8_t* buffer, uint32_t size)
{
	const char* mode = "wb";

	G_ASSERT(!path.empty());
	G_ASSERT(buffer != NULL && size > 0);

	do
	{
		G_BREAK_IF(buffer == NULL || size <= 0);

		// Read the file from hardware
		FILE *fp = fopen(path.c_str(), mode);
		G_BREAK_IF(!fp);

		fwrite(buffer, (size_t)size, 1, fp);

		fclose(fp);

		return true;
	} while (0);

	return false;
}

bool GFileSystem::writeTextFile(const std::string& path, const std::string& text)
{
	return writeFile(path, (uint8_t*)text.c_str(), (uint32_t)text.size());
}

#endif