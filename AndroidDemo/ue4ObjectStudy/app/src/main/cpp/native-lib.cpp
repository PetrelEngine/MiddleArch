#include <jni.h>
#include <string>
#include "TestDAG.h"


#define JNI_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_android_skysnow_com_ue4objectstudy_JNIAPI_CoreObjectJNI_##method_name

#ifdef __cplusplus
extern "C" {
#endif


static TestDAG* dag_;
JNI_METHOD(jstring,stringFromJNI)(JNIEnv *env,jobject jobject1)
{
    std::string hello = "CoreObject和Render部分的Demo！";
    if(dag_ == NULL)
    {
        dag_ = new TestDAG();
    }
    dag_->DAGTest();
    return env->NewStringUTF(hello.c_str());
}



#ifdef __cplusplus
}
#endif
