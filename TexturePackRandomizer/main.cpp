#include <iostream>
using namespace std;
#include <string>
#include <list>
#include <filesystem>
namespace fs = std::filesystem;
#include <direct.h>
#include <vector>
#include <map>

//Declare Variables
int Randomize();
void addAllFilesToMap(string, map<string, string>*, vector<string>*);

string path;
string texturePackName;

int main() {
    //Store path to project
    char buffer[256];
    path = getcwd(buffer, sizeof(buffer));
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

    for (auto const&  folder : fs::directory_iterator{ path + "\\randomizedTexturePacks\\" + texturePackName + "\\assets\\minecraft\\textures\\" }) { 
        //Declare Variables
        string directoryPath = folder.path().generic_string();
        map<string, string> filePaths;
        vector <string> fileNames = {};
        
        addAllFilesToMap(directoryPath, &filePaths, &fileNames);

        for (const auto & [key, value] : filePaths) { 
            //Declare Variables
            string originalFileName, randomFileName, placeholder = "";
            originalFileName = key;
            randomFileName = fileNames[rand() % fileNames.size()];

            placeholder = "placeholder.png";
            
            //Make sure randomly selected file is not the same as the original file
            while (originalFileName == randomFileName) {  randomFileName = fileNames[rand() % fileNames.size()]; }

            //Rename original file to placeholder so there are no duplicated names
            //Set the randomly selected file's name to the original file
            //Set the original file to the randomly selected file's name
            rename((value).c_str(), (directoryPath + placeholder).c_str());
            rename((filePaths[randomFileName]).c_str(), (value).c_str());
            rename((directoryPath + "placeholder.png").c_str(), (filePaths[randomFileName]).c_str());
        }

    }
    cout << "All Textures Successfully Randomized!" << endl;
    return 0;
}

void addAllFilesToMap(string path, map<string, string>* map, vector<string>* fileNames){
    //Recurseively loop through directory
    for (auto const& recursiveFile : fs::recursive_directory_iterator(path)) { 
        int count = 0;

        //Count files/folders in directory
        try { if (is_directory(recursiveFile)) { for (auto const&  file : fs::directory_iterator{ recursiveFile }) { count++; } } } 
        catch (exception e) { cout << e.what() << endl; }

        //Recursively call function to get to all files
        if (count > 1) addAllFilesToMap(recursiveFile.path().string(), map, fileNames);

        //Add files to map and vector
        if (!is_directory(recursiveFile)) {
            (*map)[recursiveFile.path().filename().string()] = recursiveFile.path().string();
            (*fileNames).push_back(recursiveFile.path().filename().string());
        }
    }
    return;
}