#include <iostream>
#include <Eigen/Dense>
#include <chrono>

using namespace Eigen;
using namespace std;
using namespace chrono;

class MatrixDecomposer
{

protected:
    MatrixXd symmetricMatrix;
    MatrixXd Q, R, L, U, L_cholesky;
    int size;

    void qrDecomposition()
    {
        HouseholderQR<MatrixXd> qr(symmetricMatrix);
        Q = qr.householderQ();
        R = qr.matrixQR().triangularView<Upper>();
    }

    void luDecomposition()
    {
        FullPivLU<MatrixXd> lu(symmetricMatrix);
        L = lu.matrixLU().triangularView<Lower>();
        U = lu.matrixLU().triangularView<Upper>();
    }

    void choleskyDecomposition()
    {
        LLT<MatrixXd> llt(symmetricMatrix);
        L_cholesky = llt.matrixL();
    }

public:
    const MatrixXd &getSymmetricMatrix() const
    {
        return symmetricMatrix;
    }
    MatrixDecomposer(int size) : size(size)
    {
        // Initialize the random symmetric positive definite matrix
        generateSymmetricPositiveDefiniteMatrix();
    }

    void generateSymmetricPositiveDefiniteMatrix()
    {
        // Generate a random symmetric positive definite matrix
        MatrixXd A = MatrixXd::Random(size, size);
        symmetricMatrix = A * A.transpose();
    }

    void displayMatrix(const MatrixXd &matrix, const string &title) const
    {
        cout << title << ":\n"
             << matrix << "\n\n";
    }

    void decomposeAndMeasureTime()
    {
        const int numIterations = 10000; // Adjust the number of iterations as needed

        // QR decomposition
        auto start = high_resolution_clock::now();
        for (int i = 0; i < numIterations; ++i)
        {
            qrDecomposition();
        }
        auto stop = high_resolution_clock::now();
        auto qr_duration = duration_cast<microseconds>(stop - start) / numIterations;
        displayMatrix(Q, "QR Decomposition (Q matrix)");
        displayMatrix(R, "QR Decomposition (R matrix)");
        cout << "Average QR Decomposition Time: " << qr_duration.count() << " microseconds\n\n";

        // LU decomposition
        start = high_resolution_clock::now();
        for (int i = 0; i < numIterations; ++i)
        {
            luDecomposition();
        }
        stop = high_resolution_clock::now();
        auto lu_duration = duration_cast<microseconds>(stop - start) / numIterations;
        displayMatrix(L, "LU Decomposition (L matrix)");
        displayMatrix(U, "LU Decomposition (U matrix)");
        cout << "Average LU Decomposition Time: " << lu_duration.count() << " microseconds\n\n";

        // Cholesky decomposition
        start = high_resolution_clock::now();
        for (int i = 0; i < numIterations; ++i)
        {
            choleskyDecomposition();
        }
        stop = high_resolution_clock::now();
        auto cholesky_duration = duration_cast<microseconds>(stop - start) / numIterations;
        displayMatrix(L_cholesky, "Cholesky Decomposition (L matrix)");
        cout << "Average Cholesky Decomposition Time: " << cholesky_duration.count() << " microseconds\n\n";

        // Calculate the ratios
        double qr_ratio = static_cast<double>(qr_duration.count()) / lu_duration.count();
        double cholesky_ratio = static_cast<double>(cholesky_duration.count()) / lu_duration.count();

        cout << "QR Decomposition Time / LU Decomposition Time Ratio: " << qr_ratio << endl;
        cout << "Cholesky Decomposition Time / LU Decomposition Time Ratio: " << cholesky_ratio << endl;
    }
};

int main()
{
    int matrixSize = 4; // Set the size of the matrix

    MatrixDecomposer decomposer(matrixSize);
    decomposer.displayMatrix(decomposer.getSymmetricMatrix(), "Generated Symmetric Positive Definite Matrix");

    decomposer.decomposeAndMeasureTime();

    return 0;
}
