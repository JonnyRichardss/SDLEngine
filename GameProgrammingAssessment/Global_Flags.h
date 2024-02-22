#ifndef USE_GAMEGLOBALS
#define USE_GAMEGLOBALS

const int FRAME_CAP = 60;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int GAME_MAX_X = 400;
const int GAME_MAX_Y = 300;

/*
* 
* PONG ONLY
const int PADDLE_X_ABS = 350;
const int PADDLE_W = 20;
const int PADDLE_H = 150;

const int SCORE_Y = 250;
const int SCORE_X_ABS = 150;

const int BALL_SIZE = 15;

const int PADDLE_MOVESPEED = 5;

const float  ACCLERATION_CLAMP_FACTOR = 70000.0f;
const float DEFLECTION_REDUCTION_MODIFIER = 250.0f;
*/
const bool DEBUG_DRAW_BB = false;
enum WaitMethods {BUSY,SDL,THREAD};
const WaitMethods GF_WAIT_METHOD = BUSY; //SDL seems to under-sleep and THREAD seems to over-sleep
#endif // !USE_GAMEGLOBALS
