#include <iostream>
#include "Graph.h"

int main()
{
    char choose;
    int N;
    Graph A(0);

    std::cout << "#=================#" << std::endl;
    std::cout << "1 - autogeneration" << std::endl;
    std::cout << "2 - ready asset" << std::endl;
    std::cout << "#=================#" << std::endl;

    std::cin >> choose;

    switch (choose)
    {
    case '1':
        system("cls");
        std::cout << "Enter the number of vertices (max 20): ";
        std::cin >> N;

        if (N > 0 && N <= 20)
        {
            A = Graph(N);
            A.CreateRandGraph();
            A.PrintGraph();
            A.BruteForce(1, A);

            std::cout << "\nBOTTOM LINE: Power " << A.maxv << ", verse: ";
            for (auto i = 0; i < A.maxv; ++i)
                std::cout << A.ans[i] << " ";
        }
        else
            std::cerr << "Error: Number of vertices must be between 1 and 20." << std::endl;

        break;

    case '2':
        system("cls");
        A = Graph(5);
        A.CreateGraph();
        A.PrintGraph();
        A.BruteForce(1, A);

        std::cout << "\nBOTTOM LINE: Power " << A.maxv << ", verse: ";
        for (auto i = 0; i < A.maxv; ++i)
            std::cout << A.ans[i] << " ";

        break;

    default:
        std::cerr << "Error: Incorrect selection." << std::endl;
        break;
    }

    std::cout << std::endl;
    return 0;
}
