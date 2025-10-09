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

	std::cout << engineWin.GetMousePos(camera).x << " " << engineWin.GetMousePos(camera).y << std::endl;

	ImGui::Begin("Editor");

	ImGui::BeginTabBar("TabBar");

	if (ImGui::TabItemButton("Map Palette")) {

	}
	if (ImGui::TabItemButton("Entity palette")) {

	}

	ImGui::EndTabBar();

	ImGui::End();
}