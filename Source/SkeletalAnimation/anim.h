//
// Created by liuqian8 on 2019/3/14.
//

#pragma once

// ---------------------------------------------------------------------------
//#include "vector3.h"
//#include "quaternion.h"

#include <glm/vec3.hpp>
#include <glm/fwd.hpp>
#include <glm/gtx/simd_quat.hpp>

/** A time-value pair specifying a certain 3D vector for the given time. */
struct aiVectorKey
{
    /** The time of this key */
    double mTime;

    /** The value of this key */
//    aiVector3D mValue;
    glm::vec3 mValue;


    /// @brief  The default constructor.
    aiVectorKey()
            : mTime( 0.0 )
            , mValue() {
        // empty
    }

    /// @brief  Construction from a given time and key value.

//    aiVectorKey(double time, const aiVector3D& value)
    aiVectorKey(double time, const glm::vec3& value)
            : mTime( time )
            , mValue( value ) {
        // empty
    }

//    typedef aiVector3D elem_type;
    typedef glm::vec3 elem_type;

    // Comparison operators. For use with std::find();
    bool operator == (const aiVectorKey& rhs) const {
        return rhs.mValue == this->mValue;
    }
    bool operator != (const aiVectorKey& rhs ) const {
        return rhs.mValue != this->mValue;
    }

    // Relational operators. For use with std::sort();
    bool operator < (const aiVectorKey& rhs ) const {
        return mTime < rhs.mTime;
    }
    bool operator > (const aiVectorKey& rhs ) const {
        return mTime > rhs.mTime;
    }
};

// ---------------------------------------------------------------------------
/** A time-value pair specifying a rotation for the given time.
 *  Rotations are expressed with quaternions. */
struct aiQuatKey
{
    /** The time of this key */
    double mTime;

    /** The value of this key */
//    aiQuaternion mValue;
    glm::quat mValue;

    aiQuatKey()
            : mTime( 0.0 )
            , mValue() {
        // empty
    }

    /** Construction from a given time and key value */
//    aiQuatKey(double time, const aiQuaternion& value)
    aiQuatKey(double time, const glm::quat& value)
            :   mTime   (time)
            ,   mValue  (value)
    {}

//    typedef aiQuaternion elem_type;
    typedef glm::quat elem_type;

    // Comparison operators. For use with std::find();
    bool operator == (const aiQuatKey& rhs ) const {
        return rhs.mValue == this->mValue;
    }
    bool operator != (const aiQuatKey& rhs ) const {
        return rhs.mValue != this->mValue;
    }

    // Relational operators. For use with std::sort();
    bool operator < (const aiQuatKey& rhs ) const {
        return mTime < rhs.mTime;
    }
    bool operator > (const aiQuatKey& rhs ) const {
        return mTime > rhs.mTime;
    }
};
