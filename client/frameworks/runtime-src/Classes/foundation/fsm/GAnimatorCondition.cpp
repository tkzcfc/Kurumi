#include "GAnimatorCondition.h"
#include "GAnimatorParams.h"

#define NO_INIT_HASH_VALUE (-1)


GAnimatorCondition::GAnimatorCondition()
	: m_params(NULL)
	, m_logicType(GLogicType::NONE)
	, m_paramHash(NO_INIT_HASH_VALUE)
	, m_compareWithParam(false)
{
	memset(&m_value, 0, sizeof(m_value));
}

GAnimatorCondition::GAnimatorCondition(GAnimatorParams* params, const std::string& paramName)
	: m_params(params)
	, m_logicType(GLogicType::NONE)
	, m_compareWithParam(false)
{
	memset(&m_value, 0, sizeof(m_value));

	m_paramHash = m_params->hashKey(paramName);
	assert(m_paramHash >= 0);
}

bool GAnimatorCondition::initConditionI(int value, GLogicType logicType)
{
	m_value.ivalue = value;
	m_logicType = logicType;
	return true;
}

bool GAnimatorCondition::initConditionB(bool value, GLogicType logicType)
{
	m_value.bvalue = value;
	m_logicType = logicType;
	return true;
}

bool GAnimatorCondition::initConditionF(float value, GLogicType logicType)
{
	m_value.fvalue = value;
	m_logicType = logicType;
	return true;
}

bool GAnimatorCondition::initConditionP(const std::string param, GLogicType logicType)
{
	assert(m_params->getParamType(m_paramHash) == m_params->getParamType(param));
	m_value.hash = m_params->hashKey(param);
	m_logicType = logicType;
	m_compareWithParam = true;
	return true;
}

bool GAnimatorCondition::initConditionT()
{
	return true;
}

bool GAnimatorCondition::check()
{
	auto paramType = m_params->getParamType(m_paramHash);
	switch (paramType)
	{
	case ParamType::INVALID:
		assert(0);
		break;
	case ParamType::BOOLEAN:
	{
		auto rvalue = m_compareWithParam ? m_params->getBool(m_value.hash) : m_value.bvalue;
		return m_params->getBool(m_paramHash) == rvalue;
	}
		break;
	case ParamType::INTEGER:
	{
		auto value = m_params->getInteger(m_paramHash);
		auto rvalue = m_compareWithParam ? m_params->getInteger(m_value.hash) : m_value.ivalue;
		switch (m_logicType)
		{
		case GLogicType::EQUAL:
			return value == rvalue;
		case GLogicType::NOTEQUAL:
			return value != rvalue;
		case GLogicType::GREATER:
			return value > rvalue;
		case GLogicType::LESS:
			return value < rvalue;
		case GLogicType::GREATER_EQUAL:
			return value >= rvalue;
		case GLogicType::LESS_EQUAL:
			return value <= rvalue;
		default:
			break;
		}
	}
		break;
	case ParamType::TRIGGER:
		return m_params->getTrigger(m_paramHash) != 0;
		break;
	case ParamType::FLOAT:
	{
		auto value = m_params->getFloat(m_paramHash);
		auto rvalue = m_compareWithParam ? m_params->getFloat(m_value.hash) : m_value.fvalue;
		switch (m_logicType)
		{
		case GLogicType::EQUAL:
			return value == rvalue;
		case GLogicType::NOTEQUAL:
			return value != rvalue;
		case GLogicType::GREATER:
			return value > rvalue;
		case GLogicType::LESS:
			return value < rvalue;
		case GLogicType::GREATER_EQUAL:
			return value >= rvalue;
		case GLogicType::LESS_EQUAL:
			return value <= rvalue;
		default:
			break;
		}
	}
	break;
	default:
		assert(0);
		break;
	}
	return false;
}

void GAnimatorCondition::clone(GAnimatorCondition* pCondition) const
{
	pCondition->m_params	= this->m_params;
	pCondition->m_value		= this->m_value;
	pCondition->m_compareWithParam = this->m_compareWithParam;
	pCondition->m_logicType = this->m_logicType;
	pCondition->m_paramHash = this->m_paramHash;
}