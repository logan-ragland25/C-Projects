#include <iostream>
using namespace std;
#include <string>
#include <list>
#include <filesystem>
namespace fs = std::filesystem;
#include <direct.h>
#include <map>
//Key - Value Pairs Here:
//https://en.cppreference.com/w/cpp/container/map

//Declare Variables
void Randomize();
string path;
string texturePackName;

int main() {
    //Store path to project
    char buffer[256];
    path = getcwd(buffer, sizeof(buffer));

    Randomize();
    cout << "success!" << endl;
    return 0;
}

void Randomize() {
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
            return; 
        }

    }   
    else { return; }

    RandomizeNonFolderDirectories();
    return;
}

void RandomizeNonFolderDirectories() {
    list<string> foldersToRandomize = {"block", "colormap", "environment", "font", "item", "map", "misc", "mob_effect", "models\\armor", "painting", 
        "particle", "trims\\color_palettes", "trims\\items", "trims\\models\\armor"};

    foreach (foldersToRandomize as folder) {
        string transfer = "";

        for (auto const& dir_entry : std::filesystem::directory_iterator{path + "\\randomizedTexturePacks\\" + texturePackName + "\\assets\\minecraft\\" + foldersToRandomize.at(folder)}) {

        }
    }
}