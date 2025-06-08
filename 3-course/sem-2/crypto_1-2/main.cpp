#include <iostream>
#include <cmath>
#include <iomanip>

//Size
const int N = 4;


void gaussElimination(double A[N][N], double b[N], double x[N]) {
    // Gauss
    for (int i = 0; i < N; ++i) {
        // Finding main element
        int maxRow = i;
        for (int k = i + 1; k < N; ++k) {
            if (std::fabs(A[k][i]) > std::fabs(A[maxRow][i])) {
                maxRow = k;
            }
        }

        // Switch row
        for (int k = 0; k < N; ++k) {
            std::swap(A[i][k], A[maxRow][k]);
        }
        std::swap(b[i], b[maxRow]);

        // Transform to top triangle form
        for (int k = i + 1; k < N; ++k) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < N; ++j) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }

    // Back step
    for (int i = N - 1; i >= 0; --i) {
        x[i] = b[i];
        for (int j = i + 1; j < N; ++j) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}

int main() {
    double A[N][N] = {
        {0.1348531574394464, 0.1878970588235294, 0.1909117647058824, 0.1779264705882353},
        {0.1878970588235294, 0.262, 0.265, 0.247},
        {0.1909117647058824, 0.265, 0.281, 0.266},
        {0.1779264705882353, 0.247, 0.266, 255}
    };

    double b[N] = {0.3516, 0.4887, 0.5105, 0.4818};
    double x[N];

    gaussElimination(A, b, x);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Розв'язок x:\n";
    for (int i = 0; i < N; ++i) {
        std::cout << "x[" << i << "] = " << x[i] << "\n";
    }

    return 0;
}
