package com.gsn.baseframework.notification;

import android.app.AlarmManager;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

public class NotifyAdapter {
public static final String TABLE_NAME_ALARMS = "alarms";
	
	public static final String DATABASE_NAME = "dbE6AlarmAppChooser";
	public static final int DATABASE_VERSION = 12;
	public static final String[] DATABASE_DROP = {
		"DROP TABLE IF EXISTS " + TABLE_NAME_ALARMS
	};
	
	
	private final Context mCtx;
	
	private static final String TAG = "AalDbAdapter";
    private DatabaseHelper mDbHelper;
    private SQLiteDatabase mDb;

    private static class DatabaseHelper extends SQLiteOpenHelper {
        DatabaseHelper(Context context) {
            super(context, DATABASE_NAME, null, DATABASE_VERSION);
        }

        @Override
        public void onCreate(SQLiteDatabase db) {
        	db.execSQL(SimplePropertyCollection.getCreateTableStatement(NotifyItem.ITEM_DEFAULT, TABLE_NAME_ALARMS));
        }

        @Override
        public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
            Log.w(TAG, "Upgrading database from version " + oldVersion + " to "
                    + newVersion + ", which will destroy all old data");
            for (int i = 0; i < DATABASE_DROP.length; i++) {
        		db.execSQL(DATABASE_DROP[i]);
        	}
            onCreate(db);
        }
    }

    public NotifyAdapter(Context ctx) {
    	this.mCtx = ctx;
    }
    
    public NotifyAdapter open() {
        mDbHelper = new DatabaseHelper(mCtx);
        mDb = mDbHelper.getWritableDatabase();
        return this;
    }
    
    public void close() {
        mDbHelper.close();
    }
    
    public Cursor fetchAllNotifications() {
    	return mDb.query(TABLE_NAME_ALARMS, SimplePropertyCollection.getKeyArray(NotifyItem.ITEM_DEFAULT), null, null, null, null, NotifyItem.KEY_ROWID);
    }
    
    public NotifyItem getAlarmById(long id) {
    	if (id == 0) {
    		return new NotifyItem();
    	} 
    	
    	Cursor cur = mDb.query(TABLE_NAME_ALARMS, SimplePropertyCollection.getKeyArray(NotifyItem.ITEM_DEFAULT), NotifyItem.KEY_ROWID+"="+id, null, null, null, NotifyItem.KEY_ROWID);
    	
    	if (cur == null) {
    		return new NotifyItem();
    	}
    	
		cur.moveToFirst();
		if (cur.isAfterLast()) {
			cur.close();
			return new NotifyItem();
		} else {
			NotifyItem ai = new NotifyItem(cur);
			cur.close();
			return ai;
		}
    }
    
    public NotifyItem getNewAlarm() {
    	return new NotifyItem();
    }
    
    public void saveNotification(NotifyItem ai) {
    	ai.saveItem(mDb, TABLE_NAME_ALARMS, NotifyItem.KEY_ROWID);
    }
    
  
    public void deleteNotification(long alarm_id) {
    	mDb.delete(TABLE_NAME_ALARMS, NotifyItem.KEY_ROWID+"="+alarm_id, null);
    }   
    public void deleteAllNotification() {
    	//mDb.delete(TABLE_NAME_ALARMS, null, null);
    	Cursor c = fetchAllNotifications();
    	if (c != null) {
    		c.moveToFirst();
    		if (!c.isAfterLast()) {
    			NotifyItem ai = null;
    			while(!c.isAfterLast()) {
    				ai = new NotifyItem(NotifyItem.ITEM_DEFAULT, c);
    				deleteNotification( ai.getInt(NotifyItem.KEY_ROWID));
    				c.moveToNext();
    			}
    		} 
    		c.close();
    	}
    }
}
