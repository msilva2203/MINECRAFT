#pragma once

#include "Object.h"
#include "Statics/Math.h"

class UCamera : public UObject
{
    typedef UObject Super;
public:
    UCamera();
    virtual ~UCamera();

public:
    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;

    void SetViewTarget();

public:
    void SetCameraTransform(FTransform NewTransform) { Transform = NewTransform; }
    void SetCameraLocation(const glm::vec3& NewLocation) { Transform.Location = NewLocation; }
    void SetCameraRotation(const glm::vec3& NewRotation) { Transform.Rotation = NewRotation; }
    
    FTransform GetCameraTransform() const { return Transform; }
    glm::vec3 GetCameraLocation() const { return GetCameraTransform().Location; }
    glm::vec3 GetCameraRotation() const { return GetCameraTransform().Rotation; }

    glm::vec3 GetCameraForwardVector() const;
    glm::vec3 GetCameraRightVector() const;
    glm::vec3 GetCameraUpVector() const;
    
    void SetFOV(const float NewValue) { FOV = FMath::Clamp<float>(NewValue, 45.0f, 120.0f); }
    float GetFOV() const { return FOV; }

private:
    FTransform Transform;
    float FOV;
    
};
