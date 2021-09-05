//
// Created by lht on 2021/8/14.
//
#include <jni.h>
#include <android/log.h>
#include "GLUtils.h"
#include "MySqure.h"

#define LOG_TAG "gles_test"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

namespace {
const char *vertexShaderSource = R"(
attribute vec3 a_Position;
attribute vec4 a_Color;
varying vec4 v_Color;
void main()
{
    gl_Position = vec4(a_Position, 1.0);
    v_Color = a_Color;
}
)";

const char *fragmentShaderSource = R"(
precision mediump float;
varying vec4 v_Color;
void main()
{
    gl_FragColor = v_Color;
}
)";

GLfloat vertices[] = {
    // positions         // colors
    0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,  // bottom left
    -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f   // top
};

GLfloat triangleVertices[] = {
    // positions         // colors
    0.0f, 0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f  // bottom left
};

const GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
};

}

MySqure::MySqure() {

}
MySqure::~MySqure() {

}
void MySqure::create() {
    mProgram = GLUtils::createProgram(&vertexShaderSource, &fragmentShaderSource);
    prepareBuffer();
}
void MySqure::prepareBuffer() {
    glGenBuffers(1, &mVertexBuffer);
    glGenBuffers(1, &mElementBuffer);
    glGenVertexArrays(1, &mVertexArray);
    glBindVertexArray(mVertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    mPositionHandle = glGetAttribLocation(mProgram, "a_Position");
    glVertexAttribPointer(mPositionHandle, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(mPositionHandle);

    mColorHandle = glGetAttribLocation(mProgram, "a_Color");
    glVertexAttribPointer(mColorHandle, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(mColorHandle);
}

void MySqure::change(int width, int height) {
    glViewport(0, 0, width, height);
}
void MySqure::draw() {
    glClearColor(0.5F, 0.5F, 0.5F, 0.5F);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(mProgram);
    glBindVertexArray(mVertexArray);
    glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);

}
void MySqure::drawTriangle() {
    //glClearColor(0.5F, 0.5F, 0.5F, 0.5F);
    //glClear(GL_COLOR_BUFFER_BIT);
    //glUseProgram(mProgram);
    mPositionHandle = glGetAttribLocation(mProgram, "aPosition");
    glVertexAttribPointer(mPositionHandle, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), triangleVertices);
    glEnableVertexAttribArray(mPositionHandle);
    mColorHandle = glGetAttribLocation(mProgram, "aColor");
    glVertexAttribPointer(mColorHandle, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), triangleVertices + 3);
    glEnableVertexAttribArray(mColorHandle);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
}
