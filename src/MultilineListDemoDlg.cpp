// MultilineListDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MultilineListDemo.h"
#include "MultilineListDemoDlg.h"
#include ".\multilinelistdemodlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMultilineListDemoDlg dialog



CMultilineListDemoDlg::CMultilineListDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultilineListDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   m_initialized = FALSE;
}

void CMultilineListDemoDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_ITEMS, m_items);
}

BEGIN_MESSAGE_MAP(CMultilineListDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
   ON_WM_SIZE()
END_MESSAGE_MAP()


// CMultilineListDemoDlg message handlers

BOOL CMultilineListDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect wr;
   GetWindowRect(wr);
   CRect cr;
   m_items.GetWindowRect(cr);
   m_edgeDelta.cx = wr.right - cr.right;
   m_edgeDelta.cy = wr.bottom - cr.bottom;

   m_initialized = TRUE;

   PopulateItemList();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMultilineListDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMultilineListDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMultilineListDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMultilineListDemoDlg::OnSize(UINT nType, int cx, int cy)
{
   CDialog::OnSize(nType, cx, cy);

   if (!m_initialized)
      return;

   CRect wr;
   GetWindowRect(wr);
   CRect cr;
   m_items.GetWindowRect(cr);
   
   cr.right = wr.right - m_edgeDelta.cx;
   cr.bottom = wr.bottom - m_edgeDelta.cy;

   ScreenToClient(cr);
   m_items.MoveWindow(cr);
   m_items.Invalidate(FALSE);
}

#define RAND(min,max) \
   ((int)(((double)rand() / (double)RAND_MAX) * (double)((max)-(min))) + (int)min)

void CMultilineListDemoDlg::PopulateItemList()
{
   //
   // Example 1
   //

   const int numCols = 3;
   const int numRows = 20;

   m_items.SetSize(numCols,numRows);

   m_items.SetColHeading(0,_T("Name"));
   m_items.SetColHeading(1,_T("Quantity"));
   m_items.SetColHeading(2,_T("Description"));
   m_items.SetColWidth(2,280);

   srand((unsigned int)time(0));

   const int numwords = 14;
   char * words[numwords] =
   {
      _T("excellent"),
      _T("quality"),
      _T("product"),
      _T("efficient"),
      _T("cheap"),
      _T("powerful"),
      _T("synergy"),
      _T("power"),
      _T("blue"),
      _T("orange"),
      _T("the"),
      _T("and"),
      _T("or"),
      _T("a")
   };

   const int minwords = 1;
   const int maxwords = 20;

   for (int row = 0; row < numRows; row++)
   {
      CString s;
      s.Format(_T("widget_%d"), row+1);
      m_items.SetCellText(0,row,s);

      s.Format(_T("%d"), RAND(0,100));
      m_items.SetCellText(1,row,s);

      s = _T("");
      int nwords = RAND(minwords,maxwords);
      for (int word = 0; word < nwords; word++)
      {
         int wordNum = RAND(0,numwords-1);

         CString tmp(words[wordNum]);
         s += words[wordNum];
         s += _T(" ");
      }
      m_items.SetCellText(2,row,s);
   }

   /*
   //
   // Example 2
   //

   // create a list with 3 columns and 2 rows
   m_items.SetSize(3,5);

   // first two columns 100 pixels wide and the third column 200 pixels wide
   m_items.SetColWidth(0,100);
   m_items.SetColWidth(1,100);
   m_items.SetColWidth(2,200);

   // set the column heading text
   m_items.SetColHeading(0,_T("Name"));
   m_items.SetColHeading(1,_T("Quantity"));
   m_items.SetColHeading(2,_T("Description"));

   // populate the list data
   m_items.SetCellText(0,0,_T("Coffee Beans"));
   m_items.SetCellText(1,0,_T("12"));
   m_items.SetCellText(2,0,
   _T("An essential part of the daily diet for ensuring productivity is at required levels.\n\nNOTE: Decaf is for wimps!"));
   m_items.SetCellText(0,2,_T("Water"));
   m_items.SetCellText(1,2,_T("10"));
   m_items.SetCellText(2,2,_T("Listed as a dependency of the coffee beans module."));
   */
}


BOOL CMultilineListDemoDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
   if ((HIWORD(wParam) == LBN_SELCHANGE) &&
       (LOWORD(wParam) == IDC_ITEMS))
   {
      int selRow = m_items.GetSelRow();

      if (selRow < 0)
      {
         SetWindowText(_T("MultilineListDemo"));
      }
      else
      {
         CString s;
         s.Format(_T("MultilineListDemo (you have selected %s)"), m_items.GetCellText(0,selRow));
         SetWindowText(s);
      }
   }

   return CDialog::OnCommand(wParam, lParam);
}
