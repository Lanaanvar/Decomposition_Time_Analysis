#include "comp.h"
#include "SPD.h"
using namespace std;

pair<long long, tuple<Matrix, Matrix>> MatrixComparator::measureTime(const Matrix &mat, function<tuple<Matrix, Matrix>(const Matrix &)> decompositionFunc)
{
    auto start = chrono::high_resolution_clock::now();
    auto decompositionResult = decompositionFunc(mat);
    auto end = chrono::high_resolution_clock::now();

    long long duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    return make_pair(duration, decompositionResult);
}

void MatrixComparator::compareAll(const Matrix &mat)
{
    auto timeTakenLU = measureTime(mat, &Matrix::luDecomposition);
    auto timeTakenQR = measureTime(mat, &Matrix::qrDecomposition);
    auto timeTakenCL = measureTime(mat, &Matrix::choleskyDecomposition);

    cout << "LU Decomposition Time : " << timeTakenLU.first << " microseconds\n";
    cout << "QR Decomposition Time : " << timeTakenQR.first << " microseconds\n";
    cout << "Cholesky Decomposition Time : " << timeTakenCL.first << " microseconds\n";
}
