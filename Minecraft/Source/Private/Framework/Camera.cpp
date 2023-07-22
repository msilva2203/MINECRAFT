#include "Framework/Camera.h"

#include "Rendering/Renderer.h"

UCamera::UCamera() :
    FOV(90.0f)
{
}

UCamera::~UCamera()
{
}

void UCamera::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool UCamera::IsTickable() const
{
    return true;
}

void UCamera::SetViewTarget()
{
    URenderer::GetRenderer()->SetCamera(this);
}

glm::vec3 UCamera::GetCameraForwardVector() const
{
    glm::vec3 Rotation = GetCameraRotation();
    
    glm::vec3 forward {
        glm::cos(glm::radians(Rotation.y)) * glm::cos(glm::radians(Rotation.x)),
        glm::sin(glm::radians(Rotation.x)),
        glm::sin(glm::radians(Rotation.y)) * glm::cos(glm::radians(Rotation.x))
    };

    forward = glm::normalize(forward);

    return forward;
}

glm::vec3 UCamera::GetCameraRightVector() const
{
    return glm::cross(GetCameraForwardVector(), FMath::UpVector);
}

glm::vec3 UCamera::GetCameraUpVector() const
{
    return glm::cross(GetCameraRightVector(), GetCameraForwardVector());
}
