#pragma once
#include <chrono>
#include <tuple>
#include <functional>
#include "SPD.h"

using namespace std;

class MatrixComparator
{

public:
    static pair<long long, tuple<Matrix, Matrix>> measureTime(const Matrix &mat, function<tuple<Matrix, Matrix>(const Matrix &)> decompositionFunc);
    static void compareAll(const Matrix &mat);
};
// #pragma once
// #include <chrono>
// #include <tuple>
// #include <functional>

// // Forward declaration of Matrix class
// class Matrix;

// class MatrixComparator
// {
// public:
//     static std::pair<long long, std::tuple<Matrix, Matrix>> measureTime(const Matrix &mat, std::function<std::tuple<Matrix, Matrix>(const Matrix &)> decompositionFunc);
//     static void compareAll(const Matrix &mat);
// };
