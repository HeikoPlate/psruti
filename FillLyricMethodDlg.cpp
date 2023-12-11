// FillLyricMethodDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "HPMF_Interface.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld FillLyricMethodDlg 


FillLyricMethodDlg::FillLyricMethodDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FillLyricMethodDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(FillLyricMethodDlg)
	//}}AFX_DATA_INIT
}


void FillLyricMethodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FillLyricMethodDlg)
	DDX_Control(pDX, IDC_USER1_FILL_LYRICS, m_user1_fill_lyrics);
	DDX_Control(pDX, IDC_USER2_FILL_LYRICS, m_user2_fill_lyrics);
	DDX_Control(pDX, IDC_USER3_FILL_LYRICS, m_user3_fill_lyrics);
	DDX_Control(pDX, IDC_NOT_AT_MEASURES_WITH_LYRICS, m_not_in_measures_with_lyrics);
	DDX_Control(pDX, IDC_NOT_AT_LYRICS, m_not_at_lyrics);
	DDX_Control(pDX, IDC_NOT_AT_BEATS_WITH_LYRICS, m_not_in_beats_with_lyrics);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FillLyricMethodDlg, CDialog)
	//{{AFX_MSG_MAP(FillLyricMethodDlg)
	ON_BN_CLICKED(IDC_NOT_AT_BEATS_WITH_LYRICS, OnNotInBeatsWithLyrics)
	ON_BN_CLICKED(IDC_NOT_AT_LYRICS, OnNotAtLyrics)
	ON_BN_CLICKED(IDC_NOT_AT_MEASURES_WITH_LYRICS, OnNotInMeasuresWithLyrics)
	ON_BN_CLICKED(IDC_USER1_FILL_LYRICS, OnUser1FillLyrics)
	ON_BN_CLICKED(IDC_USER2_FILL_LYRICS, OnUser2FillLyrics)
	ON_BN_CLICKED(IDC_USER3_FILL_LYRICS, OnUser3FillLyrics)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten FillLyricMethodDlg 

void FillLyricMethodDlg::OnNotInBeatsWithLyrics() 
{
	if (m_not_in_beats_with_lyrics.GetCheck()==1)
	{
		m_not_in_measures_with_lyrics.SetCheck(0);
		m_not_at_lyrics.SetCheck(0);
		method = NOT_IN_BEATS_WITH_LYRICS;
	}
	else
	{
		m_not_in_beats_with_lyrics.SetCheck(1);
	}
}

void FillLyricMethodDlg::OnNotAtLyrics() 
{
	if (m_not_at_lyrics.GetCheck()==1)
	{
		m_not_in_beats_with_lyrics.SetCheck(0);
		m_not_in_measures_with_lyrics.SetCheck(0);
		method = NOT_AT_LYRICS;
	}
	else
	{
		m_not_at_lyrics.SetCheck(1);
	}
}

void FillLyricMethodDlg::OnNotInMeasuresWithLyrics() 
{
	if (m_not_in_measures_with_lyrics.GetCheck()==1)
	{
		m_not_in_beats_with_lyrics.SetCheck(0);
		m_not_at_lyrics.SetCheck(0);
		method = NOT_IN_MEASURES_WITH_LYRICS;
	}
	else
	{
		m_not_in_measures_with_lyrics.SetCheck(1);
	}
}

void FillLyricMethodDlg::OnCancel() 
{
	EndDialog(0);
}

void FillLyricMethodDlg::OnOK() 
{
	EndDialog(1);
}

int FillLyricMethodDlg::get_actual_user()
{
	return is_user;
}

BOOL FillLyricMethodDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	display_actual_fill_lyrics();

	m_not_at_lyrics.SetCheck(0);
	m_not_in_beats_with_lyrics.SetCheck(0);
	m_not_in_measures_with_lyrics.SetCheck(1);
	method = NOT_IN_MEASURES_WITH_LYRICS;
	return TRUE;  
}

void FillLyricMethodDlg::display_actual_fill_lyrics()
{
	switch (is_user)
	{
	case 1:
		{
			SetDlgItemText(IDC_TAKT_LYRIC,GlobalUtilities::convert_string_to_printable(user1_takt_lyric));
			SetDlgItemText(IDC_BEAT_LYRIC,GlobalUtilities::convert_string_to_printable(user1_beat_lyric));
			SetDlgItemText(IDC_END_LYRIC,GlobalUtilities::convert_string_to_printable(user1_end_lyric));
			m_user1_fill_lyrics.SetCheck(1);
			m_user2_fill_lyrics.SetCheck(0);
			m_user3_fill_lyrics.SetCheck(0);
			break;
		}
	case 2:
		{
			SetDlgItemText(IDC_TAKT_LYRIC,GlobalUtilities::convert_string_to_printable(user2_takt_lyric));
			SetDlgItemText(IDC_BEAT_LYRIC,GlobalUtilities::convert_string_to_printable(user2_beat_lyric));
			SetDlgItemText(IDC_END_LYRIC,GlobalUtilities::convert_string_to_printable(user2_end_lyric));
			m_user1_fill_lyrics.SetCheck(0);
			m_user2_fill_lyrics.SetCheck(1);
			m_user3_fill_lyrics.SetCheck(0);
			break;
		}
	case 3:
		{
			SetDlgItemText(IDC_TAKT_LYRIC,GlobalUtilities::convert_string_to_printable(user3_takt_lyric));
			SetDlgItemText(IDC_BEAT_LYRIC,GlobalUtilities::convert_string_to_printable(user3_beat_lyric));
			SetDlgItemText(IDC_END_LYRIC,GlobalUtilities::convert_string_to_printable(user3_end_lyric));
			m_user1_fill_lyrics.SetCheck(0);
			m_user2_fill_lyrics.SetCheck(0);
			m_user3_fill_lyrics.SetCheck(1);
			break;
		}
	}
}

void FillLyricMethodDlg::set_fill_lyric_data(CString u1_takt_l, CString u1_beat_l, CString u1_end_l,
											 CString u2_takt_l, CString u2_beat_l, CString u2_end_l,
											 CString u3_takt_l, CString u3_beat_l, CString u3_end_l,
											 int is_u)
{
	// called from outside before InitDialog 
	user1_takt_lyric = u1_takt_l;
	user1_beat_lyric = u1_beat_l;
	user1_end_lyric = u1_end_l;
	user2_takt_lyric = u2_takt_l;
	user2_beat_lyric = u2_beat_l;
	user2_end_lyric = u2_end_l;
	user3_takt_lyric = u3_takt_l;
	user3_beat_lyric = u3_beat_l;
	user3_end_lyric = u3_end_l;
	is_user = is_u;
}


void FillLyricMethodDlg::OnUser1FillLyrics() 
{
	m_user1_fill_lyrics.SetCheck(1);
	m_user2_fill_lyrics.SetCheck(0);
	m_user3_fill_lyrics.SetCheck(0);
	is_user = 1;
	display_actual_fill_lyrics();
}

void FillLyricMethodDlg::OnUser2FillLyrics() 
{
	m_user1_fill_lyrics.SetCheck(0);
	m_user2_fill_lyrics.SetCheck(1);
	m_user3_fill_lyrics.SetCheck(0);
	is_user = 2;
	display_actual_fill_lyrics();	
}

void FillLyricMethodDlg::OnUser3FillLyrics() 
{
	m_user1_fill_lyrics.SetCheck(0);
	m_user2_fill_lyrics.SetCheck(0);
	m_user3_fill_lyrics.SetCheck(1);
	is_user = 3;
	display_actual_fill_lyrics();
}
