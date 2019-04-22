//
// Created by liuqian8 on 2019/4/17.
//

#pragma once

struct Vector2
{
    // Default Constructor
    Vector2()
    {
        X = 0.0f;
        Y = 0.0f;
    }
    // Variable Set Constructor
    Vector2(float X_, float Y_)
    {
        X = X_;
        Y = Y_;
    }
    // Bool Equals Operator Overload
    bool operator==(const Vector2& other) const
    {
        return (this->X == other.X && this->Y == other.Y);
    }
    // Bool Not Equals Operator Overload
    bool operator!=(const Vector2& other) const
    {
        return !(this->X == other.X && this->Y == other.Y);
    }
    // Addition Operator Overload
    Vector2 operator+(const Vector2& right) const
    {
        return Vector2(this->X + right.X, this->Y + right.Y);
    }
    // Subtraction Operator Overload
    Vector2 operator-(const Vector2& right) const
    {
        return Vector2(this->X - right.X, this->Y - right.Y);
    }
    // Float Multiplication Operator Overload
    Vector2 operator*(const float& other) const
    {
        return Vector2(this->X *other, this->Y * other);
    }

    // Positional Variables
    float X;
    float Y;
};