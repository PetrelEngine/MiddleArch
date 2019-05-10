//
//  WBGLProgram.hpp
//  WBGPUImage
//
//  Created by liming27 on 2018/1/24.
//  Copyright © 2018年 liming27. All rights reserved.
//

#pragma once

#include "Common.h"
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class WBGLProgram {
public:
    WBGLProgram();
    ~WBGLProgram();
    
    bool initWithVertexShaderString(const std::string& vertexShaderString, const std::string& fragmentShaderString);
    bool compileShader(GLuint& shader, GLenum type, const std::string& shaderString);
    void addAttribute(const std::string& attributeName);
    GLuint getAttributeIndex(const std::string& attributeName);
    GLuint getUniformIndex(const std::string& uniformName);
    bool link();
    void use();
    void destroy();
    
    std::string getVertexShaderLog();
    std::string getFragmentShaderLog();
    std::string getProgramLog();
    
    bool isInitialized() const;
    GLuint getProgramId() const;
    
private:
    bool _initialized;
    GLuint _program;
    GLuint _vertexShader;
    GLuint _fragmentShader;
    std::vector<std::string> _attributes;
    std::vector<std::string> _uniforms;
    
    std::string _vertexShaderErrorLog;
    std::string _fragmentShaderErrorLog;
    std::string _programErrorLog;
};
