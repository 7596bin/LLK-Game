#pragma once
#include"global.h"
#include"CGraph.h"
class CGameControl
{
public:
	void StartGame();
	int GetElement(int row, int col);
	void SetFirstPoint(int row, int col);
	void SetSecondPoint(int row, int col);
	void ResetGp();
	bool Link(Vertex aPath[MAX_VERTEX_NUM],int &nVertexNum);
	bool IsWin(int t);
	bool Help(Vertex aPath[MAX_VERTEX_NUM], int& nVertexNum);
	int changeGameStatus();
	int getGameModel();

	int m_GameStatus;//��Ϸ״̬
	int m_GameModel;//��Ϸģʽ
private:
	CGraph m_graph;
	Vertex m_ptSelFirst;	//��һ��ѡ��ĵ�
	Vertex m_ptSelSec;	//�ڶ���ѡ��ĵ�
};

