#include "BFS_dijkstra.h"
#include "Graph.h"
#include <iomanip>
#include <list>
using namespace std;

void BreadthFirstSearch::initialize()
{
	Vertex* pVrtx = getGraph().getVrtxArr();
	vrtxList vList;
	_graph.vertices(vList);
	int num_vertex = getNumVertices();
	for (int i = 0; i < num_vertex; ++i)
		pVrtx[i].setVertexStatus(UN_VISITED);

	edgeList eList;
	_graph.edges(eList);
	for (edgeItor pe = eList.begin(); pe != eList.end(); ++pe)
		pe->setEdgeStatus(EDGE_UN_VISITED);
}

void BreadthFirstSearch::initDistMtrx()
{
	int** ppDistMtrx;
	int num_nodes;
	Vertex* pVrtxArr;
	edgeList* pAdjListArr;
	int cur_vID, vID;

	num_nodes = getNumVertices();
	pVrtxArr = _graph.getVrtxArr();
	pAdjListArr = _graph.getEdgeListArr();

	ppDistMtrx = getppDistMtrx();
	for (int i = 0; i < num_nodes; ++i)
	{
		cur_vID = pVrtxArr[i].getID();
		edgeItor pe = pAdjListArr[cur_vID].begin();
		while (pe != pAdjListArr[cur_vID].end())
		{
			vID = (*(*pe).getVertex_2()).getID();
			ppDistMtrx[cur_vID][vID] = (*pe).getDist();
			pe++;
		}
		ppDistMtrx[cur_vID][cur_vID] = 0;
	}

}

void BreadthFirstSearch::fprintDistMtrx(ostream& fout)
{
	int** ppDistMtrx;
	Vertex* pVrtxArr;
	int num_nodes, dist, vID;
	string vName;
	pVrtxArr = _graph.getVrtxArr();
	num_nodes = getNumVertices();
	ppDistMtrx = getppDistMtrx();

	fout << "\nDistance Matrix of Graph (" << _graph.getName() << "): \n";
	fout << "      |";
	for (int i = 0; i < num_nodes; ++i)
	{
		vName = pVrtxArr[i].getName();
		fout << setw(5) << vName;
	}
	fout << "\n";

	fout << "------+";
	for (int i = 0; i < num_nodes; ++i)
		fout << "-----";

	fout << "\n";
	for (int i = 0; i < num_nodes; ++i)
	{
		vName = pVrtxArr[i].getName();
		fout << setw(5) << vName << " |";
		for (int j = 0; j < num_nodes; ++j)
		{
			dist = ppDistMtrx[i][j];
			if (dist == PLUS_INF)
				fout << setw(5) <<" +oo";
			else
				fout << setw(5) << dist;
		}
		fout << "\n";
	}
	fout << "\n";
}

void BreadthFirstSearch::DijkstraShortestPathTree(ostream& fout, Vertex& s, int* pPrev)
{

}

void BreadthFirstSearch::DijkstraShortestPath(ostream& fout, Vertex& s, Vertex& t, vrtxList& path)
{
	int** ppDistMtrx;
	int* pLeastCost;
	int num_nodes, num_selected, minID, minCost;
	BFS_PROCESS_STATUS* pBFS_Process_status;
	int* pPrev;

	Vertex* pVrtxArr, *pPrevVrtx;
	Vertex vrtx, v;
	Edge e;
	int start_vID, target_vID, cur_vID, vID;
	edgeList* pAdjListArr;

	pVrtxArr = _graph.getVrtxArr();
	pAdjListArr = _graph.getEdgeListArr();
	start_vID = s.getID();
	target_vID = t.getID();
	num_nodes = getNumVertices();
	ppDistMtrx = getppDistMtrx();

	pLeastCost = new int[num_nodes];
	pPrev = new int[num_nodes];
	pBFS_Process_status = new BFS_PROCESS_STATUS[num_nodes];
	
	for (int i = 0; i < num_nodes; ++i)
	{
		pLeastCost[i] = _ppDistMtrx[start_vID][i];
		pPrev[i] = start_vID;
		pBFS_Process_status[i] = NOT_SELECTED;
	}
	
	pBFS_Process_status[start_vID] = SELECTED;
	num_selected = 1;
	path.clear();

	int cost, round = 0;
	string vName;

	fout << "Dijkstra::Least Cost from Vertex (" << s.getName() << ") at each round: \n";
	
	fout << "           |";
	for (int i = 0; i < num_nodes; ++i)
	{
		vName = pVrtxArr[i].getName();
		fout << setw(5) << vName;
	}
	fout << "\n";

	fout << "-----------+";
	for (int i = 0; i < num_nodes; ++i)
		fout << "-----";

	fout << "\n";
	while (num_selected < num_nodes)
	{
		round++;
		fout << "round [" << setw(2) << round << "] |";
		minID = -1;
		minCost = PLUS_INF;
		for (int i = 0; i < num_nodes; ++i)
		{
			if ((pLeastCost[i] < minCost) && (pBFS_Process_status[i] != SELECTED))
			{
				minID = i;
				minCost = pLeastCost[i];
			}
		}

		if (minID == -1)
		{
			fout << "Error\n";
			break;
		}
		else
		{
			pBFS_Process_status[minID] = SELECTED;
			++num_selected;
			if (minID == target_vID)
			{
				fout << "\nreached to the target node (" << pVrtxArr[minID].getName()
					<< ") at Least Cost = " << minCost << "\n";
				vID = minID;
				do 
				{
					vrtx = pVrtxArr[vID];
					path.push_front(vrtx);
					vID = pPrev[vID];
				} while (vID != start_vID);
				vrtx = pVrtxArr[vID];
				path.push_front(vrtx);
				break;
			}
			else
			{
				int pLS, ppDistMtrx_i;
				for (int i = 0; i < num_nodes; ++i)
				{
					pLS = pLeastCost[i];
					ppDistMtrx_i = ppDistMtrx[minID][i];
					if ((pBFS_Process_status[i] != SELECTED) &&
						(pLeastCost[i] > (pLeastCost[minID] + ppDistMtrx[minID][i])))
					{
						pPrev[i] = minID;
						pLeastCost[i] = pLeastCost[minID] + ppDistMtrx[minID][i];
					}
				}
			}

			for (int i = 0; i < num_nodes; ++i)
			{
				cost = pLeastCost[i];
				if (cost == PLUS_INF)
					fout << setw(5) <<"+oo";
				else
					fout << setw(5) << pLeastCost[i];
			}
			fout << " ==> selected vertex: " << pVrtxArr[minID] << "\n";

		}
	}
}