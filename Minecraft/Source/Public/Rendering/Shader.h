#pragma once

#include "glm/glm.hpp"

#include <string>
#include <unordered_map>

struct FShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind();

public:
    // Uniforms
    void SetUniform1i(const std::string& name, int i1);
    void SetUniform1f(const std::string& name, float f1);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniform4fv(const std::string& name, const glm::vec4& vector);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
    
private:
    unsigned int CreateShader(const std::string& ShaderFilePath);
    unsigned int CompileShader(unsigned int Type, const std::string& Source);
    FShaderProgramSource ParseShader(const std::string& FilePath);

    int GetUniformLocation(const std::string& name);

private:
    unsigned int RendererID;
    std::string FilePath;
    std::unordered_map<std::string, int> UniformLocationCache;
};
