// Editor
#include <editor.h>
#include <toolSelector.h>
#include <brushPanel.h>
#include <tileSelector.h>

// Engine
#include <tilemap.h>
#include <camera.h>

// External Lib
#include <imgui.h>
#include <imconfig-SFML.h>

// STL
#include <iostream>

Editor::Editor()
{
    
}

Editor::~Editor()
{
    for(auto element : m_elements)
        delete element;
    m_elements.clear();

    delete placeHolder;
}

Editor::Editor(Engine *engine)
{
    m_engineRef = engine;
}

void Editor::addElement(Element *element)
{
    m_elements.push_back(element);
}

template <typename T>
T *Editor::getElement(std::string name)
{
    for(auto obj : m_elements) 
        if (obj->name == name) return static_cast<T*>(obj);
    return nullptr;
}

void Editor::start()
{
    registerTextures(); // Enregistre les texture qui vont faire partie de l'editeur
    registerElements(); // Enregistre les elements de l'editor
    registerToolButtons(); // Enregistre les different boutons du ToolSelector

    getElement<BrushPanel>("BrushPanel")->getBrush().texture = placeHolder;     

    // Action des boutons
    getElement<ToolSelector>("Tools")->getButton("MoveButton").setAction([&](){
        m_tool = Tools::Move;
    });

    getElement<ToolSelector>("Tools")->getButton("PaintButton").setAction([&](){
        m_tool = Tools::Paint;
    });
    getElement<ToolSelector>("Tools")->getButton("EraseButton").setAction([&](){
        m_tool = Tools::Erase;
    });
}

void Editor::update(float dt){
    // Capture les evenement entree et sor| std::views::transform(add_text)ti de Imgui
    ImGuiIO& io = ImGui::GetIO();

    // Recupere l'objet MainCamera present dans la scene
    Camera* cam =  m_engineRef->getObject<Camera>("MainCamera");
    // Recupere la position de la souris dans la scene
    sf::Vector2f mousePos = getElement<SceneRender>("Renderer")->getMousePositionInScene(*cam);
    getElement<TileSelector>("TileSelector")->setBrush(&getElement<BrushPanel>("BrushPanel")->getBrush());

    // Garde en memoire une variable pour stocké la derniere position de la souris
    static sf::Vector2f lastMousePos; 
    if(m_tool == Tools::Move){ // Si on a le MoveTools d'actif
        // Mouvement de la camera
        if(ImGui::IsMouseClicked(0)){ // Si un clique gauche est effectuer
            lastMousePos = mousePos; // Capture la derniere position de la souris dans la scene
        }
        if(ImGui::IsMouseDragging(0)){ // Si la souris effectuer un mouvement pendant un clique
            sf::Vector2f deltaMousePos = lastMousePos - mousePos; // On recupere l'ecart sur l'instant entre la position de la souris actuelle et l'ancienne
            cam->position += deltaMousePos * cam->getZoom(); // On additionne l'ecart à la position actuelle de la camera
        }

        // Zoom | Dezoom de la camera
        if(const float wheelDelta = io.MouseWheel; wheelDelta > 0){ // Si la roue de la souris bouge vers le haut
            if(cam->getZoom() - 0.1f > 0) // Si on est au dessus de 0
                cam->setZoom(cam->getZoom() - 0.1f); // Zoom
        }else if(wheelDelta < 0){ // Si la roue de la souris bouge vers le bas
            if(cam->getZoom() + 0.1f < 2) // Si on est en dessous de 2
                cam->setZoom(cam->getZoom() + 0.1f); // Dezoom 
        }
    }

    if(const auto tileMap = m_engineRef->getObject<TileMap>("TileMap")){ // Recupere la tilemap si elle existe dans la scene
        if(ImGui::IsMouseClicked(0, true)){ // Si le bouton gauche est appuyer 
            if(m_tool==Tools::Paint){ // Si on a le mode Paint d'actif
                if(sf::Vector2u gridPos = tileMap->getCoordToGridPos(mousePos); mousePos.x > 0 && mousePos.y > 0) // Prend la position de la souris sur la grid et si ses coordonees sont supperieur a {0, 0}
                    tileMap->setTile(gridPos, Tile(static_cast<sf::Vector2f>(sf::Vector2u(gridPos.x*tileMap->getTileSize().x, gridPos.y*tileMap->getTileSize().y)), // Position de la tile
                                                    static_cast<sf::Vector2f>(tileMap->getTileSize()), // Taille de la tile
                                                    getElement<BrushPanel>("BrushPanel")->getBrush().uv, 
                                                    getElement<BrushPanel>("BrushPanel")->getBrush().texture));
            } 
            if(m_tool==Tools::Erase){
                if(sf::Vector2u gridPos = tileMap->getCoordToGridPos(mousePos); mousePos.x > 0 && mousePos.y > 0) // Prend la position de la souris sur la grid et si ses coordonees sont supperieur a {0, 0}
                    tileMap->removeTile(gridPos);
            }
        }
    }

    // Boucle Update des Objets
    for(auto element : m_elements)
        element->update();
}

void Editor::registerTextures()
{
    const std::string editorButtonsTexturesPath = "ressources/editor/buttons/"; // Chemin vers les fichier des textures des bouttons
    const std::string editorTexturesPath = "ressources/editor/textures/"; // Chemin vers les fichier des textures des bouttons

    placeHolder = new sf::Texture(editorTexturesPath+"placeHolder.png");

    // Texture des boutons
    buttonsTextures["ImportButton"] = new sf::Texture(editorButtonsTexturesPath+"ImportButton.png");
    buttonsTextures["SaveButton"] = new sf::Texture(editorButtonsTexturesPath+"SaveButton.png");
    buttonsTextures["MoveButton"] = new sf::Texture(editorButtonsTexturesPath+"MoveButton.png");
    buttonsTextures["PaintButton"] = new sf::Texture(editorButtonsTexturesPath+"PaintButton.png");
    buttonsTextures["EraseButton"] = new sf::Texture(editorButtonsTexturesPath+"EraseButton.png");
}

void Editor::registerElements()
{
    // Ajout des element dans l'editor
    addElement(new SceneRender("Renderer", m_engineRef));
    addElement(new ToolSelector("Tools"));
    addElement(new BrushPanel("BrushPanel"));
    addElement(new TileSelector("TileSelector"));
}

void Editor::registerToolButtons()
{
    // Ajout des boutons
    const auto& tools = getElement<ToolSelector>("Tools");
    tools->pushButton(Button("ImportButton", buttonsTextures["ImportButton"]));
    tools->pushButton(Button("SaveButton", buttonsTextures["SaveButton"]));
    tools->pushButton(Button("MoveButton", buttonsTextures["MoveButton"]));
    tools->pushButton(Button("PaintButton", buttonsTextures["PaintButton"]));
    tools->pushButton(Button("EraseButton", buttonsTextures["EraseButton"]));
}
