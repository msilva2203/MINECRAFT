#include "Framework/Pawn.h"

#include "Statics/GameplayStatics.h"
#include "Framework/Input.h"

#include <GLFW/glfw3.h>

static bool firstMouse = true;
static float yaw = 0.0f;
static float pitch = 0.0f;
static float Sensitivity = 50.0f;

APawn::APawn() :
    LastX(0.0f),
    LastY(0.0f),
    Speed(5.0f)
{
}

void APawn::InitObject()
{
    UInput::GetInputObject()->AddAxisInput("Forward Axis");
    UInput::GetInputObject()->AddKeyToAxisInput("Forward Axis", { INPUT_KEY_W,  1.0f, false });
    UInput::GetInputObject()->AddKeyToAxisInput("Forward Axis", { INPUT_KEY_S, -1.0f, false });
    
    UInput::GetInputObject()->AddAxisInput("Right Axis");
    UInput::GetInputObject()->AddKeyToAxisInput("Right Axis", { INPUT_KEY_D,  1.0f, false });
    UInput::GetInputObject()->AddKeyToAxisInput("Right Axis", { INPUT_KEY_A, -1.0f, false });

    UInput::GetInputObject()->AddAxisInput("Up Axis");
    UInput::GetInputObject()->AddKeyToAxisInput("Up Axis", { INPUT_KEY_SPACE,  1.0f, false });
    UInput::GetInputObject()->AddKeyToAxisInput("Up Axis", { INPUT_KEY_LEFT_CONTROL, -1.0f, false });
}

void APawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    double xpos, ypos;
    glfwGetCursorPos(URenderer::GetWindow(), &xpos, &ypos);

    CameraAxisX = xpos - LastX;
    CameraAxisY = LastY - ypos;
    LastX = xpos;
    LastY = ypos;

    float AxisForward = UInput::GetInputObject()->GetAxisValue("Forward Axis");
    float AxisRight = UInput::GetInputObject()->GetAxisValue("Right Axis");
    float AxisUp = UInput::GetInputObject()->GetAxisValue("Up Axis");

    glm::vec3 Location = GetEntityLocation();
    glm::vec3 forward = UGameplayStatics::GetPlayerController(this)->PlayerCamera->GetCameraForwardVector();
    glm::vec3 right = UGameplayStatics::GetPlayerController(this)->PlayerCamera->GetCameraRightVector();
    glm::vec3 up = UGameplayStatics::GetPlayerController(this)->PlayerCamera->GetCameraUpVector();
    
    Location += AxisForward * Speed * forward * DeltaTime;
    Location += AxisRight * Speed * right * DeltaTime;
    Location += AxisUp * Speed * up * DeltaTime;
    SetEntityLocation(Location);

    glm::vec3 Rotation = GetEntityRotation();
    Rotation.x += CameraAxisY * DeltaTime * Sensitivity;
    Rotation.y += CameraAxisX * DeltaTime * Sensitivity;

    // Clamp Pitch
    if (Rotation.x > 89.0f)         Rotation.x = 89.0f;
    else if (Rotation.x < -89.0f)   Rotation.x = -89.0f;

    if (Rotation.z > 359.0f)        Rotation.z = 0.0f;
    else if (Rotation.z < 0.0f)     Rotation.z = 360.0f;
    
    SetEntityRotation(Rotation);

    UGameplayStatics::GetPlayerController(this)->SetCameraLocation(GetEntityLocation());
    UGameplayStatics::GetPlayerController(this)->SetCameraRotation(GetEntityRotation());
}

bool APawn::IsTickable() const
{
    return true;
}

void APawn::HandleInput()
{
}

void APawn::KeyCallback(int key, int action)
{
    if (key == INPUT_KEY_LEFT_SHIFT && action == INPUT_RELEASE) Speed /= 4.0f;
    if (key == INPUT_KEY_LEFT_SHIFT && action == INPUT_PRESS) Speed *= 4.0f;
    
}

void APawn::MouseCallback(double xpos, double ypos)
{
}

