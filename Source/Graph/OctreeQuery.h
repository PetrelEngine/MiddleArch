//
// Created by liuqian8 on 2019/7/24.
//
#pragma once
#include "BoundingBox.h"
#include "Drawable.h"
#include "Frustum.h"
class Drawable;
class Node;
class OctreeQuery
{
public:
    OctreeQuery(std::vector<Drawable*>& result, unsigned char drawableFlags, unsigned viewMask) :
            result_(result),
            drawableFlags_(drawableFlags),
            viewMask_(viewMask)
    {
    }

    virtual ~OctreeQuery()
    {
    }

//    virtual Intersection testOctant(const BoundingBox& box, bool inside) = 0;
//
//    virtual void testDrawables(Drawable** start, Drawable** end, bool inside) = 0;

    std::vector<Drawable*>& result_;

    unsigned char drawableFlags_;

    unsigned viewMask_;

private:
    OctreeQuery(const OctreeQuery& rhs);

    OctreeQuery& operator =(const OctreeQuery& rhs);
};

class PointOctreeQuery : public OctreeQuery
{
    PointOctreeQuery(std::vector<Drawable*>& result, const glm::vec3& point, unsigned char drawableFlags = DRAWABLE_ANY,
                     unsigned viewMask = DEFAULT_VIEWMASK) :
            OctreeQuery(result, drawableFlags, viewMask),
            point_(point)
    {
    }

//    virtual Intersection testOctant(const BoundingBox& box, bool inside) override;
//
//    virtual void testDrawables(Drawable** start, Drawable** end, bool inside) override;

    glm::vec3 point_;
};


class BoxOctreeQuery : public OctreeQuery
{
public:
/// Construct with bounding box and query parameters.
    BoxOctreeQuery(std::vector<Drawable*>& result, const BoundingBox& box, unsigned char drawableFlags = DRAWABLE_ANY,
                   unsigned viewMask = DEFAULT_VIEWMASK) :
            OctreeQuery(result, drawableFlags, viewMask),
            box_(box)
    {
    }

//    virtual Intersection testOctant(const BoundingBox& box, bool inside) override;
//
//    virtual void testDrawables(Drawable** start, Drawable** end, bool inside) override;


    BoundingBox box_;
};

class  FrustumOctreeQuery : public OctreeQuery
{
public:
    FrustumOctreeQuery(std::vector<Drawable*>& result,Frustum* frustum, unsigned char drawableFlags = DRAWABLE_ANY,
        unsigned viewMask = DEFAULT_VIEWMASK) :
        OctreeQuery(result, drawableFlags, viewMask),
        frustum_(frustum)
    {
    }

//    virtual Intersection testOctant(const BoundingBox& box, bool inside) override;
//
//    virtual void testDrawables(Drawable** start, Drawable** end, bool inside) override;

    /// Frustum.
    Frustum* frustum_;
};