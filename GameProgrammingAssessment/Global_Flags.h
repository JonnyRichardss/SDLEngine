#ifndef USE_GAMEGLOBALS
#define USE_GAMEGLOBALS

const int GF_FRAME_CAP = 240;



enum WaitMethods {BUSY,SDL,THREAD};
const WaitMethods GF_WAIT_METHOD = BUSY; //SDL seems to under-sleep and THREAD seems to over-sleep
#endif // !USE_GAMEGLOBALS
