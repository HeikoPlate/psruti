// Controller_Dlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Controller_Dlg.h"
#include "GlobalUtilities.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Controller_Dlg 


Controller_Dlg::Controller_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Controller_Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Controller_Dlg)
	//}}AFX_DATA_INIT
	m_pToolTip = NULL;


	value[0] = &m_edit_v1;
	value[1] = &m_edit_v2;
	value[2] = &m_edit_v3;
	value[3] = &m_edit_v4;
	value[4] = &m_edit_v5;
	value[5] = &m_edit_v6;
	value[6] = &m_edit_v7;
	value[7] = &m_edit_v8;
	value[8] = &m_edit_v9;
	value[9] = &m_edit_v10;
	value[10] = &m_edit_v11;
	value[11] = &m_edit_v12;
	value[12] = &m_edit_v13;
	value[13] = &m_edit_v14;
	value[14] = &m_edit_v15;
	value[15] = &m_edit_v16;

	idc_value[0] = IDC_EDIT_V1;
	idc_value[1] = IDC_EDIT_V2;
	idc_value[2] = IDC_EDIT_V3;
	idc_value[3] = IDC_EDIT_V4;
	idc_value[4] = IDC_EDIT_V5;
	idc_value[5] = IDC_EDIT_V6;
	idc_value[6] = IDC_EDIT_V7;
	idc_value[7] = IDC_EDIT_V8;
	idc_value[8] = IDC_EDIT_V9;
	idc_value[9] = IDC_EDIT_V10;
	idc_value[10] = IDC_EDIT_V11;
	idc_value[11] = IDC_EDIT_V12;
	idc_value[12] = IDC_EDIT_V13;
	idc_value[13] = IDC_EDIT_V14;
	idc_value[14] = IDC_EDIT_V15;
	idc_value[15] = IDC_EDIT_V16;

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
}


void Controller_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Controller_Dlg)
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
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_EDIT_ALL, m_edit_all);
	DDX_Control(pDX, IDC_EDIT_V1,m_edit_v1);
	DDX_Control(pDX, IDC_EDIT_V2,m_edit_v2);
	DDX_Control(pDX, IDC_EDIT_V3,m_edit_v3);
	DDX_Control(pDX, IDC_EDIT_V4,m_edit_v4);
	DDX_Control(pDX, IDC_EDIT_V5,m_edit_v5);
	DDX_Control(pDX, IDC_EDIT_V6,m_edit_v6);
	DDX_Control(pDX, IDC_EDIT_V7,m_edit_v7);
	DDX_Control(pDX, IDC_EDIT_V8,m_edit_v8);
	DDX_Control(pDX, IDC_EDIT_V9,m_edit_v9);
	DDX_Control(pDX, IDC_EDIT_V10,m_edit_v10);
	DDX_Control(pDX, IDC_EDIT_V11,m_edit_v11);
	DDX_Control(pDX, IDC_EDIT_V12,m_edit_v12);
	DDX_Control(pDX, IDC_EDIT_V13,m_edit_v13);
	DDX_Control(pDX, IDC_EDIT_V14,m_edit_v14);
	DDX_Control(pDX, IDC_EDIT_V15,m_edit_v15);
	DDX_Control(pDX, IDC_EDIT_V16,m_edit_v16);
	DDX_Control(pDX, IDC_EFFECTCOMBOBOX, m_effectcombobox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Controller_Dlg, CDialog)
	//{{AFX_MSG_MAP(Controller_Dlg)
	ON_CBN_SELCHANGE(IDC_EFFECTCOMBOBOX, OnSelchangeEffectcombobox)
	ON_EN_KILLFOCUS(IDC_EDIT_ALL, OnKillfocusEditAll)
	ON_EN_KILLFOCUS(IDC_EDIT_V1, OnKillfocusEditV1)
	ON_EN_KILLFOCUS(IDC_EDIT_V2, OnKillfocusEditV2)
	ON_EN_KILLFOCUS(IDC_EDIT_V3, OnKillfocusEditV3)
	ON_EN_KILLFOCUS(IDC_EDIT_V4, OnKillfocusEditV4)
	ON_EN_KILLFOCUS(IDC_EDIT_V5, OnKillfocusEditV5)
	ON_EN_KILLFOCUS(IDC_EDIT_V6, OnKillfocusEditV6)
	ON_EN_KILLFOCUS(IDC_EDIT_V7, OnKillfocusEditV7)
	ON_EN_KILLFOCUS(IDC_EDIT_V8, OnKillfocusEditV8)
	ON_EN_KILLFOCUS(IDC_EDIT_V9, OnKillfocusEditV9)
	ON_EN_KILLFOCUS(IDC_EDIT_V10, OnKillfocusEditV10)
	ON_EN_KILLFOCUS(IDC_EDIT_V11, OnKillfocusEditV11)
	ON_EN_KILLFOCUS(IDC_EDIT_V12, OnKillfocusEditV12)
	ON_EN_KILLFOCUS(IDC_EDIT_V13, OnKillfocusEditV13)
	ON_EN_KILLFOCUS(IDC_EDIT_V14, OnKillfocusEditV14)
	ON_EN_KILLFOCUS(IDC_EDIT_V15, OnKillfocusEditV15)
	ON_EN_KILLFOCUS(IDC_EDIT_V16, OnKillfocusEditV16)
	ON_BN_CLICKED(IDC_TAKE_IT, OnTakeIt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Controller_Dlg 

BOOL Controller_Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int i;
	int chan;

	for (i=0; i<NO_EFFECT_ELEMS; i++)
	{
		m_effectcombobox.InsertString(i,GlobalUtilities::effect_list[i].name);
	}

	SetDlgItemText(IDC_VKANAL,GlobalUtilities::get_resource_string(IDS_CHANNEL));
	SetDlgItemText(IDC_VOICE,"Voice");
	SetDlgItemText(IDC_MAXVOLUME,GlobalUtilities::get_resource_string(IDS_MAX_VAL));
	SetDlgItemText(IDC_MAXVOLUME_ALL, GlobalUtilities::get_resource_string(IDS_MAX_VAL_ALL));
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

	effect_index = 2; // Main Volume
	source_changed = false;

	init_data();

	// Tool Tips
	if (hpmfi->with_insdef)
	{
		m_pToolTip = new CToolTipCtrl;
		m_pToolTip->Create(this);
		m_pToolTip->SetDelayTime(TTDT_AUTOPOP,4000);
		m_pToolTip->SetMaxTipWidth(200);

		for (chan=0; chan<16; chan++)
		{
			if ((hpmfi->mlv_list[chan]).voicename == "") continue;
			m_pToolTip->AddTool(m_voice_type[chan],(hpmfi->mlv_list[chan]).voicename);
		}
		m_pToolTip->Activate(true);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void Controller_Dlg::init_data()
{
	int i;

	m_effectcombobox.SetCurSel(effect_index);

	for (i=0; i<16; i++)
	{

		value[i]->SetLimitText(3);

		if (!(hpmfi->mute)[i])
		{
			SetDlgItemText(idc_voice_type[i],(hpmfi->patchname)[i]);
		}
		else
		{
			value[i]->EnableWindow(false);
			SetDlgItemText(idc_voice_type[i],"");
		}
	}
	
	m_edit_all.SetLimitText(3);
	SetDlgItemText(IDC_EDIT_ALL,"100"); // Percentage

	// To be changed with each Selection:

	hpmfi->get_max_values(maxvalue, effect_index);

	CString vstr;
	for (i=0; i<16; i++)
	{
		insert_event[i] = (maxvalue[i]==-1);
		if (insert_event[i])
		{
			maxvalue[i] = GlobalUtilities::effect_list[effect_index].default_value;
		}

		if (!(hpmfi->mute)[i])
		{
			vstr.Format("%i",maxvalue[i]);
			SetDlgItemText(idc_value[i],vstr);
		}
		else
		{
			value[i]->EnableWindow(false);
		}

		chan_changed[i] = false;
	}

	SetWindowText(GlobalUtilities::effect_list[effect_index].name);
	m_edit_all.EnableWindow(GlobalUtilities::effect_list[effect_index].global_change);
	m_edit_all.EnableWindow(true);

/*
	for (chan=0; chan<16; chan++)
	{
		if(!voicelist[chan].with_note)
		{
			(bankno_list[chan])->EnableWindow(FALSE);
			(banknamelist[chan])->EnableWindow(FALSE);
			(voiceno_list[chan])->EnableWindow(FALSE);
			(browse_list[chan])->EnableWindow(FALSE);
			(voicenamelist[chan])->EnableWindow(FALSE);
		}
		if (!hpmfi->with_insdef)
		{
			banknamelist[chan]->ResetContent();
			voicenamelist[chan]->ResetContent();
			banknamelist[chan]->EnableWindow(FALSE);
			(browse_list[chan])->EnableWindow(FALSE);
			voicenamelist[chan]->EnableWindow(FALSE);
		}
	}
*/
	m_cancel.SetFocus();

}


void Controller_Dlg::OnSelchangeEffectcombobox() 
{
	int i;

	effect_index = m_effectcombobox.GetCurSel();

	hpmfi->get_max_values(maxvalue, effect_index);

	CString vstr;
	for (i=0; i<16; i++)
	{
		insert_event[i] = (maxvalue[i]==-1);
		if (insert_event[i])
		{
			maxvalue[i] = GlobalUtilities::effect_list[effect_index].default_value;
		}

		if (!(hpmfi->mute)[i])
		{
			vstr.Format("%i",maxvalue[i]);
			SetDlgItemText(idc_value[i],vstr);
		}
		chan_changed[i] = false;
	}

	SetWindowText(GlobalUtilities::effect_list[effect_index].name);
	m_edit_all.EnableWindow(GlobalUtilities::effect_list[effect_index].global_change);
	m_edit_all.EnableWindow(true);
}


void Controller_Dlg::OnKillfocusEditAll() 
{
	KillfocusEdit(16);	
}


void Controller_Dlg::KillfocusEdit(int chan)
{
	char val_str[10];
	if (chan < 16)
	{
		int val_number;
		if ((hpmfi->mute)[chan]) return;
		int l = value[chan]->LineLength();
		int len = value[chan]->GetLine(0, val_str,l);
		val_str[len] = 0;
		val_number = GlobalUtilities::compute_number(val_str,l);
		if (val_number<0 || val_number>127)
		{ // Syntax error, use 0 or 127
			val_number = val_number<0?0:127;
		}
		CString v;
		v.Format("%i",val_number);
		SetDlgItemText(idc_value[chan],v);
		chan_changed[chan] = true;
	}
	else
	{	// eval with percentage value of m_edit_all
		int i;
		int original_value;
		int new_value;
		int percent;
		CString v;

		int l = m_edit_all.LineLength();
		int len = m_edit_all.GetLine(0, val_str,l);
		val_str[len] = 0;
		percent = GlobalUtilities::compute_number(val_str,l);
		if (percent < 0)
		{
			percent = 100;
		}
		v.Format("%i",percent);
		SetDlgItemText(IDC_EDIT_ALL,v);
		if (percent == 100) return;

		for (i=0; i<16; i++)
		{
			if ((hpmfi->mute)[i]) continue;
			int l = value[i]->LineLength();
			int len = value[i]->GetLine(0, val_str,l);
			val_str[len] = 0;
			original_value = GlobalUtilities::compute_number(val_str,l);
			new_value = (int) (((float)original_value*(float)percent)/100.);

			if (new_value<0 || new_value>127)
			{ // Syntax error, use 0 or 127
				new_value = (new_value<0)?0:127;
			}
			v.Format("%i",new_value);
			SetDlgItemText(idc_value[i],v);
			chan_changed[i] = true;
		}
		// initialize percent
		SetDlgItemText(IDC_EDIT_ALL,"100");
	}
}
		

void Controller_Dlg::OnKillfocusEditV1() 
{
	KillfocusEdit(0);	
}

void Controller_Dlg::OnKillfocusEditV2() 
{
	KillfocusEdit(1);	
}

void Controller_Dlg::OnKillfocusEditV3() 
{
	KillfocusEdit(2);	
}

void Controller_Dlg::OnKillfocusEditV4() 
{
	KillfocusEdit(3);	
}

void Controller_Dlg::OnKillfocusEditV5() 
{
	KillfocusEdit(4);	
}

void Controller_Dlg::OnKillfocusEditV6() 
{
	KillfocusEdit(5);	
}

void Controller_Dlg::OnKillfocusEditV7() 
{
	KillfocusEdit(6);	
}

void Controller_Dlg::OnKillfocusEditV8() 
{
	KillfocusEdit(7);	
}

void Controller_Dlg::OnKillfocusEditV9() 
{
	KillfocusEdit(8);	
}

void Controller_Dlg::OnKillfocusEditV10() 
{
	KillfocusEdit(9);	
}

void Controller_Dlg::OnKillfocusEditV11() 
{
	KillfocusEdit(10);	
}

void Controller_Dlg::OnKillfocusEditV12() 
{
	KillfocusEdit(11);	
}

void Controller_Dlg::OnKillfocusEditV13() 
{
	KillfocusEdit(12);	
}

void Controller_Dlg::OnKillfocusEditV14() 
{
	KillfocusEdit(13);	
}

void Controller_Dlg::OnKillfocusEditV15() 
{
	KillfocusEdit(14);	
}

void Controller_Dlg::OnKillfocusEditV16() 
{
	KillfocusEdit(15);	
}

void Controller_Dlg::OnTakeIt() 
{
	// Dummy. Only to initiate OnKillfocusEditAll()	
}

void Controller_Dlg::OnCancel() 
{
	if (m_pToolTip != NULL)
	{
		delete m_pToolTip;
		m_pToolTip = NULL;
	}

	EndDialog(source_changed?1:0);
}


void Controller_Dlg::OnOK() 
{
	if (m_pToolTip != NULL)
	{
		delete m_pToolTip;
		m_pToolTip = NULL;
	}

   CWnd* pwndCtrl = GetFocus();
   CWnd* pwndCtrlNext = pwndCtrl;
   int ctrl_ID = pwndCtrl->GetDlgCtrlID();

   switch (ctrl_ID) 
   {
	   case IDC_EDIT_V1:
			if (!(hpmfi->mute)[1])
			{
				pwndCtrlNext = GetDlgItem(IDC_EDIT_V2);
				m_edit_v2.SetSel(0,-1);
				break;
			}
       case IDC_EDIT_V2:
			if (!(hpmfi->mute)[2])
			{
				pwndCtrlNext = GetDlgItem(IDC_EDIT_V3);
				m_edit_v3.SetSel(0,-1);
				break;
			}
       case IDC_EDIT_V3:
			if (!(hpmfi->mute)[3])
			{
	            pwndCtrlNext = GetDlgItem(IDC_EDIT_V4);
				m_edit_v4.SetSel(0,-1);
			    break;
			}
       case IDC_EDIT_V4:
			if (!(hpmfi->mute)[4])
			{
				pwndCtrlNext = GetDlgItem(IDC_EDIT_V5);
				m_edit_v5.SetSel(0,-1);
				break;
			}
       case IDC_EDIT_V5:
			if (!(hpmfi->mute)[5])
			{
				pwndCtrlNext = GetDlgItem(IDC_EDIT_V6);
				m_edit_v6.SetSel(0,-1);
				break;
			}
       case IDC_EDIT_V6:
			if (!(hpmfi->mute)[6])
			{
	            pwndCtrlNext = GetDlgItem(IDC_EDIT_V7);
				m_edit_v7.SetSel(0,-1);
			    break;
			}
       case IDC_EDIT_V7:
			if (!(hpmfi->mute)[7])
			{
				pwndCtrlNext = GetDlgItem(IDC_EDIT_V8);
				m_edit_v8.SetSel(0,-1);
				break;
			}
       case IDC_EDIT_V8:
			if (!(hpmfi->mute)[8])
			{
				pwndCtrlNext = GetDlgItem(IDC_EDIT_V9);
				m_edit_v9.SetSel(0,-1);
				break;
			}
       case IDC_EDIT_V9:
			if (!(hpmfi->mute)[9])
			{
	            pwndCtrlNext = GetDlgItem(IDC_EDIT_V10);
				m_edit_v10.SetSel(0,-1);
			    break;
			}
       case IDC_EDIT_V10:
			if (!(hpmfi->mute)[10])
			{
				pwndCtrlNext = GetDlgItem(IDC_EDIT_V11);
				m_edit_v11.SetSel(0,-1);
				break;
			}
       case IDC_EDIT_V11:
			if (!(hpmfi->mute)[11])
			{
	            pwndCtrlNext = GetDlgItem(IDC_EDIT_V12);
				m_edit_v12.SetSel(0,-1);
			    break;
			}
       case IDC_EDIT_V12:
			if (!(hpmfi->mute)[12])
			{
				pwndCtrlNext = GetDlgItem(IDC_EDIT_V13);
				m_edit_v13.SetSel(0,-1);
				break;
			}
       case IDC_EDIT_V13:
			if (!(hpmfi->mute)[13])
			{
				pwndCtrlNext = GetDlgItem(IDC_EDIT_V14);
				m_edit_v14.SetSel(0,-1);
				break;
			}
       case IDC_EDIT_V14:
			if (!(hpmfi->mute)[14])
			{
	            pwndCtrlNext = GetDlgItem(IDC_EDIT_V15);
				m_edit_v15.SetSel(0,-1);
			    break;
			}
       case IDC_EDIT_V15:
			if (!(hpmfi->mute)[15])
			{
	            pwndCtrlNext = GetDlgItem(IDC_EDIT_V16);
				m_edit_v16.SetSel(0,-1);
			    break;
			}
       case IDC_EDIT_V16:
            pwndCtrlNext = GetDlgItem(IDOK);
            break;
       case IDC_EDIT_ALL:
            pwndCtrlNext = GetDlgItem(IDOK);
            break;
       case IDOK:
            pwndCtrlNext = NULL;
			break;
       default:
            break;
   }
    if (pwndCtrlNext!=0)
	{
		pwndCtrlNext->SetFocus();
		return;
	}

	int chan;
	char val_str[10];
	for (chan=0; chan<16; chan++)
	{
		if ((hpmfi->mute)[chan]) continue;
		int l = value[chan]->LineLength();
		int len = value[chan]->GetLine(0, val_str,l);
		val_str[len] = 0;
		maxvalue[chan] = GlobalUtilities::compute_number(val_str,l);;
		if (maxvalue[chan]<0 || maxvalue[chan]>127)
		{ // Syntax error, use 0 or 127
			maxvalue[chan] = (maxvalue[chan]<0)?0:127;
		}
	}

	SetCursor(hCursorWait);
	hpmfi->eval_max_values(effect_index,maxvalue,insert_event,chan_changed);
	if (hpmfi->is_source_changed())
	{
		source_changed = true;
	}
/*
	CString r;
	r.Format(GlobalUtilities::get_resource_string(IDS_CONTROLLER_PERFORMED),
		     GlobalUtilities::effect_list[effect_index].name);
	::MessageBox(AfxGetMainWnd()->m_hWnd,r,"",MB_OK|MB_TASKMODAL);
*/

	init_data();
	SetCursor(hCursorOld);
}

BOOL Controller_Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if (NULL != m_pToolTip)
	{
		m_pToolTip->RelayEvent(pMsg);
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}


