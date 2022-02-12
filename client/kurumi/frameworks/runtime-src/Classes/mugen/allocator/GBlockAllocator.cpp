#include "GBlockAllocator.h"

NS_G_BEGIN

#define b2Alloc malloc
#define b2Free free

static const int32_t b2_chunkSize = 16 * 1024;
static const int32_t b2_maxBlockSize = 640;
static const int32_t b2_chunkArrayIncrement = 128;

// These are the supported object sizes. Actual allocations are rounded up the next size.
static const int32_t b2_blockSizes[b2_blockSizeCount] =
{
	16,		// 0
	32,		// 1
	64,		// 2
	96,		// 3
	128,	// 4
	160,	// 5
	192,	// 6
	224,	// 7
	256,	// 8
	320,	// 9
	384,	// 10
	448,	// 11
	512,	// 12
	640,	// 13
};

// This maps an arbitrary allocation size to a suitable slot in b2_blockSizes.
struct b2SizeMap
{
	b2SizeMap()
	{
		int32_t j = 0;
		values[0] = 0;
		for (int32_t i = 1; i <= b2_maxBlockSize; ++i)
		{
			G_ASSERT(j < b2_blockSizeCount);
			if (i <= b2_blockSizes[j])
			{
				values[i] = (int8_t)j;
			}
			else
			{
				++j;
				values[i] = (int8_t)j;
			}
		}
	}

	int8_t values[b2_maxBlockSize + 1];
};

static const b2SizeMap b2_sizeMap;

struct GAChunk
{
	int32_t blockSize;
	GABlock* blocks;
};

struct GABlock
{
	GABlock* next;
};

GBlockAllocator::GBlockAllocator()
{
	G_ASSERT(b2_blockSizeCount < UCHAR_MAX);

	m_chunkSpace = b2_chunkArrayIncrement;
	m_chunkCount = 0;
	m_chunks = (GAChunk*)b2Alloc(m_chunkSpace * sizeof(GAChunk));

	memset(m_chunks, 0, m_chunkSpace * sizeof(GAChunk));
	memset(m_freeLists, 0, sizeof(m_freeLists));
}

GBlockAllocator::~GBlockAllocator()
{
	for (int32_t i = 0; i < m_chunkCount; ++i)
	{
		b2Free(m_chunks[i].blocks);
	}

	b2Free(m_chunks);
}

void* GBlockAllocator::Allocate(int32_t size)
{
	if (size == 0)
	{
		return nullptr;
	}

	G_ASSERT(0 < size);

	if (size > b2_maxBlockSize)
	{
		return b2Alloc(size);
	}

	int32_t index = b2_sizeMap.values[size];
	G_ASSERT(0 <= index && index < b2_blockSizeCount);

	if (m_freeLists[index])
	{
		GABlock* block = m_freeLists[index];
		m_freeLists[index] = block->next;
		return block;
	}
	else
	{
		if (m_chunkCount == m_chunkSpace)
		{
			GAChunk* oldChunks = m_chunks;
			m_chunkSpace += b2_chunkArrayIncrement;
			m_chunks = (GAChunk*)b2Alloc(m_chunkSpace * sizeof(GAChunk));
			memcpy(m_chunks, oldChunks, m_chunkCount * sizeof(GAChunk));
			memset(m_chunks + m_chunkCount, 0, b2_chunkArrayIncrement * sizeof(GAChunk));
			b2Free(oldChunks);
		}

		GAChunk* chunk = m_chunks + m_chunkCount;
		chunk->blocks = (GABlock*)b2Alloc(b2_chunkSize);
#if defined(_DEBUG)
		memset(chunk->blocks, 0xcd, b2_chunkSize);
#endif
		int32_t blockSize = b2_blockSizes[index];
		chunk->blockSize = blockSize;
		int32_t blockCount = b2_chunkSize / blockSize;
		G_ASSERT(blockCount * blockSize <= b2_chunkSize);
		for (int32_t i = 0; i < blockCount - 1; ++i)
		{
			GABlock* block = (GABlock*)((int8_t*)chunk->blocks + blockSize * i);
			GABlock* next = (GABlock*)((int8_t*)chunk->blocks + blockSize * (i + 1));
			block->next = next;
		}
		GABlock* last = (GABlock*)((int8_t*)chunk->blocks + blockSize * (blockCount - 1));
		last->next = nullptr;

		m_freeLists[index] = chunk->blocks->next;
		++m_chunkCount;

		return chunk->blocks;
	}
}

void GBlockAllocator::Free(void* p, int32_t size)
{
	if (size == 0)
	{
		return;
	}

	G_ASSERT(0 < size);

	if (size > b2_maxBlockSize)
	{
		b2Free(p);
		return;
	}

	int32_t index = b2_sizeMap.values[size];
	G_ASSERT(0 <= index && index < b2_blockSizeCount);

#if defined(_DEBUG)
	// Verify the memory address and size is valid.
	int32_t blockSize = b2_blockSizes[index];
	bool found = false;
	for (int32_t i = 0; i < m_chunkCount; ++i)
	{
		GAChunk* chunk = m_chunks + i;
		if (chunk->blockSize != blockSize)
		{
			G_ASSERT((int8_t*)p + blockSize <= (int8_t*)chunk->blocks ||
				(int8_t*)chunk->blocks + b2_chunkSize <= (int8_t*)p);
		}
		else
		{
			if ((int8_t*)chunk->blocks <= (int8_t*)p && (int8_t*)p + blockSize <= (int8_t*)chunk->blocks + b2_chunkSize)
			{
				found = true;
			}
		}
	}

	G_ASSERT(found);

	memset(p, 0xfd, blockSize);
#endif

	GABlock* block = (GABlock*)p;
	block->next = m_freeLists[index];
	m_freeLists[index] = block;
}

void GBlockAllocator::Clear()
{
	for (int32_t i = 0; i < m_chunkCount; ++i)
	{
		b2Free(m_chunks[i].blocks);
	}

	m_chunkCount = 0;
	memset(m_chunks, 0, m_chunkSpace * sizeof(GAChunk));
	memset(m_freeLists, 0, sizeof(m_freeLists));
}

NS_G_END