#include <iostream>
using namespace std;
#include <string>
#include <list>
#include <filesystem>
namespace fs = std::filesystem;
#include <direct.h>
#include <vector>
#include <map>
//Key - Value Pairs Here:
//https://en.cppreference.com/w/cpp/container/map

//Declare Variables
int Randomize();
void RandomizeNonFolderDirectories();
void addAllFilesToMap(map<string, string>*, string);
void RandomizeMobs();
//void RandomizeGUI();

string path;
string texturePackName;

int main() {
    //Store path to project
    char buffer[256];
    path = getcwd(buffer, sizeof(buffer));

    if (Randomize() == 1) cout << "success!" << endl;
    return 0;
}

int Randomize() {
    //Store what user wants pack to be called
    cout << "What do you want to call this texture pack?\n\t";
    getline(cin, texturePackName);

    //Make sure directory doesn't already exists, and if it doesn't, create folder and copy files to it
    if (!fs::exists(path + "/randomizedTexturePacks/" + texturePackName)) { 
        //Create directory
        fs::create_directories(path + "/randomizedTexturePacks/" + texturePackName);
        
        //Try to copy default texture pack to newly created folder
        try { 
            fs::copy(path + "/defaultTexturePack/", path + "/randomizedTexturePacks/" + texturePackName, fs::copy_options::recursive); 
            cout << "Default Texture Pack Successfully Copied!" << endl;    
        }
        catch (exception e) { 
            cout << "There had been an error copying the default texture pack. Please try again." << endl; 
            return 1; 
        }

    }   
    else { 
        cout << "That texture pack already exists!" << endl;
        return 1; 
    }
    
    //Seed Random Numbers
    srand((unsigned) time(NULL));

    RandomizeNonFolderDirectories();
    RandomizeMobs();
    //RandomizeGUI();
    return 0;
}

void RandomizeNonFolderDirectories() {
    //Declare Variables
    string pathToTextures = path + "\\randomizedTexturePacks\\" + texturePackName + "\\assets\\minecraft\\textures\\";
    list<string> foldersToRandomize = {"block", "colormap", "environment", "font", "item", "map", "misc", "mob_effect", "models\\armor", "painting", 
        "particle", "trims\\color_palettes", "trims\\items", "trims\\models\\armor"};

    for (auto folder = foldersToRandomize.begin(); folder != foldersToRandomize.end(); folder++) {
        //Declare Variables
        string originalFileName, randomFileName = "";
        vector <string> fileNames;
        string directoryPath = pathToTextures + *folder + "\\";

        //Get files in directory and add them to vector
        for (auto const& file : fs::directory_iterator{ pathToTextures + *folder}) { fileNames.push_back(fs::path(file).filename().generic_string()); }

        for (auto const& file : fs::directory_iterator{ pathToTextures + *folder}) {
            originalFileName = fs::path(file).filename().generic_string();
            int randomFile = rand() % fileNames.size();
            randomFileName = fileNames[randomFile];

            string placeholder = "placeholder.png";
            //Make sure randomly selected file is not the same as the original file
            while (originalFileName == randomFileName) { 
                randomFile = rand() % fileNames.size();
                randomFileName = fileNames[randomFile];
            }

            //Rename original file to placeholder so there are no duplicated names
            //Set the randomly selected file's name to the original file
            //Set the original file to the randomly selected file's name
            rename((directoryPath + originalFileName).c_str(), (directoryPath + placeholder).c_str());
            rename((directoryPath + randomFileName).c_str(), (directoryPath + originalFileName).c_str());
            rename((directoryPath + "placeholder.png").c_str(), (directoryPath + randomFileName).c_str());
        }
    }
    cout << "Majority of Textures Successfully Randomized!" << endl;
    return;
}

void RandomizeMobs() {
    //Declare Variables
    string pathToTextures = path + "\\randomizedTexturePacks\\" + texturePackName + "\\assets\\minecraft\\textures\\entity\\";
    map<string, string> filePaths;
    
    addAllFilesToMap(&filePaths, pathToTextures);
    for (const auto & [key, value] : filePaths) cout << "key: " << key << ", value: " << value << endl;

    cout << "Mob Textures Successfully Randomized!" << endl;
    return;
}

void addAllFilesToMap(map<string, string>* map, string path) {
    for (auto const& recursiveFile : fs::recursive_directory_iterator(path)) { 
        int count = 0;
        try { if (is_directory(recursiveFile)) { for (auto const&  file : fs::directory_iterator{ recursiveFile }) { count++; } } } 
        catch (exception e) { cout << e.what() << endl; }
        if (count > 1) addAllFilesToMap(map, recursiveFile.path().string());

        (*map)[recursiveFile.path().filename().string()] = recursiveFile.path().string();
        
        if (!is_directory(recursiveFile)) { rename((recursiveFile.path().string()).c_str(), (path + recursiveFile.path().filename().string()).c_str()); }
    }
    return;
}