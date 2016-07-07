//
//  GLSLProgram.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/25/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef GLSLProgram_h
#define GLSLProgram_h

#include <OpenGl/OpenGl.h>
#include <string>
#include <glm/glm.hpp>

namespace TacticsEngine {
    class GLSLProgram {
    public:
        GLSLProgram();
        ~GLSLProgram();
        bool load(const std::string& vertFilePath, const std::string& fragFilePath);
        
        void use();
        void disable();
        
        void addAttribute(const std::string& attrib);
        GLint getUniformLocation(const std::string uniform) const;
        void setUniform1f(const std::string& uniform, float a);
        void setUniform2fv(const std::string& uniform, GLsizei count, const float* a);
        void setUniform1i(const std::string& uniform, GLint a);
        void setUniformMatrix4fv(const std::string& uniform, const glm::mat4& matrix);
    private:
        void loadShaderSource(GLuint shader, const char* src);
        bool compile();
        bool compile(GLuint shader);
        bool link();
        
        
        GLuint _program;
        GLuint _vertexShader;
        GLuint _fragmentShader;
        int _numAttributes;
        bool _isInUse;
    };
}
#endif /* GLSLProgram_h */
