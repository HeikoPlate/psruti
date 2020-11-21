// StartBeat.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "StartBeat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld StartBeat 


StartBeat::StartBeat(CWnd* pParent /*=NULL*/)
	: CDialog(StartBeat::IDD, pParent)
{
	//{{AFX_DATA_INIT(StartBeat)
	//}}AFX_DATA_INIT
	drum = NO_DRUMS+FIRST_DRUM; // initialized for delete countin
	velocity = 0;
}

const char* StartBeat::drums[NO_DRUMS+1] =
{
	"C#1: Surdo Mute",		// 13
	"D1:  Surdo Open",		// 14
	"Eb1: Hi Q",			// 15
	"E1:  Whip Slap",		// 16
	"F1:  Scratch H",		// 17
	"F#1: Scratch L",		// 18
	"G1:  Finger Snap",		// 19
	"Ab1: Click Noise",		// 20
	"A1:  Metronome Click",	// 21
	"Bb1: Metronome Bell",	// 22
	"B1:  Seq Click L",		// 23
	"C2:  Seq Click H",		// 24
	"C2#: Brush Tap",		// 25
	"D2:  Brush Swirl",		// 26
	"Eb2: Brush Slap",		// 27
	"E2:  Brush Tap Swirl",	// 28
	"F2:  Snare Roll",		// 29
	"F#2: Castanet",		// 30
	"G2:  Snare Soft",		// 31
	"Ab2: Sticks",			// 32
	"A2:  Kick Soft",		// 33
	"Bb2: Open Rim Shot",	// 34
	"B2:  Kick Tight",		// 35 		
	"C3:  Kick",			// 36
	"C#3: Side Stick",		// 37
	"D3:  Snare",			// 38
	"Eb3: Hand Clap",		// 39
	"E3:  Snare Tight",		// 40	
	"F3:  Floor Tom L",		// 41
	"F#3: Hi-Hat Closed",	// 42
	"G3:  Floor Tom H",		// 43
	"Ab3: Hi-Hat Pedal",	// 44
	"A3:  Low Tom",			// 45
	"Bb3: Hi-Hat Open",		// 46
	"B3:  Mid Tom L",		// 47
	"C4:  Mid Tom H",		// 48
	"C#4: Crash Cymbal 1",	// 49
	"D4:  High Tom",		// 50
	"Eb4: Ride Cymbal 1",	// 51
	"E4:  Chinese Cymbal",	// 52
	"F4:  Ride Cimbal Cup",	// 53
	"F#4: Tambourine",		// 54
	"G4:  Splash Cymbal",	// 55
	"Ab4: Cowbell",			// 56
	"A4:  Crash Cymbal 2",	// 57
	"Bb4: Vibraslap",		// 58
	"B4:  Ride Cymbal 2",	// 59
	"C5:  Bongo H",			// 60		
	"C#5: Bongo L",			// 61
	"D5:  Conga H Mute",	// 62
	"Eb5: Conga H Open",	// 63
	"E5:  Conga L",			// 64
	"F5:  Timbale H",		// 65
	"F#5: Timbale L",		// 66
	"G5:  Agogo H",			// 67
	"Ab5: Agogo L",			// 68
	"A5:  Cabasa",			// 69
	"Bb5: Maracas",			// 70
	"B5:  Samba Whistle H",	// 71
	"C6:  Samba Whistle L",	// 72
	"C#6: Guiro Short",		// 73
	"D6:  Guiro Long",		// 74
	"Eb6: Claves",			// 75
	"E6:  Wood Block H",	// 76
	"F6:  Wood Block L",	// 77
	"F#6: Cuica Mute",		// 78
	"G6:  Cuica Open",		// 79
	"Ab6: Triangle Mute",	// 80
	"A6:  Triangle Open",	// 81
	"Bb6: Shaker",			// 82
	"B6:  Jingle Bells",	// 83
	"C6:  Bell Tree",       // 84
	""						// empty string, needed for delete count in
};


void StartBeat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StartBeat)
	DDX_Control(pDX, IDC_CHECK_ONE_MEASURE, m_check_one_measure);
	DDX_Control(pDX, IDC_CHECK_ALL_BEATS, m_check_all_beats);
	DDX_Control(pDX, IDC_DRUM_LIST, m_drum);
	DDX_Control(pDX, IDC_START_BEAT_VEL, m_start_beat_vel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(StartBeat, CDialog)
	//{{AFX_MSG_MAP(StartBeat)
	ON_EN_CHANGE(IDC_START_BEAT_VEL, OnChangeStartBeatVel)
	ON_BN_CLICKED(IDC_CHECK_ALL_BEATS, OnCheckAllBeats)
	ON_BN_CLICKED(IDC_CHECK_ONE_MEASURE, OnCheckOneMeasure)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten StartBeat 

void StartBeat::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	drum = m_drum.GetCurSel()+FIRST_DRUM;
	velocity = GetDlgItemInt(IDC_START_BEAT_VEL);
	EndDialog(1);
}


void StartBeat::OnCancel() 
{
	EndDialog(-1);
}


BOOL StartBeat::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int i;

	m_drum.InitStorage(NO_DRUMS,25);
	for (i=0; i<NO_DRUMS; i++)
	{
		m_drum.AddString(drums[i]);
	}
	m_drum.SetCurSel(drum-FIRST_DRUM); 

	SetDlgItemInt(IDC_START_BEAT_VEL,velocity,FALSE);
	m_check_all_beats.SetCheck(0);
	m_check_one_measure.SetCheck(0);
	on_all_beats = false;
	only_one_measure = false;

	if (start_beat_delete)
	{
		m_drum.EnableWindow(false);
		m_start_beat_vel.EnableWindow(false);
		m_check_all_beats.EnableWindow(false);
		m_check_one_measure.EnableWindow(false);
		SetDlgItemText(IDC_START_BEAT_INS_DEL,
			GlobalUtilities::get_resource_string(IDS_COUNT_IN_DELETE));
	}
	else
	{
		m_start_beat_vel.EnableWindow(true);
		m_check_all_beats.EnableWindow(true);
		m_drum.EnableWindow(true);
		m_check_one_measure.EnableWindow(true);
		SetDlgItemText(IDC_START_BEAT_INS_DEL,
			GlobalUtilities::get_resource_string(IDS_COUNT_IN_INSERT));
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void StartBeat::OnChangeStartBeatVel() 
{

	int vel = GetDlgItemInt(IDC_START_BEAT_VEL);
	if (vel > 127)
	{
		SetDlgItemInt(IDC_START_BEAT_VEL,127,FALSE);
	}
	if (vel <= 0)
	{
		SetDlgItemInt(IDC_START_BEAT_VEL,1,FALSE);
	}
}

int StartBeat::get_velocity()
{
	return velocity;
}

int StartBeat::get_drum()
{
	return drum;
}

void StartBeat::set_velocity(int vel)
{
	velocity = vel;
}

void StartBeat::set_drum(int note)
{
	drum = note;
}

void StartBeat::OnCheckAllBeats() 
{
	on_all_beats = m_check_all_beats.GetCheck()==1;	
}

void StartBeat::OnCheckOneMeasure() 
{
	only_one_measure = m_check_one_measure.GetCheck()==1;
}
