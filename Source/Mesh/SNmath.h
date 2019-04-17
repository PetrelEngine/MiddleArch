//
// Created by liuqian8 on 2019/4/17.
//

#pragma once

#include <math.h>
#include "Vector3.h"

namespace mathSN
{
    // Vector3 Cross Product
    Vector3 CrossV3(const Vector3 a, const Vector3 b)
    {
        return Vector3(a.Y * b.Z - a.Z * b.Y,
                       a.Z * b.X - a.X * b.Z,
                       a.X * b.Y - a.Y * b.X);
    }

    // Vector3 Magnitude Calculation
    float MagnitudeV3(const Vector3 in)
    {
        return (sqrtf(powf(in.X, 2) + powf(in.Y, 2) + powf(in.Z, 2)));
    }

    // Vector3 DotProduct
    float DotV3(const Vector3 a, const Vector3 b)
    {
        return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
    }

    // Angle between 2 Vector3 Objects
    float AngleBetweenV3(const Vector3 a, const Vector3 b)
    {
        float angle = DotV3(a, b);
        angle /= (MagnitudeV3(a) * MagnitudeV3(b));
        return angle = acosf(angle);
    }

    // Projection Calculation of a onto b
    Vector3 ProjV3(const Vector3 a, const Vector3 b)
    {
        Vector3 bn = b / MagnitudeV3(b);
        return bn * DotV3(a, bn);
    }
}
