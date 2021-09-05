//
// Created by lht on 2021/8/14.
//

#ifndef GLCPPTEST_GLUTILS_H
#define GLCPPTEST_GLUTILS_H

#include <GLES3/gl3.h>

class GLUtils {
public:
    static GLuint createProgram(const char **vertexSource, const char **fragmentSource);

private:
    static GLuint loadShader(GLenum shaderType, const char **source);
};


#endif //GLCPPTEST_GLUTILS_H
