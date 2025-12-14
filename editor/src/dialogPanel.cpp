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

    ImGui::SeparatorText("Dialogs");

    for(auto dialogList : saveDialog){
        if(ImGui::Button(currentDialogList->name.c_str())){
            currentDialogList = dialogList;
        }
        ImGui::SameLine();
    }
    ImGui::NewLine();

    ImGui::SeparatorText("Creator");

    if(currentDialogList){
        for(auto dialog : currentDialogList->dialogs){
            if(ImGui::Button(dialog->ownerName.c_str())){
                currentDialog = dialog;
            }
            ImGui::SameLine();
        }
        ImGui::NewLine();

        ImGui::SeparatorText("Properties");

        if(currentDialog){
            if(ImGui::InputText("Owner Name", ownerName, 256)){
                currentDialog->ownerName = ownerName;
            }

            if(ImGui::InputText("Content", content, 1024)){
                currentDialog->content = content;
            }
        }

        if(ImGui::Button("Create new Dialog")){
            currentDialog = new Dialog;
            strcpy(ownerName, "");
            strcpy(content, "");
        }
        ImGui::SameLine();
        if(ImGui::Button("Save")){
            currentDialogList->dialogs.push_back(currentDialog);
        }
    }

    if(ImGui::InputText("Dialog List Name", dialogListName, 256)){
        currentDialogList->name = dialogListName;
    }

    if(ImGui::Button("Create new DialogList")){
        currentDialogList = new DialogList;
        strcpy(ownerName, "");
        strcpy(content, "");
    }
    ImGui::SameLine();
    if(ImGui::Button("Save DialogList")){
        saveDialog.push_back(currentDialogList);
    }

    ImGui::End();
}