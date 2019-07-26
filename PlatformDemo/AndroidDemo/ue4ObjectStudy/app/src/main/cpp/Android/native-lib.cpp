#include <jni.h>
#include <string>
#include "TestDAG.h"
#include "Context.h"
#include <iostream>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "EngineSample.h"
#include "MTTestSample.h"
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
#include "BilateralFilterSample.h"
using namespace std;

#define JNI_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_android_skysnow_com_ue4objectstudy_JNIAPI_CoreObjectJNI_##method_name
#ifdef __cplusplus
extern "C" {
#endif

JNI_METHOD(jlong ,initialEngine)(JNIEnv *env,jobject jobject1,jobject assetManager,jint width,jint height)
{
    jobject assetManagerTemp_ = env->NewGlobalRef(assetManager);
    AAssetManager* mgr = AAssetManager_fromJava(env,assetManagerTemp_);
    Context* context_ = new (std::nothrow)Context();
    context_->setSetAssetManager(mgr);
    ApplicationSystem* applicationSystem_ = new (std::nothrow)ApplicationSystem();
    applicationSystem_->initialEngine(context_,width,height);

    return (uintptr_t)(applicationSystem_);
}

JNI_METHOD(void ,RendererCreateJNI)(JNIEnv *env,jobject jobject1,jlong ApplicationSystemClassId,jint width,jint height)
{
    ApplicationSystem* applicationSystem_ = (ApplicationSystem*)(ApplicationSystemClassId);

//    PBRLightTextureSample* pbrLightTextureSample = new PBRLightTextureSample();
//    applicationSystem_->RegisteredApplication(pbrLightTextureSample);

//    BilateralFilterSample* bilateralFilterSample = new BilateralFilterSample();
//    applicationSystem_->RegisteredApplication(bilateralFilterSample);

//    TestDAG* testDAG = new TestDAG();
//    applicationSystem_->RegisteredApplication(testDAG);

    EngineSample* helloTriangleSample = new EngineSample();
    applicationSystem_->RegisteredApplication(helloTriangleSample);

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

JNI_METHOD(void,switchApplication)(JNIEnv *env,jobject jobject1,jlong ApplicationSystemClassId,jint type)
{
    ApplicationSystem* applicationSystem_ = (ApplicationSystem*)(ApplicationSystemClassId);
    int aTtype = type;
    switch (aTtype)
    {
        case 0:
        {
            ObjSample* pbrSample = new ObjSample();
            applicationSystem_->RegisteredApplication(pbrSample);
        }break;
        case 1:
        {
            DeferredRenderSample* deferredRenderSample = new DeferredRenderSample();
            applicationSystem_->RegisteredApplication(deferredRenderSample);
        }break;
        case 2:
        {
            ProductNormalMapSample* productNormalMapSample = new ProductNormalMapSample();
            applicationSystem_->RegisteredApplication(productNormalMapSample);
        }break;
        case 3:
        {
            ParallaxMappingSample* parallaxMappingSample = new ParallaxMappingSample();
            applicationSystem_->RegisteredApplication(parallaxMappingSample);
        }break;
        case 4:
        {
            GammaCorrectionSample* gammaCorrectionSample = new GammaCorrectionSample();
            applicationSystem_->RegisteredApplication(gammaCorrectionSample);
        }break;
        case 5:
        {
            PBRLightTextureSample* pbrLightTextureSample = new PBRLightTextureSample();
            applicationSystem_->RegisteredApplication(pbrLightTextureSample);
        }break;
        case 6:
        {
            NormalMapSample* normalMapSample = new NormalMapSample();
            applicationSystem_->RegisteredApplication(normalMapSample);
        }break;
        case 7:
        {
            EngineSample* helloTriangleSample = new EngineSample();
            applicationSystem_->RegisteredApplication(helloTriangleSample);
        }break;
        case 8:
        {
            MTTestSample* mtTestSample = new MTTestSample();
            applicationSystem_->RegisteredApplication(mtTestSample);
        }break;
        case 9:
        {
            ShadowMapingDepthSample* shadowMapingDepthSample = new ShadowMapingDepthSample();
            applicationSystem_->RegisteredApplication(shadowMapingDepthSample);
        }break;
        case 10:
        {
            FresnelReflectionSample* fresnelReflectionSample = new FresnelReflectionSample();
            applicationSystem_->RegisteredApplication(fresnelReflectionSample);
        }break;

    }
}


#ifdef __cplusplus
}
#endif
