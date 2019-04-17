//
// Created by liuqian8 on 2019/3/14.
//

#pragma once


#include <math.h>
#include <string>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext.hpp>

using namespace std;

struct aiCamera
{
    /** The name of the camera.
     *
     *  There must be a node in the scenegraph with the same name.
     *  This node specifies the position of the camera in the scene
     *  hierarchy and can be animated.
     */
     string mName;

    /** Position of the camera relative to the coordinate space
     *  defined by the corresponding node.
     *
     *  The default value is 0|0|0.
     */
//     aiVector3D mPosition;
    glm::vec3 mPosition;


    /** 'Up' - vector of the camera coordinate system relative to
     *  the coordinate space defined by the corresponding node.
     *
     *  The 'right' vector of the camera coordinate system is
     *  the cross product of  the up and lookAt vectors.
     *  The default value is 0|1|0. The vector
     *  may be normalized, but it needn't.
     */
//     aiVector3D mUp;
    glm::vec3 mUp;


    /** 'LookAt' - vector of the camera coordinate system relative to
     *  the coordinate space defined by the corresponding node.
     *
     *  This is the viewing direction of the user.
     *  The default value is 0|0|1. The vector
     *  may be normalized, but it needn't.
     */
//     aiVector3D mLookAt;
    glm::vec3 mLookAt;


    /** Half horizontal field of view angle, in radians.
     *
     *  The field of view angle is the angle between the center
     *  line of the screen and the left or right border.
     *  The default value is 1/4PI.
     */
    float mHorizontalFOV;

    /** Distance of the near clipping plane from the camera.
     *
     * The value may not be 0.f (for arithmetic reasons to prevent
     * a division through zero). The default value is 0.1f.
     */
    float mClipPlaneNear;

    /** Distance of the far clipping plane from the camera.
     *
     * The far clipping plane must, of course, be further away than the
     * near clipping plane. The default value is 1000.f. The ratio
     * between the near and the far plane should not be too
     * large (between 1000-10000 should be ok) to avoid floating-point
     * inaccuracies which could lead to z-fighting.
     */
    float mClipPlaneFar;


    /** Screen aspect ratio.
     *
     * This is the ration between the width and the height of the
     * screen. Typical values are 4/3, 1/2 or 1/1. This value is
     * 0 if the aspect ratio is not defined in the source file.
     * 0 is also the default value.
     */
    float mAspect;


    aiCamera()
            : mUp               (0.f,1.f,0.f)
            , mLookAt           (0.f,0.f,1.f)
            , mHorizontalFOV    (0.25f * (float)M_PI)
            , mClipPlaneNear    (0.1f)
            , mClipPlaneFar     (1000.f)
            , mAspect           (0.f)
    {}

    /** @brief Get a *right-handed* camera matrix from me
     *  @param out Camera matrix to be filled
     */
//    void GetCameraMatrix (aiMatrix4x4& out) const
    void GetCameraMatrix (glm::mat4x4& out) const
    {
        /** todo: test ... should work, but i'm not absolutely sure */
        /** We don't know whether these vectors are already normalized ...*/
//        aiVector3D zaxis = mLookAt;     zaxis.Normalize();
//        aiVector3D yaxis = mUp;         yaxis.Normalize();
//        aiVector3D xaxis = mUp^mLookAt; xaxis.Normalize();

//        out.a4 = -(xaxis * mPosition);
//        out.b4 = -(yaxis * mPosition);
//        out.c4 = -(zaxis * mPosition);

//        out.a1 = xaxis.x;
//        out.a2 = xaxis.y;
//        out.a3 = xaxis.z;

//        out.b1 = yaxis.x;
//        out.b2 = yaxis.y;
//        out.b3 = yaxis.z;

//        out.c1 = zaxis.x;
//        out.c2 = zaxis.y;
//        out.c3 = zaxis.z;

//        out.d1 = out.d2 = out.d3 = 0.f;
//        out.d4 = 1.f;

        glm::vec3 zaxis = mLookAt;     glm::normalize(zaxis);
        glm::vec3 yaxis = mUp;         glm::normalize(yaxis);
        glm::vec3 xaxis = mUp^mLookAt; glm::normalize(xaxis);

        out[3][0] = -(xaxis * mPosition).x;
        out[3][1] = -(yaxis * mPosition).y;
        out[3][2] = -(zaxis * mPosition).z;

        out[0][0] = xaxis.x;
        out[0][1] = xaxis.y;
        out[0][2] = xaxis.z;

        out[1][0] = yaxis.x;
        out[1][1] = yaxis.y;
        out[1][2] = yaxis.z;

        out[2][0] = zaxis.x;
        out[2][1] = zaxis.y;
        out[2][2] = zaxis.z;

        out[0][3] = out[1][3] = out[2][3] = 0.f;
        out[3][3] = 1.f;
    }
};