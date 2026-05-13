#include <fstream>
#include <iostream>

/*
 * Using Files for Data Storage
 * Steps:
 *  - Open the file
 *  - Use the file (read from, write to, or both)
 *  - Close the file
 *  Use fstream header file for file access
 *  - ifstream for input from a file
 *  - ofstream for output to a file
 *  - fstream for input from or output to a file
 *
 *  Define file stream objects:
 *  - ifstream infile;
 *  - ofstream outfile;
 */

using namespace std;
int main() {
  float grade1, grade2, grade3;   // This defines 3 float variables
  ifstream dataFile;              // This defines an input file stream.
                                  // dataFile is the "internal" name that is
                                  // used in the program for accessing the
                                  // data file.
  ofstream outFile;               // This defines an output file stream.
                                  // outFile is the "internal" name that is
                                  // used in the program for accessing the
                                  // output file.
  outFile << fixed << showpoint;  // These can be used with output files as
                                  // well as with cout.
  dataFile.open("grades.dat");    // This ties the internal name, dataFile,
                                  // to the actual file, grades.dat.
  outFile.open("finalgrade.out"); // This ties the internal name, outFile, to
                                  // the actual file, finalgrade.out.
  dataFile >> grade1 >> grade2    // This reads the values from the input file
      >> grade3;                  // into the 3 variables.
  outFile << grade1 << endl;      // These 3 lines write the values stored in
  outFile << grade2 << endl;      // the 3 variables to the output file
  outFile << grade3 << endl;
  return 0;
}
