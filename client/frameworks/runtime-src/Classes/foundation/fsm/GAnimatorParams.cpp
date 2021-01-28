#include "GAnimatorParams.h"


GAnimatorParams::GAnimatorParams()
{}

ParamType GAnimatorParams::getParamType(const std::string& key)
{
	auto param = getParam(key);
	if (param)
	{
		return param->type;
	}
	return ParamType::INVALID;
}

void GAnimatorParams::setBool(const std::string& key, bool value)
{
	auto param = getParam(key);
	if (param)
	{
		assert(param->type == ParamType::BOOLEAN);
		param->value.bvalue = value;
	}
	else
	{
		Param paramV;
		paramV.type = ParamType::BOOLEAN;
		paramV.value.bvalue = value;
		m_params[key] = paramV;
	}
}

void GAnimatorParams::setInteger(const std::string& key, int value)
{
	auto param = getParam(key);
	if (param)
	{
		assert(param->type == ParamType::INTEGER);
		param->value.ivalue = value;
	}
	else
	{
		Param paramV;
		paramV.type = ParamType::INTEGER;
		paramV.value.ivalue = value;
		m_params[key] = paramV;
	}
}

void GAnimatorParams::setTrigger(const std::string& key, int value)
{
	auto param = getParam(key);
	if (param)
	{
		assert(param->type == ParamType::TRIGGER);
		param->value.ivalue = value;
	}
	else
	{
		Param paramV;
		paramV.type = ParamType::TRIGGER;
		paramV.value.ivalue = value;
		m_params[key] = paramV;
	}
}

void GAnimatorParams::setFloat(const std::string& key, float value)
{
	auto param = getParam(key);
	if (param)
	{
		assert(param->type == ParamType::FLOAT);
		param->value.fvalue = value;
	}
	else
	{
		Param paramV;
		paramV.type = ParamType::FLOAT;
		paramV.value.fvalue = value;
		m_params[key] = paramV;
	}
}

void GAnimatorParams::resetTrigger(const std::string& key)
{
	setTrigger(key, 0);
}

bool GAnimatorParams::getBool(const std::string& key)
{
	auto param = getParam(key);
	if (param == NULL || param->type != ParamType::BOOLEAN)
	{
		assert(0);
		return false;
	}
	return param->value.bvalue;
}

int GAnimatorParams::getInteger(const std::string& key)
{
	auto param = getParam(key);
	if (param == NULL || param->type != ParamType::INTEGER)
	{
		assert(0);
		return 0;
	}
	return param->value.ivalue;
}

int GAnimatorParams::getTrigger(const std::string& key)
{
	auto param = getParam(key);
	if (param == NULL || param->type != ParamType::TRIGGER)
	{
		assert(0);
		return 0;
	}
	return param->value.ivalue;
}

float GAnimatorParams::getFloat(const std::string& key)
{
	auto param = getParam(key);
	if (param == NULL || param->type != ParamType::FLOAT)
	{
		assert(0);
		return 0.0f;
	}
	return param->value.fvalue;
}

void GAnimatorParams::resetAllTrigger()
{
	for (auto& it : m_params)
	{
		if (it.second.type == ParamType::TRIGGER)
		{
			it.second.value.ivalue = 0;
		}
	}
}