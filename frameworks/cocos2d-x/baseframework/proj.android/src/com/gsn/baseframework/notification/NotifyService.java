package com.gsn.baseframework.notification;

import com.gsn.baseframework.FrameworkActivity;
import android.annotation.SuppressLint;
import android.app.AlarmManager;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.media.RingtoneManager;
import android.net.Uri;
import android.os.Handler;
import android.os.IBinder;
import android.support.v4.app.NotificationCompat;
import android.support.v4.app.NotificationCompat.Builder;
import android.util.Log;

public class NotifyService extends Service {

	public static final String ACTION_CHANGE_NOTIFICATION = "change_notification";
	public static final String ACTION_SHOW_NOTIFICATION = "show_notification";
	public static final String ACTION_STOP_NOTIFICATION = "stop_notification";

	public static final String PREF_FILE_NAME = "NotificationsPrefs";
	private static final String PREF_KEY_NEXT_NOTIFICATION_ID = "next_notification_id";

	private NotificationManager mNotificationManager;

	private NotifyItem mCurrentNotification;
	private NotifyAdapter mDbAdapter;

	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void onCreate() {
		super.onCreate();

		mNotificationManager = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
		try {
			mDbAdapter = new NotifyAdapter(this);
			mDbAdapter.open();
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	@Override
	public void onDestroy() {
		Log.i("Notify", "NotifyService:onDestroy");
		// setNextNotification();
		try {
			mDbAdapter.close();
		} catch (Exception e) {
		}
		super.onDestroy();
	}

	// @SuppressLint("OldApi")
	// @Override
	// public void onStart(Intent intent, int startId) {
	// Log.i("NotifyService", "onStart");
	// super.onStart(intent, startId);
	// doAction(intent);
	// }
	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		Log.i("Notify:", "NotifyService:onStartCommand");
		doAction(intent);
		return super.onStartCommand(intent, flags, startId);
	}

	private void doAction(Intent intent) {
		if (intent == null)
			return;
		String action = intent.getAction();
		Log.i("Notify", "doAction:" + action);
		if (action.equals(ACTION_CHANGE_NOTIFICATION)) {
			setNextNotification();
		} else if (action.equals(ACTION_SHOW_NOTIFICATION)) {
			showNotification();
		} else if (action.equals(ACTION_STOP_NOTIFICATION)) {
			stopSelf();
			mNotificationManager.cancelAll();
			try {
				PendingIntent sender = PendingIntent.getBroadcast(this, 0, new Intent(this, FrameworkActivity.class),
						0);
				AlarmManager alarmManager = (AlarmManager) getSystemService(ALARM_SERVICE);
				alarmManager.cancel(sender);
			} catch (Exception e) {
				// TODO: handle exception
				e.printStackTrace();
			}
		}

	}

	private synchronized void showNotification() {
		try {
			long alarmId = loadNextAlarmPref();
			Log.i("Notify", "showNotification alarmId: " + alarmId);
			if (alarmId != 0) {
				mCurrentNotification = mDbAdapter.getAlarmById(alarmId);
				if (mCurrentNotification != null) {
					Log.i("Notify",
							"showNotification alarmId: " + alarmId + ", " + mCurrentNotification.getContentText());
			
					String packageName = this.getPackageName();
					Intent launchIntent = this.getPackageManager().getLaunchIntentForPackage(packageName);
					String className = launchIntent.getComponent().getClassName();
					Log.i("Notify","className: " + className);
					Class<?> mainClass = Class.forName(className);
					
					Intent notificationIntent = new Intent(this, mainClass);
					notificationIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP);
					PendingIntent intent = PendingIntent.getActivity(this, 0, notificationIntent, 0);

					NotificationCompat.Builder builder = new NotificationCompat.Builder(this.getApplicationContext());
					Builder notif = builder.setContentIntent(intent);
					notif.setSmallIcon(mCurrentNotification.getSmallIcon()).setTicker(mCurrentNotification.getTicker())
							.setWhen(mCurrentNotification.getTime())
							.setStyle(new NotificationCompat.BigTextStyle().bigText(mCurrentNotification.getContentText()))
							.setContentText(mCurrentNotification.getContentText())
							.setContentTitle(mCurrentNotification.getContentTitle())
							.setContentInfo(mCurrentNotification.getContentInfo())
							.setSubText(mCurrentNotification.getSubText());

					String soundUrl = mCurrentNotification.getSound();
					if (soundUrl != null && (!soundUrl.equalsIgnoreCase(""))) {
						if (soundUrl.equalsIgnoreCase("default")) {
							Uri soundUri = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION);
							notif.setSound(soundUri);
						} else {
							Uri soundUri = Uri.parse(mCurrentNotification.getSound());
							notif.setSound(soundUri);
						}
					}

					if (mCurrentNotification.isUseVibration()) {

					}
					mNotificationManager.notify((int) alarmId, notif.build());
					mDbAdapter.deleteNotification(alarmId);
				}
			}
			setNextNotification();
		} catch (Exception e) {
			e.printStackTrace();
			// TODO: handle exception
		}
	}

	private void setNextNotification() {
		try {
			PendingIntent sender = PendingIntent.getBroadcast(this, 0, new Intent(this, NotifyReceiver.class), 0);
			AlarmManager alarmManager = (AlarmManager) getSystemService(ALARM_SERVICE);
			alarmManager.cancel(sender);
			Cursor c = mDbAdapter.fetchAllNotifications();
			if (c != null) {
				try {
					c.moveToFirst();
				} catch (Exception e) {
					// TODO: handle exception
					c.close();
					return;
				}

				if (!c.isAfterLast()) {
					long nextAlarmTimeInMilis = 0;
					long nextAlarmId = 0;

					NotifyItem ai = null;
					while (!c.isAfterLast()) {
						ai = new NotifyItem(NotifyItem.ITEM_DEFAULT, c);
						Log.i("Notify", "setNextNotification time: " + ai.getTimeString());
						if (nextAlarmTimeInMilis == 0) {
							nextAlarmTimeInMilis = ai.getTime();
							nextAlarmId = ai.getInt(NotifyItem.KEY_ROWID);
						} else {
							long atim = ai.getTime();
							if (atim > 0 && atim < nextAlarmTimeInMilis) {
								nextAlarmTimeInMilis = atim;
								nextAlarmId = ai.getInt(NotifyItem.KEY_ROWID);
							}
						}
						c.moveToNext();
					}
					saveNextNotificationPref(nextAlarmId);
					Log.i("Notify", "setNextNotification ID: " + nextAlarmId + "," + nextAlarmTimeInMilis);
					if (nextAlarmId != 0) {

						alarmManager.set(AlarmManager.RTC_WAKEUP, nextAlarmTimeInMilis, sender);
					}
				}
				c.close();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	private void saveNextNotificationPref(long alarmId) {
		saveNextNotificationPref(getBaseContext(), alarmId);
	}

	public static void saveNextNotificationPref(Context c, long alarmId) {
		SharedPreferences.Editor spe = c.getSharedPreferences(PREF_FILE_NAME, MODE_PRIVATE).edit();
		spe.putLong(PREF_KEY_NEXT_NOTIFICATION_ID, alarmId);
		spe.commit();
	}

	private long loadNextAlarmPref() {
		SharedPreferences sp = getSharedPreferences(PREF_FILE_NAME, MODE_PRIVATE);
		return sp.getLong(PREF_KEY_NEXT_NOTIFICATION_ID, 0);
	}
}
