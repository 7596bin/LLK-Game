#include "pch.h"
#include "CGameControl.h"
#include"CGameLogic.h"
#include"global.h"

void CGameControl::StartGame()
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);
	m_GameStatus = GAME_PLAY;
	m_GameModel = GAME_MODEL_BASE;
}

int CGameControl::GetElement(int row, int col)
{
	return m_graph.GetVertex(row*MAX_COL+col);
}

void CGameControl::SetFirstPoint(int row, int col)
{
	m_ptSelFirst.row = row;
	m_ptSelFirst.col = col;
	m_ptSelFirst.info = GetElement(row, col);
}

void CGameControl::SetSecondPoint(int row, int col)
{
	m_ptSelSec.row = row;
	m_ptSelSec.col = col;
	m_ptSelSec.info = GetElement(row, col);
}
bool CGameControl::Link(Vertex aPath[MAX_VERTEX_NUM],int &nVertexNum)
{
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col)
	{
		return false;
	}

	if (m_ptSelFirst.info != m_ptSelSec.info)
	{
		return false;
	}

	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec))
	{
		
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);

		nVertexNum = gameLogic.GetVexPath(aPath);
		return true;
	}
	return false;
}

bool CGameControl::IsWin(int t)
{
	CGameLogic logic;
	if (t <= 0)
	{
		m_graph.ClearGraph();
		return GAME_LOSE;
	}

	if (logic.IsBlank(m_graph))
	{
		m_graph.ClearGraph();
		return GAME_SUCCESS;
	}

	return GAME_PLAY;
}

bool CGameControl::Help(Vertex aPath[MAX_VERTEX_NUM], int& nVertexNum)
{
	CGameLogic logic;
	if (!logic.IsBlank(m_graph))
	{
		logic.SearchValidPath(m_graph);
	}
	nVertexNum = logic.GetVexPath(aPath);
	return true;
}

void CGameControl::ResetGp()
{
	CGameLogic logic;
	logic.ResetGraph(m_graph);
}

int CGameControl::changeGameStatus()
{
	if (m_GameStatus == GAME_PLAY)
	{
		m_GameStatus = GAME_PAUSE;
		return m_GameStatus;
	}
	else
	{
		m_GameStatus = GAME_PLAY;
		return m_GameStatus;
	}
}

int CGameControl::getGameModel()
{
	return m_GameModel;
}