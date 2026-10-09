#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
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
    int ci = N / 2, cj = N / 2;

    vector<vector<bool>> visited(N, vector<bool>(N, false));
    int di[] = {0, 1, 0, -1}; // вправо, вниз, влево, вверх
    int dj[] = {1, 0, -1, 0};

    int i = ci, j = cj;
    D[idx++] = matrix[i][j];
    visited[i][j] = true;

    int dir = 0;
    int steps = 1;

    while (idx < N * N) {
        for (int k = 0; k < 2 && idx < N * N; ++k) {
            for (int s = 0; s < steps && idx < N * N; ++s) {
                i += di[dir];
                j += dj[dir];
                if (i >= 0 && i < N && j >= 0 && j < N && !visited[i][j]) {
                    D[idx++] = matrix[i][j];
                    visited[i][j] = true;
                }
            }
            dir = (dir + 1) % 4;
        }
        ++steps;
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
