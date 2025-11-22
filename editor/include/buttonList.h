#ifndef __BUTTON_LIST_H__
#define __BUTTON_LIST_H__

#include <elements/button.h>

#include <vector>

class ButtonList{
    public:
        ButtonList() = default;
        ~ButtonList();

        Button& at(size_t index);
        size_t size(void) const;

        Button& getButton(std::string name) noexcept;

        void pushButton(const Button& button);        
    public:
        Button& operator [](size_t index);
    protected:
        std::vector<Button> m_buttons = {};
};

#endif