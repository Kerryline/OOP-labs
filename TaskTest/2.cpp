#include <iostream>

using namespace std;

int main() {
    const int ROWS = 3;
    const int COLS = 3;
    int matrix[ROWS][COLS];

    int value = 1;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            matrix[i][j] = value++;
        }
    }

    cout << "Матрица 3x3:\n";
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}