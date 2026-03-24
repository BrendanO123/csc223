#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "graph.h"
#include "doctest.h"

using namespace std;

// for doctest
template class Graph<int>;

TEST_CASE("create and destroy graph"){
    Graph<int> graph = Graph<int>();
    CHECK_EQ(graph.nodeCount(), 0);
}

TEST_CASE("insert nodes into graph and check node count"){
    Graph<int> graph = Graph<int>();
    CHECK(graph.insertNode(1));
    CHECK(graph.insertNode(2));
    CHECK(graph.insertNode(3));
    CHECK_EQ(graph.nodeCount(), 3);
    CHECK_FALSE(graph.insertNode(1));
    CHECK_EQ(graph.nodeCount(), 3);
}

TEST_CASE("insert and connect nodes in graph"){
    Graph<int> graph = Graph<int>();
    CHECK(graph.insertNode(1));
    CHECK(graph.insertNode(2));
    CHECK(graph.insertNode(3));
    CHECK(graph.connectNodes(1, 2));
    CHECK(graph.connectNodes(2, 3));
    CHECK_FALSE(graph.connectNodes(1, 4));
    CHECK_FALSE(graph.connectNodes(4, 1));
    // check that the nodes are connected
    vector<Node<int>*> adjacentNodes1 = graph.fetchNode(1)->adjacentNodes;
    vector<Node<int>*> adjacentNodes2 = graph.fetchNode(2)->adjacentNodes;
    vector<Node<int>*> adjacentNodes3 = graph.fetchNode(3)->adjacentNodes;
    CHECK_EQ(adjacentNodes1.size(), 1);
    CHECK_EQ(adjacentNodes1[0]->data, 2);
    CHECK_EQ(adjacentNodes2.size(), 2);
    CHECK_EQ(adjacentNodes2[0]->data, 1);
    CHECK_EQ(adjacentNodes2[1]->data, 3);
    CHECK_EQ(adjacentNodes3.size(), 1);
    CHECK_EQ(adjacentNodes3[0]->data, 2);
}

TEST_CASE("delete nodes from graph"){
    Graph<int> graph = Graph<int>();
    CHECK(graph.insertNode(1));
    CHECK(graph.insertNode(2));
    CHECK(graph.insertNode(3));
    CHECK(graph.del(2));
    CHECK_EQ(graph.nodeCount(), 2);
    CHECK_FALSE(graph.del(4));
}

TEST_CASE("display graph no errors"){
    Graph<int> graph;
    CHECK(graph.insertNode(1));
    CHECK(graph.insertNode(2));
    CHECK(graph.insertNode(3));
    CHECK(graph.connectNodes(1, 2));
    CHECK(graph.connectNodes(2, 3));
    graph.display();
}