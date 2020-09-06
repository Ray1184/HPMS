/*!
 * File GLShader.h
 */

#pragma once

#include <glad/glad.h>
#include <unordered_map>
#include <sstream>
#include <glm/ext.hpp>
#include <iostream>
#include "../Shader.h"
#include "../../common/Utils.h"
#include "../Names.h"

#ifndef TRANSPOSE_MATRICES
#define TRANSPOSE GL_FALSE
#else
#define TRANSPOSE GL_TRUE
#endif

namespace hpms
{
    class GLShader : public hpms::Shader
    {

    public:

        GLShader() : clear(false)
        {

        }

        virtual ~GLShader()
        {
            Cleanup();
        }

        inline void Init() override
        {
            programId = glCreateProgram();
            if (!programId)
            {
                LOG_ERROR("Error creating shader program.");
            }
        }

        inline void CreateUniform(const std::string& name) override
        {
            GLint loc = glGetUniformLocation(programId, name.c_str());
            if (loc < 0)
            {
                std::stringstream ss;
                ss << "Uniform with name " << name << " seems not used in shader.";
                LOG_WARN(ss.str().c_str());
            }
            uniforms.insert({name, loc});
        }

        inline void CreateMaterialUniform(const std::string& name) override
        {
            std::stringstream ss;
            ss << name << UNIFORM_DIFFUSE_SFX;
            CreateUniform(ss.str());
            std::stringstream ss2;
            ss2 << name << UNIFORM_HASTEXTURE_SFX;
            CreateUniform(ss2.str());
        }

        inline void SetUniform(const std::string& name, const glm::mat4& val) override
        {
            glUniformMatrix4fv(uniforms[name], 1, TRANSPOSE, glm::value_ptr(val));
        }

        inline void SetUniform(const std::string& name, size_t size, const glm::mat4*& val) override
        {
            glUniformMatrix4fv(uniforms[name], size, TRANSPOSE, glm::value_ptr(val[0]));
        }

        inline void SetUniform(const std::string& name, int val) override
        {
            glUniform1i(uniforms[name], val);
        }

        inline void SetUniform(const std::string& name, float val) override
        {
            glUniform1f(uniforms[name], val);
        }

        inline void SetUniform(const std::string& name, const glm::vec3& val) override
        {
            glUniform3f(uniforms[name], val.x, val.y, val.z);
        }

        inline void SetUniform(const std::string& name, const glm::vec4& val) override
        {
            glUniform4f(uniforms[name], val.x, val.y, val.z, val.w);
        }

        inline void SetUniform(const std::string& name, const hpms::Material& val) override
        {
            std::stringstream ss;
            ss << name << UNIFORM_DIFFUSE_SFX;
            SetUniform(ss.str(), val.GetDiffuse());
            std::stringstream ss2;
            ss2 << name << UNIFORM_HASTEXTURE_SFX;
            SetUniform(ss2.str(), val.GetTextureName().empty() ? 0 : 1);
        }

        inline void CreateVS(const std::string& code) override
        {
            vsId = CreateShader(code.c_str(), GL_VERTEX_SHADER);

        }

        inline void CreateFS(const std::string& code) override
        {
            fsId = CreateShader(code.c_str(), GL_FRAGMENT_SHADER);

        }

        void Link() override;

        inline void Bind() override
        {
            glUseProgram(programId);
        }

        inline void Unbind() override
        {
            glUseProgram(0);
        }

        inline void Cleanup() override
        {
            if (!clear)
            {
                clear = true;
                Unbind();
                if (programId != 0)
                {
                    glDeleteProgram(programId);
                }
            }
        }

        inline const std::string Name() const override
        {
            return "GLShader";
        }

    private:

        GLuint programId;
        GLuint vsId;
        GLuint fsId;
        std::unordered_map<std::string, GLuint> uniforms;
        bool clear;

        GLuint CreateShader(const char* shaderCode, GLuint type);

    };
}
