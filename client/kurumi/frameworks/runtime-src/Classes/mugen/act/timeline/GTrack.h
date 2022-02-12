#pragma once

#include "GTimeline.h"

NS_G_BEGIN

class GSkill;
class GTrack : public GObject
{
public:

	GTrack();

	virtual ~GTrack();
	
	G_SYNTHESIZE_READONLY_BY_REF(std::vector<GTimeline*>, m_timelines, Timelines);
	G_SYNTHESIZE(GSkill*, m_skill, Skill);

	void addTimeline(GTimeline* timeline);

	void onEnter();

	void apply(int32_t frame);

	void onExit();

	int32_t getTimelineIndex(GTimeline* timeline);

	virtual void serialize(GByteBuffer& byteBuffer) override;

	virtual bool deserialize(GByteBuffer& byteBuffer) override;

private:

	void clear();

};

NS_G_END

