#pragma once

#include <chrono>
#include <string>
#include <sstream>

#include "Object.h"

// False assertion causes the Debugger to terminate and printing the logs
#define ASSERT(x) if(!(x)) { if(UDebugger::GetDebugger()) UDebugger::GetDebugger()->TerminateObject();\
    __debugbreak(); }

enum ELogType
{
    NORMAL = 0,
    WARNING,
    ERROR
};

// Debug Timer
// Can be used to benchmark code
class DebugTimer
{
public:
    DebugTimer(const std::string& Name = "Default Timer");
    ~DebugTimer();

    std::string name;
    double start;
};

// Debugger class
class UDebugger : public UObject
{
    typedef UObject Super;
public:
    UDebugger();

    // Singleton
    static UDebugger* GetDebugger();
    virtual void TerminateObject() override;
    
public:
    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;

public:
    template <typename T>
    static void Print(T Message);

    static void Log(const std::string& Message, ELogType LogType = NORMAL, bool bSaveLog = true);
    void SaveLog(const std::string& log);
    void PrintLog();

public:
    static float GetFPS();

private:
    float FPS;
    std::stringstream LogStream;
};
