#include <core.h>
#include <imgui-SFML.h>
#include <imgui.h>

void SetCustomImGuiTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Arrondis et espacements
    style.WindowRounding    = 6.0f;
    style.FrameRounding     = 4.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding      = 4.0f;
    style.ItemSpacing       = ImVec2(8.0f, 6.0f);
    style.WindowPadding     = ImVec2(12.0f, 8.0f);

    // Palette de couleurs
    colors[ImGuiCol_WindowBg]           = ImVec4(0.12f, 0.12f, 0.14f, 1.0f);
    colors[ImGuiCol_Border]             = ImVec4(0.25f, 0.25f, 0.28f, 1.0f);
    colors[ImGuiCol_FrameBg]            = ImVec4(0.20f, 0.22f, 0.25f, 1.0f);
    colors[ImGuiCol_FrameBgHovered]     = ImVec4(0.30f, 0.32f, 0.35f, 1.0f);
    colors[ImGuiCol_FrameBgActive]      = ImVec4(0.35f, 0.37f, 0.40f, 1.0f);
    colors[ImGuiCol_TitleBg]            = ImVec4(0.10f, 0.10f, 0.12f, 1.0f);
    colors[ImGuiCol_TitleBgActive]      = ImVec4(0.15f, 0.15f, 0.18f, 1.0f);
    colors[ImGuiCol_Button]             = ImVec4(0.25f, 0.28f, 0.32f, 1.0f);
    colors[ImGuiCol_ButtonHovered]      = ImVec4(0.35f, 0.38f, 0.42f, 1.0f);
    colors[ImGuiCol_ButtonActive]       = ImVec4(0.40f, 0.43f, 0.48f, 1.0f);
    colors[ImGuiCol_Header]             = ImVec4(0.25f, 0.28f, 0.32f, 1.0f);
    colors[ImGuiCol_HeaderHovered]      = ImVec4(0.35f, 0.38f, 0.42f, 1.0f);
    colors[ImGuiCol_HeaderActive]       = ImVec4(0.40f, 0.43f, 0.48f, 1.0f);
    colors[ImGuiCol_CheckMark]          = ImVec4(0.80f, 0.40f, 0.40f, 1.0f);
    colors[ImGuiCol_SliderGrab]         = ImVec4(0.80f, 0.40f, 0.40f, 1.0f);
    colors[ImGuiCol_SliderGrabActive]   = ImVec4(0.90f, 0.50f, 0.50f, 1.0f);
    colors[ImGuiCol_Text]               = ImVec4(0.95f, 0.95f, 0.96f, 1.0f);
    colors[ImGuiCol_Tab]              = ImVec4(0.25f, 0.28f, 0.32f, 1.0f);
    colors[ImGuiCol_TabHovered]       = ImVec4(0.35f, 0.38f, 0.42f, 1.0f);
    colors[ImGuiCol_TabActive]        = ImVec4(0.40f, 0.43f, 0.48f, 1.0f);
    colors[ImGuiCol_TabUnfocused]     = ImVec4(0.20f, 0.22f, 0.25f, 1.0f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.28f, 0.30f, 0.34f, 1.0f);
    colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.35f, 0.38f, 0.42f, 1.0f);
}

Core::Core(){
    Start();
    while (window.isOpen()) {
        Event();
        Update();
        Render();
    }
    delete editor;
    delete engine;
    ImGui::SFML::Shutdown();
}

void Core::Start()
{
	window.create(sf::VideoMode::getDesktopMode(), "RPG Maker");
	ImGui::SFML::Init(window);
    SetCustomImGuiTheme();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    engine = new RPGEngine;
    engine->start();
    editor = new Editor(engine);
    editor->start();
}

void Core::Event()
{
    while (const std::optional event = window.pollEvent())
    {
        ImGui::SFML::ProcessEvent(window, *event);
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void Core::Update()
{
    sf::Time time = deltaClock.restart();
    deltaTime = time.asSeconds();
    ImGui::SFML::Update(window, time);

    
    ImGui::DockSpaceOverViewport(0U, ImGui::GetMainViewport());

    engine->update(deltaTime);
    editor->update(deltaTime);
}

void Core::Render() 
{
    window.clear();
    ImGui::SFML::Render(window);
    window.display();
}