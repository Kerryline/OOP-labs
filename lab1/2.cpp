#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int* genRandArray(int size, int maxValue) {
    int* arr = new int[size + 1];
    arr[0] = size;
    for (int i = 1; i <= size; ++i) {
        arr[i] = rand() % (maxValue + 1);
    }
    return arr;
}

void print(int* arr) {
    int size = arr[0];
    cout << size << ": ";
    for (int i = 1; i <= size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int** genRandMatrix(int rows, int maxValue) {
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        int rowSize = rand() % 10 + 1;
        matrix[i] = genRandArray(rowSize, maxValue);
    }
    return matrix;
}

void printMatrix(int** matrix, int rows) {
    cout << rows << endl;
    for (int i = 0; i < rows; ++i) {
        print(matrix[i]);
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int rows = rand() % 10;
    int maxValue = 100;
    int** matrix = genRandMatrix(rows, maxValue);
    printMatrix(matrix, rows);

    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}