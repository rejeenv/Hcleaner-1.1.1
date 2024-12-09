#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>

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
    return ""; // Zwrot pustego ciągu, jeśli plik nie istnieje
}
void clearPath() {
    std::ofstream configFile(CONFIG_FILE, std::ios::trunc);
    if (configFile.is_open()) {
        configFile.close();
    }
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
            std::cout << "Cleaned folder: " << folder << "\n";
        }
        else {
            std::cout << "Folder not found: " << folderPath << "\n";
        }
    }
}

int main() {
    std::string anwser;
    const std::string license = ("license1"); // Stała przechowująca licencję
    std::cout << "                                                       HCLEANER  1.1.1\n\n\n";
    std::cout << "                   Enter the license key: ";
    std::cin >> anwser;

    if (anwser == license) {
        int option;
        std::system("cls");
        std::cout << "\nChoose an option\n";
        std::cout << "1 - Clear\n";
        std::cout << "2 - Clearing Settings\n";
        std::cout << ":/ ";
        std::cin >> option;

        // Wyczyszczenie bufora std::cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (option == 1) {
            std::string rootPath = loadPathFromConfig();

            // Pytanie użytkownika o poprawną ścieżkę, jeśli jest pusta lub nie istnieje
            while (rootPath.empty() || !fs::exists(rootPath)) {
                if (rootPath.empty()) {
                    std::cout << "Path not found in configuration. Please enter a valid path:\n/: ";
                }
                else {
                    std::cout << "Provided path does not exist. Please enter a valid path:\n/: ";
                }

                std::getline(std::cin, rootPath);
                rootPath.erase(rootPath.find_last_not_of(" \t\n\r") + 1); // Usunięcie białych znaków na końcu
            }

            savePathToConfig(rootPath); // Zapis poprawnej ścieżki do pliku
            std::cout << "Using path: " << rootPath << "\n";

            // Poprawiona lista folderów do usunięcia (bez zbędnych spacji)
            std::vector<std::string> foldersToDelete = { "plugins", "mods" };
            deleteSpecificFolders(rootPath, foldersToDelete);
        }
        if (option == 2)
        {
            int optionSet;

            std::system("cls");
            std::cout << "1 - CLEAR CFG\n\n";
            std::cout << ":/ ";
            std::cin >> optionSet;

            if (optionSet == 1)
            {
                clearPath();
                main();
            }
            else
            {
                std::cout << "Invalid option";
            }
        }
    }
    else {
        std::cout << "Incorrect license key\n";
    }

    return 0;
}
