#ifndef __DIALOG_PANEL_H__
#define __DIALOG_PANEL_H__

#include <element.h>

#include <dialog.h>

#include <vector>

class DialogPanel : public Element{
    public:
        DialogPanel() = default;
        DialogPanel(std::string _name, Base_Editor* editor);
        ~DialogPanel();

        void update(float dt) override;
    private:
        char  ownerName[256] = "";
        char content[1024] = "";
        Dialog* currentDialog;
        std::vector<Dialog*> saveDialog;
};

#endif