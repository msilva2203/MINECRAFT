#pragma once

#include "Object.h"
#include "Framework/Debugger.h"
#include "Framework/PlayerController.h"


class UGameplayStatics : public UObject
{
public:
    static APlayerController* GetPlayerController(UObject* WorldContext);
    static UTimerManager* GetWorldTimerManager(UObject* WorldContext);
    static void QuitGame();
};
