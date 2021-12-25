#include "Render.h"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

void GLCheckError() {

    while (GLenum error = glGetError()) {

        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
    }
}

void GLAPIENTRY MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}