#include "AnimClip.h"

AnimClip::AnimClip() : srcY(0), srcH(56), frameW(28), frameCount(1), interval(0.12f), looping(true){}

AnimClip::AnimClip(int y, int h, int fw, int count, float ivl, bool loop): srcY(y), srcH(h), frameW(fw),
frameCount(count), interval(ivl), looping(loop){}