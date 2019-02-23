/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "GameAssetsManager.h"
#include "GameAssetsManagerEventListener.h"
#include "base/ccUTF8.h"
#include "base/CCDirector.h"
#include "deprecated/CCString.h"

#include <stdio.h>

#ifdef MINIZIP_FROM_SYSTEM
#include <minizip/unzip.h>
#else // from our embedded sources
#include "external/unzip/unzip.h"
#endif
#include "base/CCAsyncTaskPool.h"

#include "tinydir/tinydir.h"

#define TEMP_PACKAGE_SUFFIX     "_temp"
#define VERSION_FILENAME        "version.manifest"
#define TEMP_MANIFEST_FILENAME  "project.manifest.temp"
#define MANIFEST_FILENAME       "project.manifest"
#define DOWNLOAD_MANIFEST_FILENAME       "download_project.manifest"

#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

#define DEFAULT_CONNECTION_TIMEOUT 45

#define SAVE_POINT_INTERVAL 0.1f

const std::string GameAssetsManager::VERSION_ID = "@version";
const std::string GameAssetsManager::MANIFEST_ID = "@manifest";


using namespace cocos2d;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

static std::wstring StringUtf8ToWideChar(const std::string& strUtf8)
{
	std::wstring ret;
	if (!strUtf8.empty())
	{
		int nNum = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, nullptr, 0);
		if (nNum)
		{
			WCHAR* wideCharString = new WCHAR[nNum + 1];
			wideCharString[0] = 0;

			nNum = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, wideCharString, nNum + 1);

			ret = wideCharString;
			delete[] wideCharString;
		}
		else
		{
			CCLOG("Wrong convert to WideChar code:0x%x", GetLastError());
		}
	}
	return ret;
}

static std::string StringWideCharToUtf8(const std::wstring& strWideChar)
{
	std::string ret;
	if (!strWideChar.empty())
	{
		int nNum = WideCharToMultiByte(CP_UTF8, 0, strWideChar.c_str(), -1, nullptr, 0, nullptr, FALSE);
		if (nNum)
		{
			char* utf8String = new char[nNum + 1];
			utf8String[0] = 0;

			nNum = WideCharToMultiByte(CP_UTF8, 0, strWideChar.c_str(), -1, utf8String, nNum + 1, nullptr, FALSE);

			ret = utf8String;
			delete[] utf8String;
		}
		else
		{
			CCLOG("Wrong convert to Utf8 code:0x%x", GetLastError());
		}
	}

	return ret;
}

static void listFilesRecursively(const std::string& dirPath, std::vector<std::string> *files)
{
	FileUtils* fileUtils = FileUtils::getInstance();
	std::string fullpath = fileUtils->fullPathForFilename(dirPath);
	if (fileUtils->isDirectoryExist(fullpath))
	{
		tinydir_dir dir;
		std::wstring fullpathstr = StringUtf8ToWideChar(fullpath);

		if (tinydir_open(&dir, &fullpathstr[0]) != -1)
		{
			while (dir.has_next)
			{
				tinydir_file file;
				if (tinydir_readfile(&dir, &file) == -1)
				{
					// Error getting file
					break;
				}
				std::string fileName = StringWideCharToUtf8(file.name);

				if (fileName != "." && fileName != "..")
				{
					std::string filepath = StringWideCharToUtf8(file.path);
					if (file.is_dir)
					{
						filepath.append("/");
						files->push_back(filepath);
						listFilesRecursively(filepath, files);
					}
					else
					{
						files->push_back(filepath);
					}
				}

				if (tinydir_next(&dir) == -1)
				{
					// Error getting next file
					break;
				}
			}
		}
		tinydir_close(&dir);
	}
}
#else
static void listFilesRecursively(const std::string& dirPath, std::vector<std::string> *files)
{
	FileUtils* fileUtils = FileUtils::getInstance();

	std::string fullpath = fileUtils->fullPathForFilename(dirPath);
	if (fileUtils->isDirectoryExist(fullpath))
	{
		tinydir_dir dir;
		std::string fullpathstr = fullpath;

		if (tinydir_open(&dir, &fullpathstr[0]) != -1)
		{
			while (dir.has_next)
			{
				tinydir_file file;
				if (tinydir_readfile(&dir, &file) == -1)
				{
					// Error getting file
					break;
				}
				std::string fileName = file.name;

				if (fileName != "." && fileName != "..")
				{
					std::string filepath = file.path;
					if (file.is_dir)
					{
						filepath.append("/");
						files->push_back(filepath);
						listFilesRecursively(filepath, files);
					}
					else
					{
						files->push_back(filepath);
					}
				}

				if (tinydir_next(&dir) == -1)
				{
					// Error getting next file
					break;
				}
			}
		}
		tinydir_close(&dir);
	}
}
#endif


// Implementation of GameAssetsManager

GameAssetsManager::GameAssetsManager(const std::string& manifestUrl, const std::string& storagePath, const std::string& platformName)
: _updateState(State::UNCHECKED)
, _assets(nullptr)
, _storagePath("")
, _tempVersionPath("")
, _cacheManifestPath("")
, _tempManifestPath("")
, _manifestUrl(manifestUrl)
, _localManifest(nullptr)
, _tempManifest(nullptr)
, _remoteManifest(nullptr)
, _updateEntry(UpdateEntry::NONE)
, _percent(0)
, _percentByFile(0)
, _totalToDownload(0)
, _totalWaitToDownload(0)
, _nextSavePoint(0.0)
, _maxConcurrentTask(2)
, _currConcurrentTask(0)
, _versionCompareHandle(nullptr)
, _verifyCallback(nullptr)
, _inited(false)
, _isCalculateUpdateFileSize(false)
, _enablePercentFileMap(false)
, _updateDownloadFilePercent(0)
{
    // Init variables
	_platformName = platformName;

    _eventDispatcher = Director::getInstance()->getEventDispatcher();
    std::string pointer = StringUtils::format("%p", this);
    _eventName = GameAssetsManagerEventListener::LISTENER_ID + pointer;
    _fileUtils = FileUtils::getInstance();

	cocos2d::network::DownloaderHints hints =
    {
        static_cast<uint32_t>(_maxConcurrentTask),
        DEFAULT_CONNECTION_TIMEOUT,
        ".tmp"
    };
    _downloader = std::shared_ptr<cocos2d::network::Downloader>(new cocos2d::network::Downloader(hints));
    _downloader->onTaskError = std::bind(&GameAssetsManager::onError, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
    _downloader->onTaskProgress = [this](const cocos2d::network::DownloadTask& task,
                                         int64_t /*bytesReceived*/,
                                         int64_t totalBytesReceived,
                                         int64_t totalBytesExpected)
    {
        this->onProgress(totalBytesExpected, totalBytesReceived, task.requestURL, task.identifier);
    };
    _downloader->onFileTaskSuccess = [this](const cocos2d::network::DownloadTask& task)
    {
        this->onSuccess(task.requestURL, task.storagePath, task.identifier);
    };
    setStoragePath(storagePath);
    _tempVersionPath = _tempStoragePath + VERSION_FILENAME;
    _cacheManifestPath = _storagePath + MANIFEST_FILENAME;
    _tempManifestPath = _tempStoragePath + TEMP_MANIFEST_FILENAME;
	_downloadManifestPath = _tempStoragePath + DOWNLOAD_MANIFEST_FILENAME;

    initManifests(manifestUrl);
}

GameAssetsManager::~GameAssetsManager()
{
    _downloader->onTaskError = (nullptr);
    _downloader->onFileTaskSuccess = (nullptr);
    _downloader->onTaskProgress = (nullptr);
    CC_SAFE_RELEASE(_localManifest);
    // _tempManifest could share a ptr with _remoteManifest or _localManifest
    if (_tempManifest != _localManifest && _tempManifest != _remoteManifest)
        CC_SAFE_RELEASE(_tempManifest);
    CC_SAFE_RELEASE(_remoteManifest);
}

GameAssetsManager* GameAssetsManager::create(const std::string& manifestUrl, const std::string& storagePath, const std::string& platformName)
{
    GameAssetsManager* ret = new (std::nothrow) GameAssetsManager(manifestUrl, storagePath, platformName);
    if (ret)
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void GameAssetsManager::initManifests(const std::string& manifestUrl)
{
    _inited = true;
    // Init and load local manifest
    _localManifest = new (std::nothrow) GameManifest("", _platformName);
    if (_localManifest)
    {
        loadLocalManifest(manifestUrl);
        
        // Init and load temporary manifest
        _tempManifest = new (std::nothrow) GameManifest("", _platformName);
        if (_tempManifest)
        {
            _tempManifest->parse(_tempManifestPath);
            // Previous update is interrupted
            if (_fileUtils->isFileExist(_tempManifestPath))
            {
                // Manifest parse failed, remove all temp files
                if (!_tempManifest->isLoaded())
                {
                    _fileUtils->removeDirectory(_tempStoragePath);
                    CC_SAFE_RELEASE(_tempManifest);
					_tempManifest = nullptr;
					_fileUtils->createDirectory(_tempStoragePath);
                }
            }
        }
        else
        {
            _inited = false;
        }
        
        // Init remote manifest for future usage
        _remoteManifest = new (std::nothrow) GameManifest("", _platformName);
        if (!_remoteManifest)
        {
            _inited = false;
        }
    }
    else
    {
        _inited = false;
    }
    
    if (!_inited)
    {
        CC_SAFE_RELEASE(_localManifest);
        CC_SAFE_RELEASE(_tempManifest);
        CC_SAFE_RELEASE(_remoteManifest);
        _localManifest = nullptr;
        _tempManifest = nullptr;
        _remoteManifest = nullptr;
    }
}

void GameAssetsManager::prepareLocalManifest()
{
    // An alias to assets
    _assets = &(_localManifest->getAssets());

    // Add search paths
    _localManifest->prependSearchPaths();
}

void GameAssetsManager::loadLocalManifest(const std::string& /*manifestUrl*/)
{
	GameManifest *cachedManifest = nullptr;
    // Find the cached manifest file
    if (_fileUtils->isFileExist(_cacheManifestPath))
    {
        cachedManifest = new (std::nothrow) GameManifest("", _platformName);
        if (cachedManifest) {
            cachedManifest->parse(_cacheManifestPath);
            if (!cachedManifest->isLoaded())
            {
                _fileUtils->removeFile(_cacheManifestPath);
                CC_SAFE_RELEASE(cachedManifest);
                cachedManifest = nullptr;
            }
        }
    }
	    
    // Ensure no search path of cached manifest is used to load this manifest
    std::vector<std::string> searchPaths = _fileUtils->getSearchPaths();
    if (cachedManifest)
    {
        std::vector<std::string> cacheSearchPaths = cachedManifest->getSearchPaths();
        std::vector<std::string> trimmedPaths = searchPaths;
        for (auto path : cacheSearchPaths)
        {
            const auto pos = std::find(trimmedPaths.begin(), trimmedPaths.end(), path);
            if (pos != trimmedPaths.end())
            {
                trimmedPaths.erase(pos);
            }
        }
        _fileUtils->setSearchPaths(trimmedPaths);
    }
    // Load local manifest in app package
    _localManifest->parse(_manifestUrl);
    if (cachedManifest) {
        // Restore search paths
        _fileUtils->setSearchPaths(searchPaths);
    }
    if (_localManifest->isLoaded())
    {
        // Compare with cached manifest to determine which one to use
        if (cachedManifest) {
            bool localNewer = _localManifest->versionGreater(cachedManifest, _versionCompareHandle);

			// 判断本地强更新版本是否大于缓存版本
			if (!localNewer)
			{
				localNewer = _localManifest->getStrongUpdateVersion() > cachedManifest->getStrongUpdateVersion();
			}

            if (localNewer)
            {
                // Recreate storage, to empty the content
                _fileUtils->removeDirectory(_storagePath);
                _fileUtils->createDirectory(_storagePath);
				// 清空临时目录
				_fileUtils->removeDirectory(_tempStoragePath);
				_fileUtils->createDirectory(_tempStoragePath);

                CC_SAFE_RELEASE(cachedManifest);
            }
            else
            {
                CC_SAFE_RELEASE(_localManifest);
                _localManifest = cachedManifest;
            }
        }
        prepareLocalManifest();
    }

    // Fail to load local manifest
    if (!_localManifest->isLoaded())
    {
        CCLOG("GameAssetsManager : No local manifest file found error.\n");
        dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::ERROR_NO_LOCAL_MANIFEST);
    }
}

std::string GameAssetsManager::basename(const std::string& path) const
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

std::string GameAssetsManager::get(const std::string& key) const
{
    auto it = _assets->find(key);
    if (it != _assets->cend()) {
        return _storagePath + it->second.path;
    }
    else return "";
}

const GameManifest* GameAssetsManager::getLocalManifest() const
{
    return _localManifest;
}

const GameManifest* GameAssetsManager::getRemoteManifest() const
{
    return _remoteManifest;
}

const std::string& GameAssetsManager::getStoragePath() const
{
    return _storagePath;
}

void GameAssetsManager::setVersionCompareLuaHandle(const LuaFunction& handle)
{
	_versionCompareLuaHandle = std::move(handle);
	this->setVersionCompareHandle([this](const std::string& versionA, const std::string& versionB)->int
	{
		_versionCompareLuaHandle.ppush();
		_versionCompareLuaHandle.pusharg(versionA.c_str());
		_versionCompareLuaHandle.pusharg(versionB.c_str());
		_versionCompareLuaHandle.pcall(1);

		return _versionCompareLuaHandle.retint();
	});
}

void GameAssetsManager::setVerifyLuaCallback(const LuaFunction& handle)
{
	_verifyLuaHandle = std::move(handle);
	this->setVerifyCallback([this](const std::string& path, GameManifest::Asset asset)->bool
	{
		_verifyLuaHandle.ppush();
		_verifyLuaHandle.pusharg(path.c_str());
		_verifyLuaHandle.pushusertype(&asset, "GameManifestAsset");
		_verifyLuaHandle.pcall(1);

		return _verifyLuaHandle.retbool();
	});
}

void GameAssetsManager::setUpdateDownloadFilePercentLuaCallback(const LuaFunction& handle)
{
	_updateDownloadFilePercentLuaHandle = std::move(handle);
}

void GameAssetsManager::setStoragePath(const std::string& storagePath)
{
    _storagePath = storagePath;
    adjustPath(_storagePath);
    _fileUtils->createDirectory(_storagePath);
    
    _tempStoragePath = _storagePath;
    _tempStoragePath.insert(_storagePath.size() - 1, TEMP_PACKAGE_SUFFIX);
    _fileUtils->createDirectory(_tempStoragePath);
}

void GameAssetsManager::adjustPath(std::string &path)
{
    if (path.size() > 0 && path[path.size() - 1] != '/')
    {
        path.append("/");
    }
}

bool GameAssetsManager::decompress(const std::string &zip)
{
    // Find root path for zip file
    size_t pos = zip.find_last_of("/\\");
    if (pos == std::string::npos)
    {
        CCLOG("GameAssetsManager : no root path specified for zip file %s\n", zip.c_str());
        return false;
    }
    const std::string rootPath = zip.substr(0, pos+1);
    
    // Open the zip file
    unzFile zipfile = unzOpen(FileUtils::getInstance()->getSuitableFOpen(zip).c_str());
    if (! zipfile)
    {
        CCLOG("GameAssetsManager : can not open downloaded zip file %s\n", zip.c_str());
        return false;
    }
    
    // Get info about the zip file
    unz_global_info global_info;
    if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
    {
        CCLOG("GameAssetsManager : can not read file global info of %s\n", zip.c_str());
        unzClose(zipfile);
        return false;
    }
    
    // Buffer to hold data read from the zip file
    char readBuffer[BUFFER_SIZE];
    // Loop to extract all files.
    uLong i;
    for (i = 0; i < global_info.number_entry; ++i)
    {
        // Get info about current file.
        unz_file_info fileInfo;
        char fileName[MAX_FILENAME];
        if (unzGetCurrentFileInfo(zipfile,
                                  &fileInfo,
                                  fileName,
                                  MAX_FILENAME,
                                  NULL,
                                  0,
                                  NULL,
                                  0) != UNZ_OK)
        {
            CCLOG("GameAssetsManager : can not read compressed file info\n");
            unzClose(zipfile);
            return false;
        }
        const std::string fullPath = rootPath + fileName;
        
        // Check if this entry is a directory or a file.
        const size_t filenameLength = strlen(fileName);
        if (fileName[filenameLength-1] == '/')
        {
            //There are not directory entry in some case.
            //So we need to create directory when decompressing file entry
            if ( !_fileUtils->createDirectory(basename(fullPath)) )
            {
                // Failed to create directory
                CCLOG("GameAssetsManager : can not create directory %s\n", fullPath.c_str());
                unzClose(zipfile);
                return false;
            }
        }
        else
        {
            // Create all directories in advance to avoid issue
            std::string dir = basename(fullPath);
            if (!_fileUtils->isDirectoryExist(dir)) {
                if (!_fileUtils->createDirectory(dir)) {
                    // Failed to create directory
                    CCLOG("GameAssetsManager : can not create directory %s\n", fullPath.c_str());
                    unzClose(zipfile);
                    return false;
                }
            }
            // Entry is a file, so extract it.
            // Open current file.
            if (unzOpenCurrentFile(zipfile) != UNZ_OK)
            {
                CCLOG("GameAssetsManager : can not extract file %s\n", fileName);
                unzClose(zipfile);
                return false;
            }
            
            // Create a file to store current file.
            FILE *out = fopen(FileUtils::getInstance()->getSuitableFOpen(fullPath).c_str(), "wb");
            if (!out)
            {
                CCLOG("GameAssetsManager : can not create decompress destination file %s (errno: %d)\n", fullPath.c_str(), errno);
                unzCloseCurrentFile(zipfile);
                unzClose(zipfile);
                return false;
            }
            
            // Write current file content to destinate file.
            int error = UNZ_OK;
            do
            {
                error = unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
                if (error < 0)
                {
                    CCLOG("GameAssetsManager : can not read zip file %s, error code is %d\n", fileName, error);
                    fclose(out);
                    unzCloseCurrentFile(zipfile);
                    unzClose(zipfile);
                    return false;
                }
                
                if (error > 0)
                {
                    fwrite(readBuffer, error, 1, out);
                }
            } while(error > 0);
            
            fclose(out);
        }
        
        unzCloseCurrentFile(zipfile);
        
        // Goto next entry listed in the zip file.
        if ((i+1) < global_info.number_entry)
        {
            if (unzGoToNextFile(zipfile) != UNZ_OK)
            {
                CCLOG("GameAssetsManager : can not read next file for decompressing\n");
                unzClose(zipfile);
                return false;
            }
        }
    }
    
    unzClose(zipfile);
    return true;
}

void GameAssetsManager::decompressDownloadedZip(const std::string &customId, const std::string &storagePath)
{
    struct AsyncData
    {
        std::string customId;
        std::string zipFile;
        bool succeed;
    };
    
    AsyncData* asyncData = new AsyncData;
    asyncData->customId = customId;
    asyncData->zipFile = storagePath;
    asyncData->succeed = false;
    
    std::function<void(void*)> decompressFinished = [this](void* param) {
        auto dataInner = reinterpret_cast<AsyncData*>(param);
        if (dataInner->succeed)
        {
            fileSuccess(dataInner->customId, dataInner->zipFile);
        }
        else
        {
            std::string errorMsg = "Unable to decompress file " + dataInner->zipFile;
            // Ensure zip file deletion (if decompress failure cause task thread exit anormally)
            _fileUtils->removeFile(dataInner->zipFile);
            dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::ERROR_DECOMPRESS, "", errorMsg);
            fileError(dataInner->customId, errorMsg);
        }
        delete dataInner;
    };
    AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_OTHER, std::move(decompressFinished), (void*)asyncData, [this, asyncData]() {
        // Decompress all compressed files
        if (decompress(asyncData->zipFile))
        {
            asyncData->succeed = true;
        }
        _fileUtils->removeFile(asyncData->zipFile);
    });
}

void GameAssetsManager::dispatchUpdateEvent(GameAssetsManagerEvent::EventCode code, const std::string &assetId/* = ""*/, const std::string &message/* = ""*/, int curle_code/* = CURLE_OK*/, int curlm_code/* = CURLM_OK*/)
{
    switch (code)
    {
        case GameAssetsManagerEvent::EventCode::ERROR_UPDATING:
        case GameAssetsManagerEvent::EventCode::ERROR_PARSE_MANIFEST:
        case GameAssetsManagerEvent::EventCode::ERROR_NO_LOCAL_MANIFEST:
        case GameAssetsManagerEvent::EventCode::ERROR_DECOMPRESS:
        case GameAssetsManagerEvent::EventCode::ERROR_DOWNLOAD_MANIFEST:
        case GameAssetsManagerEvent::EventCode::UPDATE_FAILED:
        case GameAssetsManagerEvent::EventCode::UPDATE_FINISHED:
        case GameAssetsManagerEvent::EventCode::ALREADY_UP_TO_DATE:
            _updateEntry = UpdateEntry::NONE;
            break;
        case GameAssetsManagerEvent::EventCode::UPDATE_PROGRESSION:
            break;
        case GameAssetsManagerEvent::EventCode::ASSET_UPDATED:
            break;
        case GameAssetsManagerEvent::EventCode::NEW_VERSION_FOUND:
            if (_updateEntry == UpdateEntry::CHECK_UPDATE)
            {
                _updateEntry = UpdateEntry::NONE;
            }
            break;
        default:
            break;
    }

    GameAssetsManagerEvent event(_eventName, this, code, _percent, _percentByFile, assetId, message, curle_code, curlm_code);
    _eventDispatcher->dispatchEvent(&event);
}

GameAssetsManager::State GameAssetsManager::getState() const
{
    return _updateState;
}

void GameAssetsManager::downloadVersion()
{
    if (_updateState > State::PREDOWNLOAD_VERSION)
        return;

    std::string versionUrl = _localManifest->getVersionFileUrl();

    if (versionUrl.size() > 0)
    {
        _updateState = State::DOWNLOADING_VERSION;
        // Download version file asynchronously
        _downloader->createDownloadFileTask(versionUrl, _tempVersionPath, VERSION_ID);
    }
    // No version file found
    else
    {
        CCLOG("GameAssetsManager : No version file found, step skipped\n");
        _updateState = State::PREDOWNLOAD_MANIFEST;
        downloadManifest();
    }
}

void GameAssetsManager::parseVersion()
{
    if (_updateState != State::VERSION_LOADED)
        return;

    _remoteManifest->parseVersion(_tempVersionPath);

    if (!_remoteManifest->isVersionLoaded())
    {
        CCLOG("GameAssetsManager : Fail to parse version file, step skipped\n");
        _updateState = State::PREDOWNLOAD_MANIFEST;
        downloadManifest();
    }
    else
    {
		// 需要强更新
		if (_localManifest->isNeedStrongUpdate(_remoteManifest))
		{
			_updateState = State::NEED_UPDATE;
			_fileUtils->removeDirectory(_tempStoragePath);
			dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::NEED_STRONG_UPDATE);
		}
		else
		{
			if (_localManifest->versionGreater(_remoteManifest, _versionCompareHandle))
			{
				_updateState = State::UP_TO_DATE;
				_fileUtils->removeDirectory(_tempStoragePath);
				dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::ALREADY_UP_TO_DATE);
			}
			else
			{
				_updateState = State::NEED_UPDATE;

				// Wait to update so continue the process
				if (_updateEntry == UpdateEntry::DO_UPDATE)
				{
					// dispatch after checking update entry because event dispatching may modify the update entry
					dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::NEW_VERSION_FOUND);
					_updateState = State::PREDOWNLOAD_MANIFEST;
					downloadManifest();
				}
				else
				{
					dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::NEW_VERSION_FOUND);
				}
			}
		}
    }
}

void GameAssetsManager::downloadManifest()
{
    if (_updateState != State::PREDOWNLOAD_MANIFEST)
        return;

    std::string manifestUrl;
    if (_remoteManifest->isVersionLoaded()) {
        manifestUrl = _remoteManifest->getManifestFileUrl();
    } else {
        manifestUrl = _localManifest->getManifestFileUrl();
    }

    if (manifestUrl.size() > 0)
    {
        _updateState = State::DOWNLOADING_MANIFEST;
        // Download version file asynchronously
        _downloader->createDownloadFileTask(manifestUrl, _downloadManifestPath, MANIFEST_ID);
    }
    // No manifest file found
    else
    {
        CCLOG("GameAssetsManager : No manifest file found, check update failed\n");
        dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::ERROR_DOWNLOAD_MANIFEST);
        _updateState = State::UNCHECKED;
    }
}

void GameAssetsManager::parseManifest()
{
    if (_updateState != State::MANIFEST_LOADED)
        return;

    _remoteManifest->parse(_downloadManifestPath);

    if (!_remoteManifest->isLoaded())
    {
        CCLOG("GameAssetsManager : Error parsing manifest file, %s", _downloadManifestPath.c_str());
        dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::ERROR_PARSE_MANIFEST);
        _updateState = State::UNCHECKED;
    }
    else
    {
		// 需要强更新
		if (_localManifest->isNeedStrongUpdate(_remoteManifest))
		{
			_updateState = State::NEED_UPDATE;
			_fileUtils->removeDirectory(_tempStoragePath);
			dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::NEED_STRONG_UPDATE);
		}
        else
        {
			if (_localManifest->versionGreater(_remoteManifest, _versionCompareHandle))
			{
				_updateState = State::UP_TO_DATE;
				_fileUtils->removeDirectory(_tempStoragePath);
				dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::ALREADY_UP_TO_DATE);
			}
			else
			{
				_updateState = State::NEED_UPDATE;
				dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::NEW_VERSION_FOUND);

				if (_updateEntry == UpdateEntry::DO_UPDATE)
				{
					startUpdate();
				}
			}
        }
    }
}

void GameAssetsManager::startUpdate()
{
    if (_updateState != State::NEED_UPDATE)
        return;

	calculateUpdateFileSize();
}


bool GameAssetsManager::continueUpdate()
{
	if (_updateState != State::NEED_UPDATE || !_isCalculateUpdateFileSize)
		return false;

	_isCalculateUpdateFileSize = false;

	_updateState = State::UPDATING;
	// Clean up before update
	_failedUnits.clear();
	_downloadUnits.clear();
	_totalWaitToDownload = _totalToDownload = 0;
	_nextSavePoint = 0;
	_percent = _percentByFile = _sizeCollected = _totalSize = 0;
	_downloadedSize.clear();
	_totalEnabled = false;

	// Temporary manifest exists, resuming previous download
	if (_tempManifest && _tempManifest->isLoaded() && _tempManifest->versionEquals(_remoteManifest))
	{
		_tempManifest->genResumeAssetsList(&_downloadUnits);
		_totalWaitToDownload = _totalToDownload = (int)_downloadUnits.size();
		this->batchDownload();

		std::string msg = StringUtils::format("Resuming from previous unfinished update, %d files remains to be finished.", _totalToDownload);
		dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::UPDATE_PROGRESSION, "", msg);
	}
	else
	{
		// Temporary manifest exists, but can't be parsed or version doesn't equals remote manifest (out of date)
		if (_tempManifest)
		{
			// Remove all temp files
			_fileUtils->removeDirectory(_tempStoragePath);
			CC_SAFE_RELEASE(_tempManifest);
			// Recreate temp storage path and save remote manifest
			_fileUtils->createDirectory(_tempStoragePath);
		}

		// Temporary manifest will be used to register the download states of each asset,
		// in this case, it equals remote manifest.
		_tempManifest = _remoteManifest;

		_tempManifest->setAllAssetDownloadState(GameManifest::DownloadState::SUCCESSED);

		// Check difference between local manifest and remote manifest
		std::unordered_map<std::string, GameManifest::AssetDiff> diff_map = _localManifest->genDiff(_remoteManifest);
		if (diff_map.size() == 0)
		{
			updateSucceed();
		}
		else
		{
			// Generate download units for all assets that need to be updated or added
			std::string packageUrl = _remoteManifest->getPackageUrl();

			// Preprocessing local files in previous version and creating download folders
			for (auto it = diff_map.begin(); it != diff_map.end(); ++it)
			{
				GameManifest::AssetDiff diff = it->second;
				if (diff.type != GameManifest::DiffType::DELETED)
				{
					std::string path = diff.asset.path;
					DownloadUnit unit;
					unit.customId = it->first;
					unit.srcUrl = packageUrl + path;
					unit.storagePath = _tempStoragePath + path;
					unit.size = diff.asset.size;
					unit.fileSize = diff.asset.fileSize;
					_downloadUnits.emplace(unit.customId, unit);
					_tempManifest->setAssetDownloadState(it->first, GameManifest::DownloadState::UNSTARTED);
				}
			}
			_totalWaitToDownload = _totalToDownload = (int)_downloadUnits.size();

			std::string msg = StringUtils::format("Start to update %d files from remote package.", _totalToDownload);
			dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::UPDATE_PROGRESSION, "", msg);

			this->batchDownload();
		}
	}
	return true;
}

void GameAssetsManager::savePercentFile()
{
	// Save current download manifest information for resuming
	_tempManifest->saveToFile(_tempManifestPath);
}

void GameAssetsManager::updateSucceed()
{
	savePercentFile();

    // Every thing is correctly downloaded, do the following
    // 1. rename temporary manifest to valid manifest
    std::string tempFileName = TEMP_MANIFEST_FILENAME;
    std::string fileName = MANIFEST_FILENAME;
    _fileUtils->renameFile(_tempStoragePath, tempFileName, fileName);

    // 2. merge temporary storage path to storage path so that temporary version turns to cached version
    if (_fileUtils->isDirectoryExist(_tempStoragePath))
    {
        // Merging all files in temp storage path to storage path
        std::vector<std::string> files;
        listFilesRecursively(_tempStoragePath, &files);
        int baseOffset = (int)_tempStoragePath.length();
        std::string relativePath, dstPath;
        for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it)
        {
            relativePath.assign((*it).substr(baseOffset));
            dstPath.assign(_storagePath + relativePath);
            // Create directory
            if (relativePath.back() == '/')
            {
                _fileUtils->createDirectory(dstPath);
            }
            // Copy file
            else
            {
                if (_fileUtils->isFileExist(dstPath))
                {
                    _fileUtils->removeFile(dstPath);
                }
                _fileUtils->renameFile(*it, dstPath);
            }
        }
        // Remove temp storage path
        _fileUtils->removeDirectory(_tempStoragePath);
    }
    // 3. swap the localManifest
    CC_SAFE_RELEASE(_localManifest);
    _localManifest = _remoteManifest;
    _localManifest->setManifestRoot(_storagePath);
    _remoteManifest = nullptr;
    // 4. make local manifest take effect
    prepareLocalManifest();

    // 5. Set update state
    _updateState = State::UP_TO_DATE;
    // 6. Notify finished event
    dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::UPDATE_FINISHED);
}

void GameAssetsManager::checkUpdate()
{
    if (_updateEntry != UpdateEntry::NONE)
    {
        CCLOGERROR("GameAssetsManager::checkUpdate, updateEntry isn't NONE");
        return;
    }

    if (!_inited){
        CCLOG("GameAssetsManager : Manifests uninited.\n");
        dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }
    if (!_localManifest->isLoaded())
    {
        CCLOG("GameAssetsManager : No local manifest file found error.\n");
        dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }

    _updateEntry = UpdateEntry::CHECK_UPDATE;

    switch (_updateState) {
        case State::UNCHECKED:
        case State::PREDOWNLOAD_VERSION:
        {
            downloadVersion();
        }
            break;
        case State::UP_TO_DATE:
        {
            dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::ALREADY_UP_TO_DATE);
        }
            break;
        case State::FAIL_TO_UPDATE:
        case State::NEED_UPDATE:
        {
            dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::NEW_VERSION_FOUND);
        }
            break;
        default:
            break;
    }
}

void GameAssetsManager::calculateUpdateFileSize()
{
	_isCalculateUpdateFileSize = true;

	unsigned int totalSize = 0U;

	// Temporary manifest exists, resuming previous download
	if (_tempManifest && _tempManifest->isLoaded() && _tempManifest->versionEquals(_remoteManifest))
	{
		DownloadUnits downloadUnits;
		_tempManifest->genResumeAssetsList(&downloadUnits);

		for (auto& it : downloadUnits)
		{
			totalSize += it.second.size;
		}
	}
	else
	{
		// Check difference between local manifest and remote manifest
		std::unordered_map<std::string, GameManifest::AssetDiff> diff_map = _localManifest->genDiff(_remoteManifest);
		
		// Preprocessing local files in previous version and creating download folders
		for (auto it = diff_map.begin(); it != diff_map.end(); ++it)
		{
			GameManifest::AssetDiff diff = it->second;
			if (diff.type != GameManifest::DiffType::DELETED)
			{
				totalSize = totalSize + diff.asset.fileSize;
			}
		}
	}

	std::string msg = StringUtils::toString(totalSize);
	dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::UPDATE_FILE_SIZE, "", msg);
}

void GameAssetsManager::update()
{
    if (_updateEntry != UpdateEntry::NONE)
    {
        CCLOGERROR("GameAssetsManager::update, updateEntry isn't NONE");
        return;
    }

    if (!_inited){
        CCLOG("GameAssetsManager : Manifests uninited.\n");
        dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }
    if (!_localManifest->isLoaded())
    {
        CCLOG("GameAssetsManager : No local manifest file found error.\n");
        dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }

    _updateEntry = UpdateEntry::DO_UPDATE;

    switch (_updateState) {
        case State::UNCHECKED:
        {
            _updateState = State::PREDOWNLOAD_VERSION;
        }
        case State::PREDOWNLOAD_VERSION:
        {
            downloadVersion();
        }
            break;
        case State::VERSION_LOADED:
        {
            parseVersion();
        }
            break;
        case State::PREDOWNLOAD_MANIFEST:
        {
            downloadManifest();
        }
            break;
        case State::MANIFEST_LOADED:
        {
            parseManifest();
        }
            break;
        case State::FAIL_TO_UPDATE:
        case State::NEED_UPDATE:
        {
			// 需要强更新
			if (_localManifest->isNeedStrongUpdate(_remoteManifest))
			{
				_updateState = State::NEED_UPDATE;
				_fileUtils->removeDirectory(_tempStoragePath);
				dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::NEED_STRONG_UPDATE);
			}
			else
			{
				// Manifest not loaded yet
				if (!_remoteManifest->isLoaded())
				{
					_updateState = State::PREDOWNLOAD_MANIFEST;
					downloadManifest();
				}
				else
				{
					startUpdate();
				}
			}
        }
            break;
        case State::UP_TO_DATE:
        case State::UPDATING:
        case State::UNZIPPING:
            _updateEntry = UpdateEntry::NONE;
            break;
        default:
            break;
    }
}

void GameAssetsManager::updateAssets(const DownloadUnits& assets)
{
    if (!_inited){
        CCLOG("GameAssetsManager : Manifests uninited.\n");
        dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }
    
    if (_updateState != State::UPDATING && _localManifest->isLoaded() && _remoteManifest->isLoaded())
    {
        _updateState = State::UPDATING;
        _downloadUnits.clear();
        _downloadedSize.clear();
        _percent = _percentByFile = _sizeCollected = _totalSize = 0;
        _totalWaitToDownload = _totalToDownload = (int)assets.size();
        _nextSavePoint = 0;
        _totalEnabled = false;
        if (_totalToDownload > 0)
        {
            _downloadUnits = assets;
            this->batchDownload();
        }
        else if (_totalToDownload == 0)
        {
            onDownloadUnitsFinished();
        }
    }
}

const DownloadUnits& GameAssetsManager::getFailedAssets() const
{
    return _failedUnits;
}

void GameAssetsManager::downloadFailedAssets()
{
    CCLOG("GameAssetsManager : Start update %lu failed assets.\n", static_cast<unsigned long>(_failedUnits.size()));
    updateAssets(_failedUnits);
}

void GameAssetsManager::fileError(const std::string& identifier, const std::string& errorStr, int errorCode, int errorCodeInternal)
{
	// 更新总进度
	auto it_percent = _percentFileMap.find(identifier);
	if (it_percent != _percentFileMap.end())
	{
		it_percent->second.curSize = it_percent->second.totalSize;
		it_percent->second.state = GameManifest::DownloadState::SUCCESSED;
	}

    auto unitIt = _downloadUnits.find(identifier);
    // Found unit and add it to failed units
    if (unitIt != _downloadUnits.end())
    {
        _totalWaitToDownload--;
        
        DownloadUnit unit = unitIt->second;
        _failedUnits.emplace(unit.customId, unit);
    }
    dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::ERROR_UPDATING, identifier, errorStr, errorCode, errorCodeInternal);
    _tempManifest->setAssetDownloadState(identifier, GameManifest::DownloadState::UNSTARTED);
    
    _currConcurrentTask = MAX(0, _currConcurrentTask-1);
    queueDowload();
}

void GameAssetsManager::fileSuccess(const std::string &customId, const std::string &storagePath)
{
    // Set download state to SUCCESSED
    _tempManifest->setAssetDownloadState(customId, GameManifest::DownloadState::SUCCESSED);
    
    auto unitIt = _failedUnits.find(customId);
    // Found unit and delete it
    if (unitIt != _failedUnits.end())
    {
        // Remove from failed units list
        _failedUnits.erase(unitIt);
    }
    
    unitIt = _downloadUnits.find(customId);
    if (unitIt != _downloadUnits.end())
    {
        // Reduce count only when unit found in _downloadUnits
        _totalWaitToDownload--;
        
        _percentByFile = 100 * (float)(_totalToDownload - _totalWaitToDownload) / _totalToDownload;
        // Notify progression event
        dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::UPDATE_PROGRESSION, "");
    }
    // Notify asset updated event
    dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::ASSET_UPDATED, customId);
    
    _currConcurrentTask = MAX(0, _currConcurrentTask-1);
    queueDowload();
}

void GameAssetsManager::onError(const network::DownloadTask& task,
                              int errorCode,
                              int errorCodeInternal,
                              const std::string& errorStr)
{
    // Skip version error occurred
    if (task.identifier == VERSION_ID)
    {
		if (FileUtils::getInstance()->removeFile(_tempVersionPath) == false)
		{
			CCLOG("GameAssetsManager : Fail to remove file:%s\n", _tempVersionPath.c_str());
		}
        CCLOG("GameAssetsManager : Fail to download version file, step skipped\n");
        _updateState = State::PREDOWNLOAD_MANIFEST;
        downloadManifest();
    }
    else if (task.identifier == MANIFEST_ID)
    {
		if (FileUtils::getInstance()->removeFile(_downloadManifestPath) == false)
		{
			CCLOG("GameAssetsManager : Fail to remove file:%s\n", _downloadManifestPath.c_str());
		}
        dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::ERROR_DOWNLOAD_MANIFEST, task.identifier, errorStr, errorCode, errorCodeInternal);
        _updateState = State::FAIL_TO_UPDATE;
    }
    else
    {
        fileError(task.identifier, errorStr, errorCode, errorCodeInternal);
    }
}

void GameAssetsManager::onProgress(double total, double downloaded, const std::string& /*url*/, const std::string &customId)
{
    if (customId == VERSION_ID || customId == MANIFEST_ID)
    {
        _percent = 100 * downloaded / total;
        // Notify progression event
        dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::UPDATE_PROGRESSION, customId);
        return;
    }
    else
    {
        // Calcul total downloaded
        bool found = false;
        double totalDownloaded = 0;
        for (auto it = _downloadedSize.begin(); it != _downloadedSize.end(); ++it)
        {
            if (it->first == customId)
            {
                it->second = downloaded;
                found = true;
            }
            totalDownloaded += it->second;
        }
        // Collect information if not registed
        if (!found)
        {
            // Set download state to DOWNLOADING, this will run only once in the download process
            _tempManifest->setAssetDownloadState(customId, GameManifest::DownloadState::DOWNLOADING);
            // Register the download size information
            _downloadedSize.emplace(customId, downloaded);
            // Check download unit size existance, if not exist collect size in total size
            if (_downloadUnits[customId].size == 0)
            {
                _totalSize += total;
                _sizeCollected++;
                // All collected, enable total size
                if (_sizeCollected == _totalToDownload)
                {
                    _totalEnabled = true;
                }
            }
        }
        
        if (_totalEnabled && _updateState == State::UPDATING)
        {
            float currentPercent = 100 * totalDownloaded / _totalSize;
            // Notify at integer level change
            if ((int)currentPercent != (int)_percent) {
                _percent = currentPercent;
				// 注释原因：这儿更新总进度虽然是对的，但是要在将所有文件大小获取到之后才会把_totalEnabled置为true
				// 而当_totalEnabled为true时才开始进度更新，这样在未获取到所有文件大小之前进度条不会动
                // Notify progression event
                //dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::UPDATE_PROGRESSION, customId);
            }
        }

		// 更新总进度
		auto it_percent = _percentFileMap.find(customId);
		if (it_percent != _percentFileMap.end())
		{
			it_percent->second.curSize = (unsigned int)downloaded;
			it_percent->second.totalSize = (unsigned int)total;
			it_percent->second.state = GameManifest::DownloadState::DOWNLOADING;
		}
		updateDownloadFilePercent();
    }
}

void GameAssetsManager::onSuccess(const std::string &/*srcUrl*/, const std::string &storagePath, const std::string &customId)
{
    if (customId == VERSION_ID)
    {
        _updateState = State::VERSION_LOADED;
        parseVersion();
    }
    else if (customId == MANIFEST_ID)
    {
        _updateState = State::MANIFEST_LOADED;
        parseManifest();
    }
    else
    {
		// 更新总进度
		auto it_percent = _percentFileMap.find(customId);
		if (it_percent != _percentFileMap.end())
		{
			it_percent->second.curSize = it_percent->second.totalSize;
			it_percent->second.state = GameManifest::DownloadState::SUCCESSED;
		}
		updateDownloadFilePercent();

        bool ok = true;
        auto &assets = _remoteManifest->getAssets();
        auto assetIt = assets.find(customId);
        if (assetIt != assets.end())
        {
            GameManifest::Asset asset = assetIt->second;
            if (_verifyCallback != nullptr)
            {
                ok = _verifyCallback(storagePath, asset);
            }
        }
        
        if (ok)
        {
            bool compressed = assetIt != assets.end() ? assetIt->second.compressed : false;
            if (compressed)
            {
                decompressDownloadedZip(customId, storagePath);
            }
            else
            {
                fileSuccess(customId, storagePath);
            }
        }
        else
        {
            fileError(customId, "Asset file verification failed after downloaded");
        }
    }
}

void GameAssetsManager::destroyDownloadedVersion()
{
    _fileUtils->removeDirectory(_storagePath);
    _fileUtils->removeDirectory(_tempStoragePath);
}

void GameAssetsManager::batchDownload()
{
	_enablePercentFileMap = true;
	_percentFileMap.clear();
    _queue.clear();

	TaskPercentData percentData;
    for(auto iter : _downloadUnits)
    {
        const DownloadUnit& unit = iter.second;
        if (unit.size > 0)
        {
            _totalSize += unit.size;
            _sizeCollected++;
        }
        
        _queue.push_back(iter.first);

		percentData.curSize = (unsigned int)unit.size;
		percentData.state = GameManifest::UNSTARTED;
		percentData.totalSize = unit.fileSize;
		_percentFileMap.insert(std::make_pair(iter.first, percentData));
    }
    // All collected, enable total size
    if (_sizeCollected == _totalToDownload)
    {
        _totalEnabled = true;
    }
    
    queueDowload();
}

void GameAssetsManager::queueDowload()
{
    if (_totalWaitToDownload == 0)
    {
        this->onDownloadUnitsFinished();
        return;
    }
    
    while (_currConcurrentTask < _maxConcurrentTask && _queue.size() > 0)
    {
        std::string key = _queue.back();
        _queue.pop_back();
        
        _currConcurrentTask++;
        DownloadUnit& unit = _downloadUnits[key];
        _fileUtils->createDirectory(basename(unit.storagePath));
        _downloader->createDownloadFileTask(unit.srcUrl, unit.storagePath, unit.customId);
        
        _tempManifest->setAssetDownloadState(key, GameManifest::DownloadState::DOWNLOADING);
    }
    if (_percentByFile / 100 > _nextSavePoint)
    {
        _nextSavePoint += SAVE_POINT_INTERVAL;
    }
	savePercentFile();
}

void GameAssetsManager::onDownloadUnitsFinished()
{
	savePercentFile();

    // Finished with error check
    if (_failedUnits.size() > 0)
    {    
        _updateState = State::FAIL_TO_UPDATE;
        dispatchUpdateEvent(GameAssetsManagerEvent::EventCode::UPDATE_FAILED);
    }
    else if (_updateState == State::UPDATING)
    {
        updateSucceed();
    }
}

// 获取更新进度
float GameAssetsManager::getUpdateDownloadFilePercent()
{
	if (!_enablePercentFileMap)
	{
		return _percent;
	}
	if (_percentFileMap.empty())
	{
		return 100.0f;
	}

	unsigned int curSize = 0;
	unsigned int totalSize = 0;
	for (auto &it : _percentFileMap)
	{
		totalSize += it.second.totalSize;
		curSize += it.second.curSize;
	}
	//CCLOG("\npercent %d - %d\n", curSize, totalSize);

	if (totalSize <= 0)
	{
		return 100.0f;
	}
	return 100.0f * ((float)curSize / (float)totalSize);
}

// 更新下载文件进度
void GameAssetsManager::updateDownloadFilePercent()
{
	float curDownloadFilePercent = getUpdateDownloadFilePercent();
	if ((int)curDownloadFilePercent != (int)_updateDownloadFilePercent)
	{
		_updateDownloadFilePercent = curDownloadFilePercent;
		if (_updateDownloadFilePercentLuaHandle.isvalid())
		{
			_updateDownloadFilePercentLuaHandle(_updateDownloadFilePercent);
		}
	}
}

