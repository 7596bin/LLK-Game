#pragma once
#include"global.h"
#include"CGraph.h"
class CGameLogic
{
public:
	CGameLogic();
	void InitMap(CGraph &g);
	bool IsLink(CGraph &g, Vertex v1, Vertex v2);
	void Clear(CGraph &g, Vertex v1, Vertex v2);
	void ResetGraph(CGraph& g);
	void UpdateArc(CGraph& g, int nRow, int nCol);
	void PushVertex(Vertex v);
	void PopVertex();
	void PushInfo(int i);
	void PopInfo();
	bool IsExsit(CGraph &g,int i);
	bool IsCorner();
	bool IsBlank(CGraph& g);
	bool SearchPathindex(CGraph& g, int V0, int V1);
	bool SearchValidPath(CGraph& g);

	void AddVertex(Vertex v);
	void DeleteVertex();
	int GetVexPath(Vertex avPath[MAX_VERTEX_NUM]);
protected:
	Vertex m_avPath[MAX_VERTEX_NUM];     //链接路径(点)
	int m_infoPath[MAX_VERTEX_NUM];      //索引路径(索引号)
	int m_nVexNum;
	int m_nInfo;
	int m_nCornerNum;			//拐点数
};

