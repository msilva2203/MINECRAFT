#pragma once

#include "Object.h"
#include "Framework/World.h"

class Application : public UObject
{
public:
    Application();
    virtual ~Application() override;

public:
    int Setup();
    void Run();

    template <class T>
    void OpenWorld()
    {
        if (GetWorld())
        {
            GetWorld()->TerminateObject();
            delete CurrentWorld;
        }
        CurrentWorld = new T;
        CurrentWorld->InitObject();
    }

public:
    bool IsRunning() const;
    void SetRunning(const bool bNewValue);
    
    virtual UWorld* GetWorld() override;

private:
    bool bRunning;
    UWorld* CurrentWorld;
};
