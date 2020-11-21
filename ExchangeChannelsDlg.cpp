// ExchangeChannelsDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "ExchangeChannelsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld ExchangeChannelsDlg 


ExchangeChannelsDlg::ExchangeChannelsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ExchangeChannelsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ExchangeChannelsDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT

	int i;
	
	source_check[0] = &m_source_1;
	source_check[1] = &m_source_2;
	source_check[2] = &m_source_3;
	source_check[3] = &m_source_4;
	source_check[4] = &m_source_5;
	source_check[5] = &m_source_6;
	source_check[6] = &m_source_7;
	source_check[7] = &m_source_8;
	source_check[8] = &m_source_9;
	source_check[9] = &m_source_10;
	source_check[10] = &m_source_11;
	source_check[11] = &m_source_12;
	source_check[12] = &m_source_13;
	source_check[13] = &m_source_14;
	source_check[14] = &m_source_15;
	source_check[15] = &m_source_16;

	dest_check[0] = &m_dest_1;
	dest_check[1] = &m_dest_2;
	dest_check[2] = &m_dest_3;
	dest_check[3] = &m_dest_4;
	dest_check[4] = &m_dest_5;
	dest_check[5] = &m_dest_6;
	dest_check[6] = &m_dest_7;
	dest_check[7] = &m_dest_8;
	dest_check[8] = &m_dest_9;
	dest_check[9] = &m_dest_10;
	dest_check[10]= &m_dest_11;
	dest_check[11]= &m_dest_12;
	dest_check[12]= &m_dest_13;
	dest_check[13]= &m_dest_14;
	dest_check[14]= &m_dest_15;
	dest_check[15]= &m_dest_16;

	// inializes membervariable list m_voice_type

	m_voice_type[0] = &m_channel_patch1;
	m_voice_type[1] = &m_channel_patch2;
	m_voice_type[2] = &m_channel_patch3;
	m_voice_type[3] = &m_channel_patch4;
	m_voice_type[4] = &m_channel_patch5;
	m_voice_type[5] = &m_channel_patch6;
	m_voice_type[6] = &m_channel_patch7;
	m_voice_type[7] = &m_channel_patch8;
	m_voice_type[8] = &m_channel_patch9;
	m_voice_type[9] = &m_channel_patch10;
	m_voice_type[10] = &m_channel_patch11;
	m_voice_type[11] = &m_channel_patch12;
	m_voice_type[12] = &m_channel_patch13;
	m_voice_type[13] = &m_channel_patch14;
	m_voice_type[14] = &m_channel_patch15;
	m_voice_type[15] = &m_channel_patch16;

	m_pToolTip = NULL;

	idc_voice_name[0] = IDC_CHANNEL_PATCH_1;
	idc_voice_name[1] = IDC_CHANNEL_PATCH_2;
	idc_voice_name[2] = IDC_CHANNEL_PATCH_3;
	idc_voice_name[3] = IDC_CHANNEL_PATCH_4;
	idc_voice_name[4] = IDC_CHANNEL_PATCH_5;
	idc_voice_name[5] = IDC_CHANNEL_PATCH_6;
	idc_voice_name[6] = IDC_CHANNEL_PATCH_7;
	idc_voice_name[7] = IDC_CHANNEL_PATCH_8;
	idc_voice_name[8] = IDC_CHANNEL_PATCH_9;
	idc_voice_name[9] = IDC_CHANNEL_PATCH_10;
	idc_voice_name[10] = IDC_CHANNEL_PATCH_11;
	idc_voice_name[11] = IDC_CHANNEL_PATCH_12;
	idc_voice_name[12] = IDC_CHANNEL_PATCH_13;
	idc_voice_name[13] = IDC_CHANNEL_PATCH_14;
	idc_voice_name[14] = IDC_CHANNEL_PATCH_15;
	idc_voice_name[15] = IDC_CHANNEL_PATCH_16;

	selection = NONE_SELECTED;

	for (i=0; i<16; i++)
	{
		source_channels[i] = false;
	}

	dest_channel = -1;

}


void ExchangeChannelsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ExchangeChannelsDlg)
	DDX_Control(pDX, IDC_CHANNEL_PATCH_1, m_channel_patch1);
	DDX_Control(pDX, IDC_CHANNEL_PATCH_2, m_channel_patch2);
	DDX_Control(pDX, IDC_CHANNEL_PATCH_3, m_channel_patch3);
	DDX_Control(pDX, IDC_CHANNEL_PATCH_4, m_channel_patch4);
	DDX_Control(pDX, IDC_CHANNEL_PATCH_5, m_channel_patch5);
	DDX_Control(pDX, IDC_CHANNEL_PATCH_6, m_channel_patch6);
	DDX_Control(pDX, IDC_CHANNEL_PATCH_7, m_channel_patch7);
	DDX_Control(pDX, IDC_CHANNEL_PATCH_8, m_channel_patch8);
	DDX_Control(pDX, IDC_CHANNEL_PATCH_9, m_channel_patch9);
	DDX_Control(pDX, IDC_CHANNEL_PATCH_10, m_channel_patch10);
	DDX_Control(pDX, IDC_CHANNEL_PATCH_11, m_channel_patch11);
	DDX_Control(pDX, IDC_CHANNEL_PATCH_12, m_channel_patch12);
	DDX_Control(pDX, IDC_CHANNEL_PATCH_13, m_channel_patch13);
	DDX_Control(pDX, IDC_CHANNEL_PATCH_14, m_channel_patch14);
	DDX_Control(pDX, IDC_CHANNEL_PATCH_15, m_channel_patch15);
	DDX_Control(pDX, IDC_CHANNEL_PATCH_16, m_channel_patch16);
	DDX_Control(pDX, IDC_SOURCE_1, m_source_1);
	DDX_Control(pDX, IDC_SOURCE_2, m_source_2);
	DDX_Control(pDX, IDC_SOURCE_3, m_source_3);
	DDX_Control(pDX, IDC_SOURCE_4, m_source_4);
	DDX_Control(pDX, IDC_SOURCE_5, m_source_5);
	DDX_Control(pDX, IDC_SOURCE_6, m_source_6);
	DDX_Control(pDX, IDC_SOURCE_7, m_source_7);
	DDX_Control(pDX, IDC_SOURCE_8, m_source_8);
	DDX_Control(pDX, IDC_SOURCE_9, m_source_9);
	DDX_Control(pDX, IDC_SOURCE_10, m_source_10);
	DDX_Control(pDX, IDC_SOURCE_11, m_source_11);
	DDX_Control(pDX, IDC_SOURCE_12, m_source_12);
	DDX_Control(pDX, IDC_SOURCE_13, m_source_13);
	DDX_Control(pDX, IDC_SOURCE_14, m_source_14);
	DDX_Control(pDX, IDC_SOURCE_15, m_source_15);
	DDX_Control(pDX, IDC_SOURCE_16, m_source_16);
	DDX_Control(pDX, IDC_DEST_1, m_dest_1);
	DDX_Control(pDX, IDC_DEST_2, m_dest_2);
	DDX_Control(pDX, IDC_DEST_3, m_dest_3);
	DDX_Control(pDX, IDC_DEST_4, m_dest_4);
	DDX_Control(pDX, IDC_DEST_5, m_dest_5);
	DDX_Control(pDX, IDC_DEST_6, m_dest_6);
	DDX_Control(pDX, IDC_DEST_7, m_dest_7);
	DDX_Control(pDX, IDC_DEST_8, m_dest_8);
	DDX_Control(pDX, IDC_DEST_9, m_dest_9);
	DDX_Control(pDX, IDC_DEST_10, m_dest_10);
	DDX_Control(pDX, IDC_DEST_11, m_dest_11);
	DDX_Control(pDX, IDC_DEST_12, m_dest_12);
	DDX_Control(pDX, IDC_DEST_13, m_dest_13);
	DDX_Control(pDX, IDC_DEST_14, m_dest_14);
	DDX_Control(pDX, IDC_DEST_15, m_dest_15);
	DDX_Control(pDX, IDC_DEST_16, m_dest_16);
	DDX_Control(pDX, IDC_LIST_COPY_EXCHANGE, m_list_copy_exchange);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ExchangeChannelsDlg, CDialog)
	//{{AFX_MSG_MAP(ExchangeChannelsDlg)
	ON_LBN_SELCHANGE(IDC_LIST_COPY_EXCHANGE, OnSelchangeListCopyExchange)
	ON_BN_CLICKED(IDC_SOURCE_1, OnSource1)
	ON_BN_CLICKED(IDC_SOURCE_2, OnSource2)
	ON_BN_CLICKED(IDC_SOURCE_3, OnSource3)
	ON_BN_CLICKED(IDC_SOURCE_4, OnSource4)
	ON_BN_CLICKED(IDC_SOURCE_5, OnSource5)
	ON_BN_CLICKED(IDC_SOURCE_6, OnSource6)
	ON_BN_CLICKED(IDC_SOURCE_7, OnSource7)
	ON_BN_CLICKED(IDC_SOURCE_8, OnSource8)
	ON_BN_CLICKED(IDC_SOURCE_9, OnSource9)
	ON_BN_CLICKED(IDC_SOURCE_10, OnSource10)
	ON_BN_CLICKED(IDC_SOURCE_11, OnSource11)
	ON_BN_CLICKED(IDC_SOURCE_12, OnSource12)
	ON_BN_CLICKED(IDC_SOURCE_13, OnSource13)
	ON_BN_CLICKED(IDC_SOURCE_14, OnSource14)
	ON_BN_CLICKED(IDC_SOURCE_15, OnSource15)
	ON_BN_CLICKED(IDC_SOURCE_16, OnSource16)
	ON_BN_CLICKED(IDC_DEST_1, OnDest1)
	ON_BN_CLICKED(IDC_DEST_2, OnDest2)
	ON_BN_CLICKED(IDC_DEST_3, OnDest3)
	ON_BN_CLICKED(IDC_DEST_4, OnDest4)
	ON_BN_CLICKED(IDC_DEST_5, OnDest5)
	ON_BN_CLICKED(IDC_DEST_6, OnDest6)
	ON_BN_CLICKED(IDC_DEST_7, OnDest7)
	ON_BN_CLICKED(IDC_DEST_8, OnDest8)
	ON_BN_CLICKED(IDC_DEST_9, OnDest9)
	ON_BN_CLICKED(IDC_DEST_10, OnDest10)
	ON_BN_CLICKED(IDC_DEST_11, OnDest11)
	ON_BN_CLICKED(IDC_DEST_12, OnDest12)
	ON_BN_CLICKED(IDC_DEST_13, OnDest13)
	ON_BN_CLICKED(IDC_DEST_14, OnDest14)
	ON_BN_CLICKED(IDC_DEST_15, OnDest15)
	ON_BN_CLICKED(IDC_DEST_16, OnDest16)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten ExchangeChannelsDlg 

void ExchangeChannelsDlg::OnOK() 
{
	bool is_source_selected = false;
	int i;
	for (i=0; i<16;i++)
	{
		if (source_channels[i])
		{
			is_source_selected = true;
			break;
		}
	}

	if (selection==NONE_SELECTED)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SELECT_FUNCTION),NULL,MB_OK|MB_TASKMODAL);
		return;
	}
	if (!is_source_selected)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SELECT_SOURCE_CHANNEL),NULL,MB_OK|MB_TASKMODAL);
		return;
	}
	if (((selection==CUT_COPY_SELECTED)  ||
		   (selection==EXCHANGE_SELECTED)||
		   (selection==COPY_SELECTED))      &&
		dest_channel==-1)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SELECT_DESTINATION_CHANNEL),NULL,MB_OK|MB_TASKMODAL);
		return;
	}

	if (((selection==CUT_COPY_SELECTED)||(selection==COPY_SELECTED))&&
		   (!(hpmfi->mute)[dest_channel]))
	{
		if (IDYES != AfxMessageBox(GlobalUtilities::get_resource_string(IDS_OVERWRITE_DESTINATION_CHANNEL),MB_YESNO,0))
		{
			return;
		}
	}

	if (m_pToolTip != NULL)
	{
		delete m_pToolTip;
		m_pToolTip = NULL;
	}

	EndDialog(1);
}

void ExchangeChannelsDlg::OnCancel() 
{
	if (m_pToolTip != NULL)
	{
		delete m_pToolTip;
		m_pToolTip = NULL;
	}
	
	EndDialog(0);
}

BOOL ExchangeChannelsDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (NULL != m_pToolTip)
	{
		m_pToolTip->RelayEvent(pMsg);
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}


BOOL ExchangeChannelsDlg::OnInitDialog() 
{
	int chan;

	CDialog::OnInitDialog();

	CString delete_channel = GlobalUtilities::get_resource_string(IDS_DELETE_CHANNEL);
	CString exchange_channels = GlobalUtilities::get_resource_string(IDS_EXCHANGE_CHANNELS);
	CString cut_copy_channel = GlobalUtilities::get_resource_string(IDS_CUT_COPY_CHANNEL);
	CString double_channel = GlobalUtilities::get_resource_string(IDS_DOUBLE_CHANNEL);
	m_list_copy_exchange.AddString(delete_channel);
	m_list_copy_exchange.AddString(exchange_channels);
	m_list_copy_exchange.AddString(cut_copy_channel);
	m_list_copy_exchange.AddString(double_channel);

	int i;

	for (i=0; i<16; i++)
	{
		if (!(hpmfi->mute)[i])
		{
			SetDlgItemText(idc_voice_name[i],(hpmfi->patchname)[i]);
		}
		else
		{
			SetDlgItemText(idc_voice_name[i],"");
		}
		source_check[i]->EnableWindow(FALSE);
		dest_check[i]->EnableWindow(FALSE);
	}

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

void ExchangeChannelsDlg::OnSelchangeListCopyExchange() 
{
	int i;

	for (i=0; i<16; i++)
	{
		source_check[i]->SetCheck(0);
		dest_check[i]->SetCheck(0);
		if (!(hpmfi->mute)[i])
		{
			source_check[i]->EnableWindow(TRUE);
		}
	}

	selection = m_list_copy_exchange.GetCurSel();

	if (selection == EXCHANGE_SELECTED)  
	{
		for (i=0; i<16; i++)
		{
			dest_check[i]->SetCheck(0);
			if (!(hpmfi->mute)[i] && ((i!=9)||hpmfi->with_xg_on))
			{
				dest_check[i]->EnableWindow(TRUE);
			}
		}
	}
	else
	if ((selection == CUT_COPY_SELECTED) || 
		(selection == COPY_SELECTED)) 
	{
		for (i=0; i<16; i++)
		{
			dest_check[i]->EnableWindow(((i==9)&&!hpmfi->with_xg_on)?FALSE:TRUE);
		}
	}
	else
	if (selection == DELETE_SELECTED)
	{
		for (i=0; i<16; i++)
		{
			dest_check[i]->EnableWindow(FALSE);
			source_channels[i] = false;
		}
	}
		
}

void ExchangeChannelsDlg::SourceClicked(int chan, int checked) 
{
	int i;

	if (selection !=DELETE_SELECTED)
	{
		if (checked==1)
		{
			for (i=0; i<16; i++)
			{
				if (i==chan) continue;
				source_check[i]->SetCheck(0);
				source_channels[i] = false;
			}
			source_channels[chan] = true;
		}
		else
		{
			for (i=0; i<16; i++)
			{
				source_check[i]->SetCheck(0);
			}
			source_channels[chan] = false;
		}

		if ((source_channels[chan]) && (dest_channel==chan))
		{
			source_check[chan]->SetCheck(0);
			source_channels[chan] = false;
		}
	}
	else
	{	// DELETE_SELECTED
		source_channels[chan] = (checked==1); 
	}
}

void ExchangeChannelsDlg::OnSource1() 
{
	SourceClicked(0,source_check[0]->GetCheck()); 
}

void ExchangeChannelsDlg::OnSource2() 
{
	SourceClicked(1,source_check[1]->GetCheck()); 
}

void ExchangeChannelsDlg::OnSource3() 
{
	SourceClicked(2,source_check[2]->GetCheck()); 
}

void ExchangeChannelsDlg::OnSource4() 
{
	SourceClicked(3,source_check[3]->GetCheck()); 
}

void ExchangeChannelsDlg::OnSource5() 
{
	SourceClicked(4,source_check[4]->GetCheck()); 
}

void ExchangeChannelsDlg::OnSource6() 
{
	SourceClicked(5,source_check[5]->GetCheck()); 
}

void ExchangeChannelsDlg::OnSource7() 
{
	SourceClicked(6,source_check[6]->GetCheck()); 
}

void ExchangeChannelsDlg::OnSource8() 
{
	SourceClicked(7,source_check[7]->GetCheck()); 
}

void ExchangeChannelsDlg::OnSource9() 
{
	SourceClicked(8,source_check[8]->GetCheck()); 
}

void ExchangeChannelsDlg::OnSource10() 
{
	SourceClicked(9,source_check[9]->GetCheck()); 
}

void ExchangeChannelsDlg::OnSource11() 
{
	SourceClicked(10,source_check[10]->GetCheck()); 
}

void ExchangeChannelsDlg::OnSource12() 
{
	SourceClicked(11,source_check[11]->GetCheck()); 
}

void ExchangeChannelsDlg::OnSource13() 
{
	SourceClicked(12,source_check[12]->GetCheck()); 
}

void ExchangeChannelsDlg::OnSource14() 
{
	SourceClicked(13,source_check[13]->GetCheck()); 
}

void ExchangeChannelsDlg::OnSource15() 
{
	SourceClicked(14,source_check[14]->GetCheck()); 
}

void ExchangeChannelsDlg::OnSource16() 
{
	SourceClicked(15,source_check[15]->GetCheck()); 
}


void ExchangeChannelsDlg::DestClicked(int chan, int checked) 
{
	int i;
	if (checked==1)
	{
		for (i=0; i<16; i++)
		{
			if (i==chan) continue;
			dest_check[i]->SetCheck(0);
		}
		dest_channel = chan;
	}
	else
	{
		dest_channel = -1;
	}

	if ((dest_channel==chan) && (source_channels[chan]))
	{
		dest_check[chan]->SetCheck(0);
		dest_channel = -1;
	}
}

void ExchangeChannelsDlg::OnDest1() 
{
	DestClicked(0,dest_check[0]->GetCheck()); 
}

void ExchangeChannelsDlg::OnDest2() 
{
	DestClicked(1,dest_check[1]->GetCheck()); 
}

void ExchangeChannelsDlg::OnDest3() 
{
	DestClicked(2,dest_check[2]->GetCheck()); 
}

void ExchangeChannelsDlg::OnDest4() 
{
	DestClicked(3,dest_check[3]->GetCheck()); 
}

void ExchangeChannelsDlg::OnDest5() 
{
	DestClicked(4,dest_check[4]->GetCheck()); 
}

void ExchangeChannelsDlg::OnDest6() 
{
	DestClicked(5,dest_check[5]->GetCheck()); 
}

void ExchangeChannelsDlg::OnDest7() 
{
	DestClicked(6,dest_check[6]->GetCheck()); 
}

void ExchangeChannelsDlg::OnDest8() 
{
	DestClicked(7,dest_check[7]->GetCheck()); 
}

void ExchangeChannelsDlg::OnDest9() 
{
	DestClicked(8,dest_check[8]->GetCheck()); 
}

void ExchangeChannelsDlg::OnDest10() 
{
	DestClicked(9,dest_check[9]->GetCheck()); 
}

void ExchangeChannelsDlg::OnDest11() 
{
	DestClicked(10,dest_check[10]->GetCheck()); 
}

void ExchangeChannelsDlg::OnDest12() 
{
	DestClicked(11,dest_check[11]->GetCheck()); 
}

void ExchangeChannelsDlg::OnDest13() 
{
	DestClicked(12,dest_check[12]->GetCheck()); 
}

void ExchangeChannelsDlg::OnDest14() 
{
	DestClicked(13,dest_check[13]->GetCheck()); 
}

void ExchangeChannelsDlg::OnDest15() 
{
	DestClicked(14,dest_check[14]->GetCheck()); 
}

void ExchangeChannelsDlg::OnDest16() 
{
	DestClicked(15,dest_check[15]->GetCheck()); 
}


