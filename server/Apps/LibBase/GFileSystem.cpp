#include "GFileSystem.h"
#include "3rd/tinydir/tinydir.h"
#include "Utils/GStringUtils.h"


void GFileSystem::listFilesRecursively(const std::string& dirPath, std::vector<std::string> *files)
{
	std::string fullpath = dirPath;

	tinydir_dir dir;
	auto fullpathstr = StringUtils::stringUtf8ToWideChar(fullpath);

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
			std::string fileName = StringUtils::stringWideCharToUtf8(file.name);

			if (fileName != "." && fileName != "..")
			{
				std::string filepath = StringUtils::stringWideCharToUtf8(file.path);
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

void GFileSystem::listFiles(const std::string& dirPath, std::vector<std::string> *files)
{
	std::string fullpath = dirPath;

	tinydir_dir dir;
	auto fullpathstr = StringUtils::stringUtf8ToWideChar(fullpath);

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
			std::string fileName = StringUtils::stringWideCharToUtf8(file.name);

			if (fileName != "." && fileName != "..")
			{
				std::string filepath = StringUtils::stringWideCharToUtf8(file.path);
				if (file.is_dir)
				{
					filepath.append("/");
					files->push_back(filepath);
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

std::string GFileSystem::baseName(const std::string& filepath)
{
	size_t pos = filepath.find_last_of("/\\");
	if (pos != std::string::npos)
	{
		return filepath.substr(pos + 1);
	}

	return filepath;
}

std::string GFileSystem::getFileExtension(std::string filePath)
{
	std::string fileExtension;
	size_t pos = filePath.find_last_of('.');
	if (pos != std::string::npos)
	{
		fileExtension = filePath.substr(pos, filePath.length());

		std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);
	}

	return fileExtension;
}

// D:\aaa\bbb\ccc\ddd\abc.txt --> D:/aaa/bbb/ccc/ddd/abc.txt
std::string GFileSystem::convertPathFormatToUnixStyle(const std::string& path)
{
	std::string ret{ path };
	int len = ret.length();
	std::replace(ret.begin(), ret.end(), '\\', '/');
	return ret;
}

std::string GFileSystem::convertPathFormatToWinStyle(const std::string& path)
{
	std::string ret{ path };
	int len = ret.length();
	std::replace(ret.begin(), ret.end(), '/', '\\');
	return ret;
}