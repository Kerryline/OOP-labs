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

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int size = rand() % 10;
    int maxValue = 100;
    int* arr = genRandArray(size, maxValue);
    print(arr);

    delete[] arr;
    return 0;
}