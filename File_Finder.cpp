#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

struct File {
    std::string name;
    std::string path;
    std::string extension;
    uintmax_t size;
};

int main() {

    std::string folder;

    std::cout << "Enter folder path: ";
    std::getline(std::cin, folder);

    std::vector<File> files;

    try {

        for (const auto& entry : fs::recursive_directory_iterator(folder)) {

            if (entry.is_regular_file()) {

                File file;

                file.name = entry.path().filename().string();
                file.path = entry.path().string();
                file.extension = entry.path().extension().string();
                file.size = entry.file_size();

                files.push_back(file);
            }
        }

    }
    catch (const fs::filesystem_error& e) {

        std::cerr << "Error: " << e.what() << '\n';
    }

    // Print everything we stored
    std::cout << "\nFiles found: " << files.size() << "\n\n";

    for (const File& file : files) {

        std::cout << file.name << " | "
                  << file.extension << " | "
                  << file.size << " bytes | "
                  << file.path << '\n';
    }

    return 0;
}