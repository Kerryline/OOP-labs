#include <iostream>

using namespace std;

int main() {
    int x = 5;
    int* ptr = &x;

    cout << "Исходное x = " << x << endl;

    *ptr = *ptr + 3;

    cout << "Новое x = " << x << endl;

    return 0;
}