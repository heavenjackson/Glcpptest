//
// Created by lht on 2021/8/14.
//

#include "GLUtils.h"
#include <android/log.h>

#define LOG_TAG "gles_test"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

GLuint GLUtils::createProgram(const char **vertexSource, const char **fragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    if (!vertexShader) {
        LOGE("vertexShader failed.");
        return 0;
    }
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (!fragmentShader) {
        LOGE("fragmentShader failed.");
        return 0;
    }
    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        GLint linkStatus;
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (!linkStatus) {
            GLint infoLen = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen > 0) {
                char *infoLog = new char[infoLen];
                glGetProgramInfoLog(program, infoLen, NULL, infoLog);
                LOGE("Error linking program:\n%s\n", infoLog);
                delete [] infoLog;
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint GLUtils::loadShader(GLenum shaderType, const char **source) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, source, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen > 0) {
                char *infoLog = new char[infoLen];
                glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
                LOGE("Error compiling shader:\n%s\n", infoLog);
                delete [] infoLog;
            }
            glDeleteShader(shader);
            shader = 0;
        }
    }
    return shader;
}
