#include "Statics/GameplayStatics.h"

#include "Framework/World.h"
#include "Statics/Globals.h"

APlayerController* UGameplayStatics::GetPlayerController(UObject* WorldContext)
{
    if (WorldContext->GetWorld())
        return WorldContext->GetWorld()->GetPlayerController();
    
    return nullptr;
}

UTimerManager* UGameplayStatics::GetWorldTimerManager(UObject* WorldContext)
{
    if (IsValid(WorldContext))
        return WorldContext->GetWorldTimerManager();

    return nullptr;
}

void UGameplayStatics::QuitGame()
{
    if (IsValid(GApp))
        GApp->SetRunning(false);
}
