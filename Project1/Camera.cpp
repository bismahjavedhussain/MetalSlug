#include "Camera.h"

Camera::Camera(float viewW, float viewH) : topLeft(0.0f, 0.0f), viewWidth(viewW), viewHeight(viewH), 
                                          mapPixelW(0.0f), mapPixelH(0.0f) {}
void Camera::setMapBounds(float pxW, float pxH)
{
    mapPixelW = pxW;
    mapPixelH = pxH;
}

void Camera::followTarget(coordSyst target)  
{
    topLeft.x = target.x - viewWidth  * 0.5f;
    topLeft.y = target.y - viewHeight * 0.5f;
    if (topLeft.x < 0.0f) topLeft.x = 0.0f;
    if (topLeft.y < 0.0f) topLeft.y = 0.0f;
    if (mapPixelW > viewWidth  && topLeft.x + viewWidth  > mapPixelW) 
        topLeft.x = mapPixelW - viewWidth;
    if (mapPixelH > viewHeight && topLeft.y + viewHeight > mapPixelH)
        topLeft.y = mapPixelH - viewHeight;
}
