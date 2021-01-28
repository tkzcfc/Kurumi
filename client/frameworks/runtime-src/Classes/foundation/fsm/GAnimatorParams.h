#pragma once

#include <assert.h>
#include <string>
#include <unordered_map>

enum class ParamType
{
	INVALID = 0,
	BOOLEAN = 1,
	INTEGER = 2,
	TRIGGER = 3,
	FLOAT	= 4,
};

/// 动画状态机参数
class GAnimatorParams
{
public:

	GAnimatorParams();

	ParamType getParamType(const std::string& key);

	void setBool(const std::string& key, bool value);

	void setInteger(const std::string& key, int value);

	void setTrigger(const std::string& key, int value);

	void setFloat(const std::string& key, float value);

	void resetTrigger(const std::string& key);

	bool getBool(const std::string& key);

	int getInteger(const std::string& key);

	int getTrigger(const std::string& key);

	float getFloat(const std::string& key);

	void resetAllTrigger();

private:

	struct Param
	{
		ParamType type;
		union
		{
			bool bvalue;
			int ivalue;
			float fvalue;
		}value;
	};

	inline Param* getParam(const std::string& key)
	{
		auto it = m_params.find(key);
		if (it == m_params.end())
		{
			return NULL;
		}
		return &it->second;
	}

private:

	std::unordered_map<std::string, Param> m_params;
};