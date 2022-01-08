#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Render.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h";
#include "Shader.h";
#include "VertexBufferLayout.h";
#include "Texture.h";
#include "vendor/glm/glm/glm.hpp";
#include "vendor/glm/glm/gtc/matrix_transform.hpp";

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec4 aPos;\n"
"layout (location = 1) in vec2 texCoord;\n"

"out vec2 v_TexCoord;\n"

"uniform mat4 u_MVP;\n"

"void main()\n"
"{\n"
"   gl_Position = u_MVP * aPos;\n"
"   v_TexCoord = texCoord;\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"layout (location = 0) out vec4 FragColor;\n"
"in vec2 v_TexCoord;\n"
"uniform sampler2D u_Texture;\n"
"void main()\n"
"{\n"
"   vec4 texColor = texture(u_Texture, v_TexCoord);\n"
"   FragColor = texColor;\n"
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
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
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



    Shader shader(vertexShaderSource,fragmentShaderSource);
    shader.Bind();
    //shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

    Texture tex("xerg.png");
    tex.Bind();
    shader.SetUniformi("u_Texture",0);


    float myfloats[] = {
        100.0f, 100.0f, 0.0f, 0.0f, // 0 
        200.0f, 100.0f, 1.0f, 0.0f, // 1
        200.0f, 200.0f, 1.0f, 1.0f, // 2
        100.0f, 200.0f, 0.0f, 1.0f, // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };


    VertexBuffer vb(myfloats, 4 * 4 * sizeof(float));
    IndexBuffer ib(indices,6);

    VertexArray va;
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    glm::mat4 proj = glm::ortho(0.0f,960.0f,0.0f,540.0f,-1.0f,1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

    glm::mat4 mvp = proj * view * model;

    shader.SetUniformMat4f("u_MVP", mvp);

    Render render;

    render.Draw(va, ib, shader);
  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

    

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        render.Draw(va, ib, shader);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}