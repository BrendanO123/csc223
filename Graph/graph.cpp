#include "graph.h"
#include <iostream>

using namespace std;

template<typename t>
requires Hashable<t>
size_t Graph<t> :: nodeCount(){
    return nodes.size();
}

template <typename t>
requires Hashable<t>
bool Graph<t> :: insertNode(t value){
    if(nodes.find(value) != nodes.end()){return false;}
    Node<t>* node = new Node<t>(value);
    nodes.emplace(value, node);
    return true;
}

template <typename t>
requires Hashable<t>
bool Graph<t> :: connectNodes(t node1, t node2){
    return connectNodes(fetchNode(node1), fetchNode(node2));
}

template <typename t>
requires Hashable<t>
bool Graph<t> :: connectNodes(Node<t>* node1, Node<t>* node2){
    if(node1 == nullptr){return false;}
    if(node2 == nullptr){return false;}
    node1->adjacentNodes.emplace(node2->data, node2);
    node2->adjacentNodes.emplace(node1->data, node1);
    return true;
}

template <typename t>
requires Hashable<t>
Node<t>* Graph<t> :: fetchNode(t value){
    if(nodes.find(value) == nodes.end()){return nullptr;}
    return nodes.at(value);
}

template <typename t>
requires Hashable<t>
bool disconnect(Node<t>* node){
    for(auto iterate = node->adjacentNodes.begin(); iterate != node->adjacentNodes.end(); iterate++){
        Node<t>* node1 = iterate->second;
        node1->adjacentNodes.erase(node->data);
    }
    return true;
}

template <typename t>
requires Hashable<t>
bool Graph<t> :: del(t value){
    Node<t>* node = pop(value);
    if(node == nullptr){return false;}
    disconnect(node);
    delete node;
    return true;
}

template <typename t>
requires Hashable<t>
Node<t>* Graph<t> :: pop(t value){
    if(nodes.find(value) == nodes.end()){return nullptr;}
    Node<t>* node = nodes.at(value);
    nodes.erase(value);
    return node;
}

template <typename t>
requires Hashable<t>
Graph<t> ::  ~Graph(){
    for(auto iterate = nodes.begin(); iterate!=nodes.end();){
        delete iterate->second;
        iterate = nodes.erase(iterate);
    }
}

template <typename t>
requires Hashable<t>
void Graph<t> :: display(){
    for(auto iterate = nodes.begin(); iterate != nodes.end(); iterate++){
        t val = iterate->first;
        Node<t>* node = iterate->second;
        unordered_map<t, Node<t>*> adj = node->adjacentNodes;
        cout << val << " has " << adj.size() << (adj.size() == 1 ? " neighbor" : " neighbors") << endl;
        for(auto iterate = adj.begin(); iterate != adj.end(); iterate++){
            Node<t>* n = iterate->second;
            cout << " " << n->data << endl;
        }
    }
}

template class Graph<int>;
template class Graph<string>;