#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <exception>
#include "BST.h"

int main() 
{
    std::ofstream out("results.txt");
    if (!out) 
    {
        std::cerr << "It was not possible to open the file for recording results.\n";
        return 1;
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int size = 10; size <= 200; size += 1) 
    {
        try 
        {
            auto start = std::chrono::high_resolution_clock::now();

            auto [B, C] = BSTListStructure::prepareIntersection(size, size * 3, size / 3);
            auto D = BSTListStructure::generate(size, size * 3);
            auto E = BSTListStructure::generate(size, size * 3);
            auto A = BSTListStructure::generate(size, size * 3);

            auto step1 = BSTListStructure::intersect(B, C);
            auto step2 = BSTListStructure::unify(D, E);
            auto step3 = BSTListStructure::concatSeq(step2, A);
            auto result = BSTListStructure::unify(step1, step3);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            size_t totalPower = A.getPower() + B.getPower() + C.getPower() + D.getPower() + E.getPower() + step1.getPower() + step2.getPower() + step3.getPower() + result.getPower();
            int containerCount = 9;
            double avgPower = static_cast<double>(totalPower) / containerCount;

            std::cout << size << " " << duration << " " << avgPower << "\n";
            out << size << " " << duration << "\n";
        }
        catch (const std::bad_alloc&)
        {
            std::cerr << "Not enough memory with size: " << size << ". Pass.\n";
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error in size " << size << ": " << e.what() << "\n";
        }
    }

    out.close();
    return 0;
}
