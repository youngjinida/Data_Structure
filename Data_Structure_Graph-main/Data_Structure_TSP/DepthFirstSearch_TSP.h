#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include <iostream>
#include "Graph.h"

using namespace std;

typedef Graph::Vertex Vertex;
typedef Graph::Edge Edge;
typedef list<Graph::Vertex> vrtxList;
typedef list<Graph::Edge> edgeList;
typedef list<Graph::Vertex>::iterator vItr;
typedef list<Graph::Edge>::iterator eItr;

class DepthFirstSearch
{
public:
	//DepthFirstSearch() {}
	//~DepthFirstSearch() {}
	DepthFirstSearch(Graph& g);
	void findPath(Vertex& s, Vertex& t, vrtxList& path, vrtxList& shortest_path, int* cost);
	Graph& getGraph() { return _graph; }
	void showConectivity(ostream& fout);
protected:
	void initialize();
	void dfsTraversal_TSP(Vertex& v, Vertex& target, vrtxList& path, vrtxList& shortest_path, int* cost);
	int getMin()const { return min_cost; }
	virtual void traverseDiscovery(const Edge& e, const Vertex& from) {}
	virtual void traverseBack(const Edge& e, const Vertex& from) {}
	virtual void finishVisit(const Vertex& v) {}
	virtual bool isDone() const { return _done; }
	void visit(Vertex& v);
	void visit(Edge& e);
	void unvisit(Vertex& v);
	void unvisit(Edge& e);
	bool isVisit(Vertex& v);
	bool isVisit(Edge& e);
	void setStatus(Edge& e, EdgeStatus es);
	EdgeStatus getEdgeStatus(Edge& e);

protected:
	Graph& _graph;
	Vertex _start;
	bool _done;
	int find_node;
	int min_cost;
private:
	VrtxStatus* _pVrtxStatus;
	EdgeStatus** _ppEdgeStatus;
	int** _ppConectivitiy;
};

#endif