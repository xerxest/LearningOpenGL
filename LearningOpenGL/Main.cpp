#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


static int CreateShader(const std::string& )

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

    float myfloats[6] = {
       -0.5f, -0.5f, 
        0.0f,  0.5f, 
        0.5f, -0.5f 
    };


    unsigned int mybuff;
    glGenBuffers(1, &mybuff);
    glBindBuffer(GL_ARRAY_BUFFER, mybuff);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float),myfloats, GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, sizeof(float)*2 ,0);

    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,NULL);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}