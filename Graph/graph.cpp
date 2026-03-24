#include "graph.h"
#include <iostream>

using namespace std;

template<typename t>
requires Hashable<t>
int Graph<t> :: nodeCount(){
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
    node1->adjacentNodes.emplace_back(node2);
    node2->adjacentNodes.emplace_back(node1);
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
bool Graph<t> :: del(t value){
    if(nodes.find(value) == nodes.end()){return false;}
    delete nodes.at(value);
    nodes.erase(value);
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
        vector<Node<t>*> adj = node->adjacentNodes;
        cout << val << " has " << adj.size() << " neighbors:" << endl;
        for(int i = 0; i<adj.size(); i++){
            Node<t>* n = adj[i];
            cout << " " << n->data << endl;
        }
    }
}