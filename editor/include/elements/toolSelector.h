#ifndef __TOOL_SELECTOR_H__
#define __TOOL_SELECTOR_H__

#include <buttonList.h>
#include <element.h>

class ToolSelector : public ButtonList, public Element{
    public:
        ToolSelector() = default;
        ToolSelector(std::string _name, Base_Editor* editor);
        ~ToolSelector() = default;

        void update(float dt) override;
};

#endif
