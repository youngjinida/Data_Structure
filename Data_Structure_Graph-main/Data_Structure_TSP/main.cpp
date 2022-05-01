#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "DepthFirstSearch_TSP.h"

#define NUM_NODES 12
#define NUM_EDGES 37

void main()
{
	Vertex v[NUM_NODES] =
	{
	Vertex("인천", 0), Vertex("서울", 1),
	Vertex("강릉", 2), Vertex("천안", 3),
	Vertex("청주", 4), Vertex("동해", 5),
	Vertex("대전", 6), Vertex("울진", 7),
	Vertex("광주", 8), Vertex("대구", 9),
	Vertex("울산", 10), Vertex("부산", 11)
	};

	Edge edges[NUM_EDGES] =
	{
	Edge(v[0], v[1], 7), Edge(v[1], v[0], 3),
	Edge(v[1], v[2], 5), Edge(v[2], v[1], 3),
	Edge(v[0], v[3], 1), Edge(v[3], v[0], 3),
	Edge(v[1], v[4], 8), Edge(v[4], v[1], 13),
	Edge(v[4], v[3], 3), Edge(v[3], v[4], 4),
	Edge(v[2], v[5], 3), Edge(v[5], v[2], 5),
	Edge(v[5], v[4], 2), Edge(v[4], v[5], 1),
	Edge(v[3], v[6], 4), Edge(v[6], v[3], 5),
	Edge(v[4], v[7], 2), Edge(v[7], v[4], 2),
	Edge(v[6], v[7], 5), Edge(v[7], v[6], 5),
	Edge(v[6], v[9], 3), Edge(v[6], v[8], 3),
	Edge(v[7], v[9], 3), Edge(v[7], v[10], 3),
	Edge(v[7], v[5], 3), Edge(v[5], v[7], 5),
	Edge(v[9], v[4], 6),
	Edge(v[9], v[6], 6), Edge(v[9], v[10], 2),
	Edge(v[9], v[11], 1), Edge(v[8], v[6], 3),
	Edge(v[8], v[9], 6), Edge(v[8], v[11], 5),
	Edge(v[10], v[7], 1), Edge(v[10], v[11], 2),
	Edge(v[11], v[8], 4), Edge(v[11], v[10], 3)
	};
	Graph simpleGraph("GRAPH_SQUARE_16_NODES", NUM_NODES);
	cout << "Inserting vertices .." << endl;
	for (int i = 0; i < NUM_NODES; i++) {
		simpleGraph.insertVertex(v[i]);
	}
	vrtxList vrtxLst;
	simpleGraph.vertices(vrtxLst);
	int count = 0;
	cout << "Inserted vertices: ";
	for (vItr vItor = vrtxLst.begin(); vItor != vrtxLst.end(); ++vItor) {
		cout << *vItor << " ";
	}
	cout << endl;
	cout << "Inserting edges .." << endl;
	for (int i = 0; i < NUM_EDGES; i++)
	{
		simpleGraph.insertEdge(edges[i]);
	}
	cout << "Inserted edges: " << endl;
	count = 0;
	edgeList egLst;
	simpleGraph.edges(egLst);
	for (eItr p = egLst.begin(); p != egLst.end(); ++p)
	{
		count++;
		cout << *p << ", ";
		if (count % 5 == 0)
			cout << endl;
	}
	cout << endl;
	cout << "Print out Graph based on Adjacency List .." << endl;
	simpleGraph.fprintGraph(cout);
	cout << "Testing dfsGraph..." << endl;
	DepthFirstSearch dfsGraph(simpleGraph);
	vrtxList path;
	vrtxList shortest_path;
	int min_cost= 0;
	dfsGraph.findPath(v[0], v[0], path, shortest_path, &min_cost);
	cout << "\nPath(" << v[0] << " = > " << v[0] << "): ";
	for (vItr vItor = shortest_path.begin(); vItor != shortest_path.end(); ++vItor)
		cout << *vItor << " ";
	cout << endl;
	cout << "TSP Min Cost is " << min_cost << "!!\n";
}