//
//  GLSLProgram.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/25/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "GLSLProgram.h"
#include <OpenGL/gl3.h>
#include <fstream>
#include <vector>
#include "Error.h"
#include "IOManager.h"
namespace TacticsEngine {
    GLSLProgram::GLSLProgram() :
        _program(0), _vertexShader(0), _fragmentShader(0), _numAttributes(0), _isInUse(false)
    {
        
    }
    GLSLProgram::~GLSLProgram() {
        
    }
    
    bool GLSLProgram::load(const std::string& vertFilePath, const std::string& fragFilePath) {
        // Have OpenGL create the shaders
        _vertexShader = glCreateShader(GL_VERTEX_SHADER);
        if (_vertexShader == 0) {
            Error::getInstance().fail(ErrorCodes::FAILED_TO_CREATE_SHADER);
            return false;
        }
        
        _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        if (_fragmentShader == 0) {
            Error::getInstance().fail(ErrorCodes::FAILED_TO_CREATE_SHADER);
            return false;
        }
        
        std::vector<unsigned char> vertFileContents;
        std::vector<unsigned char> fragFileContents;
        
        IOManager::getInstance().readTextFileToBuffer(vertFilePath, vertFileContents);
        IOManager::getInstance().readTextFileToBuffer(fragFilePath, fragFileContents);
        
        loadShaderSource(_vertexShader, (const char*)&(vertFileContents[0]));
        loadShaderSource(_fragmentShader, (const char*)&(fragFileContents[0]));
        
        if (compile()) {
            addAttribute("vertexPos");
            addAttribute("vertexColor");
            addAttribute("vertexUV");
            return link();
        } else {
            return false;
        }
    }
    
    void GLSLProgram::loadShaderSource(GLuint shader, const char* src) {
        glShaderSource(shader, 1, &src, nullptr);
    }
    
    bool GLSLProgram::compile() {
        _program = glCreateProgram();
        if(compile(_vertexShader) && compile(_fragmentShader)) {
            return true;
        } else {
            glDeleteProgram(_program);
            return false;
        }
    }
    
    bool GLSLProgram::compile(GLuint shader) {
        
        GLint isCompiled = 0;
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        
        if (isCompiled == GL_FALSE) {
            GLint logSize = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
            std::vector<char> errorLog(logSize);
            glGetShaderInfoLog(shader, logSize, &logSize, &(errorLog[0]));
            glDeleteShader(shader);
            
            Error::getInstance().fail(ErrorCodes::FAILED_TO_COMPILE_SHADER, &errorLog[0]);
            return false;
        }
        
        
        return true;
    }
    
    bool GLSLProgram::link() {
        glAttachShader(_program, _vertexShader);
        glAttachShader(_program, _fragmentShader);
        
        glLinkProgram(_program);
        
        GLint isLinked = 0;
        glGetProgramiv(_program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            GLint logSize = 0;
            glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &logSize);
            std::vector<char> errorLog(logSize);
            glGetProgramInfoLog(_program, logSize, &logSize, &(errorLog[0]));
            
            glDeleteProgram(_program);
            glDeleteShader(_vertexShader);
            glDeleteShader(_fragmentShader);
            
            Error::getInstance().fail(ErrorCodes::FAILED_TO_LINK_SHADERS, &errorLog[0]);
            return false;
        }
        
        return true;
    }
    
    void GLSLProgram::addAttribute(const std::string& attrib) {
        if (!_isInUse) {
            glBindAttribLocation(_program, _numAttributes++, attrib.c_str());
        }
    }
    
    void GLSLProgram::use() {
        if (!_isInUse) {
            _isInUse = true;
            glUseProgram(_program);
            for (int i = 0; i < _numAttributes; i++) {
                glEnableVertexAttribArray(i);
            }
        }
    }
    
    void GLSLProgram::disable() {
        if (_isInUse) {
            _isInUse = false;
            glUseProgram(0);
            for (int i = 0; i < _numAttributes; i++) {
                glDisableVertexAttribArray(i);
            }
        }
    }
    
    GLint GLSLProgram::getUniformLocation(const std::string uniform) const {
        GLint loc = glGetUniformLocation(_program, uniform.c_str());
        if (loc == GL_INVALID_INDEX) {
            Error::getInstance().fail(ErrorCodes::UNKNOWN, "Uniform not found: " + uniform);
        }
        return loc;
    }
    
    void GLSLProgram::setUniform1f(const std::string& uniform, float a) {
        glUniform1f(getUniformLocation(uniform), a);
    }
    
    void GLSLProgram::setUniform2fv(const std::string& uniform, GLsizei count, const float* val) {
        glUniform2fv(getUniformLocation(uniform), count, val);
    }
    
    void GLSLProgram::setUniform1i(const std::string& uniform, GLint a) {
        glUniform1i(getUniformLocation(uniform), a);
    }
    void GLSLProgram::setUniformMatrix4fv(const std::string& uniform, const glm::mat4& matrix) {
        //glUniform4fv(<#GLint location#>, <#GLsizei count#>, <#const GLfloat *value#>)
        
        glUniformMatrix4fv(getUniformLocation(uniform), 1, GL_FALSE, &(matrix[0][0]));
    }
    
}
