// InsertChordLyrics.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "InsertChordLyrics.h"
#include "GlobalUtilities.h"
#include "HP_midifile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld InsertChordLyrics 


InsertChordLyrics::InsertChordLyrics(CWnd* pParent /*=NULL*/)
	: CDialog(InsertChordLyrics::IDD, pParent)
{
	//{{AFX_DATA_INIT(InsertChordLyrics)
	//}}AFX_DATA_INIT
	linefeed_char = GlobalUtilities::get_linefeed_char();
}


void InsertChordLyrics::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InsertChordLyrics)
	DDX_Control(pDX, IDC_WHOLE_NOTE_BUTTON, m_whole_note);
	DDX_Control(pDX, IDC_QUARTER_NOTE_BUTTON, m_quarter_note);
	DDX_Control(pDX, IDC_EIGHTH_NOTE_BUTTON, m_eighth_note);
	DDX_Control(pDX, IDC_HALF_NOTE_BUTTON, m_half_note);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InsertChordLyrics, CDialog)
	//{{AFX_MSG_MAP(InsertChordLyrics)
	ON_BN_CLICKED(IDC_EIGHTH_NOTE_BUTTON, OnEighthNoteButton)
	ON_BN_CLICKED(IDC_HALF_NOTE_BUTTON, OnHalfNoteButton)
	ON_BN_CLICKED(IDC_WHOLE_NOTE_BUTTON, OnWholeNoteButton)
	ON_BN_CLICKED(IDC_QUARTER_NOTE_BUTTON, OnQuarterNoteButton)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten InsertChordLyrics 

void InsertChordLyrics::OnOK() 
{
	int i,k;
	char * cstring;
	int time;
	int old_time = -1;

	for (i=0; i<act_list_no; i++)
	{
		// quantize time by ppqn/resolution and beat-resolution
		time = record_chord_lyric_list[i].time;
		if (resolution != 0)
		{
			int delta = time%resolution;
			if (delta!=0)
			{
				int base = time/resolution;
				if (delta < resolution/2)
				{
					time = base*resolution;
				}
				else
				{
					time = (base+1)*resolution;
				}
			}
			// after quantisizing events on same time-stamps?
			if (time <= old_time)
			{
				time = old_time+resolution/8;
			}
		}
		else
		{
			if (time==old_time)
			{
				time += 60;
			}
		}
		old_time = time;
		HP_SetFirst(HP_LAST);
		
		if (is_chord_record)
		{
			HP_InsertChord(mf,time,
				              record_chord_lyric_list[i].cr,
					          record_chord_lyric_list[i].ct,
						      record_chord_lyric_list[i].bn,
							  record_chord_lyric_list[i].bt);
		}

		if (is_lyric_record)
		{
			int len = (record_chord_lyric_list[i].text).GetLength();
			cstring = new char[len+1];
			for (k=0; k<len;k++)
			{
				cstring[k] = record_chord_lyric_list[i].text[k];
			}
			cstring[len] = (char)0;
			
			// posit linefeed lyrics
			int act_time = ((cstring[0]==linefeed_char)&&(len == 1))?time-5:time;
			if (act_time < 0) act_time= 0;
			old_time = act_time;

			HP_InsertLyric(mf,act_time,cstring);
			delete[] cstring;
		}
	}
	CDialog::OnOK();
}


BOOL InsertChordLyrics::OnInitDialog() 
{
	CDialog::OnInitDialog();

	HICON hIcon;
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON10);
	m_whole_note.SetIcon(hIcon);	
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON11);
	m_half_note.SetIcon(hIcon);	
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON12);
	m_quarter_note.SetIcon(hIcon);	
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON13);
	m_eighth_note.SetIcon(hIcon);	
	
	int ppqn = hpmfi->get_ppqn();

	resolution = 0;
	CString title = is_chord_record?
							GlobalUtilities::get_resource_string(IDS_INSERT_CHORDS):
							GlobalUtilities::get_resource_string(IDS_INSERT_LYRICS);
	SetWindowText(title);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void InsertChordLyrics::OnWholeNoteButton() 
{
	int ppqn = hpmfi->get_ppqn();
	int own_res = 4*ppqn;

	resolution = own_res;
	m_whole_note.SetState(TRUE);
	m_half_note.SetState(FALSE);
	m_quarter_note.SetState(FALSE);
	m_eighth_note.SetState(FALSE);
}

void InsertChordLyrics::OnHalfNoteButton() 
{
	int ppqn = hpmfi->get_ppqn();
	int own_res = 2*ppqn;

	resolution = own_res;
	m_whole_note.SetState(FALSE);
	m_half_note.SetState(TRUE);
	m_quarter_note.SetState(FALSE);
	m_eighth_note.SetState(FALSE);
}

void InsertChordLyrics::OnQuarterNoteButton() 
{
	int own_res = hpmfi->get_ppqn();

	resolution = own_res;
	m_whole_note.SetState(FALSE);
	m_half_note.SetState(FALSE);
	m_quarter_note.SetState(TRUE);
	m_eighth_note.SetState(FALSE);
}

void InsertChordLyrics::OnEighthNoteButton() 
{
	int own_res = hpmfi->get_ppqn()/2;

	resolution = own_res;
	m_whole_note.SetState(FALSE);
	m_half_note.SetState(FALSE);
	m_quarter_note.SetState(FALSE);
	m_eighth_note.SetState(TRUE);
}
