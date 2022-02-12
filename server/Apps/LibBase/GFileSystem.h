#pragma once

#include "GPlatformMacros.h"


class GFileSystem
{
public:
	static bool isFileExist(const std::string& filename);
	static bool isDirectoryExist(const std::string& path);

	static bool createDirectory(const std::string& path);
	static bool removeDirectory(const std::string& dirPath);

	static int64_t getFileSize(const std::string& path);
	static bool removeFile(const std::string &filepath);
	static bool renameFile(const std::string &oldfullpath, const std::string &newfullpath);

	static uint8_t* readFile(const std::string& filename, uint32_t& outSize);
	static std::string readStringFromFile(const std::string& filename);
	static bool readStringFromFile(const std::string& filename, std::string& outData);

	static bool writeFile(const std::string& path, uint8_t* buffer, uint32_t size);
	static bool writeTextFile(const std::string& path, const std::string& text);

	static void listFilesRecursively(const std::string& dirPath, std::vector<std::string> *files);

	static void listFiles(const std::string& dirPath, std::vector<std::string> *files);

	//static bool isRelativePath(const char* path)
	//{
	//	if(!path || path[0] == '/' || path[0] == '\\')
	//	{
	//		return false;
	//	}

	//	if(strlen(path) >= 2 && isalpha(path[0]) && path[1] == ':')
	//	{
	//		return false;
	//	}

	//	return true;
	//}

	//static bool isAbsolutePath(const char* path)
	//{
	//	if(!path)
	//	{
	//		return false;
	//	}

	//	return !isRelativePath(path);
	//}

};
