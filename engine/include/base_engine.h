#ifndef __BASE_ENGINE_H__
#define __BASE_ENGINE_H__

class BaseEngine{
    public:
        virtual ~BaseEngine() = default;

        virtual void Start()=0;
        virtual void Update()=0;
        virtual void Render()=0;
    
};

#endif