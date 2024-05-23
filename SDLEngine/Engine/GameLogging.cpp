#include "GameLogging.h"
#include <iostream>
#include "GameUtils.h"
#include <cstdio>
#include <ctime>
static const char* LOG_FOLDER_PATH = "Logs/";// TODO!
static const char* LOGFILE_NAME = "latest.log";// TODO!
static const bool VERBOSE_CONSOLE = false;// TODO!
static const bool DO_FILE_LOGGING = true;// TODO!
static const bool DO_BATCH_LOGGING = false;// TODO!
static const bool CONSOLE_SHOW_TIME = false;// TODO!
//TODO during refactor add a function to set these as settings and have defaults in engine_flags.h
static GameLogging* _instance;
GameLogging* GameLogging::GetInstance()
{
    if (_instance == nullptr)
        _instance = new GameLogging();
    return _instance;  
}

GameLogging::GameLogging()
{
    LogPath = std::string(LOG_FOLDER_PATH) + std::string(LOGFILE_NAME);
    RenameLastLogFile();
    MakeNewLogFile();
  
    Log("Initialised logging.");
}

GameLogging::~GameLogging()
{
}

void GameLogging::Log(std::string logText)
{
    FileLog(logText);
    if (consoleLogEnabled && !VERBOSE_CONSOLE)//VERBOSE_CONSOLE flag allows me to access logs that are sent straight to a file (to declutter console)
        AddTime(logText);//tecnically not ideal - this will add the time twice once for filelog and once here but fuck it its just a debug option
        std::cout << logText<<"\n";
}

void GameLogging::FileLog(std::string logText)
{
    AddTime(logText);
    if (VERBOSE_CONSOLE)
        std::cout << logText << "\n";
    if (DO_FILE_LOGGING) {
        logBuffer.push_back(logText);
        if(!DO_BATCH_LOGGING)
            SaveLogFile();
    }
}
void GameLogging::DebugLog(std::string logText) {
    if (showDebugLogs) {
        Log(logText);
    }
}

void GameLogging::ToggleConsoleLog()
{
    consoleLogEnabled = consoleLogEnabled ? false : true;
    std::cout << "Console logging " << (consoleLogEnabled ? "enabled" : "disabled") << "!\n";
}

void GameLogging::ToggleDebugLog()
{
    showDebugLogs = showDebugLogs ? false : true;
    std::cout << "Extra logging " << (showDebugLogs ? "enabled" : "disabled") << "!\n";
}

void GameLogging::SaveLogFile()
{
    //added for flexibility later if I want to log multiple lines at once
    //right now I'm thinking it's better to log instantly so it's easier to identify where errors occur
    //could be moved to update or something for performance but obviously if it crashes between logs I will lose the information
    //fun fact I learned about how frustrating this can be because PCSX2 won't display a std::cout until it detects a \n
    if (!fileExists)
        return;
    if (WriteFile(LogPath, logBuffer))
        logBuffer.clear();
    else {
        fileExists = false;
        Log("SaveLogFile() write failed!"); 
    }
    
}

void GameLogging::AddTime(std::string& logText)
{
    if (CONSOLE_SHOW_TIME) {
        char timeString[40];
        time_t timeNow = time(0);
        tm tmNow;
        localtime_s(&tmNow, &timeNow);
        strftime(timeString, 40, "[%F-%H-%M-%S]: ", &tmNow);
        logText = timeString + logText;
    }
}

void GameLogging::RenameLastLogFile()
{
    std::string fileTime = LOG_FOLDER_PATH;
    if (ReadFileFirstLine(LogPath, fileTime)) {
        fileTime.append(".log");
        if (rename(LogPath.c_str(), fileTime.c_str())) {//rename is a c function so returns 0 on success
            Log("Found old log file - failed to rename!");
            return;
        }
    }
    else {
        Log("Failed to find old log file");
        return;
    }
    Log("Successfully renamed old log file");
}

void GameLogging::MakeNewLogFile()
{
    char* timeString = new char[30];
    time_t timeNow = time(0);
    tm tmNow;
    localtime_s(&tmNow, &timeNow);
    strftime(timeString, 30, "%F-%H-%M-%S",&tmNow);
    logBuffer.insert(logBuffer.begin(), timeString);
    delete[20] timeString;
    if (WriteFile(LogPath, logBuffer)) {
        logBuffer.clear();
        Log("Successfully created " +std::string(LOGFILE_NAME));
        fileExists = true;
    }
    else
        Log("Failed to make "+ std::string(LOGFILE_NAME));
}
