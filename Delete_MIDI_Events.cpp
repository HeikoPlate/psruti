// Delete_MIDI_Events.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Delete_MIDI_Events.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Delete_MIDI_Events 


Delete_MIDI_Events::Delete_MIDI_Events(CWnd* pParent /*=NULL*/)
	: CDialog(Delete_MIDI_Events::IDD, pParent)
{
	//{{AFX_DATA_INIT(Delete_MIDI_Events)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT

	m_pToolTip = NULL;
	event_type = -1;
	ctrl_number = -1;

	// inializes membervariable list m_voice_type

	m_voice_type[0] = &m_v_voice1;
	m_voice_type[1] = &m_v_voice2;
	m_voice_type[2] = &m_v_voice3;
	m_voice_type[3] = &m_v_voice4;
	m_voice_type[4] = &m_v_voice5;
	m_voice_type[5] = &m_v_voice6;
	m_voice_type[6] = &m_v_voice7;
	m_voice_type[7] = &m_v_voice8;
	m_voice_type[8] = &m_v_voice9;
	m_voice_type[9] = &m_v_voice10;
	m_voice_type[10] = &m_v_voice11;
	m_voice_type[11] = &m_v_voice12;
	m_voice_type[12] = &m_v_voice13;
	m_voice_type[13] = &m_v_voice14;
	m_voice_type[14] = &m_v_voice15;
	m_voice_type[15] = &m_v_voice16;


	idc_voice_type[0] = IDC_V_VOICE1;
	idc_voice_type[1] = IDC_V_VOICE2;
	idc_voice_type[2] = IDC_V_VOICE3;
	idc_voice_type[3] = IDC_V_VOICE4;
	idc_voice_type[4] = IDC_V_VOICE5;
	idc_voice_type[5] = IDC_V_VOICE6;
	idc_voice_type[6] = IDC_V_VOICE7;
	idc_voice_type[7] = IDC_V_VOICE8;
	idc_voice_type[8] = IDC_V_VOICE9;
	idc_voice_type[9] = IDC_V_VOICE10;
	idc_voice_type[10] = IDC_V_VOICE11;
	idc_voice_type[11] = IDC_V_VOICE12;
	idc_voice_type[12] = IDC_V_VOICE13;
	idc_voice_type[13] = IDC_V_VOICE14;
	idc_voice_type[14] = IDC_V_VOICE15;
	idc_voice_type[15] = IDC_V_VOICE16;

	idc_no_list[0] = IDC_NO1;
	idc_no_list[1] = IDC_NO2;
	idc_no_list[2] = IDC_NO3;
	idc_no_list[3] = IDC_NO4;
	idc_no_list[4] = IDC_NO5;
	idc_no_list[5] = IDC_NO6;
	idc_no_list[6] = IDC_NO7;
	idc_no_list[7] = IDC_NO8;
	idc_no_list[8] = IDC_NO9;
	idc_no_list[9] = IDC_NO10;
	idc_no_list[10] = IDC_NO11;
	idc_no_list[11] = IDC_NO12;
	idc_no_list[12] = IDC_NO13;
	idc_no_list[13] = IDC_NO14;
	idc_no_list[14] = IDC_NO15;
	idc_no_list[15] = IDC_NO16;
	idc_no_list[16] = IDC_NO_ALL;

	checklist[0]= &m_check1;
	checklist[1]= &m_check2;
	checklist[2]= &m_check3;
	checklist[3]= &m_check4;
	checklist[4]= &m_check5;
	checklist[5]= &m_check6;
	checklist[6]= &m_check7;
	checklist[7]= &m_check8;
	checklist[8]= &m_check9;
	checklist[9]= &m_check10;
	checklist[10]= &m_check11;
	checklist[11]= &m_check12;
	checklist[12]= &m_check13;
	checklist[13]= &m_check14;
	checklist[14]= &m_check15;
	checklist[15]= &m_check16;
	checklist[16]= &m_check_all;

	int ch, i, k;
	for (ch=0; ch<16; ch++)
	{
		is_checked[ch] = false;
	}

	for (k=0; k<17; k++)
	{
		for (i=0; i<NO_MIDI_EVENTS; i++)
		{
			(no_midi_events_list[k])[i] = 0;
			(no_midi_events_before_notes_list[k])[i] = 0;
			(no_midi_events_note_area_list[k])[i] = 0;
		}
	}
}


void Delete_MIDI_Events::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Delete_MIDI_Events)
	DDX_Control(pDX, IDC_NOTE_AREA, m_note_area);
	DDX_Control(pDX, IDC_BEFORE_NOTES, m_before_notes);
	DDX_Control(pDX, IDC_CHECK1, m_check1);
	DDX_Control(pDX, IDC_CHECK2, m_check2);
	DDX_Control(pDX, IDC_CHECK3, m_check3);
	DDX_Control(pDX, IDC_CHECK4, m_check4);
	DDX_Control(pDX, IDC_CHECK5, m_check5);
	DDX_Control(pDX, IDC_CHECK6, m_check6);
	DDX_Control(pDX, IDC_CHECK7, m_check7);
	DDX_Control(pDX, IDC_CHECK8, m_check8);
	DDX_Control(pDX, IDC_CHECK9, m_check9);
	DDX_Control(pDX, IDC_CHECK10, m_check10);
	DDX_Control(pDX, IDC_CHECK11, m_check11);
	DDX_Control(pDX, IDC_CHECK12, m_check12);
	DDX_Control(pDX, IDC_CHECK13, m_check13);
	DDX_Control(pDX, IDC_CHECK14, m_check14);
	DDX_Control(pDX, IDC_CHECK15, m_check15);
	DDX_Control(pDX, IDC_CHECK16, m_check16);
	DDX_Control(pDX, IDC_CHECK_ALL, m_check_all);
	DDX_Control(pDX, IDC_MIDI_EVENT_COMBOBOX, m_midi_event_combobox);
	DDX_Control(pDX, IDC_V_VOICE1, m_v_voice1);
	DDX_Control(pDX, IDC_V_VOICE2, m_v_voice2);
	DDX_Control(pDX, IDC_V_VOICE3, m_v_voice3);
	DDX_Control(pDX, IDC_V_VOICE4, m_v_voice4);
	DDX_Control(pDX, IDC_V_VOICE5, m_v_voice5);
	DDX_Control(pDX, IDC_V_VOICE6, m_v_voice6);
	DDX_Control(pDX, IDC_V_VOICE7, m_v_voice7);
	DDX_Control(pDX, IDC_V_VOICE8, m_v_voice8);
	DDX_Control(pDX, IDC_V_VOICE9, m_v_voice9);
	DDX_Control(pDX, IDC_V_VOICE10, m_v_voice10);
	DDX_Control(pDX, IDC_V_VOICE11, m_v_voice11);
	DDX_Control(pDX, IDC_V_VOICE12, m_v_voice12);
	DDX_Control(pDX, IDC_V_VOICE13, m_v_voice13);
	DDX_Control(pDX, IDC_V_VOICE14, m_v_voice14);
	DDX_Control(pDX, IDC_V_VOICE15, m_v_voice15);
	DDX_Control(pDX, IDC_V_VOICE16, m_v_voice16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Delete_MIDI_Events, CDialog)
	//{{AFX_MSG_MAP(Delete_MIDI_Events)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_BN_CLICKED(IDC_CHECK9, OnCheck9)
	ON_BN_CLICKED(IDC_CHECK10, OnCheck10)
	ON_BN_CLICKED(IDC_CHECK11, OnCheck11)
	ON_BN_CLICKED(IDC_CHECK12, OnCheck12)
	ON_BN_CLICKED(IDC_CHECK13, OnCheck13)
	ON_BN_CLICKED(IDC_CHECK14, OnCheck14)
	ON_BN_CLICKED(IDC_CHECK15, OnCheck15)
	ON_BN_CLICKED(IDC_CHECK16, OnCheck16)
	ON_BN_CLICKED(IDC_CHECK_ALL, OnCheck_All)
	ON_CBN_SELCHANGE(IDC_MIDI_EVENT_COMBOBOX, OnSelchangeMidiEventCombobox)
	ON_BN_CLICKED(IDC_BEFORE_NOTES, OnBeforeNotes)
	ON_BN_CLICKED(IDC_NOTE_AREA, OnNoteArea)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Delete_MIDI_Events 

BOOL Delete_MIDI_Events::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int ch, i;
	
	SetDlgItemText(IDC_VKANAL,GlobalUtilities::get_resource_string(IDS_CHANNEL));
	SetDlgItemText(IDC_VK1,"1");
	SetDlgItemText(IDC_VK2,"2");
	SetDlgItemText(IDC_VK3,"3");
	SetDlgItemText(IDC_VK4,"4");
	SetDlgItemText(IDC_VK5,"5");
	SetDlgItemText(IDC_VK6,"6");
	SetDlgItemText(IDC_VK7,"7");
	SetDlgItemText(IDC_VK8,"8");
	SetDlgItemText(IDC_VK9,"9");
	SetDlgItemText(IDC_VK10,"10");
	SetDlgItemText(IDC_VK11,"11");
	SetDlgItemText(IDC_VK12,"12");
	SetDlgItemText(IDC_VK13,"13");
	SetDlgItemText(IDC_VK14,"14");
	SetDlgItemText(IDC_VK15,"15");
	SetDlgItemText(IDC_VK16,"16");

	SetDlgItemText(IDC_VOICE,"Voice");
	SetDlgItemText(IDC_SELECT_CHAN,GlobalUtilities::get_resource_string(IDS_SELECT));
	SetDlgItemText(IDC_MIDI_EVENT,"MIDI Event");
	SetDlgItemText(IDC_NUMBER,GlobalUtilities::get_resource_string(IDS_NUMBER));
	SetDlgItemText(IDC_EDIT_NOTE_AREA,GlobalUtilities::get_resource_string(IDS_NOTE_AREA));
	SetDlgItemText(IDC_EDIT_BEFORE_NOTES,GlobalUtilities::get_resource_string(IDS_BEFORE_NOTES));
	
	for (ch=0; ch<16; ch++)
	{

		m_voice_type[ch]->SetLimitText(3);

		if (!(hpmfi->mute)[ch])
		{
			SetDlgItemText(idc_voice_type[ch],(hpmfi->patchname)[ch]);
		}
		else
		{
			m_voice_type[ch]->EnableWindow(false);
			SetDlgItemText(idc_voice_type[ch],"");
			checklist[ch]->DestroyWindow();
			checklist[ch] = NULL;
		}
		SetDlgItemInt(idc_no_list[ch],0);
	}

	SetDlgItemInt(idc_no_list[16],0);

	

	// Tool Tips
	if (hpmfi->with_insdef)
	{
		m_pToolTip = new CToolTipCtrl;
		m_pToolTip->Create(this);
		m_pToolTip->SetDelayTime(TTDT_AUTOPOP,4000);
		m_pToolTip->SetMaxTipWidth(200);

		for (ch=0; ch<16; ch++)
		{			
			if ((hpmfi->mlv_list[ch]).voicename == "") continue;
			m_pToolTip->AddTool(m_voice_type[ch],(hpmfi->mlv_list[ch]).voicename);
		}
		m_pToolTip->Activate(true);
	}

	for (i=0; i<NO_MIDI_EVENTS; i++)
	{
		m_midi_event_combobox.InsertString(i,GlobalUtilities::midi_event_list[i].name);
	}

	fill_no_midi_events_list();
	
	m_before_notes.SetCheck(0);
	before_notes_checked = false;
	m_note_area.SetCheck(1);
	note_area_checked = true;

 	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void Delete_MIDI_Events::OnClose() 
{
	EndDialog(0);
}


void Delete_MIDI_Events::OnCancel() 
{
	EndDialog(0);
}

void Delete_MIDI_Events::OnOK() 
{
	int chan;
	bool chan_selected = false;

	for (chan=0; chan<16; chan++)
	{
		if (is_checked[chan])
		{
			chan_selected = true;
			break;
		}
	}
	if ((event_type == -1) || ((event_type != HP_SYSEX) && (!chan_selected)))
	{
		return;
	}

	EndDialog(1);
}

BOOL Delete_MIDI_Events::PreTranslateMessage(MSG* pMsg) 
{
	if (NULL != m_pToolTip)
	{
		m_pToolTip->RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void Delete_MIDI_Events::fill_no_midi_events_list()
{
	int id, chan, time, type, number, value;
	int i = 0;
	bool first_note_arrived = false;
	HP_Rewind(hpmfi->mf); 
	while (HP_ReadEvent(hpmfi->mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE)
		{
			first_note_arrived = true;
			continue;
		}

		if ((chan < 0) && (type != HP_SYSEX))
		{
			continue;
		}

		
		for (i=0; i<NO_MIDI_EVENTS; i++)
		{

			if (type != GlobalUtilities::midi_event_list[i].event_type)
			{
				continue;
			}

			if ((GlobalUtilities::midi_event_list[i].number == -1) && 
				(GlobalUtilities::midi_event_list[i].event_type != HP_SYSEX))
			{
				(no_midi_events_list[chan])[i] = (no_midi_events_list[chan])[i]+1;
				if (first_note_arrived)
				{
					(no_midi_events_note_area_list[chan])[i] = (no_midi_events_note_area_list[chan])[i]+1;
				}
				else
				{
					(no_midi_events_before_notes_list[chan])[i] = (no_midi_events_before_notes_list[chan])[i]+1;
				}
				continue;
			}

			if (GlobalUtilities::midi_event_list[i].event_type == HP_SYSEX)
			{
				(no_midi_events_list[16])[i] = (no_midi_events_list[16])[i]+1;
				if (first_note_arrived)
				{
					(no_midi_events_note_area_list[16])[i] = (no_midi_events_note_area_list[16])[i]+1; 
				}
				else
				{
					(no_midi_events_before_notes_list[16])[i] = (no_midi_events_before_notes_list[16])[i]+1;
				}
				continue;
			}

			HP_ReadController(hpmfi->mf,id, &time, &chan, &number, &value);

			if (number != GlobalUtilities::midi_event_list[i].number)
			{
				continue;
			}
			(no_midi_events_list[chan])[i] = (no_midi_events_list[chan])[i]+1;
			if (first_note_arrived)
			{
				(no_midi_events_note_area_list[chan])[i] = (no_midi_events_note_area_list[chan])[i]+1;
			}
			else
			{
				(no_midi_events_before_notes_list[chan])[i] = (no_midi_events_before_notes_list[chan])[i]+1;
			}
		}
	}
}

void Delete_MIDI_Events::checked(int chan, bool is)
{
	int index = m_midi_event_combobox.GetCurSel();

	if (index >= 0)
	{
		if (GlobalUtilities::midi_event_list[index].event_type == HP_SYSEX)
		{
			int i;
			checklist[16]->SetCheck(0);
			for (i=0; i<16; i++)
			{
				if(checklist[i]==NULL)
				{
					continue;
				}
				is_checked[i] = false;
				checklist[i]->SetCheck(0);
			}
		}
	}

	if (GlobalUtilities::midi_event_list[index].event_type != HP_SYSEX)
	{
		is_checked[chan] = is;
	}
}

void Delete_MIDI_Events::OnCheck1() 
{
	int state = m_check1.GetCheck();
	checked(0,state==1);
}

void Delete_MIDI_Events::OnCheck2() 
{
	int state = m_check2.GetCheck();
	checked(1,state==1);
}

void Delete_MIDI_Events::OnCheck3() 
{
	int state = m_check3.GetCheck();
	checked(2,state==1);
}

void Delete_MIDI_Events::OnCheck4() 
{
	int state = m_check4.GetCheck();
	checked(3,state==1);
}
void Delete_MIDI_Events::OnCheck5() 
{
	int state = m_check5.GetCheck();
	checked(4,state==1);
}
void Delete_MIDI_Events::OnCheck6() 
{
	int state = m_check6.GetCheck();
	checked(5,state==1);
}
void Delete_MIDI_Events::OnCheck7() 
{
	int state = m_check7.GetCheck();
	checked(6,state==1);
}
void Delete_MIDI_Events::OnCheck8() 
{
	int state = m_check8.GetCheck();
	checked(7,state==1);
}
void Delete_MIDI_Events::OnCheck9() 
{
	int state = m_check9.GetCheck();
	checked(8,state==1);
}
void Delete_MIDI_Events::OnCheck10() 
{
	int state = m_check10.GetCheck();
	checked(9,state==1);
}
void Delete_MIDI_Events::OnCheck11() 
{
	int state = m_check11.GetCheck();
	checked(10,state==1);
}
void Delete_MIDI_Events::OnCheck12() 
{
	int state = m_check12.GetCheck();
	checked(11,state==1);
}
void Delete_MIDI_Events::OnCheck13() 
{
	int state = m_check13.GetCheck();
	checked(12,state==1);
}
void Delete_MIDI_Events::OnCheck14() 
{
	int state = m_check14.GetCheck();
	checked(13,state==1);
}
void Delete_MIDI_Events::OnCheck15() 
{
	int state = m_check15.GetCheck();
	checked(14,state==1);
}
void Delete_MIDI_Events::OnCheck16() 
{
	int state = m_check16.GetCheck();
	checked(15,state==1);
}

void Delete_MIDI_Events::OnCheck_All() 
{
	int state = m_check_all.GetCheck();
	int ch;
	for (ch=0; ch<16; ch++)
	{
		if (checklist[ch]==NULL)
		{
			continue;
		}
		checklist[ch]->SetCheck(state);
		checked(ch,state==1);
	}
}

void Delete_MIDI_Events::OnSelchangeMidiEventCombobox() 
{
	int chan;
	int no_all = 0;
	int index = m_midi_event_combobox.GetCurSel();
	bool all_notes_checked = before_notes_checked && note_area_checked;

	if (!before_notes_checked && !note_area_checked)
	{
		for (chan=0; chan<16; chan++)
		{
			SetDlgItemInt(idc_no_list[chan],0);
		}
		SetDlgItemInt(IDC_NO_ALL,0);
		return;
	}

	if ((GlobalUtilities::midi_event_list[index]).event_type == HP_SYSEX )
	{
		for (chan=0; chan<16; chan++)
		{
			SetDlgItemInt(idc_no_list[chan],0);
			if (checklist[chan]!=NULL)
			{
				checklist[chan]->SetCheck(0);
			}
		}
		m_check_all.SetCheck(0);
		all_notes_checked = false;

		SetDlgItemInt(IDC_NO_ALL, (no_midi_events_list[16])[index]);
		m_check_all.SetCheck(0);

		int number_all = 0;

		if (before_notes_checked && note_area_checked)
		{
			number_all = (no_midi_events_before_notes_list[16])[index] +
						 (no_midi_events_note_area_list[16])[index];
		}
		else
		{
			if (before_notes_checked)
			{
				number_all = (no_midi_events_before_notes_list[16])[index];
			}
			else
			{
				number_all = (no_midi_events_note_area_list[16])[index];
			}
		}

		SetDlgItemInt(IDC_NO_ALL, number_all);

	}
	else
	{
		for (chan=0; chan<16; chan++)
		{
			int no;

			if (all_notes_checked)
			{
				no = (no_midi_events_list[chan])[index];
			}
			else
			{
				if (before_notes_checked)
				{
					no = (no_midi_events_before_notes_list[chan])[index];
				}
				else
				{
					no =(no_midi_events_note_area_list[chan])[index];
				}
			}
			no_all += no;
			SetDlgItemInt(idc_no_list[chan],no);
		}
	}

	if ((GlobalUtilities::midi_event_list[index]).event_type != HP_SYSEX)
	{
		SetDlgItemInt(IDC_NO_ALL, no_all);
	}

	event_type = (GlobalUtilities::midi_event_list[index]).event_type;
	ctrl_number = (GlobalUtilities::midi_event_list[index]).number;
}

void Delete_MIDI_Events::OnBeforeNotes() 
{
	before_notes_checked = (m_before_notes.GetCheck()==1);
	if (event_type != -1)
	{
		OnSelchangeMidiEventCombobox();
	}
}

void Delete_MIDI_Events::OnNoteArea() 
{
	note_area_checked = (m_note_area.GetCheck()==1);		
	if (event_type != -1)
	{
		OnSelchangeMidiEventCombobox();
	}
}
