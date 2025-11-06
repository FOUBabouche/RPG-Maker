#include <buttonList.h>

ButtonList::~ButtonList()
{
    for(auto button : m_buttons)
        delete button;
    m_buttons.clear();
}

Button *ButtonList::at(size_t index)
{
    return m_buttons[index];
}

size_t ButtonList::size(void) const
{
    return m_buttons.size();
}

void ButtonList::pushButton(Button* button)
{
    m_buttons.push_back(button);
}

Button *ButtonList::operator[](size_t index)
{
    return at(index);
}
