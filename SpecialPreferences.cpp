// SpecialPreferences.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "SpecialPreferences.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSpecialPreferences 


CSpecialPreferences::CSpecialPreferences(CWnd* pParent /*=NULL*/)
	: CDialog(CSpecialPreferences::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpecialPreferences)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CSpecialPreferences::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpecialPreferences)
	DDX_Control(pDX, IDC_CHECK_WITHOUT_SYSEX_DRUMKIT_MODE, m_without_sysex_drumkit_mode);
	DDX_Control(pDX, IDC_VH_EVENTS_DELETE, m_vh_events_delete);
	DDX_Control(pDX, IDC_DRUMS_FROM_INSFILE, m_drums_from_insfile);
	DDX_Control(pDX, IDC_NO_LYRICS_CUEPOINT, m_no_lyric_cuepoint);
	DDX_Control(pDX, IDC_ALLOW_ALIEN_VOICES, m_allow_alien_voices);
	DDX_Control(pDX, IDC_ALLOW_ALIEN_SYSEX, m_allow_alien_sysex);
	DDX_Control(pDX, IDC_FILL_SEQU_TRACK, m_fill_sequ_track);
	DDX_Control(pDX, IDC_DRUM_SETUP_CONVERT, m_drum_setup_convert);
	DDX_Control(pDX, IDC_MP_CONVERT, m_mp_convert);
	DDX_Control(pDX, IDC_DELETE_DOUBLE_NOTES, m_delete_double_notes);
	DDX_Control(pDX, IDC_DELETE_NOT_DOUBLE_DRUM_NOTES, m_delete_not_double_drum_notes);
	DDX_Control(pDX, IDC_CHECK_DCHAN, m_check_dchan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpecialPreferences, CDialog)
	//{{AFX_MSG_MAP(CSpecialPreferences)
	ON_BN_CLICKED(IDC_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_DELETE_DOUBLE_NOTES, OnDeleteDoubleNotes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CSpecialPreferences 

void CSpecialPreferences::OnOK() 
{
	int no_eff_blocks = GetDlgItemInt(IDC_NO_EFF_BLOCKS);
	o_inifile->set_no_effect_blocks(no_eff_blocks);

	int vh_eff_block = GetDlgItemInt(IDC_VH_EFF_BLOCK);
	o_inifile->set_vh_effect_block(vh_eff_block);
	
	int dchan = m_check_dchan.GetCheck();
	o_inifile->set_delete_empty_chan(dchan==1);

	int double_notes = m_delete_double_notes.GetCheck();
	o_inifile->set_double_notes(double_notes==0);

	int delete_not_double_drum_notes = m_delete_not_double_drum_notes.GetCheck();
	o_inifile->set_not_double_drum_notes(delete_not_double_drum_notes==1); 

	int mp_convert = m_mp_convert.GetCheck();
	o_inifile->set_multipart_convert(mp_convert);

	int drum_setup_convert = m_drum_setup_convert.GetCheck();
	o_inifile->set_drumsetup_convert(drum_setup_convert);

	int fill_sequ_track = m_fill_sequ_track.GetCheck();
	o_inifile->set_fill_sequ_track(fill_sequ_track==1);

	int delete_alien_sysex = m_allow_alien_sysex.GetCheck();   // look at text in window!
	o_inifile->set_alien_sysex(delete_alien_sysex==1?0:1);

	int delete_alien_voices = m_allow_alien_voices.GetCheck(); // look at text in window!
	o_inifile->set_alien_voice(delete_alien_voices==1?0:1);

	int no_lyric_cuepoint = m_no_lyric_cuepoint.GetCheck(); 
	o_inifile->set_with_lyric_cuepoint(no_lyric_cuepoint==1?0:1);

	int drums_from_insfile = m_drums_from_insfile.GetCheck(); 
	o_inifile->set_with_drums_from_insfile(drums_from_insfile==1?1:0);

	int vh_events_delete = m_vh_events_delete.GetCheck(); 
	o_inifile->set_vh_events_delete(vh_events_delete==1?1:0);

	int with_sysex_drumkit_mode = m_without_sysex_drumkit_mode.GetCheck();
	o_inifile->set_with_sysex_drumkit_mode(with_sysex_drumkit_mode==1?0:1);

	CDialog::OnOK();
}

void CSpecialPreferences::OnCancel() 
{
	CDialog::OnCancel();
}

BOOL CSpecialPreferences::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int no_eff_blocks = o_inifile->get_no_effect_blocks();
	SetDlgItemInt(IDC_NO_EFF_BLOCKS,no_eff_blocks);

	int vh_eff_block = o_inifile->get_vh_effect_block();
	SetDlgItemInt(IDC_VH_EFF_BLOCK, vh_eff_block);

	bool dchan = o_inifile->get_delete_empty_chan();
	m_check_dchan.SetCheck(dchan?1:0);

	bool delete_double_notes = !o_inifile->get_double_notes();
	m_delete_double_notes.SetCheck(delete_double_notes?1:0);

	bool delete_not_double_drum_notes = !o_inifile->get_not_double_drum_notes();
	if (delete_double_notes)
	{
		m_delete_not_double_drum_notes.SetCheck(delete_not_double_drum_notes?0:1);
		m_delete_not_double_drum_notes.EnableWindow(true);
	}
	else
	{
		m_delete_not_double_drum_notes.SetCheck(0);
		m_delete_not_double_drum_notes.EnableWindow(false);
	}

	int mp_convert = o_inifile->get_multipart_convert();
	m_mp_convert.SetCheck(mp_convert);

	int drum_setup_convert = o_inifile->get_drumsetup_convert();
	m_drum_setup_convert.SetCheck(drum_setup_convert);

	bool fill_sequ_track = o_inifile->get_fill_sequ_track();
	m_fill_sequ_track.SetCheck(fill_sequ_track?1:0);

	bool allow_alien_sysex = o_inifile->get_alien_sysex();
	m_allow_alien_sysex.SetCheck(allow_alien_sysex?0:1);        // look at text in window!

	bool allow_alien_voices = o_inifile->get_alien_voice();
	m_allow_alien_voices.SetCheck(allow_alien_voices?0:1);      // look at text in window!

	bool with_lyric_cuepoint = o_inifile->get_with_lyric_cuepoint();
	m_no_lyric_cuepoint.SetCheck(with_lyric_cuepoint?0:1);      // look at text in window!

	bool with_drums_from_insfile = o_inifile->get_with_drums_from_insfile();
	m_drums_from_insfile.SetCheck(with_drums_from_insfile?1:0); // look at text in window!

	bool vh_events_delete = o_inifile->get_vh_events_delete();
	m_vh_events_delete.SetCheck(vh_events_delete?1:0);              // look at text in window!

	bool with_sysex_drumkit_mode = o_inifile->get_with_sysex_drumkit_mode();
	m_without_sysex_drumkit_mode.SetCheck(with_sysex_drumkit_mode?0:1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CSpecialPreferences::OnDefault() 
{
	SetDlgItemInt(IDC_NO_EFF_BLOCKS,5);
	SetDlgItemInt(IDC_VH_EFF_BLOCK, 5);
	m_check_dchan.SetCheck(1);
	m_delete_double_notes.SetCheck(1);
	m_mp_convert.SetCheck(1);
	m_drum_setup_convert.SetCheck(0);
	m_fill_sequ_track.SetCheck(1);
	m_allow_alien_sysex.SetCheck(1); // look at text in window!
	m_allow_alien_voices.SetCheck(1);// look at text in window!
	m_no_lyric_cuepoint.SetCheck(0);
	m_drums_from_insfile.SetCheck(0);
	m_vh_events_delete.SetCheck(0);    // look at text in window!
	m_without_sysex_drumkit_mode.SetCheck(1);
}

void CSpecialPreferences::OnDeleteDoubleNotes() 
{
	m_delete_not_double_drum_notes.EnableWindow(m_delete_double_notes.GetCheck()==1);
	m_delete_not_double_drum_notes.SetCheck(0);
}

