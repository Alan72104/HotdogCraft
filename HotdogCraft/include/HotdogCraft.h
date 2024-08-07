#pragma once

#include <AssetStore.h>
#include <Camera.h>
#include <fwd.h>
#include <GameRenderer.h>
#include <GLFW/glfw3.h>
#include <Graphics/Shaders/Shader.h>
#include <Graphics/Textures/TextureAtlas.h>
#include <ScopeTimer.h>
#include <string>
#include <Timer.h>

namespace HotdogCraft
{
    class HotdogCraft
    {
    public:
        static up<HotdogCraft> instance;
        static HotdogCraft& ins();

        HotdogCraft();
        ~HotdogCraft();
        AssetStore& getAssetStore() { return assetStore; }
        GameRenderer& getGameRenderer() { return gameRenderer; }

        void run();

    private:
        GLFWwindow* window{ nullptr };
        std::string windowTitle{ "HotdogCraft 0.0.1" };
        int windowWidth{ 0 };
        int windowHeight{ 0 };
        u64 frameCount{ 0 };
        double startTime{ 0 };
        double lastUpdateTime{ 0 };
        double lastRenderTime{ 0 };
        double targetUpdateFreq{ 20 };
        double targetRenderFreq{ 120 };
        ScopeTimer updateTimer{ 60 };
        ScopeTimer renderTimer{ 60 };
        Timer titleTimer{ 0.5 };
        bool imguiDemoWindow{ false };
        AssetStore assetStore{};
        GameRenderer gameRenderer;
        Camera camera{};
        up<Graphics::Shaders::Shader> shaderMain{};
        up<Graphics::Textures::TextureAtlas> atlas{};

        static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        void initWindow();
        void initGame();
        void mainLoop();
        void processInput();
        void update();
        void renderImgui();
        void render();

        void loadWorld();
    };
}
