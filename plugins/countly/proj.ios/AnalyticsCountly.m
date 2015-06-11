/****************************************************************************
Copyright (c) Shrine Studio
Auth : shadow
****************************************************************************/
#import "AnalyticsCountly.h"
//#import "MobClick.h"
#import "Countly.h"
#define OUTPUT_LOG(...)     if (self.debug) NSLog(__VA_ARGS__);

@implementation AnalyticsCountly

@synthesize debug = __debug;


#pragma mark - Interfaces for ProtocolAds impl

- (void) startSession: (NSString*) appKey
{
    OUTPUT_LOG(@"countly startSession invoked");
    [[Countly sharedInstance] startOnCloudWithAppKey:appKey];
}



- (void) stopSession
{
    OUTPUT_LOG(@"countly stopSession in countly not available on iOS");
}

- (void) setSessionContinueMillis: (long) millis
{
    OUTPUT_LOG(@"countly setSessionContinueMillis in countly not available on iOS");
}

- (void) setCaptureUncaughtException: (BOOL) isEnabled
{
    OUTPUT_LOG(@"countly setCaptureUncaughtException invoked");
}

- (void) setDebugMode: (BOOL) isDebugMode
{
    OUTPUT_LOG(@"countly setDebugMode invoked");
    self.debug = isDebugMode;
}

- (void) logError: (NSString*) errorId withMsg:(NSString*) message
{
    OUTPUT_LOG(@"logError in countly not available on iOS");
}

- (void) logEvent: (NSString*) eventId
{
    OUTPUT_LOG(@"countly logEvent invoked by count 1");
    [[Countly sharedInstance] recordEvent:eventId count:1];
}

- (void) logEvent: (NSString*) eventId withParam:(NSMutableDictionary*) paramMap
{
    OUTPUT_LOG(@"countly logEvent:withParam invoked(%@)", [paramMap debugDescription]);
    NSString* eventName = eventId;
    NSNumber* countInt = (NSNumber*) [paramMap objectForKey:@"Param1"];
    NSNumber* sumFloat = (NSNumber*) [paramMap objectForKey:@"Param2"];
    NSMutableDictionary* dict = (NSMutableDictionary*) [paramMap objectForKey:@"Param3"];
    [[Countly sharedInstance] recordEvent:eventName segmentation:dict count:[countInt integerValue] sum:[sumFloat doubleValue]];

}

- (void) logTimedEventBegin: (NSString*) eventId
{
    OUTPUT_LOG(@"countly logTimedEventBegin invoked");

}

- (void) logTimedEventEnd: (NSString*) eventId
{
    OUTPUT_LOG(@"countly logTimedEventEnd invoked");

}

- (NSString*) getSDKVersion
{
    return @"2.0";
}

- (NSString*) getPluginVersion
{
    return @"1.0.0";
}
#pragma mark - Countly sdk impl
- (void) startSessionWithParams: (NSMutableDictionary*) params
{
    OUTPUT_LOG(@"countly startSessionWithParams invoked(%@)", [params debugDescription]);
    NSString* appKey = (NSString*) [params objectForKey:@"Param1"];
    NSString* serverurl = (NSString*) [params objectForKey:@"Param2"];
    [[Countly sharedInstance] start:appKey withHost:serverurl];
}
- (void) logEventWithParams: (NSMutableDictionary*) params
{
    OUTPUT_LOG(@"countly logEventWithParams invoked(%@)", [params debugDescription]);
    NSString* eventName = (NSString*) [params objectForKey:@"Param1"];
    NSMutableDictionary* dict = (NSMutableDictionary*) [params objectForKey:@"Param2"];
    NSNumber* countInt = (NSNumber*) [params objectForKey:@"Param3"];
    NSNumber* sumFloat = (NSNumber*) [params objectForKey:@"Param4"];
    [[Countly sharedInstance] recordEvent:eventName segmentation:dict count:[countInt integerValue] sum:[sumFloat doubleValue]];
}

@end
