#include <jni.h>
#include <string>
#include "TestDAG.h"
#include "Context.h"
#include <iostream>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "DeferredRenderSample.h"
#include "ApplicationSystem.h"
#include "PBRSample.h"
#include "ProductNormalMapSample.h"
using namespace std;

#define JNI_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_android_skysnow_com_ue4objectstudy_JNIAPI_CoreObjectJNI_##method_name
#ifdef __cplusplus
extern "C" {
#endif


static TestDAG* dag_;
JNI_METHOD(jstring,stringFromJNI)(JNIEnv *env,jobject jobject1)
{
    std::string hello = "CoreObject";
    if(dag_ == NULL)
    {
        dag_ = new TestDAG();
    }
    dag_->DAGTest();

    int result = dag_->Sum_Solution(10);
    hello += "::"+std::to_string(result);
    return env->NewStringUTF(hello.c_str());
}

JNI_METHOD(jlong ,setAssetsManagerJNI)(JNIEnv *env,jobject jobject1,jobject assetManager)
{
    jobject assetManagerTemp_ = env->NewGlobalRef(assetManager);
    AAssetManager* mgr = AAssetManager_fromJava(env,assetManagerTemp_);
    Context* context_ = new (std::nothrow)Context();
    context_->setSetAssetManager(mgr);
    return (uintptr_t)(context_);
}

JNI_METHOD(void,setTexture2DId)(JNIEnv *env,jobject jobject1,jlong contextClassId,jstring name,jint textureId)
{
    Context* context_ = ((Context*)contextClassId);
    context_->setTextureId("fish",textureId);
}


JNI_METHOD(jlong,RendererCreateJNI)(JNIEnv *env,jobject jobject1,jlong contextClassId,jint width,jint height)
{
    Context* context_ = ((Context*)contextClassId);
    ApplicationSystem* applicationSystem_ = new (std::nothrow)ApplicationSystem();

//    PBRSample* pbrSample = new PBRSample();
//    applicationSystem_->RegisteredApplication(pbrSample);

//    DeferredRenderSample* deferredRenderSample = new DeferredRenderSample();
//    applicationSystem_->RegisteredApplication(deferredRenderSample);

    ProductNormalMapSample* productNormalMapSample = new ProductNormalMapSample();
    applicationSystem_->RegisteredApplication(productNormalMapSample);

    applicationSystem_->CreateScence(context_,width,height);
    return (uintptr_t)(applicationSystem_);
}

JNI_METHOD(void,RendererFrameJNI)(JNIEnv *env,jobject jobject1,jlong contextClassId,jlong ApplicationSystemClassId)
{
    Context* context_ = ((Context*)contextClassId);

    ApplicationSystem* applicationSystem_ = (ApplicationSystem*)(ApplicationSystemClassId);
    applicationSystem_->RenderOneFrame(context_);
}

JNI_METHOD(void ,move)(JNIEnv *env,jobject jobject1,jlong ApplicationSystemClassId)
{
    ApplicationSystem* applicationSystem_ = (ApplicationSystem*)(ApplicationSystemClassId);

//    PBRSample* pbrSample = (PBRSample*)applicationSystem_->GetCurrApplication();
//    pbrSample->move();
//    DeferredRenderSample* deferredRenderSample = (DeferredRenderSample*)applicationSystem_->GetCurrApplication();
//    deferredRenderSample->move();

    ProductNormalMapSample* productNormalMapSample = (ProductNormalMapSample*)applicationSystem_->GetCurrApplication();
    productNormalMapSample->move();

}


#ifdef __cplusplus
}
#endif
