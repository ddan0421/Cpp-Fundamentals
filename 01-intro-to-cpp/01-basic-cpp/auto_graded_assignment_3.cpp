#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main(){
  string name, eventType, location, color, speaker;
  int numGuests;
  
  cout << "Please enter your name:" << endl;
  getline(cin, name);
  cout << "Please enter the type of event you are planning:" << endl;
  getline(cin, eventType);
  cout << "Please enter the location of the event:" << endl;
  getline(cin, location);
  cout << "Please enter the main theme or color scheme of the event:" << endl;
  getline(cin, color);
  cout << "Please enter the name of a key guest or speaker:" << endl;
  getline(cin, speaker);
  cout << "Please enter the number of guests expected:" <<endl;
  cin >> numGuests;
  
  cin.ignore();

  cout << "Hello " << name << "!" <<endl << "Your " << eventType
    << " is all set to happen at " << location << ".\n"
    << "You can expect around " << numGuests << " guests to join the celebration.\n"
    << "The event will be adorned with a " << color << " theme, making it a memorable day.\n"
    << "Special guest " << speaker << " will be the highlight of the event.\n"
    << "We are looking forward to helping you make your event successful!\n";
  return 0;

}




