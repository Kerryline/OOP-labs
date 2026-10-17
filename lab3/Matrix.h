#pragma once

#include <stdexcept>

class Matrix {
public:
    // Конструкторы
    Matrix();
    explicit Matrix(int size);
    Matrix(int rows, int cols);

    // Конструктор копирования (глубокое копирование)
    Matrix(const Matrix& other);

    // Деструктор
    ~Matrix();

    // Доступ к элементам
    int  get(int i, int j) const;
    void set(int i, int j, int value);

    // Заполнение
    void inputFromKeyboard();
    void fillRandom();

    // Вывод
    void print() const;

    // Вычисление суммы всех элементов
    int sum() const;

    // Геттеры
    int getRows() const;
    int getCols() const;

    // Домашка
    Matrix transpose() const;

private:
    int** data_;
    int   rows_;
    int   cols_;
};