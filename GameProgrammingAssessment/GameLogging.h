#ifndef USE_GAMELOG
#define USE_GAMELOG
#include <string>
#include <vector>
#include "Global_Flags.h"
class GameLogging
{
public:
	static GameLogging* GetInstance();
	void Log(std::string logText);
	void FileLog(std::string logText);
	void DebugLog(std::string logText);
	void ToggleConsoleLog();
	void SaveLogFile();
private:
	GameLogging();
	~GameLogging();
	bool consoleLogEnabled=CONSOLE_LOG_DEFAULT;
	bool fileExists=false;
	std::string LogPath;
	std::vector<std::string> logBuffer;
	
	void RenameLastLogFile();
	void MakeNewLogFile();
};
#endif // !USE_GAMELOG


