#pragma once

#include "mugen/platform/GStdC.h"

// 逻辑拷贝自 box2d b2_block_allocator.h

NS_G_BEGIN

const int32_t b2_blockSizeCount = 14;

struct GABlock;
struct GAChunk;


class GBlockAllocator
{
public:
	GBlockAllocator();
	~GBlockAllocator();

	void* Allocate(int32_t size);

	void Free(void* p, int32_t size);

	void Clear();

private:

	GAChunk* m_chunks;
	int32_t m_chunkCount;
	int32_t m_chunkSpace;

	GABlock* m_freeLists[b2_blockSizeCount];
};

NS_G_END