//
// Created by liuqian8 on 2019/6/26.
//
#include "CaseShaderProgram.h"

CaseShaderProgram::CaseShaderProgram()
{

}

CaseShaderProgram::~CaseShaderProgram()
{
    if (vertexShader_)
        glDeleteShader(vertexShader_);

    if (fragmentShader_)
        glDeleteShader(fragmentShader_);

    if (programId_)
        glDeleteProgram(programId_);
}

bool CaseShaderProgram::link(std::string vsCode, std::string fsCode)
{
    programId_ = glCreateProgram();
    if (!compileShader(vertexShader_, GL_VERTEX_SHADER ,vsCode)) {
        return false;
    }
    // Create and compile fragment shader
    if (!compileShader(fragmentShader_, GL_FRAGMENT_SHADER,fsCode)) {
        return false;
    }
    glAttachShader(programId_, vertexShader_);
    glAttachShader(programId_, fragmentShader_);

    GLint status;
    glLinkProgram(programId_);

    glGetProgramiv(programId_, GL_LINK_STATUS, &status);
    if (status == GL_FALSE){
        GLint logLength;
        glValidateProgram(programId_);
        glGetProgramiv(programId_, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            GLchar *log = new GLchar[logLength];
            glGetProgramInfoLog(programId_, logLength, &logLength, log);
            LOGE("Error==> programErrorLog:%s",log);
            //NSLog(@"program_ validate log:\n%s", log);
            delete [] log;
        }
        return false;
    }

    if (vertexShader_) {
        glDeleteShader(vertexShader_);
        vertexShader_ = 0;
    }

    if (fragmentShader_) {
        glDeleteShader(fragmentShader_);
        fragmentShader_ = 0;
    }
    return true;
}

void CaseShaderProgram::use()
{
    glUseProgram(programId_);
}

void CaseShaderProgram::setParamater(const std::string param, float value)
{
    glUniform1f(glGetUniformLocation(programId_,param.c_str()),value);
}

void CaseShaderProgram::setParamater(const std::string param, const int value)
{
    glUniform1i(glGetUniformLocation(programId_,param.c_str()),value);
}

void CaseShaderProgram::setParamater(const std::string param, const bool value)
{
    glUniform1i(glGetUniformLocation(programId_,param.c_str()),(int)value);
}

void CaseShaderProgram::setParamater(const std::string param, const glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(programId_,param.c_str()),1,GL_FALSE,(GLfloat *)&value);
}

void CaseShaderProgram::setParamater(const std::string param, const glm::vec2 value)
{
    glUniform2fv(glGetUniformLocation(programId_,param.c_str()),1,(GLfloat *)&value);
}

void CaseShaderProgram::setParamater(const std::string param, const glm::vec3 value)
{
    glUniform3fv(glGetUniformLocation(programId_,param.c_str()),1,(GLfloat *)&value);
}

void CaseShaderProgram::setParamater(const std::string param, const glm::vec4 value)
{
    glUniform4fv(glGetUniformLocation(programId_,param.c_str()),1,(GLfloat *)&value);
}

int CaseShaderProgram::getUniformationLocation(const std::string paramName)
{
    return glGetUniformLocation(programId_,paramName.c_str());
}

int CaseShaderProgram::getAttribLocation(const std::string paramName)
{
    return glGetAttribLocation(programId_, paramName.c_str());
}

bool CaseShaderProgram::compileShader(GLuint &shader, GLenum type, const std::string &shaderCode)
{
    GLint status;

    const GLchar* source = shaderCode.c_str();
    if (!source) {
        return false;
    }

    shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, NULL);

    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength > 0) {
            GLchar *log = new GLchar[logLength];
            glGetShaderInfoLog(shader, logLength, &logLength, log);
            if(type == GL_VERTEX_SHADER){
                LOGE("vertex error:%s",log);
            }else if(type == GL_FRAGMENT_SHADER){
                LOGE("fragment error:%s",log);
            }
            delete [] log;
        }
    }
    return status == GL_TRUE;
}
