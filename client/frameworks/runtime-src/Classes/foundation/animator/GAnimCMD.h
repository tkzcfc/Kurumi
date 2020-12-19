#pragma once

#include "foundation/GameMacro.h"
#include "json/document.h"

struct GKfAniCMDData
{
	std::vector<std::string> actions;
	std::vector<std::string> audios;

	uint32_t seekIndex(const std::string& action)
	{
		for (uint32_t i = 0; i < actions.size(); ++i)
		{
			if (actions[i] == action)
				return i;
		}
		G_ASSERT(false);
		return 0U;
	}
};

class GAnimCMD
{
public:

	static GAnimCMD* create(rapidjson::Value& jsonValue);

	~GAnimCMD();

	GKfAniCMDData* get(const std::string& name);
	
private:

	GAnimCMD();

	bool init(rapidjson::Value& jsonValue);

public:

	std::unordered_map<std::string, GKfAniCMDData> m_cmdData;
	std::string anime;
	std::string image;
	bool isLeft;
};

class GAnimCMDCache
{
public:

	static GAnimCMDCache* getInstance();

	static void destroy();

	GAnimCMD* getOrCreate(const std::string& roleName);

	const std::vector<std::string>& getAllRole();

private:

	GAnimCMDCache();

	~GAnimCMDCache();

	void init();

	static GAnimCMDCache* instance;

	std::unordered_map<std::string, GAnimCMD*> m_cmdCache;
	std::vector<std::string> m_roleListCache;
};
