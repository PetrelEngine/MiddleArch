//
// Created by liuqian8 on 2019/3/14.
//
#pragma once
#include <string>
#include <cmath>

using namespace std;
// ----------------------------------------------------------------------------------
/** Represents a color in Red-Green-Blue space.
*/
struct aiColor3D
{
    aiColor3D ()  : r(0.0f), g(0.0f), b(0.0f) {}
    aiColor3D (float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
    explicit aiColor3D (float _r) : r(_r), g(_r), b(_r) {}
    aiColor3D (const aiColor3D& o) : r(o.r), g(o.g), b(o.b) {}

    /** Component-wise comparison */
    // TODO: add epsilon?
    bool operator == (const aiColor3D& other) const
    {return r == other.r && g == other.g && b == other.b;}

    /** Component-wise inverse comparison */
    // TODO: add epsilon?
    bool operator != (const aiColor3D& other) const
    {return r != other.r || g != other.g || b != other.b;}

    /** Component-wise comparison */
    // TODO: add epsilon?
    bool operator < (const aiColor3D& other) const {
        return r < other.r || ( r == other.r && (g < other.g || (g == other.g && b < other.b ) ) );
    }

    /** Component-wise addition */
    aiColor3D operator+(const aiColor3D& c) const {
        return aiColor3D(r+c.r,g+c.g,b+c.b);
    }

    /** Component-wise subtraction */
    aiColor3D operator-(const aiColor3D& c) const {
        return aiColor3D(r-c.r,g-c.g,b-c.b);
    }

    /** Component-wise multiplication */
    aiColor3D operator*(const aiColor3D& c) const {
        return aiColor3D(r*c.r,g*c.g,b*c.b);
    }

    /** Multiply with a scalar */
    aiColor3D operator*(float f) const {
        return aiColor3D(r*f,g*f,b*f);
    }

    /** Access a specific color component */
    float operator[](unsigned int i) const {
        return *(&r + i);
    }

    /** Access a specific color component */
    float& operator[](unsigned int i) {
        if ( 0 == i ) {
            return r;
        } else if ( 1 == i ) {
            return g;
        } else if ( 2 == i ) {
            return b;
        }
        return r;
    }

    /** Check whether a color is black */
    bool IsBlack() const {
        static const float epsilon = float(10e-3);
        return std::fabs( r ) < epsilon && std::fabs( g ) < epsilon && std::fabs( b ) < epsilon;
    }

    //! Red, green and blue color values
    float r, g, b;
};  // !struct aiColor3D

