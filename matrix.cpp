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

// vector<vector<double>> Matrix::getData()
// {
//     return data;
// }

// void generateSPDMatrix(Matrix &matrix) {
//     int n;
//     std::cout << "Enter the size of the matrix: ";
//     std::cin >> n;

//     matrix.getData() = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));

//     for (int i = 0; i < n; ++i) {
//         for (int j = i; j < n; ++j) {
//             matrix.getData() = matrix.getData() = static_cast<double>(rand()) / RAND_MAX;
//         }
//     }

//     for (int i = 0; i < n; ++i) {
//         for (int j = 0; j < i; ++j) {
//             matrix.getData() = matrix.getData();
//         }
//     }

//     for (int i = 0; i < n; ++i) {
//         matrix.data[i][i] += 1.0;
//     }
// }

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
            cout << fixed << setprecision(6) << value << " ";
        }
        cout << "\n";
    }
}

Matrix Matrix::choleskyDecomposition() const
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
    return L;
}

pair<Matrix, Matrix> Matrix::luDecomposition() const
{
    Matrix L(data.size(), data.size()), U(data.size(), data.size());
    for (int i=0; i<data.size(); i++)
    {
        for(int j=0; j<data.size(); j++)
        {
            if(i>j)
            {
                L.data[i][j]=data[i][j];
                U.data[i][j]=0.0;
            }
            else if(i==j){
                L.data[i][j]=1.0;
                U.data[i][j]=data[i][j];
            }
            else{
                L.data[i][j]=0.0;
                U.data[i][j]=data[i][j];
            }
        }
    }
    for(int k=0; k<data.size(); k++)
    {
        for(int i=k+1; ++i<data.size(); ++i)
        {
            L.data[i][k]=U.data[i][k]/U.data[i][k];
            for(int j=k; j<data.size(); ++j)
            {
                U.data[i][j] -=L.data[i][k]*U.data[k][j];
            }
        }
    }
    return make_pair(L, U);
}

pair<Matrix, Matrix> Matrix::qrDecomposition() const
{
    Matrix Q(data.size(), data.size()), R(data.size(), data.size());
    for(int k=0; k<data.size(); k++)
    {
        double norm=0.0;
        for(int i=0; i<data.size(); i++)
        {
            norm +=data[i][k]*data[i][k];
        }
        norm = sqrt(norm);

        for(int i=0; i<data.size(); i++)
        {
            Q.data[i][k]= data[i][k]/norm;
        }

        for(int j=k; j<data.size(); j++)
        {
            double sum =0.0;
            for(int i=0; i<data.size(); i++)
            {
                sum+= Q.data[i][k]*data[i][j];
            }
            R.data[k][j]=sum;
        }

        for(int i=0; i<data.size(); i++)
        {
            for(int j=k+1; j<data.size(); j++)
            {
                Q.data[i][j] -=R.data[k][j]*Q.data[i][k];
            }
        }
    }

    return make_pair(Q, R);
}