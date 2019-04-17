//
// Created by liuqian8 on 2019/3/14.
//

#pragma once


// ---------------------------------------------------------------------------
#include <vector>
#include <glm/vec3.hpp>
//#include "vector3.h"

/** Helper structure representing a face with smoothing groups assigned */
struct FaceWithSmoothingGroup {
    FaceWithSmoothingGroup()
            : mIndices()
            , iSmoothGroup(0)
    {
    }

    //! Indices. .3ds is using uint16. However, after
    //! an unique vertex set has been generated,
    //! individual index values might exceed 2^16
    unsigned mIndices[3];

    //! specifies to which smoothing group the face belongs to
    unsigned iSmoothGroup;
};

// ---------------------------------------------------------------------------
/** Helper structure representing a mesh whose faces have smoothing
    groups assigned. This allows us to reuse the code for normal computations
    from smoothings groups for several loaders (3DS, ASE). All of them
    use face structures which inherit from #FaceWithSmoothingGroup,
    but as they add extra members and need to be copied by value we
    need to use a template here.
    */
template <class T> struct MeshWithSmoothingGroups
{
    //! Vertex positions
//    std::vector<aiVector3D> mPositions;
    std::vector<glm::vec3> mPositions;

    //! Face lists
    std::vector<T> mFaces;

    //! List of normal vectors
//    std::vector<aiVector3D> mNormals;
    std::vector<glm::vec3> mNormals;

};