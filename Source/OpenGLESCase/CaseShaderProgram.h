//
// Created by liuqian8 on 2019/6/26.
//
#pragma once
#include "vec4.hpp"
#include "vec3.hpp"
#include "vec2.hpp"
#include "mat4x4.hpp"

#include "Common.h"
class CaseShaderProgram
{
public:
    CaseShaderProgram();

    ~CaseShaderProgram();

    bool link(std::string vsCode,std::string fsCode);

    void use();
    //float 数据
    void setParamater(const std::string param,float value);
    void setParamater(const std::string param,const glm::vec4 value);
    void setParamater(const std::string param,const glm::vec3 value);
    void setParamater(const std::string param,const glm::vec2 value);
    void setParamater(const std::string param,const int value);
    void setParamater(const std::string param,const bool value);
    void setParamater(const std::string param,const glm::mat4 value);


    int getUniformationLocation(const std::string paramName);

    int getAttribLocation(const std::string paramName);

private:
    bool compileShader(GLuint& shader,GLenum type,const std::string& shaderCode);
protected:
    unsigned programId_;

    GLuint vertexShader_;
    GLuint fragmentShader_;
};
