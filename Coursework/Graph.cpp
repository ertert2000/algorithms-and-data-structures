#include "Graph.h"


Graph::Graph(int N) : N(N), matrix(N, std::vector<int>(N, 0)), U(N, 1), K(N), ans(N) {}

Graph::Graph() : N(1), matrix(1, std::vector<int>(1, 0)), U(1, 1), K(1), ans(1) {}

void Graph::addEdge(int v1, int v2)
{
    matrix[v1][v2] = 1;
    matrix[v2][v1] = 1;
}

void Graph::PrintGraph()
{
    if (N < 21) 
    {
        std::cout << "\nAdjacency matrix:";
        std::cout << "\n      ";

        for (int i = 0; i < N; ++i)
            std::cout << i + 1 << " ";

        std::cout << "\n----------------------------------------";

        for (int i = 0; i < N; ++i) 
        {
            if (i + 1 >= 10)
                std::cout << "\n " << i + 1 << "| ";
            else
                std::cout << "\n " << i + 1 << " | ";
            for (int j = 0; j < N; ++j)
                std::cout << " " << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Graph::BruteForce(int currentDepth, Graph& parentGraph)
{
    int vertex, startIndex, neighbor;
    if (currentDepth == 1)
        startIndex = 0;
    else
        startIndex = K[currentDepth - 2] + 1;

    for (vertex = startIndex; vertex < N; vertex++)
        if (U[vertex])
        {
            K[currentDepth - 1] = vertex;
            neighbor = 0;
            while ((neighbor < currentDepth) && (K[neighbor] < N) && (vertex < N) && matrix[K[neighbor]][vertex])
                neighbor++;

            if (neighbor + 1 == currentDepth)
            {
                if (currentDepth > maxv)
                {
                    maxv = currentDepth;
                    for (int i = 0; i < currentDepth; ++i)
                        ans[i] = K[i] + 1;
                }
                if (currentDepth == maxv)
                {
                    std::cout << '\n' << " max=" << maxv << " : ";

                    for (int i = 0; i < maxv; ++i)
                        std::cout << (K[i] + 1) << " ";
                }

                U[vertex] = 0;
                parentGraph.BruteForce(currentDepth + 1, *this);
                U[vertex] = 1;
            }
        }
}

void Graph::CreateRandGraph()
{
    for (auto i = 0; i < N; ++i)
    {
        U[i] = 1;
        for (auto j = i; j < N; ++j)
        {
            if (j == i)
                matrix[i][j] = 0;
            else
                matrix[i][j] = matrix[j][i] = rand() % 15 > 2;
        }
    }
}

void Graph::CreateGraph()
{
    int tempmatrix[5][5] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 1},
        {1, 0, 1, 0, 1},
        {0, 1, 1, 1, 0}
    };

    for (auto i = 0; i < N; ++i)
    {
        U[i] = 1;
        for (auto j = 0; j < N; ++j)
        {
            matrix[i][j] = tempmatrix[i][j];
        }
    }
}

Graph& Graph::operator=(const Graph& other)
{
    if (this == &other)
        return *this;

    N = other.N;
    maxv = other.maxv;

    matrix = other.matrix;
    K = other.K;
    U = other.U;
    ans = other.ans;

    return *this;
}

Graph::~Graph() {}
