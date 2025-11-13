// Editor
#include <editor.h>
#include <toolSelector.h>

// Engine
#include <tile.h>
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

    // Textures of Buttons
    buttonsTextures["ImportButton"] = new sf::Texture(editorButtonsTexturesPath+"ImportButton.png");
    buttonsTextures["SaveButton"] = new sf::Texture(editorButtonsTexturesPath+"SaveButton.png");
    buttonsTextures["MoveButton"] = new sf::Texture(editorButtonsTexturesPath+"MoveButton.png");
    buttonsTextures["PaintButton"] = new sf::Texture(editorButtonsTexturesPath+"PaintButton.png");
    buttonsTextures["EraseButton"] = new sf::Texture(editorButtonsTexturesPath+"EraseButton.png");

    // Declare Elements in Editor
    addElement(new SceneRender("Renderer", m_engineRef));
    addElement(new ToolSelector("Tools"));

    // Using Element
    const auto& tools = getElement<ToolSelector>("Tools");
    tools->pushButton(Button("ImportButton", buttonsTextures["ImportButton"]));
    tools->pushButton(Button("SaveButton", buttonsTextures["SaveButton"]));
    tools->pushButton(Button("MoveButton", buttonsTextures["MoveButton"]));
    tools->pushButton(Button("PaintButton", buttonsTextures["PaintButton"]));
    tools->pushButton(Button("EraseButton", buttonsTextures["EraseButton"]));

    // Buttons Actions
    getElement<ToolSelector>("Tools")->getButton("MoveButton").setAction([&](){
        // Exemple de ce qu'il peut y avoir dans les action d'un bouton
        ///////////////////////////////////////////////////////////////
        std::cout << "Move" << std::endl;
        m_engineRef->addObject(new Tile({100, 100}, {32, 64}));
        ///////////////////////////////////////////////////////////////
    });
}

void Editor::update(float dt){
    Camera* camPosition =  m_engineRef->getObject<Camera>("MainCamera");
    

    if(tool == Tools::Move){
        if(ImGui::IsMouseClicked(0)){

        }
    }

    // Boucle Update des Objets
    for(auto element : m_elements)
        element->update();
}