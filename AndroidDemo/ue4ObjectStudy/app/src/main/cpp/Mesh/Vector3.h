//
// Created by liuqian8 on 2019/4/17.
//
#pragma once

struct Vector3
{
    // Default Constructor
    Vector3()
    {
        X = 0.0f;
        Y = 0.0f;
        Z = 0.0f;
    }
    // Variable Set Constructor
    Vector3(float X_, float Y_, float Z_)
    {
        X = X_;
        Y = Y_;
        Z = Z_;
    }
    // Bool Equals Operator Overload
    bool operator==(const Vector3& other) const
    {
        return (this->X == other.X && this->Y == other.Y && this->Z == other.Z);
    }
    // Bool Not Equals Operator Overload
    bool operator!=(const Vector3& other) const
    {
        return !(this->X == other.X && this->Y == other.Y && this->Z == other.Z);
    }
    // Addition Operator Overload
    Vector3 operator+(const Vector3& right) const
    {
        return Vector3(this->X + right.X, this->Y + right.Y, this->Z + right.Z);
    }
    // Subtraction Operator Overload
    Vector3 operator-(const Vector3& right) const
    {
        return Vector3(this->X - right.X, this->Y - right.Y, this->Z - right.Z);
    }
    // Float Multiplication Operator Overload
    Vector3 operator*(const float& other) const
    {
        return Vector3(this->X * other, this->Y * other, this->Z * other);
    }
    // Float Division Operator Overload
    Vector3 operator/(const float& other) const
    {
        return Vector3(this->X / other, this->Y / other, this->Z / other);
    }

    // Positional Variables
    float X;
    float Y;
    float Z;
};