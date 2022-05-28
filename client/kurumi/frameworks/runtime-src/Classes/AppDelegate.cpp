/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "AppDelegate.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "cocos2d.h"
#include "scripting/lua-bindings/manual/lua_module_register.h"
#include "external/xxtea/xxtea.h"
#include "lua_modules/custom_lua_modules.h"

#define RUN_TEST_SCENE 0

#if RUN_TEST_SCENE
#include "test/TestScene.h"
#include "test/TestScene1.h"
#endif

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0 };

    GLView::setGLContextAttrs(glContextAttrs);
}

int register_custom_module(lua_State* L)
{
	custom_lua_modules(L);
    // Register your custom module add in Classes here.
    return 1;
}

static void decoder(Data &data)
{
    unsigned char sign[] = "XXXXXXXX";
    unsigned char key[] = "xyzabc";

    // decrypt XXTEA
    if (!data.isNull()) {
        bool isEncoder = false;
        unsigned char *buf = data.getBytes();
        ssize_t size = data.getSize();
        ssize_t len = strlen((char *)sign);
        if (size <= len) {
            return;
        }

        for (int i = 0; i < len; ++i) {
            isEncoder = buf[i] == sign[i];
            if (!isEncoder) {
                break;
            }
        }

        if (isEncoder) {
            xxtea_long newLen = 0;
            unsigned char* buffer = xxtea_decrypt(buf + len,
                    (xxtea_long)(size - len),
                    (unsigned char*)key,
                    (xxtea_long)strlen((char *)key),
                    &newLen);
            data.clear();
            data.fastSet(buffer, newLen);
        }
    }
}

bool AppDelegate::applicationDidFinishLaunching()
{
#if	CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM
	auto defaultResourceRootPath = FileUtils::getInstance()->getDefaultResourceRootPath();
	if (defaultResourceRootPath.back() == '/')
	{
		defaultResourceRootPath.erase(defaultResourceRootPath.size() - 1);
	}

	auto writePath = defaultResourceRootPath.substr(0, defaultResourceRootPath.find_last_of('/') + 1);
	FileUtils::getInstance()->setWritablePath(writePath);
	CCLOG("writePath:%s", writePath.c_str());

	if (!FileUtils::getInstance()->isDirectoryExist(defaultResourceRootPath))
	{
		if (writePath.back() == '/')
		{
			writePath.erase(writePath.size() - 1);
		}
		auto newPath = writePath.substr(0, writePath.find_last_of('/') + 1);
		FileUtils::getInstance()->setDefaultResourceRootPath(newPath);
        CCLOG("newPath:%s", newPath.c_str());
	}
#endif

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
		glview = cocos2d::GLViewImpl::createWithRect("kurumi", Rect(0, 0, 1136, 640));
        director->setOpenGLView(glview);
        director->startAnimation();
    }

    // set default FPS
    director->setAnimationInterval(1.0 / 60.0f);

    // register lua module
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    LuaStack *stack = engine->getLuaStack();
    lua_State *L = stack->getLuaState();
    lua_module_register(L);
    //register custom function
    register_custom_module(L);
	
    // resource decode, game32.zip & game64.zip deal as resoruce.
    FileUtils::getInstance()->setFileDataDecoder(decoder);
#if 0 // set to 1 for release mode
    // use luajit bytecode package
#if defined(__aarch64__) || defined(__arm64__) || defined(__x86_64__)
    stack->loadChunksFromZIP("res/game64.zip");
#else
    stack->loadChunksFromZIP("res/game32.zip");
#endif
    stack->executeString("require 'main'");
#else // #if 0

	auto writablePath = FileUtils::getInstance()->getWritablePath();
#if defined(__aarch64__) || defined(__arm64__) || defined(__x86_64__)
	FileUtils::getInstance()->addSearchPath(writablePath + "hot_up/res/");
	FileUtils::getInstance()->addSearchPath(writablePath + "hot_up/src64/");
	FileUtils::getInstance()->addSearchPath(writablePath + "hot_up/src/");
	FileUtils::getInstance()->addSearchPath("res/");
	FileUtils::getInstance()->addSearchPath("src64/");
	FileUtils::getInstance()->addSearchPath("src/");
#else
	FileUtils::getInstance()->addSearchPath(writablePath + "hot_up/res/");
	FileUtils::getInstance()->addSearchPath(writablePath + "hot_up/src32/");
	FileUtils::getInstance()->addSearchPath(writablePath + "hot_up/src/");
	FileUtils::getInstance()->addSearchPath("res/");
	FileUtils::getInstance()->addSearchPath("src32/");
	FileUtils::getInstance()->addSearchPath("src/");
#endif


#if RUN_TEST_SCENE
	FileUtils::getInstance()->addSearchPath("res/");
	FileUtils::getInstance()->addSearchPath("src/");


	//Director::getInstance()->runWithScene(TestScene::createScene());
	Director::getInstance()->runWithScene(TestScene1::createScene());
	Director::getInstance()->setDisplayStats(true);
#else
	// use discrete files
	engine->executeScriptFile("main.lua");
#endif
#endif

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("APP_ENTER_BACKGROUND_EVENT");
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("APP_ENTER_FOREGROUND_EVENT");
}
