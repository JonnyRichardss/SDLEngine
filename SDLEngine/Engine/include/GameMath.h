#ifndef USE_GAMEMATH
#define USE_GAMEMATH
#include <math.h>
#include <string>
#include "SDL.h"
struct Vector2 {
    float x;
    float y;
    Vector2() :x(0), y(0) {}
    Vector2(float _x, float _y) : x(_x), y(_y) {}
    Vector2(float _val) : x(_val), y(_val) {}
    Vector2& operator+=(const Vector2& _other) {
        this->x += _other.x;
        this->y += _other.y;
        return *this;
    }
    Vector2& operator-=(const Vector2& _other) {
        this->x -= _other.x;
        this->y -= _other.y;
        return *this;
    }
    friend Vector2 operator+(Vector2 lhs, const Vector2& rhs) {
        lhs += rhs;
        return lhs;
    }
    friend Vector2 operator-(Vector2 lhs, const Vector2& rhs) {
        lhs -= rhs;
        return lhs;
    }
    Vector2& operator*= (const float& other) {
        this->x *= other;
        this->y *= other;
        return *this;
    }
    Vector2& operator/= (const float& other) {
        this->x /= other;
        this->y /= other;
        return *this;
    }
    friend Vector2 operator* (const float& lhs, Vector2 rhs) {
        return rhs *= lhs;
    }
    friend Vector2 operator* (Vector2 lhs, const float& rhs) {
        return lhs *= rhs;
    }
    friend Vector2 operator/ (const float& lhs, Vector2 rhs) {
        return rhs /= lhs;
    }
    friend Vector2 operator/ (Vector2 lhs, const float& rhs) {
        return lhs /= rhs;
    }
    bool operator== (const Vector2& other) {
        return (x == other.x && y == other.y);
    }
    bool operator!= (const Vector2& other) {
        return !(*this == other);
    }
    static Vector2 one() {
        return Vector2(1, 1);
    }
    static Vector2 up() {
        return Vector2(0, 1);
    }
    static Vector2 right() {
        return Vector2(1, 0);
    }
    static Vector2 zero() {
        return Vector2();
    }
    static float dot(Vector2 a, Vector2 b) {
        return (a.x * b.x) + (a.y * b.y);
    }
    static float AngleBetweenRAD(Vector2 a, Vector2 b) {
        //https://stackoverflow.com/questions/14066933/direct-way-of-computing-the-clockwise-angle-between-two-vectors
        float det = a.x * b.y - a.y * b.x;
        return (atan2(det, dot(a, b)));
    }
    static Vector2 RotateAroundOrigin(Vector2 point, float angleRAD) {
        float x = point.x;
        float y = point.y;
        float newX = x * cos(angleRAD) - y * sin(angleRAD);
        float newY = y * cos(angleRAD) + x * sin(angleRAD);
        return Vector2(newX, newY);
    }
    static Vector2 RotateAroundPoint(Vector2 point,float angleRAD ,Vector2 centre){
        Vector2 translated = point - centre;
        Vector2 newPos = RotateAroundOrigin(translated,angleRAD);
        return newPos + centre;
    }
    static Vector2 Lerp(Vector2 a, Vector2 b,float fac) {
        Vector2 offset = b - a;
        return a + (offset)*fac;
    }
    float GetMagnitude() {
        return sqrt(pow(x, 2) + pow(y, 2));
    }
    Vector2 Normalise() {
        float mag = GetMagnitude();
        if (mag == 0) return Vector2(0, 0);
        float _x = x / mag;
        float _y = y / mag;
        return Vector2(_x, _y);
    }
    Vector2 Clamp(float magnitude) {
        if (GetMagnitude() >= magnitude) {
            return (Normalise() * magnitude);
        }
        else {
            return (*this);
        }
    }
    std::string ToString() {
        return ("(" + std::to_string(x) + "," + std::to_string(y) + ")");
    }
    SDL_Point ToSDLPoint() {
        SDL_Point output = { x,y };
        return output;
    }
};
struct JRrect {
    Vector2 points[4];
    JRrect() {
        for (int i = 0; i < 4; i++) {
            points[i] = Vector2::zero();
        }
    }
    JRrect(Vector2 a, Vector2 b, Vector2 c, Vector2 d) {
        points[0] = a;
        points[1] = b;
        points[2] = c;
        points[3] = d;
    }

    static JRrect RotateAroundPoint(JRrect rect,float angleRAD, Vector2 centre) {
        for (int i = 0; i < 4;i++) {
            rect.points[i] = Vector2::RotateAroundPoint(rect.points[i], angleRAD, centre);
        }
        return rect;
    }

};
long double Lerp(long double a, long double b, long double fac);
#endif // !USE_GAMEMATH


