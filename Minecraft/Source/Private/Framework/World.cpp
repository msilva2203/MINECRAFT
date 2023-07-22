#include "Framework/World.h"
#include "Framework/TimerManager.h"

#include "Tests/LiminalTriangle.h"
#include "Tests/PartyTriangle.h"
#include "Tests/RotatingCube.h"

#include <chrono>

#include "Game/ChunkManager.h"
#include "Statics/Globals.h"

static int count = 0;


UWorld::UWorld() :
    DeltaTime(0.0f),
    LastFrameTime(0.0f)
{
    TimerManager = CreateObject<UTimerManager>();
    PlayerController = SpawnEntity<APlayerController>();
    //CreateObject<PartyTriangle>();
    //CreateObject<LiminalTriangle>();
    //SpawnEntity<RotatingCube>();
    //SpawnEntity<Chunk>();
    CreateObject<UChunkManager>();
    
}

void UWorld::InitObject()
{
    Super::InitObject();
    
}

void UWorld::TerminateObject()
{
    for(std::vector<UObject*>::iterator it = WorldObjects.begin(); it < WorldObjects.end(); it++)
    {
        (*it)->TerminateObject();
    }
}


void UWorld::Update(float CurrentTime)
{
    DeltaTime = CurrentTime - LastFrameTime;
    LastFrameTime = CurrentTime;

    UDebugger::GetDebugger()->Tick(DeltaTime);

    for(std::vector<UObject*>::iterator it = WorldObjects.begin(); it < WorldObjects.end(); it++)
    {
        if ((*it)->IsTickable() && !(*it)->Terminated())
            (*it)->Tick(DeltaTime);
    }
}

float UWorld::GetWorldDeltaTime() const
{
    return DeltaTime;
}

UWorld* UWorld::GetWorld()
{
    return this;
}

UTimerManager* UWorld::GetTimerManager()
{
    return TimerManager;
}

APlayerController* UWorld::GetPlayerController()
{
    return PlayerController;
}

