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