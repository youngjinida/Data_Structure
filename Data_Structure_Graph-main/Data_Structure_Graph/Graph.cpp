#include "Graph.h"


void Graph::insertVertex(Vertex& v)
{
	int vID;
	vID = v.getID();
	if (_pVrtxArr[vID] == NULL)
	{
		_pVrtxArr[vID] = v;
	}
}
void Graph::vertices(vrtxList& vList)
{
	vList.clear();
	for (int i = 0; i < getnumVertices(); ++i)
		vList.push_back(_pVrtxArr[i]);
}

void Graph::insertEdge(Edge& e)
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	Vertex* pVrtx;
	

	vrtx_1 = *e.getVertex_1();
	vrtx_2 = *e.getVertex_2();
	vID_1 = vrtx_1.getID();
	vID_2 = vrtx_2.getID();

	if (_pVrtxArr[vID_1] == NULL)
	{
		_pVrtxArr[vID_1] = vrtx_1;
	}

	if (_pVrtxArr[vID_2] == NULL)
	{
		_pVrtxArr[vID_2] = vrtx_2;
	}

	e.setpVertex_1(&_pVrtxArr[vID_1]);
	e.setpVertex_2(&_pVrtxArr[vID_2]);

	_pAdjListArray[vID_1].push_back(e);
}

void Graph::edges(edgeList& eList)
{
	edgeItr eItr;
	Edge e;
	eList.clear();
	for (int i = 0; i < getnumVertices(); ++i)
	{
		eItr = _pAdjListArray[i].begin();
		while (eItr != _pAdjListArray[i].end())
		{
			e = *eItr;
			eList.push_back(e);
			eItr++;
		}
	}
}

bool Graph::isValidVrtxID(int v_id)
{
	return ((v_id >= 0) && (v_id < _num_vertices));
}

void Graph::incidentEdges(Vertex& v, edgeList& edges)
{
	Edge e;
	edgeItr eItr;
	int vID = v.getID();
	eItr = _pAdjListArray[vID].begin();
	while (eItr != _pAdjListArray[vID].end())
	{
		e = *eItr;
		edges.push_back(e);
		eItr++;
	}
}

bool Graph::isAdjacentTo(Vertex& v, Vertex& w)
{
	return false;
}



void Graph::eraseVertex(Vertex v)
{

}

void Graph::eraseEdge(Edge e)
{

}


void Graph::fprintGraph(ostream& fout)
{
	int i, j;
	edgeItr eItr;
	Edge e;
	int numOutGoingEdges;
	fout << this->getName() << " with" << this->getnumVertices()
		<< " vertices has following connectivity : \n";
	for (i = 0; i < getnumVertices(); ++i)
	{
		fout << " vertex (" << setw(3) << _pVrtxArr[i].getName() << ") : ";
		numOutGoingEdges = _pAdjListArray[i].size();

		eItr = _pAdjListArray[i].begin();
		while (eItr != _pAdjListArray[i].end())
		{
			e = *eItr;
			fout << e << " ";
			eItr++;
		}
		fout << "\n";
	}
}