#include "GAnimatorCondition.h"
#include "GAnimatorParams.h"

GAnimatorCondition::GAnimatorCondition()
	: m_params(NULL)
	, m_value(0)
	, m_fvalue(0.0f)
	, m_logicType(GLogicType::NONE)
{

}

GAnimatorCondition::GAnimatorCondition(GAnimatorParams* params, const std::string& paramName, int value, float fvalue, GLogicType logicType)
	: m_params(params)
	, m_paramName(paramName)
	, m_value(value)
	, m_fvalue(fvalue)
	, m_logicType(logicType)
{
	assert(m_params != NULL);
}

bool GAnimatorCondition::check()
{
	auto paramType = m_params->getParamType(m_paramName);
	switch (paramType)
	{
	case ParamType::INVALID:
		assert(0);
		break;
	case ParamType::BOOLEAN:
		return m_params->getBool(m_paramName) == (bool)m_value;
		break;
	case ParamType::INTEGER:
	{
		auto value = m_params->getInteger(m_paramName);
		switch (m_logicType)
		{
		case GLogicType::EQUAL:
			return value == m_value;
			break;
		case GLogicType::NOTEQUAL:
			return value != m_value;
			break;
		case GLogicType::GREATER:
			return value > m_value;
			break;
		case GLogicType::LESS:
			return value < m_value;
			break;
		case GLogicType::GREATER_EQUAL:
			return value >= m_value;
			break;
		case GLogicType::LESS_EQUAL:
			return value <= m_value;
			break;
		default:
			break;
		}
	}
		break;
	case ParamType::TRIGGER:
		return m_params->getTrigger(m_paramName) != 0;
		break;
	case ParamType::FLOAT:
	{
		auto value = m_params->getFloat(m_paramName);
		switch (m_logicType)
		{
		case GLogicType::EQUAL:
			return value == m_fvalue;
			break;
		case GLogicType::NOTEQUAL:
			return value != m_fvalue;
			break;
		case GLogicType::GREATER:
			return value > m_fvalue;
			break;
		case GLogicType::LESS:
			return value < m_fvalue;
			break;
		case GLogicType::GREATER_EQUAL:
			return value >= m_fvalue;
			break;
		case GLogicType::LESS_EQUAL:
			return value <= m_fvalue;
			break;
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
	pCondition->m_params = this->m_params;
	pCondition->m_paramName = this->m_paramName;
	pCondition->m_value = this->m_value;
	pCondition->m_fvalue = this->m_fvalue;
	pCondition->m_logicType = this->m_logicType;
}