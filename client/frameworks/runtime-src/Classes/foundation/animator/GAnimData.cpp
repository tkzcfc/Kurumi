#include "GAnimData.h"
#include "foundation/file/GFileUtiles.h"
#include "json/stringbuffer.h"
#include "json/document.h"

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

bool GAnimData::initWithFile(const std::string& file)
{
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

	m_names.resize(memberCount);
	m_aniDatas.resize(memberCount);

	uint32_t curIndex = 0;
	uint32_t duration;
	rapidjson::Value::MemberIterator member;
	rapidjson::Value::MemberIterator for_it;
	rapidjson::Value::MemberIterator for_mem;
	rapidjson::Value::MemberIterator for_it_info;
	for (auto it = json.MemberBegin(); it != json.MemberEnd(); ++it)
	{
		if (it->name.IsString())
		{
			auto name = it->name.GetString();
			m_names[curIndex] = name;

			auto & aniData = m_aniDatas[curIndex];

			curIndex++;

			//
			auto& jsonData = it->value;

			G_ASSERT(json.HasMember("duration"));
			member = jsonData.FindMember("duration");
			duration = member->value.GetUint();

			G_ASSERT(duration > 0);
			if(duration <= 0) continue;

			aniData.duration = duration;
			aniData.kfaabbs = new GKfAABB*[duration];
			aniData.kfcollisions = new GKfCollisions*[duration];
			aniData.events = new GKfEvent*[duration];

			for (uint32_t i = 0; i < duration; ++i)
			{
				aniData.kfaabbs[i] = NULL;
				aniData.kfcollisions[i] = NULL;
				aniData.events[i] = NULL;
			}

			if (jsonData.HasMember("events"))
			{
				member = jsonData.FindMember("events");
				for (auto for_it = member->value.MemberBegin(); for_it != member->value.MemberEnd(); ++for_it)
				{
					G_ASSERT(for_it->value.HasMember("i"));
					for_mem = for_it->value.FindMember("i");
					uint32_t frame = for_mem->value.GetUint();
					if (frame < duration)
					{
						for_mem = for_it->value.FindMember("name");
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
				for (auto for_it = member->value.MemberBegin(); for_it != member->value.MemberEnd(); ++for_it)
				{
					G_ASSERT(for_it->value.HasMember("i"));
					for_mem = for_it->value.FindMember("i");
					uint32_t frame = for_mem->value.GetUint();
					if (frame < duration)
					{
						if (aniData.kfaabbs[frame] == NULL)
						{
							auto aabb = new GKfAABB();

							G_ASSERT(for_it->value.HasMember("x"));
							for_mem = for_it->value.FindMember("x");
							aabb->x = (float32)for_mem->value.GetDouble();

							G_ASSERT(for_it->value.HasMember("y"));
							for_mem = for_it->value.FindMember("y");
							aabb->y = (float32)for_mem->value.GetDouble();

							G_ASSERT(for_it->value.HasMember("w"));
							for_mem = for_it->value.FindMember("w");
							aabb->w = (float32)for_mem->value.GetDouble();

							G_ASSERT(for_it->value.HasMember("h"));
							for_mem = for_it->value.FindMember("h");
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
				for (auto for_it = member->value.MemberBegin(); for_it != member->value.MemberEnd(); ++for_it)
				{
					G_ASSERT(for_it->value.HasMember("i"));
					for_mem = for_it->value.FindMember("i");
					uint32_t frame = for_mem->value.GetUint();
					if (frame < duration)
					{
						G_ASSERT(for_it->value.HasMember("infos"));
						for_mem = for_it->value.FindMember("infos");
						if (!for_mem->value.Empty())
						{
							if (aniData.kfcollisions[frame] == NULL)
							{
								auto collisions = new GKfCollisions();
								for (auto for_it_info = for_mem->value.MemberBegin(); for_it_info != for_mem->value.MemberEnd(); ++for_it_info)
								{
									G_ASSERT(for_it_info->value.HasMember("name"));
									auto tmp = for_it_info->value.FindMember("name");
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

											G_ASSERT(for_it_info->value.HasMember("x1"));
											tmp = for_it_info->value.FindMember("x1");
											rect->v[0].x = (float32)tmp->value.GetDouble();

											G_ASSERT(for_it_info->value.HasMember("y1"));
											tmp = for_it_info->value.FindMember("y1");
											rect->v[0].y = (float32)tmp->value.GetDouble();


											G_ASSERT(for_it_info->value.HasMember("x2"));
											tmp = for_it_info->value.FindMember("x2");
											rect->v[1].x = (float32)tmp->value.GetDouble();

											G_ASSERT(for_it_info->value.HasMember("y2"));
											tmp = for_it_info->value.FindMember("y2");
											rect->v[1].y = (float32)tmp->value.GetDouble();


											G_ASSERT(for_it_info->value.HasMember("x3"));
											tmp = for_it_info->value.FindMember("x3");
											rect->v[2].x = (float32)tmp->value.GetDouble();

											G_ASSERT(for_it_info->value.HasMember("y3"));
											tmp = for_it_info->value.FindMember("y3");
											rect->v[2].y = (float32)tmp->value.GetDouble();


											G_ASSERT(for_it_info->value.HasMember("x4"));
											tmp = for_it_info->value.FindMember("x4");
											rect->v[3].x = (float32)tmp->value.GetDouble();

											G_ASSERT(for_it_info->value.HasMember("y4"));
											tmp = for_it_info->value.FindMember("y4");
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
	int32_t index = -1;
	for (uint32_t i = 0; i < m_names.size(); ++i)
	{
		if (m_names[i].compare(aniName) == 0)
		{
			index = i;
			break;
		}
	}
	if (index < 0) return NULL;

	return &m_aniDatas[index];
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

GAnimData* GAnimDataCache::getOrCreate(const std::string& filename)
{
	auto it = m_aniDataCache.find(filename);
	if (it != m_aniDataCache.end())
	{
		return it->second;
	}

	GAnimData* data = GAnimData::create(filename);
	G_ASSERT(data != NULL);

	m_aniDataCache[filename] = data;

	return data;
}

