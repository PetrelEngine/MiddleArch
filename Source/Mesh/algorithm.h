//
// Created by liuqian8 on 2019/4/17.
//
#pragma once

#include <vector>
#include "Vector3.h"
#include "mathSN.h"
#include <string>
namespace algorithm
{
    // Vector3 Multiplication Opertor Overload
    Vector3 operator*(const float& left, const Vector3& right)
    {
        return Vector3(right.X * left, right.Y * left, right.Z * left);
    }

    // A test to see if P1 is on the same side as P2 of a line segment ab
    bool SameSide(Vector3 p1, Vector3 p2, Vector3 a, Vector3 b)
    {
        Vector3 cp1 = mathSN::CrossV3(b - a, p1 - a);
        Vector3 cp2 = mathSN::CrossV3(b - a, p2 - a);

        if (mathSN::DotV3(cp1, cp2) >= 0)
            return true;
        else
            return false;
    }

    // Generate a cross produect normal for a triangle
    Vector3 GenTriNormal(Vector3 t1, Vector3 t2, Vector3 t3)
    {
        Vector3 u = t2 - t1;
        Vector3 v = t3 - t1;

        Vector3 normal = mathSN::CrossV3(u,v);

        return normal;
    }

    // Check to see if a Vector3 Point is within a 3 Vector3 Triangle
    bool inTriangle(Vector3 point, Vector3 tri1, Vector3 tri2, Vector3 tri3)
    {
        // Test to see if it is within an infinite prism that the triangle outlines.
        bool within_tri_prisim = SameSide(point, tri1, tri2, tri3) && SameSide(point, tri2, tri1, tri3)
                                 && SameSide(point, tri3, tri1, tri2);

        // If it isn't it will never be on the triangle
        if (!within_tri_prisim)
            return false;

        // Calulate Triangle's Normal
        Vector3 n = GenTriNormal(tri1, tri2, tri3);

        // Project the point onto this normal
        Vector3 proj = mathSN::ProjV3(point, n);

        // If the distance from the triangle to the point is 0
        //	it lies on the triangle
        if (mathSN::MagnitudeV3(proj) == 0)
            return true;
        else
            return false;
    }

    // Split a String into a string array at a given token
    inline void split(const std::string &in,
                      std::vector<std::string> &out,
                      std::string token)
    {
        out.clear();

        std::string temp;

        for (int i = 0; i < int(in.size()); i++)
        {
            std::string test = in.substr(i, token.size());

            if (test == token)
            {
                if (!temp.empty())
                {
                    out.push_back(temp);
                    temp.clear();
                    i += (int)token.size() - 1;
                }
                else
                {
                    out.push_back("");
                }
            }
            else if (i + token.size() >= in.size())
            {
                temp += in.substr(i, token.size());
                out.push_back(temp);
                break;
            }
            else
            {
                temp += in[i];
            }
        }
    }

    // Get tail of string after first token and possibly following spaces
    inline std::string tail(const std::string &in)
    {
        size_t token_start = in.find_first_not_of(" \t");
        size_t space_start = in.find_first_of(" \t", token_start);
        size_t tail_start = in.find_first_not_of(" \t", space_start);
        size_t tail_end = in.find_last_not_of(" \t");
        if (tail_start != std::string::npos && tail_end != std::string::npos)
        {
            return in.substr(tail_start, tail_end - tail_start + 1);
        }
        else if (tail_start != std::string::npos)
        {
            return in.substr(tail_start);
        }
        return "";
    }

    // Get first token of string
    inline std::string firstToken(const std::string &in)
    {
        if (!in.empty())
        {
            size_t token_start = in.find_first_not_of(" \t");
            size_t token_end = in.find_first_of(" \t", token_start);
            if (token_start != std::string::npos && token_end != std::string::npos)
            {
                return in.substr(token_start, token_end - token_start);
            }
            else if (token_start != std::string::npos)
            {
                return in.substr(token_start);
            }
        }
        return "";
    }

    // Get element at given index position
    template <class T>
    inline const T & getElement(const std::vector<T> &elements, std::string &index)
    {
        int idx = std::stoi(index);
        if (idx < 0)
            idx = int(elements.size()) + idx;
        else
            idx--;
        return elements[idx];
    }
}
