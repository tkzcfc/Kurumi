#pragma once

#include "foundation/GameMacro.h"

// 逻辑拷贝自box2d b2_block_allocator.h


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

