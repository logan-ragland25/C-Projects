#include <iostream>
using namespace std;
#include <string>
#include <filesystem>
namespace fs = std::filesystem;

void Randomize();

int main() {
    Randomize();
    cout << "success!" << endl;
    return 0;
}

void Randomize() {
    string texturePackName;
    cout << "What do you want to call this texture pack?\n\t";
    getline(cin, texturePackName);
    if (!fs::exists("/Minecraft Texture Pack Randomizer/randomizedTexturePacks/" + texturePackName)) { 
        fs::create_directories("/Minecraft Texture Pack Randomizer/randomizedTexturePacks/" + texturePackName);
        //filesystem::copy("/defaultTexturePack", "/randomizedTexturePacks/" + texturePackName); 
    }   
    else {
        cout << "FAIL" << endl;
    }
    return;
}