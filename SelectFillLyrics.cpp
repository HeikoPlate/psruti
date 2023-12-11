// SelectFillLyrics.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "SelectFillLyrics.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld SelectFillLyrics 


SelectFillLyrics::SelectFillLyrics(CWnd* pParent /*=NULL*/)
	: CDialog(SelectFillLyrics::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelectFillLyrics)
	//}}AFX_DATA_INIT
}


BOOL SelectFillLyrics::OnInitDialog() 
{
	CDialog::OnInitDialog();


	cuepointlyrctick = 0;

	m_select_linefeed.SetCheck(0);
	m_shift_linefeeds.EnableWindow(false);
	m_shift_linefeeds_at.EnableWindow(false);
	SetDlgItemInt(IDC_SHIFT_TICKS,240,FALSE);
	SetDlgItemInt(IDC_SHIFT_TICKS_AT,240,FALSE);
	shift_ticks = -1;
	shift_ticks_at = -1;
	m_shift_ticks.EnableWindow(false);
	m_shift_ticks_at.EnableWindow(false);

	m_select_cuepoint_lyrc.SetCheck(0);
	SetDlgItemInt(IDC_EDIT_LYRC_TICKS,100,FALSE);
	m_cuepoint_lyrc_ticks.EnableWindow(false);
	if (!hpmfi->lyric_cuepoint)
	{
		m_select_cuepoint_lyrc.EnableWindow(false);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void SelectFillLyrics::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelectFillLyrics)
	DDX_Control(pDX, IDC_SHIFT_LINEFEEDS_AT, m_shift_linefeeds_at);
	DDX_Control(pDX, IDC_SHIFT_TICKS_AT, m_shift_ticks_at);
	DDX_Control(pDX, IDC_SHIFT_TICKS, m_shift_ticks);
	DDX_Control(pDX, IDC_SHIFT_LINEFEEDS, m_shift_linefeeds);
	DDX_Control(pDX, IDC_EDIT_LYRC_TICKS, m_cuepoint_lyrc_ticks);
	DDX_Control(pDX, IDC_SELECT_CUEPOINT_LYRC, m_select_cuepoint_lyrc);
	DDX_Control(pDX, IDC_SELECT_LINEFEED_CHECK, m_select_linefeed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelectFillLyrics, CDialog) 
	//{{AFX_MSG_MAP(SelectFillLyrics)
	ON_BN_CLICKED(IDC_SELECT_LINEFEED_CHECK, OnSelectLinefeedCheck)
	ON_EN_CHANGE(IDC_SHIFT_TICKS, OnChangeShiftTicks)
	ON_BN_CLICKED(IDC_SHIFT_LINEFEEDS_AT, OnShiftLinefeedsAt)
	ON_EN_CHANGE(IDC_SHIFT_TICKS_AT, OnChangeShiftTicksAt)
	ON_BN_CLICKED(IDC_SELECT_CUEPOINT_LYRC, OnSelectCuepointLyrc)
	ON_EN_CHANGE(IDC_EDIT_LYRC_TICKS, OnChangeEditLyrcTicks)
	ON_BN_CLICKED(IDC_SHIFT_LINEFEEDS, OnShiftLinefeeds)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten SelectFillLyrics 

void SelectFillLyrics::OnOK() 
{
	is_linefeed = (m_select_linefeed.GetCheck()==1);
	is_cuepoint_lyrc = (m_select_cuepoint_lyrc.GetCheck()==1);
	CDialog::OnOK();
}

bool SelectFillLyrics::linefeed_selected()
{
	return is_linefeed;
}

bool SelectFillLyrics::cuepoint_lyrc_selected()
{
	return is_cuepoint_lyrc;
}


int SelectFillLyrics::get_cuepoint_lyrc_tick()
{
	return cuepointlyrctick;
}

int SelectFillLyrics::get_shift_ticks()
{
	return shift_ticks;
}

int SelectFillLyrics::get_shift_ticks_at()
{
	return shift_ticks_at;
}

void SelectFillLyrics::OnSelectLinefeedCheck() 
{
	bool is = (m_select_linefeed.GetCheck() == 1);	
	
	if (is)
	{	// right side: only change linefeed for one file
		m_shift_linefeeds.EnableWindow(true);
		m_shift_linefeeds_at.EnableWindow(true);
		m_shift_linefeeds.SetCheck(0);
		m_shift_linefeeds_at.SetCheck(0);
		SetDlgItemInt(IDC_SHIFT_TICKS,240,FALSE);
		shift_ticks = -1;
		shift_ticks_at = -1;
		m_shift_ticks.EnableWindow(false);
		m_shift_ticks_at.EnableWindow(false);
		m_select_cuepoint_lyrc.SetCheck(0);
		m_cuepoint_lyrc_ticks.EnableWindow(false);
		SetDlgItemInt(IDC_EDIT_LYRC_TICKS,10,FALSE);
		cuepointlyrctick = 0;
	}
	else
	{	// left side: permanent define fill-lyrics, linefeed and linefeedtick
		m_shift_linefeeds.SetCheck(0);
		m_shift_linefeeds_at.SetCheck(0);
		m_shift_linefeeds.EnableWindow(false);
		m_shift_linefeeds_at.EnableWindow(false);
		SetDlgItemInt(IDC_SHIFT_TICKS,240,FALSE);
		shift_ticks = -1;
		shift_ticks_at = -1;
		m_shift_ticks.EnableWindow(false);
		m_shift_ticks_at.EnableWindow(false);

		m_select_cuepoint_lyrc.SetCheck(0);
		m_cuepoint_lyrc_ticks.EnableWindow(false);
		SetDlgItemInt(IDC_EDIT_LYRC_TICKS,10,FALSE);
		cuepointlyrctick = 0;
	}

}

void SelectFillLyrics::OnSelectCuepointLyrc() 
{
	bool is = (m_select_cuepoint_lyrc.GetCheck() == 1);	
	
	if (is)
	{
		m_cuepoint_lyrc_ticks.EnableWindow(true);
		SetDlgItemInt(IDC_EDIT_LYRC_TICKS,10,FALSE);
		cuepointlyrctick = 10;
		m_cuepoint_lyrc_ticks.SetFocus();
		m_cuepoint_lyrc_ticks.SetSel(0,-1);

		m_shift_linefeeds.SetCheck(0);
		m_shift_linefeeds_at.SetCheck(0);

		m_shift_linefeeds.EnableWindow(false);
		m_shift_linefeeds_at.EnableWindow(false);
		SetDlgItemInt(IDC_SHIFT_TICKS,240,FALSE);
		shift_ticks = -1;
		shift_ticks_at = -1;
		m_shift_ticks.EnableWindow(false);
		m_shift_ticks_at.EnableWindow(false);

		m_select_linefeed.SetCheck(0);
	}
	else
	{
		m_cuepoint_lyrc_ticks.EnableWindow(false);
		SetDlgItemInt(IDC_EDIT_LYRC_TICKS,10,FALSE);
		cuepointlyrctick = 0;
	}
}

void SelectFillLyrics::OnShiftLinefeeds() 
{	// right side
	bool is = (m_shift_linefeeds.GetCheck() == 1);
	if(is)
	{
		m_shift_linefeeds_at.SetCheck(0);
		m_shift_ticks_at.EnableWindow(false);
		SetDlgItemInt(IDC_SHIFT_TICKS,240,FALSE);
		SetDlgItemInt(IDC_SHIFT_TICKS_AT,240,FALSE);
		m_shift_ticks.EnableWindow(true);
		m_shift_ticks.SetFocus();
		m_shift_ticks.SetSel(0,-1);
		shift_ticks = 240;
		shift_ticks_at = -1;
	}
	else
	{
		SetDlgItemInt(IDC_SHIFT_TICKS,240,FALSE);
		m_shift_ticks.EnableWindow(false);
		shift_ticks = -1;
		shift_ticks_at = -1;
	}
}

void SelectFillLyrics::OnShiftLinefeedsAt() 
{
	bool is = (m_shift_linefeeds_at.GetCheck() == 1);
	if(is)
	{
		m_shift_ticks.EnableWindow(false);
		m_shift_linefeeds.SetCheck(0);
		SetDlgItemInt(IDC_SHIFT_TICKS_AT,240,FALSE);
		m_shift_ticks_at.EnableWindow(true);
		m_shift_ticks_at.SetFocus();
		m_shift_ticks_at.SetSel(0,-1);
		shift_ticks_at = 240;
		shift_ticks = -1;
	}
	else
	{
		SetDlgItemInt(IDC_SHIFT_TICKS,240,FALSE);
		m_shift_ticks.EnableWindow(false);
		m_shift_ticks_at.EnableWindow(false);
		shift_ticks = -1;
		shift_ticks_at = -1;
	}
}

void SelectFillLyrics::OnChangeEditLyrcTicks() 
{
	int no = GetDlgItemInt(IDC_EDIT_LYRC_TICKS);
	if ((no<0)||(no>479))
	{
		no = no<0?0:479;
		SetDlgItemInt(IDC_EDIT_LYRC_TICKS,no,FALSE);
	}
	cuepointlyrctick = no==0?-1:no;
}

void SelectFillLyrics::OnChangeShiftTicks() 
{
	int no = GetDlgItemInt(IDC_SHIFT_TICKS);
	if ((no<0)||(no>479))
	{
		no = no<0?0:479;
		SetDlgItemInt(IDC_SHIFT_TICKS,no,FALSE);
	}
	shift_ticks = no==0?-1:no;
}


void SelectFillLyrics::OnChangeShiftTicksAt() 
{
	int no = GetDlgItemInt(IDC_SHIFT_TICKS_AT);
	if ((no<0)||(no>479))
	{
		no = no<0?0:479;
		SetDlgItemInt(IDC_SHIFT_TICKS_AT,no,FALSE);
	}
	shift_ticks_at = no==0?-1:no;
}

