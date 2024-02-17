#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

#define Error(x) std::cerr << "\033[31m> [ERROR] " << x << "\033[0m\n"; system("pause"); return 0
#define str(x) std::to_string(x)

int main(int argc, char* argv[]) {
    if (argc < 2) {
        Error("No input folder found. Drag the folder you want to organise onto this EXE.");
    } else if (argc > 2) {
        Error("To many arguments. Only drag a single folder onto this EXE that contains subfolders.");
    }

    const std::string directoryPath = argv[1];
    size_t total_i = 1;
    size_t chapter = 1;
    size_t chapter_i;

    fs::path destinationPath = "Organised Volume";
    fs::create_directory(destinationPath);

    for (const auto& subDirectoryPath : fs::directory_iterator(directoryPath)) {
        chapter_i = 1;
        for (const auto& entry : fs::directory_iterator(subDirectoryPath)) {
            fs::path newPath = destinationPath / ("Ch" + str(chapter) + "-" + str(chapter_i++) + " (" + str(total_i++) + ")" + entry.path().extension().string());
            fs::copy_file(entry, newPath);
        }
        chapter++;
    }
}