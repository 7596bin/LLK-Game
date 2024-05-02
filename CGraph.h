#pragma once
#include"global.h"
typedef int Vertices[MAX_VERTEX_NUM];
typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
//图数据结构类
class CGraph
{
public:
	CGraph();
	~CGraph();
	void InitGraph();
	void ClearGraph();
	int AddVertex(int nInfo);
	void AddArc(int nIndex1, int nIndex2);
	int GetVertex(int nIndex);
	Vertex setVertex(int i);
	bool GetArc(int nIndex1, int nIndex2);
	void UpdateVertex(int nIndex, int nInfo);
	int GetVexnum();
	Vertices m_Vertices;		//顶点数组
protected:
	
	AdjMatrix m_AdjMatrix;		//关系矩阵
	int m_nVexnum;				//顶点数
	int m_nArcnum;				//边数
};

