#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int rows;
    cout << "Введите количество строк: ";
    cin >> rows;

    if (rows <= 0) {
        cout << "Количество строк должно быть положительным.\n";
        return 1;
    }

    int** matrix = new int*[rows];
    int*  sizes  = new int[rows];

    cout << "Введите количество элементов для каждой строки:\n";
    for (int i = 0; i < rows; ++i) {
        cout << "  Строка " << i << ": ";
        cin >> sizes[i];
        if (sizes[i] < 0) {
            cout << "  Длина не может быть отрицательной → 0\n";
            sizes[i] = 0;
        }
        matrix[i] = (sizes[i] > 0) ? new int[sizes[i]] : nullptr;
    }

    // заполнение
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < sizes[i]; ++j)
            matrix[i][j] = rand() % 100;

    // вывод построчно
    cout << "\nДвумерный динамический массив (зубчатый):\n";
    for (int i = 0; i < rows; ++i) {
        cout << "Строка " << i << " (" << sizes[i] << " эл.):";
        for (int j = 0; j < sizes[i]; ++j)
            cout << setw(4) << matrix[i][j];
        cout << "\n";
    }

    // освобождение
    for (int i = 0; i < rows; ++i)
        delete[] matrix[i];
    delete[] matrix;
    delete[] sizes;

    return 0;
}
