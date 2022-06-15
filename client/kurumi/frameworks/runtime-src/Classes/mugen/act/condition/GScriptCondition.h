#pragma once

#include "GCondition.h"

NS_G_BEGIN


/// 条件
#if RUNTIME_IN_COOCS
class GScriptCondition : public GCondition, public cocos2d::Ref
#else
class GScriptCondition : public GCondition
#endif
{
public:
	
	GScriptCondition();
	
	virtual ~GScriptCondition();
	
	virtual void serialize(GByteBuffer& byteBuffer);

	virtual bool deserialize(GByteBuffer& byteBuffer);

	G_SYNTHESIZE(std::string, m_scriptFile, ScriptFile);
	G_SYNTHESIZE(std::string, m_argStr, ArgStr);
	G_SYNTHESIZE_IS(bool, m_isScriptCode, ScriptCode);

	virtual bool check() override;

#if RUNTIME_IN_COOCS
	
	virtual void reset() override;

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