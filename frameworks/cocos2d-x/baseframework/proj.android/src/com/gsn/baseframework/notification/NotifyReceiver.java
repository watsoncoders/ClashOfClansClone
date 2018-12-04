package com.gsn.baseframework.notification;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.PowerManager;
public class NotifyReceiver extends BroadcastReceiver{
	
	@Override
	public void onReceive(Context ctx, Intent arg1) {
	
			PowerManager pm = (PowerManager) ctx.getSystemService(Context.POWER_SERVICE);
			PowerManager.WakeLock wl = pm.newWakeLock( PowerManager.PARTIAL_WAKE_LOCK, "NotifyReceiver");
			wl.acquire(30000);
			Intent i = new Intent(ctx, NotifyService.class);
			i.setAction(NotifyService.ACTION_SHOW_NOTIFICATION);
			ctx.startService(i);
	}
}
