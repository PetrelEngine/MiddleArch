#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <GLES2/gl2.h>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>


using namespace std;

class ShaderProgram {
public:
    unsigned int ID;

    ShaderProgram() : ID(0) {}

    ShaderProgram(const string &vertex_code, const string &frag_code) {
        GLint Result = GL_FALSE;
        int InfoLogLength = 0;
        // Create the shaders
        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        // Compile Vertex Shader
        //printf("Compiling shader : %s\n", vertex_file_path);
        char const *VertexSourcePointer = vertex_code.c_str();
        glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
        glCompileShader(VertexShaderID);

        // Check Vertex Shader
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (!Result) {
            std::vector<char> VertexShaderErrorMessage(InfoLogLength);
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            if (VertexShaderErrorMessage.size() != 0)
                throw runtime_error(
                        string("VERTEX ERROR: ") + string(VertexShaderErrorMessage.data()));
            else
                throw runtime_error(string("VERTEX ERROR: "));
        }

        // Compile Fragment Shader
        char const *FragmentSourcePointer = frag_code.c_str();
        glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
        glCompileShader(FragmentShaderID);

        // Check Fragment Shader
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (!Result) {
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL,
                               &FragmentShaderErrorMessage[0]);
            if (FragmentShaderErrorMessage.size() != 0)
                throw runtime_error(
                        string("FRAGMENT ERROR: ") + string(FragmentShaderErrorMessage.data()));
            else
                throw runtime_error(string("FRAGMENT ERROR: "));
        }

        // Link the program
        //fprintf(stdout, "Linking programn\n");
        GLuint ProgramID = glCreateProgram();
        glAttachShader(ProgramID, VertexShaderID);
        glAttachShader(ProgramID, FragmentShaderID);
        glLinkProgram(ProgramID);

        // Check the program
        glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
        glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (!Result) {
            std::vector<char> ProgramErrorMessage(InfoLogLength);
            glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            if (ProgramErrorMessage.size() != 0)
                throw runtime_error(string("LINK ERROR: ") + string(ProgramErrorMessage.data()));
            else
                throw runtime_error(string("LINK ERROR: "));
        }

        glDeleteShader(VertexShaderID);
        glDeleteShader(FragmentShaderID);

        ID = ProgramID;
    }

    GLuint getUniformLocation(const char *name) {
        return glGetUniformLocation(ID, name);
    }

    GLuint getAttribLocation(const char *name) {
        return glGetAttribLocation(ID, name);
    }

    static bool check(const char *name) {
        GLenum ret = glGetError();
        if (ret != GL_NO_ERROR) {
//            LOGE("==== '%s' GL_CHECK_ERROE  = %x====\n", name, ret);
            //if debug 强制crash

//            throw runtime_error(string("GL_CHECK ERROR see log for details"));
            return false;
        } else {
            return true;
        }
    }


    void setUniform1i(char *uniformName, GLint value) {
        GLuint location = glGetUniformLocation(ID, uniformName);
        glUniform1i(location, value);
    }

    void setUniform1f(char *uniformName, GLfloat value) {
        GLuint location = glGetUniformLocation(ID, uniformName);
        glUniform1f(location, value);
    }

    void setUniform3fv(char *uniformName, GLfloat *value) {
        GLuint location = glGetUniformLocation(ID, uniformName);
        glUniform3fv(location, 1, value);
    }

    void setUniform4fv(char *uniformName, GLfloat *value) {
        GLuint location = glGetUniformLocation(ID, uniformName);
        glUniform4fv(location, 1, value);
    }

    void uniformMat4(int count, glm::mat4 mat4, GLuint location) {
        glUniformMatrix4fv(location, count, GL_FALSE, &mat4[0][0]);
    }
};

