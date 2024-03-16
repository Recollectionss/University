#include <iostream>
#include <vector>
#include "cmath"

//// Функція для додавання двох матриць
std::vector<std::vector<double>> matrixAddition(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B) {
    int n = A.size();
    std::vector<std::vector<double>> C(n, std::vector<double>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

//// Функція для віднімання двох матриць
std::vector<std::vector<double>> matrixSubtraction(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B) {
    int n = A.size();
    std::vector<std::vector<double>> C(n, std::vector<double>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    return C;
}

//// Функція для множення матриць методом Штрассена
std::vector<std::vector<double>> strassenMultiplication(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B) {
    int n = A.size();

    if (n <= 2) {
        // Для множення невеликих матриць
        std::vector<std::vector<double>> C(n, std::vector<double>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return C;
    }

    int half = n / 2;

    // Разбиття матриці на підматриці
    std::vector<std::vector<double>> A11(half, std::vector<double>(half));
    std::vector<std::vector<double>> A12(half, std::vector<double>(half));
    std::vector<std::vector<double>> A21(half, std::vector<double>(half));
    std::vector<std::vector<double>> A22(half, std::vector<double>(half));
    std::vector<std::vector<double>> B11(half, std::vector<double>(half));
    std::vector<std::vector<double>> B12(half, std::vector<double>(half));
    std::vector<std::vector<double>> B21(half, std::vector<double>(half));
    std::vector<std::vector<double>> B22(half, std::vector<double>(half));

    for (int i = 0; i < half; ++i) {
        for (int j = 0; j < half; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    // Обчислення допоміжних матриць
    std::vector<std::vector<double>> P1 = strassenMultiplication(matrixAddition(A11, A22), matrixAddition(B11, B22));
    std::vector<std::vector<double>> P2 = strassenMultiplication(matrixAddition(A21, A22), B11);
    std::vector<std::vector<double>> P3 = strassenMultiplication(A11, matrixSubtraction(B12, B22));
    std::vector<std::vector<double>> P4 = strassenMultiplication(A22, matrixSubtraction(B21, B11));
    std::vector<std::vector<double>> P5 = strassenMultiplication(matrixAddition(A11, A12), B22);
    std::vector<std::vector<double>> P6 = strassenMultiplication(matrixSubtraction(A21, A11), matrixAddition(B11, B12));
    std::vector<std::vector<double>> P7 = strassenMultiplication(matrixSubtraction(A12, A22), matrixAddition(B21, B22));

    // Визначення результатних підматриць
    std::vector<std::vector<double>> C11 = matrixAddition(matrixSubtraction(matrixAddition(P1, P4), P5), P7);
    std::vector<std::vector<double>> C12 = matrixAddition(P3, P5);
    std::vector<std::vector<double>> C21 = matrixAddition(P2, P4);
    std::vector<std::vector<double>> C22 = matrixAddition(matrixAddition(matrixSubtraction(P1, P2), P3), P6);

    // Збір результату із підматриць
    std::vector<std::vector<double>> C(n, std::vector<double>(n));
    for (int i = 0; i < half; ++i) {
        for (int j = 0; j < half; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }

    return C;
}


//// Функція для обчислення детермінанта матриці розмірності n x n
template<typename T>
T determinant(std::vector<std::vector<T>>& matrix) {
    int n = matrix.size();
    if (n == 0 || matrix[0].size() != n) {
        // Матриця не є квадратною або порожньою
        return 0;
    }

    if (n == 1) {
        return matrix[0][0];
    }

    T det = 0;
    int sign = 1;
    for (int i = 0; i < n; ++i) {
        std::vector<std::vector<T>> submatrix(n - 1, std::vector<T>(n - 1));
        for (int j = 1; j < n; ++j) {
            int k = 0;
            for (int l = 0; l < n; ++l) {
                if (l != i) {
                    submatrix[j - 1][k++] = matrix[j][l];
                }
            }
        }
        det += sign * matrix[0][i] * determinant(submatrix);
        sign = -sign;
    }

    return det;
}

//// Функція для обчислення оберненої матриці за допомогою методу мінорів
template<typename T>
std::vector<std::vector<T>> inverseMatrix(std::vector<std::vector<T>>& matrix) {
    int n = matrix.size();
    std::vector<std::vector<T>> invMatrix(n, std::vector<T>(n));

    T det = determinant(matrix);
    if (det == 0) {
        std::cout << "Детермінант дорівнює нулю, обернена матриця не існує." << std::endl;
        return invMatrix;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::vector<std::vector<T>> submatrix(n - 1, std::vector<T>(n - 1));
            int p = 0, q = 0;
            for (int k = 0; k < n; ++k) {
                if (k != i) {
                    q = 0;
                    for (int l = 0; l < n; ++l) {
                        if (l != j) {
                            submatrix[p][q] = matrix[k][l];
                            ++q;
                        }
                    }
                    ++p;
                }
            }
            invMatrix[j][i] = (T)(std::pow(-1, i + j) * determinant(submatrix) / det);
        }
    }

    return invMatrix;
}

//// Функція для виведення матриці на екран
template<typename T>
void printMatrix(std::vector<std::vector<T>>& matrix) {
    for (const auto& row : matrix) {
        for (const T& elem : row) {
            std::cout << elem << "\t";
        }
        std::cout << std::endl;
    }
}

int main() {


    //// Приклад використання
    std::vector<std::vector<double>> A = {{1, sqrt(2), -3, 4},
                                       {5, -4, 3.5, -2},
                                       {7, 3, -1, 6},
                                       {3, -4, sqrt(5), 2}};
    std::vector<std::vector<double>> B = {{7, 1, -9, 8},
                                       {1, 2, 2, 4},
                                       {5, 2, 7, 2},
                                       {-9, 3, 1, -2}};


    std::vector<std::vector<double>> C = strassenMultiplication(A, B);

    std:: cout << "Початкова матриця А: \n";
    printMatrix(A);
    std:: cout << "\nПочаткова матриця В: \n";
    printMatrix(B);


    std::cout << "\nМноження матриць методом Штрассена:" << std::endl;
    printMatrix(C);

    std::vector<std::vector<double>>invmatrix = inverseMatrix(C);


    std::cout << "\nОбернена матриця:" << std::endl;
    printMatrix(invmatrix);

    return 0;
}
