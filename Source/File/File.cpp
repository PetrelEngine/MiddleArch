//
// Created by liuqian8 on 2019/4/16.
//
#include "File.h"
#include <sys/stat.h>
File::~File()
{

}

std::string File::getStringFromFile(const string filename)
{
    std::string s;
    getContents(filename,&s);
    return s;
}

std::string File::getStringFromFileAssets(const string filename)
{
//    std::string s;
    char* pData;
#if PLATFORM == PLATFORM_ANDROID
    AAssetManager* mgr_ = context_->getAAssetManager();
    AAsset *asset = AAssetManager_open(mgr_, filename.c_str(), AASSET_MODE_UNKNOWN);
    if(!asset){
        LOGE("asset not found");
        return NULL;
    }
    size_t size = AAsset_getLength(asset);
    if(size > 0)
    {
        pData = new char[size];
        int iRet = AAsset_read(asset,pData,size);
        if(iRet <= 0)
        {
            delete [] pData;
            pData = NULL;
            LOGE("load file failure! %s\n",filename.c_str());
        }else{
            LOGI("load file success! %s\n",filename.c_str());
            LOGI("load file success! Data is:\n%s\n",pData);
        }
    }
    AAsset_close(asset);
    if( asset == NULL )
        size = 0;

    return pData;
#endif
    return pData;
}

Status File::getContents(const std::string &filename, ResizableBuffer *buffer)
{
    if(filename.empty())
        return Status::NotExists;
    FILE *fp = fopen(filename.c_str(), "rb");
    if (!fp)
        return Status::OpenFailed;
#if defined(_MSC_VER)
    auto descriptor = _fileno(fp);
#else
    auto descriptor = fileno(fp);
#endif
    struct stat statBuf;
    if (fstat(descriptor, &statBuf) == -1) {
        fclose(fp);
        return Status::ReadFailed;
    }
    size_t size = statBuf.st_size;
    buffer->resize(size);
    size_t readsize = fread(buffer->buffer(), 1, size, fp);
    fclose(fp);
    if (readsize < size) {
        buffer->resize(readsize);
        return Status::ReadFailed;
    }
    return Status::OK;
}