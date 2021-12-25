#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Render.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h";
#include "Shader.h";

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 u_Color;\n"
"void main()\n"
"{\n"
"   FragColor = u_Color;\n"
"}\n\0";
    
int main(void)
{
    glEnable(GL_DEBUG_OUTPUT);

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,GL_TRUE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    if (glewInit() != GLEW_OK) {
        std::cout << "Glew init Error" << std::endl;
    }

    glDebugMessageCallback(MessageCallback, 0);


    Shader shader(vertexShaderSource, fragmentShaderSource);
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);


    float myfloats[] = {
       -0.5f, -0.5f, // 0 
        0.5f, -0.5f, // 1
        0.5f,  0.5f,  // 2
       -0.5f,  0.5f  // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };


    VertexBuffer vb(myfloats, 4 * 2 * sizeof(float));
    IndexBuffer ib(indices,6);

    VertexArray va;
    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        va.Bind();
        ib.Bind();
        

        //glDrawArrays(GL_TRIANGLES, 0, 6);
       glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}