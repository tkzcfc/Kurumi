#pragma once

#include "GEventFrame.h"

NS_G_BEGIN

#if RUNTIME_IN_COOCS
class GScriptFrame : public GEventFrame, public cocos2d::Ref
#else
class GScriptFrame : public GEventFrame
#endif
{
public:

	GScriptFrame();

	virtual ~GScriptFrame();


	G_SYNTHESIZE(std::string, m_scriptFile, ScriptFile);
	G_SYNTHESIZE(std::string, m_argStr, ArgStr);
	G_SYNTHESIZE_IS(bool, m_isScriptCode, ScriptCode);

	virtual void serialize(GByteBuffer& byteBuffer) override;

	virtual bool deserialize(GByteBuffer& byteBuffer) override;

	virtual void onEmit() override;
#if RUNTIME_IN_COOCS


	void* getScriptObject() const;

private:

	void getScriptObjectInternal() const;

	bool loadAndExecuteScript();

	void getUserData();

	void storeLuaTable();

	bool getLuaFunction(const std::string& functionName);

	void removeLuaTable();

	static void initClass();
#endif
private:

	bool m_isInitLuaTab;
	bool m_succeedLoadingScript;

	// string value of index
	std::string m_strIndex;

	// the index used to get lua table, it is unique for every component
	static int _index;
};

NS_G_END

