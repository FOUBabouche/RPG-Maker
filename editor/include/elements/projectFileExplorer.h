#ifndef __PROJECT_FILE_EXPLORER_H__
#define __PROJECT_FILE_EXPLORER_H__

#include <element.h>

#include <filesystem>

class ProjectFileExplorer : public Element{
    public:
        ProjectFileExplorer() = default;
        ProjectFileExplorer(std::string _name, Base_Editor* editor);
        ~ProjectFileExplorer();

        void update(float dt) override;
    private:
        std::filesystem::path currentFolderPosition;
        sf::Texture *folderIcon;
        sf::Texture *fileIcon;
};

#endif