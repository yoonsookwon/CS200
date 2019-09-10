#include "pch.h"
//#include <CS230/math/angles.hpp>
//#include <CS230/math/vector2.hpp>
#include  "vector2.hpp"
#include <cassert>
#include <limits>
/*------------------------------------------------------------------------
Name: yoonsoo.kwon
Assignment number: 1
Course name: CS230
Term: Spring Year(2019)
------------------------------------------------------------------------*/

namespace CS230
{
    vector2::vector2() noexcept
    {
        x = 0;
        y = 0;
    }

    vector2::vector2(float repeated_float) noexcept
    {
        x = repeated_float;
        y = repeated_float;
    }

    vector2::vector2(float fx, float fy) noexcept
    {
        x = fx;
        y = fy;
    }

    void operator+=(vector2& v, const vector2& adding_vector) noexcept
    {
        v.x += adding_vector.x;
        v.y += adding_vector.y;
    }

    void operator-=(vector2& v, const vector2& subtracting_vector) noexcept
    {
        v.x -= subtracting_vector.x;
        v.y -= subtracting_vector.y;
    }

    void operator*=(vector2& v, float scale) noexcept
    {
        v.x *= scale;
        v.y *= scale;
    }

    void operator/=(vector2& v, float divisor) noexcept
    {
        // to assert divisior is not 0, and it's not going to excute this function if the divisor value is 0
        assert(divisor != 0.0f);

        v.x /= divisor;
        v.y /= divisor;
    }
    vector2 operator-(const vector2& v) noexcept { return vector2(-v.x, -v.y); }

    vector2 operator+(const vector2& v1, const vector2& v2) noexcept { return vector2(v1.x + v2.x, v1.y + v2.y); }

    vector2 operator-(const vector2& v1, const vector2& v2) noexcept { return vector2(v1.x - v2.x, v1.y - v2.y); }

    vector2 operator*(const vector2& v, float scale) noexcept { return vector2(scale * v.x, scale * v.y); }

    vector2 operator*(float scale, const vector2& v) noexcept { return vector2(v.x * scale, v.y * scale); }

    vector2 operator/(const vector2& v, float divisor) noexcept
    {
        // to assert divisior is not 0, and it's not going to excute this function if the divisor value is 0
        assert(divisor != 0.0f);
        return vector2(v.x / divisor, v.y / divisor);
    }

    [[nodiscard]] bool operator==(const vector2& v1, const vector2& v2) noexcept
    {
        // use epsilon() to get Rounding Error Occurrence,
        // it's calculated to equal value if the error difference of the value is smaller than epsilon
        return fabs(v1.x - v2.x) <= std::numeric_limits<float>::epsilon() &&
               fabs(v1.y - v2.y) <= std::numeric_limits<float>::epsilon();
    }

    [[nodiscard]] bool operator!=(const vector2& v1, const vector2& v2) noexcept
    {
        // use epsilon() to get Rounding Error Occurrence,
        // it's calculated to different value if the error difference of the value is greater than epsilon
        return !(v1 == v2);
    }

    [[nodiscard]] float dot(vector2 a, vector2 b) noexcept
    {
        float dotResult = (a.x * b.x) + (a.y * b.y);
        return dotResult;
    }

    vector2 perpendicular_to(vector2 a) noexcept { return vector2(-a.y, a.x); }

    [[nodiscard]] float magnitude(vector2 a) noexcept { return sqrt(dot(a, a)); }

    [[nodiscard]] float magnitude_squared(vector2 a) noexcept { return dot(a, a); }

    vector2 normalize(vector2 a) noexcept
    {
        float magnitudeVal = magnitude(a);
        assert(magnitudeVal != 0);
        return vector2(a / magnitudeVal);
    }

    [[nodiscard]] float distance_between(vector2 a, vector2 b) noexcept { return sqrt(distance_between_squared(a, b)); }

    [[nodiscard]] float distance_between_squared(vector2 a, vector2 b) noexcept
    {
        float xDistance = fabs((a.x - b.x) * (a.x - b.x));
        float yDistance = fabs((a.y - b.y) * (a.y - b.y));

        return xDistance + yDistance;
    }

    [[nodiscard]] float angle_between(vector2 a, vector2 b) noexcept
    {
        assert(magnitude(a) * magnitude(b) != 0);
        float radian = dot(a, b) / (magnitude(a) * magnitude(b));
        float result = acos(radian);

        return result;
    }

    vector2 rotate_by(float angle_in_radians, vector2 v) noexcept
    {
        vector2 rotated;
        float   cosine = cos(angle_in_radians);
        float   sine   = sin(angle_in_radians);

        rotated.x = (v.x * cosine) + (v.y * (-sine));
        rotated.y = (v.x * sine) + (v.y * cosine);

        return rotated;
    }
}
