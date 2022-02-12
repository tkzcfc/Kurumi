#pragma once

#include "GFrame.h"

NS_G_BEGIN

// 碰撞信息帧
class GCollisionFrame : public GFrame
{
public:

	GCollisionFrame();

	virtual ~GCollisionFrame();

	virtual void onUpdate(int32_t currentFrameIndex) override;

	virtual void serialize(GByteBuffer& byteBuffer) override;

	virtual bool deserialize(GByteBuffer& byteBuffer) override;

	void setShape(GShape* shape);

	GShape* getShape();

	bool intersects(GCollisionFrame* other);

protected:

	GShape* m_shape;

};

NS_G_END
