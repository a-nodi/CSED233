#pragma once
#include <fstream>
#include <iostream>
#include <string>
#define NodeMaxCount 101
#define INF 2147483647
using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////

typedef struct node {
  string label;
  int aList_index;
  node *next;
} Node;

typedef struct adjacency_list {
  string label;
  int aList_index;
  int count;
  node *head;
} Adjacency_list;

typedef struct {
  int count; // # of elements in the current stack
  Node *top; // Pointer that points to the top node of stack
} Stack;

typedef struct {
  int count;   // # of elements in the current queue
  Node *front; // Pointer that points to the front node of queue
  Node *rear;  // Pointer that points to the rear node of queue
} Queue;

typedef struct {
  string label;
  int aList_index;
  int distance;
} PNode;

typedef struct {
  string source;
  string destination;
  int source_index;
  int destination_index;
  int edge_cost;
} EdgeNode;

typedef struct string_node{
	string path;
	string_node *next;
} StringNode;

typedef struct {
	int count;
	string_node *head;
} StringList;

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph {
public:
  Graph(){};
  ~Graph(){};

  string DFS();
  string BFS();

  int addDirectedEdge(string nodeA, string nodeB);
  int addDirectedEdge(string nodeA, string nodeB, int weight);
  int addUndirectedEdge(string nodeA, string nodeB);
  int addUndirectedEdge(string nodeA, string nodeB, int weight);

  int countUndirectedCycle();
  string getTopologicalSort();
  int countDirectedCycle();
  string getShortestPath(string source, string destination);
  string getAllShortestPaths();
  int primMST(ofstream &, string startNode);
  int kruskalMST(ofstream &);

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////

  Adjacency_list *aList = NULL;
  int **path_cost = NULL;
  int *num_parent = NULL;
  int *distance = NULL;
  int len = 0;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
