#pragma once

#include <GL/glew.h>

#include <iostream>

void GLClearError();

void GLCheckError();

void GLAPIENTRY MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam);