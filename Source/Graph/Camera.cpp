//
// Created by liuqian8 on 2019/6/14.
//
#include "matrix_transform.hpp"
#include "Camera.h"

Camera::Camera(Context *context):
    Object(context),
    cameraPos_(0,0,0),
    cameraLookAt_(0,0,1),
    cameraUpvec_(0,1,0),
    fov_(90.0f),
    near_(0.1f),
    far_(1000.0f),
    aspectRadio_(0.5625f),
    cameraDirty_(true),
    frustumDirty_(true),
    cameraMat_(glm::mat4(1.0)),
    frustumMat_(glm::mat4(1.0))
{
}

Camera::~Camera()
{

}

void Camera::setCameraPosition(glm::vec3 cameraPos)
{
    cameraPos_ = cameraPos;
    cameraDirty_ = true;
}

void Camera::setCameraLookAt(glm::vec3 lookAt)
{
    cameraLookAt_ = lookAt;
    cameraDirty_ = true;
}

void Camera::setCameraUp(glm::vec3 upVec)
{
    cameraUpvec_ = upVec;
    cameraDirty_ = true;
}

glm::mat4 Camera::getCamera()
{
    if(cameraDirty_)
    {
        cameraMat_ = glm::lookAt(cameraPos_,cameraLookAt_,cameraUpvec_);
        cameraDirty_ = false;
    }

    return cameraMat_;
}

void Camera::setFov(float fov)
{
    fov_ = fov;
    frustumDirty_ = true;
}

void Camera::setAspectRadio(float aspectRadio)
{
    aspectRadio_ = aspectRadio;
    frustumDirty_ = true;
}

void Camera::setNear(float near)
{
    near_ = near;
    frustumDirty_ = true;
}

void Camera::setFar(float far)
{
    far_ = far;
    frustumDirty_ = true;
}

glm::mat4 Camera::getFrustum()
{
    if(frustumDirty_)
    {
        frustumMat_ = glm::perspective(fov_, aspectRadio_, near_, far_);
        frustumDirty_ = false;
    }
    return frustumMat_;
}