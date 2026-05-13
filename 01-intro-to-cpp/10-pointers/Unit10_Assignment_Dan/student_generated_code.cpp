#include <iomanip>
#include <iostream>

using namespace std;

// Dan Dan

// Option 1: Write a program that will read scores into an array. The size of
// the array should be input by the user (dynamic array). The program will find
// and print out the average of the scores. It will also call a function that
// will sort (using a bubble sort) the scores in ascending order. The values are
// then printed in this sorted order.

void sort(int *, int);
void displayScores(int *, int);

int main() {
  int NumScores;
  float average;
  float total = 0;
  int *scores = nullptr;

  cout << fixed << showpoint << setprecision(2);

  cout << "Please input the number of scores" << endl;
  cin >> NumScores;

  while (NumScores <= 0) // checks for a legal value
  {
    cout << "There must be at least one score. Please reenter.\n";
    cout << "Please input the number of scores" << endl;
    cin >> NumScores;
  }

  scores = new int[NumScores];

  for (int i = 0; i < NumScores; i++) {
    cout << "Please enter a score" << endl;
    cin >> *(scores + i);
    total += *(scores + i);
  }
  average = total / NumScores;
  cout << "The average of the scores is " << average << endl;

  sort(scores, NumScores);
  cout << "\nHere are the scores in ascending order" << endl;
  displayScores(scores, NumScores);

  delete[] scores;
  scores = nullptr;

  return 0;
}

// Using bubble sort
void sort(int *score, int num_scores) {
  for (int i = num_scores - 1; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      if (score[j] > score[j + 1]) {
        int temp = score[j];
        score[j] = score[j + 1];
        score[j + 1] = temp;
      }
    }
  }
}

void displayScores(int *score, int numOfGrades) {
  for (int i = 0; i < numOfGrades; i++) {
    cout << score[i] << endl;
  }
}
