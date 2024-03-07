#include <iostream>
using namespace std;
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
#include <direct.h>

void Randomize();
string path;

int main() {
    //Store path to project
    char buffer[256];
    path = getcwd(buffer, sizeof(buffer));

    Randomize();
    cout << "success!" << endl;
    return 0;
}

void Randomize() {
    //Declare Variables
    string texturePackName;

    //Store what user wants pack to be called
    cout << "What do you want to call this texture pack?\n\t";
    getline(cin, texturePackName);

    //Make sure directory doesn't already exists, and if it doesn't, create folder and copy files to it
    if (!fs::exists(path + "/randomizedTexturePacks/" + texturePackName)) { 
        //Create directory
        fs::create_directories(path + "/randomizedTexturePacks/" + texturePackName);
        
        cout << "default: " << fs::exists(path + "/defaultTexturePack") << "\nrandomized: " << fs::exists(path + "/randomizedTexturePacks/" + texturePackName) << endl;
        
        //Try to copy default texture pack to newly created folder
        try { fs::copy(path + "/defaultTexturePack", path + "/randomizedTexturePacks/" + texturePackName, fs::copy_options::recursive); }
        catch (exception e) { cout << "There had been an error copying default files. Please try again." << endl; }
    }   
    else {
        cout << "FAIL" << endl;
    }
    return;
}