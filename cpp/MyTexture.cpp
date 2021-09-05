//
// Created by lht on 2021/8/22.
//

#include <cstdlib>
#include "MyTexture.h"

#define LOG_TAG "gles_test"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

namespace {
const char* vertexShaderSource = R"(
attribute vec3 a_Position;
attribute vec2 a_TexCoordinate;
varying vec2 v_TexCoordinate;
void main()
{
    gl_Position = vec4(a_Position, 1.0);
    v_TexCoordinate = a_TexCoordinate;
}
)";

const char* fragmentShaderSource = R"(
precision mediump float;
uniform sampler2D u_Texture;
varying vec2 v_TexCoordinate;
void main()
{
    gl_FragColor = texture2D(u_Texture, v_TexCoordinate);
}
)";

#if 0
const GLfloat vertices[] = {
        // positions
        0.5f, 0.5f, 0.0f,  //top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f,  // top left
};
#else
const GLfloat vertices[] = {
        // positions       //texture coordinate
        0.5f, 0.5f, 0.0f,  1.0f,  1.0f, //top right
        0.5f, -0.5f, 0.0f,  1.0f,  0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f,  0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f,  1.0f  // top left
};
#endif
const GLfloat textureCoords[] = {
        0.0f,  1.0f,   // top left
        0.0f,  0.0f,   // bottom left
        1.0f,  0.0f,   // bottom right
        1.0f,  1.0f    // top right
};

const GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
};

}

MyTexture::MyTexture() {

}
MyTexture::~MyTexture() {
    if (mPixels) {
        free(mPixels);
    }
    glDeleteVertexArrays(1, &mVertexArray);
    glDeleteBuffers(1, &mVertexBuffer);
    glDeleteBuffers(1, &mElementBuffer);
}

void MyTexture::create() {
    mProgram = GLUtils::createProgram(&vertexShaderSource, &fragmentShaderSource);
    prepareBuffer();
}
void MyTexture::prepareBuffer() {
    glGenVertexArrays(1, &mVertexArray);
    glGenBuffers(1, &mVertexBuffer);
    glGenBuffers(1, &mElementBuffer);
    glBindVertexArray(mVertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    mPositionHandle = glGetAttribLocation(mProgram, "a_Position");
    glVertexAttribPointer(mPositionHandle, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(mPositionHandle);

    mTextureCoordinateHandle = glGetAttribLocation(mProgram, "a_TexCoordinate");
    glVertexAttribPointer(mTextureCoordinateHandle, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(mTextureCoordinateHandle);

    loadtexture();

    glUseProgram(mProgram);
    mTextureUniformHandle = glGetUniformLocation(mProgram, "u_Texture");
    glUniform1i(mTextureUniformHandle, 0);
}
void MyTexture::change(int width, int height) {
    LOGD("change.");
    glViewport(0, 0, width, height);
}
#if 1
void MyTexture::draw() {
    LOGD("draw");
    glClearColor(0.5F, 0.5F, 0.5F, 0.5F);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(mProgram);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mPixels);

    //glBindVertexArray(mVertexArray);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
#else
void MyTexture::draw() {
    LOGD("draw");
    glClearColor(0.5F, 0.5F, 0.5F, 0.5F);
    glClear(GL_COLOR_BUFFER_BIT);

    mPositionHandle = glGetAttribLocation(mProgram, "a_Position");
    glVertexAttribPointer(mPositionHandle, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), vertices);
    glEnableVertexAttribArray(mPositionHandle);

    mTextureCoordinateHandle = glGetAttribLocation(mProgram, "a_TexCoordinate");
    glVertexAttribPointer(mTextureCoordinateHandle, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), textureCoords);
    glEnableVertexAttribArray(mTextureCoordinateHandle);

    loadtexture();

    glUseProgram(mProgram);
    mTextureUniformHandle = glGetUniformLocation(mProgram, "u_Texture");
    glUniform1i(mTextureUniformHandle, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureHandle);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
}
#endif
void MyTexture::loadtexture(){
    glGenTextures(1, &mTextureHandle);
    glBindTexture(GL_TEXTURE_2D, mTextureHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mPixels);
}
void MyTexture::setAssetAndGeneratePixels(AAssetManager* aAssetManager) {
    LOGD("setAssetAndGeneratePixels.");
    if (!aAssetManager) {
        LOGE("aAssetManager null.");
        return;
    }
    mAAssetManager = aAssetManager;
    const char* fileName = "3.jpg";
    AAsset* asset = AAssetManager_open(mAAssetManager, fileName, AASSET_MODE_STREAMING);
    if (!asset) {
        LOGE("asset null.");
        return;
    }
    AImageDecoder* decoder;
    int result = AImageDecoder_createFromAAsset(asset, &decoder);
    if (result != ANDROID_IMAGE_DECODER_SUCCESS) {
        LOGE("file could not be decoded.");
        AAsset_close(asset);
        return;
    }
    const AImageDecoderHeaderInfo* info = AImageDecoder_getHeaderInfo(decoder);
    mWidth = AImageDecoderHeaderInfo_getWidth(info);
    mHeight = AImageDecoderHeaderInfo_getHeight(info);
    AndroidBitmapFormat format = static_cast<AndroidBitmapFormat>(AImageDecoderHeaderInfo_getAndroidBitmapFormat(
            info));
    size_t stride = AImageDecoder_getMinimumStride(decoder);
    size_t size = mHeight * stride;
    mPixels = malloc(size);
    result = AImageDecoder_decodeImage(decoder, mPixels, stride, size);
    if (result != ANDROID_IMAGE_DECODER_SUCCESS) {
        LOGE("decode error.");
    }
    AImageDecoder_delete(decoder);
    AAsset_close(asset);
}
