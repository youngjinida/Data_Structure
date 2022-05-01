#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "BFS_dijkstra.h"

#define NUM_NODES 7
#define NUM_EDGES 26

using namespace std;
void main()
{
	
	Vertex v[NUM_NODES] = // 7 nodes
	{
		Vertex("SF", 0), Vertex("LA", 1), Vertex("DLS", 2),
		Vertex("CHG", 3), Vertex("MIA", 4), Vertex("NY", 5),
		Vertex("BOS", 6)
	};
	Graph::Edge edges[NUM_EDGES] =
		// 70 edges
	{
	Edge(v[0], v[1], 337), Edge(v[1], v[0], 337),
	Edge(v[0], v[2], 1464), Edge(v[2], v[0], 1464),
	Edge(v[0], v[3], 1846), Edge(v[3], v[0], 1846),
	Edge(v[0], v[6], 2704), Edge(v[6], v[0], 2704),
	Edge(v[1], v[2], 1235), Edge(v[2], v[1], 1235),
	Edge(v[1], v[4], 2342), Edge(v[4], v[1], 2342),
	Edge(v[2], v[3], 802), Edge(v[3], v[2], 802),
	Edge(v[2], v[4], 1121), Edge(v[4], v[2], 1121),
	Edge(v[3], v[5], 740), Edge(v[5], v[3], 740),
	Edge(v[3], v[6], 867), Edge(v[6], v[3], 867),
	Edge(v[5], v[4], 1090), Edge(v[4], v[5], 1090),
	Edge(v[5], v[6], 187), Edge(v[6], v[5], 187),
	Edge(v[4], v[6], 1258), Edge(v[6], v[4], 1258),
	};

	int test_start = 1;
	int test_end = 6;
	Graph simpleGraph("GRAPH_SIMPLE_USA_7_NODES", NUM_NODES);

	cout << "Inserting vertices .." << "\n";
	for (int i = 0; i < NUM_NODES; i++) {
		simpleGraph.insertVertex(v[i]);
	}

	vrtxList vtxLst;
	simpleGraph.vertices(vtxLst);
	int count = 0;

	cout << "Inserted vertices: ";
	for (vrtxItor vItor = vtxLst.begin(); vItor != vtxLst.end(); ++vItor) {
		cout << *vItor << ", ";
	}
	cout << "\n";

	cout << "Inserting edges .." << "\n";
	for (int i = 0; i < NUM_EDGES; i++)
	{
		simpleGraph.insertEdge(edges[i]);
	}

	cout << "Inserted edges: " << "\n";
	count = 0;
	edgeList egLst;
	simpleGraph.edges(egLst);
	for (edgeItor p = egLst.begin(); p != egLst.end(); ++p)
	{
		count++;
		cout << *p << ", ";
		if (count % 5 == 0)
			cout << "\n";
	}

	cout << "\n";
	cout << "Print out Graph based on Adjacency List .." << "\n";
	simpleGraph.fprintGraph(cout);

	/* ==========================================*/
	BreadthFirstSearch bfsGraph(simpleGraph);
	cout << "\nTesting Breadth First Search with Dijkstra Algorithm" << "\n";
	bfsGraph.initDistMtrx(); 
	bfsGraph.fprintDistMtrx(cout);

	vrtxList path;
	path.clear();
	cout << "\nDijkstra Shortest Path Finding from " << v[test_start].getName() << " to "
		<< v[test_end].getName() << " .... " << "\n";
	bfsGraph.DijkstraShortestPath(cout, v[test_start], v[test_end], path);
	cout << "Path found by DijkstraShortestPath from " << v[test_start] << " to "
		<< v[test_end] << " : ";
	for (vrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
	{
		cout << *vItor << " ";
	}
	cout << "\n";

}