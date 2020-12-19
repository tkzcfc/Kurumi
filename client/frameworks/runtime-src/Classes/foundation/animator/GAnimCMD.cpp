#include "GAnimCMD.h"
#include "foundation/file/GFileUtiles.h"
#include "json/stringbuffer.h"
#include "json/document.h"

//////////////////////////////////////////////////////////////////////////
/// GAnimCMD
//////////////////////////////////////////////////////////////////////////

GAnimCMD* GAnimCMD::create(rapidjson::Value& jsonValue)
{
	GAnimCMD* cmd = new GAnimCMD();
	if (cmd && cmd->init(jsonValue))
	{
		return cmd;
	}
	if (cmd) delete cmd;
	return cmd;
}

GAnimCMD::GAnimCMD()
{
	isLeft = true;
}

GAnimCMD::~GAnimCMD()
{}

GKfAniCMDData* GAnimCMD::get(const std::string& name)
{
	auto it = m_cmdData.find(name);
	if (it == m_cmdData.end())
	{
		return NULL;
	}
	return &it->second;
}

bool GAnimCMD::init(rapidjson::Value& jsonValue)
{
	if (jsonValue.HasMember("anime") == false)
		return false;

	auto member = jsonValue.FindMember("anime");
	if (member->value.IsString() == false)
		return false;

	anime = member->value.GetString();
	if (anime.empty())
		return false;

	if (jsonValue.HasMember("image"))
	{
		member = jsonValue.FindMember("image");
		image = member->value.GetString();
	}

	if (jsonValue.HasMember("direction"))
	{
		member = jsonValue.FindMember("direction");
		std::string direction = member->value.GetString();
		if (direction == "Right")
			isLeft = false;
	}

	std::string name;
	GKfAniCMDData data;
	std::string audio;
	for (auto it = jsonValue.MemberBegin(); it != jsonValue.MemberEnd(); ++it)
	{
		if (it->value.IsObject() && it->value.HasMember("action"))
		{
			member = it->value.FindMember("action");
			if (member->value.Size() > 0)
			{
				name = it->name.GetString();
				if (m_cmdData.find(name) == m_cmdData.end())
				{
					m_cmdData[name] = data;
					auto& kfData = m_cmdData[name];

					kfData.actions.resize(member->value.Size());
					kfData.audios.resize(member->value.Size());

					for (uint32_t i = 0; i < member->value.Size(); ++i)
					{
						kfData.actions[i] = member->value[i].GetString();
					}

					if (it->value.HasMember("audio"))
					{
						member = it->value.FindMember("audio");

						for (uint32_t i = 0; i < member->value.Size(); ++i)
						{
							if (kfData.actions.size() <= i)
							{
								//G_ASSERT(false);
							}
							else
							{
								audio = member->value[i].GetString();
								if (audio.empty() == false && audio != "N")
									kfData.audios[i] = audio;
							}
						}
					}
				}
				else
				{
					G_ASSERT(false);
				}
			}
			else
			{
				G_ASSERT(false);
			}
		}
	}

	return true;
}



//////////////////////////////////////////////////////////////////////////
/// GAnimCMDCache
//////////////////////////////////////////////////////////////////////////

GAnimCMDCache* GAnimCMDCache::instance = NULL;

GAnimCMDCache* GAnimCMDCache::getInstance()
{
	if (instance == NULL)
	{
		instance = new GAnimCMDCache();
		instance->init();
	}
	return instance;
}

void GAnimCMDCache::destroy()
{
	if (instance)
	{
		delete instance;
		instance = NULL;
	}
}

GAnimCMDCache::GAnimCMDCache()
{}

GAnimCMDCache::~GAnimCMDCache()
{
	for (auto& it : m_cmdCache)
	{
		delete it.second;
	}
	m_cmdCache.clear();
}


GAnimCMD* GAnimCMDCache::getOrCreate(const std::string& roleName)
{
	auto it = m_cmdCache.find(roleName);
	if (it == m_cmdCache.end())
		return NULL;
	return it->second;
}

const std::vector<std::string>& GAnimCMDCache::getAllRole()
{
	return m_roleListCache;
}

void GAnimCMDCache::init()
{
	do 
	{
		const char* file = "anis.json";

		std::string fileContent;
		if(GFileUtiles::readFileString(file, fileContent) == false || fileContent.empty())
			break;

		rapidjson::Document json;
		rapidjson::StringStream stream(fileContent.c_str());

		json.ParseStream<0>(stream);
		if (json.HasParseError())
		{
			G_LOG_F("'%s' GetParseError %d\n", file, json.GetParseError());
			break;
		}

		for (auto it = json.MemberBegin(); it != json.MemberEnd(); ++it)
		{
			if (it->value.HasMember("anime"))
			{
				std::string name = it->name.GetString();
				if (name.empty()) continue;

				if (m_cmdCache.find(name) == m_cmdCache.end())
				{
					m_cmdCache[name] = GAnimCMD::create(it->value);
				}
				else
				{
					G_ASSERT(false);
				}
			}
		}

		m_roleListCache.reserve(m_roleListCache.size());
		for (auto& it : m_cmdCache)
		{
			m_roleListCache.push_back(it.first);
		}
		return;
	} while (false);
	G_LOG_F("GAnimCMDCache init Fail!!!");
}




