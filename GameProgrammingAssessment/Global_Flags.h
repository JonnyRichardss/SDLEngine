#ifndef USE_GAMEGLOBALS
#define USE_GAMEGLOBALS
constexpr int FRAME_CAP = 60;

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int GAME_MAX_X = 800;
constexpr int GAME_MAX_Y = 600;

constexpr int COLLISION_INIT_SIZE = 100;
constexpr int COLLISION_EXPAND_SIZE = 10;
constexpr int MAX_COLLISIONS = 50;
constexpr int SPLASH_SCREEN_DURATION = 1;

static const char* LOG_FOLDER_PATH = "Logs/";
static const char* LOGFILE_NAME = "latest.log";

static const char* BASE_ASSET_PATH = "Assets/";
static const char* SPRITE_INFO_FORMAT = ".spritedims";

constexpr bool DEBUG_DRAW_BB = false; //this doesnt work anymore since the scaling and rotation assumptions it worked from are no longer valid
constexpr bool DEBUG_EXTRA_LOGGING = true; //designed for when using print debugging so I can (possibly) leave the logs in
constexpr bool DEBUG_FRAMETIME_LOG = false;//also disables profiling if its on or not
		constexpr bool DEBUG_DO_PROFILING = true;

constexpr bool CONSOLE_LOG_DEFAULT = true;
constexpr bool DO_FILE_LOGGING = true;
constexpr bool DO_BATCH_LOGGING = true;
constexpr bool VERBOSE_CONSOLE = false;



constexpr bool AUDIO_FAILURE_FATAL = true;

static bool ENGINE_QUIT_FLAG = false;//be aware this doesn't work the way you think it does

constexpr int NUM_BOIDS = 1024;

constexpr int NUM_TEST_COLLIDERS = 50;
constexpr int TEST_COLLIDER_SIZE = 90;

constexpr int MUSIC_TEMPO = 192;
constexpr int MUSIC_START_OFFSET = 0;
constexpr int MUSIC_VOLUME = 1;
constexpr int MASTER_VOLUME = 1;
enum WaitMethods {WM_BUSY,WM_SDL,WM_THREAD};
static constexpr WaitMethods GF_WAIT_METHOD = WM_BUSY; //SDL seems to under-sleep and THREAD seems to over-sleep
#endif // !USE_GAMEGLOBALS
