/**
 * File GLRenderer.cpp
 */
#include "GLRenderer.h"

void hpms::GLRenderer::MeshInit(hpms::Mesh& mesh)
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

    LOG_DEBUG(std::string("Mesh with name " + mesh.GetName() + " initialized.").c_str());
}

void hpms::GLRenderer::ModelsDraw(Mesh& mesh, Texture* texture, const AdvModelItem* currentItem,
                                  const std::unordered_map<const AdvModelItem*, std::vector<Entity*>>& itemsMap,
                                  Shader* s,
                                  std::function<void(const AdvModelItem*, Entity*, Shader*)> pipelineCallback)
{
    // Texture activation.
    if (mesh.IsTextured())
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->GetId());
    }

    // Draw the mesh.
    glBindVertexArray(vaoMap[mesh.GetKey()]);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);


    // Invoke pipeline callback and then render.
    for (Entity* entity : itemsMap.at(currentItem))
    {
        pipelineCallback(currentItem, entity, s);
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

void hpms::GLRenderer::MeshCleanup(hpms::Mesh& mesh)
{
    glDisableVertexAttribArray(0);

    // Delete the VBOs
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    for (GLuint buffer : vbosMap[mesh.GetKey()])
    {
        glDeleteBuffers(1, &buffer);
    }

    LOG_DEBUG(std::string("Mesh with name " + mesh.GetName() + " cleanup done.").c_str());
}

void hpms::GLRenderer::TextureInit(hpms::Texture& text)
{
    // Texture binding.
    unsigned int id;
    glGenTextures(1, &id);

    text.SetId(id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, text.GetWidth(),
                 text.GetHeight(), 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, text.GetData());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    LOG_DEBUG(std::string("Texture with name " + text.GetPath() + " initialized.").c_str());
}

void hpms::GLRenderer::TextureCleanup(hpms::Texture& text)
{
    unsigned int id = text.GetId();
    glDeleteTextures(1, &id);
    text.SetId(id);

    LOG_DEBUG(std::string("Texture with name " + text.GetPath() + " cleanup done.").c_str());

}

void hpms::GLRenderer::ClearBuffer()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

}