#include "Rendering/Shader.h"

#include "Framework/Debugger.h"
#include "Rendering/Renderer.h"

#include <fstream>
#include <sstream>

#include "glm/gtc/type_ptr.inl"


Shader::Shader(const std::string& filepath) :
    RendererID(0),
    FilePath(filepath)
{
    RendererID = CreateShader(filepath);
}

Shader::~Shader()
{
    glCall(glDeleteProgram(RendererID))
}


void Shader::Bind() const
{
    glCall(glUseProgram(RendererID))
}

void Shader::Unbind()
{
    glCall(glUseProgram(0))
}

unsigned Shader::CreateShader(const std::string& ShaderFilePath)
{
    FShaderProgramSource Source = ParseShader(ShaderFilePath);
    
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, Source.VertexSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, Source.FragmentSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned Shader::CompileShader(unsigned Type, const std::string& Source)
{
    unsigned int id = glCreateShader(Type);
    const char* src = Source.c_str();
    
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::stringstream stringmessage;
        stringmessage << "OpenGL: failed to compile "  << ((Type == GL_VERTEX_SHADER) ? "vertex" : "fragment") << " shader (" << FilePath << ") : " << message;

        UDebugger::Log(stringmessage.str(), ERROR);
        
        glDeleteShader(id);
        
        return 0;
    }

    return id;
}

FShaderProgramSource Shader::ParseShader(const std::string& FilePath)
{
    std::ifstream stream(FilePath);

    enum class EShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    EShaderType Type = EShaderType::NONE;
    std::stringstream ss[2];
    
    std::string line;
    while(std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                Type = EShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                Type = EShaderType::FRAGMENT;
        }
        else
        {
            if (Type != EShaderType::NONE)
            {
                ss[(int)Type] << line << '\n';
            }
        }
    }

    return { ss[0].str(), ss[1].str() };
}

void Shader::SetUniform1i(const std::string& name, int i1)
{
    glCall(glUniform1i(GetUniformLocation(name), i1))
}

void Shader::SetUniform1f(const std::string& name, float f1)
{
    glCall(glUniform1f(GetUniformLocation(name), f1))
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3))
}

void Shader::SetUniform4fv(const std::string& name, const glm::vec4& vector)
{
    glCall(glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(vector)))
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    glCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]))
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (UniformLocationCache.find(name) != UniformLocationCache.end())
        return UniformLocationCache[name];
    
    glCall(int location = glGetUniformLocation(RendererID, name.c_str()))
    if (location == -1)
    {
        std::stringstream message;
        message << "OpenGl: uniform <" << name << "> doesn't exist";
        UDebugger::Log(message.str(), WARNING);
    }

    UniformLocationCache[name] = location;
    std::stringstream message;
    message << "Shader cached uniform <" << name << "> at location = " << location <<  " : " << FilePath;
    UDebugger::Log(message.str(), NORMAL);
    return location;
}
