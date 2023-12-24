// // main.cpp
// #include "SPD.h"
// #include "comp.h"

// int main()
// {
//     int choice;
//     Matrix A(3, 3); // Change the dimensions as needed

//     do
//     {
//         std::cout << "\n-------------------------------------------------\n";
//         std::cout << "--------------------Main Menu--------------------\n";
//         std::cout << "1. Generate Matrix \n";
//         std::cout << "2. Display \n";
//         std::cout << "3. LU Decomposition\n";
//         std::cout << "4. QR Decomposition\n";
//         std::cout << "5. Cholesky Decomposition\n";
//         std::cout << "6. Run n times (all decompositions)\n";
//         std::cout << "7. Compare\n";
//         std::cout << "8. Exit\n";
//         std::cout << "Enter your choice : ";
//         std::cin >> choice;
//         std::cout << "-------------------------------------------------\n"
//                   << std::endl;

//         switch (choice)
//         {
//         case 1:
//         {
//             auto result = A.luDecomposition();
//             std::cout << "L:\n";
//             result.first.display();
//             std::cout << "U:\n";
//             result.second.display();
//             break;
//         }
//         case 2:
//         {
//             auto result = A.qrDecomposition();
//             std::cout << "Q:\n";
//             result.first.display();
//             std::cout << "R:\n";
//             result.second.display();
//             break;
//         }
//         case 3:
//         {
//             auto result = A.choleskyDecomposition();
//             std::cout << "L (Cholesky):\n";
//             result.first.display();
//             std::cout << "I:\n";
//             result.second.display();
//             break;
//         }
//         case 4:
//         {
//             MatrixComparator::compareAll(A);
//             break;
//         }
//         case 5:
//         {
//             MatrixComparator::compareAll(A);
//             break;
//         }
//         case 6:
//             std::cout << "Exiting program.\n";
//             break;
//         default:
//             std::cout << "Invalid choice. Please try again.\n";
//         }
//     } while (choice != 6);

//     return 0;
// }
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
        std::cout << "1. Generate Matrix \n";
        std::cout << "2. Display \n";
        std::cout << "3. LU Decomposition\n";
        std::cout << "4. QR Decomposition\n";
        std::cout << "5. Cholesky Decomposition\n";
        std::cout << "6. Run n times (all decompositions)\n";
        std::cout << "7. Compare\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice : ";
        std::cin >> choice;
        std::cout << "-------------------------------------------------\n"
                  << std::endl;

        switch (choice)
        {
        case 1:
        {
            A.generateSPDMatrix(); // Generate a matrix
            std::cout << "Matrix Generated:\n";
            A.display();
            break;
        }
        case 2:
        {
            std::cout << "Matrix Display:\n";
            A.display();
            break;
        }
        case 3:
        {
            auto result = A.luDecomposition();
            std::cout << "L (LU Decomposition):\n";
            result.first.display();
            std::cout << "U:\n";
            result.second.display();
            break;
        }
        case 4:
        {
            auto result = A.qrDecomposition();
            std::cout << "Q (QR Decomposition):\n";
            result.first.display();
            std::cout << "R:\n";
            result.second.display();
            break;
        }
        case 5:
        {
            auto result = A.choleskyDecomposition();
            std::cout << "L (Cholesky Decomposition):\n";
            result.first.display();
            std::cout << "I:\n";
            result.second.display();
            break;
        }
        case 6:
            MatrixComparator::compareAll(A);
            break;
        case 7:
            MatrixComparator::compareAll(A);
            break;
        case 8:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}
