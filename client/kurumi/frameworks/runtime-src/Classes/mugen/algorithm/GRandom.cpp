#include "GRandom.h"
#include <assert.h>


NS_G_BEGIN

static unsigned int permuteQPR(unsigned int x)
{
	static const unsigned int prime = 4294967291u;
	if (x >= prime)
		return x;  // The 5 integers out of range are mapped to themselves.
	unsigned int residue = ((unsigned long long) x * x) % prime;
	return (x <= prime / 2) ? residue : prime - residue;
}


////////////////////////////////////////////////////////////////////////////////////////

GRandom::GRandom(unsigned int seedBase, unsigned int seedOffset)
{
	m_index = permuteQPR(permuteQPR(seedBase) + 0x682f0161);
	m_intermediateOffset = permuteQPR(permuteQPR(seedOffset) + 0x46790905);
}

unsigned int GRandom::next()
{
	return permuteQPR((permuteQPR(m_index++) + m_intermediateOffset) ^ 0x5bf03635);
}

unsigned int GRandom::next(unsigned int max)
{
	return (unsigned int)(next() % max);
}

// @return [min,max)
unsigned int GRandom::range(unsigned int min, unsigned int max)
{
	assert(min < max);
	int num = max - min;
	return next(num) + min;
}


// @return [0, 1.0]
double GRandom::random0_1()
{
	const uint32_t M = 0x7fff;
	return (double)random(0, M) / M;
}

// @return [min, max]
uint32_t GRandom::random(uint32_t min, uint32_t max)
{
	assert(min < max);
	return range(min, max + 1);
}

// @return [min, max]
float GRandom::randomFloat(float min, float max)
{
	return min + (float)random0_1() * (max - min);
}

NS_G_END