#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

#define PLUS_INF INT_MAX/2

enum VrtxStatus { UN_VISITED, VISITED, VRTX_NOT_FOUND };
enum EdgeStatus { DISCOVERY, BACK, CROSS, EDGE_UN_VISITED, EDGE_VISITED, EDGE_NOT_FOUND };

class Graph
{
	class Vertex;
	class Edge;
	typedef list<Graph::Vertex> vrtxList;
	typedef list<Graph::Edge> edgeList;
	typedef list<Graph::Vertex>::iterator vrtxItr;
	typedef list<Graph::Edge>::iterator edgeItr;

public:
	class Vertex
	{
		friend ostream& operator<<(ostream& fout, Vertex& v)
		{
			fout << v.getName();
			return fout;
		}
	public:
		Vertex()
			:_id(-1) {}
		Vertex(string name, int id)
			:_name(name), _id(id) {}
		Vertex(int id)
			:_id(id) {}
		int getID()const { return _id; }
		string getName()const { return _name; }
		VrtxStatus getVertexStatus()const { return _vrtxStatus; }
		void setID(int id) { _id = id; }
		void setName(string name) { _name = name; }
		void setVertexStatus(VrtxStatus vrtxStatus) { _vrtxStatus = vrtxStatus; }
		bool operator==(Vertex v) { return (this->getID() == v.getID()) && (this->getName() == v.getName()); }
		bool operator!=(Vertex v) { return (this->getID() != v.getID()) || (this->getName() != v.getName()); }
	private:
		string _name;
		int _id;
		VrtxStatus _vrtxStatus;
	};

	class Edge
	{
		friend ostream& operator<<(ostream& fout, Edge& e)
		{
			fout << "Edge(" << setw(2) << *e.getVertex_1() << ", " << setw(2)
				<< *e.getVertex_2() << ", " << setw(4) << e.getDist() << ")";
			return fout;
		}
	public:
		Edge() {}
		Edge(Vertex& Vrtx_1, Vertex& Vrtx_2, int distance)
			:_pVrtx_1(&Vrtx_1), _pVrtx_2(&Vrtx_2), _distance(distance), _edgeStatus(EDGE_UN_VISITED) {}
		Vertex* getVertex_1()const { return _pVrtx_1; }
		Vertex* getVertex_2()const { return _pVrtx_2; }
		int getDist()const { return _distance; }
		EdgeStatus getEdgeStatus()const { return _edgeStatus; }
		void setpVertex_1(Vertex* pVrtx_1) { _pVrtx_1 = pVrtx_1; }
		void setpVertex_2(Vertex* pVrtx_2) { _pVrtx_2 = pVrtx_2; }
		void setDist(int distance) { _distance = distance; }
		void setEdgeStatus(EdgeStatus es) { _edgeStatus = es; }
		void endVertices(vrtxList& vList)
		{
			vList.push_back(*(this->getVertex_1()));
			vList.push_back(*(this->getVertex_2()));
		}
		Vertex opposite(Vertex& v) const
		{
			if (v == *_pVrtx_1)
				return *_pVrtx_2;
			else if (v == *_pVrtx_2)
				return *_pVrtx_1;
			else
				return NULL;
		}
		bool operator==(Edge& e)const
		{
			return ((this->getVertex_1() == e.getVertex_1()) && (this->getVertex_2() == e.getVertex_2()));
		}
		bool operator!=(Edge& e)const
		{
			return ((this->getVertex_1() != e.getVertex_1()) || (this->getVertex_2() != e.getVertex_2()));
		}
	private:
		Vertex* _pVrtx_1;
		Vertex* _pVrtx_2;
		int _distance;
		EdgeStatus _edgeStatus;

	};
public:
	Graph()
		:_grph_name(""), _pVrtxArr(NULL), _pAdjListArray(NULL), _num_vertices(0) {}
	Graph(string grph_name, int num_vertices)
		:_grph_name(grph_name), _num_vertices(num_vertices)
	{
		_pVrtxArr = new Vertex[num_vertices];
		for (int i = 0; i < num_vertices; ++i)
			_pVrtxArr[i] = NULL;

		_pAdjListArray = new edgeList[num_vertices];
		for (int i = 0; i < num_vertices; ++i)
			_pAdjListArray[i].clear();
	}
	string getName()const { return _grph_name; }
	Vertex* getVrtxArr()const { return _pVrtxArr; }
	edgeList* getEdgeListArr()const { return _pAdjListArray; }
	int getnumVertices()const { return _num_vertices; }
	bool isValidVrtxID(int v_id);
	void vertices(vrtxList& vList);
	void edges(edgeList& eList);
	bool isAdjacentTo(Vertex& v, Vertex& w);
	void insertVertex(Vertex& v);
	void insertEdge(Edge& e);
	void eraseVertex(Vertex v);
	void eraseEdge(Edge e);
	void incidentEdges(Vertex& v, edgeList& edges);
	void fprintGraph(ostream& fout);
private:
	string _grph_name;
	Vertex* _pVrtxArr;
	edgeList* _pAdjListArray;
	int _num_vertices;
};


#endif // !GRAPH_H

