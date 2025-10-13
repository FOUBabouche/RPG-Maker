#include "editor.h"

#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

void Editor::Start() {
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	placeHolder.loadFromFile("Placeholder.png");
	
}

void Editor::Event(std::optional<sf::Event> event) {
	if (tool == Paint) {
		if (const auto mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (mouse->button == sf::Mouse::Button::Left) {
				leftPressed = true;
			}
			if (mouse->button == sf::Mouse::Button::Right) {
				rightPressed = true;
			}
		}
		if (const auto mouse = event->getIf<sf::Event::MouseButtonReleased>()) {
			if (mouse->button == sf::Mouse::Button::Left) {
				leftPressed = false;
			}
			if (mouse->button == sf::Mouse::Button::Right) {
				rightPressed = false;
			}
		}
	}

	if (tool == Move) {
		if (const auto wheel = event->getIf<sf::Event::MouseWheelScrolled>()) {
			if (wheel->delta < 0) {
				zoom -= 0.05f;
			}
			if (wheel->delta > 0) {
				zoom += 0.05f;
			}
		}
	}
}

void Editor::Update(Engine& engine, float deltaTime) {
	ImGui::DockSpaceOverViewport(0U,ImGui::GetMainViewport());

	camera.SetZoom(zoom);

	engineWin.Draw(engine, camera);
	camera.Update(deltaTime);
	camera.SetRenderTarget(*engineWin.getRender().get(), engineWin.getAvailSize());

	engineWin.GetMousePos(camera.GetView().getViewport().position, camera.GetZoom());

	sf::Vector2u mPos = engine.grid.GetCoordToGridPos(engineWin.GetMousePos(camera.GetView().getViewport().position, camera.GetZoom()));
	//std::cout << mPos.x << " " << mPos.y << std::endl;

	if (leftPressed) {
		engine.grid.SetTile(mPos, sf::Color::Red, &placeHolder);
	}
	if (rightPressed) {
		engine.grid.RemoveTile(mPos);
	}

	ImGui::Begin("Editor");

	ImGui::BeginTabBar("TabBar");

	ImGui::ImageButton("move", )

	if (ImGui::TabItemButton("Map Palette")) {

	}
	if (ImGui::TabItemButton("Entity palette")) {

	}

	ImGui::EndTabBar();

	ImGui::End();
}