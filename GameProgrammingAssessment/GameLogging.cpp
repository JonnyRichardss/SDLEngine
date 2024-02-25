#include "GameLogging.h"
#include <iostream>
#include "GameUtils.h"
#include <cstdio>
#include <ctime>
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
        std::cout << logText<<"\n";
}

void GameLogging::FileLog(std::string logText)
{
    // it REALLY doesn't matter but i do wonder (since these are const bools defined in code) if these branches will compile out or not
    if (VERBOSE_CONSOLE)
        std::cout << logText << "\n";
    if (DO_FILE_LOGGING) {
        logBuffer.push_back(logText);
        if(!DO_BATCH_LOGGING)
            SaveLogFile();
    }
}
void GameLogging::DebugLog(std::string logText) {
    if (DEBUG_EXTRA_LOGGING) {
        Log(logText);
    }
}

void GameLogging::ToggleConsoleLog()
{
    consoleLogEnabled = consoleLogEnabled ? false : true;
    std::cout << "Console logging " << (consoleLogEnabled ? "enabled" : "disabled") << "!\n";
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
    char* timeString = new char[20];
    time_t timeNow = time(0);
    tm tmNow;
    localtime_s(&tmNow, &timeNow);
    strftime(timeString, 20, "%F-%H-%M-%S",&tmNow);
    logBuffer.insert(logBuffer.begin(), timeString);
    delete[20] timeString;
    if (WriteFile(LogPath, logBuffer)) {
        
        Log("Successfully created " +std::string(LOGFILE_NAME));
        fileExists = true;
    }
    else
        Log("Failed to make "+ std::string(LOGFILE_NAME));
}
