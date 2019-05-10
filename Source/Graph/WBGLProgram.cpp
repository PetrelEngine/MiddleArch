//
//  WBGLProgram.cpp
//  WBGPUImage
//
//  Created by liming27 on 2018/1/24.
//  Copyright © 2018年 liming27. All rights reserved.
//

#include "WBGLProgram.hpp"

WBGLProgram::WBGLProgram() :
_initialized(false),
_program(0),
_vertexShader(0),
_fragmentShader(0),
_vertexShaderErrorLog(""),
_fragmentShaderErrorLog(""),
_programErrorLog(""){
    
}

WBGLProgram::~WBGLProgram() {
    destroy();
}

bool WBGLProgram::initWithVertexShaderString(const std::string& vertexShaderString, const std::string& fragmentShaderString) {
    
    _initialized = false;
    
    _attributes.clear();
    _uniforms.clear();
    _program = glCreateProgram();
    
    if (!compileShader(_vertexShader, GL_VERTEX_SHADER ,vertexShaderString)) {
        return false;
    }
    
    // Create and compile fragment shader
    if (!compileShader(_fragmentShader, GL_FRAGMENT_SHADER,fragmentShaderString)) {
        return false;
    }
    
    glAttachShader(_program, _vertexShader);
    glAttachShader(_program, _fragmentShader);
    
    return true;
}

bool WBGLProgram::compileShader(GLuint& shader, GLenum type, const std::string& shaderString) {
    
    GLint status;
    
    const GLchar* source = shaderString.c_str();
    if (!source) {
        //NSLog(@"Failed to load vertex shader");
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
                _vertexShaderErrorLog = std::string(log);
                LOGE("vertex error:%s",_vertexShaderErrorLog.c_str());
            }else if(type == GL_FRAGMENT_SHADER){
                _fragmentShaderErrorLog = std::string(log);
                LOGE("fragment error:%s",_fragmentShaderErrorLog.c_str());
            }
            //TODO: NSLog(@"Shader compile log:\n%s", log);
            delete [] log;
        }
    }
    
    return status == GL_TRUE;
}

void WBGLProgram::addAttribute(const std::string& attributeName) {
    
    std::vector<std::string>::const_iterator found = std::find(_attributes.begin(), _attributes.end(), attributeName);
    if (found == _attributes.end()) {
        
        // the attribute was not found, add it to the end of attributes_ and bind it
        _attributes.push_back(attributeName);
        
        size_t indexOfAttribute = _attributes.size() - 1;
        
        glBindAttribLocation(_program, (GLuint)indexOfAttribute, attributeName.c_str());
    }
}

GLuint WBGLProgram::getAttributeIndex(const std::string& attributeName) {
    
    // TODO: take care of element not found?
    std::vector<std::string>::const_iterator found = std::find(_attributes.begin(), _attributes.end(), attributeName);
    
    return (GLuint)(found - _attributes.begin());
}

GLuint WBGLProgram::getUniformIndex(const std::string& uniformName) {
    
    return glGetUniformLocation(_program, uniformName.c_str());
}

bool WBGLProgram::link() {
    
    GLint status;
    
    glLinkProgram(_program);
    
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE){
        GLint logLength;
        glValidateProgram(_program);
        glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            GLchar *log = new GLchar[logLength];
            glGetProgramInfoLog(_program, logLength, &logLength, log);
            _programErrorLog = std::string(log);
            //NSLog(@"program_ validate log:\n%s", log);
            delete [] log;
        }
        return false;
    }
    
    if (_vertexShader) {
        glDeleteShader(_vertexShader);
        _vertexShader = 0;
    }
    
    if (_fragmentShader) {
        glDeleteShader(_fragmentShader);
        _fragmentShader = 0;
    }
    
    _initialized = true;
    
    return true;
}

void WBGLProgram::use() {
    glUseProgram(_program);
}

void WBGLProgram::destroy() {
    
    if (_vertexShader)
        glDeleteShader(_vertexShader);
    
    if (_fragmentShader)
        glDeleteShader(_fragmentShader);
    
    if (_program)
        glDeleteProgram(_program);
}

std::string WBGLProgram::getVertexShaderLog() {
    return _vertexShaderErrorLog;
}

std::string WBGLProgram::getFragmentShaderLog() {
    return _fragmentShaderErrorLog;
}

std::string WBGLProgram::getProgramLog() {
    return _programErrorLog;
}

bool WBGLProgram::isInitialized() const {
    return _initialized;
}

GLuint WBGLProgram::getProgramId() const {
    return _program;
}
