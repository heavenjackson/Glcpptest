package com.htss.glcpptest;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class NativeRenderer implements GLSurfaceView.Renderer {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    private Context mActivityContext;
    public NativeRenderer(Context activityContext) {
        mActivityContext = activityContext;
    }
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        nativeSurfaceCreate();
        setNativeAssetManager(mActivityContext.getAssets());
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        nativeSurfaceChange(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        nativeDrawFrame();
    }
    public static native void nativeSurfaceCreate();
    public static native void nativeSurfaceChange(int width, int height);
    public static native void nativeDrawFrame();
    public static native void setNativeAssetManager(AssetManager assetManager);
}
