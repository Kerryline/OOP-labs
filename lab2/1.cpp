#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

void printMatrix(int** matrix, int N) {
    cout << "\nМатрица " << N << "x" << N << ":\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << setw(5) << matrix[i][j];
        cout << "\n";
    }
}

void printArray(const char* title, int* D, int size) {
    cout << "\n" << title << "\n";
    for (int i = 0; i < size; ++i) {
        cout << setw(5) << D[i];
        if ((i + 1) % 10 == 0) cout << "\n";
    }
    if (size % 10 != 0) cout << "\n";
}

// a) по правым диагоналям, начиная с правого верхнего
void fillByRightDiagonals(int** matrix, int N, int* D) {
    int idx = 0;
    // s = i + j  от N-1 вниз до 0, затем от N до 2N-2
    for (int s = N - 1; s >= 0; --s) {
        for (int i = 0; i <= s; ++i) {
            int j = s - i;
            if (j >= 0 && j < N)
                D[idx++] = matrix[i][j];
        }
    }
    for (int s = N; s <= 2 * (N - 1); ++s) {
        for (int i = s - (N - 1); i < N; ++i) {
            int j = s - i;
            if (j >= 0 && j < N)
                D[idx++] = matrix[i][j];
        }
    }
}

// b) по левым диагоналям, начиная с левого верхнего
void fillByLeftDiagonals(int** matrix, int N, int* D) {
    int idx = 0;
    // диагонали, стартующие на верхней строке
    for (int start_j = 0; start_j < N; ++start_j) {
        int i = 0, j = start_j;
        while (i < N && j < N) {
            D[idx++] = matrix[i][j];
            ++i; ++j;
        }
    }
    // диагонали, стартующие на левом столбце
    for (int start_i = 1; start_i < N; ++start_i) {
        int i = start_i, j = 0;
        while (i < N && j < N) {
            D[idx++] = matrix[i][j];
            ++i; ++j;
        }
    }
}

// c) по спирали, начиная с центрального элемента
void fillBySpiralFromCenter(int** matrix, int N, int* D) {
    int idx = 0;
    int ci = N / 2, cj = N / 2;   // центр (для чётного N берём правый нижний из четырёх центральных)

    // Спираль = кольцо за кольцом: слой l состоит из клеток,
    // расстояние до центра по строке/столбцу которых равно l.
    int maxLayer = max(max(ci, N - 1 - ci), max(cj, N - 1 - cj));

    for (int l = 0; l <= maxLayer; ++l) {
        int top    = max(0, ci - l);
        int bottom = min(N - 1, ci + l);
        int left   = max(0, cj - l);
        int right  = min(N - 1, cj + l);

        // Записываем периметр кольца по часовой стрелке:
        // верхняя строка → правый столбец → нижняя строка → левый столбец.
        // Фильтр dist==l нужен для чётного N: из-за смещённого центра
        // кольца неровные, часть клеток периметра уже записана раньше.
        auto emit = [&](int i, int j) {
            if (max(abs(i - ci), abs(j - cj)) == l) {
                D[idx++] = matrix[i][j];
            }
        };
        for (int j = left; j <= right; ++j) emit(top, j);
        for (int i = top + 1; i <= bottom; ++i) emit(i, right);
        for (int j = right - 1; j >= left; --j) emit(bottom, j);
        for (int i = bottom - 1; i > top; --i) emit(i, left);
    }
}

// d) по спирали, начиная с левого верхнего
void fillBySpiralFromTopLeft(int** matrix, int N, int* D) {
    int idx = 0;
    int top = 0, bottom = N - 1, left = 0, right = N - 1;

    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; ++j)
            D[idx++] = matrix[top][j];
        ++top;

        for (int i = top; i <= bottom; ++i)
            D[idx++] = matrix[i][right];
        --right;

        if (top <= bottom) {
            for (int j = right; j >= left; --j)
                D[idx++] = matrix[bottom][j];
            --bottom;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; --i)
                D[idx++] = matrix[i][left];
            ++left;
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int N;
    cout << "Введите размер матрицы N: ";
    cin >> N;

    if (N <= 0) {
        cout << "N должно быть положительным.\n";
        return 1;
    }

    // создание и заполнение матрицы
    int** matrix = new int*[N];
    for (int i = 0; i < N; ++i)
        matrix[i] = new int[N];

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            matrix[i][j] = rand() % 100;

    printMatrix(matrix, N);

    int size = N * N;
    int* D = new int[size];

    // a)
    fillByRightDiagonals(matrix, N, D);
    printArray("a) D — по правым диагоналям (с правого верхнего):", D, size);

    // b)
    fillByLeftDiagonals(matrix, N, D);
    printArray("b) D — по левым диагоналям (с левого верхнего):", D, size);

    // c)
    fillBySpiralFromCenter(matrix, N, D);
    printArray("c) D — по спирали от центра:", D, size);

    // d)
    fillBySpiralFromTopLeft(matrix, N, D);
    printArray("d) D — по спирали от левого верхнего:", D, size);

    // освобождение памяти
    for (int i = 0; i < N; ++i)
        delete[] matrix[i];
    delete[] matrix;
    delete[] D;

    return 0;
}
