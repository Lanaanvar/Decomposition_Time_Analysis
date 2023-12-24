#include "SPD.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

Matrix::Matrix(int rows, int cols) : data(rows, vector<double>(cols, 0.0)) {}

void Matrix::generateSPDMatrix()
{
    int n;
    std::cout << "Enter the size of the matrix: ";
    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            data[i][j] = data[i][j] = static_cast<double>(rand()) / RAND_MAX;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            data[i][j] = data[j][i];
        }
    }

    for (int i = 0; i < n; ++i)
    {
        data[i][i] += 1.0;
    }
}

void Matrix::savetoCSV(const string &filename)
{
    ofstream file(filename);
    if (file.is_open())
    {
        for (const auto &row : data)
        {
            for (const auto &value : row)
            {
                file << fixed << setprecision(6) << value << ",";
            }
            file << "\n";
        }
        file.close();
    }
}

void Matrix::loadfromCSV(const string &filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        for (auto &row : data)
        {
            for (auto &value : row)
            {
                char comma;
                file >> value >> comma;
            }
        }
        file.close();
    }
}

void Matrix::display() const
{
    for (const auto &row : data)
    {
        for (const auto &value : row)
        {
            cout << fixed << setprecision(4) << value << " ";
        }
        cout << "\n";
    }
}

pair<Matrix, Matrix> Matrix::choleskyDecomposition() const
{
    Matrix L(data.size(), data.size());
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (i == j)
            {
                double sum = 0;
                for (int k = 0; k < j; k++)
                {
                    sum += L.data[i][j] * L.data[i][k];
                }
                L.data[i][j] = sqrt(data[i][j] - sum);
            }
            else
            {
                double sum = 0;
                for (int k = 0; k < j; k++)
                {
                    sum += L.data[i][k] * L.data[j][k];
                }
                L.data[i][j] = (data[i][j] - sum) / L.data[j][j];
            }
        }
    }
    Matrix I(data.size(), data.size());
    for (int i = 0; i < data.size(); i++)
    {
        I.data[i][i] = 1.0;
    }

    // return the decomposed matrix and the identity matrix
    return make_pair(L, I);
}

pair<Matrix, Matrix> Matrix::luDecomposition() const
{
    Matrix L(data.size(), data.size()), U(data.size(), data.size());
    // int n = m.rows;
    // Matrix L(n, n), U(n, n);
    int n = data.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            float sum = 0;
            for (int k = 0; k < i; k++)
            {
                sum += L.data[i][k] * U.data[k][j];
            }
            U.data[i][j] = data[i][j] - sum;
        }
        for (int j = i; j < n; j++)
        {
            if (i == j)
            {
                if (U.data[i][i] == 0)
                {
                    throw std::invalid_argument("[LU] => Division by zero.");
                }
                L.data[i][i] = 1;
            }
            else
            {
                float sum = 0;
                for (int k = 0; k < i; k++)
                {
                    sum += L.data[j][k] * U.data[k][i];
                }
                L.data[j][i] = (data[j][i] - sum) / U.data[i][i];
            }
        }
    }

    return make_pair(L, U);
}

// pair<Matrix, Matrix> Matrix::luDecomposition() const
// {
//     Matrix L(data.size(), data.size()), U(data.size(), data.size());

//     for (int i = 0; i < data.size(); i++)
//     {
//         for (int j = 0; j < data.size(); j++)
//         {
//             if (i > j)
//             {
//                 L.data[i][j] = data[i][j];
//                 U.data[i][j] = 0.0;
//             }
//             else if (i == j)
//             {
//                 L.data[i][j] = 1.0;
//                 U.data[i][j] = data[i][j];
//             }
//             else
//             {
//                 L.data[i][j] = 0.0;
//                 U.data[i][j] = data[i][j];
//             }
//         }
//     }

//     for (int k = 0; k < data.size(); k++)
//     {
//         for (int i = k + 1; i < data.size(); ++i)
//         {
//             if (U.data[i][k] != 0.0) // Check for zero division
//             {
//                 L.data[i][k] = U.data[i][k] / U.data[k][k];
//                 for (int j = k; j < data.size(); ++j)
//                 {
//                     U.data[i][j] -= L.data[i][k] * U.data[k][j];
//                 }
//             }
//         }
//     }

//     return make_pair(L, U);
// }

// double Matrix::operator()(int row, int col) const
// {
//     return data[row][col];
// }

// double &Matrix::operator()(int row, int col) const
// {
//     return data[row][col];
// }

// // Function to get the size of the matrix
// int Matrix::size() const
// {
//     return data.size();
// }

// Function to perform QR decomposition
pair<Matrix, Matrix> Matrix::qrDecomposition() const
{
    Matrix Q(data.size(), data.size()), R(data.size(), data.size());
    for (int k = 0; k < data.size(); ++k)
    {
        double norm = 0.0;
        for (int i = 0; i < data.size(); ++i)
        {
            norm += data[i][k] * data[i][k];
        }
        norm = std::sqrt(norm);

        for (int i = 0; i < data.size(); ++i)
        {
            Q.data[i][k] = data[i][k] / norm;
        }

        for (int j = k; j < data.size(); ++j)
        {
            double sum = 0.0;
            for (int i = 0; i < data.size(); ++i)
            {
                sum += Q.data[i][k] * data[i][j];
            }
            R.data[k][j] = sum;
        }

        for (int i = 0; i < data.size(); ++i)
        {
            for (int j = k + 1; j < data.size(); ++j)
            {
                data[i][j] -= R.data[k][j] * Q.data[i][k];
            }
        }
    }

    return std::make_pair(Q, R);
}
// pair<Matrix, Matrix> Matrix::qrDecomposition() const {
//     int n = data.size();
//     Matrix Q(n, n), R(n, n);

//     for (int k = 0; k < n; ++k) {
//         // Compute the Householder vector
//         float vNorm = 0;
//         for (int i = k; i < n; ++i) {
//             vNorm += data[i][k] * data[i][k];
//         }
//         // Ensure vNorm is non-zero to avoid division by zero
//         if (vNorm == 0) {
//             continue;  // Skip this column if it's already zero
//         }
//         float v = data[k][k] + std::copysign(vNorm, data[k][k]);
//         float vNormInv = 1.0f / std::sqrt(2 * vNorm);
//         Matrix vHouse = Matrix::identity(n, n);
//         vHouse.data[k][k] = v * vNormInv;
//         for (int i = k + 1; i < n; ++i) {
//             vHouse.data[i][k] = data[i][k] * vNormInv;
//         }

//         // Apply the Householder transformation
//         Q = Q * vHouse;
//         R = vHouse.transpose() * R;
//         R = R * vHouse;

//         // Update R (only the upper triangular part)
//         for (int i = k; i < n; ++i) {
//             R.data[i][k] = data[i][k];
//         }
//     }

//     return std::make_pair(Q.transpose(), R);  // Q is built as Q^T, so return its transpose
// }
