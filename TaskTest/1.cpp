#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    const int SIZE = 8;
    int arr[SIZE];

    for (int i = 0; i < SIZE; ++i) {
        arr[i] = rand() % 50 + 1;
    }

    cout << "Чётные элементы массива: ";
    for (int i = 0; i < SIZE; ++i) {
        if (arr[i] % 2 == 0) {
            cout << arr[i] << " ";
        }
    }
    cout << endl;

    return 0;
}
