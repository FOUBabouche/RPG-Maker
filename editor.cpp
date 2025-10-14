#include "editor.h"

#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

void Editor::Start() {
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	placeHolder.loadFromFile("Placeholder.png");
	moveButton.loadFromFile("MoveButton.png");
	paintButton.loadFromFile("PaintButton.png");
	eraseButton.loadFromFile("EraseButton.png");
}

void Editor::Event(std::optional<sf::Event> event) {
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
		if(tool == Paint)engine.grid.SetTile(mPos, sf::Color::Red, &placeHolder);
		if (tool == Erase)engine.grid.RemoveTile(mPos);
	}

	ImGui::Begin("Editor");

	if(ImGui::ImageButton("move", moveButton, { 32, 32 })) {
		tool = Move;
	}
	ImGui::SameLine();
	if (ImGui::ImageButton("paint", paintButton, { 32, 32 })) {
		tool = Paint;
	}
	ImGui::SameLine();
	if(ImGui::ImageButton("erase", eraseButton, { 32, 32 })) {
		tool = Erase;
	}

	ImGui::BeginTabBar("TabBar");

	if (ImGui::TabItemButton("Map Palette")) {

	}
	if (ImGui::TabItemButton("Entity palette")) {

	}

	ImGui::EndTabBar();

	ImGui::End();
}