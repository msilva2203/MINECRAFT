#include "Framework/Debugger.h"

#include "Statics/Globals.h"

#include <chrono>
#include <iostream>
#include <ctime>
#include <fstream>
#include <filesystem>

UDebugger* GDebugger;

static void PrintFPS()
{
    
}


DebugTimer::DebugTimer(const std::string& Name) :
    name(Name)
{
    start = glfwGetTime();
}

DebugTimer::~DebugTimer()
{
    const double end = glfwGetTime();
    const double elapsed = (end - start) * 1000.0f;
    
    std::stringstream message;
    message << "<" << name << "> Elapsed Time: " << elapsed << "ms";
    UDebugger::Log(message.str());
}


UDebugger::UDebugger() :
    FPS(0.0f)
{
    std::filesystem::create_directory("Logs/");
}

UDebugger* UDebugger::GetDebugger()
{
    if (!IsValid(GDebugger))
        GDebugger = new UDebugger;
    return GDebugger;
}

void UDebugger::TerminateObject()
{
    Super::TerminateObject();

    PrintLog();
}

void UDebugger::Tick(float DeltaTime)
{
    FPS = 1.0f / DeltaTime;

    //std::stringstream fps;
    //fps << "FPS: " << GetFPS();
    //UDebugger::Log(fps.str());
}

bool UDebugger::IsTickable() const
{
    return true;
}

template <typename T>
void UDebugger::Print(T Message)
{
    std::cout << Message << std::endl;
}

template void UDebugger::Print<const char*>(const char*);

void UDebugger::Log(const std::string& Message, ELogType LogType, bool bSaveLog)
{
    int now = (int)std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    
    std::string sec = std::to_string(now % 60);
    if (sec.size() == 1) sec = "0" + sec;
    std::string min = std::to_string(now / 60 % 60);
    if (min.size() == 1) min = "0" + min;
    std::string hour = std::to_string(now / 60 / 60 % 24 + 1);
    if (hour.size() == 1) hour = "0" + hour;
    std::string log = "[" + hour + ":" + min + ":" + sec + "] ";

    switch (LogType)
    {
    case NORMAL:
        break;
    case WARNING:
        log += "WARNING: ";
        break;
    case ERROR:
        log += "ERROR: ";
        break;
    }

    log += Message;

    std::cout << log << std::endl;

    // Adds log to Application Debugger if possible
    if (bSaveLog)
    {
        UDebugger* Debugger = UDebugger::GetDebugger();
        if (IsValid(Debugger))
            Debugger->SaveLog(log);
        else
        {
            UDebugger::Log("Debugger is invalid", WARNING, false);
        }
    }
}

void UDebugger::SaveLog(const std::string& log)
{
    LogStream << log << std::endl;
}

void UDebugger::PrintLog()
{
    Log("Printing Logs");

    tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);

    std::string path = "Logs/";
    std::string filename;
    filename = filename + path + "LOG[" + std::to_string(newtime.tm_year) + ":" + std::to_string(newtime.tm_mon) + ":" + std::to_string(newtime.tm_mday) + "].txt";

    //std::cout << filename << std::endl;
    
    std::ofstream stream("Logs/log.txt");
    stream << LogStream.str() << std::endl;
    stream.close();
}

float UDebugger::GetFPS()
{
    if (IsValid(GDebugger))
        return GDebugger->FPS;

    return 0.0f;
}
