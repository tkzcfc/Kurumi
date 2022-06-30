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