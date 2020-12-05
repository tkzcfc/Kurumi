#include "GFileUtiles.h"


bool GFileUtiles::readFileString(const std::string& file, std::string& out)
{
#if G_TARGET_SERVER
#else
	out = cocos2d::FileUtils::getInstance()->getStringFromFile(file);
#endif
	return true;
}
