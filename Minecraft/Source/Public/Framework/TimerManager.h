#pragma once

#include "Object.h"

#include <vector>
#include <string>


typedef unsigned int TimerHandle;

struct FTimer
{
    TimerHandle Handle;
    void (*Callback)();
    float Time, Range;
    bool bLoop;
    bool bPaused;
    unsigned int NumLoops;
    std::string TimerName;
    bool bDebug;
};

class UTimerManager : public UObject
{
    typedef UObject Super;
public:
    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;

    void SetTimer(TimerHandle& Handle, void(*Callback)(), float Range, bool bLoop, const std::string& TimerName = "Default Timer", bool bDebug = false);
    void ClearTimer(TimerHandle& Handle);
    void PauseTimer(TimerHandle& Handle);
    void ResumeTimer(TimerHandle& Handle);
    bool IsTimerActive(TimerHandle& Handle);
    bool IsTimerPaused(TimerHandle& Handle);

    float TimeRemaining(TimerHandle& Handle);
    bool IsTimerLooping(TimerHandle& Handle);
    unsigned int GetTimerNumLoops(TimerHandle& Handle);

private:
    std::vector<FTimer> Timers;
};
