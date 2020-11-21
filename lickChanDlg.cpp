// lickChanDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "lickChanDlg.h"
#include "GlobalUtilities.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld ClickChanDlg 


ClickChanDlg::ClickChanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ClickChanDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ClickChanDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void ClickChanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ClickChanDlg)
	DDX_Control(pDX, IDC_BEAT_DRUM_COMBO, m_beat_drum_combo);
	DDX_Control(pDX, IDC_DRUM_MAINVOLUME, m_drum_mainvolume);
	DDX_Control(pDX, IDC_MEASURE_DRUM_COMBO, m_measure_drum_combo);
	DDX_Control(pDX, IDC_MEASURE_DRUM_VELOCITY, m_measure_drum_velocity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ClickChanDlg, CDialog)
	//{{AFX_MSG_MAP(ClickChanDlg)
	ON_EN_CHANGE(IDC_DRUM_MAINVOLUME, OnChangeDrumMainvolume)
	ON_EN_CHANGE(IDC_MEASURE_DRUM_VELOCITY, OnChangeMeasureDrumVelocity)
	ON_EN_CHANGE(IDC_BEAT_DRUM_VELOCITY, OnChangeBeatDrumVelocity)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten ClickChanDlg 

void ClickChanDlg::OnCancel() 
{
	EndDialog(1);
}

void ClickChanDlg::OnOK() 
{
	main_vol_chan10 = GetDlgItemInt(IDC_DRUM_MAINVOLUME);
	noteval_meas = GlobalUtilities::gm_drum_list[m_measure_drum_combo.GetCurSel()].drum_note_number;
	vel_meas = GetDlgItemInt(IDC_MEASURE_DRUM_VELOCITY);
	noteval_beat = GlobalUtilities::gm_drum_list[m_beat_drum_combo.GetCurSel()].drum_note_number;
	vel_beat = GetDlgItemInt(IDC_BEAT_DRUM_VELOCITY);
	EndDialog(0);
}

BOOL ClickChanDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	main_vol_chan10 = o_inifile->get_click_main_vol();
	noteval_meas = o_inifile->get_click_note_meas();
	noteval_beat = o_inifile->get_click_note_beat();
	vel_meas = o_inifile->get_click_vel_meas();
	vel_beat = o_inifile->get_click_vel_beat();

	int i;
	CString drum_line;

	SetDlgItemInt(IDC_DRUM_MAINVOLUME,main_vol_chan10);
	SetDlgItemInt(IDC_MEASURE_DRUM_VELOCITY,vel_meas);
	SetDlgItemInt(IDC_BEAT_DRUM_VELOCITY,vel_beat);

	for (i=0; i<NO_GM_DRUMS; i++)
	{
		drum_line = GlobalUtilities::compute_notestring(GlobalUtilities::gm_drum_list[i].drum_note_number);
		drum_line += ": ";
		drum_line += GlobalUtilities::gm_drum_list[i].drum_name;
		m_measure_drum_combo.AddString(drum_line);
		m_beat_drum_combo.AddString(drum_line);

		if (GlobalUtilities::gm_drum_list[i].drum_note_number == noteval_meas)
		{
			m_measure_drum_combo.SetCurSel(i);
		}
		if (GlobalUtilities::gm_drum_list[i].drum_note_number == noteval_beat)
		{
			m_beat_drum_combo.SetCurSel(i);
		}
	}

	return TRUE;  
}

void ClickChanDlg::OnChangeDrumMainvolume() 
{
	int mainvolume = GetDlgItemInt(IDC_DRUM_MAINVOLUME);
	if (mainvolume < 0)
	{
		SetDlgItemInt(IDC_DRUM_MAINVOLUME,0);
	}
	if (mainvolume > 127)
	{
		SetDlgItemInt(IDC_DRUM_MAINVOLUME,127);
	}
}

void ClickChanDlg::OnChangeMeasureDrumVelocity() 
{
	int beatdrumvelocity = GetDlgItemInt(IDC_MEASURE_DRUM_VELOCITY);
	if (beatdrumvelocity < 1)
	{
		SetDlgItemInt(IDC_MEASURE_DRUM_VELOCITY,1);
	}
	if (beatdrumvelocity > 127)
	{
		SetDlgItemInt(IDC_MEASURE_DRUM_VELOCITY,127);
	}
}

void ClickChanDlg::OnChangeBeatDrumVelocity() 
{
	int beatdrumvelocity = GetDlgItemInt(IDC_BEAT_DRUM_VELOCITY);
	if (beatdrumvelocity < 1)
	{
		SetDlgItemInt(IDC_BEAT_DRUM_VELOCITY,1);
	}
	if (beatdrumvelocity > 127)
	{
		SetDlgItemInt(IDC_BEAT_DRUM_VELOCITY,127);
	}
}
