//
// Created by lht on 2021/8/14.
//

#ifndef GLCPPTEST_MYSQURE_H
#define GLCPPTEST_MYSQURE_H

#include <GLES3/gl3.h>
#include "GraphicsInterface.h"

class MySqure : public GraphicsInterface {
public:
    MySqure();
    ~MySqure();
    virtual void create() override ;
    virtual void change(int width, int height) override ;
    virtual void draw() override ;
    void drawTriangle();

private:
    void prepareBuffer();
    GLuint mVertexBuffer;
    GLuint mElementBuffer;
    GLuint mVertexArray;
    GLuint mProgram;
    GLuint mPositionHandle;
    GLuint mColorHandle;
};


#endif //GLCPPTEST_MYSQURE_H
