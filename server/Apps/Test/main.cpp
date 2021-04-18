#include "GLibBase.h"

class Random
{
	unsigned int m_index;
	unsigned int m_intermediateOffset;

	static unsigned int permuteQPR(unsigned int x)
	{
		static const unsigned int prime = 4294967291u;
		if (x >= prime)
			return x;  // The 5 integers out of range are mapped to themselves.
		unsigned int residue = ((unsigned long long) x * x) % prime;
		return (x <= prime / 2) ? residue : prime - residue;
	}

public:
	Random(unsigned int seedBase, unsigned int seedOffset)
	{
		m_index = permuteQPR(permuteQPR(seedBase) + 0x682f0161);
		m_intermediateOffset = permuteQPR(permuteQPR(seedOffset) + 0x46790905);
	}

	unsigned int next()
	{
		return permuteQPR((permuteQPR(m_index++) + m_intermediateOffset) ^ 0x5bf03635);
	}

	unsigned int next(unsigned int max)
	{
		return (unsigned int)(next() % max);
	}

	// @return [min,max)
	unsigned int range(unsigned int min, unsigned int max)
	{
		assert(min != max);
		if (min > max) 
		{
			auto tmp = min;
			min = max;
			max = tmp;
		}

		int num = max - min;

		return next(num) + min;
	}
};


int main(int argc, char** argv)
{
	unsigned int seed = (unsigned int)time(NULL);
	Random rsu(seed, seed + 1);
	Random rsu1(seed, seed + 1);
	unsigned int i = 0;
	do
	{
		assert(rsu.range(1, 0x7fff) == rsu1.range(1, 0x7fff));

		if (i > 10000)
			break;

	} while (++i != 0);

	system("pause");
	return EXIT_SUCCESS;
}
