// SlctChordChan.cpp: Implementation
//

#include "stdafx.h"
#include "Resource.h"
#include "SlctChordChan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld SlctChordChan


SlctChordChan::SlctChordChan(CWnd* pParent /*=NULL*/)
	: CDialog(SlctChordChan::IDD, pParent)
{
	//{{AFX_DATA_INIT(SlctChordChan)
	//}}AFX_DATA_INIT
	int i;

	check_list[0] = &m_check_chan_1;
	check_list[1] = &m_check_chan_2;
	check_list[2] = &m_check_chan_3;
	check_list[3] = &m_check_chan_4;
	check_list[4] = &m_check_chan_5;
	check_list[5] = &m_check_chan_6;
	check_list[6] = &m_check_chan_7;
	check_list[7] = &m_check_chan_8;
	check_list[8] = &m_check_chan_9;
	check_list[9] = &m_check_chan_10;
	check_list[10] = &m_check_chan_11;
	check_list[11] = &m_check_chan_12;
	check_list[12] = &m_check_chan_13;
	check_list[13] = &m_check_chan_14;
	check_list[14] = &m_check_chan_15;
	check_list[15] = &m_check_chan_16;
	check_list[16] = &m_check_chan_all;
	bass_check_list[0] = &m_check_bass_1;
	bass_check_list[1] = &m_check_bass_2;
	bass_check_list[2] = &m_check_bass_3;
	bass_check_list[3] = &m_check_bass_4;
	bass_check_list[4] = &m_check_bass_5;
	bass_check_list[5] = &m_check_bass_6;
	bass_check_list[6] = &m_check_bass_7;
	bass_check_list[7] = &m_check_bass_8;
	bass_check_list[8] = &m_check_bass_9;
	bass_check_list[9] = &m_check_bass_10;
	bass_check_list[10] = &m_check_bass_11;
	bass_check_list[11] = &m_check_bass_12;
	bass_check_list[12] = &m_check_bass_13;
	bass_check_list[13] = &m_check_bass_14;
	bass_check_list[14] = &m_check_bass_15;
	bass_check_list[15] = &m_check_bass_16;
	
	all_selected = false;
	multi_selected = false;
	single_selected = false;
	bass_channel = -1;

 	// init: no chan selected
	for (i=0; i<16; i++)
	{
		chan_list[i] = false;
	}
}


void SlctChordChan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SlctChordChan)
	DDX_Control(pDX, IDC_CHORD_PATCH1, m_chord_patch1);
	DDX_Control(pDX, IDC_CHORD_PATCH2, m_chord_patch2);
	DDX_Control(pDX, IDC_CHORD_PATCH3, m_chord_patch3);
	DDX_Control(pDX, IDC_CHORD_PATCH4, m_chord_patch4);
	DDX_Control(pDX, IDC_CHORD_PATCH5, m_chord_patch5);
	DDX_Control(pDX, IDC_CHORD_PATCH6, m_chord_patch6);
	DDX_Control(pDX, IDC_CHORD_PATCH7, m_chord_patch7);
	DDX_Control(pDX, IDC_CHORD_PATCH8, m_chord_patch8);
	DDX_Control(pDX, IDC_CHORD_PATCH9, m_chord_patch9);
	DDX_Control(pDX, IDC_CHORD_PATCH10, m_chord_patch10);
	DDX_Control(pDX, IDC_CHORD_PATCH11, m_chord_patch11);
	DDX_Control(pDX, IDC_CHORD_PATCH12, m_chord_patch12);
	DDX_Control(pDX, IDC_CHORD_PATCH13, m_chord_patch13);
	DDX_Control(pDX, IDC_CHORD_PATCH14, m_chord_patch14);
	DDX_Control(pDX, IDC_CHORD_PATCH15, m_chord_patch15);
	DDX_Control(pDX, IDC_CHORD_PATCH16, m_chord_patch16);
	DDX_Control(pDX, IDC_CHECK_PROT_CHORDS_LYRIC, m_prot_chords_lyric);
	DDX_Control(pDX, IDC_CHECK_CHAN_1, m_check_chan_1);
	DDX_Control(pDX, IDC_CHECK_CHAN_2, m_check_chan_2);
	DDX_Control(pDX, IDC_CHECK_CHAN_3, m_check_chan_3);
	DDX_Control(pDX, IDC_CHECK_CHAN_4, m_check_chan_4);
	DDX_Control(pDX, IDC_CHECK_CHAN_5, m_check_chan_5);
	DDX_Control(pDX, IDC_CHECK_CHAN_6, m_check_chan_6);
	DDX_Control(pDX, IDC_CHECK_CHAN_7, m_check_chan_7);
	DDX_Control(pDX, IDC_CHECK_CHAN_8, m_check_chan_8);
	DDX_Control(pDX, IDC_CHECK_CHAN_9, m_check_chan_9);
	DDX_Control(pDX, IDC_CHECK_CHAN_10, m_check_chan_10);
	DDX_Control(pDX, IDC_CHECK_CHAN_11, m_check_chan_11);
	DDX_Control(pDX, IDC_CHECK_CHAN_12, m_check_chan_12);
	DDX_Control(pDX, IDC_CHECK_CHAN_13, m_check_chan_13);
	DDX_Control(pDX, IDC_CHECK_CHAN_14, m_check_chan_14);
	DDX_Control(pDX, IDC_CHECK_CHAN_15, m_check_chan_15);
	DDX_Control(pDX, IDC_CHECK_CHAN_16, m_check_chan_16);
	DDX_Control(pDX, IDC_CHECK_CHAN_ALL, m_check_chan_all);
	DDX_Control(pDX, IDC_CHECK_BASS1, m_check_bass_1);
	DDX_Control(pDX, IDC_CHECK_BASS2, m_check_bass_2);
	DDX_Control(pDX, IDC_CHECK_BASS3, m_check_bass_3);
	DDX_Control(pDX, IDC_CHECK_BASS4, m_check_bass_4);
	DDX_Control(pDX, IDC_CHECK_BASS5, m_check_bass_5);
	DDX_Control(pDX, IDC_CHECK_BASS6, m_check_bass_6);
	DDX_Control(pDX, IDC_CHECK_BASS7, m_check_bass_7);
	DDX_Control(pDX, IDC_CHECK_BASS8, m_check_bass_8);
	DDX_Control(pDX, IDC_CHECK_BASS9, m_check_bass_9);
	DDX_Control(pDX, IDC_CHECK_BASS10, m_check_bass_10);
	DDX_Control(pDX, IDC_CHECK_BASS11, m_check_bass_11);
	DDX_Control(pDX, IDC_CHECK_BASS12, m_check_bass_12);
	DDX_Control(pDX, IDC_CHECK_BASS13, m_check_bass_13);
	DDX_Control(pDX, IDC_CHECK_BASS14, m_check_bass_14);
	DDX_Control(pDX, IDC_CHECK_BASS15, m_check_bass_15);
	DDX_Control(pDX, IDC_CHECK_BASS16, m_check_bass_16);
	DDX_Control(pDX, IDC_CHECK_PROT_CHORDS, m_prot_chords);
	DDX_Control(pDX, IDC_CHECK_INSERT_CHORDS, m_insert_chords);
	DDX_Control(pDX, IDC_CHECK_SYSEX_CHORDS, m_sysex_chords);
	DDX_Control(pDX, IDC_CHECK_SIMPLE, m_simple_chord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SlctChordChan, CDialog)
	//{{AFX_MSG_MAP(SlctChordChan)
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_BN_CLICKED(IDC_CHECK_PROT_CHORDS, OnCheckProtChords)
	ON_BN_CLICKED(IDC_CHECK_INSERT_CHORDS, OnCheckInsertChords)
	ON_BN_CLICKED(IDC_CHECK_CHAN_1, OnCheckChan1)
	ON_BN_CLICKED(IDC_CHECK_CHAN_2, OnCheckChan2)
	ON_BN_CLICKED(IDC_CHECK_CHAN_3, OnCheckChan3)
	ON_BN_CLICKED(IDC_CHECK_CHAN_4, OnCheckChan4)
	ON_BN_CLICKED(IDC_CHECK_CHAN_5, OnCheckChan5)
	ON_BN_CLICKED(IDC_CHECK_CHAN_6, OnCheckChan6)
	ON_BN_CLICKED(IDC_CHECK_CHAN_7, OnCheckChan7)
	ON_BN_CLICKED(IDC_CHECK_CHAN_8, OnCheckChan8)
	ON_BN_CLICKED(IDC_CHECK_CHAN_9, OnCheckChan9)
	ON_BN_CLICKED(IDC_CHECK_CHAN_10, OnCheckChan10)
	ON_BN_CLICKED(IDC_CHECK_CHAN_11, OnCheckChan11)
	ON_BN_CLICKED(IDC_CHECK_CHAN_12, OnCheckChan12)
	ON_BN_CLICKED(IDC_CHECK_CHAN_13, OnCheckChan13)
	ON_BN_CLICKED(IDC_CHECK_CHAN_14, OnCheckChan14)
	ON_BN_CLICKED(IDC_CHECK_CHAN_15, OnCheckChan15)
	ON_BN_CLICKED(IDC_CHECK_CHAN_16, OnCheckChan16)
	ON_BN_CLICKED(IDC_CHECK_CHAN_ALL, OnCheckChanAll)
	ON_BN_CLICKED(IDC_CHECK_BASS1, OnCheckBass1)
	ON_BN_CLICKED(IDC_CHECK_BASS2, OnCheckBass2)
	ON_BN_CLICKED(IDC_CHECK_BASS3, OnCheckBass3)
	ON_BN_CLICKED(IDC_CHECK_BASS4, OnCheckBass4)
	ON_BN_CLICKED(IDC_CHECK_BASS5, OnCheckBass5)
	ON_BN_CLICKED(IDC_CHECK_BASS6, OnCheckBass6)
	ON_BN_CLICKED(IDC_CHECK_BASS7, OnCheckBass7)
	ON_BN_CLICKED(IDC_CHECK_BASS8, OnCheckBass8)
	ON_BN_CLICKED(IDC_CHECK_BASS9, OnCheckBass9)
	ON_BN_CLICKED(IDC_CHECK_BASS10, OnCheckBass10)
	ON_BN_CLICKED(IDC_CHECK_BASS11, OnCheckBass11)
	ON_BN_CLICKED(IDC_CHECK_BASS12, OnCheckBass12)
	ON_BN_CLICKED(IDC_CHECK_BASS13, OnCheckBass13)
	ON_BN_CLICKED(IDC_CHECK_BASS14, OnCheckBass14)
	ON_BN_CLICKED(IDC_CHECK_BASS15, OnCheckBass15)
	ON_BN_CLICKED(IDC_CHECK_BASS16, OnCheckBass16)
	ON_BN_CLICKED(IDC_CHECK_PROT_CHORDS_LYRIC, OnCheckProtChordsLyric)
	ON_BN_CLICKED(IDC_CHECK_SIMPLE, OnCheckSimple)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten SlctChordChan

void SlctChordChan::OnCancel()
{
	chords_save  = false;
	chords_print = false;
	chords_print_lyric = false;
	EndDialog(-1);
}

BOOL SlctChordChan::OnInitDialog()
{
	int i;

	CDialog::OnInitDialog();

	m_pToolTip = NULL;

	CEdit* patch_list[16] =
	{
		&m_chord_patch1,
		&m_chord_patch2,
		&m_chord_patch3,
		&m_chord_patch4,
		&m_chord_patch5,
		&m_chord_patch6,
		&m_chord_patch7,
		&m_chord_patch8,
		&m_chord_patch9,
		&m_chord_patch10,
		&m_chord_patch11,
		&m_chord_patch12,
		&m_chord_patch13,
		&m_chord_patch14,
		&m_chord_patch15,
		&m_chord_patch16
	};


	int chord_voiceIDClist[NO_CHORDLIST_CHAN] =
	{
		IDC_CHORD_PATCH1,
		IDC_CHORD_PATCH2,
		IDC_CHORD_PATCH3,
		IDC_CHORD_PATCH4,
		IDC_CHORD_PATCH5,
		IDC_CHORD_PATCH6,
		IDC_CHORD_PATCH7,
		IDC_CHORD_PATCH8,
		IDC_CHORD_PATCH9,
		IDC_CHORD_PATCH10,
		IDC_CHORD_PATCH11,
		IDC_CHORD_PATCH12,
		IDC_CHORD_PATCH13,
		IDC_CHORD_PATCH14,
		IDC_CHORD_PATCH15,
		IDC_CHORD_PATCH16,
		IDC_CHORD_PATCHALL,
		IDC_CHORD_GROUP,
	};

	int no_chordIDClist[NO_CHORDLIST_CHAN] =
	{
		IDC_CHORD_NO1,
		IDC_CHORD_NO2,
		IDC_CHORD_NO3,
		IDC_CHORD_NO4,
		IDC_CHORD_NO5,
		IDC_CHORD_NO6,
		IDC_CHORD_NO7,
		IDC_CHORD_NO8,
		IDC_CHORD_NO9,
		IDC_CHORD_NO10,
		IDC_CHORD_NO11,
		IDC_CHORD_NO12,
		IDC_CHORD_NO13,
		IDC_CHORD_NO14,
		IDC_CHORD_NO15,
		IDC_CHORD_NO16,
		IDC_CHORD_NOALL,
		IDC_CHORD_NOGROUP
	};

	allowed_selection[CHORD_INDEX_ALL] = true;	// all

	for (i=0; i<16; i++)
	{
//		if (((hpmfi->mute)[i])||(!(hpmfi->mlv_list)[i].melody)||(hpmfi->mlv_list)[i].is_mega)
		if (((hpmfi->mute)[i])||(!(hpmfi->mlv_list)[i].melody))
		{
			allowed_selection[i] = false;
		}
		else
		{
			CString pn = (hpmfi->patchname)[i];
			pn.Remove(' ');
			SetDlgItemText(chord_voiceIDClist[i],pn);
			allowed_selection[i] = true;
		}


/*
		(hpmfi->lf)->add("chan %i, mute %i, melody %i",
			i,
			(hpmfi->mute)[i],
			(hpmfi->mlv_list)[i].melody
			);
*/
	}

	for (i=0; i<17; i++)
	{		
		check_list[i]->EnableWindow(allowed_selection[i]);
		check_list[i]->SetCheck(0);		 // irrelevant
		if (i<16)
		{
			bass_check_list[i]->EnableWindow(allowed_selection[i]);
			bass_check_list[i]->SetCheck(0); // irrelevant
		}
	}
	
	SetDlgItemText(chord_voiceIDClist[CHORD_INDEX_SEL],
		GlobalUtilities::get_resource_string(IDS_SELECTION));

	for (i=0; i<NO_CHORDLIST_CHAN; i++)
	{
		if (i < 16)
		{ // only chord channels
			if (!allowed_selection[i])
			{
				continue;
			}
		}
		SetDlgItemInt(no_chordIDClist[i],no_list[i],FALSE);
	}

	m_simple_chord.SetCheck(1);		// Select simple chords
	is_simple_chords = true;
	m_sysex_chords.SetCheck(0);		// No SysEx chord events
	m_insert_chords.SetCheck(1);	// Select Insert Chords
	m_prot_chords.SetCheck(0);		// No protocol as XF chords
	m_prot_chords_lyric.SetCheck(0);// No protocol as lyrics 

	// Tool Tips
	if (hpmfi->with_insdef)
	{
		int chan;
		m_pToolTip = new CToolTipCtrl;
		m_pToolTip->Create(this);
		m_pToolTip->SetDelayTime(TTDT_AUTOPOP,4000);
		m_pToolTip->SetMaxTipWidth(200);
		for (chan=0; chan<16; chan++)
		{
			if (!(hpmfi->mlv_list[chan]).melody) continue;
			if ((hpmfi->mlv_list[chan]).voicename == "") continue;
			m_pToolTip->AddTool(patch_list[chan],(hpmfi->mlv_list[chan]).voicename);
		}
		m_pToolTip->Activate(true);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

BOOL SlctChordChan::PreTranslateMessage(MSG* pMsg) 
{
	if (NULL != m_pToolTip)
	{
		m_pToolTip->RelayEvent(pMsg);
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}


void SlctChordChan::check_chan_event(int list_index, bool on)
{
//	CString r;
//	r.Format("check_chan_event: list_index %i, %s",list_index,on?"On":"Off");
//	::MessageBox(AfxGetMainWnd()->m_hWnd,r,"Test",MB_OK|MB_TASKMODAL);

	int i;

	if (list_index==CHORD_INDEX_ALL)
	{
		if (on)
		{
			for (i=0; i<16; i++)
			{
				if (allowed_selection[i])
				{
					if (bass_check_list[i]->GetCheck()==0)
					{
						check_list[i]->SetCheck(1);
						chan_list[i] = true;
					}
				}
				else
				{
					check_list[i]->SetCheck(0);
					chan_list[i] = false;
				}
			}
			all_selected = true;
			multi_selected = false;
			single_selected = false;
			// all selected, display the number of all
			hpmfi->pre_eval_chords(no_list, chan_list,is_simple_chords,bass_channel);

			SetDlgItemInt(IDC_CHORD_NOGROUP,no_list[16],FALSE);
		}
		else
		{
			for (i=0; i<16; i++)
			{
				check_list[i]->SetCheck(0);
				chan_list[i] = false;
			}
			all_selected = false;
			multi_selected = false;
			single_selected = false;
			SetDlgItemInt(IDC_CHORD_NOGROUP,0,FALSE);
		}
		return;
	}


	// one channel switched on or off:
	if (all_selected)
	{	// only if "All" checked on
		check_list[16]->SetCheck(0);
	}

	all_selected = false;
	chan_list[list_index] = on; // switched on or off


	// look for selected channels
	int no_selected = 0;
	int ix; // actual index, for single_selected only
	for (i=0; i<16; i++)
	{
		if (chan_list[i]) 
		{
			no_selected++;
			ix = i; 
		}
	}

	if (no_selected==0)
	{
		multi_selected = false;
		single_selected = false;
		SetDlgItemInt(IDC_CHORD_NOGROUP,0,FALSE);
	}
	else
	if (no_selected==1)
	{
		multi_selected = false;
		single_selected = true;
		single_chan = ix;
		SetDlgItemInt(IDC_CHORD_NOGROUP,no_list[ix],FALSE);
	}
	else // no_selected > 1
	{	
		multi_selected = true;
		single_selected = false;
		hpmfi->pre_eval_chords(no_list, chan_list,is_simple_chords,bass_channel);
		SetDlgItemInt(IDC_CHORD_NOGROUP,no_list[CHORD_INDEX_SEL],FALSE);
	}
}


void SlctChordChan::check_bass_event(int list_index, bool on)
{
	int i;
/*
	CString r;
	r.Format("check_bass_event: list_index %i, %s",list_index,on?"On":"Off");
	::MessageBox(AfxGetMainWnd()->m_hWnd,r,"Test",MB_OK|MB_TASKMODAL);
*/
	if (on)
	{
		for (i=0; i<16; i++)
		{
			if (i == list_index) continue;
			bass_check_list[i]->SetCheck(0); // irrelevant
		}

		if(	(!all_selected && !multi_selected && !single_selected) ||
			(single_selected && (check_list[list_index]->GetCheck()==1)))
		{
			bass_check_list[list_index]->SetCheck(0); 
			bass_channel = -1;
			check_list[list_index]->EnableWindow(true);
		}
		else
		{
			check_list[list_index]->SetCheck(0);
			check_chan_event(list_index,false);
			check_list[list_index]->EnableWindow(false);
			bass_channel = list_index;
		}
	}
	else
	{
		check_list[list_index]->EnableWindow(true);
		check_chan_event(list_index,false);
		bass_channel = -1;
	}
	hpmfi->pre_eval_chords(no_list, chan_list,is_simple_chords,bass_channel);
	SetDlgItemInt(IDC_CHORD_NOGROUP,no_list[CHORD_INDEX_SEL],FALSE);
}


void SlctChordChan::get_chan_list(bool chan_l[16])
{
	int i;
	for (i=0; i<16; i++)
	{
		chan_l[i] = chan_list[i];
	}
}


void SlctChordChan::OnOk()
{
	if (m_prot_chords.GetCheck()==1)
	{
		chords_save  = false;
		chords_print = true;
		chords_print_lyric = false;
	}
	if (m_prot_chords_lyric.GetCheck()==1)
	{
		chords_save  = false;
		chords_print = false;
		chords_print_lyric = true;
	}
	if (m_insert_chords.GetCheck()==1)
	{
		chords_save  = true;
		chords_print = false;
		chords_print_lyric = false;
	}
	hpmfi->is_simple_chords = is_simple_chords;
	hpmfi->is_sysex_chords = (m_sysex_chords.GetCheck()==1)?true: false;
	
	int ret = all_selected?16:multi_selected?17:single_selected?single_chan:-1;
	EndDialog(ret);
}


void SlctChordChan::OnCheckProtChords()
{
	int check = m_prot_chords.GetCheck();
	m_insert_chords.SetCheck(check==0?1:0);
	m_prot_chords_lyric.SetCheck(0);
	m_sysex_chords.SetCheck(0);
}

void SlctChordChan::OnCheckProtChordsLyric() 
{
	int check = m_prot_chords_lyric.GetCheck();
	m_insert_chords.SetCheck(check==0?1:0);
	m_insert_chords.SetCheck(check==0?1:0);
	m_prot_chords.SetCheck(0);
	m_sysex_chords.SetCheck(0);
}

void SlctChordChan::OnCheckInsertChords()
{
	int check = m_insert_chords.GetCheck();
	m_prot_chords.SetCheck(check==0?1:0);
	m_prot_chords_lyric.SetCheck(0);
	m_sysex_chords.SetCheck(0);
}

void SlctChordChan::OnCheckChan1() 
{
	check_chan_event(0,m_check_chan_1.GetCheck()==1);
}

void SlctChordChan::OnCheckChan2() 
{
	check_chan_event(1,m_check_chan_2.GetCheck()==1);
}

void SlctChordChan::OnCheckChan3() 
{
	check_chan_event(2,m_check_chan_3.GetCheck()==1);
}

void SlctChordChan::OnCheckChan4() 
{
	check_chan_event(3,m_check_chan_4.GetCheck()==1);
}

void SlctChordChan::OnCheckChan5() 
{
	check_chan_event(4,m_check_chan_5.GetCheck()==1);
}

void SlctChordChan::OnCheckChan6() 
{
	check_chan_event(5,m_check_chan_6.GetCheck()==1);
}

void SlctChordChan::OnCheckChan7() 
{
	check_chan_event(6,m_check_chan_7.GetCheck()==1);
}

void SlctChordChan::OnCheckChan8() 
{
	check_chan_event(7,m_check_chan_8.GetCheck()==1);
}

void SlctChordChan::OnCheckChan9() 
{
	check_chan_event(8,m_check_chan_9.GetCheck()==1);
}
void SlctChordChan::OnCheckChan10() 
{
	check_chan_event(9,m_check_chan_10.GetCheck()==1);
}

void SlctChordChan::OnCheckChan11() 
{
	check_chan_event(10,m_check_chan_11.GetCheck()==1);
}

void SlctChordChan::OnCheckChan12() 
{
	check_chan_event(11,m_check_chan_12.GetCheck()==1);
}

void SlctChordChan::OnCheckChan13() 
{
	check_chan_event(12,m_check_chan_13.GetCheck()==1);
}

void SlctChordChan::OnCheckChan14() 
{
	check_chan_event(13,m_check_chan_14.GetCheck()==1);
}

void SlctChordChan::OnCheckChan15() 
{
	check_chan_event(14,m_check_chan_15.GetCheck()==1);
}

void SlctChordChan::OnCheckChan16() 
{
	check_chan_event(15,m_check_chan_16.GetCheck()==1);
}

void SlctChordChan::OnCheckChanAll() 
{
	check_chan_event(16,m_check_chan_all.GetCheck()==1);
}


void SlctChordChan::OnCheckBass1() 
{
	check_bass_event(0,m_check_bass_1.GetCheck()==1);
}

void SlctChordChan::OnCheckBass2() 
{
	check_bass_event(1,m_check_bass_2.GetCheck()==1);
}

void SlctChordChan::OnCheckBass3() 
{
	check_bass_event(2,m_check_bass_3.GetCheck()==1);
}

void SlctChordChan::OnCheckBass4() 
{
	check_bass_event(3,m_check_bass_4.GetCheck()==1);
}

void SlctChordChan::OnCheckBass5() 
{
	check_bass_event(4,m_check_bass_5.GetCheck()==1);
}

void SlctChordChan::OnCheckBass6() 
{
	check_bass_event(5,m_check_bass_6.GetCheck()==1);
}

void SlctChordChan::OnCheckBass7() 
{
	check_bass_event(6,m_check_bass_7.GetCheck()==1);
}

void SlctChordChan::OnCheckBass8() 
{
	check_bass_event(7,m_check_bass_8.GetCheck()==1);
}

void SlctChordChan::OnCheckBass9() 
{
	check_bass_event(8,m_check_bass_9.GetCheck()==1);
}
void SlctChordChan::OnCheckBass10() 
{
	check_bass_event(9,m_check_bass_10.GetCheck()==1);
}

void SlctChordChan::OnCheckBass11() 
{
	check_bass_event(10,m_check_bass_11.GetCheck()==1);
}

void SlctChordChan::OnCheckBass12() 
{
	check_bass_event(11,m_check_bass_12.GetCheck()==1);
}

void SlctChordChan::OnCheckBass13() 
{
	check_bass_event(12,m_check_bass_13.GetCheck()==1);
}

void SlctChordChan::OnCheckBass14() 
{
	check_bass_event(13,m_check_bass_14.GetCheck()==1);
}

void SlctChordChan::OnCheckBass15() 
{
	check_bass_event(14,m_check_bass_15.GetCheck()==1);
}

void SlctChordChan::OnCheckBass16() 
{
	check_bass_event(15,m_check_bass_16.GetCheck()==1);
}

void SlctChordChan::OnCheckSimple() 
{
	is_simple_chords = (m_simple_chord.GetCheck()==1)?true: false;
	hpmfi->pre_eval_chords(no_list, chan_list,is_simple_chords,bass_channel);
	SetDlgItemInt(IDC_CHORD_NOGROUP,no_list[CHORD_INDEX_SEL],FALSE);
}
