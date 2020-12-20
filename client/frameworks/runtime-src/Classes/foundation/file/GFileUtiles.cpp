#include "GFileUtiles.h"


bool GFileUtiles::readFileString(const std::string& file, std::string& out)
{
#if G_TARGET_SERVER
	std::string fullPath = file;
	FILE *fp = fopen(fullPath.c_str(), "rt");
	if (!fp)
		return false;

	fseek(fp, 0, SEEK_END);
	ssize_t size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	if (size <= 0)
	{
		fclose(fp);
		out = "";
		return true;
	}
	unsigned char* buffer = (unsigned char*)malloc(sizeof(unsigned char) * (size + 1));
	buffer[size] = '\0';

	auto readsize = fread(buffer, sizeof(unsigned char), size, fp);
	fclose(fp);

	if (readsize < size)
	{
		buffer[readsize] = '\0';
	}
	out.assign(buffer, readsize);
	free(buffer);
#else
	out = cocos2d::FileUtils::getInstance()->getStringFromFile(file);
#endif
	
	return true;
}
