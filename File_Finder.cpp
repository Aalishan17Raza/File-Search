#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    std::string folder;

    std::cout << "Enter folder path: ";
    std::getline(std::cin, folder);

    try {
        for (const auto& entry : fs::recursive_directory_iterator(folder)) {
            if (entry.is_regular_file()) {
                std::cout << entry.path() << '\n';
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}