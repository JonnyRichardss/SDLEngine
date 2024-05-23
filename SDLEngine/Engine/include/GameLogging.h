#ifndef USE_GAMELOG
#define USE_GAMELOG
#include <string>
#include <vector>
//#include "Global_Flags.h"  TODO!
//TODO -- REWRITE THIS WHOLE THINGS AS A BACKEND FOR SDL_LOG -- IT HAS LOTS OF FEATURES BUILT IN
class GameLogging
{
public:
	static GameLogging* GetInstance();
	void Log(std::string logText);
	void FileLog(std::string logText);
	void DebugLog(std::string logText);
	void ToggleConsoleLog();
	void ToggleDebugLog();
	void SaveLogFile();
private:
	GameLogging();
	~GameLogging();
	bool consoleLogEnabled=true;  // TODO!
	bool showDebugLogs = false;  // TODO!
	bool fileExists=false;
	std::string LogPath;
	std::vector<std::string> logBuffer;
	void AddTime(std::string& logText);
	void RenameLastLogFile();
	void MakeNewLogFile();
};
#endif // !USE_GAMELOG


