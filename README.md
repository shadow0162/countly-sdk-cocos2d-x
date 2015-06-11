# countly-sdk-cocos2d-x
Countly SDK for cocos2d-x &amp; cocos2d-js

it's base on

- [Plugin-x](https://github.com/cocos2d-x/plugin-x)
- [Countly-sdk-js](https://github.com/Countly/countly-sdk-js)

you can get countly server code :
- [Countly Server](https://github.com/Countly/countly-server)


## How to use

1. download cocos2d-x v3.6.x from [cocos2dx org](http://www.cocos2d-x.org/download)
2. setup running environment of android & ios.
3. copy & replace all of files to {coco2dx root}\plugin folder.
4. build & run HelloPlugins sample.

## Using Countly SDK

In Configs.h set the appKey:
```
/**
 @brief Developer information of Countly
 */
#define COUNTLY_KEY_IOS           "def31073c215efdsfsdfsdfa9fra08c7a59ff0"
#define COUNTLY_KEY_ANDROID       "433516e3eawerwerwerwe75b88bab1c5e626af"    
```

In HelloWorldScene.cpp:
```c++
#include "TestCountlyScene.h"
//#include "TestAnalyticsScene.h"
...
case 1:
   //newScene = TestAnalytics::scene();
   newScene = TestCountly::scene();
   break;
...
```
In TestCountlyScene.cpp:
```c++
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
    
    //std::string urlHost = "http://192.168.0.156";
    //PluginParam pParam2(urlHost.c_str());
    
    //_pluginAnalytics->callFuncWithParam("startSessionWithParams", &pParam1,&pParam2, NULL);
    
    _pluginAnalytics->setCaptureUncaughtException(true);
    
    const char* sdkVer = _pluginAnalytics->getSDKVersion().c_str();
    log("SDK version : %s", sdkVer);

}
```

If you want to reuse Umeng & flurry sdk, please uncommment the code in 'HelloWorldScene' below.



## Troubleshooting
```
NSPersistentStoreCoordinator with a nil model'
```
In this case got to 
https://github.com/Countly/countly-sdk-js/tree/master/src/ios/sdk
Drag and drop "Countly.xcdatamodeld" folder into your plugins folder.
and build it using Xcode.