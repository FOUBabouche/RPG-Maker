#include "editor.h"

#include <imgui-SFML.h>
#include <imgui.h>

void Editor::Start() {
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

}

void Editor::Update() {
	ImGui::DockSpaceOverViewport(0U,ImGui::GetMainViewport());

	ImGui::Begin("Editor");

	ImGui::BeginTabBar("TabBar");

	if (ImGui::TabItemButton("Map Palette")) {

	}
	if (ImGui::TabItemButton("Entity palette")) {

	}

	ImGui::EndTabBar();

	ImGui::End();
}