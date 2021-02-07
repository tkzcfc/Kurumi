#pragma once

#include <assert.h>
#include <string>

typedef std::string FStateKeyType;
typedef int FEventNameType;

static const FStateKeyType FStateKeyInvalid = "";
static const FEventNameType FEventNameInvalid = -1;

class GState;
/// 状态转换通道
class GTranslation
{
public:

	GTranslation();

	GTranslation(const FStateKeyType& toState);

	virtual ~GTranslation();

protected:

	virtual bool polling(GState* curState);

	virtual bool progressEvent(GState* curState, const FEventNameType& evetName);

public:

	void setToState(const FStateKeyType& toState);

	const FStateKeyType& getToState();

	void setEventName(const FEventNameType& eventName);

	const FEventNameType& getEventName();

	void setUserData(void* userData);

	void* getUserData();

private:
	friend class GState;
	FStateKeyType m_toState;
	FEventNameType m_eventName;
	void* m_userData;
};


class GDelayTranslation : public GTranslation
{
public:

	GDelayTranslation(const FStateKeyType& toState, const float delayTime);

protected:

	virtual bool polling(GState* curState)override;

private:

	float m_delayTime;
};