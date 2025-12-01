#include <export/exportObject.h>

#include <fstream>
#include <filesystem>

void ObjectExporter::Export(std::string objectName){
    const char* path = "./Project/export/dlls/";
    const char* scriptPath = "./Project/export/script/";

    std::ofstream cppFile((scriptPath+objectName+"_export.cpp"));
    cppFile << "#include <Player.h>\n"
            << "#include \"object_export.h\"\n"

            << "OBJECT_API Object* CreateObject() { return new " << objectName << "(); }\n"
            << "OBJECT_API void DestroyObject(Object* obj) { delete obj; }\n";
    cppFile.close();
    std::filesystem::remove(".\\bin\\Debug\\cmake\\out\\CMakeCache.txt");
    std::system(("cmake -G \"Visual Studio 17 2022\" -S . -B cmake/out -DCMAKE_TOOLCHAIN_FILE=\"C:\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake\" -DLIB_NAME=\"" + objectName + "\"").c_str());
    std::system("cmake --build cmake/out");
}