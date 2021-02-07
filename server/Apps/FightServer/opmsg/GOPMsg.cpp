#include "GOPMsg.h"


//! 自动复位的按键
static G_BIT_TYPE s_AutoResetKeyArr[] = {
	G_KEY_JUMP,
	G_KEY_SKILL_1,
	G_KEY_SKILL_2,
	G_KEY_SKILL_3,
	G_KEY_SKILL_4,
	G_KEY_SKILL_5,
	G_KEY_SKILL_6,
	G_KEY_SKILL_7,
};

static G_BIT_TYPE s_AutoResetKey = G_KEY_NONE;

// 判断该键位是否自动复位
bool isAutoResetKey(G_BIT_TYPE key)
{
	for (auto i = 0; i < G_ARRAY_LEN(s_AutoResetKeyArr); ++i)
	{
		if (s_AutoResetKeyArr[i] == key)
			return true;
	}
	return false;
}

G_BIT_TYPE getAutoResetKeys()
{
	if (s_AutoResetKey != G_KEY_NONE)
		return s_AutoResetKey;

	for (auto i = 0; i < G_ARRAY_LEN(s_AutoResetKeyArr); ++i)
	{
		G_BIT_SET(s_AutoResetKey, s_AutoResetKeyArr[i]);
	}
	return s_AutoResetKey;
}


