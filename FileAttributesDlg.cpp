// FileAttributesDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "FileAttributesDlg.h"
#include "GlobalUtilities.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld FileAttributesDlg 


FileAttributesDlg::FileAttributesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FileAttributesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(FileAttributesDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void FileAttributesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FileAttributesDlg)
	DDX_Control(pDX, IDC_FILE_ATTRIBUTES, m_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FileAttributesDlg, CDialog)
	//{{AFX_MSG_MAP(FileAttributesDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten FileAttributesDlg 

BOOL FileAttributesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString text;
	CString linefeed = (char)0x0d;
	linefeed += (char)0x0a;
	CString yes = GlobalUtilities::get_resource_string(IDS_YES);
	CString no  = GlobalUtilities::get_resource_string(IDS_NO);
	CString tab = "\t";
	CString r;

//	SetWindowText("File Daten");
	SetWindowText(GlobalUtilities::get_resource_string(IDS_FILE_DATA));
	
	// Sourcefile

	text = "MIDI File: " + tab + sourcefile + linefeed;
	if (with_additional_chunks)
	{
		text+= tab + tab + GlobalUtilities::get_resource_string(IDS_MORE_CHUNKS_SHORT) + "!" + linefeed;
	}

	// Songname

	text+= "Songname:  " + tab + songname + linefeed;

	// Copyright

	text+= "Copyright:  " + tab + copyright + linefeed;

	// Format
	
	text+= "Format:       " + tab + format +" / " + sub_format + linefeed;

	// PPQN
	
	r.Format("%i",original_ppqn);
	text+= "PPQN:         " + tab + r + linefeed;

	// Measure

	text+= GlobalUtilities::get_resource_string(IDS_TIME) + 
		":         " + tab + takt + linefeed;

	// Tempo

	if (tempo != -1) 
	{
		r.Format("%4.2f",tempo);
	}
	else
	{
		r = "--";
	}
	text+= "Tempo:        " + tab + r + linefeed;

	// Key Signature

	// text+= "Tonart:       " + tab + key + linefeed;
	text+= GlobalUtilities::get_resource_string(IDS_KEY) + 
		":           " + tab + key + linefeed;

	// Lyrics

	// text+= "Lyrics:       " + tab + (lyrics?"ja":"nein") + linefeed;
	text+= "Lyrics:       " + tab + (lyrics?yes:no) + linefeed;

	// Chords

	//	text+= "Akkorde:      " + tab + (chords?"ja":"nein") + linefeed;
	text+= GlobalUtilities::get_resource_string(IDS_CHORDS) + 
		":         " + tab + (chords?yes:no) + linefeed;

	// VH Channels

	text+= GlobalUtilities::get_resource_string(IDS_VH_CHANNEL) + 
		":         " + tab + vh_channels + linefeed;
	
	// Score channels

	int score_chan_left;
	int score_chan_right;
	CString rl, rr;
	hpmfi->get_scorechan(&score_chan_left, &score_chan_right);

	if (score_chan_left >=0)
	{
		rl.Format("L = %i, ",score_chan_left+1);
	}
	else 
	{
		rl.Format("L = %s, ","--");
	}

	if (score_chan_right >=0)
	{
		rr.Format("R = %i",score_chan_right+1);
	}
	else 
	{
		rr.Format("R = %s","--");
	}

    text+= GlobalUtilities::get_resource_string(IDS_SCORE_CHANNELS) +tab +rl +rr +linefeed;

	// Count In

//	text+= "Einzähler:    " + tab +(count_in?"ja":"nein") + linefeed;
	text+= GlobalUtilities::get_resource_string(IDS_COUNT_IN) + 
		":         " + tab + (count_in?yes:no) + linefeed;

	// No Measures

	r.Format("%i",no_measures);
//	text+= "Taktanzahl:" + tab + r + linefeed;
	text+= GlobalUtilities::get_resource_string(IDS_NO_MEASURES)+":      " + tab + r + linefeed;

	// Duration

//	r.Format("%i",duration);
	r.Format("%i:%2.2i min",duration/60,duration%60);
//	text+= "Dauer:        " + tab + r + " Sekunden"; 
	text+= GlobalUtilities::get_resource_string(IDS_DURATION)+":        " + tab + r + linefeed;

	m_text.SetWindowText(text);
	
	return TRUE;  
}
