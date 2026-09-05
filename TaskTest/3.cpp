#include <iostream>

using namespace std;

bool isPositive(int num) {
    return num > 0;
}

int main() {
    int a;
    cout << "Введите целое число: ";
    cin >> a;

    if (isPositive(a)) {
        cout << "Число положительное" << endl;
    } else {
        cout << "Число не положительное (отрицательное или ноль)" << endl;
    }

    return 0;
}