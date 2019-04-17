//
// Created by liuqian8 on 2019/4/16.
//
#pragma once

#pragma once
#include "Common.h"
#if PLATFORM == PLATFORM_ANDROID
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#endif
class Context
{
public:
    Context();

    ~Context();

    void setTextureId(string nameType, int textureId) ;

    int getTextureId(string name) ;

#if PLATFORM == PLATFORM_ANDROID
    void setSetAssetManager(AAssetManager *mgr)
    {
        if(nullptr == mgr)
            LOGE("AAssetManager is null pointer. -----Context.cpp.");
        mgr_ = mgr;
    }

    AAssetManager* getAAssetManager()
    {
        if(nullptr == mgr_)
            LOGE("AAssetManager is null pointer. -----Context.cpp.");
        return mgr_;
    }
#endif
protected:
    SN_HashMap<string,int>      textureList_;
    int tempId_;
#if PLATFORM == PLATFORM_ANDROID
    AAssetManager* mgr_;
#endif
};
