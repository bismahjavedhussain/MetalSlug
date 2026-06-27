#pragma once



struct AnimClip
{
    int srcY;
    int  srcH;
    int  frameW;
    int frameCount;
    float interval;
    bool looping;

    AnimClip();
    AnimClip(int y, int h, int fw, int count, float ivl, bool loop);
};