#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Matrix
{
private:
    mutable vector<vector<double>> data;

public:
    Matrix(int rows, int cols);
    void generateSPDMatrix();
    void savetoCSV(const string &filename);
    void loadfromCSV(const string &filename);
    void display() const;
    int size() const;
    double& operator()(int row, int col);
    double operator()(int row, int col) const;
    // vector<vector<double>>getData();

    pair<Matrix, Matrix> choleskyDecomposition() const;
    pair<Matrix, Matrix> luDecomposition() const;
    pair<Matrix, Matrix> qrDecomposition() const;
};