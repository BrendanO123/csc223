#include "graph.h"
#include <iostream>

using namespace std;

template <typename t>
requires Hashable<t>
bool Graph<t> :: insertNode(t value){
    if(nodes.find(value) != nodes.end()){return false;}
    Node node = new Node(value);
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

int main(){
    Graph<int> graph = Graph();
    graph.insertNode(1);
    cout << graph.fetchNode(1)->data << endl;
    cout << graph.pop(1)->data << endl;
    graph.insertNode(1);
    graph.insertNode(2);
    graph.connectNodes(1,2);
    cout << graph.fetchNode(2)->adjacentNodes.at(0)->data << endl;
    return 0;
}