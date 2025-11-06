#include <editor.h>
#include <toolSelector.h>

Editor::Editor()
{
    
}

Editor::~Editor()
{
    for(auto element : m_elements)
        delete element;
    m_elements.clear();
}

Editor::Editor(BaseEngine *engine)
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
        return (obj->name == name ? static_cast<T*>(obj) : nullptr);
    return nullptr;
}

void Editor::start()
{
    SceneRender* renderer = new SceneRender(m_engineRef);
    renderer->name = "Renderer";
    addElement(renderer);
    ToolSelector* tools = new ToolSelector();
    tools->name = "Tools";
    addElement(tools);
    getElement<ToolSelector>("Tools")->pushButton(new Button());
}

void Editor::update(float dt){
    for(auto element : m_elements)
        element->update();
}
void Editor::draw(){
    
}