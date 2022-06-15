#include "GamePlayer.h"

// 游戏玩家

uint32_t GamePlayer::INVALID_SESSION_ID = UINT32_MAX;

GamePlayer::GamePlayer()
{
	m_initLastInput = false;
	m_ping = 0;
	m_lastFrame = 0;
	m_loadPercent = 0.0f;
	m_loadFinish = false;
	this->offline();
}

GamePlayer::~GamePlayer()
{
	for (auto it : m_inputs)
	{
		delete it;
	}
	for (auto it : m_inputCache)
	{
		delete it;
	}
	m_inputCache.clear();
	m_inputs.clear();
}

err::Code GamePlayer::init(const ::svr_msg::FightRoleSpawnInfo& info)
{
	m_playerID = info.roleid();
	return err::Code::SUCCESS;
}

void GamePlayer::offline()
{
	this->setSessionID(INVALID_SESSION_ID);
	this->setLastRecvFrame(0U);
	this->setPing(0);
	this->setOfflineTime(GApplication::getInstance()->getRunTime());
}

void GamePlayer::input(const msg::RunNextFrameReq& data, uint32_t frame)
{
	auto oldFrame = m_lastFrame;
	m_lastFrame = data.frame();

	auto input = dequeue();
	input->mutable_input()->CopyFrom(data.input());
	input->set_frame(frame);
	input->set_pid(this->getPlayerID());

	if (m_inputs.empty())
	{
		m_inputs.push_back(input);
		return;
	}

	auto back = m_inputs.back();
	if (back->frame() < frame)
	{
		m_inputs.push_back(input);
		return;
	}

	G_ASSERT(data.frame() >= oldFrame);
	auto diffFrame = data.frame() - oldFrame;

	// 客户端同一帧发送两次输入
	if (oldFrame > 0 && diffFrame == 0)
	{
		// 合并输入
		back->mutable_input()->set_key_down(back->mutable_input()->key_down() | data.input().key_down());
		//G_ASSERT(0);
		return;
	}

	auto newFrame = back->frame() + diffFrame;
	if (newFrame < frame) newFrame = frame;

	input->set_frame(newFrame);
	m_inputs.push_back(input);
}

msg::PlayerFrameInput* GamePlayer::getInput(uint32_t frame)
{
	if (m_inputs.empty())
		return NULL;

	msg::PlayerFrameInput* out = NULL;
	msg::PlayerFrameInput* tmp = NULL;
	std::size_t count = 0;
	for (std::size_t i = 0; i < m_inputs.size(); ++i)
	{
		count = i;
		tmp = m_inputs[i];
		if (tmp->frame() == frame)
		{
			out = tmp;
			m_lastInput.CopyFrom(*tmp);
			m_initLastInput = true;
			break;
		}
	}

	if (out == NULL && m_initLastInput)
	{
		out = &m_lastInput;
	}

	// 释放无效输入
	if (count > 10)
	{
		std::vector<msg::PlayerFrameInput*> tmp;
		tmp.reserve(m_inputs.size());

		std::size_t boundary = count - 2;
		for (std::size_t i = 0; i < m_inputs.size(); ++i)
		{
			if (i >= boundary)
			{
				tmp.push_back(m_inputs[i]);
			}
			else
			{
				enqueue(m_inputs[i]);
			}
		}

		m_inputs.swap(tmp);
	}

	return out;
}

msg::PlayerFrameInput* GamePlayer::dequeue()
{
	if (m_inputCache.empty())
	{
		return new msg::PlayerFrameInput();
	}
	auto tmp = m_inputCache.back();
	tmp->Clear();
	m_inputCache.pop_back();
	return tmp;
}

void GamePlayer::enqueue(msg::PlayerFrameInput* input)
{
	m_inputCache.push_back(input);
}
