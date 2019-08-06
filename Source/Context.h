//
// Created by liuqian8 on 2019/4/16.
//
#pragma once
#include "Common.h"
#include "Object.h"
#if PLATFORM == PLATFORM_ANDROID
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#endif
#include <vector>
class Context
{
    friend class Object;
public:
    Context()
    {
    }
    ~Context();

    template <class T> inline T createObject()
    {
        return static_cast<T>(createObject(T::getTypeStatic()));
    }

    Object* createObject(std::string type);

    void registerFactory(ObjectFactory* factory);

    void registerFactory(ObjectFactory* factory, const char* category);

    void registerSubsystem(Object* subsystem);

    Object* getSubsystem(string type) const;

    void removeSubsystem(string ObjectType);

    template <class T> T* getSubsystem() const;
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

    template <class T> void registerFactory();

    template <class T> void registerFactory(const char* category);
protected:
    SN_HashMap<string ,Object*> subsystem_;
#if PLATFORM == PLATFORM_ANDROID
    AAssetManager* mgr_;
#endif

private:
    SN_HashMap<std::string,ObjectFactory*> factories_;
    SN_HashMap<std::string,std::vector<string>> objectCategories_;
};

template <class T> void Context::registerFactory()
{
    registerFactory(new ObjectFactoryImpl<T>(this));
}

template <class T> void Context::registerFactory(const char* category)
{
    registerFactory(new ObjectFactoryImpl<T>(this), category);
}

template <class T> T* Context::getSubsystem() const
{
    return static_cast<T*> (getSubsystem(T::getTypeNameStatic()));
}
