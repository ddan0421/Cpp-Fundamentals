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

class Artifact() {
private:
  string name;
  string category;
  int age;
};
