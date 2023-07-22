#pragma once

#include "Debugger.h"
#include "Entity.h"
#include "Object.h"
#include "PlayerController.h"

#include <vector>

class UWorld : public UObject
{
    typedef UObject Super;
public:
    UWorld();
    virtual void InitObject() override;
    virtual void TerminateObject() override;
    
public:
    void Update(float CurrentTime);
    float GetWorldDeltaTime() const;

    template <class T>
    T* CreateObject()
    {
        T* NewObject = new T;

        if(IsValid(NewObject))
        {
            Cast<UObject>(NewObject)->SetWorld(this);
            Cast<UObject>(NewObject)->InitObject();
            WorldObjects.push_back(NewObject);
        }
        else
        {
            UDebugger::Log("Could not create new object", ERROR);
        }

        return NewObject;
    }

    template <class T>
    T* SpawnEntity(FTransform SpawnTransform = FTransform())
    {
        T* NewEntity = new T;

        if (IsValid(NewEntity))
        {
            Cast<AEntity>(NewEntity)->SetEntityTransform(SpawnTransform);
            Cast<AEntity>(NewEntity)->SetWorld(this);
            Cast<AEntity>(NewEntity)->InitObject();
            WorldObjects.push_back(NewEntity);
        }
        else
        {
            UDebugger::Log("Could not create new entity", ERROR);
        }

        return NewEntity;
    }

    void AddObject(UObject* Object)
    {
        WorldObjects.push_back(Object);
    }


public:
    virtual UWorld* GetWorld() override;
    UTimerManager* GetTimerManager();
    APlayerController* GetPlayerController();

private:
    float DeltaTime;
    float LastFrameTime;

    UTimerManager* TimerManager;
    APlayerController* PlayerController;

    std::vector<UObject*> WorldObjects;
};
