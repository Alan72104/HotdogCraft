#pragma once

#include <string>
#include <unordered_map>

namespace HotdogCraft::Graphics::Shaders
{
    class Shader
    {
    public:
        Shader(std::string vertName, std::string fragName);
        Shader(Shader&) = delete;
        ~Shader();

        void bind() const;

    private:
        int handle;
        std::string vertName;
        std::string fragName;
        std::string shaderName;
        std::unordered_map<std::string, int> uniforms{};
        std::unordered_map<std::string, int> attributes{};

        std::string ReadAndPreProcess(std::string name);
    };
}