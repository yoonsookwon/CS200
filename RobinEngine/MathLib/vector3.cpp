#include "pch.h"
//#include <CS230/math/angles.hpp>
//#include <CS230/math/vector3.hpp>
#include "vector3.hpp"
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
    vector3::vector3() noexcept
    {
        x = 0;
        y = 0;
        z = 0;
    }

    vector3::vector3(float repeated_float) noexcept
    {
        x = repeated_float;
        y = repeated_float;
        z = repeated_float;
    }
    vector3::vector3(float fx, float fy, float fz) noexcept
    {
        x = fx;
        y = fy;
        z = fz;
    }
    void operator+=(vector3& v, const vector3& adding_vector) noexcept
    {
        v.x = v.x + adding_vector.x;
        v.y = v.y + adding_vector.y;
        v.z = v.z + adding_vector.z;
    }

    void operator-=(vector3& v, const vector3& subtracting_vector) noexcept
    {
        v.x = v.x - subtracting_vector.x;
        v.y = v.y - subtracting_vector.y;
        v.z = v.z - subtracting_vector.z;
    }

    void operator*=(vector3& v, float scale) noexcept
    {
        v.x = v.x * scale;
        v.y = v.y * scale;
        v.z = v.z * scale;
    }

    void operator/=(vector3& v, float divisor) noexcept
    {

        // to assert divisior is not 0, and it's not going to excute this function if the divisor value is 0
        assert(divisor != 0.0f);

        v.x /=  divisor;
        v.y /= divisor;
        v.z /= divisor;
    }

    vector3 operator-(const vector3& v) noexcept
    {
        return vector3(v.x * -1, v.y * -1, v.z * -1);
    }

    vector3 operator+(const vector3& v1, const vector3& v2) noexcept
    {
        return vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    }

    vector3 operator-(const vector3& v1, const vector3& v2) noexcept
    {
        return vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    }

    vector3 operator*(const vector3& v, float scale) noexcept
    {
       return vector3(scale * v.x, scale * v.y, scale * v.z);
    }

    vector3 operator*(float scale, const vector3& v) noexcept
    {
        return vector3(v.x * scale, v.y * scale, v.z * scale);
    }

    vector3 operator/(const vector3& v, float divisor) noexcept
    {
        // to assert divisior is not 0, and it's not going to excute this function if the divisor value is 0
        assert(divisor != 0.0f);
        return vector3(v.x / divisor, v.y / divisor, v.z / divisor);
    }

    [[nodiscard]] bool operator==(const vector3& v1, const vector3& v2) noexcept
    {
        // use epsilon() to get Rounding Error Occurrence, 
        //it's calculated to equal value if the error difference of the value is smaller than epsilon
        return fabs(v1.x - v2.x) <= std::numeric_limits<float>::epsilon() &&
               fabs(v1.y - v2.y) <= std::numeric_limits<float>::epsilon() &&
               fabs(v1.z - v2.z) <= std::numeric_limits<float>::epsilon();
    }

    [[nodiscard]] bool operator!=(const vector3& v1, const vector3& v2) noexcept
    {
        // use epsilon() to get Rounding Error Occurrence,
        // it's calculated to different value if the error difference of the value is greater than epsilon
        return !(v1 == v2);
    }

    [[nodiscard]] float dot(vector3 a, vector3 b) noexcept
    {
        float dotResult = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
        return dotResult;
    }
    vector3 cross(vector3 a, vector3 b) noexcept { 
        return vector3((a.y * b.z - a.z * b.y), (a.z * b.x - a.x * b.z), (a.x * b.y - a.y * b.x));
	}

    [[nodiscard]] float magnitude(vector3 a) noexcept { return sqrt(dot(a,a)); }

    [[nodiscard]] float magnitude_squared(vector3 a) noexcept { return dot(a,a); }

    vector3 normalize(vector3 a) noexcept
    {
        float magnitudeVal = magnitude(a);
        assert(magnitudeVal != 0);
        return vector3(a/magnitudeVal);
    }

    [[nodiscard]] float distance_between(vector3 a, vector3 b) noexcept
    {
        return sqrt(distance_between_squared(a, b));
    }

    [[nodiscard]] float distance_between_squared(vector3 a, vector3 b) noexcept
    {
        float xDistance = fabs((a.x - b.x) * (a.x - b.x));
        float yDistance = fabs((a.y - b.y) * (a.y - b.y));
        float zDistance = fabs((a.z - b.z) * (a.z - b.z));

        return xDistance + yDistance + zDistance;
    }

	[[nodiscard]] float angle_between(vector3 a, vector3 b) noexcept
    {
        assert(magnitude(a) * magnitude(b) != 0);
        float radian = dot(a, b) / (magnitude(a) * magnitude(b));

        return acos(radian);
    }
}
