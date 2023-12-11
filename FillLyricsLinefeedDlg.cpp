// FillLyricsLinefeedDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "FillLyricsLinefeedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CFillLyricsLinefeedDlg 


CFillLyricsLinefeedDlg::CFillLyricsLinefeedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFillLyricsLinefeedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFillLyricsLinefeedDlg)
	m_takt_lyric = _T("");
	m_beat_lyric = _T("");
	m_end_lyric = _T("");
	//}}AFX_DATA_INIT
}


void CFillLyricsLinefeedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFillLyricsLinefeedDlg)
	DDX_Control(pDX, IDC_USER3_FILL_LYRICS, m_user3);
	DDX_Control(pDX, IDC_USER2_FILL_LYRICS, m_user2);
	DDX_Control(pDX, IDC_USER1_FILL_LYRICS, m_user1);
	DDX_Control(pDX, IDC_LFLYRIC_TICKS, m_lflyric_ticks);
	DDX_Control(pDX, IDC_LINEFEED_LYRIC_CHECK, m_lflyric_check);
	DDX_Text(pDX, IDC_TAKT_LYRIC, m_takt_lyric);
	DDX_Text(pDX, IDC_BEAT_LYRIC, m_beat_lyric);
	DDX_Text(pDX, IDC_END_LYRIC, m_end_lyric);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFillLyricsLinefeedDlg, CDialog)
	//{{AFX_MSG_MAP(CFillLyricsLinefeedDlg)
	ON_BN_CLICKED(IDC_LINEFEED_LYRIC_CHECK, OnLflyricCheck)
	ON_EN_CHANGE(IDC_LFLYRIC_TICKS, OnChangeLflyricTicks)
	ON_BN_CLICKED(IDC_DEFAULT_LYRICS, OnDefaultLyrics)
	ON_EN_CHANGE(IDC_TAKT_LYRIC, OnChangeTaktLyric)
	ON_EN_CHANGE(IDC_BEAT_LYRIC, OnChangeBeatLyric)
	ON_EN_CHANGE(IDC_END_LYRIC, OnChangeEndLyric)
	ON_BN_CLICKED(IDC_USER2_FILL_LYRICS, OnUser2FillLyrics)
	ON_BN_CLICKED(IDC_USER3_FILL_LYRICS, OnUser3FillLyrics)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	ON_BN_CLICKED(IDC_USER1_FILL_LYRICS, OnUser1FillLyrics)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CFillLyricsLinefeedDlg 

BOOL CFillLyricsLinefeedDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	actualize();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CFillLyricsLinefeedDlg::actualize()
{
	m_lflyric_ticks.EnableWindow(false);
	m_lflyric_check.SetCheck(0);

	switch (is_user)
	{
	case 1:
		{
			SetDlgItemText(IDC_TAKT_LYRIC,GlobalUtilities::convert_string_to_printable(user1_takt_lyric));	
			SetDlgItemText(IDC_BEAT_LYRIC,GlobalUtilities::convert_string_to_printable(user1_beat_lyric));	
			SetDlgItemText(IDC_END_LYRIC,GlobalUtilities::convert_string_to_printable(user1_end_lyric));
			m_lflyric_check.SetCheck(0);

			if (user1_linefeedlyrictick==-1)
			{
				SetDlgItemText(IDC_LFLYRIC_TICKS,"");
			}
			else
			{
				SetDlgItemInt(IDC_LFLYRIC_TICKS,user1_linefeedlyrictick,FALSE);
			}
			m_user1.SetCheck(1);
			m_user2.SetCheck(0);
			m_user3.SetCheck(0);
			break;
		}
	case 2:
		{
			SetDlgItemText(IDC_TAKT_LYRIC,GlobalUtilities::convert_string_to_printable(user2_takt_lyric));	
			SetDlgItemText(IDC_BEAT_LYRIC,GlobalUtilities::convert_string_to_printable(user2_beat_lyric));	
			SetDlgItemText(IDC_END_LYRIC,GlobalUtilities::convert_string_to_printable(user2_end_lyric));
			m_lflyric_check.SetCheck(0);

			if (user2_linefeedlyrictick==-1)
			{
				SetDlgItemText(IDC_LFLYRIC_TICKS,"");
			}
			else
			{
				SetDlgItemInt(IDC_LFLYRIC_TICKS,user2_linefeedlyrictick,FALSE);
			}
			m_user1.SetCheck(0);
			m_user2.SetCheck(1);
			m_user3.SetCheck(0);
			break;
		}
	case 3:
		{
			SetDlgItemText(IDC_TAKT_LYRIC,GlobalUtilities::convert_string_to_printable(user3_takt_lyric));	
			SetDlgItemText(IDC_BEAT_LYRIC,GlobalUtilities::convert_string_to_printable(user3_beat_lyric));	
			SetDlgItemText(IDC_END_LYRIC,GlobalUtilities::convert_string_to_printable(user3_end_lyric));
			m_lflyric_check.SetCheck(0);

			if (user3_linefeedlyrictick==-1)
			{
				SetDlgItemText(IDC_LFLYRIC_TICKS,"");
			}
			else
			{
				SetDlgItemInt(IDC_LFLYRIC_TICKS,user3_linefeedlyrictick,FALSE);
			}
			m_user1.SetCheck(0);
			m_user2.SetCheck(0);
			m_user3.SetCheck(1);
			break;
		}
	}
}

void CFillLyricsLinefeedDlg::set_user(int user)
{
	is_user = user;
}

void CFillLyricsLinefeedDlg::set_user1_fill_lyric_data(CString tl, CString bl, CString el, int lflt)
{
	user1_takt_lyric = tl;
	user1_beat_lyric = bl;
	user1_end_lyric = el;
	user1_linefeedlyrictick = lflt;
}

void CFillLyricsLinefeedDlg::set_user2_fill_lyric_data(CString tl, CString bl, CString el, int lflt)
{
	user2_takt_lyric = tl;
	user2_beat_lyric = bl;
	user2_end_lyric = el;
	user2_linefeedlyrictick = lflt;
}

void CFillLyricsLinefeedDlg::set_user3_fill_lyric_data(CString tl, CString bl, CString el, int lflt)
{
	user3_takt_lyric = tl;
	user3_beat_lyric = bl;
	user3_end_lyric = el;
	user3_linefeedlyrictick = lflt;
}


void CFillLyricsLinefeedDlg::OnLflyricCheck() 
{
	if (m_lflyric_check.GetCheck()==0)
	{
		m_lflyric_ticks.EnableWindow(false);
	}
	else
	{
		m_lflyric_ticks.EnableWindow(true);
		m_lflyric_ticks.SetFocus();
	}
}

void CFillLyricsLinefeedDlg::OnChangeLflyricTicks() 
{
	int no = GetDlgItemInt(IDC_LFLYRIC_TICKS);
	switch (is_user)
	{
	case 1:
		{
			if ((no<0)||(no>479))
			{
				SetDlgItemInt(IDC_LFLYRIC_TICKS,user1_linefeedlyrictick,FALSE);
				return;
			}
			else
			{
				user1_linefeedlyrictick = no;
			}
			break;
		}
	case 2:
		{
			if ((no<0)||(no>479))
			{
				SetDlgItemInt(IDC_LFLYRIC_TICKS,user2_linefeedlyrictick,FALSE);
				return;
			}
			else
			{
				user2_linefeedlyrictick = no;
			}
			break;
		}
	case 3:
		{
			if ((no<0)||(no>479))
			{
				SetDlgItemInt(IDC_LFLYRIC_TICKS,user3_linefeedlyrictick,FALSE);
				return;
			}
			else
			{
				user3_linefeedlyrictick = no;
			}
			break;
		}
	}
}

void CFillLyricsLinefeedDlg::OnDefaultLyrics() 
{
	SetDlgItemText(IDC_TAKT_LYRIC,GlobalUtilities::convert_string_to_printable(GlobalUtilities::init_takt_lyric));	
	SetDlgItemText(IDC_BEAT_LYRIC,GlobalUtilities::convert_string_to_printable(GlobalUtilities::init_beat_lyric));	
	SetDlgItemText(IDC_END_LYRIC,GlobalUtilities::convert_string_to_printable(GlobalUtilities::init_end_lyric));	
	SetDlgItemInt(IDC_LFLYRIC_TICKS,30,FALSE);
	switch (is_user)
	{
	case 1:
		{
			user1_takt_lyric = GlobalUtilities::init_takt_lyric;
			user1_beat_lyric = GlobalUtilities::init_beat_lyric;
			user1_end_lyric = GlobalUtilities::init_end_lyric;
			user1_linefeedlyrictick = 30;
			break;
		}
	case 2:
		{
			user2_takt_lyric = GlobalUtilities::init_takt_lyric;
			user2_beat_lyric = GlobalUtilities::init_beat_lyric;
			user2_end_lyric = GlobalUtilities::init_end_lyric;
			user2_linefeedlyrictick = 30;
			break;
		}
	case 3:
		{
			user3_takt_lyric = GlobalUtilities::init_takt_lyric;
			user3_beat_lyric = GlobalUtilities::init_beat_lyric;
			user3_end_lyric = GlobalUtilities::init_end_lyric;
			user3_linefeedlyrictick = 30;
			break;
		}
	}
	m_lflyric_check.SetCheck(0);
	m_lflyric_ticks.EnableWindow(false);
}

int CFillLyricsLinefeedDlg::get_user()
{
	return is_user;
}

CString CFillLyricsLinefeedDlg::get_user1_takt_lyric()
{
	return user1_takt_lyric;
}

CString CFillLyricsLinefeedDlg::get_user1_beat_lyric()
{
	return user1_beat_lyric;
}

CString CFillLyricsLinefeedDlg::get_user1_end_lyric()
{
	return user1_end_lyric;
}

CString CFillLyricsLinefeedDlg::get_user2_takt_lyric()
{
	return user2_takt_lyric;
}

CString CFillLyricsLinefeedDlg::get_user2_beat_lyric()
{
	return user2_beat_lyric;
}

CString CFillLyricsLinefeedDlg::get_user2_end_lyric()
{
	return user2_end_lyric;
}

CString CFillLyricsLinefeedDlg::get_user3_takt_lyric()
{
	return user3_takt_lyric;
}

CString CFillLyricsLinefeedDlg::get_user3_beat_lyric()
{
	return user3_beat_lyric;
}

CString CFillLyricsLinefeedDlg::get_user3_end_lyric()
{
	return user3_end_lyric;
}

int CFillLyricsLinefeedDlg::get_user1_linefeedlyrictick()
{
	if (user1_linefeedlyrictick==0)
	{
		user1_linefeedlyrictick=-1;
	}
	return user1_linefeedlyrictick;
}

int CFillLyricsLinefeedDlg::get_user2_linefeedlyrictick()
{
	if (user2_linefeedlyrictick==0)
	{
		user2_linefeedlyrictick=-1;
	}
	return user2_linefeedlyrictick;
}

int CFillLyricsLinefeedDlg::get_user3_linefeedlyrictick()
{
	if (user3_linefeedlyrictick==0)
	{
		user3_linefeedlyrictick=-1;
	}
	return user3_linefeedlyrictick;
}

void CFillLyricsLinefeedDlg::OnOK() 
{
	EndDialog(0);
}

void CFillLyricsLinefeedDlg::OnCancel() 
{
	EndDialog(-1);
}

void CFillLyricsLinefeedDlg::OnChangeTaktLyric() 
{
	CString lyric_text;
	int len_text;
	GetDlgItemText(IDC_TAKT_LYRIC,lyric_text);
	len_text = lyric_text.GetLength();
	lyric_text = lyric_text.Mid(1,len_text-2);

	switch (is_user)
	{
	case 1:
		{
			user1_takt_lyric = lyric_text;
			break;
		}
	case 2:
		{
			user2_takt_lyric = lyric_text;
			break;
		}
	case 3:
		{
			user3_takt_lyric = lyric_text;
			break;
		}
	}
}

void CFillLyricsLinefeedDlg::OnChangeBeatLyric() 
{
	CString lyric_text;
	int len_text;
	GetDlgItemText(IDC_BEAT_LYRIC,lyric_text);
	len_text = lyric_text.GetLength();
	lyric_text = lyric_text.Mid(1,len_text-2);
	switch (is_user)
	{
	case 1:
		{
			user1_beat_lyric = lyric_text;
			break;
		}
	case 2:
		{
			user2_beat_lyric = lyric_text;
			break;
		}
	case 3:
		{
			user3_beat_lyric = lyric_text;
			break;
		}
	}
}

void CFillLyricsLinefeedDlg::OnChangeEndLyric() 
{
	CString lyric_text;
	int len_text;
	GetDlgItemText(IDC_END_LYRIC,lyric_text);
	len_text = lyric_text.GetLength();
	lyric_text = lyric_text.Mid(1,len_text-2);
	switch (is_user)
	{
	case 1:
		{
			user1_end_lyric = lyric_text;
			break;
		}
	case 2:
		{
			user2_end_lyric = lyric_text;
			break;
		}
	case 3:
		{
			user3_end_lyric = lyric_text;
			break;
		}
	}
}


void CFillLyricsLinefeedDlg::OnUser1FillLyrics() 
{
	is_user = 1;
	m_user1.SetCheck(1);
	m_user2. SetCheck(0);
	m_user3.SetCheck(0);
	actualize();	
}

void CFillLyricsLinefeedDlg::OnUser2FillLyrics() 
{
	is_user = 2;
	m_user1.SetCheck(0);
	m_user2. SetCheck(1);
	m_user3.SetCheck(0);
	actualize();	
}

void CFillLyricsLinefeedDlg::OnUser3FillLyrics() 
{
	is_user = 3;
	m_user1.SetCheck(0);
	m_user2. SetCheck(0);
	m_user3.SetCheck(1);
	actualize();	
}

