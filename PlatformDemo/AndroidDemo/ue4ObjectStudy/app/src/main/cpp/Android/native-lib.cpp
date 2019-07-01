#include <jni.h>
#include <string>
#include "TestDAG.h"
#include "Context.h"
#include <iostream>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <Sample/HelloTriangleSample.h>
#include <Sample/MTTestSample.h>
#include "Graphics.h"
#include "PBRLightTextureSample.h"
#include "NormalMapSample.h"
#include "GammaCorrectionSample.h"
#include "ParallaxMappingSample.h"
#include "DeferredRenderSample.h"
#include "ApplicationSystem.h"
#include "ObjSample.h"
#include "ProductNormalMapSample.h"
#include "ShadowMapingDepthSample.h"
#include "FresnelReflectionSample.h"
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
    ApplicationSystem* applicationSystem_ = new (std::nothrow)ApplicationSystem();
    applicationSystem_->initialEngine(context_);

    return (uintptr_t)(applicationSystem_);
}

JNI_METHOD(void,setTexture2DId)(JNIEnv *env,jobject jobject1,jlong ApplicationSystemClassId,jstring name,jint textureId)
{
    const char* nameStr = env->GetStringUTFChars(name,0);
    string nameT = const_cast<char*>(nameStr);
    ApplicationSystem* applicationSystem_ = (ApplicationSystem*)(ApplicationSystemClassId);
    Context* context_ = applicationSystem_->getContext();
    context_->setTextureId(nameT,textureId);
    env->ReleaseStringUTFChars(name,nameStr);
}


JNI_METHOD(void ,RendererCreateJNI)(JNIEnv *env,jobject jobject1,jlong ApplicationSystemClassId,jint width,jint height)
{
    ApplicationSystem* applicationSystem_ = (ApplicationSystem*)(ApplicationSystemClassId);
//    ObjSample* pbrSample = new ObjSample();
//    applicationSystem_->RegisteredApplication(pbrSample);

//    DeferredRenderSample* deferredRenderSample = new DeferredRenderSample();
//    applicationSystem_->RegisteredApplication(deferredRenderSample);

//    ProductNormalMapSample* productNormalMapSample = new ProductNormalMapSample();
//    applicationSystem_->RegisteredApplication(productNormalMapSample);

//    ParallaxMappingSample* parallaxMappingSample = new ParallaxMappingSample();
//    applicationSystem_->RegisteredApplication(parallaxMappingSample);

//    GammaCorrectionSample* gammaCorrectionSample = new GammaCorrectionSample();
//    applicationSystem_->RegisteredApplication(gammaCorrectionSample);

    PBRLightTextureSample* pbrLightTextureSample = new PBRLightTextureSample();
    applicationSystem_->RegisteredApplication(pbrLightTextureSample);

//    NormalMapSample* normalMapSample = new NormalMapSample();
//    applicationSystem_->RegisteredApplication(normalMapSample);

//    HelloTriangleSample* helloTriangleSample = new HelloTriangleSample();
//    applicationSystem_->RegisteredApplication(helloTriangleSample);

//    MTTestSample* mtTestSample = new MTTestSample();
//    applicationSystem_->RegisteredApplication(mtTestSample);

//    ShadowMapingDepthSample* shadowMapingDepthSample = new ShadowMapingDepthSample();
//    applicationSystem_->RegisteredApplication(shadowMapingDepthSample);

//    FresnelReflectionSample* fresnelReflectionSample = new FresnelReflectionSample();
//    applicationSystem_->RegisteredApplication(fresnelReflectionSample);

    applicationSystem_->CreateScence(width,height);
}

JNI_METHOD(void,RendererFrameJNI)(JNIEnv *env,jobject jobject1,jlong ApplicationSystemClassId)
{
    ApplicationSystem* applicationSystem_ = (ApplicationSystem*)(ApplicationSystemClassId);
    applicationSystem_->RenderOneFrame();
}

JNI_METHOD(void ,move)(JNIEnv *env,jobject jobject1,jlong ApplicationSystemClassId)
{
    ApplicationSystem* applicationSystem_ = (ApplicationSystem*)(ApplicationSystemClassId);
    applicationSystem_->Move();
}

JNI_METHOD(void,engineRelease)(JNIEnv *env,jobject jobject1,jlong ApplicationSystemClassId)
{
    ApplicationSystem* applicationSystem_ = (ApplicationSystem*)(ApplicationSystemClassId);
    if(applicationSystem_ != NULL)
    {
        delete applicationSystem_;
        applicationSystem_ = NULL;
    }
}


#ifdef __cplusplus
}
#endif
