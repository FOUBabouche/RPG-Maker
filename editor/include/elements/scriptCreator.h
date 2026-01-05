#ifndef __SCRIPT_CREATOR__
#define __SCRIPT_CREATOR__

#include <element.h>

class ScriptCreator : public Element{
    public:
        ScriptCreator(std::string _name, Base_Editor* editor);
    
        void update(float dt) override;
    private:
        char scriptName[256] = "";
};

#endif