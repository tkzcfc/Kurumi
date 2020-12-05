#pragma once

#include "foundation/math/GMath.h"
#include <string>
#include <unordered_map>

enum kAniRectType
{
	RECT_HIT = 0,
	RECT_ATK_A,
	RECT_ATK_B,

	RECT_COUNT
};

struct GKfAABB
{
	float32 x;
	float32 y;
	float32 w;
	float32 h;
};

struct GAniRect
{
	GVec2 v[4];
};

struct GKfCollisions
{
	GAniRect* rect[kAniRectType::RECT_COUNT];
	GKfCollisions()
	{
		for (uint32_t i = 0; i < kAniRectType::RECT_COUNT; ++i)
			rect[i] = NULL;
	}

	~GKfCollisions()
	{
		for (uint32_t i = 0; i < kAniRectType::RECT_COUNT; ++i)
		{
			if(rect[i]) delete rect[i];
		}
	}
};

struct GKfEvent
{
	std::vector<std::string> names;
};

struct GAnimationData
{
	uint32_t duration;
	GKfAABB** kfaabbs;
	GKfCollisions** kfcollisions;
	GKfEvent** events;
	bool isLoop;
	GAnimationData()
	{
		isLoop = false;
		duration = 0;
		kfaabbs = NULL;
		kfcollisions = NULL;
		events = NULL;
	}
	~GAnimationData()
	{
		for (uint32_t i = 0; i < duration; ++i)
		{
			if (kfaabbs[i]) delete kfaabbs[i];
			if (kfcollisions[i]) delete kfcollisions[i];
			if (events[i]) delete events[i];
		}
		if (kfaabbs) delete[]kfaabbs;
		if (kfcollisions) delete[]kfcollisions;
		if (events) delete[]events;
	}
};

class GAnimData
{
public:

	static GAnimData* create(const std::string& file);

	virtual ~GAnimData();

	const std::vector<std::string>& names();

	GAnimationData* getAniData(const std::string& aniName);

protected:

	GAnimData();

	bool initWithFile(const std::string& file);

	std::vector<std::string> m_names;
	std::vector<GAnimationData> m_aniDatas;
};


class GAnimDataCache
{
public:

	GAnimDataCache();

	~GAnimDataCache();

	static GAnimDataCache* getInstance();

	static void destroy();

	GAnimData* getOrCreate(const std::string& filename);

private:

	std::unordered_map<std::string, GAnimData*> m_aniDataCache;

	static GAnimDataCache* instance;
};

