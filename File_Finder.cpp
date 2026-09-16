#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <cctype>

namespace fs = std::filesystem;

struct File {
    std::string name;
    std::string path;
    std::string extension;
    uintmax_t size;
};

std::string toLower(std::string text) {
    for (char& c : text) {
        c = std::tolower(c);
    }

    return text;
}

int main() {

    std::string folder;

    std::cout << "Enter folder path: ";
    std::getline(std::cin, folder);

    std::vector<File> files;

    try {

        // Scan the folder
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
        return 1;
    }

    std::cout << "\nFiles found: " << files.size() << '\n';

    // Search
    std::string query;

    std::cout << "\nSearch: ";
    std::getline(std::cin, query);

    std::cout << "\nResults:\n";

    for (const File& file : files) {

        if (toLower(file.name).find(toLower(query)) != std::string::npos) {

            std::cout << file.name << '\n';
            std::cout << "  " << file.path << '\n';
            std::cout << "  " << file.size << " bytes\n\n";
        }
    }

    return 0;
}