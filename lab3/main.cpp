#include "Matrix.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    Matrix m1;
    Matrix m2(3);
    Matrix m3(3, 4);
    Matrix m4(2, 3);

    std::cout << "m1 (0×0):\n";
    m1.print();
    std::cout << "\nm2 (3×3, единичная):\n";
    m2.print();
    std::cout << "\nm3 (3×4, нули):\n";
    m3.print();
    std::cout << "\nm4 (2×3, нули):\n";
    m4.print();

    std::cout << "\nm2 после заполнения i*j\n";
    for (int i = 0; i < m2.getRows(); ++i) {
        for (int j = 0; j < m2.getCols(); ++j) {
            m2.set(i, j, i * j);
        }
    }
    m2.print();

    std::cout << "\nm3 после fillRandom()\n";
    m3.fillRandom();
    m3.print();

    std::cout << "\nm4: ввод с клавиатуры\n";
    m4.inputFromKeyboard();
    std::cout << "m4 после ввода:\n";
    m4.print();

    std::cout << "\nСумма элементов m3 = " << m3.sum() << "\n";

    std::cout << "\nДемонстрация исключений\n";
    try {
        Matrix bad(-1, 5);
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }
    try {
        m3.get(100, 100);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }

    std::cout << "\nКопирование Matrix mm = m3\n";
    Matrix mm = m3;
    mm.print();

    std::cout << "\nТранспонированная m3\n";
    Matrix tr = m3.transpose();
    tr.print();

    std::cout << "\nКонец программы\n";
    return 0;
}