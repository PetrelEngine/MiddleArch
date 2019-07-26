//
// Created by liuqian8 on 2019/6/4.
//
#pragma once

#include "DataStruct.h"
#include "type_mat.hpp"
#include "type_mat4x4.hpp"
#include "Drawable.h"
#include <vector>
class View;
class Geometry;
class ShaderVariation;
class Drawable;
class Camera;
class Texture2D;
class Material;
class Pass;
class Zone;
//Queued 3D geometry draw call.
struct Batch
{
    Batch()
    {
    }

    Batch(const SourceBatch& rhs):
            geometry_(rhs.geometry_),
            modelmatrix_(rhs.wordTransform_),
            distance_(rhs.distance_),
            instancingData_(rhs.instancingData_),
            material_(rhs.material_),
            numWorldTransforms_(rhs.numWorldTransforms_)
    {
    }

    void Prepare(View* view,Camera* camera,bool setModelTransform, bool allowDepthWrite);

    void Draw(View* view,Camera* camera, bool allowDepthWrite);

    Zone* zone_;

    glm::mat4        modelmatrix_;

    Geometry*        geometry_;

    ShaderVariation* vertexShader_;

    ShaderVariation* pixelShader_;

    float distance_;

    void* instancingData_;

    Material* material_;

    Pass* pass_;

    unsigned numWorldTransforms_;
};
//一个实例化几何体的几何数据
struct InstanceData
{
    InstanceData()
    {
    }

    InstanceData(const glm::mat4 worldTransform,const void* instanceData,float distance)
    {

    }

    glm::mat4 worldTrancsform_;
    const void* instancingData_;

    float distance_;
};

struct BatchGroup:public Batch
{
    BatchGroup():
            startIndex_(M_MAX_UNSIGNED)
    {
    }

    BatchGroup(const Batch& batch):
            Batch(batch),
            startIndex_(M_MAX_UNSIGNED)
    {
    }

    ~BatchGroup()
    {

    }

    void addTransforms(const Batch& batch)
    {
        InstanceData newInstance;
        newInstance.distance_ = batch.distance_;
        newInstance.instancingData_ = batch.instancingData_;
        newInstance.worldTrancsform_ = batch.modelmatrix_;
    }

    void Draw(View* view,Camera* camera, bool allowDepthWrite) const;
    unsigned startIndex_;
    std::vector<InstanceData> instances_;
};

struct BatchGroupKey
{
    BatchGroupKey()
    {

    }




    Zone* zone_;

    Pass* pass_;

    Material* material_;

    Geometry* geometry_;

    unsigned char renderOrder_;
};

struct BatchQueue
{
public:

    void clear(int maxSortedInstances);

    void draw(View* view, Camera* camera, bool markToStencil, bool usingLightOptimization, bool allowDepthWrite) const;
};
