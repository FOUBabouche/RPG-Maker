#ifndef __SHADER_EDITOR_H__
#define __SHADER_EDITOR_H__

#include <element.h>

class ShaderEditor : public Element{
    public:
        ShaderEditor() = default;
        ~ShaderEditor() = default;

        void update(float dt) override;
    private:
        
};

#endif