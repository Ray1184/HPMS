/**
 * File GLRenderer.cpp
 */
#include "GLRenderer.h"


void hpms::GLRenderer::MeshInit(hpms::Mesh& mesh)
{
    // Generate and assign VAO.
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    mesh.SetVaoId(vao);
    glBindVertexArray(mesh.GetVaoId());

    // Positions.
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    mesh.AddVbo(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.GetPositions()[0] * mesh.GetPositions().size()),
                 &mesh.GetPositions()[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

    // UVs.
    glGenBuffers(1, &vbo);
    mesh.AddVbo(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.GetTextCoords()[0] * mesh.GetTextCoords().size()),
                 &mesh.GetTextCoords()[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

    // Normals.
    glGenBuffers(1, &vbo);
    mesh.AddVbo(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.GetNormals()[0] * mesh.GetNormals().size()),
                 &mesh.GetNormals()[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, 0);

    // Weights.
    glGenBuffers(1, &vbo);
    mesh.AddVbo(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.GetWeights()[0] * mesh.GetWeights().size()),
                 &mesh.GetWeights()[0], GL_STATIC_DRAW);
    glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, 0);

    // Joints.
    glGenBuffers(1, &vbo);
    mesh.AddVbo(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.GetJointIndices()[0] * mesh.GetJointIndices().size()),
                 &mesh.GetJointIndices()[0], GL_STATIC_DRAW);
    glVertexAttribPointer(4, 4, GL_FLOAT, false, 0, 0);

    // Indices.
    glGenBuffers(1, &vbo);
    mesh.AddVbo(vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh.GetIndices()[0] * mesh.GetIndices().size()),
                 &mesh.GetIndices()[0], GL_STATIC_DRAW);

    // Unbind VBO and VAO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    LOG_DEBUG(std::string("Mesh with name " + mesh.GetName() + " initialized.").c_str());
}

void hpms::GLRenderer::ModelsDraw(Mesh& mesh, Texture* texture, std::vector<hpms::AdvModelItem*>& items,
                                  Transformation& t, Shader& s,
                                  std::function<void(AdvModelItem*, Transformation&, Shader&)> pipelineCallback)
{
    // Texture activation.
    if (mesh.IsTextured())
    {
        glBindTexture(GL_TEXTURE_2D, texture->GetId());
    }

    // Draw the mesh.
    glBindVertexArray(mesh.GetVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);

    // Invoke pipeline callback and then render.
    for (AdvModelItem* item : items)
    {
        pipelineCallback(item, t, s);
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
    for (unsigned int i = 0; i < mesh.GetVboList().size(); i++)
    {
        glDeleteBuffers(1, &mesh.GetVboList()[i]);
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