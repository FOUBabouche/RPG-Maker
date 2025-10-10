#include "editor.h"

#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

void Editor::Start() {
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void Editor::Update(Engine& engine) {
	ImGui::DockSpaceOverViewport(0U,ImGui::GetMainViewport());

	engineWin.Draw(engine, camera);
	camera.SetRenderTarget(engineWin);

	engineWin.GetMousePos(camera);

	sf::Vector2u mPos = engine.grid.GetMouseToGridPos(engineWin.GetMousePos(camera));
	std::cout << mPos.x << " " << mPos.y << std::endl;

	ImGui::Begin("Editor");

	ImGui::BeginTabBar("TabBar");

	if (ImGui::TabItemButton("Map Palette")) {

	}
	if (ImGui::TabItemButton("Entity palette")) {

	}

	ImGui::EndTabBar();

	ImGui::End();
}