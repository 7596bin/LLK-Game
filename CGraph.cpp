#include "pch.h"
#include "CGraph.h"

CGraph::CGraph()
{
	InitGraph();
}

CGraph::~CGraph()
{
	;
}

int CGraph::AddVertex(int nInfo)
{
	if(m_nVexnum>=MAX_VERTEX_NUM)
	{
		return m_nVexnum;
	}
	m_Vertices[m_nVexnum++] = nInfo;
	return m_nVexnum;
}

void CGraph::AddArc(int nIndex1, int nIndex2)
{
	m_AdjMatrix[nIndex1][nIndex2] = true;
	m_AdjMatrix[nIndex2][nIndex1] = true;
}

int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

Vertex CGraph::setVertex(int i)
{
	Vertex v;
	v.row = i / MAX_COL;
	v.col = i % MAX_COL;
	v.info = GetVertex(i);
	return v;
}

bool CGraph::GetArc(int nIndex1, int nIndex2)
{
	return m_AdjMatrix[nIndex1][nIndex2];
}

void CGraph::UpdateVertex(int nIndex, int nInfo)
{
	m_Vertices[nIndex] = nInfo;
}

void CGraph::InitGraph()
{
	//初始化顶点
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		m_Vertices[i] = -1;
	}
	//初始化边
	for (int i = 0;i<MAX_VERTEX_NUM;i++)
	{
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			m_AdjMatrix[i][j] = false;
		}
	}

	m_nVexnum = 0;
	m_nArcnum = 0;
}

void CGraph::ClearGraph()
{
	InitGraph();
}

int CGraph::GetVexnum()
{
	return m_nVexnum;
}