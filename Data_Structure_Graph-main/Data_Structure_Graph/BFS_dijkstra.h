#ifndef BFS_DIJKSTRA_H
#define BFS_DIJKSTRA_H

#include "Graph.h"
#include <iostream>
using namespace std;

typedef Graph::Vertex Vertex;
typedef Graph::Edge Edge;
typedef list<Vertex> vrtxList;
typedef list<Edge> edgeList;
typedef list<Vertex>::iterator vrtxItor;
typedef list<Edge>::iterator edgeItor;
enum BFS_PROCESS_STATUS { NOT_SELECTED, SELECTED };

class BreadthFirstSearch
{
public:
	BreadthFirstSearch(Graph& g)
		:_graph(g)
	{
		int num_nodes = _graph.getnumVertices();
		_ppDistMtrx = new int* [num_nodes];
		for (int i = 0; i < num_nodes; ++i)
			_ppDistMtrx[i] = new int[num_nodes];

		for (int i = 0; i < num_nodes; ++i)
			for (int j = 0; j < num_nodes; ++j)
				_ppDistMtrx[i][j] = PLUS_INF;
	}
	void initDistMtrx();
	void fprintDistMtrx(ostream& fout);
	void DijkstraShortestPathTree(ostream& fout, Vertex& s, int* pPrev);
	void DijkstraShortestPath(ostream& fout, Vertex& s, Vertex& t, vrtxList& path);
	Graph& getGraph()const { return _graph; }
	int** getppDistMtrx()const { return _ppDistMtrx; }

protected:
	void initialize();
	bool isValidID(int vID) { return _graph.isValidVrtxID(vID); }
	int getNumVertices() { return _graph.getnumVertices(); }
private:
	Graph& _graph;
	bool _done;
	int** _ppDistMtrx;
};

#endif