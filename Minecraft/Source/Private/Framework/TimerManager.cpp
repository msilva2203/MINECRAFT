#include "Framework/TimerManager.h"

#include "Framework/Debugger.h"


void UTimerManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    std::vector<unsigned int> TrashHandles = {};

    std::vector<FTimer>::iterator end = Timers.end();
    for (std::vector<FTimer>::iterator Timer = Timers.begin(); Timer != end; Timer++)
    {
        if (!Timer->bPaused)
        {
            Timer->Time += DeltaTime;

            std::stringstream message;
            message << "Timer <" << Timer->TimerName << "> concluded after " << Timer->Range << " seconds : ";
            
            if (Timer->Time >= Timer->Range)
            {
                Timer->Callback();
            
                if (Timer->bLoop)
                {
                    Timer->Time = 0.0f;
                    Timer->NumLoops++;
                    message << "loop " << Timer->NumLoops;
                }
                else
                {
                    TrashHandles.push_back(Timer->Handle);
                    message << "not looping";
                }

                if (Timer->bDebug)
                {
                    UDebugger::Log(message.str());
                }
            }
        }
    }

    if (!TrashHandles.empty())
    {
        for (auto Handle : TrashHandles)
        {
            ClearTimer(Handle);
        }
    }
}

bool UTimerManager::IsTickable() const
{
    return true;
}

void UTimerManager::SetTimer(TimerHandle& Handle, void(*Callback)(), float Range, bool bLoop, const std::string& TimerName, bool bDebug)
{
    FTimer NewTimer;
    Handle = Timers.size() + 1;

    NewTimer.Time = 0.0f;
    NewTimer.Callback = Callback;
    NewTimer.Handle = Handle;
    NewTimer.Range = Range;
    NewTimer.bLoop = bLoop;
    NewTimer.bPaused = false;
    NewTimer.NumLoops = 0;
    NewTimer.TimerName = TimerName;
    NewTimer.bDebug = bDebug;

    Timers.push_back(NewTimer);
}

void UTimerManager::ClearTimer(TimerHandle& Handle)
{
    // Handle indexed at 0 is considered invalid
    if (Handle == 0) return;
    
    std::vector<FTimer>::iterator end = Timers.end();
    for (std::vector<FTimer>::iterator it = Timers.begin(); it != end; it++)
    {
        if (it->Handle == Handle)
        {
            Timers.erase(it);

            // Handle is set to 0 after clearing it from the manager
            // Handle indexed at 0 is considered invalid
            Handle = 0;
            return;
        }
    }

    // Handle is set to 0 if handle is not found
    // Handle indexed at 0 is considered invalid
    Handle = 0;
}

void UTimerManager::PauseTimer(TimerHandle& Handle)
{
    // Handle indexed at 0 is considered invalid
    if (Handle == 0) return;

    std::vector<FTimer>::iterator end = Timers.end();
    for (std::vector<FTimer>::iterator it = Timers.begin(); it != end; it++)
    {
        if (it->Handle == Handle)
        {
            it->bPaused = true;
            return;
        }
    }

    // Handle is set to 0 if handle is not found
    // Handle indexed at 0 is considered invalid
    Handle = 0;
}

void UTimerManager::ResumeTimer(TimerHandle& Handle)
{
    // Handle indexed at 0 is considered invalid
    if (Handle == 0) return;

    std::vector<FTimer>::iterator end = Timers.end();
    for (std::vector<FTimer>::iterator it = Timers.begin(); it != end; it++)
    {
        if (it->Handle == Handle)
        {
            it->bPaused = false;
            return;
        }
    }

    // Handle is set to 0 if handle is not found
    // Handle indexed at 0 is considered invalid
    Handle = 0;
}

bool UTimerManager::IsTimerPaused(TimerHandle& Handle)
{
    // Handle indexed at 0 is considered invalid
    if (Handle == 0) return false;

    std::vector<FTimer>::iterator end = Timers.end();
    for (std::vector<FTimer>::iterator it = Timers.begin(); it != end; it++)
    {
        if (it->Handle == Handle)
        {
            return it->bPaused;
        }
    }

    // Handle is set to 0 if handle is not found
    // Handle indexed at 0 is considered invalid
    Handle = 0;
    return false;
}

bool UTimerManager::IsTimerActive(TimerHandle& Handle)
{
    // Handle indexed at 0 is considered invalid
    if (Handle == 0) return false;

    std::vector<FTimer>::iterator end = Timers.end();
    for (std::vector<FTimer>::iterator it = Timers.begin(); it != end; it++)
    {
        if (it->Handle == Handle)
        {
            return true;
        }
    }

    // Handle is set to 0 if handle is not found
    // Handle indexed at 0 is considered invalid
    Handle = 0;
    return false;
}

float UTimerManager::TimeRemaining(TimerHandle& Handle)
{
    // Handle indexed at 0 is considered invalid
    if (Handle == 0) return 0.0f;
    
    std::vector<FTimer>::iterator end = Timers.end();
    for (std::vector<FTimer>::iterator it = Timers.begin(); it != end; it++)
    {
        if (it->Handle == Handle)
        {
            return it->Range - it->Time;
        }
    }

    // Handle is set to 0 if handle is not found
    // Handle indexed at 0 is considered invalid
    Handle = 0;
    return 0.0f;
}

bool UTimerManager::IsTimerLooping(TimerHandle& Handle)
{
    // Handle indexed at 0 is considered invalid
    if (Handle == 0) return 0.0f;

    std::vector<FTimer>::iterator end = Timers.end();
    for (std::vector<FTimer>::iterator it = Timers.begin(); it != end; it++)
    {
        if (it->Handle == Handle)
        {
            return it->bLoop;
        }
    }

    // Handle is set to 0 if handle is not found
    // Handle indexed at 0 is considered invalid
    Handle = 0;
    return 0.0f;
}

unsigned UTimerManager::GetTimerNumLoops(TimerHandle& Handle)
{
    // Handle indexed at 0 is considered invalid
    if (Handle == 0) return 0.0f;

    std::vector<FTimer>::iterator end = Timers.end();
    for (std::vector<FTimer>::iterator it = Timers.begin(); it != end; it++)
    {
        if (it->Handle == Handle)
        {
            return it->NumLoops;
        }
    }

    // Handle is set to 0 if handle is not found
    // Handle indexed at 0 is considered invalid
    Handle = 0;
    return 0.0f;
}
