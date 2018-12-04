package com.gsn.baseframework.notification;

import java.io.BufferedReader;
import java.util.Calendar;

import android.database.Cursor;
import android.media.RingtoneManager;

public class NotifyItem extends SimplePropertyCollection {
	public NotifyItem() {
		super(ITEM_DEFAULT);
	}
	public NotifyItem(BufferedReader reader, boolean skipId) throws Exception {
		super(ITEM_DEFAULT, reader, skipId, KEY_ROWID);
//		LiteHelper.setProFeatures(this);
	}
	public NotifyItem(SimpleProperty[] defaults, Cursor cur) {
		super(defaults, cur);
//		LiteHelper.setProFeatures(this);
	}
	public NotifyItem(SimpleProperty[] defaults) {
		super(defaults);
		// TODO Auto-generated constructor stub
	}
	public NotifyItem(Cursor cur) {
		super(ITEM_DEFAULT, cur);
//		LiteHelper.setProFeatures(this);
	}
	public static final String KEY_ROWID = "_id";
	public static final String KEY_CONTENT_TEXT = "_text";
	public static final String KEY_TIME = "_time";
	public static final String KEY_CONTENT_TITLE = "_title";
	public static final String KEY_CONTENT_INFO = "_info";
	public static final String KEY_SUB_TEXT = "_subText";
	public static final String KEY_SMALL_ICON = "_smallIcon";
	public static final String KEY_SOUND = "_sound";
	public static final String KEY_USE_VIBRATION = "_useVibration";
	public static final String KEY_TICKER = "_ticker";
	
	public static final SimpleProperty[] ITEM_DEFAULT = new SimpleProperty[] {
		new SimpleProperty(KEY_ROWID, 0),
		new SimpleProperty(KEY_CONTENT_TEXT, ""),
		new SimpleProperty(KEY_TIME, (long)12),
		new SimpleProperty(KEY_CONTENT_TITLE, ""),
		new SimpleProperty(KEY_CONTENT_INFO, ""),
		new SimpleProperty(KEY_SUB_TEXT, ""),
		new SimpleProperty(KEY_SMALL_ICON, 0),
		new SimpleProperty(KEY_SOUND, ""),
		new SimpleProperty(KEY_USE_VIBRATION, false),
		new SimpleProperty(KEY_TICKER, ""),
		
	};
	
	public String getTicker(){
		return getString(KEY_TICKER);
	}
	
	public String getContentText() {
		return getString(KEY_CONTENT_TEXT);
	}
	public String getSubText(){
		return getString(KEY_SUB_TEXT);
	}
	public String getContentInfo()
	{
		return getString(KEY_CONTENT_INFO);
	}
	public String getContentTitle()
	{
		return getString(KEY_CONTENT_TITLE);
	}
	public int getSmallIcon()
	{
		return getInt(KEY_SMALL_ICON);
	}
	public long getTime()
	{
		return getLong(KEY_TIME);
	}
	public String getSound()
	{
		return getString(KEY_SOUND);
	}
	public boolean isUseVibration()
	{
		return getBool(KEY_USE_VIBRATION);
	}
	public Calendar getTimeCalendar() {
		Calendar aCal = Calendar.getInstance();
		aCal.setTimeInMillis(getTime());
		return aCal;
	}

	public String getTimeString() {
//		String rStr = "";
		Calendar c = getTimeCalendar();
		return c.getTime().toString();
	}
}
