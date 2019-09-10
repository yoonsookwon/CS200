#include "pch.h"
//#include <CS230/math/matrix3.hpp>
//#include <CS230/math/vector2.hpp>
#include  "matrix3.hpp"
#include  "vector2.hpp"
#include  "vector3.hpp"
#include <cassert>
#include <iostream>
#include <limits>
/*------------------------------------------------------------------------
Name: yoonsoo.kwon
Assignment number: 1
Course name: CS230
Term: Spring Year(2019)
------------------------------------------------------------------------*/
namespace CS230
{
    matrix3::matrix3() noexcept
    {
        for (int column = 0; column < 3; ++column)
        {
            for (int row = 0; row < 3; ++row)
            {
                elements[column][row] = 0;
            }
        }
    }
    matrix3::matrix3(vector3 first_column, vector3 second_column, vector3 third_column) noexcept
    {
        elements[0][0] = first_column.x;
        elements[1][0] = second_column.x;
        elements[2][0] = third_column.x;

        elements[0][1] = first_column.y;
        elements[1][1] = second_column.y;
        elements[2][1] = third_column.y;

        elements[0][2] = first_column.z;
        elements[1][2] = second_column.z;
        elements[2][2] = third_column.z;
    }
    matrix3::matrix3(float column0_row0, float column0_row1, float column0_row2, float column1_row0, float column1_row1,
                     float column1_row2, float column2_row0, float column2_row1, float column2_row2) noexcept
    {
        elements[0][0] = column0_row0;
        elements[1][0] = column1_row0;
        elements[2][0] = column2_row0;

        elements[0][1] = column0_row1;
        elements[1][1] = column1_row1;
        elements[2][1] = column2_row1;

        elements[0][2] = column0_row2;
        elements[1][2] = column1_row2;
        elements[2][2] = column2_row2;
    }
    float matrix3::operator()(int column, int row) const noexcept
    {
        // To assert column and row are greater than -1 and smaller than 3
        assert(column >= 0 && column < 3);
        assert(row >= 0 && row < 3);

        return elements[column][row];
    }

    float& matrix3::operator()(int column, int row) noexcept
    {
        // To assert column and row are greater than -1 and smaller than 3
        assert(column >= 0 && column < 3);
        assert(row >= 0 && row < 3);

        return elements[column][row];
    }

    matrix3 operator*(const matrix3& m1, const matrix3& m2) noexcept
    {
        matrix3 multiply;
        // triple For Loop to calculate of both matrixs
        for (int row = 0; row < 3; row++)
        {
            for (int column = 0; column < 3; column++)
            {
                for (int k = 0; k < 3; k++)
                {
                    multiply.elements[column][row] += m1.elements[k][row] * m2.elements[column][k];
                }
            }
        }
        return multiply;
    }
    void operator*=(matrix3& m1, const matrix3& m2) noexcept
    {
        // I'm using the matrix operator what i made above
        m1 = m1 * m2;
    }
    vector3 operator*(const matrix3& m, vector3 v) noexcept
    {
        return vector3((m.elements[0][0] * v.x) + (m.elements[1][0] * v.y) + (m.elements[2][0] * v.z),
                       (m.elements[0][1] * v.x) + (m.elements[1][1] * v.y) + (m.elements[2][1] * v.z),
                       (m.elements[0][2] * v.x) + (m.elements[1][2] * v.y) + (m.elements[2][2] * v.z));
    }
    matrix3 MATRIX3::transpose(const matrix3& m) noexcept
    {
        matrix3 transpose;

        vector3 v1 = {m.elements[0][0], m.elements[0][1], m.elements[0][2]};
        vector3 v2 = {m.elements[1][0], m.elements[1][1], m.elements[1][2]};
        vector3 v3 = {m.elements[2][0], m.elements[2][1], m.elements[2][2]};

        transpose.elements[0][0] = v1.x;
        transpose.elements[1][0] = v1.y;
        transpose.elements[2][0] = v1.z;

        transpose.elements[0][1] = v2.x;
        transpose.elements[1][1] = v2.y;
        transpose.elements[2][1] = v2.z;

        transpose.elements[0][2] = v3.x;
        transpose.elements[1][2] = v3.y;
        transpose.elements[2][2] = v3.z;

        return transpose;
    }
    matrix3 MATRIX3::build_rotation(float angle_in_radians) noexcept
    {
        matrix3 rotate;

        float cosine = cos(angle_in_radians);
        float sine   = sin(angle_in_radians);

        rotate.elements[0][0] = cosine;
        rotate.elements[1][0] = -sine;
        rotate.elements[2][0] = 0.f;

        rotate.elements[0][1] = sine;
        rotate.elements[1][1] = cosine;
        rotate.elements[2][1] = 0.f;

        rotate.elements[0][2] = 0.f;
        rotate.elements[1][2] = 0.f;
        rotate.elements[2][2] = 1.f;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (fabs(rotate.elements[i][j]) <= std::numeric_limits<float>::epsilon())
                    rotate.elements[i][j] = 0.0f;
            }
        }
        return rotate;
    }
    matrix3 MATRIX3::build_identity() noexcept { return matrix3(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f); }

    matrix3 MATRIX3::build_scale(float scale_x, float scale_y) noexcept
    {
        return matrix3(scale_x, 0.f, 0.f, 0.f, scale_y, 0.f, 0.f, 0.f, 1.f);
    }

    matrix3 MATRIX3::build_scale(float scale) noexcept
    {
        return build_scale(scale, scale);
    }

    matrix3 MATRIX3::build_scale(const vector2& scale) noexcept
    { 
        return build_scale(scale.x, scale.y);
    }

    matrix3 MATRIX3::build_translation(float translate_x, float translate_y) noexcept
    {
        return matrix3(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, translate_x, translate_y, 1.f);
    }

    matrix3 MATRIX3::build_translation(const vector2& translation) noexcept
    {
        return build_translation(translation.x, translation.y);
    }
}
