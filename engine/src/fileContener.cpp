#include <fileContener.hpp>


#include <iostream>

FileContener::FileContener(const std::filesystem::path& path){
    m_directoryPath = path;
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        m_contentPaths.push_back(std::filesystem::absolute(std::filesystem::relative(entry.path())));
    }
}

void FileContener::init(const std::filesystem::path& path){
    m_directoryPath = path;
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        m_contentPaths.push_back(std::filesystem::absolute(std::filesystem::relative(entry.path())));
    }
}

void FileContener::addFile(const std::filesystem::path& path){
    std::filesystem::copy(path, m_directoryPath.string() + "/" + path.filename().string());
    m_contentPaths.push_back(std::filesystem::relative(m_directoryPath.string() + "/" + path.filename().string()));
}

std::vector<std::filesystem::path> FileContener::getContentPaths(void) const{
    return m_contentPaths;
}

void FileContener::show(){
    for(auto path : m_contentPaths){
        std::cout << path << std::endl;
        std::cout << path.filename() << std::endl;
    }
}

FileContener& FileContener::operator>>(FileContener& b){
    for (auto path : m_contentPaths)
        addFile(path);
    return b;
}