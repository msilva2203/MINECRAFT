#pragma once

#include "Statics/Math.h"


// Forward Declarations
class UWorld;
class UTimerManager;

class UObject
{
public:
    UObject();
    virtual ~UObject();

    virtual void InitObject();
    virtual void TerminateObject();
    
public:
    virtual void Tick(float DeltaTime);
    virtual bool IsTickable() const;

    void SetWorld(UWorld* NewWorld);
    virtual UWorld* GetWorld();
    UTimerManager* GetWorldTimerManager();

public:
    static bool IsValid(UObject* Object);
    
    template <class T>
    static T* Cast(UObject* Object)
    {
        return static_cast<T*>(Object);
    }

    bool Terminated() const;

private:
    UWorld* World;

    bool bTerminated;
};
