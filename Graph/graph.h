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
    unordered_map<t, Node<t>*> nodes;
    bool insertNode(t value);
    bool connectNodes(t node1, t node2);
    bool connectNodes(Node<t>* node1, Node<t>* node2);
    Node<t>* fetchNode(t name);
    bool del(t name);
    Node<t>* pop(t name);
    Graph(){nodes = unordered_map<t, Node<t>*>();}
    ~Graph();
};