#include <iostream>
using namespace std;
#include <string>
#include <fstream>

int main() {
    //Declare Variables
    ofstream PasswordsFile("Password Creator\\passwords.txt", ios::app);
    string characterList = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890~`!@#$%^&*_-+=<,>.?/";

    string sitename;
    string username;
    string pLengthInput;
    int pLength;
    string password = "";

    //Get Name of Site
    cout << "Please enter the name of the website or software:\n\t-";
    getline(cin, sitename);

    //Get Username
    cout << "\nPlease enter your username:\n\t-";
    getline(cin, username);

    //Get Password Length
    cout << "\nPlease enter the length of your password (Must be between 8 and 32 characters):\n\t-";
    getline(cin, pLengthInput);
    try { pLength = stoi(pLengthInput); }
    catch (exception e) { }
    
    //Make sure password meets requested length and is not a string
    if (pLength < 8 || pLength > 32) {
        while (true) {
            cout << "\nPlease match the requested format of an integer between 8 and 32 characters):\n\t-";
            getline(cin, pLengthInput);
            try { 
                pLength = stoi(pLengthInput);
                if (pLength >= 8 && pLength <= 32) {
                    break;
                }
            }
            catch (exception e) {
                cout << "Please enter a number!" << endl;
            }
        }
    }

    //Seed random value
    srand((unsigned) time(NULL));
    
    //Create password from characters acoording to inputed length
    for (int pos = 0; pos < pLength; pos++) { password += characterList[rand() % characterList.length()]; }

    //Print data into file then close it
    PasswordsFile << "Site: " << sitename << "\nUsername: " << username << "\nPassword: " << password << "\n" << endl;
    PasswordsFile.close();

    //Notify user password successfully generated
    cout << "\nSuccess! Your random password is " << password << endl;
}