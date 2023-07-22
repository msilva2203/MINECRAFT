#include "Statics/Math.h"


glm::vec3 FMath::UpVector = { 0.0f, 1.0f, 0.0f };

template <typename T>
T FMath::Clamp(T Value, T Min, T Max)
{
    if (Value > Max) return Max;
    if (Value < Min) return Min;
    return Value;
}

template float FMath::Clamp<float>(float, float, float);


bool FMath::CompareFloat(float A, float B, float Precision)
{
    A *= Precision;
    B *= Precision;

    return ((int)A == (int)B);
}
