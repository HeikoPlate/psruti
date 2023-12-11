// delete_keyboard_events.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "delete_keyboard_events.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld delete_keyboard_events 


delete_keyboard_events::delete_keyboard_events(CWnd* pParent /*=NULL*/)
	: CDialog(delete_keyboard_events::IDD, pParent)
{
	//{{AFX_DATA_INIT(delete_keyboard_events)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void delete_keyboard_events::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(delete_keyboard_events)
	DDX_Control(pDX, IDC_SP_MARKER, m_sp_marker);
	DDX_Control(pDX, IDC_GUIDE, m_sysex_guide);
	DDX_Control(pDX, IDC_PHRASE_METAS, m_phrase_metas);
	DDX_Control(pDX, IDC_SCORE_START_BAR, m_score_start_bar);
	DDX_Control(pDX, IDC_GUIDE_TRACK_FLAG, m_guide_track_flag);
	DDX_Control(pDX, IDC_LYRICS_BITMAP_EVENTS, m_lyrics_bitmap_events);
	DDX_Control(pDX, IDC_KBD_VOICE_EVENTS, m_kbd_voice_events);
	DDX_Control(pDX, IDC_STYLE_SYSEX, m_style_sysex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(delete_keyboard_events, CDialog)
	//{{AFX_MSG_MAP(delete_keyboard_events)
	ON_BN_CLICKED(IDC_KBD_VOICE_EVENTS, OnKbdVoiceEvents)
	ON_BN_CLICKED(IDC_STYLE_SYSEX, OnStyleSysex)
	ON_BN_CLICKED(IDC_GUIDE_TRACK_FLAG, OnGuideTrackFlag)
	ON_BN_CLICKED(IDC_LYRICS_BITMAP_EVENTS, OnLyricsBitmapEvents)
	ON_BN_CLICKED(IDC_PHRASE_METAS, OnPhraseMetas)
	ON_BN_CLICKED(IDC_SCORE_START_BAR, OnScoreStartBar)
	ON_BN_CLICKED(IDC_GUIDE, OnSysExGuide)
	ON_BN_CLICKED(IDC_SP_MARKER, OnSpMarker)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten delete_keyboard_events 

void delete_keyboard_events::OnKbdVoiceEvents() 
{
	del_kbd_voice_events = (m_kbd_voice_events.GetCheck()==1)?true:false;
}

void delete_keyboard_events::OnGuideTrackFlag() 
{
	del_guide_track_events = (m_guide_track_flag.GetCheck()==1)?true:false;
}

void delete_keyboard_events::OnSysExGuide() 
{
	del_sysex_guide_events = (m_sysex_guide.GetCheck()==1)?true:false;
}

void delete_keyboard_events::OnLyricsBitmapEvents() 
{
	del_lyrics_bitmap_events = (m_lyrics_bitmap_events.GetCheck()==1)?true:false;
}

void delete_keyboard_events::OnPhraseMetas() 
{
	del_phrase_events = (m_phrase_metas.GetCheck()==1)?true:false;
}

void delete_keyboard_events::OnScoreStartBar() 
{
del_score_start_bar_events = (m_score_start_bar.GetCheck()==1)?true:false;
}

void delete_keyboard_events::OnStyleSysex() 
{
	del_style_events = (m_style_sysex.GetCheck()==1)?true:false;
}

void delete_keyboard_events::OnSpMarker() 
{
	del_sp_marker_events = (m_sp_marker.GetCheck()==1)?true:false;
}


BOOL delete_keyboard_events::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	del_kbd_voice_events = true;
	m_kbd_voice_events.SetCheck(1);

	del_phrase_events = true;
    m_phrase_metas.SetCheck(1);

	del_guide_track_events = true;
    m_guide_track_flag.SetCheck(1);

	del_sysex_guide_events = true;
	m_sysex_guide.SetCheck(1);

	del_lyrics_bitmap_events = true;
 	m_lyrics_bitmap_events.SetCheck(1);

	del_score_start_bar_events = true;
 	m_score_start_bar.SetCheck(1);

	del_style_events = true;
	m_style_sysex.SetCheck(1);

	del_sp_marker_events = false;
	m_sp_marker.SetCheck(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void delete_keyboard_events::OnOK() 
{
	EndDialog(1);
}

void delete_keyboard_events::OnCancel() 
{
	EndDialog(-1);
}

