#pragma once
#include <vector>
#include <string>
using namespace std;

class Graph {
public:
    Graph() {}
    ~Graph() {}
    void addEdge(string st1, string st2);
    void addVertex(int vnumber);

    void print_friends(int** matrix_v, string name_user);
    void print_3h(int** matrix_v, string name_user);
    void print_other(int** matrix_v, string name_user);

    void findMinDistancesFloyd(string name_user);
    bool edgeExists(int v1, int v2);

    vector<vector<int>> matrix; // матрица смежности
    int size_matrix;
    vector<string> vname;
    vector<int> vertexes;
};