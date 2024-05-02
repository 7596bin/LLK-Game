#pragma once
#include"global.h"
#include"CGameControl.h"
#include"CGameLogic.h"
#include"CGraph.h"
#include"CHelpDialog.h"

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	HICON m_hIcon;       //系统图标
	CDC m_dcMem;		//内存DC
	CDC m_dcElement;	//元素DC
	CDC m_dcMask;		//掩码DC
	CDC m_dcBG;		
	CDC m_dcPause;      //暂停画面

	CPoint m_ptGameTop;		//起始点坐标
	CSize m_sizeElem;		//图片元素大小
	bool m_bFirstPoint;		//是否是第一次选中图片
	CRect m_rtGameRect;  //游戏区域大小
	CGameControl m_gameControl;
	bool m_bPlaying;
	bool m_bPause;



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void DrawTipFrame(int nRow,int nCol);
	bool IsLink();
	void DrawTipLine(Vertex aPath[MAX_VERTEX_NUM],int VexNum);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

protected:
	void InitBackground();
	void InitElement();
	void UpdateWindow();
	void UpdateMap();
public:
	afx_msg void OnPaint();
	afx_msg void OnClickedBtnStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedBtnRemind();
	afx_msg void OnClickedBtnReset();
	CProgressCtrl m_GameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void initGameProgress();
	void DrawGameTime();
	void JudgeWin();
	afx_msg void OnClickedIdcbtnStop();
	afx_msg void OnClickedBtnHel();
};
