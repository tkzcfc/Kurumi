/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameAssetsManagerEventListener.h"
#include "GameAssetsManagerEvent.h"
#include "GameAssetsManager.h"
#include "cocos2d.h"

using namespace cocos2d;

const std::string GameAssetsManagerEventListener::LISTENER_ID = "__game_assets_manager_";

GameAssetsManagerEventListener::GameAssetsManagerEventListener()
: _onAssetsManagerExEvent(nullptr)
, _assetsManagerEx(nullptr)
{
}

GameAssetsManagerEventListener* GameAssetsManagerEventListener::create(GameAssetsManager *gameAssetsManager, const std::function<void(GameAssetsManagerEvent*)>& callback)
{
    GameAssetsManagerEventListener* ret = new GameAssetsManagerEventListener();
    if (ret && ret->init(gameAssetsManager, callback))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

GameAssetsManagerEventListener* GameAssetsManagerEventListener::create(GameAssetsManager* gameAssetsManager, const LuaFunction& handle)
{
	GameAssetsManagerEventListener* ret = new GameAssetsManagerEventListener();
	if (ret && ret->init(gameAssetsManager, handle))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool GameAssetsManagerEventListener::init(const GameAssetsManager *gameAssetsManager, const std::function<void(GameAssetsManagerEvent*)>& callback)
{
    bool ret = false;
    
    _assetsManagerEx = gameAssetsManager;
    _onAssetsManagerExEvent = callback;
    
    auto func = [this](EventCustom *event) -> void
    {
		GameAssetsManagerEvent *eventAssetsManagerEx = dynamic_cast<GameAssetsManagerEvent*>(event);
        _onAssetsManagerExEvent(eventAssetsManagerEx);
    };
    std::string pointer = StringUtils::format("%p", gameAssetsManager);
    if (EventListenerCustom::init(LISTENER_ID + pointer, func))
    {
        ret = true;
    }
    return ret;
}

bool GameAssetsManagerEventListener::init(const GameAssetsManager *gameAssetsManager, const LuaFunction& handle)
{
	bool ret = false;

	_assetsManagerEx = gameAssetsManager;
	m_luaHandle = handle;

	auto func = [this](EventCustom *event) -> void
	{
		GameAssetsManagerEvent *eventAssetsManagerEx = dynamic_cast<GameAssetsManagerEvent*>(event);
		
		if (m_luaHandle.isvalid())
		{
			m_luaHandle.ppush();
			m_luaHandle.pushusertype(eventAssetsManagerEx, "GameAssetsManagerEvent");
			m_luaHandle.pcall();
		}
	};
	std::string pointer = StringUtils::format("%p", gameAssetsManager);
	if (EventListenerCustom::init(LISTENER_ID + pointer, func))
	{
		ret = true;
	}
	return ret;
}

GameAssetsManagerEventListener* GameAssetsManagerEventListener::clone()
{
	CC_ASSERT(0 && "clone is not supported.");
	return NULL;
    //GameAssetsManagerEventListener* ret = new GameAssetsManagerEventListener();
    //if (ret && ret->init(_assetsManagerEx, _onAssetsManagerExEvent))
    //{
    //    ret->autorelease();
    //}
    //else
    //{
    //    CC_SAFE_DELETE(ret);
    //}
    //return ret;
}

bool GameAssetsManagerEventListener::checkAvailable()
{
    bool ret = false;
    if (EventListener::checkAvailable() && _assetsManagerEx != nullptr)
    {
		if (_onAssetsManagerExEvent != nullptr || m_luaHandle.isvalid())
		{
			ret = true;
		}
    }
    return ret;
}
