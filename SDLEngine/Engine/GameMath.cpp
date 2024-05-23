#include "GameMath.h"

long double Lerp(long double a, long double b, long double fac) {
    return a + fac * (b - a);
}
