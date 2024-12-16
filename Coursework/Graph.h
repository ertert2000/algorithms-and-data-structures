#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>


class Graph
{
private:
    int N;
    std::vector<std::vector<int>> matrix;
    std::vector<int> K;
    std::vector<int> U;
public:
    int maxv = 0;

    std::vector<int> ans;

    Graph(int N);

    Graph();

    Graph(const Graph&) = delete;

    Graph(Graph&&) = delete;

	void addEdge(int v1, int v2);

    void PrintGraph();

    void BruteForce(int currentDepth, Graph& parentGraph);

    void CreateRandGraph();

    void CreateGraph();

    Graph& operator=(const Graph& other);

    ~Graph();
};

