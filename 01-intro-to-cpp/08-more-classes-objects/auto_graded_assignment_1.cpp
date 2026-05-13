// Goal: Learn how to write an interactive program using classes.
//
// Assignment: You are an inventory manager in the mystical world of Classica,
// an ancient civilization known for its enchanted artifacts. Your role is to
// manage these artifacts using a program that organizes, updates, and displays
// them. This program is your key to maintaining the balance and prosperity of
// Classica.
//
// Your task is to create an Artifact class and a main function that utilizes
// this class. The program should be interactive and allow the user to add,
// update, and display artifacts in the inventory.
//
// Artifact Class Requirements:
//
// Data Members:
//
// name: A string to store the artifact's name.
// category: A string to store the category of the artifact (e.g., "weapon",
// "tool", "jewelry"). age: An integer to store the age of the artifact in
// years. Constructors:
//
// A default constructor that initializes the artifact's name to "Unknown",
// category to "None", and age to 0. A parameterized constructor that takes
// values for the name, category, and age in this order. Mutators (Setters):
//
// setName: Accepts a string and sets the artifact's name.
// setCategory: Accepts a string and sets the artifact's category.
// setAge: Accepts an integer and sets the artifact's age.
// Accessors (Getters):
//
// getName: Returns the artifact's name.
// getCategory: Returns the artifact's category.
// getAge: Returns the artifact's age.
// Overloaded Operators:
//
// Overload the << operator to display the artifact's details in the format:
// "Name: [name], Category: [category], Age: [age] years". Main Function
// Requirements:
//
// Prompt the user to enter details for an artifact (name, category, age) and
// use the input to create an Artifact object using the parameterized
// constructor. Display the created artifact's details using the overloaded <<
// operator. Allow the user to update the artifact's category and display the
// updated details. I/O Specifications:
//
// Input: The program should ask the user for the artifact's name, category, and
// age as shown in the sample run below. Output: The program should output the
// artifact's details as shown in the sample run below.

#include <iostream>
#include <string>
// Dan Dan

using namespace std;

class Artifact {
private:
  string name;
  string category;
  int age;

public:
  Artifact();
  Artifact(string n, string c, int a);

  void setName(string n);
  void setCategory(string c);
  void setAge(int a);

  string getName() const;
  string getCategory() const;
  int getAge() const;
};

Artifact::Artifact() : name("Unknown"), category("None"), age(0) {}

Artifact::Artifact(string n, string c, int a) {
  name = n;
  category = c;
  age = a;
}

void Artifact::setName(string n) { name = n; };
void Artifact::setCategory(string c) { category = c; };
void Artifact::setAge(int a) { age = a; };

string Artifact::getName() const { return name; }
string Artifact::getCategory() const { return category; }
int Artifact::getAge() const { return age; }

/*
When you write: cout << "hello"; the compiler turns it into:
cout.operator<<("hello"); (this uses built-in overloads provided by the standard
library)

cout is an object of type ostream. So cout is an instance of a class ostream

so when you overload << for a custom type, you define a function like:
operator<<(ostream& os, const Artifact& artifact); and then the expression:
cout << artifact becomes operator<<(cout, artifact);
*/
ostream &operator<<(ostream &os, const Artifact &obj) {
  os << "Name: " << obj.getName() << ", Category: " << obj.getCategory()
     << ", Age: " << obj.getAge() << " years" << endl;
  return os;
}

int main() {
  string ArtName;
  string ArtCat;
  int ArtAge;

  cout << "Enter artifact's name: ";
  getline(cin, ArtName);

  cout << "Enter artifact's category: ";
  getline(cin, ArtCat);

  cout << "Enter artifact's age: ";
  cin >> ArtAge;

  cin.ignore();

  Artifact art(ArtName, ArtCat, ArtAge);

  cout << "\nArtifact Details:" << endl;
  cout << art;

  cout << "\nUpdate artifact's category: ";
  getline(cin, ArtCat);
  art.setCategory(ArtCat);
  cout << "Updated Artifact Details: " << endl;
  cout << art;

  return 0;
}
