#include <elements/dialogPanel.h>

#include <imgui.h>

DialogPanel::DialogPanel(std::string _name, Base_Editor* editor){
    name = _name;
    m_editor = editor;
}

DialogPanel::~DialogPanel(){
    delete ownerName;
    delete content;

    for(auto dialog : saveDialog){
        delete dialog;
    }
    saveDialog.clear();
}

void DialogPanel::update(float dt){
    ImGui::Begin("Dialog");

    for(auto dialog : saveDialog){
        if(!dialog->ownerName.empty()){
            if(ImGui::Button(dialog->ownerName.c_str())){
                currentDialog = dialog;
            }
            ImGui::SameLine();
        }
    }

    if(saveDialog.size() > 0){
        if(ImGui::InputText("Owner Name", ownerName, 256, ImGuiInputTextFlags_EnterReturnsTrue)){
            currentDialog->ownerName = ownerName;
        }

        if(ImGui::InputText("Content", content, 1024)){
            currentDialog->content = content;
        }

        if(!currentDialog->next){
            if(ImGui::Button("Add next Dialog")){
                currentDialog->next = new Dialog;
                currentDialog= currentDialog->next;
                strcpy(ownerName, "");
                strcpy(content, "");
            }
        }else{
            if(ImGui::Button("Go to Next Dialog")){
                currentDialog = currentDialog->next;
                strcpy(ownerName, currentDialog->ownerName.c_str());
                strcpy(content, currentDialog->content.c_str());
            }
        }


        if(ImGui::Button("Save Dialog")){
            currentDialog->ownerName = ownerName;
            currentDialog->content = content;
        }
        ImGui::SameLine();
    }

    if(ImGui::Button("Create new Dialog")){
        saveDialog.push_back(new Dialog);
        currentDialog = saveDialog[saveDialog.size()-1];
        strcpy(ownerName, "");
        strcpy(content, "");
    }

    ImGui::End();
}