#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

//static int CreateShader(const std::string& )


static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError() {

    while (GLenum error = glGetError()) {

        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
    }
}

static void GLAPIENTRY MessageCallback(GLenum source,
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

    //std::cout << glGetString(GL_VERSION) << std::endl;


    unsigned int vertexShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1,&vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1,&fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << std::endl;
    }

    // link shaders 

    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }



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
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float) ,0);

    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
       

        glDrawArrays(GL_TRIANGLES, 0, 6);
       // glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,0);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}