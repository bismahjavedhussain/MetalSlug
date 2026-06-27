#pragma once
#include "coordSyst.h"

class TileMap;


class Camera
{
    coordSyst topLeft;  
    float viewWidth;    
    float viewHeight;   
    float mapPixelW;
    float mapPixelH;

public:
    Camera(float viewW = 1600.0f, float viewH = 900.0f);

    void setMapBounds(float pxW, float pxH);
    void followTarget(coordSyst target);

    coordSyst getOffset() const { return topLeft; }
    float getViewWidth()  const { return viewWidth;  }
    float getViewHeight() const { return viewHeight; }
};
