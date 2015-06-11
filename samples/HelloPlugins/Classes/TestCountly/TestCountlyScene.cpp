/****************************************************************************
 Copyright (c) 2012-2013 cocos2d-x.org
 
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
#include "TestCountlyScene.h"
#include "PluginManager.h"
#include "HelloWorldScene.h"
#include "Configs.h"

using namespace cocos2d;
using namespace cocos2d::plugin;

enum {
    TAG_LOG_EVENT_ID = 0,
};

typedef struct tagEventMenuItem {
    std::string id;
    int tag;
}EventMenuItem;

static EventMenuItem s_EventMenuItem[] = {
    {"LogEvent-eventId"   , TAG_LOG_EVENT_ID},
};

Scene* TestCountly::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    TestCountly *layer = TestCountly::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestCountly::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    _pluginAnalytics = NULL;
    loadPlugins();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    Point posBR = Point(origin.x + visibleSize.width, origin.y);
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemFont *pBackItem = MenuItemFont::create("Back", CC_CALLBACK_1(TestCountly::menuBackCallback, this));
    Size backSize = pBackItem->getContentSize();
    pBackItem->setPosition(posBR + Point(- backSize.width / 2, backSize.height / 2));
    
    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create(pBackItem, NULL);
    pMenu->setPosition( Point::ZERO );
    this->addChild(pMenu, 1);
    
    float yPos = 0;
    for (int i = 0; i < sizeof(s_EventMenuItem)/sizeof(s_EventMenuItem[0]); i++) {
        Label* label = Label::create(s_EventMenuItem[i].id.c_str(), "Arial", 24);
        MenuItemLabel* pMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(TestCountly::eventMenuCallback, this));
        pMenu->addChild(pMenuItem, 0, s_EventMenuItem[i].tag);
        yPos = visibleSize.height - 35*i - 100;
        pMenuItem->setPosition( Point(visibleSize.width / 2, yPos));
    }
    
    std::string strName = _pluginAnalytics->getPluginName();
    std::string strVer = _pluginAnalytics->getSDKVersion();
    char ret[256] = { 0 };
    sprintf(ret, "Plugin : %s, Ver : %s", strName.c_str(), strVer.c_str());
    Label* pLabel = Label::create(ret, "Arial", 18, Size(visibleSize.width, 0), TextHAlignment::CENTER);
    pLabel->setPosition(Point(visibleSize.width / 2, yPos - 80));
    addChild(pLabel);
    
    return true;
}

void TestCountly::onExit()
{
    unloadPlugins();
    Layer::onExit();
}

void TestCountly::eventMenuCallback(Ref* pSender)
{
    MenuItemLabel* pMenuItem = (MenuItemLabel*)pSender;
    
    switch (pMenuItem->getTag())
    {
        case TAG_LOG_EVENT_ID:
        {
            
            
            PluginParam event("purchase");
            
            LogEventParamMap paramMap;
            paramMap.insert(LogEventParamPair("purchase_id", "product02"));
            PluginParam mapValue(paramMap);
            
            PluginParam count(1);
            
            PluginParam sum(5.8f);
            _pluginAnalytics->callFuncWithParam("logEventWithParams", &event, &mapValue, &count,&sum, NULL);
        }
            break;
            
        default:
            break;
    }
}

void TestCountly::loadPlugins()
{
    LanguageType langType = Application::getInstance()->getCurrentLanguage();
    
    std::string countlyKey = "";
    std::string pluginName = "";
    std::string strAppKey = "";
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    countlyKey = COUNTLY_KEY_IOS;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    countlyKey = COUNTLY_KEY_ANDROID;
#endif
    
    
    pluginName = "AnalyticsCountly";
    strAppKey = countlyKey;
    
    _pluginAnalytics = dynamic_cast<ProtocolAnalytics*> (PluginManager::getInstance()->loadPlugin(pluginName.c_str()));
    
    _pluginAnalytics->setDebugMode(true);
    //start on cloud
    _pluginAnalytics->startSession(strAppKey.c_str());
    
    //start on local
    //PluginParam pParam1(strAppKey.c_str());
    
    //std::string urlHost = "http://127.0.0.1";
    //PluginParam pParam2(urlHost.c_str());
    
    //_pluginAnalytics->callFuncWithParam("startSessionWithParams", &pParam1,&pParam2, NULL);
    
    _pluginAnalytics->setCaptureUncaughtException(true);
    
    const char* sdkVer = _pluginAnalytics->getSDKVersion().c_str();
    log("SDK version : %s", sdkVer);

}

void TestCountly::unloadPlugins()
{
    if (NULL != _pluginAnalytics) {
        _pluginAnalytics->stopSession();
        
        std::string pluginName = _pluginAnalytics->getPluginName();
        PluginManager::getInstance()->unloadPlugin(pluginName.c_str());
        _pluginAnalytics = NULL;
    }
}

void TestCountly::menuBackCallback(Ref* pSender)
{
    Scene* newScene = HelloWorld::scene();
    Director::getInstance()->replaceScene(newScene);
}
