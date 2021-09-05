#include <jni.h>
#include <string>
#include <android/log.h>
#include "MySqure.h"
#include "MyTexture.h"
#include "TextureMatrix.h"

#define LOG_TAG "gles_test"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static GraphicsInterface *graphicInstance;

extern "C"
JNIEXPORT void JNICALL
Java_com_htss_glcpptest_NativeRenderer_nativeSurfaceCreate(JNIEnv *env, jclass clazz) {
    if (graphicInstance) {
        delete graphicInstance;
        graphicInstance = NULL;
    }
    //graphicInstance = new MySqure();
    //graphicInstance = new MyTexture();
    graphicInstance = new TextureMatrix();
    if (graphicInstance) {
        graphicInstance->create();
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_htss_glcpptest_NativeRenderer_nativeSurfaceChange(JNIEnv *env, jclass clazz, jint width,
                                                           jint height) {
    if (graphicInstance) {
        graphicInstance->change(width, height);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_htss_glcpptest_NativeRenderer_nativeDrawFrame(JNIEnv *env, jclass clazz) {
    if (graphicInstance) {
        graphicInstance->draw();
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_htss_glcpptest_NativeRenderer_setNativeAssetManager(JNIEnv *env, jclass clazz,
                                                             jobject asset_manager) {
    AAssetManager* aAssetManager = AAssetManager_fromJava(env, asset_manager);
    if (graphicInstance) {
        graphicInstance->setAssetAndGeneratePixels(aAssetManager);
    }
}