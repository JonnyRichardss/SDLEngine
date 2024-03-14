#ifndef USE_GAMEGLOBALS
#define USE_GAMEGLOBALS
constexpr int FRAME_CAP = 60;

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int GAME_MAX_X = 1000;
constexpr int GAME_MAX_Y = 1000;

constexpr int SPLASH_SCREEN_DURATION = 999;
static const char* LOG_FOLDER_PATH = "Logs/";
static const char* LOGFILE_NAME = "latest.log";

static const char* BASE_ASSET_PATH = "Assets/";
static const char* SPRITE_INFO_FORMAT = ".spritedims";

constexpr bool DEBUG_DRAW_BB = false;
constexpr bool DEBUG_EXTRA_LOGGING = true; //designed for when using print debugging so I can (possibly) leave the logs in

constexpr bool CONSOLE_LOG_DEFAULT = true;
constexpr bool DO_FILE_LOGGING = true;
constexpr bool DO_BATCH_LOGGING = true;
constexpr bool VERBOSE_CONSOLE = false;

constexpr bool DO_PROFILING = true;

constexpr bool AUDIO_FAILURE_FATAL = true;

static bool ENGINE_QUIT_FLAG = false;//be aware this doesn't work the way you think it does

constexpr int NUM_BOIDS = 1024;

constexpr int MUSIC_TEMPO = 192;
constexpr int MUSIC_START_OFFSET = 0;
constexpr int MUSIC_VOLUME = 0;
constexpr int MASTER_VOLUME = 0;
enum WaitMethods {BUSY,SDL,THREAD};
static constexpr WaitMethods GF_WAIT_METHOD = BUSY; //SDL seems to under-sleep and THREAD seems to over-sleep
#endif // !USE_GAMEGLOBALS
