# countly-sdk-cocos2d-x
Countly SDK for cocos2d-x &amp; cocos2d-js

Troubleshooting
-----
```
NSPersistentStoreCoordinator with a nil model'
```
In this case got to 
https://github.com/Countly/countly-sdk-js/tree/master/src/ios/sdk
Drag and drop "Countly.xcdatamodeld" folder into your plugins folder.
and build it using Xcode.
