#ifndef __ANIMATION_PANEL_H__
#define __ANIMATION_PANEL_H__

#include <element.h>
#include <SFML/Graphics/Rect.hpp>
#include <vector>

class AnimationPanel : public Element{
    public:
        AnimationPanel() = default;
        AnimationPanel(std::string _name, Base_Editor* editor);
        ~AnimationPanel() = default;

        void setCurrentUVDragged(const sf::IntRect& uv);

        void update(float dt) override;
    private:
        std::vector<sf::IntRect> m_uvs;
        sf::IntRect m_currentUv;
        bool isPlayingAnimation;
        float animationSpeed = 1;
        float totalTime = 0;
        int currentUVIndex = 0;
        bool isPlaying = false;
};

#endif