#include "Graph.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

// Add friend
void Graph::addEdge(string st1, string st2)
{
    int v1 = -1;
    int v2 = -1;
    for (int i = 0; i < vname.size(); i++) {
        if (vname[i] == st1)
            v1 = i;
        if (vname[i] == st2)
            v2 = i;
    }
    if (v1 == -1) {
        vname.push_back(st1);
        v1 = vname.size() - 1;
        addVertex(v1);
    }
    if (v2 == -1) {
        vname.push_back(st2);
        v2 = vname.size() - 1;
        addVertex(v2);
    }

    matrix[v1][v2] = 1;
    matrix[v2][v1] = 1;
}
// добавление человека
void Graph::addVertex(int value) {
    vertexes.push_back(value);
    size_matrix++;
    vector<vector<int>> newMatrix(size_matrix, vector<int>(size_matrix, 0));
    for (int i = 0; i < size_matrix - 1; i++) {
        for (int j = 0; j < size_matrix - 1; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    matrix = newMatrix;
}

//Алгоритм Флойда-Уоршелла (сокращенно — Флойда)
#define VERYBIGINT 1000000000
void Graph::findMinDistancesFloyd(string name_user)
{
    // матрица путей
    int** weights = new int* [size_matrix];
    for (int i = 0; i < size_matrix; i++) {
        weights[i] = new int[size_matrix];
    }
    // инициализаци матрицы
    for (int i = 0; i < size_matrix; i++)
    {
        for (int j = 0; j < size_matrix; j++)
        {
            if (i == j)
            {
                weights[i][j] = 0; // путь до самой себя равен 0
            }
            else {
                if (!edgeExists(i, j))
                {
                    weights[i][j] = VERYBIGINT; // если ребра нет
                }
                else {
                    weights[i][j] = matrix[i][j]; // если ребро есть
                }
            }
        }
    }

    for (int k = 0; k < vertexes.size(); k++) // итерации по k
    {
        int ck = vertexes[k]; // возьмем номер вершины
        for (int i = 0; i < vertexes.size(); i++)
        {
            if (i == k)
                continue;
            int ci = vertexes[i];
            for (int j = 0; j < vertexes.size(); j++)
            {
                if (j == k)
                    continue;
                int cj = vertexes[j];
                if (weights[ci][ck] + weights[ck][cj] < weights[ci][cj]) {
                    // пересчет мматрицы путей
                    weights[ci][cj] = weights[ci][ck] + weights[ck][cj];
                }
            }
        }
    }
    print_friends(weights, name_user);
    print_3h(weights, name_user);
    print_other(weights, name_user);
}

//Печать друзей
void Graph::print_friends(int** matrix_v, string name_user) {
    for (int i = 0; i < size_matrix; i++) {
        if (vname[i] == name_user && size_matrix > 1) {
            cout << vname[i] << " friends: ";
            int f = 0;
            for (int j = 0; j < size_matrix; j++) {
                if (matrix_v[i][j] == 1) {
                    if (f > 0)
                        cout << ", ";
                    cout << vname[j];
                    f++;
                }
            }
            if (f > 0) {
                cout << "." << endl;
            }
            else {
                cout << " you don`t have friends. " << endl;
            }
            break;
        }
    }
}

//Печать знакомств 3 рукопажатия
void Graph::print_3h(int** matrix_v, string name_user) {
    for (int i = 0; i < size_matrix; i++) {
        if (vname[i] == name_user) {
            cout << vname[i] << " could know: ";
            int f = 0;
            for (int j = 0; j < size_matrix; j++) {
                if (matrix_v[i][j] < 4 && matrix_v[i][j] >= 2) {
                    if (f > 0)
                        cout << ", ";
                    cout << vname[j];
                    f++;
                }
            }
            if (f > 0) {
                cout << "." << endl;
            }
            else {
                cout << " you need to add friends. " << endl;
            }
            break;
        }
    }
}

//Печать остальных пользователей
void Graph::print_other(int** matrix_v, string name_user) {
    cout << "Other online users: " << endl;
    set <string> other;
    for (int i = 0; i < size_matrix; i++) {
        for (int j = 0; j < size_matrix; j++) {
            if (vname[j] == name_user) {
                continue;
            }
            if ((matrix_v[i][j] == 0 && i != j) || matrix_v[i][j] > 3) {
                other.insert(vname[j]);
            }
        }
    }
    for (string element : other) {
        cout << element << ", ";
    }
    cout << endl << endl;
}

bool Graph::edgeExists(int v1, int v2)
{
    return matrix[v1][v2] > 0;
}
