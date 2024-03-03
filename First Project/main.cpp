//Import iostream for input/output
#include <iostream>
#include <string>

int main() {
    std::string name;
    int age;

    std::cout << "Enter your name" << std::endl;
    std::getline(std::cin, name);

    std::cout << "Enter your age" << std::endl;
    std::cin >> age;

    std::cout << name << ", you are " << age << " years old" << std::endl;
    return 0;
} 