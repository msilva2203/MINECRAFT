#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

struct FMath
{
    static glm::vec3 UpVector;
    
    template <typename T>
    static T Clamp(T Value, T Min, T Max);

    static bool CompareFloat(float A, float B, float Precision = 1000);
    
};


struct FTransform
{
    glm::vec3 Location;
    glm::vec3 Rotation;
    glm::vec3 Scale;

    FTransform() : Scale(1.0f, 1.0f, 1.0f) {}
    FTransform(glm::vec3 InLocation) : Location(InLocation), Scale(1.0f, 1.0f, 1.0f) {}
    FTransform(glm::vec3 InLocation, glm::vec3 InRotation, glm::vec3 InScale) : Location(InLocation), Rotation(InRotation), Scale(InScale) {}
};