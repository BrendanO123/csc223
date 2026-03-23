#include "graph.h"

using namespace std;

template <typename t>
bool Graph<t> :: insertNode(string name, t value){
    if(nodes.find(name) != nodes.end()){return false;}
    Node node = new Node(value);
    nodes.emplace(name, node);
    return true;
}

template <typename t>
bool Graph<t> :: connectNodes(string node1, string node2){
    return connectNodes(fetchNode(node1), fetchNode(node2));
}

template <typename t>
bool Graph<t> :: connectNodes(Node<t>* node1, Node<t>* node2){
    if(node1 == nullptr){return false;}
    if(node2 == nullptr){return false;}
    node1->adjacentNodes.emplace_back(node2);
    node2->adjacentNodes.emplace_back(node1);
    return true;
}

template <typename t>
Node<t>* Graph<t> :: fetchNode(string name){
    if(nodes.find(name) == nodes.end()){return nullptr;}
    return nodes.at(name);
}

template <typename t>
bool Graph<t> :: del(string name){
    if(nodes.find(name) == nodes.end()){return false;}
    delete nodes.at(name);
    nodes.erase(name);
}
template <typename t>
Node<t>* Graph<t> :: pop(string name){
    if(nodes.find(name) == nodes.end()){return nullptr;}
    Node<t>* node = nodes.at(name);
    nodes.erase(name);
    return node;
}

template <typename t>
Graph<t> ::  ~Graph(){
    for(auto iterate = nodes.begin(); iterate!=nodes.end();){
        delete iterate->second;
        iterate = nodes.erase(iterate);
    }
}