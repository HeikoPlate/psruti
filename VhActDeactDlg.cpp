// VhActDeactDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "VhActDeactDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld VhActDeactDlg 


VhActDeactDlg::VhActDeactDlg(CWnd* pParent /*=NULL*/)
	: CDialog(VhActDeactDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(VhActDeactDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void VhActDeactDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VhActDeactDlg)
	DDX_Control(pDX, IDC_CHANNEL_LIST, m_channel_list);
	DDX_Control(pDX, IDC_SELECT, m_select);
	DDX_Control(pDX, IDC_DESELECT, m_deselect);
	DDX_Control(pDX, IDC_VH_DEACT_CHECK, m_vh_deact);
	DDX_Control(pDX, IDC_VH_ACT_CHECK, m_vh_act);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VhActDeactDlg, CDialog)
	//{{AFX_MSG_MAP(VhActDeactDlg)
	ON_BN_CLICKED(IDC_VH_ACT_CHECK, OnVhActCheck)
	ON_BN_CLICKED(IDC_VH_DEACT_CHECK, OnVhDeactCheck)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	ON_BN_CLICKED(IDC_DESELECT, OnDeselect)
	ON_LBN_SELCHANGE(IDC_CHANNEL_LIST, OnSelchangeChannelList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten VhActDeactDlg 

void VhActDeactDlg::OnSelect() 
{
	if (m_select.GetCheck()==0)
	{
		vh_select = false;
		m_deselect.EnableWindow(true);
	}
	else
	{
		vh_select = true;
		vh_deselect = false;
		m_deselect.SetCheck(0);
		m_deselect.EnableWindow(false);
	}
}

void VhActDeactDlg::OnDeselect() 
{
	if (m_deselect.GetCheck()==0)
	{
		vh_deselect = false;
		m_select.EnableWindow(true);
	}
	else
	{
		vh_deselect = true;
		vh_select = false;
		m_vh_act.SetCheck(0);
		m_vh_deact.SetCheck(0);

		m_select.SetCheck(0);
		m_select.EnableWindow(false);
		m_vh_act.EnableWindow(false);
		m_vh_deact.EnableWindow(false);
		
		// clear channel list
		int i;
		for (i=0; i<16; i++)
		{
			m_channel_list.InsertString(i,"");
		}
	}
}


void VhActDeactDlg::OnVhActCheck() 
{
	if (m_vh_act.GetCheck()==0)
	{
		vh_act = -1;
		m_vh_deact.EnableWindow(true);
	}
	else
	{
		vh_act = 1;
		vh_deact = -1;
		m_vh_deact.SetCheck(0);
		m_vh_deact.EnableWindow(false);
	}
}

void VhActDeactDlg::OnVhDeactCheck() 
{
	if (m_vh_deact.GetCheck()==0)
	{
		vh_deact = -1;
		m_vh_act.EnableWindow(true);

	}
	else
	{
		vh_deact = 1;
		vh_act = 0;
		m_vh_act.SetCheck(0);
		m_vh_act.EnableWindow(false);
	}
}

void VhActDeactDlg::OnCancel() 
{
	EndDialog(-1);
}

void VhActDeactDlg::OnOK() 
{
/*
	CString r;
	r.Format("vh_channel %i\nvh_select %i\nvh_deselect %i\nvh_act %i\nvh_deact %i",
				vh_channel, vh_select, vh_deselect, vh_act,  vh_deact);
	MessageBox(r);
	EndDialog(-1);
*/

	EndDialog(1);
}

BOOL VhActDeactDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_select.SetCheck(0);
	m_deselect.SetCheck(0);
	m_vh_act.SetCheck(0);
	m_vh_deact.SetCheck(0);
	vh_select = false;
	vh_deselect = false;
	vh_act = -1;
	vh_deact = -1;
	vh_channel = -1;

	int channel_index = -1;
	int chan;
	CString r;

	// Fill channel list
	for (chan=15; chan>=0; chan--)
	{
		channel_index++;
		r.Format("%2i",chan+1);
		m_channel_list.AddString(r);
		channel_index_list[channel_index] = chan;
	}

	m_channel_list.SetCurSel(0);
	vh_channel = channel_index_list[0];
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void VhActDeactDlg::OnSelchangeChannelList() 
{
	int nIndex = m_channel_list.GetCurSel();
	if (nIndex > 15)
	{
		nIndex = 0;
		m_channel_list.SetCurSel(nIndex);
	}

	vh_channel = channel_index_list[nIndex];
}
