#include "GFileUtiles.h"


bool GFileUtiles::readFileString(const std::string& file, std::string& out)
{
	out = cocos2d::FileUtils::getInstance()->getStringFromFile(file);	
	return true;
}
