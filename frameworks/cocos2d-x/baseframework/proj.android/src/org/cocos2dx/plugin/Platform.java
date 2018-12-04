package org.cocos2dx.plugin;


import java.io.File;
import java.util.regex.Pattern;

import org.json.JSONObject;

import com.gsn.baseframework.notification.NotifyAdapter;
import com.gsn.baseframework.notification.NotifyItem;
import com.gsn.baseframework.notification.NotifyService;

import android.accounts.Account;
import android.accounts.AccountManager;
import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.app.Activity;
import android.app.ActivityManager;
import android.app.ActivityManager.MemoryInfo;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Build;
import android.os.Environment;
import android.os.StatFs;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.util.Patterns;

public class Platform {
	public static final String PREF_FILE_NAME = "PlatformPrefs";
	private static final String PREF_KEY_TYPE_OF_FOLDER_ASSETS_ID = "type_folder_assets_id";
	private static final int TYPE_FOLDER_ASSETS_NONE = -1;
	private static final int TYPE_FOLDER_ASSETS_INTERNAL = 0;
	private static final int TYPE_FOLDER_ASSETS_EXTERNAL = 1;
	
    static final String TAG = "Platform";

    static boolean bDebug = false;
    Context mContext;
    
    private String imei = "";
    private String phoneNumber = "";
    private String mailAccount = "";
    private String externalDataPath = "";
    private NotifyAdapter mDbAdapter = null;
    public final int PluginType = 5;//can de ben c++ khoi tao class
    private int typeOfFolderAssets = TYPE_FOLDER_ASSETS_NONE;
    
    protected static void LogE(String msg, Exception e) {
        Log.e(TAG, msg, e);
        e.printStackTrace();
    }

    protected static void LogD(String msg) {
        if (bDebug) {
            Log.d(TAG, msg);
        }
    }

	public Platform(Context context) {
        mContext = context;
        // DeviceInfo
     	TelephonyManager telephonyManager = (TelephonyManager)context.getSystemService(Context.TELEPHONY_SERVICE);
     	// imei
     	imei = telephonyManager.getDeviceId();
     	// Phone number
     	phoneNumber = telephonyManager.getLine1Number();
     	// Mail Account
     	mailAccount = "";
     	Pattern emailPattern = Patterns.EMAIL_ADDRESS; // API level 8+
     	Account[] accounts = AccountManager.get(context).getAccounts();
     	for (Account account : accounts) {
     		if (emailPattern.matcher(account.name).matches()) {
     		mailAccount = account.name;
     		    break;
     		}
     	}
     		// External Data Path
     	File sdCard =  Environment.getExternalStorageDirectory();
     	File dir = new File(sdCard.getAbsolutePath() + "/Android");
     	if(!dir.exists())
     		dir.mkdirs();
     	externalDataPath = dir.getAbsolutePath();
        //notify
     	if (mDbAdapter == null) {
			mDbAdapter = new NotifyAdapter(mContext);
			mDbAdapter.open();
		}
     
     	initFolderDownloadAssets();
    }
	
	private void initFolderDownloadAssets()
	{
		//assets
     	SharedPreferences sp = mContext.getSharedPreferences(PREF_FILE_NAME, Context.MODE_PRIVATE);
		int folderType =  sp.getInt(PREF_KEY_TYPE_OF_FOLDER_ASSETS_ID, TYPE_FOLDER_ASSETS_NONE);
		//chose folder to download assets internal or external
		if(folderType == TYPE_FOLDER_ASSETS_NONE)
		{
			long freeExternalSize = getAvailableExternalMemorySize();
			long freeInternalSize = getAvailableInternalMemorySize();
			
			if(freeInternalSize > freeExternalSize)
			{
				folderType = TYPE_FOLDER_ASSETS_INTERNAL;
			}else
			{
				folderType = TYPE_FOLDER_ASSETS_EXTERNAL;
			}
			
			Log.i("Platform","freeExternalSize: " + freeExternalSize + ", freeInternalSize: " + freeInternalSize + ", folderType: " + folderType);
			
			SharedPreferences.Editor spe = mContext.getSharedPreferences(PREF_FILE_NAME, Context.MODE_PRIVATE).edit();
			spe.putInt(PREF_KEY_TYPE_OF_FOLDER_ASSETS_ID, folderType);
			spe.commit();
		}
		typeOfFolderAssets = folderType;
	}
    private Context getContext() {
        return mContext;
    }

    private Activity getActivity() {
        return (Activity) mContext;
    }
    
    public String getPluginVersion() {
        return "0.1.0";
    }
    //IMEI
    public String getIMEI()
	{
		return imei;
	}
    //Phone Number
	public String getPhoneNumber()
	{
		return phoneNumber;
	}
	//Mail
	public String getMailAccount()
	{
		return mailAccount;
	}
	//external
	public String getExternalDataPath()
	{
	    return externalDataPath; 
	}
	//DeviceName
	public String getDeviceModel()
	{
	    return android.os.Build.MODEL;
	}
	//free ram, tinh theo MB
	public int getAvailableRAM()
	{
	    ActivityManager activityManager = (ActivityManager) getActivity().getSystemService(Activity.ACTIVITY_SERVICE);
	    MemoryInfo memoryInfo = new ActivityManager.MemoryInfo();
	    activityManager.getMemoryInfo(memoryInfo);
	    return (int)(memoryInfo.availMem/(1024*1024));
	}
	//Version code
	public int getVersionCode()
	{
	    PackageInfo pInfo;
	    try {
		pInfo = getActivity().getPackageManager().getPackageInfo(getActivity().getPackageName(), 0);
		int versionNumber = pInfo.versionCode;
		return versionNumber;
	    } catch (NameNotFoundException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	    }
	    return 0;
	}
	//OS version
	public String getOSVersion()
	{
	    return android.os.Build.VERSION.RELEASE;
	}
	//connection type 0: ko co mang, 1: 3g, 2: wifi
	public int getConnectionStatus()
	{
		ConnectivityManager manager = (ConnectivityManager) getActivity().getSystemService(Activity.CONNECTIVITY_SERVICE);
		boolean is3g =false;
		boolean isWifi = false;
		NetworkInfo mobileNetWorkInfo = manager.getNetworkInfo(ConnectivityManager.TYPE_MOBILE);
		if( mobileNetWorkInfo!= null)
		{
			is3g = mobileNetWorkInfo.isConnectedOrConnecting();
		}
		
		NetworkInfo wifiNetWorkInfo = manager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
		if( wifiNetWorkInfo!= null)
		{
			isWifi = wifiNetWorkInfo.isConnectedOrConnecting();
		}
		if(is3g)
		{
			return 1;
		}else if (isWifi)
		{
			return 2;
		}
		return 0;
	}
	
	@TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR2)
	public long getAvailableInternalMemorySize()
	{
		File path = Environment.getDataDirectory();
		StatFs stat = new StatFs(path.getPath());
		if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR2)
		{
			long blockSize = stat.getBlockSizeLong();
			long availableBlocks = stat.getAvailableBlocksLong();
			return availableBlocks* blockSize;
		}else
		{
			long blockSize = stat.getBlockSize();
			long availableBlocks = stat.getAvailableBlocks();
			return availableBlocks* blockSize;
		}
		
	}
	@TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR2)
	public long getAvailableExternalMemorySize()
	{
		if(externalMemoryAvailable()){
			File path = Environment.getExternalStorageDirectory();
			StatFs stat = new StatFs(path.getPath());
			if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR2)
			{
				long blockSize = stat.getBlockSizeLong();
				long availableBlocks = stat.getAvailableBlocksLong();
				return availableBlocks*blockSize;
			}else
			{
				long blockSize = stat.getBlockSize();
				long availableBlocks = stat.getAvailableBlocks();
				return availableBlocks*blockSize;
			}
		}else{
			return -1;
		}
	}
	public boolean externalMemoryAvailable()
	{
		return android.os.Environment.getExternalStorageState().equals(android.os.Environment.MEDIA_MOUNTED);
	}
	
	public String getFolderUpdateAssets(String folderName)
	{
		if(typeOfFolderAssets == TYPE_FOLDER_ASSETS_EXTERNAL)
		{
			File sdCard =  Environment.getExternalStorageDirectory();
	     	File dir = new File(sdCard.getAbsolutePath() + "/" + folderName);
	     	if(!dir.exists())
	     		dir.mkdirs();
	     	return dir.getAbsolutePath();
		}
		if(typeOfFolderAssets == TYPE_FOLDER_ASSETS_INTERNAL)
		{
	     	File dir = new File(mContext.getFilesDir().getAbsolutePath() + "/" + folderName);
	     	if(!dir.exists())
	     		dir.mkdirs();
	     	return dir.getAbsolutePath();
		}
		return "";
	}
	public long getAvailableUpdateAssetMemorySize()
	{
		if(typeOfFolderAssets == TYPE_FOLDER_ASSETS_NONE)
		{
			return -1;
		}else if(typeOfFolderAssets == TYPE_FOLDER_ASSETS_INTERNAL)
		{
			return getAvailableInternalMemorySize();
		}else
		{
			return getAvailableExternalMemorySize();
		}
	}
	public void addNotify( String data) {

		Log.i("addNotify", data);
			
		try {
			JSONObject  notifyData = new JSONObject(data);
			String contentText = notifyData.getString("contentText");
			long time = notifyData.getLong("time");
			//icon
			PackageManager pm = mContext.getPackageManager();
			ApplicationInfo ai = pm.getApplicationInfo(getContext().getPackageName(), 0);
			//app name
			String appName = (String)pm.getApplicationLabel(ai);
			
			NotifyItem item = mDbAdapter.getNewAlarm();
			item.set(NotifyItem.KEY_CONTENT_TEXT, contentText);
			item.set(NotifyItem.KEY_TIME, time);
			item.set(NotifyItem.KEY_SMALL_ICON, ai.icon);
			if(notifyData.has("sound"))
			{
				item.set(NotifyItem.KEY_SOUND, notifyData.getString("sound"));
			}
			if(notifyData.has("contentTitle"))
			{
				item.set(NotifyItem.KEY_CONTENT_TITLE, notifyData.getString("contentTitle"));
			}
			else
			{
				item.set(NotifyItem.KEY_CONTENT_TITLE, appName);
			}
			if(notifyData.has("contentInfo"))
			{
				item.set(NotifyItem.KEY_CONTENT_INFO, notifyData.getString("contentInfo"));
			}
			if(notifyData.has("subText"))
			{
				item.set(NotifyItem.KEY_SUB_TEXT, notifyData.getString("subText"));
			}
			if(notifyData.has("useVibration"))
			{
				item.set(NotifyItem.KEY_USE_VIBRATION, notifyData.getBoolean("useVibration"));
			}

			mDbAdapter.saveNotification(item);
		} catch (Exception e) {
			e.printStackTrace();
		}

	}
	
	public void showNotify() {
		Intent i = new Intent(getContext(), NotifyService.class);
		i.setAction(NotifyService.ACTION_CHANGE_NOTIFICATION);
		mContext.startService(i);
	}

	public void cancelAllNotification() {
		try {
			Log.i("cancelAllNotification", "cancelAllNotification");
			mDbAdapter.deleteAllNotification();
			Intent i = new Intent(mContext, NotifyService.class);
			i.setAction(NotifyService.ACTION_STOP_NOTIFICATION);
			mContext.startService(i);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
}
