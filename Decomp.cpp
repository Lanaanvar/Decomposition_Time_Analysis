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
        generateSPDMatrix();
    }

    void generateSPDMatrix()
    {
        MatrixXd L = MatrixXd::Random(size, size).array().abs();
        symmetricMatrix = L * L.transpose();
    }

    void displayMatrix(const MatrixXd &matrix, const string &title) const
    {
        cout << "\n"
             << title << ":\n"
             << matrix << "\n\n";
    }

    void decomposeAndMeasureTime()
    {
        const int numIterations = 10;

        auto start = high_resolution_clock::now();
        for (int i = 0; i < numIterations; ++i)
        {
            qrDecomposition();
        }
        auto stop = high_resolution_clock::now();
        auto qr_duration = duration_cast<microseconds>(stop - start) / numIterations;
        cout << "x----------------------------------------------------------------------------------x"
             << "\n";
        cout << "Average QR Decomposition Time: " << qr_duration.count() << " microseconds\n\n";

        start = high_resolution_clock::now();
        for (int i = 0; i < numIterations; ++i)
        {
            luDecomposition();
        }
        stop = high_resolution_clock::now();
        auto lu_duration = duration_cast<microseconds>(stop - start) / numIterations;
        cout << "x----------------------------------------------------------------------------------x"
             << "\n";
        cout << "Average LU Decomposition Time: " << lu_duration.count() << " microseconds\n\n";

        start = high_resolution_clock::now();
        for (int i = 0; i < numIterations; ++i)
        {
            choleskyDecomposition();
        }
        stop = high_resolution_clock::now();
        auto cholesky_duration = duration_cast<microseconds>(stop - start) / numIterations;
        cout << "x----------------------------------------------------------------------------------x"
             << "\n";
        cout << "Average Cholesky Decomposition Time: " << cholesky_duration.count() << " microseconds\n\n";

        double qr_cholesky_ratio = static_cast<int>(qr_duration.count()) / cholesky_duration.count();
        double lu_cholesky_ratio = static_cast<int>(lu_duration.count()) / cholesky_duration.count();
        double cholesky_cholesky_ratio = static_cast<int>(cholesky_duration.count()) / cholesky_duration.count();

        cout << "x----------------------------------------------------------------------------------x"
             << "\n";

        cout << "QR : LU : Cholesky -> " << qr_cholesky_ratio << " : " << lu_cholesky_ratio << " : " << cholesky_cholesky_ratio << endl;
    }
};

int main()
{
    int matrixSize;
    cout << "\nEnter the size of the matrix : ";
    cin >> matrixSize;

    MatrixDecomposer decomposer(matrixSize);

    decomposer.decomposeAndMeasureTime();

    cout << "\n\n";

    return 0;
}
