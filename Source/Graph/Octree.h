//
// Created by liuqian8 on 2019/6/25.
//
#pragma once
#include "Component.h"
#include "BoundingBox.h"
#include "Drawable.h"
#include "OctreeQuery.h"
class Octree;
static const int NUM_OCTANTS = 8;
static const unsigned ROOT_INDEX = UINT_MAX;
class Octant
{
public:
    Octant(const BoundingBox& box, unsigned level, Octant* parent, Octree* root, unsigned index = ROOT_INDEX);

    virtual ~Octant();

    Octant* getOrCreateChild(unsigned index);

    void deleteChild(unsigned index);

    void insertDrawable(Drawable* drawable);

    bool checkDrawableFit(const BoundingBox& box) const;

    void addDrawable(Drawable* drawable)
    {
//        drawable->SetOctant(this);
//        drawables_.Push(drawable);
//        incDrawableCount();
    }

    void removeDrawable(Drawable* drawable, bool resetOctant = true)
    {
//        if (drawables_.Remove(drawable))
//        {
//            if (resetOctant)
//                drawable->SetOctant(nullptr);
//            decDrawableCount();
//        }
    }

    const BoundingBox& getWorldBoundingBox() const { return worldBoundingBox_; }

    const BoundingBox& getCullingBox() const { return cullingBox_; }

    unsigned getLevel() const { return level_; }

    Octant* getParent() const { return parent_; }

    Octree* getRoot() const { return root_; }

    unsigned getNumDrawables() const { return numDrawables_; }

    bool isEmpty() { return numDrawables_ == 0; }

    void resetRoot();

//    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

protected:
    void Initialize(const BoundingBox& box);

    void GetDrawablesInternal(OctreeQuery& query, bool inside) const;

//    void GetDrawablesInternal(RayOctreeQuery& query) const;
//
//    void GetDrawablesOnlyInternal(RayOctreeQuery& query, std::vector<Drawable*>& drawables) const;

    void incDrawableCount()
    {
        ++numDrawables_;
        if (parent_)
            parent_->incDrawableCount();
    }

    void decDrawableCount()
    {
        Octant* parent = parent_;

        --numDrawables_;
        if (!numDrawables_)
        {
            if (parent)
                parent->deleteChild(index_);
        }

        if (parent)
            parent->decDrawableCount();
    }

    BoundingBox worldBoundingBox_;

    BoundingBox cullingBox_;

    std::vector<Drawable*> drawables_;

    Octant* children_[NUM_OCTANTS];

    glm::vec3 center_;

    glm::vec3 halfSize_;

    unsigned numDrawables_;

    unsigned level_;

    Octant* parent_;

    Octree* root_;

    unsigned index_;
};

class Octree:public Component,public Octant
{
    ENGINE_OBJECT(Octree,Component);
public:
    Octree(Context* context);

    virtual ~Octree() override;
};