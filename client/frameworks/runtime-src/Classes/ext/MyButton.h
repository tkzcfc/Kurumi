#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "lua_function/LuaFunction.h"

USING_NS_CC;

class MyButton : public ui::Button
{
public:
	MyButton();

	virtual ~MyButton();

	/**
	* Create a empty Button.
	*@return A empty Button instance.
	*/
	static MyButton* create();

	///**
	//* Create a button with custom textures.
	//* @param normalImage normal state texture name.
	//* @param selectedImage  selected state texture name.
	//* @param disableImage disabled state texture name.
	//* @param texType    @see `TextureResType`
	//* @return a Button instance.
	//*/
	//static MyButton* create(const std::string& normalImage,
	//	const std::string& selectedImage = "",
	//	const std::string& disableImage = "",
	//	ui::TextureResType texType = ui::TextureResType::LOCAL);

	void registerStateChangedCall(int call);

	void enableTouchScaleEffect();

	void disenableTouchScaleEffect();

	void setScaleOnPressed(float scale);

	float getScaleOnPressed();

protected:

	virtual void onEnter()override;

	virtual void onPressStateChangedToNormal() override;
	virtual void onPressStateChangedToPressed() override;
	virtual void onPressStateChangedToDisabled() override;

	virtual ui::Widget* createCloneInstance() override;
	virtual void copySpecialProperties(Widget* model) override;
protected:
	bool m_initOriginalScale;
	float m_originalScaleX;
	float m_originalScaleY;
	LuaFunction* m_stateChangedLuaHandle;
	bool m_touchScaleEffectEnabled;
	bool m_pressedTag;
	float m_scaleOnPressed;
};
