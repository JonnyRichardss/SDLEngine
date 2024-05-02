#ifndef USE_GAMEGLOBALS
#define USE_GAMEGLOBALS
constexpr int FRAME_CAP = 60;

constexpr int WINDOW_WIDTH = 1600;
constexpr int WINDOW_HEIGHT = 900;
constexpr int GAME_MAX_X = 800;
constexpr int GAME_MAX_Y = 450;

constexpr int COLLISION_INIT_SIZE = 100;
constexpr int COLLISION_EXPAND_SIZE = 10;
//not used - the reallcoation was buggy
//allocing every frame *might* get laggy but who knows

constexpr int SPLASH_SCREEN_DURATION = 13040;
constexpr int MAIN_SONG_DURATION = 73040;

static const char* LOG_FOLDER_PATH = "Logs/";
static const char* LOGFILE_NAME = "latest.log";

static const char* BASE_ASSET_PATH = "Assets/";
static const char* SPRITE_INFO_FORMAT = ".spritedims";

static const char* SCORE_FONT_PATH = "Assets/cour.ttf";
constexpr int SCORE_FONT_PTSIZE = 18;
constexpr int SCORE_POS_X = -700;
constexpr int SCORE_POS_Y = -400;

constexpr int BONUS_MODE_SCORE_THRESHOLD = 5000;

constexpr bool DEBUG_DRAW_MELEES = false;
constexpr bool DEBUG_DRAW_BB = false; 
constexpr bool DEBUG_EXTRA_LOGGING = false; //designed for when using print debugging so I can (possibly) leave the logs in
constexpr bool DEBUG_FRAMETIME_LOG = false;//also disables profiling if its on or not
		constexpr bool DEBUG_DO_PROFILING = false;

		
constexpr bool CONSOLE_LOG_DEFAULT = true;
constexpr bool DO_FILE_LOGGING = true;
constexpr bool DO_BATCH_LOGGING = true;
constexpr bool VERBOSE_CONSOLE = false;
constexpr bool CONSOLE_SHOW_TIME = false;


constexpr bool AUDIO_FAILURE_FATAL = true;

static bool ENGINE_QUIT_FLAG = false;//be aware this doesn't work the way you think it does

constexpr float BASE_PUSH_FACTOR = 0.01;
constexpr float BASE_FRICTION = 0.25;

constexpr float PLAYER_IFRAMES = 30;
constexpr float PLAYER_HP = 100;
constexpr float DASH_DISTANCE = 150;
constexpr float PLAYER_SPEED = 10;
constexpr float ENEMY_STEP_WIDTH = 20;

//if i have time ill look into extending timing window for mid-combo specifically
constexpr float ATTACK1_DAMAGE = 10;
constexpr int ATTACK1_COMBO_LENGTH = 3;
constexpr int ATTACK1_COMBO_COOLDOWN = 3;

constexpr float ATTACK2_DAMAGE = 10;
constexpr int ATTACK2_COMBO_LENGTH = 3;
constexpr int ATTACK2_COMBO_COOLDOWN = 2;

constexpr int DASH_COMBO_LENGTH = 3;
constexpr int DASH_COMBO_COOLDOWN = 2;

constexpr float ENEMY_DAMAGE = 5;
constexpr float ENEMY_HP = 20;

constexpr int NUM_BOIDS = 1024;

constexpr int NUM_TEST_COLLIDERS = 500;
constexpr int MAX_COLLISIONS = 100;//length of "colliders" array - not entirely sure this is necessary at the scales we can reasonably reach
constexpr int TEST_COLLIDER_SIZE = 25;

constexpr float TIMING_LENIENCY = 3.0; 
//higher = smaller timing window, values <2 will cause problems 
//(this assumes whole number values but i think decimals will be ok too (stored as float to prevent casting))
//also - there is an intermittent timing based bug with a value of 2.0
//this is to do with the way combos are reset and is pretty much not worth it to fix
constexpr int MUSIC_TEMPO = 184;
constexpr double MS_PER_BEAT = 60000.0f / (float)MUSIC_TEMPO;
constexpr int MUSIC_START_OFFSET = 0;
constexpr float MUSIC_VOLUME = 1;
constexpr float MASTER_VOLUME = 1;
enum WaitMethods {WM_BUSY,WM_SDL,WM_THREAD};
static constexpr WaitMethods GF_WAIT_METHOD = WM_BUSY; //SDL seems to under-sleep and THREAD seems to over-sleep
#endif // !USE_GAMEGLOBALS
