// main.cpp
#include "SPD.h"
#include "comp.h"

int main()
{
    int choice;
    Matrix A(3, 3); // Change the dimensions as needed

    do
    {
        std::cout << "\n-------------------------------------------------\n";
        std::cout << "--------------------Main Menu--------------------\n";
        std::cout << "1. LU Decomposition\n";
        std::cout << "2. QR Decomposition\n";
        std::cout << "3. Cholesky Decomposition\n";
        std::cout << "4. Run n times (all decompositions)\n";
        std::cout << "5. Compare\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice : ";
        std::cin >> choice;
        std::cout << "-------------------------------------------------\n"
                  << std::endl;

        switch (choice)
        {
        case 1:
        {
            auto result = A.luDecomposition();
            std::cout << "L:\n";
            result.first.display();
            std::cout << "U:\n";
            result.second.display();
            break;
        }
        case 2:
        {
            auto result = A.qrDecomposition();
            std::cout << "Q:\n";
            result.first.display();
            std::cout << "R:\n";
            result.second.display();
            break;
        }
        case 3:
        {
            auto result = A.choleskyDecomposition();
            std::cout << "L (Cholesky):\n";
            result.first.display();
            std::cout << "I:\n";
            result.second.display();
            break;
        }
        case 4:
        {
            MatrixComparator::compareAll(A);
            break;
        }
        case 5:
        {
            MatrixComparator::compareAll(A);
            break;
        }
        case 6:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
