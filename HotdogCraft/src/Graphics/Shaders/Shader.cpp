#include "Graphics/Shaders/Shader.h"
#include <filesystem>
#include <fstream>
#include <glad/glad.h>
#include <Graphics/GlHelpers.h>
#include <HotdogCraft.h>
#include <Logger.h>
#include <print>
#include <regex>
#include <string>

namespace HotdogCraft::Graphics::Shaders
{
    Shader::Shader(std::string vertName, std::string fragName)
        : vertName(vertName)
        , fragName(fragName)
    {
        shaderName = std::format("({}, {})", vertName, fragName);

        std::string shaderSource = ReadAndPreProcess(vertName);
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        auto source = shaderSource.c_str();
        glShaderSource(vertexShader, 1, &source, 0);
        glCompileShader(vertexShader);
        glObjectLabel(GL_SHADER, vertexShader, -1, std::format("Shader {}", vertName).c_str());

        shaderSource = ReadAndPreProcess(fragName);
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        source = shaderSource.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);
        glCompileShader(fragmentShader);
        glObjectLabel(GL_SHADER, fragmentShader, -1, std::format("Shader {}", fragName).c_str());

        handle = glCreateProgram();
        glAttachShader(handle, vertexShader);
        glAttachShader(handle, fragmentShader);
        glLinkProgram(handle);
        bind();
        glObjectLabel(GL_PROGRAM, handle, -1, std::format("Program {}", shaderName).c_str());

        glDetachShader(handle, vertexShader);
        glDetachShader(handle, fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        Logger::info("Shader {} compiled", shaderName);

        int count;
        Logger::verbose("Uniforms:");
        glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &count);
        for (int i = 0; i < count; i++)
        {
            char name[100];
            int size;
            u32 type;
            glGetActiveUniform(handle, i, sizeof(name), nullptr, &size, &type, name);
            int location = glGetUniformLocation(handle, name);
            Logger::verbose("    {} {} {}", GlHelpers::getTypeName(type), name, size);
            uniforms[name] = location;
        }

        Logger::verbose("Attributes:");
        glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTES, &count);
        for (int i = 0; i < count; i++)
        {
            char name[100];
            int size;
            u32 type;
            glGetActiveAttrib(handle, i, sizeof(name), nullptr, &size, &type, name);
            int location = glGetAttribLocation(handle, name);
            Logger::verbose("    {} {} {}", GlHelpers::getTypeName(type), name, size);
            attributes[name] = location;
        }
    }

    Shader::~Shader()
    {
        glDeleteProgram(handle);
    }

    void Shader::bind() const
    {
        glUseProgram(handle);
    }

    std::string Shader::ReadAndPreProcess(std::string name)
    {
        static std::regex includeRegex("^\\s*#\\s*include\\s+[\"<](.*)[\">]");

        std::stringstream stream;
        stream << HotdogCraft::ins().getAssetStore().getShader(name);
        std::string line;
        std::string res;
        while (std::getline(stream, line))
        {
            std::smatch matches;
            if (std::regex_search(line, matches, includeRegex))
            {
                res += HotdogCraft::ins().getAssetStore().getShader(matches[1]);
                res += '\n';
                Logger::verbose("Included {}", matches[1].str());
            }
            else
            {
                res += line;
                res += '\n';
            }
        }
        Logger::verbose("Preprocessed source {}", name);
        return res;
    }
}