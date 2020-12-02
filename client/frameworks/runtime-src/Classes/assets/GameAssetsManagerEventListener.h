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

#ifndef __cocos2d_libs__GameAssetsManagerEventListener__
#define __cocos2d_libs__GameAssetsManagerEventListener__

#include "base/CCEventListener.h"
#include "base/CCEventListenerCustom.h"
//#include "extensions/ExtensionMacros.h"
//#include "extensions/ExtensionExport.h"

#include "lua_function/LuaFunction.h"


class GameAssetsManagerEvent;
class GameAssetsManager;

/**
 *  Usage:
 *        auto dispatcher = Director::getInstance()->getEventDispatcher();
 *        auto manager = GameAssetsManager::create(manifestUrl, storagePath);
 *     Adds a listener:
 *
 *        auto callback = [](GameAssetsManagerEvent* event){ do_some_thing(); };
 *        auto listener = GameAssetsManagerEventListener::create(manager, callback);
 *        dispatcher->addEventListenerWithSceneGraphPriority(listener, one_node);
 *
 *     Removes a listener
 *
 *        dispatcher->removeEventListener(listener);
 */
class GameAssetsManagerEventListener : public cocos2d::EventListenerCustom
{
public:
    friend class GameAssetsManager;
    
    /** Creates an event listener with type and callback.
     *  @param eventType The type of the event.
     *  @param callback The callback function when the specified event was emitted.
     */
    static GameAssetsManagerEventListener* create(GameAssetsManager *gameAssetsManager, const std::function<void(GameAssetsManagerEvent*)>& callback);
    
	static GameAssetsManagerEventListener* create(GameAssetsManager* gameAssetsManager, int handle);

    /// Overrides
    virtual bool checkAvailable() override;
    virtual GameAssetsManagerEventListener* clone() override;
    
CC_CONSTRUCTOR_ACCESS:
    /** Constructor */
    GameAssetsManagerEventListener();
    
    /** Initializes event with type and callback function */
    bool init(const GameAssetsManager *gameAssetsManager, const std::function<void(GameAssetsManagerEvent*)>& callback);

	bool init(const GameAssetsManager *gameAssetsManager, int callback);
    
protected:
    static const std::string LISTENER_ID;
    
    std::function<void(GameAssetsManagerEvent*)> _onAssetsManagerExEvent;
    
    const GameAssetsManager *_assetsManagerEx;
    
    //friend class luaGameAssetsManagerEventListener;

	LuaFunction m_luaHandle;
};

#endif /* defined(__cocos2d_libs__GameAssetsManagerEventListener__) */
