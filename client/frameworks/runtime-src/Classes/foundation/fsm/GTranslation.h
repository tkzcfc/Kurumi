#pragma once

#include <assert.h>
#include <string>

typedef std::string FStateKeyType;
typedef int FEventNameType;

static const FStateKeyType FStateKeyInvalid = "";
static const FEventNameType FEventNameInvalid = -1;

class GState;
class GTranslation
{
public:

	GTranslation();

	GTranslation(const FStateKeyType& toState);

	virtual ~GTranslation();

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
	FStateKeyType m_toState;
	FEventNameType m_eventName;
	void* m_userData;
};


class GDelayTranslation : public GTranslation
{
public:

	GDelayTranslation(const FStateKeyType& toState, const float delayTime);

	virtual bool polling(GState* curState)override;

private:

	float m_delayTime;
};