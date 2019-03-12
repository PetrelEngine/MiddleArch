//
// Created by Administrator on 2017/10/17.
//

#ifndef RENDEREFFECT_ANDROIDLOG_H
#define RENDEREFFECT_ANDROIDLOG_H
#include <android/log.h>
#define  LQ_LOG_TAG    "EffectRender:"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LQ_LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LQ_LOG_TAG,__VA_ARGS__)
#endif //RENDEREFFECT_ANDROIDLOG_H
