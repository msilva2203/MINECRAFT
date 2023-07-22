#pragma once

#include "Camera.h"
#include "Entity.h"
#include "Pawn.h"

class APlayerController : public AEntity
{
    typedef AEntity Super;
public:
    APlayerController();
    ~APlayerController();

    virtual void InitObject() override;
    
public:
    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;

    virtual void HandleInput();
    virtual void OnKeyCallback(int key, int action);
    virtual void OnMouseCallback(double xpos, double ypos);

    void SetShowMouseCursor(bool bNewValue);
    bool IsShowingMouseCursor() const { return bShowMouseCursor; }

    void SetCameraLocation(const glm::vec3& NewLocation) { PlayerCamera->SetCameraLocation(NewLocation); }
    void SetCameraRotation(const glm::vec3& NewRotation) { PlayerCamera->SetCameraRotation(NewRotation); }

public:
    UCamera* PlayerCamera;

private:
    APawn* PlayerPawn;
    bool bShowMouseCursor;
};
