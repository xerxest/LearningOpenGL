#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

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

    std::cout << glGetString(GL_VERSION) << std::endl;

    float myfloats[] = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f,-0.5f };


    unsigned int mybuff;

    glGenBuffers(1, &mybuff);

    std::cout << mybuff << std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, mybuff);
    
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float),myfloats,mybuff);

    //glVertexAttribPointer(0, 2 * sizeof(float));

    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);

        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);

        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}