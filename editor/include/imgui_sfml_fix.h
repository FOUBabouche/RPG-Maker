#ifndef __IMGUI_SFML_FIX_H__
#define __IMGUI_SFML_FIX_H__

#include <imgui-SFML_export.h>
#include <imgui-SFML.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <imgui.h>

namespace ImGui
{
    [[nodiscard]] ImTextureID convertGLTextureHandleToImTextureID(GLuint glTextureHandle)
    {
        ImTextureID textureID{};
        std::memcpy(&textureID, &glTextureHandle, sizeof(GLuint));
        return textureID;
    }

    [[nodiscard]] ImVec2 toImVec2(const sf::Vector2f& v)
    {
        return {v.x, v.y};
    }

    [[nodiscard]] ImColor toImColor(sf::Color c)
    {
        return {int{c.r}, int{c.g}, int{c.b}, int{c.a}};
    }

    IMGUI_SFML_API void Image(const sf::Texture&  texture,
                            const sf::Vector2f& size,
                            const ImVec2& uv0,
                            const ImVec2& uv1,
                            const sf::Color&    tintColor   = sf::Color::White,
                            const sf::Color&    borderColor = sf::Color::Transparent){
        ImTextureID textureID = convertGLTextureHandleToImTextureID(texture.getNativeHandle());

        ImGui::Image(textureID, toImVec2(size), uv0, uv1, toImColor(tintColor), toImColor(borderColor));

    }
}

#endif