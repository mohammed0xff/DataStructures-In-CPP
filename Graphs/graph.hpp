#pragma once


#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

class vertex
{
public:

	vertex(string x)
		:val(x)
	{
	}
	string val;
};


class Graph
{
public:
	Graph(int size);
	~Graph();

	void addVertex(vertex* vertex);
	void addEdge(int from, int to);

	int vertixIndex(vertex* vertex);

	void depthFirstSearchHelper(vertex* vertex, vector<bool>& marks);
	void BreadthFirstSearchHelper(vertex* vertex, vector<bool>& marks);

	void depthFirstSearch(vertex* vertex);
	void BreadthFirstSearch(vertex* vertex);

private:
	vector<vertex*> vertices;
	vector<vector<bool>> edges;

	int noVertices;
	int maxVertices;
};


Graph::Graph(int size) {
	noVertices = 0;
	maxVertices = size;

	vertices.resize(size, nullptr);
	edges.resize(size, vector<bool>(size, 0));
}


Graph::~Graph() {
	for (int i = 0; i < noVertices; i++)
	{
		delete vertices[i];
	}
}


void Graph::addVertex(vertex* vertix) {
	vertices[noVertices] = vertix;
	for (int i = 0; i < maxVertices; i++)
	{
		edges[noVertices][i] = false;
		edges[i][noVertices] = false;
	}
	noVertices++;
}


void Graph::addEdge(int from, int to) {
	int row;
	int column;

	row = vertixIndex(vertices[from]);
	column = vertixIndex(vertices[to]);
	edges[row][column] = true;
}


int Graph::vertixIndex(vertex* vertix) {
	int i = 0;
	while (i < noVertices)
	{
		if (vertices[i] == vertix)
			return i;
		i++;
	}
	return -1;
}

void Graph::depthFirstSearchHelper(vertex* vertix, vector<bool>& marks) {
	int idx, ixd2;
	if (vertix == NULL) return;

	cout << vertix->val << " ";
	idx = vertixIndex(vertix);
	marks[idx] = true;

	for (int i = 0; i < noVertices; i++)
	{
		ixd2 = vertixIndex(vertices[i]);
		if (edges[idx][ixd2] != false)
		{
			if (marks[i] == false)
				depthFirstSearchHelper(vertices[i], marks);
		}
	}
}

void Graph::depthFirstSearch(vertex* vertix) {

	vector<bool> marks;
	marks.resize(vertices.size());

	depthFirstSearchHelper(vertix, marks);

	cout << endl;
}

void Graph::BreadthFirstSearchHelper(vertex* vertix, vector<bool>& marks) {
	int idx, idx2;
	queue <vertex*> que;
	idx = vertixIndex(vertix);
	marks[idx] = true;
	que.push(vertix);

	while (!que.empty())
	{
		vertex* node = que.front();
		que.pop();
		idx = vertixIndex(node);
		cout << node->val << " ";
		for (int i = 0; i < noVertices; i++)
		{
			idx2 = vertixIndex(vertices[i]);
			if (edges[idx][idx2] != false)
			{
				if (marks[i] == false)
				{
					marks[i] = true;
					que.push(vertices[i]);
				}
			}
		}
	}
}


void Graph::BreadthFirstSearch(vertex* vertix) {

	vector<bool> marks;
	marks.resize(vertices.size());

	BreadthFirstSearchHelper(vertix, marks);

	cout << endl;
}

