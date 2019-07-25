//
// Created by liuqian8 on 2019/7/24.
//
#include "common.hpp"
#include "BoundingBox.h"
#include "Frustum.h"

void BoundingBox::define(const std::vector<glm::vec3> vertices, unsigned count)
{
    clear();

    if (!count)
        return;

    merge(vertices, count);
}

void BoundingBox::define(const Frustum& frustum)
{
    clear();
//    define(frustum.vertices_, NUM_FRUSTUM_VERTICES);
}

void BoundingBox::merge(const Frustum& frustum)
{
//    merge(frustum.vertices_, NUM_FRUSTUM_VERTICES);
}

void BoundingBox::merge(const std::vector<glm::vec3> vertices, unsigned count)
{
    while (count--)
        merge(vertices[count]);
}

void BoundingBox::transform(const glm::mat3& transform)
{
//    *this = Transformed(Matrix3x4(transform));
}

float BoundingBox::distanceToPoint(const glm::vec3& point) const
{
    const glm::vec3 offset = center() - point;
    const glm::vec3 absOffset(abs(offset.x), abs(offset.y), abs(offset.z));

    return glm::max(glm::vec3(0,0,0),absOffset - halfSize()).length();
}

void BoundingBox::clip(const BoundingBox& box)
{
    if (box.min_.x > min_.x)
        min_.x = box.min_.x;
    if (box.max_.x < max_.x)
        max_.x = box.max_.x;
    if (box.min_.y > min_.y)
        min_.y = box.min_.y;
    if (box.max_.y < max_.y)
        max_.y = box.max_.y;
    if (box.min_.z > min_.z)
        min_.z = box.min_.z;
    if (box.max_.z < max_.z)
        max_.z = box.max_.z;

    if (min_.x > max_.x || min_.y > max_.y || min_.z > max_.z)
    {
        min_ = glm::vec3(M_INFINITY, M_INFINITY, M_INFINITY);
        max_ = glm::vec3(-M_INFINITY, -M_INFINITY, -M_INFINITY);
    }
}