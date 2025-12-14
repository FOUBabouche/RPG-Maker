#ifndef __DIALOG_H__
#define __DIALOG_H__

#include <string>
#include <vector>

struct Dialog{
    std::string ownerName = "";
    std::string content = "";
};

struct DialogList{
    std::string name;
    std::vector<Dialog*> dialogs;
};

#endif