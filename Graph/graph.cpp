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
    node1->adjacentNodes.emplace(node1->data, node2);
    node2->adjacentNodes.emplace(node2->data, node1);
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
    for(int i = node->adjacentNodes.size()-1; i >=0; i--){
        
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

int main(){
    Graph<int> IGraph = Graph<int>();
    Graph<string> SGraph = Graph<string>();
    cout << "Welcome to the Graph Creation Wizard™." << endl;
    cout << "Enter either [I] for an integer graph or [S] for a string graph." << endl;
    char type;
    cin >> type;
    char input;
    int node1, node2;
    string n1, n2;
    getline(cin, n1);
    while(true){
        cout << "Either add a node [A], connect a node [C], remove a node [R], or display the graph [D]." << endl;
        cout << "When done, type Q to display your graph." << endl;
        cin >> input; getline(cin, n1);
        if(input == 'A'){
            cout << "Enter the value of the node you want to add." << endl;
            switch(type){
                case 'I':
                    cin >> node1; getline(cin, n1);
                    if(IGraph.insertNode(node1)){
                        cout << "Node added successfully." << endl;
                    } else {
                        cout << "Node already exists." << endl;
                    }
                    break;
                case 'S':
                default:
                    getline(cin, n1);
                    if(SGraph.insertNode(n1)){
                        cout << "Node added successfully." << endl;
                    } else {
                        cout << "Node already exists." << endl;
                    }
                    break;
            }
        } else if(input == 'C'){
            cout << "Enter the values of the nodes you want to connect on two lines." << endl;
            switch(type){
                case 'I':
                    cin >> node1; getline(cin, n1);
                    cin >> node2; getline(cin, n1);
                    if(IGraph.connectNodes(node1, node2)){
                        cout << "Nodes connected successfully." << endl;
                    } else {
                        cout << "One or both nodes do not exist." << endl;
                    }
                    break;
                case 'S':
                default:
                    getline(cin, n1);
                    getline(cin, n2);
                    if(SGraph.connectNodes(n1, n2)){
                        cout << "Nodes connected successfully." << endl;
                    } else {
                        cout << "One or both nodes do not exist." << endl;
                    }
                    break;
            }
        } else if(input == 'Q' || input == 'D'){
            switch(type){
                case 'I':
                IGraph.display();
                break;
            case 'S':
            default:
                SGraph.display();
                break;
            }
            if(input == 'Q'){break;}
        } else if(input == 'R'){
            cout << "Enter the value of the node you want to remove." << endl;
            Node<int>* INode;
            Node<string>* SNode;
            switch(type){
                case 'I':
                    cin >> node1; getline(cin, n1);
                    if(IGraph.del(node1)){
                        cout << "Removed node " << node1 << '.' << endl;
                    }
                    else{
                        cout << "Node does not exist." << endl;
                    }
                    break;
                case 'S':
                    getline(cin, n1);
                    if(SGraph.del(n1)){
                        cout << "Removed node " << n1 << '.' << endl;
                    }
                    else{
                        cout << "Node does not exist." << endl;
                    }
                    break;
            }
        } else {
            cout << "Invalid input. Please enter either A, C, D, R, or Q." << endl; 
        }
    }
}