//
// Created by liuqian8 on 2019/5/21.
//
#include <cmath>
#include "Sphere.h"
#include "Common.h"
Sphere::Sphere()
{
    Data_.clear();
    Positions_.clear();
    Uv_.clear();
    Normals_.clear();
    Indices_.clear();
    ProductSphere();
}

void Sphere::ProductSphere() {
    const unsigned int X_SEGMENTS = 64;
    const unsigned int Y_SEGMENTS = 64;
    const float PI = 3.14159265359f;
    for (unsigned int y = 0; y <= Y_SEGMENTS; ++y) {
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
            float xSegment = (float) x / (float) X_SEGMENTS;
            float ySegment = (float) y / (float) Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            Positions_.push_back(glm::vec3(xPos, yPos, zPos));
            Uv_.push_back(glm::vec2(xSegment, ySegment));
            Normals_.push_back(glm::vec3(xPos, yPos, zPos));
        }
    }

    bool oddRow = false;
    for (int y = 0; y < Y_SEGMENTS; ++y) {
        if (!oddRow) // even rows: y == 0, y == 2; and so on
        {
            for (int x = 0; x <= X_SEGMENTS; ++x) {
                Indices_.push_back(y * (X_SEGMENTS + 1) + x);
                Indices_.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            }
        } else {
            for (int x = X_SEGMENTS; x >= 0; --x) {
                Indices_.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                Indices_.push_back(y * (X_SEGMENTS + 1) + x);
            }
        }
        oddRow = !oddRow;
    }
    indexCount = Indices_.size();

    for (int i = 0; i < Positions_.size(); ++i) {
        Data_.push_back(Positions_[i].x);
        Data_.push_back(Positions_[i].y);
        Data_.push_back(Positions_[i].z);
        if (Uv_.size() > 0) {
            Data_.push_back(Uv_[i].x);
            Data_.push_back(Uv_[i].y);
        }
        if (Normals_.size() > 0) {
            Data_.push_back(Normals_[i].x);
            Data_.push_back(Normals_[i].y);
            Data_.push_back(Normals_[i].z);
        }
    }
}

Sphere::~Sphere()
{

}
