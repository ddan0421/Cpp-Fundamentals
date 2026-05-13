#include <iostream>
#include <string>

using namespace std;

class Address {
public:
    string city;
    string street;
    int zip;
    Address(string c, string s, int z) : city(c), street(s), zip(z) {}
};

class Person {
private:
    Address address;
public:
    Person(string city, string street, int zip) : address(city, street, zip) {}
    void showAddress() {
        cout << "City: " << address.city << endl; 
        cout << "Street: " << address.street << endl;
        cout << "Zip: " << address.zip << endl;
    }
};


int main(){
    Person person1("Duluth", "Oakton St", 879711);
    person1.showAddress();
    return 0;
}
