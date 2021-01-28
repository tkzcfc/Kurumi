#include "GAnimatorStateMachine.h"
#include "json/stringbuffer.h"
#include "json/document.h"
#include "foundation/GameMacro.h"


///////////////////////////////////////////////////////////////////////////

static GAnimatorState* createStateWithJson(rapidjson::Value& value, GAnimatorStateMachine* stateMachine, GAnimatorParams* params, bool isAnyState)
{
	GAnimatorState* pState = NULL;
	if (isAnyState)
	{
		pState = new GAnimatorState(stateMachine, "AnyState");
	}
	else
	{
		auto state = value.FindMember("state")->value.GetString();
		auto loop = value.FindMember("loop")->value.GetBool();
		auto motion = value.FindMember("motion")->value.GetString();
		auto speed = value.FindMember("speed")->value.GetFloat();
		auto multiplier = value.FindMember("multiplier")->value.GetString();

		pState = new GAnimatorState(stateMachine, state);
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
		auto transitions = value.FindMember("transitions")->value.GetArray();
		for (rapidjson::SizeType j = 0U; j < transitions.Size(); j++)
		{
			auto toState = transitions[j].FindMember("toState")->value.GetString();
			auto hasExitTime = transitions[j].FindMember("hasExitTime")->value.GetBool();
			auto conditions = transitions[j].FindMember("conditions")->value.GetArray();

			auto pTransition = new GAnimatorTranslation(toState);
			pTransition->setHasExitTime(hasExitTime);

			for (rapidjson::SizeType k = 0U; k < conditions.Size(); k++)
			{
				auto k_param = conditions[k].FindMember("param")->value.GetString();
				auto k_value = conditions[k].FindMember("value")->value.GetInt();
				auto k_fvalue = conditions[k].FindMember("value")->value.GetFloat();
				auto k_logic = conditions[k].FindMember("logic")->value.GetInt();

				if (k_logic == (int)GLogicType::EQUAL)
					pTransition->addCondition(GAnimatorCondition(params, k_param, k_value, k_fvalue, GLogicType::EQUAL));
				else if (k_logic == (int)GLogicType::NOTEQUAL)
					pTransition->addCondition(GAnimatorCondition(params, k_param, k_value, k_fvalue, GLogicType::NOTEQUAL));
				else if (k_logic == (int)GLogicType::GREATER)
					pTransition->addCondition(GAnimatorCondition(params, k_param, k_value, k_fvalue, GLogicType::GREATER));
				else if (k_logic == (int)GLogicType::LESS)
					pTransition->addCondition(GAnimatorCondition(params, k_param, k_value, k_fvalue, GLogicType::LESS));
				else if (k_logic == (int)GLogicType::GREATER_EQUAL)
					pTransition->addCondition(GAnimatorCondition(params, k_param, k_value, k_fvalue, GLogicType::GREATER_EQUAL));
				else if (k_logic == (int)GLogicType::LESS_EQUAL)
					pTransition->addCondition(GAnimatorCondition(params, k_param, k_value, k_fvalue, GLogicType::LESS_EQUAL));
				else
					assert(false);
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
		G_LOG_E("'%s' GetParseError %d\n", file, json.GetParseError());
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
					m_params->setBool(param, (bool)value.FindMember("init")->value.GetInt());
				else if (type == (int)ParamType::INTEGER)
					m_params->setInteger(param, value.FindMember("init")->value.GetInt());
				else if (type == (int)ParamType::TRIGGER)
					m_params->setTrigger(param, value.FindMember("init")->value.GetInt());
				else if (type == (int)ParamType::FLOAT)
					m_params->setFloat(param, value.FindMember("init")->value.GetFloat());
				else
					assert(0);
			}
		}
	}

	// states
	for (rapidjson::SizeType i = 0U; i < statesMember->value.Size(); i++)
	{
		auto& value = statesMember->value[i];
		m_fsm->addState(createStateWithJson(value, this, m_params.get(), false));
	}

	// anyState
	if (json.HasMember("anyState"))
	{
		auto& value = json.FindMember("anyState")->value;
		if(value.HasMember("transitions") && value.FindMember("transitions")->value.Size() > 0)
			m_fsm->setAnyState(createStateWithJson(value, this, m_params.get(), true));
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
