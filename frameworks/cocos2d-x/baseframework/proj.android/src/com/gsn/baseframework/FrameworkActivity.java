package com.gsn.baseframework;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.plugin.FacebookWrapper;
import org.cocos2dx.plugin.GoogleWrapper;
import org.cocos2dx.plugin.PluginWrapper;
import org.cocos2dx.plugin.ZaloWrapper;


import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;

public class FrameworkActivity extends Cocos2dxActivity {
    static String hostIPAdress = "0.0.0.0";
	@Override
	protected void onCreate(final Bundle savedInstanceState) {
	        super.onCreate(savedInstanceState);
	        
	        //google
	        	GoogleWrapper.onSaveInstanceState(savedInstanceState);
	        //debug
	        if(nativeIsLandScape()) {
	            setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_LANDSCAPE);
	        } else {
	            setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_PORTRAIT);
	        }
	        if(nativeIsDebug()){
	            getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
	        }
	        hostIPAdress = getHostIpAddress();
	}
	@Override
	public final Cocos2dxGLSurfaceView onCreateView(){
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
		glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
		//plugin
        PluginWrapper.init(this);
        PluginWrapper.setGLSurfaceView(glSurfaceView);
        FacebookWrapper.onCreate(this);
        ZaloWrapper.onCreate(this);
        return glSurfaceView;
	}
	@Override
	public void onResume()
	{
		super.onResume();
		//plugin
		PluginWrapper.onResume();
		//FacebookWrapper.onResume(this);
		ZaloWrapper.onResume(this);
	}
	@Override
	public void onPause()
	{
		super.onPause();
		//plugin
		PluginWrapper.onPause();
		//FacebookWrapper.onPause(this);
	}
	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data){
		
		Log.d("User","mOnActivityResult: " +  requestCode + ", " + resultCode);
		FacebookWrapper.onAcitivityResult(requestCode, resultCode, data);
		//plugin
		PluginWrapper.onActivityResult(requestCode, resultCode, data);
		
		super.onActivityResult(requestCode, resultCode, data);
		
	}
	@Override
	public void onSaveInstanceState(Bundle outState)
	{
		super.onSaveInstanceState(outState);
		//plugin
		FacebookWrapper.onSaveInstanceState(outState);
		GoogleWrapper.onSaveInstanceState(outState);
	}
	 public String getHostIpAddress() {
	        WifiManager wifiMgr = (WifiManager) getSystemService(WIFI_SERVICE);
	        WifiInfo wifiInfo = wifiMgr.getConnectionInfo();
	        int ip = wifiInfo.getIpAddress();
	        return ((ip & 0xFF) + "." + ((ip >>>= 8) & 0xFF) + "." + ((ip >>>= 8) & 0xFF) + "." + ((ip >>>= 8) & 0xFF));
	    }
	    
	    public static String getLocalIpAddress() {
	        return hostIPAdress;
	    }
	private static native boolean nativeIsLandScape();
	private static native boolean nativeIsDebug();
}
