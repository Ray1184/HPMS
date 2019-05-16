/**
 * File GLRenderer.cpp
 */
#include "GLRenderer.h"
#include "../ResourceCache.h"

void hpms::GLRenderer::QuadMeshInit()
{
    glGenVertexArrays(1, &quadVao);
    glBindVertexArray(quadVao);

    static GLfloat vertices[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f
    };

    // Positions.
    glGenBuffers(1, &quadVbo);
    glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Unbind VBO and VAO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    LOG_DEBUG(std::string("Pictures quad initialized.").c_str());
}

void hpms::GLRenderer::MeshInit(const hpms::Mesh& mesh)
{

    // Generate and assign VAO.
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    vaoMap[mesh.GetKey()] = vao;

    // Positions.
    GLuint vbo;
    glGenBuffers(1, &vbo);
    vbosMap[mesh.GetKey()].push_back(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.GetPositions().size() * sizeof(float),
                 mesh.GetPositions().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) nullptr);


    // UVs (only for textured meshes).
    if (mesh.IsTextured())
    {
        glGenBuffers(1, &vbo);
        vbosMap[mesh.GetKey()].push_back(vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, mesh.GetTextCoords().size() * sizeof(float),
                     mesh.GetTextCoords().data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    // Normals.
    glGenBuffers(1, &vbo);
    vbosMap[mesh.GetKey()].push_back(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.GetNormals().size() * sizeof(float),
                 mesh.GetNormals().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Weights.
    glGenBuffers(1, &vbo);
    vbosMap[mesh.GetKey()].push_back(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.GetWeights().size() * sizeof(float),
                 mesh.GetWeights().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Joints.
    glGenBuffers(1, &vbo);
    vbosMap[mesh.GetKey()].push_back(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.GetJointIndices().size() * sizeof(unsigned int),
                 mesh.GetJointIndices().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Indices.
    glGenBuffers(1, &vbo);
    vbosMap[mesh.GetKey()].push_back(vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndices().size() * sizeof(unsigned int),
                 mesh.GetIndices().data(), GL_STATIC_DRAW);


    // Unbind VBO and VAO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    LOG_DEBUG(std::string("Mesh with key " + mesh.GetKey() + " initialized.").c_str());
}

void
hpms::GLRenderer::ModelsDraw(const std::unordered_map<const AdvModelItem*, std::vector<Entity*>>& modelToEntitiesMap,
                             Shader* s, Camera* c, Window* w,
                             std::function<void(Entity*, Shader*, Camera*, Window* w)> pipelineCallback)
{


    for (const auto& entry : modelToEntitiesMap)
    {
        const AdvModelItem* item = entry.first;

        for (const Mesh& mesh : item->GetMeshes())
        {

            s->SetUniform(UNIFORM_MATERIAL, mesh.GetMaterial());
            if (mesh.IsTextured())
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texBufferMap[mesh.GetMaterial().GetTextureName()]);
            }

            // Draw the mesh.
            glBindVertexArray(vaoMap[mesh.GetKey()]);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            glEnableVertexAttribArray(3);
            glEnableVertexAttribArray(4);

            for (Entity* entity : entry.second)
            {
                pipelineCallback(entity, s, c, w);
                glDrawElements(GL_TRIANGLES, mesh.GetVertexCount(), GL_UNSIGNED_INT, nullptr);
            }



            // Restore state.
            glDisableVertexAttribArray(4);
            glDisableVertexAttribArray(3);
            glDisableVertexAttribArray(2);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(0);
            glBindVertexArray(0);

            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}

void hpms::GLRenderer::QuadsDraw(const std::string& textureName)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texBufferMap[textureName]);

    glBindVertexArray(quadVao);
    glEnableVertexAttribArray(0);

    // Draw the mesh.
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Restore state.
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);

}

void hpms::GLRenderer::MeshCleanup(const hpms::Mesh& mesh)
{
    glDisableVertexAttribArray(0);

    // Delete the VBOs
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    for (GLuint buffer : vbosMap[mesh.GetKey()])
    {
        glDeleteBuffers(1, &buffer);
    }

    LOG_DEBUG(std::string("Mesh with key " + mesh.GetKey() + " cleanup done.").c_str());
}

void hpms::GLRenderer::TextureInit(const hpms::Texture& text)
{
    // Texture binding.
    unsigned int id;
    glGenTextures(1, &id);

    texBufferMap[text.GetPath()] = id;
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, text.GetWidth(),
                 text.GetHeight(), 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, text.GetData());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    LOG_DEBUG(std::string("Texture with name " + text.GetPath() + " initialized.").c_str());
}

void hpms::GLRenderer::TextureCleanup(const hpms::Texture& text)
{
    unsigned int id = texBufferMap[text.GetPath()];
    glDeleteTextures(1, &id);

    LOG_DEBUG(std::string("Texture with name " + text.GetPath() + " cleanup done.").c_str());

}

void hpms::GLRenderer::QuadMeshCleanup()
{
    glDisableVertexAttribArray(0);

    // Delete the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &quadVbo);

    LOG_DEBUG(std::string("Pictures quad cleanup done.").c_str());
}

void hpms::GLRenderer::ClearAllBuffers()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

}

void hpms::GLRenderer::ClearDepthBuffer()
{

    glClear(GL_DEPTH_BUFFER_BIT);

}