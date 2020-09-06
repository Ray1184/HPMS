/*!
 * File GLShader.cpp
 */

#include "GLShader.h"

GLuint hpms::GLShader::CreateShader(const char* shaderCode, GLuint type)
{
    GLuint shaderId = glCreateShader(type);
    if (!shaderId)
    {
        std::stringstream ss;

        ss << "Could not create ";
        if (type == GL_VERTEX_SHADER)
        {
            ss << "VERTEX SHADER";
        } else
        {
            ss << "FRAGMENT SHADER";
        }
        LOG_ERROR(ss.str().c_str());
    }

    glShaderSource(shaderId, 1, &shaderCode, NULL);
    glCompileShader(shaderId);

    GLint compiled = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
        glDeleteShader(shaderId);
        std::string str(errorLog.begin(), errorLog.end());
        LOG_ERROR(str.c_str());
    }

    glAttachShader(programId, shaderId);

    return shaderId;

}

void hpms::GLShader::Link()
{

    glLinkProgram(programId);
    GLint linked = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(programId, maxLength, &maxLength, &errorLog[0]);
        glDeleteProgram(programId);
        std::string str(errorLog.begin(), errorLog.end());
        LOG_ERROR(str.c_str());
    }

    if (vsId != 0)
    {
        glDetachShader(programId, vsId);
    }
    if (fsId != 0)
    {
        glDetachShader(programId, fsId);
    }

    glValidateProgram(programId);

    GLint validated = 0;
    glGetProgramiv(programId, GL_VALIDATE_STATUS, &validated);
    if (validated == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> warnLog(maxLength);
        glGetProgramInfoLog(programId, maxLength, &maxLength, &warnLog[0]);
        glDeleteProgram(programId);
        std::string str(warnLog.begin(), warnLog.end());
        LOG_WARN(str.c_str());
    }

}
