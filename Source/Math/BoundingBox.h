//
// Created by liuqian8 on 2019/7/24.
//
#pragma once
#include "MathDefs.h"
#include "vec3.hpp"
#include "mat3x3.hpp"
#include <vector>
class Frustum;

class BoundingBox
{
public:
    BoundingBox() :
            min_(M_INFINITY, M_INFINITY, M_INFINITY),
            max_(-M_INFINITY, -M_INFINITY, -M_INFINITY)
    {
    }

    BoundingBox(const BoundingBox& box) :
            min_(box.min_),
            max_(box.max_)
    {
    }

    BoundingBox(const glm::vec3& min, const glm::vec3& max) :
            min_(min),
            max_(max)
    {
    }

    BoundingBox(float min, float max) :
            min_(glm::vec3(min, min, min)),
            max_(glm::vec3(max, max, max))
    {
    }

    void define(const BoundingBox& box)
    {
        define(box.min_, box.max_);
    }

    void define(const glm::vec3& min, const glm::vec3& max)
    {
        min_ = min;
        max_ = max;
    }

    void define(float min, float max)
    {
        min_ = glm::vec3(min, min, min);
        max_ = glm::vec3(max, max, max);
    }

    void define(const glm::vec3& point)
    {
        min_ = max_ = point;
    }

    void merge(const glm::vec3& point)
    {
        if (point.x < min_.x)
            min_.x = point.x;
        if (point.y < min_.y)
            min_.y = point.y;
        if (point.z < min_.z)
            min_.z = point.z;
        if (point.x > max_.x)
            max_.x = point.x;
        if (point.y > max_.y)
            max_.y = point.y;
        if (point.z > max_.z)
            max_.z = point.z;
    }

    void merge(const BoundingBox& box)
    {
        if (box.min_.x < min_.x)
            min_.x = box.min_.x;
        if (box.min_.y < min_.y)
            min_.y = box.min_.y;
        if (box.min_.z < min_.z)
            min_.z = box.min_.z;
        if (box.max_.x > max_.x)
            max_.x = box.max_.x;
        if (box.max_.y > max_.y)
            max_.y = box.max_.y;
        if (box.max_.z > max_.z)
            max_.z = box.max_.z;
    }

    void define(const std::vector<glm::vec3> vertices, unsigned count);

    void define(const Frustum& frustum);

    void merge(const std::vector<glm::vec3> vertices, unsigned count);

    void merge(const Frustum& frustum);

    void clip(const BoundingBox& box);

    void transform(const glm::mat3& transform);

    void clear()
    {
        min_ = glm::vec3(M_INFINITY, M_INFINITY, M_INFINITY);
        max_ = glm::vec3(-M_INFINITY, -M_INFINITY, -M_INFINITY);
    }

    bool defined() const
    {
        return min_.x != M_INFINITY;
    }

    glm::vec3 center() const { return (max_ + min_) * 0.5f; }

    glm::vec3 size() const { return max_ - min_; }

    glm::vec3 halfSize() const { return (max_ - min_) * 0.5f; }

    float distanceToPoint(const glm::vec3& point) const;

    Intersection isInside(const glm::vec3& point) const
    {
        if (point.x < min_.x || point.x > max_.x || point.y < min_.y || point.y > max_.y ||
            point.z < min_.z || point.z > max_.z)
            return OUTSIDE;
        else
            return INSIDE;
    }

    Intersection isInside(const BoundingBox& box) const
    {
        if (box.max_.x < min_.x || box.min_.x > max_.x || box.max_.y < min_.y || box.min_.y > max_.y ||
            box.max_.z < min_.z || box.min_.z > max_.z)
            return OUTSIDE;
        else if (box.min_.x < min_.x || box.max_.x > max_.x || box.min_.y < min_.y || box.max_.y > max_.y ||
                 box.min_.z < min_.z || box.max_.z > max_.z)
            return INTERSECTS;
        else
            return INSIDE;
    }

    Intersection isInsideFast(const BoundingBox& box) const
    {
        if (box.max_.x < min_.x || box.min_.x > max_.x || box.max_.y < min_.y || box.min_.y > max_.y ||
            box.max_.z < min_.z || box.min_.z > max_.z)
            return OUTSIDE;
        else
            return INSIDE;
    }

    glm::vec3 min_;
    float dummyMin_;

    glm::vec3 max_;
    float dummyMax_;
};
