#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <concepts>

using namespace std;

template<typename T>
concept Hashable = requires(T a){
    { std::hash<T>{}(a) } -> std::convertible_to<size_t>;
};

template <typename t>
requires Hashable<t>
struct Node{
    t data;
    vector<Node<t>*> adjacentNodes;
    Node(t dat) : data(dat){adjacentNodes = vector<Node<t>*>();}
    Node(){adjacentNodes = vector<Node<t>*>();}
};

template <typename t>
requires Hashable<t>
class Graph{
    unordered_map<t, Node<t>*> nodes;
    public:
        size_t nodeCount();
        bool insertNode(t value);
        bool connectNodes(t node1, t node2);
        bool connectNodes(Node<t>* node1, Node<t>* node2);
        Node<t>* fetchNode(t name);
        bool del(t name);
        Node<t>* pop(t name);
        void display();
        Graph(){nodes = unordered_map<t, Node<t>*>();}
        ~Graph();
};