//
// Created by liuqian8 on 2019/7/24.
//
#pragma once
#include <cmath>

#undef M_PI
static const float M_PI = 3.14159265358979323846264338327950288f;

static const float M_INFINITY = (float)HUGE_VAL;
static const unsigned NUM_FRUSTUM_VERTICES = 8;
enum Intersection
{
    OUTSIDE,
    INTERSECTS,
    INSIDE
};

