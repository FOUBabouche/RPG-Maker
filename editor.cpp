#include "editor.h"
#include "eMath.h"
#include "tool.h"

#include <SFML/Graphics/Sprite.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

Editor::Editor()
{
	col = new float[3] {1, 1, 1};
}

Editor::~Editor() {
	delete[]col;
	for (size_t i = 0; i < textures.size(); i++)
	{
		delete textures[i];
	}
	textures.clear();
}

void Editor::Start(Engine& engine) {
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	importButton = new sf::Texture("ImportButton.png");
	saveButton = new sf::Texture("SaveButton.png");
	moveButton = new sf::Texture("MoveButton.png");
	paintButton = new sf::Texture("PaintButton.png");
	eraseButton = new sf::Texture("EraseButton.png");
	textureButton = new sf::Texture("TextureButton.png");
	addLayerButton = new sf::Texture("AddLayerButton.png");
	selectLayerButton = new sf::Texture("LayerButton.png");

	placeHolder = new sf::Texture("Placeholder.png");
	currentTexture = new sf::Texture();

	brush.SetTextureName("Placeholder.png");
	brush.SetTexture(placeHolder);
	brush.SetUV({ {0, 0}, {(int)brush.GetTexture()->getSize().x, (int)brush.GetTexture()->getSize().y} });

	engine.AddLayer({ 16, 16 });
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

	sf::Vector2u mousePosOnGrid = engine.grids[currentGridSelected].GetCoordToGridPos(mousePos);

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
			if (tool == Paint)engine.grids[currentGridSelected].SetTile(mousePosOnGrid, { brush.GetSize(), brush.GetSize()}, brush.GetColor(), brush.GetTexture(), brush.GetUV(), brush.GetTextureName());
			if (tool == Erase)engine.grids[currentGridSelected].RemoveTile(mousePosOnGrid);
		}
	}

	if (tool == Paint) {
		if(brushWinIsOpen)
		{
			if (ImGui::Begin("Brush", &brushWinIsOpen)) {
				ImGui::SeparatorText("Grid Properties");
				ImGui::Text("X: ");
				ImGui::SameLine();
				int tileSizeX = (int)engine.grids[currentGridSelected].getTileSize().x;
				if (ImGui::InputInt("##X: ", &tileSizeX)) {
					engine.grids[currentGridSelected].setTileSize({ (unsigned int)tileSizeX, engine.grids[currentGridSelected].getTileSize().y });
				}
				ImGui::Text("Y: ");
				ImGui::SameLine();
				int tileSizeY = (int)engine.grids[currentGridSelected].getTileSize().y;
				if (ImGui::InputInt("##Y: ", &tileSizeY)) {
					engine.grids[currentGridSelected].setTileSize({ engine.grids[currentGridSelected].getTileSize().x, (unsigned int)tileSizeY });
				}
				ImGui::SeparatorText("Brush Properties");
				if (ImGui::ColorPicker3("Brush Color", col, 0)) {
					brush.SetColor({ static_cast<uint8_t>(col[0] * 255), static_cast<uint8_t>(col[1] * 255), static_cast<uint8_t>(col[2] * 255), 255 });
				}
				ImGui::SeparatorText("Current Texture");
				sf::Sprite preview(*brush.GetTexture(), brush.GetUV());
				ImGui::Image(preview, {128, 128});

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
					textures.push_back(new sf::Texture(currentTexturePath));
					currentTexture = textures[textures.size() - 1];
					brush.SetTextureName(currentTexturePath);
					brush.SetTexture(textures[textures.size() - 1]);
				}
				if (texturesPaths.size() > 0) {
					if (ImGui::BeginCombo("Texture List", currentTexturePath.c_str())) {
						for (size_t i = 0; i < texturesPaths.size(); i++)
						{
							bool is_selected = (currentTexturePath == texturesPaths[i]);
							if (ImGui::Selectable(texturesPaths[i].c_str(), is_selected)) {
								currentTexturePath = texturesPaths[i];
								currentTexture = textures[i];
								brush.SetTextureName(currentTexturePath);
								brush.SetTexture(textures[i]);
							}
						}
						ImGui::EndCombo();
					}

					ImGui::SeparatorText("Current Texture");

					// IMAGE DE LA TEXTURE MA GUEULE
					for (int x = 0; x < currentTexture->getSize().x; x += engine.grids[currentGridSelected].getTileSize().x)
					{
						for (int y = 0; y < currentTexture->getSize().y; y += engine.grids[currentGridSelected].getTileSize().y)
						{
							sf::Sprite texturePart(*currentTexture, { {y, x}, {(int)engine.grids[currentGridSelected].getTileSize().x,(int)engine.grids[currentGridSelected].getTileSize().y} });
							ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
							ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
							ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));
							if (ImGui::ImageButton(std::string(std::to_string(x) + " " + std::to_string(y)).c_str(), texturePart, { (float)engine.grids[currentGridSelected].getTileSize().x,(float)engine.grids[currentGridSelected].getTileSize().y })) {
								brush.SetUV({ {y, x}, {(int)engine.grids[currentGridSelected].getTileSize().x, (int)engine.grids[currentGridSelected].getTileSize().y} });
							}
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

	if (selectLayerWinIsOpen) {
		ImGui::OpenPopup("Select a Layer");

		ImGui::SetNextWindowSize(ImVec2(-1, -1), ImGuiCond_Always);

		if (ImGui::BeginPopupModal("Select a Layer", &selectLayerWinIsOpen))
		{
			ImGui::Text("Layers :");
			for (size_t i = 0; i < engine.grids.size(); i++)
			{
				if (ImGui::Button(std::to_string(i + 1).c_str(), { 20, 20 })) {
					currentGridSelected = i;
					selectLayerWinIsOpen = false;
				}
				ImGui::SameLine();
			}

			ImGui::EndPopup();
		}
	}

	ImGui::Begin("Tools");

	if (ImGui::ImageButton("import", *importButton, { 32, 32 })) {
		LoadScene(engine, "test.txt");
	}
	ImGui::SameLine();
	if (ImGui::ImageButton("save", *saveButton, { 32, 32 })) {
		SaveScene(engine, "test.txt");
	}
	ImGui::SameLine();
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
	ImGui::SameLine();
	if (ImGui::ImageButton("addLayer", *addLayerButton, { 32, 32 })) {
		engine.AddLayer({ 16, 16 });
	}
	ImGui::SameLine();
	if (ImGui::ImageButton("selectLayer", *selectLayerButton, { 32, 32 })) {
		selectLayerWinIsOpen = true;
	}

	ImGui::End();
}

void Editor::SaveScene(Engine& engine, std::string fileName)
{
	std::ofstream savingFile(fileName.c_str());

	if (savingFile.is_open()) {
		for (auto grid : engine.grids)
		{
			savingFile << "L" << std::endl;
			for (auto&& x : grid.getTiles()) {
				for (auto&& y : x) {
					if (y == (Tile&)Tile()) continue;
					savingFile << y;
				}
			}
		}
		savingFile.close();
		return;
	}
	std::cout << "Cant write in file..." << std::endl;
}

void Editor::LoadScene(Engine& engine, std::string fileName)
{
	// Parsing fichier
	std::vector<std::vector<std::string>> tilesInfos;
	std::ifstream savingFile(fileName);
	std::string line;
	while (std::getline(savingFile, line, '\n')) {
		std::vector<std::string> variables;
		std::stringstream content(line);
		std::string info;
		while (std::getline(content, info, ';')) {
			variables.push_back(info);
		}
		std::vector<std::string> loc;
		for (auto var : variables)
		{
			std::stringstream varContent(var);
			std::string buffer;
			while (std::getline(varContent, buffer, ',')) {
				loc.push_back(buffer);
			}
		}
		tilesInfos.push_back(loc);
	}

	// Load Scene
 	engine = Engine();
	for (int i = 0; i < tilesInfos.size(); i++)
	{
		if (tilesInfos[i][0] == "L") {
			engine.AddLayer({ 16, 16 });
			currentGridSelected = 0;
			continue;
		}
		engine.grids[currentGridSelected].SetTile(
			{ (unsigned int)std::stoi(tilesInfos[i][0]),  (unsigned int)std::stoi(tilesInfos[i][1])},												// Position
			{ (unsigned int)std::stoi(tilesInfos[i][2]),  (unsigned int)std::stoi(tilesInfos[i][3]) },											// Size
			{ static_cast<uint8_t>(std::stoi(tilesInfos[i][4])), static_cast<uint8_t>(std::stoi(tilesInfos[i][5])), static_cast<uint8_t>(std::stoi(tilesInfos[i][6])), static_cast<uint8_t>(std::stoi(tilesInfos[i][7])) }, // Color
			placeHolder,
			{ {std::stoi(tilesInfos[i][8]), std::stoi(tilesInfos[i][9])}, {std::stoi(tilesInfos[i][10]), std::stoi(tilesInfos[i][11])} },// UV
			tilesInfos[i][12]
		);
	}

}
