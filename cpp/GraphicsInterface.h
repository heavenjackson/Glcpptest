//
// Created by lht on 2021/8/22.
//

#ifndef GLCPPTEST_GRAPHICSINTERFACE_H
#define GLCPPTEST_GRAPHICSINTERFACE_H

#include <android/asset_manager.h>

class GraphicsInterface {
public:
    virtual ~GraphicsInterface() {};
    virtual void create() = 0;
    virtual void change(int width, int height) = 0;
    virtual void draw() = 0;
    virtual void setAssetAndGeneratePixels(AAssetManager* aAssetManager) {}
};

#endif //GLCPPTEST_GRAPHICSINTERFACE_H
