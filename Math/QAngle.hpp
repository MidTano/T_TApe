#pragma once
#include <cmath>
#include <algorithm>
#include <limits>

#include "Vector2d.hpp"
#include "Vector3d.hpp"

enum class AngleSmoothType : int{
    LerpSmoothing = 0,
    LinearSmoothing = 1,
    ExponentialSmoothing = 2,
    SCurveSmoothing = 3,
    BezierSmoothing = 4,
    AccelerationSmoothing = 5,
    JerkLimitedSmoothing = 6
};

struct QAngle {

    float x;
    float y;

    QAngle() : x(0), y(0) {}

    QAngle(float x, float y) : x(x), y(y) {}

    inline QAngle operator+(const QAngle& other) const {
        return QAngle(x + other.x, y + other.y);
    }

    inline QAngle operator-(const QAngle& other) const {
        return QAngle(x - other.x, y - other.y);
    }

    inline QAngle operator*(const float scalar) const {
        return QAngle(x * scalar, y * scalar);
    }

    inline QAngle operator/(const float scalar) const {
        return QAngle(x / scalar, y / scalar);
    }

    inline QAngle& operator+=(const QAngle& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    inline QAngle& operator-=(const QAngle& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    inline QAngle& operator*=(const float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    inline QAngle& operator/=(const float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    inline bool operator==(const QAngle& other) const
    {
        return x == other.x && y == other.y;
    }

    inline bool operator!=(const QAngle& other) const
    {
        return !(*this == other);
    }

    inline float dot(const QAngle& other) const {
        return x * other.x + y * other.y;
    }

    inline float length() const {
        return std::sqrt(x * x + y * y);
    }

    float distanceTo(const QAngle& other) const {
        return (other - *this).length();
    };

    inline QAngle& normalize() {
        float len = length();
        if (len > 0) {
            x /= len;
            y /= len;
        }
        return *this;
    }

    inline QAngle& clamp(float minVal, float maxVal) {
        x = std::clamp(x, minVal, maxVal);
        y = std::clamp(y, minVal, maxVal);

        return *this;
    }

    inline QAngle lerp(const QAngle& other, float t) const {
        return (*this) * (1.0f - t) + other * t;
    }

    // Fixed the fixAngle() function to have a faster implementation
    inline QAngle& fixAngle() {
        if (x > 89.0f) {
            x = 89.0f;
        }
        else if (x < -89.0f) {
            x = -89.0f;
        }

        while (y > 180.f)
            y -= 360.f;

        while (y < -180.f)
            y += 360.f;

        return *this;
    }

    // Simplified the isValid() function
    inline bool isValid() const {
        return std::isfinite(x) && std::isfinite(y);
    }

    inline static QAngle zero() {
        return QAngle(0, 0);
    }
}; 
