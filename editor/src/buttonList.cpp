#include <buttonList.h>

ButtonList::~ButtonList()
{
    // for(auto button : m_buttons)
    //     delete button;
    m_buttons.clear();
}

Button &ButtonList::at(size_t index)
{
    return m_buttons[index];
}

size_t ButtonList::size(void) const
{
    return m_buttons.size();
}

Button &ButtonList::getButton(std::string name) noexcept
{
    for (auto& button : m_buttons)
        if(button.name == name)
            return button;
}

void ButtonList::pushButton(const Button& button)
{
    m_buttons.push_back(button);
}

Button &ButtonList::operator[](size_t index)
{
    return at(index);
}
