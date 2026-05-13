#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int rows = 3, cols = 4;
  vector<vector<float>> profit(rows, vector<float>(cols));

  for (int x = 0; x < rows; x++) {
    for (int y = 0; y < cols; y++) {
      cout << "Enter profit: ";
      cin >> profit[x][y];
    }
  }

  // Output
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << setw(4) << profit[i][j] << " ";
    }
    cout << endl;
  }
}
