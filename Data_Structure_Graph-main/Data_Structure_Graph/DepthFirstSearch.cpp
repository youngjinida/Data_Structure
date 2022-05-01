#include <iostream>
#include <list>
#include <algorithm>
#include "Graph.h"
#include "DepthFirstSearch.h"

using namespace std;

DepthFirstSearch::DepthFirstSearch(Graph& g)
	:_graph(g)
{
	int num_nodes = _graph.getnumVertices();
	_pVrtxStatus = new VrtxStatus[num_nodes];
	_ppEdgeStatus = new EdgeStatus * [num_nodes];
	_ppConectivitiy = new int* [num_nodes];
	
	for (int i = 0; i < num_nodes; ++i)
	{
		_pVrtxStatus[i] = UN_VISITED;
		_ppEdgeStatus[i] = new EdgeStatus[num_nodes];
		_ppConectivitiy[i] = new int[num_nodes];
		for (int j = 0; j < num_nodes; ++j)
		{
			_ppEdgeStatus[i][j] = EDGE_UN_VISITED;
			_ppConectivitiy[i][j] = PLUS_INF;
		}
	}

	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	edgeList eList;
	
	_graph.edges(eList);
	for (eItr pe = eList.begin(); pe != eList.end(); ++pe)
	{
		vrtx_1 = *((*pe).getVertex_1());
		vID_1 = vrtx_1.getID();
		vrtx_2 = *((*pe).getVertex_2());
		vID_2 = vrtx_2.getID();
		_ppConectivitiy[vID_1][vID_2] = (*pe).getDist();
	}

	for (int i = 0; i < num_nodes; ++i)
		_ppConectivitiy[i][i] = 0;
}

void DepthFirstSearch::initialize()
{
	int num_nodes = _graph.getnumVertices();

	vrtxList verts;
	_graph.vertices(verts);
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;

	this->_done = false;

	for (int i = 0; i < num_nodes; ++i)
		_pVrtxStatus[i] = UN_VISITED;
	for (int i = 0; i < num_nodes; ++i)
		for (int j = 0; j < num_nodes; ++j)
			_ppEdgeStatus[i][j] = EDGE_UN_VISITED;
}

void DepthFirstSearch::showConectivity(ostream& fout)
{
	int num_nodes = _graph.getnumVertices();
	int dist;
	Graph g = getGraph();
	Vertex* pVrtxArr = g.getVrtxArr();

	fout << "Connectivity of graph: \n";
	fout << "   |";
	
	for (int i = 0; i < num_nodes; ++i)
		fout << setw(5) << pVrtxArr[i].getName();
	fout << "\n";
	
	fout << "-----+";
	for (int i = 0; i < num_nodes; ++i)
		fout << "-----";
	fout << "\n";

	for (int i = 0; i < num_nodes; ++i)
	{
		fout << "  " << pVrtxArr[i].getName() << "|";
		for (int j = 0; j < num_nodes; ++j)
		{
			dist = _ppConectivitiy[i][j];
			if (dist == PLUS_INF)
				fout << " +oo";
			else
				fout << setw(5) << dist;
		}
		fout << "\n";
	}
}

void DepthFirstSearch::visit(Vertex& v)
{
	int vID = v.getID();
	if (_graph.isValidVrtxID(vID))
		_pVrtxStatus[vID] = VISITED;
}

void DepthFirstSearch::visit(Edge& e)
{
	int vID_1 = (*e.getVertex_1()).getID();
	int vID_2 = (*e.getVertex_2()).getID();
	if (_graph.isValidVrtxID(vID_1) && _graph.isValidVrtxID(vID_2))
		_ppEdgeStatus[vID_1][vID_2] = EDGE_VISITED;
}

void DepthFirstSearch::unvisit(Vertex& v)
{
	int vID = v.getID();
	if (_graph.isValidVrtxID(vID))
		_pVrtxStatus[vID] = UN_VISITED;
}

void DepthFirstSearch::unvisit(Edge& e)
{
	int vID_1 = (*e.getVertex_1()).getID();
	int vID_2 = (*e.getVertex_2()).getID();
	if (_graph.isValidVrtxID(vID_1) && _graph.isValidVrtxID(vID_2))
		_ppEdgeStatus[vID_1][vID_2] = EDGE_UN_VISITED;
}

bool DepthFirstSearch::isVisit(Vertex& v)
{
	int vID = v.getID();
	if (_graph.isValidVrtxID(vID))
		return (_pVrtxStatus[vID] == VISITED);
	else
		return false;
}

bool DepthFirstSearch::isVisit(Edge& e)
{
	int vID_1 = (*e.getVertex_1()).getID();
	int vID_2 = (*e.getVertex_2()).getID();
	if (_graph.isValidVrtxID(vID_1) && _graph.isValidVrtxID(vID_2))
	{
		EdgeStatus es = _ppEdgeStatus[vID_1][vID_2];
		if (es == EDGE_VISITED || es == DISCOVERY || es == BACK)
			return true;
		else
			return false;
	}
	else
		return false;

}
void DepthFirstSearch::setStatus(Edge& e, EdgeStatus es)
{
	int vID_1 = (*e.getVertex_1()).getID();
	int vID_2 = (*e.getVertex_2()).getID();
	if (_graph.isValidVrtxID(vID_1) && _graph.isValidVrtxID(vID_2))
	{
		_ppEdgeStatus[vID_1][vID_2] = es;
	}
}

EdgeStatus DepthFirstSearch::getEdgeStatus(Edge& e)
{
	int vID_1 = (*e.getVertex_1()).getID();
	int vID_2 = (*e.getVertex_2()).getID();
	if (_graph.isValidVrtxID(vID_1) && _graph.isValidVrtxID(vID_2))
	{
		return _ppEdgeStatus[vID_1][vID_2];
	}
	else
		return EDGE_NOT_FOUND;
}

void DepthFirstSearch::findPath(Vertex& s, Vertex& t, vrtxList& path)
{
	initialize();
	path.clear();
	path.push_back(s);
	dfsTraversal(s, t, path);
}

void DepthFirstSearch::dfsTraversal(Vertex& v, Vertex& target, vrtxList& path)
{
	visit(v);
	if (v == target)
	{
		_done = true;
		return;
	}

	edgeList incidentEdges;
	incidentEdges.clear();
	_graph.incidentEdges(v, incidentEdges);
	eItr pe = incidentEdges.begin();
	while (!isDone() && pe != incidentEdges.end())
	{
		Edge e = *pe;
		pe++;
		
		EdgeStatus es = getEdgeStatus(e);
		if (es == EDGE_UN_VISITED)
		{
			visit(e);
			Vertex w = e.opposite(v);
			if (!isVisit(w))
			{
				path.push_back(w);
				setStatus(e, DISCOVERY);
				if (!isDone())
				{
					dfsTraversal(w, target, path);
					if (!isDone())
					{
						Vertex last_pushed = path.back();
						path.pop_back();
					}
				}
			}
			else
			{
				setStatus(e, BACK);
			}
		}
	}

}