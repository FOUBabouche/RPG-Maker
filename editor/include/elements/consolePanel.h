#ifndef __CONSOLE_PANEL_H__
#define __CONSOLE_PANEL_H__

#include <element.h>

#include <vector>
#include <string>
#include <utility>
#include <concepts>

class ConsolePanel : public Element{
    public:
        ConsolePanel() =default;
        ConsolePanel(std::string _name, Base_Editor* editor);
        ~ConsolePanel() = default;

        template<typename... Args>
        static void Log(Args... args){
            if(!(lineExist(args),...)){
                (m_lines.push_back({1,args}),...);
            }else{
                m_lines[(findLine(args), ...)].first++;
            }
        }

        void update(float dt) override;
    private:
        static bool lineExist(std::string);
        static size_t findLine(std::string);

    private:
        static std::vector<std::pair<unsigned int, std::string>> m_lines;
};

using Debug = ConsolePanel;


#endif