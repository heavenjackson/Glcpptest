//
// Created by lht on 2021/8/22.
//

#ifndef GLCPPTEST_MYTEXTURE_H
#define GLCPPTEST_MYTEXTURE_H

#include <jni.h>
#include <android/log.h>
#include "GLUtils.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <GLES3/gl3.h>
#include "GraphicsInterface.h"
#include <android/imagedecoder.h>
#include <android/bitmap.h>

class MyTexture : public GraphicsInterface{
public:
    MyTexture();
    virtual ~MyTexture();
    virtual void create() override;
    virtual void change(int width, int height) override;
    virtual void draw() override;
    virtual void setAssetAndGeneratePixels(AAssetManager* aAssetManager) override;
private:
    void loadtexture();
    void prepareBuffer();
    GLuint mVertexBuffer;
    GLuint mElementBuffer;
    GLuint mVertexArray;
    GLuint mProgram;
    GLuint mPositionHandle;
    GLuint mTextureCoordinateHandle;
    GLuint mTextureHandle;
    GLuint mTextureUniformHandle;
    int32_t mWidth;
    int32_t mHeight;
    AAssetManager* mAAssetManager;
    void* mPixels;
};


#endif //GLCPPTEST_MYTEXTURE_H
