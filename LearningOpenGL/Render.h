#pragma once

#include <GL/glew.h>
#include <iostream>
#include "VertexArray.h";
#include "IndexBuffer.h";
#include "Shader.h";

void GLClearError();

void GLCheckError();

void GLAPIENTRY MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam);

class Render
{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};