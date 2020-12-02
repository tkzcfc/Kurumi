#include "MyButton.h"

static constexpr float ZOOM_ACTION_TIME_STEP1 = 0.05f;
static constexpr float ZOOM_ACTION_TIME_STEP2 = 0.1f;

static constexpr int ACTION_TAG_SCALE_ON_PRESSED = 0xbbcc01;
static constexpr int ACTION_TAG_SCALE_ON_NORMAL = 0xbbcc02;

MyButton::MyButton()
	: m_originalScaleX(1.0f)
	, m_originalScaleY(1.0f)
	, m_initOriginalScale(false)
	, m_stateChangedLuaHandle(NULL)
	, m_touchScaleEffectEnabled(true)
	, m_pressedTag(false)
	, m_scaleOnPressed(0.95f)
{
	this->setZoomScale(-0.05f);
	this->setPressedActionEnabled(false);
}

MyButton::~MyButton()
{
	CC_SAFE_DELETE(m_stateChangedLuaHandle);
}

MyButton* MyButton::create()
{
	MyButton* widget = new (std::nothrow) MyButton();
	if (widget && widget->init())
	{
		widget->autorelease();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return nullptr;
}

//MyButton* MyButton::create(const std::string &normalImage,
//	const std::string& selectedImage,
//	const std::string& disableImage,
//	ui::TextureResType texType)
//{
//	MyButton *btn = new (std::nothrow) MyButton;
//	if (btn && btn->init(normalImage, selectedImage, disableImage, texType))
//	{
//		btn->autorelease();
//		return btn;
//	}
//	CC_SAFE_DELETE(btn);
//	return nullptr;
//}

void MyButton::onEnter()
{
	ui::Button::onEnter();
	if (!m_initOriginalScale)
	{
		m_originalScaleX = this->getScaleX();
		m_originalScaleY = this->getScaleY();
		m_initOriginalScale = !m_initOriginalScale;
	}
}

void MyButton::onPressStateChangedToNormal()
{
	ui::Button::onPressStateChangedToNormal();

	if (!m_pressedTag)
	{
		m_pressedTag = false;
		return;
	}

	if (m_stateChangedLuaHandle && m_stateChangedLuaHandle->isvalid())
	{
		m_stateChangedLuaHandle->ppush();
		m_stateChangedLuaHandle->pusharg("normal");
		m_stateChangedLuaHandle->pcall();
	}

	//CCLOG("ACTION_TAG_SCALE_ON_NORMAL - %d", this->getActionByTag(ACTION_TAG_SCALE_ON_NORMAL));
	//CCLOG("ACTION_TAG_SCALE_ON_PRESSED - %d", this->getActionByTag(ACTION_TAG_SCALE_ON_PRESSED));
	
	this->stopActionByTag(ACTION_TAG_SCALE_ON_NORMAL);
	this->stopActionByTag(ACTION_TAG_SCALE_ON_PRESSED);
	
	if (!m_touchScaleEffectEnabled)
	{
		return;
	}

	auto action = ScaleTo::create(ZOOM_ACTION_TIME_STEP1, m_originalScaleX, m_originalScaleY);
	action->setTag(ACTION_TAG_SCALE_ON_NORMAL);
	this->runAction(action);
}

void MyButton::onPressStateChangedToPressed()
{
	m_pressedTag = true;

	ui::Button::onPressStateChangedToPressed();
	if (m_stateChangedLuaHandle && m_stateChangedLuaHandle->isvalid())
	{
		m_stateChangedLuaHandle->ppush();
		m_stateChangedLuaHandle->pusharg("pressed");
		m_stateChangedLuaHandle->pcall();
	}

	//CCLOG("ACTION_TAG_SCALE_ON_NORMAL - %d", this->getActionByTag(ACTION_TAG_SCALE_ON_NORMAL));
	//CCLOG("ACTION_TAG_SCALE_ON_PRESSED - %d", this->getActionByTag(ACTION_TAG_SCALE_ON_PRESSED));

	this->stopActionByTag(ACTION_TAG_SCALE_ON_NORMAL);
	this->stopActionByTag(ACTION_TAG_SCALE_ON_PRESSED);

	if (!m_touchScaleEffectEnabled)
	{
		return;
	}
	auto action = ScaleTo::create(ZOOM_ACTION_TIME_STEP2, m_originalScaleX * m_scaleOnPressed, m_originalScaleY * m_scaleOnPressed);
	action->setTag(ACTION_TAG_SCALE_ON_PRESSED);
	this->runAction(action);
}

void MyButton::onPressStateChangedToDisabled()
{
	ui::Button::onPressStateChangedToDisabled();
	if (m_stateChangedLuaHandle && m_stateChangedLuaHandle->isvalid())
	{
		m_stateChangedLuaHandle->ppush();
		m_stateChangedLuaHandle->pusharg("disabled");
		m_stateChangedLuaHandle->pcall();
	}
}

void MyButton::enableTouchScaleEffect()
{
	m_touchScaleEffectEnabled = true;
}

void MyButton::disenableTouchScaleEffect()
{
	m_touchScaleEffectEnabled = false;
}

void MyButton::setScaleOnPressed(float scale)
{
	m_scaleOnPressed = scale;
}

float MyButton::getScaleOnPressed()
{
	return m_scaleOnPressed;
}

void MyButton::registerStateChangedCall(int call)
{
	CC_SAFE_DELETE(m_stateChangedLuaHandle);
	m_stateChangedLuaHandle = new LuaFunction(call);
}

ui::Widget* MyButton::createCloneInstance()
{
	return MyButton::create();
}

void MyButton::copySpecialProperties(Widget* widget)
{
	MyButton* button = dynamic_cast<MyButton*>(widget);
	if (button)
	{
		button->m_touchScaleEffectEnabled = this->m_touchScaleEffectEnabled;
		button->m_scaleOnPressed = this->m_scaleOnPressed;
	}
}