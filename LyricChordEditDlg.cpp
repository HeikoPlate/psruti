// LyricChordEditDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "LyricChordEditDlg.h"
#include "GlobalUtilities.h"
#include "HPMF_Interface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld LyricChordEditDlg 


LyricChordEditDlg::LyricChordEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(LyricChordEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(LyricChordEditDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	delete_event = false;
}


void LyricChordEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LyricChordEditDlg)
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_NEWPAGE, m_newpage);
	DDX_Control(pDX, IDC_LINEFEED, m_linefeed);
	DDX_Control(pDX, IDC_DELETE, m_delete);
	DDX_Control(pDX, IDC_CHORD_LYRIC_TEXT, m_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LyricChordEditDlg, CDialog)
	//{{AFX_MSG_MAP(LyricChordEditDlg)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_LINEFEED, OnLinefeed)
	ON_BN_CLICKED(IDC_NEWPAGE, OnNewpage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten LyricChordEditDlg 

void LyricChordEditDlg::OnOK() 
{
	CString mbt_str;

	GetDlgItemText(IDC_TAKT_BEAT_TICK,mbt_str);
	int m, b, t;
	if (GlobalUtilities::analyse_mbt(mbt_str,&m,&b,&t))
	{
		takt = m;
		beat = b;
		tick = t;
	}
	else
	{
		SetDlgItemText(IDC_TAKT_BEAT_TICK,"");
		return;
	}
	
	int time = hpmfi->get_time_from_takt_bar_tick(takt,beat,tick);
	if (time<0)
	{
		SetDlgItemText(IDC_TAKT_BEAT_TICK,"");
		return;
	}

	
	if (type==CHORD_TYPE)
	{
		GetDlgItemText(IDC_CHORD_LYRIC_TEXT,text);
	
		if (!GlobalUtilities::find_cr_ct_bn_bt(text, &cr, &ct, &bn, &bt))
		{
			SetDlgItemText(IDC_CHORD_LYRIC_TEXT,"");
			return;
		}
	}

	if ((type==LYRIC_TYPE)||(type==LINEFEED_TYPE))
	{
		GetDlgItemText(IDC_CHORD_LYRIC_TEXT,text);
/*
		int len = text.GetLength();
		if (len>1)
		{
			int i;
			for (i=0; i<len; i++)
			{
				if (text[i]=='<')
				{
					text.Delete(i,1);
				}
			}
		}
*/
	}


	EndDialog(0);
}

void LyricChordEditDlg::OnCancel() 
{
	delete_event = false;
	EndDialog(-1);
}

BOOL LyricChordEditDlg::OnInitDialog() 
{
	delete_event = false;
	CDialog::OnInitDialog();
	CString r;
	CString local_text;
	
	if (type==CHORD_TYPE)
	{
		SetDlgItemText(IDC_ACT_TYPE,GlobalUtilities::get_resource_string(IDS_CHORD)+':');
		m_linefeed.ShowWindow(SW_HIDE);
		m_newpage.ShowWindow(SW_HIDE);
		SetWindowText(GlobalUtilities::get_resource_string(IDS_CHORD));
		if (text != "")
		{
			SetDlgItemText(IDC_CHORD_LYRIC_TEXT,text);
		}
	}

	if (type==LYRIC_TYPE) 
	{
		SetDlgItemText(IDC_ACT_TYPE,"Lyric:");
		m_linefeed.ShowWindow(SW_HIDE);
		m_newpage.ShowWindow(SW_HIDE);
		SetWindowText("Lyric");
		if (text != "")
		{
			SetDlgItemText(IDC_CHORD_LYRIC_TEXT,text);
		}
	}

	if (type==LINEFEED_TYPE)
	{
		m_text.EnableWindow(FALSE);
		m_linefeed.ShowWindow(SW_SHOW);

		m_newpage.ShowWindow(SW_SHOW);
		m_newpage.SetCheck(0);

		SetWindowText(
			GlobalUtilities::get_resource_string(IDS_LINEFEED)+'/'+GlobalUtilities::get_resource_string(IDS_NEWPAGE));

		m_delete.EnableWindow(FALSE);
		m_ok.EnableWindow(TRUE);

		if (text=="")
		{
			m_linefeed.SetCheck(1);
			OnLinefeed();
			m_delete.EnableWindow(FALSE);
			local_text = "/";
			SetDlgItemText(IDC_CHORD_LYRIC_TEXT,local_text);
		}

		if (text=="/")
		{
			SetDlgItemText(IDC_ACT_TYPE,GlobalUtilities::get_resource_string(IDS_LINEFEED)+':');
			m_linefeed.SetCheck(1);
			m_newpage.SetCheck(0);
			m_linefeed.EnableWindow(FALSE);
			m_newpage.EnableWindow(FALSE);
			local_text = "/";
			SetDlgItemText(IDC_CHORD_LYRIC_TEXT,local_text);
		}

		if (text=="<")
		{
			SetDlgItemText(IDC_ACT_TYPE,GlobalUtilities::get_resource_string(IDS_NEWPAGE)+':');
			m_linefeed.SetCheck(0);
			m_newpage.SetCheck(1);
			m_linefeed.EnableWindow(FALSE);
			m_newpage.EnableWindow(FALSE);
			local_text = "<";
			SetDlgItemText(IDC_CHORD_LYRIC_TEXT,local_text);
		}
	}

	if ((text=="/")||(text=="<"))
	{
		m_ok.EnableWindow(FALSE);
		m_delete.EnableWindow(TRUE);
	}
	else
	{
		if (text!="")
		{
			m_ok.EnableWindow(TRUE);
			m_delete.EnableWindow(TRUE);
		}
		else
		{
			m_ok.EnableWindow(TRUE);
			m_delete.EnableWindow(FALSE);
		}
	}

	r.Format("%3.3i:%2.2i:%3.3i",takt+1, beat+1, tick);
	SetDlgItemText(IDC_TAKT_BEAT_TICK,r);

	return TRUE;  
}

void LyricChordEditDlg::OnDelete() 
{
	delete_event = true;
	OnOK();
}

void LyricChordEditDlg::OnLinefeed() 
{
	CString local_text;
	if (text=="")
	{
		m_ok.EnableWindow(TRUE);
		m_delete.EnableWindow(FALSE);
		SetDlgItemText(IDC_CHORD_LYRIC_TEXT,text);
	}
	else
	{
		m_ok.EnableWindow(FALSE);
		m_delete.EnableWindow(TRUE);
		return;
	}

	int linefeed_check = m_linefeed.GetCheck();
	if (linefeed_check==0)
	{
		m_linefeed.SetCheck(0);
		m_newpage.SetCheck(1);
		local_text = "<";
		SetDlgItemText(IDC_CHORD_LYRIC_TEXT,local_text);
		SetDlgItemText(IDC_ACT_TYPE,GlobalUtilities::get_resource_string(IDS_NEWPAGE)+':');
	}
	else
	{
		m_linefeed.SetCheck(1);
		m_newpage.SetCheck(0);
		local_text = "/";
		SetDlgItemText(IDC_CHORD_LYRIC_TEXT,local_text);
		SetDlgItemText(IDC_ACT_TYPE,GlobalUtilities::get_resource_string(IDS_LINEFEED)+':');
	}
}

void LyricChordEditDlg::OnNewpage() 
{
	CString local_text;
	if (text=="")
	{
		m_ok.EnableWindow(TRUE);
		m_delete.EnableWindow(FALSE);
		SetDlgItemText(IDC_CHORD_LYRIC_TEXT,text);
	}
	else
	{
		m_ok.EnableWindow(FALSE);
		m_delete.EnableWindow(TRUE);
		return;
	}
	
	int newpage_check = m_newpage.GetCheck();
	if (newpage_check==0)
	{
		m_linefeed.SetCheck(1);
		m_newpage.SetCheck(0);
		local_text = "/";
		SetDlgItemText(IDC_CHORD_LYRIC_TEXT,local_text);
		SetDlgItemText(IDC_ACT_TYPE,GlobalUtilities::get_resource_string(IDS_LINEFEED)+':');	}
	else
	{
		m_linefeed.SetCheck(0);
		m_newpage.SetCheck(1);
		local_text = "<";
		SetDlgItemText(IDC_CHORD_LYRIC_TEXT,local_text);
		SetDlgItemText(IDC_ACT_TYPE,GlobalUtilities::get_resource_string(IDS_NEWPAGE)+':');
	}
}
