#include <cstring>
#include <format>
#include <fwd.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/string_cast.hpp>
#include <Graphics/Shaders/Shader.h>
#include <Graphics/Textures/AtlasTexture.h>
#include <Graphics/Textures/Texture.h>
#include <HotdogCraft.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <malloc.h>
#include <memory>
#include <stb_image.h>
#include <utility>
#include <Utils.h>

namespace HotdogCraft
{
    up<HotdogCraft> HotdogCraft::instance = nullptr;

    HotdogCraft& HotdogCraft::ins()
    {
        return *instance;
    }

    HotdogCraft::HotdogCraft()
        : gameRenderer(*this)
    {
    }

    HotdogCraft::~HotdogCraft()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();
    }

    void HotdogCraft::run()
    {
        initWindow();
        initGame();
        startTime = glfwGetTime();
        mainLoop();
    }

    void HotdogCraft::initWindow()
    {
        glfwInit();

        window = glfwCreateWindow(1366, 768, "HotdogCraft 0.0.1", nullptr, nullptr);
        glfwMakeContextCurrent(window);
        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
        glfwSwapInterval(0);

        glfwSetKeyCallback(window, glfwKeyCallback);

        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::GetStyle().WindowRounding = 9;
        ImGui::GetStyle().ChildRounding = 9;
        ImGui::GetStyle().FrameRounding = 9;
        ImGui::GetStyle().PopupRounding = 9;
        ImGui::GetStyle().GrabRounding = 9;
        auto font = assetStore.getFont("Exo2-Medium.otf");
        auto newData = malloc(font.size());
        assert(newData);
        memcpy(newData, font.data(), font.size());
        ImGui::GetIO().Fonts->AddFontFromMemoryTTF(newData, (int)font.size(), 20);

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
    }

    void HotdogCraft::initGame()
    {
        shaderMain = std::make_unique<Graphics::Shaders::Shader>("main.vert", "main.frag");
        atlas = std::make_unique<Graphics::Textures::TextureAtlas>("atlas");
        //atlas->addTexture(Graphics::Texture("dirt.png"));
        //atlas->addTexture(Graphics::Texture("grass_block_side.png"));
        //atlas->addTexture(Graphics::Texture("grass_block_top.png"));
        for (const auto& entry :
            std::filesystem::directory_iterator(assetStore.getAssetDir() / "textures"))
        {
            if (entry.is_regular_file() && entry.path().filename().string().ends_with(".png"))
            {
                atlas->addTexture(Graphics::Textures::Texture(entry.path().filename().string()));
            }
        }
        atlas->stitchAll();

        glViewport(0, 0, windowWidth, windowHeight);
        glClearColor(130 / 255.0f, 40 / 255.0f, 138 / 255.0f, 1.0f);
    }

    void HotdogCraft::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {

    }

    void HotdogCraft::mainLoop()
    {
        while (true)
        {
            if (glfwWindowShouldClose(window))
                break;

            double time = glfwGetTime();
            double updateDelay = ((1 / targetUpdateFreq) - updateTimer.getAvg()) - (time - lastUpdateTime);
            double renderDelay = ((1 / targetRenderFreq) - renderTimer.getAvg()) - (time - lastRenderTime);

            glfwWaitEventsTimeout(std::max(std::min(updateDelay, renderDelay), 0.0));

            processInput();

            time = glfwGetTime();
            updateDelay = ((1 / targetUpdateFreq) - updateTimer.getAvg()) - (time - lastUpdateTime);
            renderDelay = ((1 / targetRenderFreq) - renderTimer.getAvg()) - (time - lastRenderTime);

            if (updateDelay <= 0.0)
                update();
            if (renderDelay <= 0.0)
                render();

            if (titleTimer.checkElapsedAndReset())
            {
                glfwSetWindowTitle(window, std::format("{} #{} upd {:.2f} ren {:.2f}",
                    windowTitle,
                    Utils::formatCommas(frameCount),
                    updateTimer.getAvg() * 1000,
                    renderTimer.getAvg() * 1000).c_str());
            }
        }
    }

    void HotdogCraft::processInput()
    {
    }

    void HotdogCraft::update()
    {
        auto _ = updateTimer.time();
        lastUpdateTime = glfwGetTime();
    }

    void HotdogCraft::renderImgui()
    {
        if (imguiDemoWindow)
            ImGui::ShowDemoWindow(&imguiDemoWindow);

        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoDocking | //ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove;
        constexpr float PAD = 5.0f;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
        ImVec2 work_size = viewport->WorkSize;
        ImVec2 window_pos(work_pos.x + PAD, work_pos.y + PAD);
        ImVec2 window_pos_pivot;
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::SetNextWindowBgAlpha(0.35f);
        if (ImGui::Begin("Main overlay", nullptr, windowFlags))
        {
            ImGui::Text(windowTitle.c_str());
            ImGui::Text(std::format("Upd {:.2f} Ren {:.2f}",
                updateTimer.getAvg() * 1000,
                renderTimer.getAvg() * 1000).c_str());
            ImGui::Separator();
        }
        ImGui::End();

        if (ImGui::Begin("Debug"))
        {
            auto& textures = atlas->getTextures();
            ImGui::TextF("Atlas texture count: {}", textures.size());
            ImGui::Image((void*)atlas->getHandle(),
                ImVec2(atlas->getTexSize().x, atlas->getTexSize().y),
                ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1), ImVec4(1, 1, 1, 1));
        }
        ImGui::End();
    }

    void HotdogCraft::render()
    {
        auto _ = renderTimer.time();
        lastRenderTime = glfwGetTime();
        frameCount++;

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        renderImgui();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
}