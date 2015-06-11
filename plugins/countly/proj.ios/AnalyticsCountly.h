#import "InterfaceAnalytics.h"

@interface AnalyticsCountly : NSObject <InterfaceAnalytics>
{
}

@property BOOL debug;

/**
 interfaces of protocol : InterfaceAnalytics
 */
- (void) startSession: (NSString*) appKey;
- (void) stopSession;
- (void) setSessionContinueMillis: (long) millis;
- (void) setCaptureUncaughtException: (BOOL) isEnabled;
- (void) setDebugMode: (BOOL) isDebugMode;
- (void) logError: (NSString*) errorId withMsg:(NSString*) message;
- (void) logEvent: (NSString*) eventId;
- (void) logEvent: (NSString*) eventId withParam:(NSMutableDictionary*) paramMap;
- (void) logTimedEventBegin: (NSString*) eventId;
- (void) logTimedEventEnd: (NSString*) eventId;
- (NSString*) getSDKVersion;
- (NSString*) getPluginVersion;

/**
 interfaces of countly SDK
 */

- (void) startSessionWithParams: (NSMutableDictionary*) params;
- (void) logEventWithParams:(NSMutableDictionary*) params;

@end
