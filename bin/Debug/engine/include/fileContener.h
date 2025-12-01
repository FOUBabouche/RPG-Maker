#ifndef __FILE_CONTENER__
#define __FILE_CONTENER__

#include <filesystem>
#include <vector>

class FileContener{
    public:
        FileContener() = default;
        FileContener(const std::filesystem::path& path);

        void init(const std::filesystem::path& path);
        void addFile(const std::filesystem::path& path);

        std::vector<std::filesystem::path> getContentPaths(void) const;

        void show();
    public:
        FileContener& operator>>(FileContener& b);
    private:
        std::filesystem::path m_directoryPath;
        std::vector<std::filesystem::path> m_contentPaths;
};

#endif