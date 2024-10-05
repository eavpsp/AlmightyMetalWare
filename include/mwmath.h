#ifndef MATH_H
#define MATH_H

#include <glm/glm.hpp>
namespace MW_Math
{
    //float lerp(float a, float b, float t);
    float Random(float min, float max);
    int Random(int min, int max);
    float lerp(float a, float b, float t);
    glm::vec3 lerp(glm::vec3 a, glm::vec3 b, float t);

    float clamp(float value, float min, float max);
};


#endif /* MATH_H */
