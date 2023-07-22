#include "Object.h"

#include "Framework/World.h"

UObject::UObject() :
    World(nullptr),
    bTerminated(false)
{
}

UObject::~UObject()
{
}

void UObject::InitObject()
{
}

void UObject::TerminateObject()
{
    bTerminated = true;
}


void UObject::Tick(float DeltaTime)
{
}

bool UObject::IsTickable() const
{
    return false;
}

void UObject::SetWorld(UWorld* NewWorld)
{
    World = NewWorld;
}

UWorld* UObject::GetWorld()
{
    return World;
}

UTimerManager* UObject::GetWorldTimerManager()
{
    if (IsValid(GetWorld()))
        return GetWorld()->GetTimerManager();

    return nullptr;
}


bool UObject::IsValid(UObject* Object)
{
    return Object != nullptr;
}

bool UObject::Terminated() const
{
    return bTerminated;
}
