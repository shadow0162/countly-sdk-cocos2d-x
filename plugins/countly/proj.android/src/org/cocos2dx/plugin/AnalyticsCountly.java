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
package org.cocos2dx.plugin;

import java.util.HashMap;
import java.util.Hashtable;
import java.util.Iterator;

import org.json.JSONObject;

import android.content.Context;
import android.util.Log;

import ly.count.android.api.Countly;
import ly.count.android.api.DeviceId;

public class AnalyticsCountly implements InterfaceAnalytics {

	private Context mContext = null;

	protected static String TAG = "AnalyticsCountly";

	protected static void LogE(String msg, Exception e) {
		Log.e(TAG, msg, e);
		e.printStackTrace();
	}

	private static boolean isDebug = true;

	protected static void LogD(String msg) {
		if (isDebug) {
			Log.d(TAG, msg);
		}
	}

	public AnalyticsCountly(Context context) {
		mContext = context;
	}

	public boolean isValid() {
		return mContext != null;
	}

	@Override
	public void startSession(String appKey) {
		LogD("startSession invoked on Countly Cloud!");
		String serverUrl = "https://cloud.count.ly";
		// serverUrl = serverUrl.replace("https://", "http://");
		Countly.sharedInstance().init(mContext, serverUrl, appKey, null,
				DeviceId.Type.OPEN_UDID);
		Countly.sharedInstance().onStart();
	}

	@Override
	public void stopSession() {
		LogD("stopSession invoked!");
		Countly.sharedInstance().onStop();
	}

	@Override
	public void setSessionContinueMillis(int millis) {
		LogD("setSessionContinueMillis is not in Countly!");
	}

	@Override
	public void setCaptureUncaughtException(boolean isEnabled) {
		LogD("setCaptureUncaughtException is not in Countly!");
	}

	@Override
	public void setDebugMode(boolean isDebugMode) {
		isDebug = isDebugMode;
		Countly.sharedInstance().setLoggingEnabled(isDebugMode);
	}

	@Override
	public void logError(String errorId, String message) {
		LogD("logError invoked!");
	}

	@Override
	public void logEvent(String eventId) {
		LogD("logEvent(" + eventId + ") invoked!");
		Countly.sharedInstance().recordEvent(eventId, 1);
	}

	@Override
	public void logEvent(String eventId, Hashtable<String, String> paramMap) {
		LogD("logEvent(" + eventId + "," + paramMap.toString() + ") invoked!");
		int eventCount = Integer.parseInt(paramMap.get("Param1"));
		float eventSum = Float.parseFloat(paramMap.get("Param2"));
		Countly.sharedInstance().recordEvent(eventId, eventCount, eventSum);
	}

	@Override
	public void logTimedEventBegin(String eventId) {
		LogD("logTimedEventBegin(" + eventId + ") is not in Countly!");
	}

	@Override
	public void logTimedEventEnd(String eventId) {
		LogD("logTimedEventEnd(" + eventId + ") is not in Countly!");
	}

	@Override
	public String getSDKVersion() {
		LogD("getSDKVersion invoked!");
		return Countly.COUNTLY_SDK_VERSION_STRING;
	}

	@Override
	public String getPluginVersion() {
		return "0.1.0";
	}

	public void startSessionWithParams(JSONObject eventInfo) {
		try {
			String appKey = eventInfo.getString("Param1");
			String serverUrl = eventInfo.getString("Param2");
			Countly.sharedInstance().init(mContext, serverUrl, appKey, null,
					DeviceId.Type.OPEN_UDID);
			Countly.sharedInstance().onStart();
		} catch (Exception e) {
			LogE("Exception in logEventWithDurationParams", e);
		}
	}

	public void logEventWithParams(JSONObject eventInfo) {
		LogD("startSessionWithParams invoked! event : " + eventInfo.toString());
		if (!isValid())
			return;
		try {
			String eventId = eventInfo.getString("Param1");
			int eventCount = eventInfo.getInt("Param3");
			float eventSum = eventInfo.getInt("Param4");
			if (eventInfo.has("Param2")) {
				JSONObject params = eventInfo.getJSONObject("Param2");
				HashMap<String, String> segmentation = getMapFromJson(params);
				Countly.sharedInstance().recordEvent(eventId, segmentation,
						eventCount, eventSum);
			} else {
				Countly.sharedInstance().recordEvent(eventId, eventCount,
						eventSum);
			}
		} catch (Exception e) {
			LogE("Exception in logEventWithDurationParams", e);
		}

	}

	private HashMap<String, String> changeTableToMap(
			Hashtable<String, String> param) {
		HashMap<String, String> retParam = new HashMap<String, String>();
		for (Iterator<String> it = param.keySet().iterator(); it.hasNext();) {
			String key = it.next();
			String value = param.get(key);

			retParam.put(key, value);
		}

		return retParam;
	}

	private HashMap<String, String> getMapFromJson(JSONObject json) {
		HashMap<String, String> curMap = new HashMap<String, String>();
		try {
			@SuppressWarnings("rawtypes")
			Iterator it = json.keys();
			while (it.hasNext()) {
				String key = (String) it.next();
				String value = json.getString(key);
				curMap.put(key, value);
			}
		} catch (Exception e) {
			LogE("Error when get HashMap from JSONObject", e);
		}

		return curMap;
	}

}
