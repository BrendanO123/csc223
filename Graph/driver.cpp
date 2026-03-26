#include "graph.h"
#include <iostream>

using namespace std;

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