#ifndef __DIALOG_H__
#define __DIALOG_H__

#include <string>

struct Dialog{
    Dialog* next = nullptr;
    std::string ownerName;
    std::string content;
};

#endif