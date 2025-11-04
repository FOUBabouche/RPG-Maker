#ifndef __ELEMENT_H__
#define __ELEMENT_H__

class Element{
    public:
        virtual ~Element() = default;

        virtual void update() = 0;
        virtual void draw() = 0;
};

#endif