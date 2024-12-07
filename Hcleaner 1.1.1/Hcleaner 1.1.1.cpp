#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

const std::string CONFIG_FILE = "config.txt";

std::string loadPathFromConfig() {
    std::ifstream configFile(CONFIG_FILE);
    if (configFile.is_open()) {
        std::string path;
        std::getline(configFile, path);
        configFile.close();
        return path;
    }
    return "";
}

void savePathToConfig(const std::string& path) {
    std::ofstream configFile(CONFIG_FILE);
    if (configFile.is_open()) {
        configFile << path;
        configFile.close();
    }
}

void deleteSpecificFolders(const std::string& rootPath, const std::vector<std::string>& foldersToDelete) {
    if (!fs::exists(rootPath)) {
        std::cout << "FAD directory not found.\n";
        return;
    }

    if (!fs::is_directory(rootPath)) {
        std::cout << "Provided FAD path is not a directory.\n";
        return;
    }

    for (const auto& folder : foldersToDelete) {
        std::string folderPath = rootPath + "/" + folder;
        if (fs::exists(folderPath) && fs::is_directory(folderPath)) {
            for (const auto& entry : fs::directory_iterator(folderPath)) {
                if (fs::is_regular_file(entry)) {
                    fs::remove(entry.path());
                    std::cout << "Deleted file: " << entry.path() << "\n";
                }
            }
            std::cout << "Cleaned FAD02: " << "\n";
        }
        else {
            std::cout << "Folder not found: " << folderPath << "\n";
        }
    }
}

int main() {
    std::string answer;
    std::string license = "license1";
    std::cout << "                                                       HCLEANER  1.1.1\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "                   Enter the license key: ";
    std::cin >> answer;
    std::cin.ignore(); // Ignore remaining newline character from std::cin

    if (answer == license) {
        std::string rootPath = loadPathFromConfig();

        if (rootPath.empty()) {
            std::cout << "Enter the root FAD directory path: ";
            std::getline(std::cin, rootPath); // Allows spaces in path
            savePathToConfig(rootPath);
        }
        else {
            std::cout << "Using saved path: " << rootPath << "\n";
        }

        std::vector<std::string> foldersToDelete = { "plugins", "mods" };
        deleteSpecificFolders(rootPath, foldersToDelete);
    }
    else {
        std::cout << "__________\n";
        std::cout << "This license doesn't exist\n";
    }

    return 0;
}
