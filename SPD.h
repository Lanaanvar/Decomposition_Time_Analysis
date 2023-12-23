#include<iostream>
#include<vector>
using namespace std;

class Matrix{
    private:
    vector<vector<double>> data;

    public:
    Matrix(int rows, int cols);
    void generateSPDMatrix();
    void savetoCSV(const string& filename);
    void loadfromCSV(const string& filename);
    void display()const;
    // vector<vector<double>>getData();

    Matrix choleskyDecomposition() const;
    pair<Matrix, Matrix> luDecomposition() const;
    pair<Matrix, Matrix> qrDecomposition() const;
    
};