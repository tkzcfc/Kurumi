#include "GAnimatorStateMachine.h"
#include "foundation/GameMacro.h"

///////////////////////////////////////////////////////////////////////////

static GAnimatorState* initStateWithJson(rapidjson::Value& value, GAnimatorState* pState, GAnimatorParams* params, bool isAnyState)
{
	if (!isAnyState)
	{
		auto loop = value.FindMember("loop")->value.GetBool();
		auto motion = value.FindMember("motion")->value.GetString();
		auto speed = (float)value.FindMember("speed")->value.GetDouble();
		auto multiplier = value.FindMember("multiplier")->value.GetString();

		pState->setLoop(loop);

		assert(speed > 0.0f);
		pState->setSpeed(speed);

		if (strlen(motion) > 0)
			pState->setMotion(motion);
		if (strlen(multiplier) > 0)
			pState->setMutiplier(multiplier);
	}

	if (value.HasMember("transitions"))
	{
		auto& transitions = value.FindMember("transitions")->value;
		for (rapidjson::SizeType j = 0U; j < transitions.Size(); j++)
		{
			auto toState = transitions[j].FindMember("toState")->value.GetString();
			auto hasExitTime = transitions[j].FindMember("hasExitTime")->value.GetBool();
			auto& conditions = transitions[j].FindMember("conditions")->value;

			auto pTransition = new GAnimatorTranslation(toState);
			pTransition->setHasExitTime(hasExitTime);

			for (rapidjson::SizeType k = 0U; k < conditions.Size(); k++)
			{
				auto k_param = conditions[k].FindMember("param")->value.GetString();
				auto k_logic = conditions[k].FindMember("logic")->value.GetInt();
				int useparam = 0;
				if(conditions[k].HasMember("useparam"))
					useparam = conditions[k].FindMember("useparam")->value.GetInt();

				if (k_logic < (int)GLogicType::EQUAL || k_logic >= (int)GLogicType::NONE)
				{
					assert(false);
					continue;
				}
				auto condition = GAnimatorCondition(params, k_param);
				if (useparam == 1)
				{
					condition.initConditionP(conditions[k].FindMember("rparam")->value.GetString(), (GLogicType)k_logic);
					pTransition->addCondition(condition);
				}
				else
				{
					auto k_value = conditions[k].FindMember("value")->value.GetInt();
					auto k_fvalue = conditions[k].FindMember("value")->value.GetDouble();
					if (params->getParamType(k_param) == ParamType::BOOLEAN)
					{
						condition.initConditionB(k_value != 0, (GLogicType)k_logic);
						pTransition->addCondition(condition);
					}
					else if (params->getParamType(k_param) == ParamType::INTEGER)
					{
						condition.initConditionI(k_value, (GLogicType)k_logic);
						pTransition->addCondition(condition);
					}
					else if (params->getParamType(k_param) == ParamType::FLOAT)
					{
						condition.initConditionF((float)k_fvalue, (GLogicType)k_logic);
						pTransition->addCondition(condition);
					}
					else if (params->getParamType(k_param) == ParamType::TRIGGER)
					{
						condition.initConditionT();
						pTransition->addCondition(condition);
					}
					else
					{
						assert(false);
					}
				}
			}
			pState->addTranslation(pTransition);
		}
	}

	return pState;
}

///////////////////////////////////////////////////////////////////////////

GAnimatorStateMachine::GAnimatorStateMachine()
	: m_animCompleteState(NULL)
	, m_anyState(NULL)
	, m_animComplete(false)
{
	m_params = std::make_unique<GAnimatorParams>();
	m_fsm = std::make_unique<GFSM>();
}

GAnimatorStateMachine::~GAnimatorStateMachine()
{}

void GAnimatorStateMachine::onStateEnter(GAnimatorState* state)
{
	m_animComplete = false;
}

void GAnimatorStateMachine::onStateStay(GAnimatorState* state)
{}

void GAnimatorStateMachine::onStateExit(GAnimatorState* state)
{}

bool GAnimatorStateMachine::initWithJson(const std::string& content)
{
	rapidjson::Document json;
	rapidjson::StringStream stream(content.c_str());

	json.ParseStream<0>(stream);
	if (json.HasParseError())
	{
		G_LOG_E("'%s' GetParseError %d\n", "GAnimatorStateMachine::initWithJson", json.GetParseError());
		return false;
	}

	if (!json.HasMember("defaultState"))
		return false;

	if (!json.HasMember("states"))
		return false;

	auto dfStateMember = json.FindMember("defaultState");
	if (!dfStateMember->value.IsString())
	{
		return false;
	}

	auto statesMember = json.FindMember("states");
	if (!statesMember->value.IsArray())
	{
		return false;
	}

	// parameters
	if (json.HasMember("parameters"))
	{
		auto paramsMember = json.FindMember("parameters");
		if (!paramsMember->value.IsArray())
			return false;

		for (rapidjson::SizeType i = 0U; i < paramsMember->value.Size(); i++)
		{
			auto& value = paramsMember->value[i];
			if (value.HasMember("param") && value.HasMember("type") && value.HasMember("init"))
			{
				auto type = value.FindMember("type")->value.GetInt();
				auto param = value.FindMember("param")->value.GetString();
				if (type == (int)ParamType::BOOLEAN)
					m_params->setBool(param, value.FindMember("init")->value.GetInt() != 0);
				else if (type == (int)ParamType::INTEGER)
					m_params->setInteger(param, value.FindMember("init")->value.GetInt());
				else if (type == (int)ParamType::TRIGGER)
					m_params->setTrigger(param, value.FindMember("init")->value.GetInt());
				else if (type == (int)ParamType::FLOAT)
					m_params->setFloat(param, (float)value.FindMember("init")->value.GetDouble());
				else
					assert(0);
			}
		}
	}

	// states
	for (rapidjson::SizeType i = 0U; i < statesMember->value.Size(); i++)
	{
		auto& value = statesMember->value[i];
		{
			auto state = value.FindMember("state")->value.GetString();
			auto pState = newState(state);
			m_fsm->addState(initStateWithJson(value, pState, m_params.get(), false));
		}
	}

	// anyState
	if (json.HasMember("anyState"))
	{
		auto& value = json.FindMember("anyState")->value;
		if (value.HasMember("transitions") && value.FindMember("transitions")->value.Size() > 0)
		{
			auto pState = newState("anyState");
			m_fsm->setAnyState(initStateWithJson(value, pState, m_params.get(), true));
		}
	}
	
	// defaultState
	m_fsm->setEntryStateByName(dfStateMember->value.GetString());

	return true;
}

void GAnimatorStateMachine::update(float dt)
{
	m_fsm->update(dt);
	if (m_animComplete)
	{
		if (m_animCompleteState && m_animCompleteState->isLoop())
			resetAnimComplete();
	}

	// 混合播放速度
	auto curState = dynamic_cast<GAnimatorState*>(m_fsm->getCurState());
	if (curState)
	{
		float playSpeed = curState->getSpeed();
		if (curState->getMutiplier().empty() == false)
		{
			playSpeed *= m_params->getFloat(curState->getMutiplier());
		}
		this->scaleTime(playSpeed);
	}
}

void GAnimatorStateMachine::onAnimFinished()
{
	m_animCompleteState = dynamic_cast<GAnimatorState*>(this->m_fsm->getCurState());
	assert(m_animCompleteState != NULL);
	m_animComplete = true;
}

void GAnimatorStateMachine::resetAnimComplete()
{
	m_animCompleteState = NULL;
	m_animComplete = false;
}

void GAnimatorStateMachine::registerStateGenLogic(const FStateKeyType& stateName, const GStateGenInterface& func)
{
	m_stateFactory[stateName] = func;
}

GAnimatorState* GAnimatorStateMachine::newState(const FStateKeyType& stateName)
{
	auto it = m_stateFactory.find(stateName);
	if (it == m_stateFactory.end())
	{
		return new GAnimatorState(this, stateName);
	}
	auto pState = it->second(this, stateName);
	assert(pState != NULL);
	return pState;
}

