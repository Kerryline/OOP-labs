#include "Matrix.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Matrix::Matrix()
    : data_(nullptr), rows_(0), cols_(0)
{
}

Matrix::Matrix(int size)
    : data_(nullptr), rows_(size), cols_(size)
{
    if (size < 0) {
        throw std::invalid_argument("Размерность не может быть отрицательной");
    }
    if (size == 0) {
        return;
    }

    data_ = new int*[rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new int[cols_]{};
    }

    for (int i = 0; i < rows_; ++i) {
        data_[i][i] = 1;
    }
}

Matrix::Matrix(int rows, int cols)
    : data_(nullptr), rows_(rows), cols_(cols)
{
    if (rows < 0 || cols < 0) {
        throw std::invalid_argument("Размерность не может быть отрицательной");
    }
    if (rows == 0 || cols == 0) {
        rows_ = 0;
        cols_ = 0;
        return;
    }

    data_ = new int*[rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new int[cols_]{};

    }
}

Matrix::~Matrix() {
    if (data_ == nullptr) {
        return;
    }

    for (int i = 0; i < rows_; ++i) {
        delete[] data_[i];
    }
    delete[] data_;
}

int Matrix::get(int i, int j) const {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Индекс выходит за границы матрицы");
    }
    return data_[i][j];
}

void Matrix::set(int i, int j, int value) {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Индекс выходит за границы матрицы");
    }
    data_[i][j] = value;
}


void Matrix::inputFromKeyboard() {
    std::cout << "Введите " << rows_ * cols_ << " чисел:\n";
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            std::cin >> data_[i][j];
        }
    }
}

void Matrix::fillRandom() {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] = rand() % 100;
        }
    }
}


void Matrix::print() const {
    if (rows_ == 0 || cols_ == 0) {
        std::cout << "(пустая матрица 0×0)\n";
        return;
    }
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            std::cout << data_[i][j] << '\t';
        }
        std::cout << '\n';
    }
}

int Matrix::sum() const {
    int result = 0;
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result += data_[i][j];
        }
    }
    return result;
}

int Matrix::getRows() const { return rows_; }
int Matrix::getCols() const { return cols_; }

Matrix Matrix::transpose() const {
    Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result.set(j, i, data_[i][j]);
        }
    }
    return result;
}