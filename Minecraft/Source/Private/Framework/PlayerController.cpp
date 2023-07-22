
#include "Framework/PlayerController.h"

#include "Framework/Debugger.h"
#include "Framework/World.h"
#include "Rendering/Renderer.h"
#include "Statics/GameplayStatics.h"
#include "Framework/Input.h"

#include <GLFW/glfw3.h>

#include "Framework/TimerManager.h"

static bool bInc = false;
static bool bDec = false;
static bool bFullscreen = false;

static void PrintFPS()
{
}


APlayerController::APlayerController() :
    PlayerCamera(nullptr),
    PlayerPawn(nullptr),
    bShowMouseCursor(false)
{
}

APlayerController::~APlayerController()
{
}

void APlayerController::InitObject()
{
    Super::InitObject();

    PlayerCamera = GetWorld()->CreateObject<UCamera>();
    PlayerCamera->SetViewTarget();

    PlayerPawn = GetWorld()->SpawnEntity<APawn>();

    SetShowMouseCursor(IsShowingMouseCursor());
    UInput::SetInputMode(GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    TimerHandle Handle;
    GetWorldTimerManager()->SetTimer(Handle, PrintFPS, 1.0f, true, "FPS Timer");
}

void APlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    HandleInput();

    if (bInc) PlayerCamera->SetFOV(PlayerCamera->GetFOV() + 15.0f * GetWorld()->GetWorldDeltaTime());
    if (bDec) PlayerCamera->SetFOV(PlayerCamera->GetFOV() - 15.0f * GetWorld()->GetWorldDeltaTime());
}

bool APlayerController::IsTickable() const
{
    return true;
}

void APlayerController::HandleInput()
{
    if (IsValid(PlayerPawn)) PlayerPawn->HandleInput();
}

void APlayerController::OnKeyCallback(int key, int action)
{
    if (IsValid(PlayerPawn)) PlayerPawn->KeyCallback(key, action);

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        UGameplayStatics::QuitGame();
    
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
        SetShowMouseCursor(!IsShowingMouseCursor());

    if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS) bInc = true;
    if (key == GLFW_KEY_KP_ADD && action == GLFW_RELEASE) bInc = false;
    
    if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS) bDec = true;
    if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_RELEASE) bDec = false;

    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        bFullscreen = !bFullscreen;
        URenderer::SetDisplayMode(bFullscreen ? EDisplayMode::FULLSCREEN : EDisplayMode::WINDOWED);
    }
        
}

void APlayerController::OnMouseCallback(double xpos, double ypos)
{
    if (IsValid(PlayerPawn)) PlayerPawn->MouseCallback(xpos, ypos);
}

void APlayerController::SetShowMouseCursor(bool bNewValue)
{
    if (bShowMouseCursor != bNewValue)
    {
        bShowMouseCursor = bNewValue;
        if (bShowMouseCursor)   UInput::SetInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        else                    UInput::SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}
