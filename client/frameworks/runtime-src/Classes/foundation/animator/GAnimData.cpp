#include "GAnimData.h"
#include "foundation/file/GFileUtiles.h"
#if G_TARGET_CLIENT
#include "json/stringbuffer.h"
#include "json/document.h"
#endif

static kAniRectType getRectType(const std::string& name)
{
	if (name == "RECT_HIT") return kAniRectType::RECT_HIT;
	if (name == "RECT_ATK_A") return kAniRectType::RECT_ATK_A;
	if (name == "RECT_ATK_B") return kAniRectType::RECT_ATK_B;
	G_ASSERT(false);
	return kAniRectType::RECT_COUNT;
}

//////////////////////////////////////////////////////////////////////////
/// GAnimData
//////////////////////////////////////////////////////////////////////////
GAnimData* GAnimData::create(const std::string& file)
{
	GAnimData* ani = new GAnimData();
	if (ani->initWithFile(file))
	{
		return ani;
	}
	delete ani;
	return NULL;
}

GAnimData::~GAnimData()
{}

GAnimData::GAnimData()
{}

bool GAnimData::initWithFile(const std::string& roleName)
{
	char szBuf[128];
	sprintf(szBuf, "json/ani/%s.json", roleName.c_str());

	std::string file = szBuf;
	std::string fileContent;
	if (!GFileUtiles::readFileString(file, fileContent) || fileContent.empty())
		return false;

	rapidjson::Document json;
	rapidjson::StringStream stream(fileContent.c_str());

	json.ParseStream<0>(stream);
	if (json.HasParseError())
	{
		G_LOG_E("'%s' GetParseError %d\n", file.c_str(), json.GetParseError());
		return false;
	}

	auto memberCount = json.MemberCount();
	if (memberCount <= 0)
	{
		G_LOG_E("'%s' Empty frame\n", file.c_str());
		return false;
	}

	json.HasMember("");
	if (!json.HasMember("armatureName"))
	{
		G_LOG_E("'%s' no 'armatureName'\n", file.c_str());
		return false;
	}
	auto armatureName = json.FindMember("armatureName");
	if (!armatureName->value.IsString())
	{
		G_LOG_E("'%s' no 'armatureName'\n", file.c_str());
		return false;
	}
	m_armatureName = armatureName->value.GetString();

	m_names.resize(memberCount);
	m_aniDatas.resize(memberCount);

	uint32_t curIndex = 0;
	uint32_t duration;
	rapidjson::Value::MemberIterator member;
	rapidjson::Value::MemberIterator for_mem;
	for (auto it = json.MemberBegin(); it != json.MemberEnd(); ++it)
	{
		if (it->name.IsString())
		{
			auto& jsonData = it->value;
			if (!jsonData.IsObject()) continue;

			auto name = it->name.GetString();
			m_names[curIndex] = name;

			auto & aniData = m_aniDatas[curIndex];

			curIndex++;
			
			G_ASSERT(jsonData.HasMember("duration"));
			member = jsonData.FindMember("duration");
			duration = member->value.GetUint();

			G_ASSERT(duration > 0);
			if(duration <= 0) continue;

			aniData.duration = duration;
			aniData.kfaabbs = new GKfAABB*[duration];
			aniData.kfcollisions = new GKfCollisions*[duration];
			aniData.events = new GKfEvent*[duration];
			aniData.isLoop = false;

			for (uint32_t i = 0; i < duration; ++i)
			{
				aniData.kfaabbs[i] = NULL;
				aniData.kfcollisions[i] = NULL;
				aniData.events[i] = NULL;
			}

			if (jsonData.HasMember("loop"))
			{
				member = jsonData.FindMember("loop");
				aniData.isLoop = member->value.IsTrue();
			}

			if (jsonData.HasMember("events"))
			{
				member = jsonData.FindMember("events");
				for (uint32_t i = 0; i < member->value.Size(); ++i)
				{
					auto& tmpValue = member->value[i];
					G_ASSERT(tmpValue.HasMember("i"));
					for_mem = tmpValue.FindMember("i");
					uint32_t frame = for_mem->value.GetUint();
					if (frame < duration)
					{
						for_mem = tmpValue.FindMember("name");
						if (aniData.events[frame] == NULL)
							aniData.events[frame] = new GKfEvent();
						aniData.events[frame]->names.push_back(for_mem->value.GetString());
					}
					else
					{
						G_ASSERT(false);
					}
				}
			}

			if (jsonData.HasMember("aabbs"))
			{
				member = jsonData.FindMember("aabbs");
				for (uint32_t i = 0; i < member->value.Size(); ++i)
				{
					auto& tmpValue = member->value[i];
					G_ASSERT(tmpValue.HasMember("i"));
					for_mem = tmpValue.FindMember("i");
					uint32_t frame = for_mem->value.GetUint();
					if (frame < duration)
					{
						if (aniData.kfaabbs[frame] == NULL)
						{
							auto aabb = new GKfAABB();

							G_ASSERT(tmpValue.HasMember("x"));
							for_mem = tmpValue.FindMember("x");
							aabb->x = (float32)for_mem->value.GetDouble();

							G_ASSERT(tmpValue.HasMember("y"));
							for_mem = tmpValue.FindMember("y");
							aabb->y = (float32)for_mem->value.GetDouble();

							G_ASSERT(tmpValue.HasMember("w"));
							for_mem = tmpValue.FindMember("w");
							aabb->w = (float32)for_mem->value.GetDouble();

							G_ASSERT(tmpValue.HasMember("h"));
							for_mem = tmpValue.FindMember("h");
							aabb->h = (float32)for_mem->value.GetDouble();

							aniData.kfaabbs[frame] = aabb;
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

			if (jsonData.HasMember("collisions"))
			{
				member = jsonData.FindMember("collisions");
				for (uint32_t i = 0; i < member->value.Size(); ++i)
				{
					auto& tmpValue = member->value[i];
					G_ASSERT(tmpValue.HasMember("i"));
					for_mem = tmpValue.FindMember("i");
					uint32_t frame = for_mem->value.GetUint();
					if (frame < duration)
					{
						G_ASSERT(tmpValue.HasMember("infos"));
						for_mem = tmpValue.FindMember("infos");
						if (!for_mem->value.Empty())
						{
							if (aniData.kfcollisions[frame] == NULL)
							{
								auto collisions = new GKfCollisions();
								
								for(uint32_t info_i = 0; info_i < for_mem->value.Size(); ++info_i)
								{
									auto& tmpInfo = for_mem->value[info_i];
									G_ASSERT(tmpInfo.HasMember("name"));
									auto tmp = tmpInfo.FindMember("name");
									auto rtype = getRectType(tmp->value.GetString());
									if (rtype != kAniRectType::RECT_COUNT)
									{
										if (collisions->rect[rtype])
										{
											G_ASSERT(false);
										}
										else
										{
											auto rect = new GAniRect();

											G_ASSERT(tmpInfo.HasMember("x1"));
											tmp = tmpInfo.FindMember("x1");
											rect->v[0].x = (float32)tmp->value.GetDouble();

											G_ASSERT(tmpInfo.HasMember("y1"));
											tmp = tmpInfo.FindMember("y1");
											rect->v[0].y = (float32)tmp->value.GetDouble();


											G_ASSERT(tmpInfo.HasMember("x2"));
											tmp = tmpInfo.FindMember("x2");
											rect->v[1].x = (float32)tmp->value.GetDouble();

											G_ASSERT(tmpInfo.HasMember("y2"));
											tmp = tmpInfo.FindMember("y2");
											rect->v[1].y = (float32)tmp->value.GetDouble();


											G_ASSERT(tmpInfo.HasMember("x3"));
											tmp = tmpInfo.FindMember("x3");
											rect->v[2].x = (float32)tmp->value.GetDouble();

											G_ASSERT(tmpInfo.HasMember("y3"));
											tmp = tmpInfo.FindMember("y3");
											rect->v[2].y = (float32)tmp->value.GetDouble();


											G_ASSERT(tmpInfo.HasMember("x4"));
											tmp = tmpInfo.FindMember("x4");
											rect->v[3].x = (float32)tmp->value.GetDouble();

											G_ASSERT(tmpInfo.HasMember("y4"));
											tmp = tmpInfo.FindMember("y4");
											rect->v[3].y = (float32)tmp->value.GetDouble();

											collisions->rect[rtype] = rect;
										}
									}
								}
								aniData.kfcollisions[frame] = collisions;
							}
							else
							{
								G_ASSERT(0);
							}
						}
					}
					else
					{
						G_ASSERT(false);
					}
				}
			}
		}
		else
		{
			G_LOG_E("'%s' Illegal animation data\n", file.c_str());
			G_ASSERT(false);
		}
	}
	return true;
}


const std::vector<std::string>& GAnimData::names()
{
	return m_names;
}

GAnimationData* GAnimData::getAniData(const std::string& aniName)
{
	if (aniName.empty())
		return NULL;

	int32_t index = -1;
	for (uint32_t i = 0; i < m_names.size(); ++i)
	{
		if (m_names[i] == aniName)
		{
			index = i;
			break;
		}
	}
	if (index < 0) return NULL;

	return &m_aniDatas[index];
}

const std::string& GAnimData::getArmatureName()
{
	return m_armatureName;
}



//////////////////////////////////////////////////////////////////////////
/// GAnimDataCache
//////////////////////////////////////////////////////////////////////////

GAnimDataCache* GAnimDataCache::instance = NULL;

GAnimDataCache* GAnimDataCache::getInstance()
{
	if (instance == NULL)
	{
		instance = new GAnimDataCache();
	}
	return instance;
}

void GAnimDataCache::destroy()
{
	if (instance)
	{
		delete instance;
		instance = NULL;
	}
}

GAnimDataCache::GAnimDataCache()
{}

GAnimDataCache::~GAnimDataCache()
{
	for (auto& it : m_aniDataCache)
	{
		if (it.second) delete it.second;
	}
	m_aniDataCache.clear();
}

GAnimData* GAnimDataCache::getOrCreate(const std::string& roleName)
{
	auto it = m_aniDataCache.find(roleName);
	if (it != m_aniDataCache.end())
	{
		return it->second;
	}

	GAnimData* data = GAnimData::create(roleName);
	G_ASSERT(data != NULL);

	m_aniDataCache[roleName] = data;

	return data;
}

