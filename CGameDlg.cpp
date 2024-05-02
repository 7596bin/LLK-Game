// CGameDlg.cpp: 实现文件
//
#include <afxcmn.h>
#include "pch.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include"global.h"
#include"resource.h"
#include <afxwin.h>



// CGameDlg 对话框

 IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_ptGameTop.x = MAP_LEFT;
	m_ptGameTop.y = MAP_TOP;

	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;

	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;

	m_bFirstPoint = true;
	m_bPlaying = false;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_REMIND, &CGameDlg::OnClickedBtnRemind)
	ON_BN_CLICKED(IDC_BTN_RESET, &CGameDlg::OnClickedBtnReset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCBTN_STOP, &CGameDlg::OnClickedIdcbtnStop)
	ON_BN_CLICKED(IDC_BTN_HEL, &CGameDlg::OnClickedBtnHel)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


void CGameDlg::InitBackground()
{
	CClientDC dc(this);
	HANDLE bmp = ::LoadImage(NULL, _T("theme/picture/fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE bmpPause = ::LoadImage(NULL, _T("res / IDB_STOP_BG.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(bmp);

	m_dcPause.CreateCompatibleDC(&dc);
	m_dcPause.SelectObject(bmpPause);

	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	UpdateWindow();
}

void CGameDlg::UpdateWindow()
{
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);

	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	CenterWindow();
}

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitBackground();
	InitElement();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}





void CGameDlg::InitElement()
{
	CClientDC dc(this);
	HANDLE bmp = ::LoadImage(NULL, _T("theme/picture/fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(bmp);

	HANDLE hMask = ::LoadImage(NULL, _T("theme/picture/fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hMask);
}



void CGameDlg::OnClickedBtnStart()
{
	m_gameControl.StartGame();

	m_bPlaying = true;
	this->GetDlgItem(IDC_BTN_START)->EnableWindow(false);

	initGameProgress();

	UpdateMap();

	InvalidateRect(m_rtGameRect, FALSE);
}


void CGameDlg::UpdateMap()
{
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);

	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			int nInfo = m_gameControl.GetElement(i, j);
			if (nInfo == BLANK)continue;
			
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nInfo * nElemH, SRCPAINT);     //将背景图片与掩码相或
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nInfo * nElemH, SRCAND);		//将上一步得到的相或图片与元素图片进行相与
		}
	}
	Invalidate(false);
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!m_bPlaying)
	{
		return;
	}
	
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y)
	{
		return ;
	}

	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;       //行号
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;		//列号

	if (nRow > MAX_ROW || nCol > MAX_COL)
	{
		return ;
	}
	if (m_bFirstPoint)
	{
		TRACE("First point: (%d, %d),%d\n", nRow, nCol,m_gameControl.GetElement(nRow,nCol));
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);
	}
	else
	{
		TRACE("Sec point: (%d, %d),%d\n", nRow, nCol, m_gameControl.GetElement(nRow, nCol));
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetSecondPoint(nRow, nCol);

		Vertex aPath[MAX_VERTEX_NUM];
		int VexNum;

		if (m_gameControl.Link(aPath,VexNum))
		{
			DrawTipLine(aPath,VexNum);
			JudgeWin();
			UpdateMap();
		}
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);

	}
	m_bFirstPoint = !m_bFirstPoint;
}

void CGameDlg::DrawTipFrame(int nRow,int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}




void CGameDlg::DrawTipLine(Vertex aPath[MAX_VERTEX_NUM], int VexNum)
{
	if (VexNum < 2) return; // 至少需要两个点来绘制线

	CClientDC dc(this);

	// 设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	// 将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	dc.MoveTo(m_ptGameTop.x + aPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + aPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);

	for (int i = 1; i < VexNum; i++) // 从第二个点开始
	{
		if (aPath[i].col == aPath[i - 1].col && aPath[i].row == aPath[i - 1].row)
			continue; // 如果当前点与上一个点重复，则跳过

		// 绘制连接线
		dc.LineTo(m_ptGameTop.x + aPath[i].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + aPath[i].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}

	dc.SelectObject(pOldPen); // 恢复旧的画笔
}

void CGameDlg::initGameProgress()
{

	//初始化进度条
	m_GameProgress.SetRange(0, 300);
	m_GameProgress.SetStep(-1);
	m_GameProgress.SetPos(300);

	this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
}


void CGameDlg::OnClickedBtnRemind()
{
	Vertex aPath[MAX_VERTEX_NUM];
	int VexNum;
	if (m_gameControl.Help(aPath, VexNum))
	{
		DrawTipFrame(aPath[0].row, aPath[0].col);
		DrawTipFrame(aPath[VexNum-1].row, aPath[VexNum-1].col);
		DrawTipLine(aPath, VexNum);
		UpdateMap();
	}
	Sleep(200);
	InvalidateRect(m_rtGameRect, FALSE);
}


void CGameDlg::OnClickedBtnReset()
{
	m_gameControl.ResetGp();
	UpdateMap();
	Sleep(200);
	InvalidateRect(m_rtGameRect, FALSE);
}

void CGameDlg::JudgeWin()
{
	bool bGameStatue = m_gameControl.IsWin(m_GameProgress.GetPos());

	if (bGameStatue == GAME_PLAY)
	{
		return;
	}
	else
	{
		m_bPlaying = false;
		KillTimer(PLAY_TIMER_ID);

		CString strTitle;
		this->GetWindowTextW(strTitle);
		if (bGameStatue == GAME_SUCCESS)
		{
			MessageBox(_T("获胜！"), strTitle);
		}
		else if (bGameStatue == GAME_LOSE)
		{
			MessageBox(_T("很遗憾,时间到了！"), strTitle);
		}
		this->GetDlgItem(IDC_BTN_START)->EnableWindow(true);
	}
}

void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying)
	{
		int nPos = m_GameProgress.GetPos();
		if (nPos > 0)
		{
			m_GameProgress.StepIt();
			DrawGameTime(); // 更新剩余时间显示
			UpdateMap();
			Sleep(200);
		}
		else
		{
			// 游戏时间到，处理游戏结束逻辑
			m_bPlaying = false;
			KillTimer(PLAY_TIMER_ID);
			MessageBox(_T("游戏时间到，游戏结束"));
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CGameDlg::DrawGameTime()
{
	// 获取进度条的矩形区域
	CRect progressRect;
	GetDlgItem(IDC_GAME_TIME)->GetClientRect(&progressRect);

	// 计算文本输出位置
	CRect textRect;
	textRect.left = progressRect.right + 80; 
	textRect.top = progressRect.top+520;
	textRect.right = textRect.left + 20; 
	textRect.bottom = progressRect.bottom+520;

	// 绘制剩余游戏时间
	CClientDC pDC(this);
	CFont timeFont;
	timeFont.CreatePointFont(200, _T("楷体"));
	CFont* oldFont = pDC.SelectObject(&timeFont);
	pDC.SetTextColor(RGB(255, 0, 0));
	pDC.SetBkMode(TRANSPARENT);
	// 创建白色画刷
	CBrush brush(BS_SOLID, RGB(255, 255, 255));

	// 清除原有文本
// 清除原有文本
	pDC.FillRect(textRect, &brush);
	CString cstr;
	cstr.Format(L"%d s", m_GameProgress.GetPos());
	pDC.TextOut(textRect.left, textRect.top, cstr);
	pDC.SelectObject(oldFont);
	brush.DeleteObject();
	// 使文本区域失效以强制重绘
	InvalidateRect(textRect, TRUE);
}







void CGameDlg::OnClickedIdcbtnStop()
{
	int curGameStatus = m_gameControl.changeGameStatus();
	if (curGameStatus == GAME_PLAY)
	{
		if (GAME_MODEL_BASE == m_gameControl.getGameModel())
			SetTimer(PLAY_TIMER_ID, 1000, NULL);
		UpdateMap();
		Invalidate(TRUE);
		GetDlgItem(IDCBTN_STOP)->SetWindowTextW(L"暂停游戏");
	}
	else if (curGameStatus == GAME_PAUSE)
	{
		if (GAME_MODEL_BASE == m_gameControl.getGameModel())
			KillTimer(PLAY_TIMER_ID);
		m_dcMem.BitBlt(0, 0, 800, 600, &m_dcPause, 0, 0, SRCCOPY);
		Invalidate(TRUE);
		GetDlgItem(IDCBTN_STOP)->SetWindowTextW(L"继续游戏");
	}
}


void CGameDlg::OnClickedBtnHel()
{
	CHelpDialog dlg;
	dlg.DoModal();
}
