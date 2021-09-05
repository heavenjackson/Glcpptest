package com.htss.glcpptest;

import androidx.appcompat.app.AppCompatActivity;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private GLSurfaceView mGLSurfaceView;
    private final String mTag = "gles_test";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mGLSurfaceView = new GLSurfaceView(this);
        // Check if the system supports OpenGL ES 3.0.
        final ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        final ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();
        Log.d(mTag, "gles supported version:" + configurationInfo.reqGlEsVersion);
        final boolean supportsEs2 = configurationInfo.reqGlEsVersion >= 0x30000;
        if (supportsEs2) {
            mGLSurfaceView.setEGLContextClientVersion(3);
            mGLSurfaceView.setRenderer(new NativeRenderer(this));
        } else {
            return;
        }
        setContentView(mGLSurfaceView);
    }

    @Override
    protected void onResume() {
        super.onResume();
        mGLSurfaceView.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        mGLSurfaceView.onPause();
    }
}