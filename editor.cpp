#include "editor.h"
#include "eMath.h"

#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>


Editor::Editor()
{
	col = new float[4] {0, 0, 0, 0};
}

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
			canBeANewPos = true;
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
	camera.SetRenderTarget(*engineWin.getRender().get(), engineWin.getAvailSize());

	sf::Vector2f mousePos = engineWin.GetMousePos(camera.GetView().getCenter(), camera.GetView().getSize(), zoom);

	sf::Vector2u mousePosOnGrid = engine.grid.GetCoordToGridPos(mousePos);

	if (leftPressed && engineWin.isHover()) {
		if (canBeANewPos) {
			lastMousePos = mousePos;
			canBeANewPos = false;
		}
		if (tool == Move) {
			sf::Vector2f deltaPos = lastMousePos - mousePos;
			camera.SetPosition(camera.GetView().getCenter() + deltaPos);
			engineWin.getRender().get()->setView(camera.GetView());
		}
		if(tool == Paint)engine.grid.SetTile(mousePosOnGrid, brush.GetColor(), &placeHolder);
		if (tool == Erase)engine.grid.RemoveTile(mousePosOnGrid);
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

	if (tool == Paint) {
		if (ImGui::ColorPicker4("Brush Color", col)) {
			brush.SetColor({ static_cast<uint8_t>(col[0] * 255), static_cast<uint8_t>(col[1] * 255), static_cast<uint8_t>(col[2] * 255), static_cast<uint8_t>(col[3] * 255) });
		}
		
	}

	ImGui::BeginTabBar("TabBar");

	if (ImGui::TabItemButton("Map Palette")) {

	}
	if (ImGui::TabItemButton("Entity palette")) {

	}

	ImGui::EndTabBar();

	ImGui::End();
}