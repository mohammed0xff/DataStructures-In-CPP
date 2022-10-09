#include "graph.hpp"


int main()
{
	Graph matrix(10);

	vertex* A = new vertex("A");
	matrix.addVertex(A);

	vertex* B = new vertex("B");
	matrix.addVertex(B);
	
	vertex* C = new vertex("C");
	matrix.addVertex(C);
	
	vertex* D = new vertex("D");
	matrix.addVertex(D);
	/*
	
		A ------ B
		|       /|  
		|     /  |  
		|   /    |   
		| /      | 
		D ------ C

	*/
	matrix.addEdge(matrix.vertixIndex(A), matrix.vertixIndex(B));
	matrix.addEdge(matrix.vertixIndex(A), matrix.vertixIndex(D));
	matrix.addEdge(matrix.vertixIndex(B), matrix.vertixIndex(D));
	matrix.addEdge(matrix.vertixIndex(D), matrix.vertixIndex(C));
	matrix.addEdge(matrix.vertixIndex(B), matrix.vertixIndex(C));
	matrix.addEdge(matrix.vertixIndex(C), matrix.vertixIndex(B));


	// Depth first Search Traversal from A
	matrix.depthFirstSearch(A);

	// Breadth Search Traversal Graph Traversal from D
	matrix.BreadthFirstSearch(D);

	return 0;
}
