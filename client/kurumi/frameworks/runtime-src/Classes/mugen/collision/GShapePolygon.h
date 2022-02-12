#pragma once

#include "GShape.h"

NS_G_BEGIN

#define MAX_POLY_VERTEX_COUNT 8

class GShapePolygon : public GShape
{
public:

	GShapePolygon();

	virtual ~GShapePolygon();

	G_FORCEINLINE GFixedVec2* getVertexs() { return m_vertexs; }

	G_SYNTHESIZE_READONLY(uint32_t, m_count, VerticesCount);

	virtual void set(GFixedVec2* vertices, uint32_t count);

public:

	virtual void serialize(GByteBuffer& byteBuffer) override;

	virtual bool deserialize(GByteBuffer& byteBuffer) override;

	virtual void updateAABB() override;

protected:

	GFixedVec2 m_vertexs[MAX_POLY_VERTEX_COUNT];
};

NS_G_END
