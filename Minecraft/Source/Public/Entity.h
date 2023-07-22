#pragma once

#include "Object.h"

class AEntity : public UObject
{
    typedef UObject Super;
public:
    
    
public:
    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;

public:
    FTransform GetEntityTransform() const;
    glm::vec3 GetEntityLocation() const;
    glm::vec3 GetEntityRotation() const;
    glm::vec3 GetEntityScale() const;

    void SetEntityTransform(FTransform NewTransform);
    void SetEntityLocation(const glm::vec3& NewLocation);
    void SetEntityRotation(const glm::vec3& NewRotation);
    void SetEntityScale(const glm::vec3& NewScale);

    void OffsetLocation(const glm::vec3& Offset);
    void OffsetRotation(const glm::vec3& Offset);
    void OffsetScale(const glm::vec3& Offset);

private:
    FTransform Transform;
    
};
