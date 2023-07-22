#include "Entity.h"

void AEntity::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

bool AEntity::IsTickable() const
{
    return true;
}

FTransform AEntity::GetEntityTransform() const
{
    return Transform;
}

glm::vec3 AEntity::GetEntityLocation() const
{
    return Transform.Location;
}

glm::vec3 AEntity::GetEntityRotation() const
{
    return Transform.Rotation;
}

glm::vec3 AEntity::GetEntityScale() const
{
    return Transform.Scale;
}

void AEntity::SetEntityTransform(FTransform NewTransform)
{
    Transform = NewTransform;
}

void AEntity::SetEntityLocation(const glm::vec3& NewLocation)
{
    Transform.Location = NewLocation;
}

void AEntity::SetEntityRotation(const glm::vec3& NewRotation)
{
    Transform.Rotation = NewRotation;
}

void AEntity::SetEntityScale(const glm::vec3& NewScale)
{
    Transform.Scale = NewScale;
}

void AEntity::OffsetLocation(const glm::vec3& Offset)
{
    Transform.Location.x += Offset.x;
    Transform.Location.y += Offset.y;
    Transform.Location.z += Offset.z;
}

void AEntity::OffsetRotation(const glm::vec3& Offset)
{
    Transform.Rotation.x += Offset.x;
    Transform.Rotation.y += Offset.y;
    Transform.Rotation.z += Offset.z;
}

void AEntity::OffsetScale(const glm::vec3& Offset)
{
    Transform.Scale.x += Offset.x;
    Transform.Scale.y += Offset.y;
    Transform.Scale.z += Offset.z;
}
