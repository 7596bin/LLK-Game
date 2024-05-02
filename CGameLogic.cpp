#include "pch.h"
#include "CGameLogic.h"
CGameLogic::CGameLogic()
{
	m_nVexNum = 0;
	m_nInfo = 0;
	m_nCornerNum = 0;
}
void CGameLogic::InitMap(CGraph& g)
{
	//随机地图
	int anTemp[MAX_VERTEX_NUM];
	//花色重复数目
	for (int i = 0; i < REPEAT_NUM; i++)
	{
		//花色数目
		for (int j = 0; j < MAX_PIC_NUM; j++)
		{
			anTemp[i * MAX_PIC_NUM + j] = i;
		}
	}

	//设置种子
	srand(time(0));
	for (int i = 0; i < 100; i++)
	{
		int index1 = rand() % MAX_VERTEX_NUM;
		int index2 = rand() % MAX_VERTEX_NUM;

		//交换两个数值
		int temp = anTemp[index1];
		anTemp[index1] = anTemp[index2];
		anTemp[index2] = temp;
	}

	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			g.AddVertex(anTemp[i * MAX_COL + j]);
			UpdateArc(g, i, j);
		}
	}
		
}

bool CGameLogic::IsLink(CGraph& g, Vertex v1, Vertex v2)
{
	int IndexV1 = v1.row * MAX_COL + v1.col;
	int IndexV2 = v2.row * MAX_COL + v2.col;
	PushVertex(v1);
	PushInfo(IndexV1);
	if (SearchPathindex(g,IndexV1,IndexV2))
	{
		PushVertex(v2);
		PushInfo(IndexV2);
		return true;
	}

	PopVertex();
	PopInfo();
	return false;
}


void CGameLogic::PushVertex(Vertex v)
{
	m_avPath[m_nVexNum++] = v;
}

void CGameLogic::PopVertex()
{
	m_nVexNum--;
}

void CGameLogic::PushInfo(int i)
{
	m_infoPath[m_nInfo++] = i;
	if (IsCorner())
	{
		m_nCornerNum++;
	}
}

void CGameLogic::PopInfo()
{
	if (IsCorner())
	{
		m_nCornerNum--;
	}
	m_nInfo--;
}


void CGameLogic::Clear(CGraph &g, Vertex v1, Vertex v2)
{
	int IndexV1 = v1.row * MAX_COL + v1.col;
	int IndexV2 = v2.row * MAX_COL + v2.col;

	g.UpdateVertex(IndexV1, BLANK);
	g.UpdateVertex(IndexV2, BLANK);

	UpdateArc(g, v1.row, v1.col);
	UpdateArc(g, v2.row, v2.col);
}

void CGameLogic::ResetGraph(CGraph& g)
{
	for (int i = 0; i < 100; i++)
	{
		int index1 = rand() % MAX_VERTEX_NUM;
		int index2 = rand() % MAX_VERTEX_NUM;

		//交换两个数值
		int temp = g.m_Vertices[index1];
		g.m_Vertices[index1] = g.m_Vertices[index2];
		g.m_Vertices[index2] = temp;
	}
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			UpdateArc(g, i, j);
		}
	}
}

void CGameLogic::UpdateArc(CGraph& g, int nRow, int nCol)
{
	int nIndex1 = nRow * MAX_COL + nCol;
	if (nCol > 0) //左边相邻
	{
		int nIndex2 = nIndex1 - 1;
		int nInfo1 = g.GetVertex(nIndex1);
		int nInfo2 = g.GetVertex(nIndex2);
		if (nInfo1==nInfo2||nInfo1==BLANK||nInfo2==BLANK)
		{
			g.AddArc(nIndex1,nIndex2);
		}
	}

	if (nCol < MAX_COL-1)  //右边相邻
	{
		int nIndex2 = nIndex1 + 1;
		int nInfo1 = g.GetVertex(nIndex1);
		int nInfo2 = g.GetVertex(nIndex2);
		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
		{
			g.AddArc(nIndex1, nIndex2);
		}
	}

	if (nRow > 0)  //上方相邻
	{
		int nIndex2 = nIndex1 - MAX_COL;
		int nInfo1 = g.GetVertex(nIndex1);
		int nInfo2 = g.GetVertex(nIndex2);
		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
		{
			g.AddArc(nIndex1, nIndex2);
		}
	}

	if (nRow < MAX_COL-1)  //下方相邻
	{
		int nIndex2 = nIndex1 + MAX_COL;
		int nInfo1 = g.GetVertex(nIndex1);
		int nInfo2 = g.GetVertex(nIndex2);
		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
		{
			g.AddArc(nIndex1, nIndex2);
		}
	}
}




void CGameLogic::AddVertex(Vertex v)
{
	m_avPath[m_nVexNum++] = v;
}

void CGameLogic::DeleteVertex()
{
	m_nVexNum--;
}

bool CGameLogic::IsExsit(CGraph &g,int index)
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_infoPath[i] == index)
			return true;
	}
	return false;
}

bool CGameLogic::IsCorner()
{
	if (m_nInfo >= 3)
	{
		if ((m_infoPath[m_nInfo - 1] + m_infoPath[m_nInfo - 3]) / 2 != m_infoPath[m_nInfo - 2])
		{
			return true;
		}
	}
	return false;
}

bool CGameLogic::IsBlank(CGraph& g)
{
	int n = g.GetVexnum();
	for (int i = 0; i < n; i++)
	{
		if (g.GetVertex(i) != BLANK)
		{
			return false;
		}
	}

	return true;
}

bool CGameLogic::SearchPathindex(CGraph& g, int V0, int V1)
{
	int nVexNum = g.GetVexnum();

	for (int Vi = 0; Vi < nVexNum; Vi++)
	{
		if (g.GetArc(V0, Vi) && !IsExsit(g,Vi))
		{
			PushVertex(g.setVertex(Vi));
			PushInfo(Vi);
			if (m_nCornerNum > 2)
			{
				PopVertex();
				PopInfo();
				continue;
			}

			if (Vi != V1)
			{
				if (g.GetVertex(Vi) != BLANK)
				{
					PopVertex();
					PopInfo();
					continue;
				}
				if (SearchPathindex(g, Vi, V1))
				{
					return true;
				}
			}
			else
			{
				return true;
			}

			PopVertex();
			PopInfo();
		}
	}
	return false;
}

bool CGameLogic::SearchValidPath(CGraph& g)
{
	int n = g.GetVexnum();
	for (int i = 0; i < n; i++)
	{
		if (g.GetVertex(i) != BLANK)
		{
			for (int j = 0; j < n; j++)
			{
				if (i != j)
				{
					if (g.GetVertex(j) == g.GetVertex(i))
					{
						PushInfo(i);
						PushVertex(g.setVertex(i));
						if (SearchPathindex(g, i, j))
						{
							PushInfo(j);
							PushVertex(g.setVertex(j));
							return true;
						}
						PopInfo();
						PopVertex();
					}
				}
			}
		}
	}
	return false;
}

int CGameLogic::GetVexPath(Vertex avPath[MAX_VERTEX_NUM])
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}