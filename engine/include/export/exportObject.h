#ifndef __EXPORT_OBJECT_H__
#define __EXPORT_OBJECT_H__

#include <string>

class ObjectExporter{
    public:
        static void Export(std::string className);
    public:
        static bool isFinish = false;
};

#endif