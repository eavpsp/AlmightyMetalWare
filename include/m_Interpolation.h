#ifndef M_INTERPOLATION_H
#define M_INTERPOLATION_H

namespace mmath
{
    float lerp(float x, float y, float t) 
    {
        return x * (1.f - t) + y * t;
    }
}



#endif // M_INTERPOLATION_H
