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
        vector<Node<t>*> adj = node->adjacentNodes;
        cout << val << " has " << adj.size() << (adj.size() == 1 ? " neighbor" : " neighbors") << endl;
        for(int i = 0; i<adj.size(); i++){
            Node<t>* n = adj[i];
            cout << " " << n->data << endl;
        }
    }
}

int main(){
    Graph<int> graph;
    cout << "Welcome to the Graph Creation Wizard™." << endl;
    char input;
    int node1, node2;
    while(true){
        cout << "Either add a node [A] or connect a node [C]." << endl;
        cout << "When done, type Q to display your graph." << endl;
        cin >> input;
        if(input == 'A'){
            cout << "Enter the value of the node you want to add." << endl;
            cin >> node1;
            if(graph.insertNode(node1)){
                cout << "Node added successfully." << endl;
            } else {
                cout << "Node already exists." << endl;
            }
        } else if(input == 'C'){
            cout << "Enter the values of the nodes you want to connect." << endl;
            cin >> node1 >> node2;
            if(graph.connectNodes(node1, node2)){
                cout << "Nodes connected successfully." << endl;
            } else {
                cout << "One or both nodes do not exist." << endl;
            }
        } else if(input == 'Q'){
            graph.display();
            break;
        } else {
            cout << "Invalid input. Please enter either A for add or C for connect." << endl; 
        }
    }
}