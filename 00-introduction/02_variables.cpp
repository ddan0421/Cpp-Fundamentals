#include <iostream>

int main(){
    
    int x; // declaration
    x = 5; // assignment

    // or
    // int x = 5;

    int y = 9;


    int sum = x + y;

    double gpa = 4.1;
    double temperature = 25.1;


    char grade = 'a';
    char currency = '$';

    bool student = true;
    bool power = false;


    std::string name = "Dan!";

    std::cout << "Hello" << " " << name << "\n";
    std::cout << "Yo " << name << "Temperature is " << temperature << " Celsius" << "\n";

    std::cout << x << "\n";
    std::cout << y << "\n";
    std::cout << sum << "\n";
    std::cout << temperature << "\n";
    std::cout << grade << "\n";
    std::cout << student << "\n";
    std::cout << power << "\n";

    return 0;
}
