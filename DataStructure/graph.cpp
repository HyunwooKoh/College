// graph.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
// 템플리트의 사용으로 한 파일에 모든 클래스들을 포함하고 있음

#include "stdafx.h"
#include <iostream>
using namespace std;

class Graph;   //Forward Declaration

 //Declare nodes to represent graphs in a linked list
class ChainNode {       // One node class
friend class Graph; 
private:
   int data;       // Data field
   ChainNode *link;  // Link field
};

typedef ChainNode *ChainNodePointer ;

class Graph
{
public:
	Graph(int size) ;
	void InsertEdge(int v, int u);    // Expressed as adjacency list
    void PrintVertex();               // Output of adjacency list
    void DFS(const int v);            // Depth-first search
    void Components();                // Finding connection elements
private:
    ChainNodePointer *HeadNodes;   // Head node of one vertex in adjacency list
	int n ;                        // n: number of vertices
	bool *visited ;                // Indicate whether or not to visit
};

Graph::Graph(int size)
{ 
	HeadNodes = new ChainNodePointer[size]; // Create an array of n headnodes
	visited   = new bool[size];          // Create n visited fields
	n = size;
    for(int i=0; i<n; i++) {
	   HeadNodes[i] = 0 ;     // Initialization of the head node
       visited[i] = false;    // Initialization of visited field
	}
}

void Graph::InsertEdge(int u, int v) 
{
   // Insert node at the beginning of vertex u's linked list
   ChainNode *p = new ChainNode();
   p->data = v; 
   p->link = HeadNodes[u] ;
   HeadNodes[u] = p ;

   // Insert node at the beginning of vertex v's linked list
   p = new ChainNode();
   p->data = u ;
   p->link = HeadNodes[v] ;
   HeadNodes[v] = p ;
}

void Graph::PrintVertex()
{
   cout << "\n\n When expressed as a list  -----   ";

   for(int i=0; i<n; i++)
   {
       cout << "\n " << i << " Adjacent vertices: ";
       for(ChainNode *p = HeadNodes[i]; p; p=p->link)
           cout << p->data << "  ";
   }
}

void Graph::DFS(const int v)
{
   cout << v << "  ";
   visited[v] = true;
   for(ChainNode *p = HeadNodes[v]; p; p=p->link)
   {
       int w = p->data;
       if (!visited[w])
       {
           DFS(w);
       }
   }
}

void Graph::Components()
{
   cout << "\n\n Finding connection elements with DFS:";
   for(int i=0; i<n; i++)
       if(!visited[i]) {
		   cout << "\n One connecting element - ";
           DFS(i);      // One element found
	   }
}

int _tmain(int argc, _TCHAR* argv[])
{
   int n, e ;  // n: number of vertices, e: number of edges
   int k, u, v ;
   cout << " Enter the number of vertices and the number of edges: ";
   cin >> n >> e ;

   Graph g(n);
   
   for(int i=0; i<e; i++) {
	   k = i+1;
       cout << "Enter the "<< k << " edge (u, v)" ;
	   cin >> u >> v ;
       g.InsertEdge(u, v);
   }
   g.PrintVertex();  // Print the connected list of the input graph
   g.Components();   // Find connection elements of input graph
   cout << "\n\n";

   return 0;
}

