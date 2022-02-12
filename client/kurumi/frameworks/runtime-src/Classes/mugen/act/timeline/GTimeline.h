#pragma once

#include "../frame/GFrame.h"

NS_G_BEGIN

class GTrack;
class GSkill;
class GTimeline : public GObject
{
public:
	GTimeline();

	virtual ~GTimeline();

	virtual void serialize(GByteBuffer& byteBuffer) override;

	virtual bool deserialize(GByteBuffer& byteBuffer) override;

	void onEnter();

	void apply(int32_t frame);

	void onExit();

public:

	void addFrame(GFrame* frame, GFrameType type);

	void removeFrame(GFrame* frame);

	GFrame* getCurFrameByType(GFrameType type);

	GSkill* getSkill();

	int32_t getFrameIndex(GFrame* frame);

	G_SYNTHESIZE(GTrack*, m_track, Track);
	G_SYNTHESIZE_READONLY(int32_t, m_frame, Frame);
	G_SYNTHESIZE_READONLY(GFrame*, m_curFrame, CurFrame);
	G_SYNTHESIZE_READONLY_BY_REF(std::vector<GFrame*>, m_frames, Frames);

private:

	void doSort();

	void clearFrame();
	
private:
	bool m_sortDirty;
};

NS_G_END