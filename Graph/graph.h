#pragma once

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

template <typename t>
struct Node{
    t data;
    vector<Node<t>*> adjacentNodes;
    Node(t dat) : data(dat){adjacentNodes = vector<Node<t>*>();}
    Node(){adjacentNodes = vector<Node<t>*>();}
};
template <typename t>
class Graph{
    unordered_map<string, Node<t>*> nodes;
    bool insertNode(string name, t value);
    bool connectNodes(string node1, string node2);
    bool connectNodes(Node<t>* node1, Node<t>* node2);
    Node<t>* fetchNode(string name);
    bool del(string name);
    Node<t>* pop(string name);
    Graph(){nodes = unordered_map<string, Node<t>*>();}
    ~Graph();
};