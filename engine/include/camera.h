#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <object.h>

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Camera : public Object{
    public:
        Camera();
        Camera(std::string name);
        Camera(std::string name, sf::Vector2f position);
        ~Camera() = default;

        sf::View& getHandle(void);

        void setZoom(float zoom);
        float getZoom(void) const;

        void start() override {};
        void update(float dt)override;
        void draw(sf::RenderTarget& target)override;
    private:
        sf::View m_handle;
        float m_zoom;                                              
};

#endif