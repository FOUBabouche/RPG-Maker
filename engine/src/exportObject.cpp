#include <export/exportObject.h>

#include <thread>
#include <fstream>
#include <filesystem>

void ObjectExporter::Export(std::string objectName){
    const char* path = "./Project/export/dlls/";
    const char* scriptPath = "./Project/export/script/";

    isFinish = false;

    std::ofstream cppFile((scriptPath+objectName+"_export.cpp"));
    cppFile << "#include <Player.h>\n"
            << "#include \"object_export.h\"\n"

            << "OBJECT_API Object* CreateObject() { return new " << objectName << "(); }\n"
            << "OBJECT_API void DestroyObject(Object* obj) { delete obj; }\n"
            << "OBJECT_API char* GetNameObject(Object* obj) { return (char*)obj->name.c_str(); }\n"
            << "OBJECT_API void StartObject(Object* obj) { obj->start(); }\n"
            << "OBJECT_API void UpdateObject(Object* obj, float dt) { obj->update(dt); }\n"
            << "OBJECT_API void DrawObject(Object* obj, sf::RenderTarget& target) { obj->draw(target); }\n";
    cppFile.close();
    std::thread compile([&]{
        std::filesystem::remove(".\\bin\\Debug\\cmake\\out\\CMakeCache.txt");
        std::system(("cmake -G \"Visual Studio 17 2022\" -S . -B cmake/out -DCMAKE_TOOLCHAIN_FILE=\"C:\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake\" -DLIB_NAME=\"" + objectName + "\"").c_str());
        std::system("cmake --build cmake/out");
        isFinish = true;
    });
    compile.detach();
}