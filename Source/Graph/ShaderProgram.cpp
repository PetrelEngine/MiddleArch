//
// Created by liuqian8 on 2019/5/29.
//
#include "ShaderProgram.h"
#include "Common.h"
ShaderProgram::ShaderProgram(Graphics *graphics, ShaderVariation *vertexShader,ShaderVariation *pixelShader):
    GPUObject(graphics),
    vertexShader_(vertexShader),
    pixeShader_(pixelShader)
{
}

ShaderProgram::~ShaderProgram()
{

}

bool ShaderProgram::Link()
{
    if(!vertexShader_ || !pixeShader_ || !vertexShader_->getGPUObjectName() || !pixeShader_->getGPUObjectName())
        return false;

    object_.name_ = glCreateProgram();
    if(!object_.name_)
    {
        LOGE("Could not create shader program");
        return false;
    }

    glAttachShader(object_.name_,vertexShader_->getGPUObjectName());
    glAttachShader(object_.name_,pixeShader_->getGPUObjectName());
    glLinkProgram(object_.name_);
    int linked,length;
    glGetProgramiv(object_.name_,GL_LINK_STATUS,&linked);
    if(!linked)
    {
        glGetProgramiv(object_.name_, GL_INFO_LOG_LENGTH, &length);
        char* buf = (char*)malloc(length);
        int outLength;
        glGetProgramInfoLog(object_.name_, length, &outLength, buf);
        LOGE("Could not link program:\n%s\n", buf);
        free(buf);
        glDeleteProgram(object_.name_);
        object_.name_ = 0;
    }
    if(!object_.name_)
        return false;

    const int MAX_NAME_LENGTH = 256;
    char nameBuffer[MAX_NAME_LENGTH];
    int attributeCount,uniformCount,elementCount,nameLength;
    GLenum type;
    glUseProgram(object_.name_);
    //查询获取统一变量
    glGetProgramiv(object_.name_,GL_ACTIVE_ATTRIBUTES,&attributeCount);
    for(int i = 0; i < attributeCount; i ++)
    {
        glGetActiveAttrib(object_.name_,i,(GLsizei)MAX_NAME_LENGTH,&nameLength, &elementCount, &type, nameBuffer);
        string name = string(nameBuffer,nameLength);
        VertexElementSemantic semantic = MAX_VERTEX_ELEMENT_SEMANTICS;
        unsigned char semanticIndex = 0;
        for(unsigned j = MAX_VERTEX_ELEMENT_SEMANTICS - 1;j < MAX_VERTEX_ELEMENT_SEMANTICS;j--)
        {
            string elementSemanticName = ShaderVariation::elementSemanticNames[j];
            string::size_type flag = name.find(elementSemanticName);
            if(flag != name.npos)
            {
                semantic = (VertexElementSemantic)j;
                break;
            }
        }
        int location = glGetAttribLocation(object_.name_, name.c_str());
        vertexAttributes_[make_pair(semantic,name)] = (unsigned)location;
    }

    //获取uniforms 变量
    glGetProgramiv(object_.name_, GL_ACTIVE_UNIFORMS, &uniformCount);
    for(int i = 0; i < uniformCount; ++i)
    {
        glGetActiveUniform(object_.name_,(GLuint)i,MAX_NAME_LENGTH,nullptr, &elementCount, &type, nameBuffer);
        int location = glGetUniformLocation(object_.name_, nameBuffer);
        string name(nameBuffer);
        if(name[0] == 'c')//处理uniform变量
        {
            ShaderParameter parameter;
            parameter.name_ = name;
            parameter.glType_ = type;
            parameter.location_ = location;
            LOGE("c 打头的uniform变量：%s",name.c_str());
            if(location >= 0)
                shaderParameters_[name] = parameter;
        }else if(location >= 0 && name[0] == 's'){//处理Sample2D类型的统一变量
            LOGE("s 打头的uniform变量：%s",name.c_str());
            ShaderParameter parameter;
            parameter.name_ = name;
            parameter.glType_ = type;
            parameter.location_ = location;
            if(location >= 0)
                shaderParameters_[name] = parameter;
        }
    }
    return true;
}


ShaderVariation* ShaderProgram::GetPixelShader() const
{
    return pixeShader_;
}

ShaderVariation* ShaderProgram::GetVertexShader() const
{
    return vertexShader_;
}

const ShaderParameter* ShaderProgram::GetParameter(string param) const
{
    SN_Map<string,ShaderParameter>::const_iterator i = shaderParameters_.find(param);
    if (i != shaderParameters_.end())
        return &i->second;
    else
        return nullptr;
}