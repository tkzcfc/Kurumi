#pragma once
#include "TCPCommon.h"

class TCPBuffer
{
	struct block
	{
		unsigned int dataLen;
		char* data;
		block* pre;
		block* next;
	};

	unsigned int m_blockSize;
	unsigned int m_curDataLength;
	block* m_headBlock;
	block* m_tailBlock;
public:
	TCPBuffer() = delete;
	TCPBuffer(int blockSize)
	{
		assert(blockSize > 0);
		m_blockSize = blockSize;
		m_curDataLength = 0;
		m_headBlock = createBlock();
		m_tailBlock = m_headBlock;
	}

	virtual ~TCPBuffer()
	{
		clear();
		fc_free(m_headBlock->data);
		fc_free(m_headBlock);
	}

	unsigned int getDataLength()
	{
		return m_curDataLength;
	}

	void add(char* pData, unsigned int dataLen)
	{
		char* curData = pData;
		while (dataLen > 0)
		{
			//空间不够，创建新的节点
			if (m_tailBlock->dataLen >= m_blockSize)
			{
				block* b = createBlock();
				m_tailBlock->next = b;
				b->pre = m_tailBlock;
				m_tailBlock = b;
			}
			unsigned int sub = m_blockSize - m_tailBlock->dataLen;
			int copylen = (sub > dataLen) ? dataLen : sub;
			
			memcpy(m_tailBlock->data + m_tailBlock->dataLen, curData, copylen);
			
			m_tailBlock->dataLen += copylen;
			m_curDataLength += copylen;
			curData = curData + copylen;
			dataLen -= copylen;
		}
	}

	bool get(char* pOutData)
	{
		if (m_curDataLength <= 0)
			return false;

		int curIndex = 0;
		block* curBlock = m_headBlock;
		do
		{
			memcpy(pOutData + curIndex, curBlock->data, curBlock->dataLen);
			curIndex += curBlock->dataLen;
			curBlock = curBlock->next;
		} while (curBlock);

		return true;
	}

	void clear()
	{
		while (m_tailBlock != m_headBlock)
		{
			block* pre = m_tailBlock->pre;
			pre->next = NULL;
			fc_free(m_tailBlock->data);
			fc_free(m_tailBlock);
			m_tailBlock = pre;
		}
		m_headBlock->dataLen = 0;
		m_headBlock->next = NULL;
		m_curDataLength = 0;
	}

	char* getHeadBlockData()
	{
		return m_headBlock->data;
	}

private:
	block* createBlock()
	{
		auto p = (block*)fc_malloc(sizeof(block));
		p->next = NULL;
		p->pre = NULL;
		p->dataLen = 0;
		p->data = (char*)fc_malloc(m_blockSize);
		return p;
	}
};