// Editor
#include <editor.h>
#include <toolSelector.h>

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
    const std::string editorButtonsTexturesPath = "ressources/editor/buttons/";

    // Texture des boutons
    buttonsTextures["ImportButton"] = new sf::Texture(editorButtonsTexturesPath+"ImportButton.png");
    buttonsTextures["SaveButton"] = new sf::Texture(editorButtonsTexturesPath+"SaveButton.png");
    buttonsTextures["MoveButton"] = new sf::Texture(editorButtonsTexturesPath+"MoveButton.png");
    buttonsTextures["PaintButton"] = new sf::Texture(editorButtonsTexturesPath+"PaintButton.png");
    buttonsTextures["EraseButton"] = new sf::Texture(editorButtonsTexturesPath+"EraseButton.png");

    // Ajout des element dans l'editor
    addElement(new SceneRender("Renderer", m_engineRef));
    addElement(new ToolSelector("Tools"));

    // Ajout des boutons
    const auto& tools = getElement<ToolSelector>("Tools");
    tools->pushButton(Button("ImportButton", buttonsTextures["ImportButton"]));
    tools->pushButton(Button("SaveButton", buttonsTextures["SaveButton"]));
    tools->pushButton(Button("MoveButton", buttonsTextures["MoveButton"]));
    tools->pushButton(Button("PaintButton", buttonsTextures["PaintButton"]));
    tools->pushButton(Button("EraseButton", buttonsTextures["EraseButton"]));

    // Action des boutons
    getElement<ToolSelector>("Tools")->getButton("MoveButton").setAction([&](){
        m_tool = Tools::Move;
    });

    getElement<ToolSelector>("Tools")->getButton("PaintButton").setAction([&](){
        m_tool = Tools::Paint;
    });
}

void Editor::update(float dt){
    // Capture les evenement entree et sorti de Imgui
    ImGuiIO& io = ImGui::GetIO();
    // Recupere l'objet MainCamera present dans la scene
    Camera* cam =  m_engineRef->getObject<Camera>("MainCamera");
    
    // Recupere la position de la souris dans la scene
    sf::Vector2f mousePos = getElement<SceneRender>("Renderer")->getMousePositionInScene(*cam);

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
            cam->setZoom(cam->getZoom() - 0.1f); // Zoom
        }else if(wheelDelta < 0){ // Si la roue de la souris bouge vers le bas
            cam->setZoom(cam->getZoom() + 0.1f); // Dezoom 
        }
    }

    if(m_tool==Tools::Paint){ // Si on a le mode Paint d'actif
        if(const auto tileMap = m_engineRef->getObject<TileMap>("TileMap")){
            if(ImGui::IsMouseClicked(0, true)){
                if(sf::Vector2u gridPos = tileMap->getCoordToGridPos(mousePos); mousePos.x > 0 && mousePos.y > 0)
                    tileMap->setTile(gridPos, reinterpret_cast<Tile&>(Tile(static_cast<sf::Vector2f>(sf::Vector2u(gridPos.x*tileMap->getTileSize().x, gridPos.y*tileMap->getTileSize().y)),
                                                                       static_cast<sf::Vector2f>(tileMap->getTileSize()))));
            }
        }
    }

    // Boucle Update des Objets
    for(auto element : m_elements)
        element->update();
}