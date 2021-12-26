#include "Shader.h";
#include "Render.h";


Shader::Shader(const char* vertexSource, const char* fragmentSource)
{
    unsigned int vertexShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexSource, NULL);
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

    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << std::endl;
    }

    // link shaders 

     m_ShaderID = glCreateProgram();

    glAttachShader(m_ShaderID, vertexShader);
    glAttachShader(m_ShaderID, fragmentShader);

    glLinkProgram(m_ShaderID);
    glValidateProgram(m_ShaderID);
    glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &success);


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (!success) {
        glGetProgramInfoLog(m_ShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

Shader::~Shader()
{
    glDeleteProgram(m_ShaderID);
}

void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{
    glUniform4f(getUniformLocation(name), v1, v2, v3, v4);
}

void Shader::SetUniformi(const std::string& name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

void Shader::Bind() const
{
    glUseProgram(m_ShaderID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

int Shader::getUniformLocation(const std::string& name)
{	
    if (m_LocationCache.find(name) != m_LocationCache.end()) {
        return m_LocationCache[name];
    }

    int loc = glGetUniformLocation(m_ShaderID, name.c_str());

    if (loc == -1) {
        std::cout << "location for uniform does not exist" << std::endl;
    }

    m_LocationCache[name] = loc;

    return  m_LocationCache[name];
}


