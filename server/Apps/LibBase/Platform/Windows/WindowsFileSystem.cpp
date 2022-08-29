#include "GFileSystem.h"

#if G_TARGET_PLATFORM == G_PLATFORM_WIN32
#include <regex>

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
			LOG(ERROR) << "Wrong convert to WideChar code:" << GetLastError();
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
			LOG(ERROR) << "Wrong convert to Utf8 code:" << GetLastError();
		}
	}

	return ret;
}

static std::string UTF8StringToMultiByte(const std::string& strUtf8)
{
	std::string ret;
	if (!strUtf8.empty())
	{
		std::wstring strWideChar = StringUtf8ToWideChar(strUtf8);
		int nNum = WideCharToMultiByte(CP_ACP, 0, strWideChar.c_str(), -1, nullptr, 0, nullptr, FALSE);
		if (nNum)
		{
			char* ansiString = new char[nNum + 1];
			ansiString[0] = 0;

			nNum = WideCharToMultiByte(CP_ACP, 0, strWideChar.c_str(), -1, ansiString, nNum + 1, nullptr, FALSE);

			ret = ansiString;
			delete[] ansiString;
		}
		else
		{
			LOG(ERROR) << "Wrong convert to Ansi code:" << GetLastError();
		}
	}

	return ret;
}

bool GFileSystem::isFileExist(const std::string& filename)
{
	if (filename.empty())
	{
		return false;
	}

	std::string strPath = filename;

	DWORD attr = GetFileAttributesW(StringUtf8ToWideChar(strPath).c_str());
	if (attr == INVALID_FILE_ATTRIBUTES || (attr & FILE_ATTRIBUTE_DIRECTORY))
		return false;
	return true;
}

bool GFileSystem::isDirectoryExist(const std::string& path)
{
	unsigned long fAttrib = GetFileAttributesW(StringUtf8ToWideChar(path).c_str());
	if (fAttrib != INVALID_FILE_ATTRIBUTES &&
		(fAttrib & FILE_ATTRIBUTE_DIRECTORY))
	{
		return true;
	}
	return false;
}

bool GFileSystem::createDirectory(const std::string& dirPath)
{
	G_ASSERT(!dirPath.empty());

	if (isDirectoryExist(dirPath))
		return true;

	std::wstring path = StringUtf8ToWideChar(dirPath);

	// Split the path
	size_t start = 0;
	size_t found = path.find_first_of(L"/\\", start);
	std::wstring subpath;
	std::vector<std::wstring> dirs;

	if (found != std::wstring::npos)
	{
		while (true)
		{
			subpath = path.substr(start, found - start + 1);
			if (!subpath.empty())
				dirs.push_back(subpath);
			start = found + 1;
			found = path.find_first_of(L"/\\", start);
			if (found == std::wstring::npos)
			{
				if (start < path.length())
				{
					dirs.push_back(path.substr(start));
				}
				break;
			}
		}
	}

	if ((GetFileAttributesW(path.c_str())) == INVALID_FILE_ATTRIBUTES)
	{
		subpath = L"";
		for (size_t i = 0, size = dirs.size(); i < size; ++i)
		{
			subpath += dirs[i];

			std::string utf8Path = StringWideCharToUtf8(subpath);
			if (!isDirectoryExist(utf8Path))
			{
				BOOL ret = CreateDirectoryW(subpath.c_str(), NULL);
				if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
				{
					LOG(ERROR) << "Fail create directory " << utf8Path.c_str() << " !Error code is " << GetLastError();
					return false;
				}
			}
		}
	}
	return true;
}


bool GFileSystem::removeDirectory(const std::string& dirPath)
{
	std::wstring wpath = StringUtf8ToWideChar(dirPath);
	std::wstring files = wpath + L"*.*";
	WIN32_FIND_DATA wfd;
	HANDLE  search = FindFirstFileExW(files.c_str(), FindExInfoStandard, &wfd, FindExSearchNameMatch, NULL, 0);
	bool ret = true;
	if (search != INVALID_HANDLE_VALUE)
	{
		BOOL find = true;
		while (find)
		{
			// Need check string . and .. for delete folders and files begin name.
#ifdef UNICODE
			std::wstring fileName = wfd.cFileName;
#else
			std::wstring fileName = StringUtf8ToWideChar(wfd.cFileName);
#endif
			if (fileName != L"." && fileName != L"..")
			{
#ifdef UNICODE
				std::wstring temp = wpath + wfd.cFileName;
#else
				std::wstring temp = wpath + StringUtf8ToWideChar(wfd.cFileName);
#endif
				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					temp += '/';
					ret = ret && removeDirectory(StringWideCharToUtf8(temp));
				}
				else
				{
					SetFileAttributesW(temp.c_str(), FILE_ATTRIBUTE_NORMAL);
					ret = ret && DeleteFileW(temp.c_str());
				}
			}
			find = FindNextFile(search, &wfd);
		}
		FindClose(search);
	}
	if (ret && RemoveDirectoryW(wpath.c_str()))
	{
		return true;
	}
	return false;
}

bool GFileSystem::removeFile(const std::string &filepath)
{
	std::regex pat("\\/");
	std::string win32path = std::regex_replace(filepath, pat, "\\");

	if (DeleteFileW(StringUtf8ToWideChar(win32path).c_str()))
	{
		return true;
	}
	else
	{
		LOG(ERROR) << "Fail remove file " << filepath << " !Error code is " << GetLastError();
		return false;
	}
}

bool GFileSystem::renameFile(const std::string &oldfullpath, const std::string &newfullpath)
{
	G_ASSERT(!oldfullpath.empty());
	G_ASSERT(!newfullpath.empty());

	std::wstring _wNew = StringUtf8ToWideChar(newfullpath);
	std::wstring _wOld = StringUtf8ToWideChar(oldfullpath);

	if (isFileExist(newfullpath))
	{
		if (!DeleteFileW(_wNew.c_str()))
		{
			LOG(ERROR) << "Fail to delete file " << newfullpath << " !Error code is " << GetLastError();
		}
	}

	if (MoveFileW(_wOld.c_str(), _wNew.c_str()))
	{
		return true;
	}
	else
	{
		LOG(ERROR) << "Fail to rename file " << oldfullpath << " to " << newfullpath << " !Error code is " << GetLastError();
		return false;
	}
}

int64_t GFileSystem::getFileSize(const std::string& path)
{
	if (!isFileExist(path))
		return 0LL;

	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (!GetFileAttributesExW(StringUtf8ToWideChar(path).c_str(), GetFileExInfoStandard, &fad))
	{
		return 0LL; // error condition, could call GetLastError to find out more
	}
	LARGE_INTEGER size;
	size.HighPart = fad.nFileSizeHigh;
	size.LowPart = fad.nFileSizeLow;
	return (int64_t)size.QuadPart;
}

uint8_t* GFileSystem::readFile(const std::string& filename, uint32_t& outSize)
{
	outSize = 0;

	if (filename.empty())
		return NULL;

	// read the file from hardware

	HANDLE fileHandle = ::CreateFileW(StringUtf8ToWideChar(filename).c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, nullptr);

	// OpenFailed
	if (fileHandle == INVALID_HANDLE_VALUE)
		return NULL;

	DWORD hi;
	auto size = ::GetFileSize(fileHandle, &hi);
	if (hi > 0)
	{
		::CloseHandle(fileHandle);
		// TooLarge
		return NULL;
	}
	// don't read file content if it is empty
	if (size == 0)
	{
		::CloseHandle(fileHandle);
		return NULL;
	}

	uint8_t* buffer = (uint8_t*)malloc(size);
	DWORD sizeRead = 0;
	BOOL successed = ::ReadFile(fileHandle, buffer, size, &sizeRead, nullptr);
	::CloseHandle(fileHandle);

	if (!successed) {
		LOG(ERROR) << "Get data from file(" << filename << ") failed, error code is " << ::GetLastError();
		free(buffer);
		// ReadFailed
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

static std::string s_exeDir;
static std::string s_exeName;
static void _checkExePath()
{
	if (s_exeDir.empty())
	{
		WCHAR utf16Path[MAX_PATH + 1] = { 0 };
		size_t nNum = GetModuleFileNameW(NULL, utf16Path, MAX_PATH);
		std::wstring u16pathsv{ utf16Path, nNum };
		std::string path = StringWideCharToUtf8(u16pathsv);

		std::replace(path.begin(), path.end(), '\\', '/');

		s_exeName = GFileSystem::baseName(path);
		s_exeDir = path.substr(0, path.size() - s_exeName.size());
	}
}

std::string GFileSystem::getExeDirectory()
{
	_checkExePath();
	return s_exeDir;
}

std::string GFileSystem::getExeName()
{
	_checkExePath();
	return s_exeName;
}

std::string GFileSystem::getCwd()
{
	WCHAR buf[1024];
	size_t nNum  = GetCurrentDirectoryW(1000, buf);
	std::wstring u16pathsv{ buf, nNum };
	return StringWideCharToUtf8(u16pathsv);
}

void GFileSystem::setCwd(const std::string& cwd)
{
	std::wstring u16cwd = StringUtf8ToWideChar(cwd);
	SetCurrentDirectoryW(u16cwd.c_str());
}

#endif