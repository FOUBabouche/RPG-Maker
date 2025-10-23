#include "editor.h"
#include "eMath.h"
#include "tool.h"

#include <iostream>

#include <SFML/Graphics/Sprite.hpp>
#include <imgui-SFML.h>
#include <imgui.h>


Editor::Editor()
{
	col = new float[3] {1, 1, 1};
}

Editor::~Editor() {
	delete[]col;
	delete currentTexture;
}

void Editor::Start() {
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	placeHolder = new sf::Texture("Placeholder.png");
	moveButton = new sf::Texture("MoveButton.png");
	paintButton = new sf::Texture("PaintButton.png");
	eraseButton = new sf::Texture("EraseButton.png");
	textureButton = new sf::Texture("TextureButton.png");

	brush.SetTexure(placeHolder);
	brush.SetUV({ {0, 0}, {(int)brush.GetTexture()->getSize().x, (int)brush.GetTexture()->getSize().y} });
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
				if (zoom <= 0.05f)
					zoom = 0.05f;
			}
			if (wheel->delta > 0) {
				zoom += 0.05f;
				if (zoom >= 7.f)
					zoom = 7.f;
			}
		}
	}
}

void Editor::Update(Engine& engine, float deltaTime) {
	ImGui::DockSpaceOverViewport(0U,ImGui::GetMainViewport());

	engineWin.Draw(engine, camera);
	camera.SetRenderTarget(*engineWin.getRender().get(), engineWin.getAvailSize());

	sf::Vector2f mousePos = engineWin.GetMousePos(camera.GetView().getCenter(), camera.GetView().getSize(), zoom);
	camera.SetZoom(zoom);

	sf::Vector2u mousePosOnGrid = engine.grid.GetCoordToGridPos(mousePos);

	if (leftPressed && engineWin.isHover()) {
		if (canBeANewPos) {
			lastMousePos = mousePos;
			canBeANewPos = false;
		}
		if (tool == Move) {
			sf::Vector2f deltaPos = lastMousePos - mousePos;
			camera.SetPosition(camera.GetView().getCenter() + deltaPos * zoom);
			engineWin.getRender().get()->setView(camera.GetView());
		}
		if (mousePos.x >= 0 && mousePos.y >= 0) {
			if (tool == Paint)engine.grid.SetTile(mousePosOnGrid, brush.GetColor(), brush.GetTexture(), brush.GetUV());
			if (tool == Erase)engine.grid.RemoveTile(mousePosOnGrid);
		}
	}

	if (tool == Paint) {
		if(brushWinIsOpen)
		{
			if (ImGui::Begin("Brush", &brushWinIsOpen)) {
				if (ImGui::ColorPicker3("Brush Color", col, 0)) {
					brush.SetColor({ static_cast<uint8_t>(col[0] * 255), static_cast<uint8_t>(col[1] * 255), static_cast<uint8_t>(col[2] * 255), 255 });
				}
				ImGui::SeparatorText("Current Texture");
				ImGui::Image(*brush.GetTexture(), { 128 , 128 }, {0, 0}, {1, 1});

				ImGui::End();
			}
		}
	}

	if (tool == Paint) {
		if (selectTextureWinIsOpen)
		{
			if (ImGui::Begin("Texture Palette", &selectTextureWinIsOpen)) {
				if(ImGui::Button("Add Texture")) {
					texturesPaths.push_back(getFilePathByDialog());
					currentTexturePath = texturesPaths[texturesPaths.size()-1];
					currentTexture = new sf::Texture(currentTexturePath);
				}
				if (texturesPaths.size() > 0) {
					if (ImGui::BeginCombo("Texture List", currentTexturePath.c_str())) {
						for (size_t i = 0; i < texturesPaths.size(); i++)
						{
							bool is_selected = (currentTexturePath == texturesPaths[i]);
							if (ImGui::Selectable(texturesPaths[i].c_str(), is_selected)) {
								currentTexturePath = texturesPaths[i];
								currentTexture = new sf::Texture(currentTexturePath);
							}
						}
						ImGui::EndCombo();
					}

					ImGui::SeparatorText("Current Texture");

					// IMAGE DE LA TEXTURE MA GUEULE
					for (int x = 0; x < currentTexture->getSize().x; x += engine.grid.getTileSize().x)
					{
						for (int y = 0; y < currentTexture->getSize().y; y += engine.grid.getTileSize().y)
						{
							sf::Sprite texturePart(*currentTexture, { {y, x}, {(int)engine.grid.getTileSize().x,(int)engine.grid.getTileSize().y} });
							ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
							ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
							ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));
							ImGui::ImageButton(std::string(std::to_string(x)+" "+ std::to_string(y)).c_str(), texturePart, {(float)engine.grid.getTileSize().x,(float)engine.grid.getTileSize().y}, ImVec4(0.0f, 0.0f, 0.0f, 0.0f), ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
							ImGui::PopStyleColor(3);
							ImGui::SameLine();
						}
						ImGui::NewLine();
					}

				}

				ImGui::End();
			}
		}
	}

	ImGui::Begin("Tools");

	if(ImGui::ImageButton("move", *moveButton, { 32, 32 })) {
		tool = Move;
	}
	ImGui::SameLine();
	if (ImGui::ImageButton("paint", *paintButton, { 32, 32 })) {
		tool = Paint;
		brushWinIsOpen = true;
	}
	ImGui::SameLine();
	if(ImGui::ImageButton("erase", *eraseButton, { 32, 32 })) {
		tool = Erase;
	}
	ImGui::SameLine();
	if (ImGui::ImageButton("textureSelect", *textureButton, { 32, 32 })) {
		tool = Paint;
		brushWinIsOpen = true;
		selectTextureWinIsOpen = true;
	}

	ImGui::End();
}