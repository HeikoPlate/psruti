// Delete_short_notes.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Delete_short_notes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Delete_short_notes 


Delete_short_notes::Delete_short_notes(CWnd* pParent /*=NULL*/)
	: CDialog(Delete_short_notes::IDD, pParent)
{
	//{{AFX_DATA_INIT(Delete_short_notes)
	//}}AFX_DATA_INIT

	int ch;
	for (ch = 0; ch < 16; ch++)
	{
		chan_list[ch] = 0;
		min_note_length[ch] = -1;
	}

    // initialize IDC Typetext-array

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

	m_pToolTip = NULL;

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

	upto_tick = -1;
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
}


void Delete_short_notes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(Delete_short_notes)
	DDX_Control(pDX, IDC_CHECK_ALL, m_check_all);
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
	DDX_Control(pDX, IDC_TICKS, m_ticks);
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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Delete_short_notes, CDialog)
	//{{AFX_MSG_MAP(Delete_short_notes)
	ON_EN_CHANGE(IDC_UPTO_TICK, OnChangeUptoTick)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_ALL, OnCheckAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Delete_short_notes 

BOOL Delete_short_notes::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int ch;
	
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
	SetDlgItemText(IDC_ALL,"All");
	SetDlgItemText(IDC_SELECT_CHAN,GlobalUtilities::get_resource_string(IDS_SELECT));
	SetDlgItemText(IDC_INCL,GlobalUtilities::get_resource_string(IDS_DELETE_UPTO));
	SetDlgItemText(IDC_TICKS,"Ticks");
	SetDlgItemText(IDC_VOICE,"Voice");
	SetDlgItemText(IDC_MIN_LENGTH,GlobalUtilities::get_resource_string(IDS_MIN_LENGTH));

	idclist_length[0] = IDC_MIN_LEN1;
	idclist_length[1] = IDC_MIN_LEN2;
	idclist_length[2] = IDC_MIN_LEN3;
	idclist_length[3] = IDC_MIN_LEN4;
	idclist_length[4] = IDC_MIN_LEN5;
	idclist_length[5] = IDC_MIN_LEN6;
	idclist_length[6] = IDC_MIN_LEN7;
	idclist_length[7] = IDC_MIN_LEN8;
	idclist_length[8] = IDC_MIN_LEN9;
	idclist_length[9] = IDC_MIN_LEN10;
	idclist_length[10] = IDC_MIN_LEN11;
	idclist_length[11] = IDC_MIN_LEN12;
	idclist_length[12] = IDC_MIN_LEN13;
	idclist_length[13] = IDC_MIN_LEN14;
	idclist_length[14] = IDC_MIN_LEN15;
	idclist_length[15] = IDC_MIN_LEN16;

	for (ch=0; ch<16; ch++)
	{
		if (!(hpmfi->mlv_list[ch]).melody || (hpmfi->mute)[ch])
		{
			checklist[ch]->DestroyWindow( );
			chan_list[ch] = -1; // channel not allowed
			checklist[ch] = NULL;
		}
	}

	int id, type, time;
	int note,velocity,length;

	HP_Rewind(hpmfi->mf);
	while (HP_ReadEvent(hpmfi->mf,&id,&ch,&time,&type)==HP_ERR_NONE)
	{
		if (type != HP_NOTE) continue;
		HP_ReadNote(hpmfi->mf,id,&time,&ch,&note,&velocity,&length);
		if((length<min_note_length[ch]) || (min_note_length[ch] < 0))
		{
			min_note_length[ch] = length;
		}
	}

	for (ch=0; ch<16; ch++)
	{
		if ((!hpmfi->mute[ch]) && (hpmfi->mlv_list[ch].melody))
		{
			if (min_note_length[ch]==-1)
			{
				SetDlgItemText(idclist_length[ch],"");
				checklist[ch]->DestroyWindow( );
			}
			else
			{
				SetDlgItemInt(idclist_length[ch],min_note_length[ch]);
			}
		}
		else
		{
			SetDlgItemText(idclist_length[ch],"");
		}
	}

	m_ticks.SetLimitText(3);
	SetDlgItemInt(IDC_UPTO_TICK,0);

	for (ch=0; ch<16; ch++)
	{
		if (!(hpmfi->mute)[ch])
		{
			SetDlgItemText(idc_voice_type[ch],(hpmfi->patchname)[ch]);
		}
		else
		{
			m_voice_type[ch]->EnableWindow(false);
			SetDlgItemText(idc_voice_type[ch],"");
		}
	}


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
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

BOOL Delete_short_notes::PreTranslateMessage(MSG* pMsg) 
{
	if (NULL != m_pToolTip)
	{
		m_pToolTip->RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void Delete_short_notes::OnChangeUptoTick() 
{
	int vel = GetDlgItemInt(IDC_UPTO_TICK);
	if (vel > 480)
	{
		SetDlgItemInt(IDC_UPTO_TICK,0);
	}
}

void Delete_short_notes::OnCancel() 
{
	EndDialog(0);
}

void Delete_short_notes::OnClose() 
{
	EndDialog(0);
}

void Delete_short_notes::OnOK() 
{
	int ch;
	bool chan_selected = false;
	upto_tick = GetDlgItemInt(IDC_UPTO_TICK);
	if (upto_tick < 0) return;
	for (ch=0; ch<16; ch++)
	{
		if (chan_list[ch] < 0)
		{
			continue;
		}
		if (checklist[ch]->GetCheck())
		{
			chan_list[ch] = 1;
			chan_selected = true;
		}
		else
		{
			chan_list[ch] = 0;
		}
	}
	if(!chan_selected) return;

	EndDialog(1);
}


void Delete_short_notes::OnCheckAll() 
{
	int ch;
	int checked =m_check_all.GetCheck();

	for (ch=0; ch<16; ch++)
	{
		if (checklist[ch] == NULL) 
		{
			continue;
		}
		checklist[ch]->SetCheck(checked);
	}
}
