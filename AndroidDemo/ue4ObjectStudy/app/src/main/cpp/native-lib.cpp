#include <jni.h>
#include <string>

#define JNI_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_android_skysnow_com_ue4objectstudy_JNIAPI_CoreObjectJNI_##method_name

#ifdef __cplusplus
extern "C" {
#endif



JNI_METHOD(jstring,stringFromJNI)(JNIEnv *env,jobject jobject1)
{
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



#ifdef __cplusplus
}
#endif
