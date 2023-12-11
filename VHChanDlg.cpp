// VHChanDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "VHChanDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld VHChanDlg 


VHChanDlg::VHChanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(VHChanDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(VHChanDlg)
	//}}AFX_DATA_INIT
	int i;
	for (i=0; i<16; i++)
	{
		vh_channel_index_list[i] = -1;
	}
	no_vh_chans = 0;

}


void VHChanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VHChanDlg)
	DDX_Control(pDX, IDC_VH_CHAN_LIST, m_vh_chan_list);
	DDX_Control(pDX, IDC_DELETE_VOCODER_CHAN, m_delete_vocalharmony);
	DDX_Control(pDX, IDC_SELECT_VOCODER_CHAN, m_select_vocoder_chan);
	DDX_Control(pDX, IDC_CHECK_SELECT_LENGTHEN, m_lengthen_select);
	DDX_Control(pDX, IDC_CHECK_ACT_DEAKT, m_act_deact_select);
	DDX_Control(pDX, IDC_NO_QUARTERS, m_no_quarters);
	DDX_Control(pDX, IDC_VH_ACT_DEACT, m_vh_act_deact);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VHChanDlg, CDialog)
	//{{AFX_MSG_MAP(VHChanDlg)
	ON_BN_CLICKED(IDC_CHECK_ACT_DEAKT, OnCheckActDeakt)
	ON_BN_CLICKED(IDC_CHECK_SELECT_LENGTHEN, OnCheckSelectLengthen)
	ON_EN_UPDATE(IDC_NO_QUARTERS, OnUpdateNoQuarters)
	ON_BN_CLICKED(IDC_SELECT_VOCODER_CHAN, OnSelectVocoderChan)
	ON_BN_CLICKED(IDC_DELETE_VOCODER_CHAN, OnDeleteVocalHarmony)
	ON_LBN_SELCHANGE(IDC_VH_CHAN_LIST, OnSelchangeVhChanList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten VHChanDlg 

BOOL VHChanDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	no_vh_chans = 0;
	vocoder_channel_act = -1; // activate / deactivate
	act_vocoder_channel = -1;
	vocoder_channel_set = false;
	vocoder_channel_delete = false;


	SetDlgItemInt(IDC_NO_QUARTERS,0); // default

	// look for vh_sysexes that define others than vocoder
	vh_sysexes_exist = hpmfi->with_vh_sysexes(false);

	// look for vocoder
	vocoder_defined = hpmfi->is_vocalharmony_vocoder();

	if (!vocoder_defined && vh_sysexes_exist)
	{
		m_act_deact_select.EnableWindow(false);
		m_lengthen_select. EnableWindow(false);
		m_select_vocoder_chan.EnableWindow(false);
		m_delete_vocalharmony.EnableWindow(false); /* ! */
	}



	int chan;
	CString r;

	
	for (chan=15; chan>=0; chan--)
	{
		if (hpmfi->vh_channel[chan])
		{
			r.Format("%2i",chan+1);
			m_vh_chan_list.InsertString(no_vh_chans,r);
			vh_channel_index_list[no_vh_chans] = chan;
			no_vh_chans++;
		}
	}

/* Test
	int i;
	int n;
	CString str;
	
	for (i=0; i<no_vh_chans; i++)
	{
		n = m_vh_chan_list.GetLBTextLen(i);
		m_vh_chan_list.GetLBText(i,str.GetBuffer(n));
		r.Format("index %i, chan %i, chanstring %s",i,vh_channel_index_list[i],str);
		MessageBox(r);
		str.ReleaseBuffer();
	}
*/ // End Test

	if (no_vh_chans>0)
	{
		int vocoder_chan = -1;
		if (vocoder_defined)
		{
			int i;
			for (i=0; i<no_vh_chans; i++)
			{
				vocoder_chan = vh_channel_index_list[i];

				if (hpmfi->vh_channel_sysex_exist[vocoder_chan])
				{
					m_vh_chan_list.SetCurSel(i);
					act_vocoder_channel = vocoder_chan;
					m_select_vocoder_chan.EnableWindow(false);
					break;
				}
			}
		                                                                                                       
			if (act_vocoder_channel<0)
			{
//				m_select_vocoder_chan.EnableWindow(false);
				m_act_deact_select.EnableWindow(false);
				m_lengthen_select.EnableWindow(false);
			}

		}
		else
		{
			// vh chans exist but no vocoder
			m_select_vocoder_chan.EnableWindow(true);
			m_act_deact_select.EnableWindow(false);
			m_lengthen_select.EnableWindow(act_vocoder_channel>=0);
		}
	}
	else
	{	// no_vh_chans == 0
		m_select_vocoder_chan.EnableWindow(false);
		m_act_deact_select.EnableWindow(false);
		m_lengthen_select.EnableWindow(false);
	}

	if (!hpmfi->vh_ad_on_sysex_exist)
	{
		SetDlgItemText(IDC_VH_ACT_DEACT,GlobalUtilities::get_resource_string(IDS_ACTIVATE_VH_CHANNEL));
	}
	else
	{
		SetDlgItemText(IDC_VH_ACT_DEACT,GlobalUtilities::get_resource_string(IDS_DEACTIVATE_VH_CHANNEL));
	}
/*		

		vocoder_channel_set = false;
		vocoder_channel_act = -1;
		vocoder_channel_delete = false;

		m_act_deact_select.SetCheck(0);

		m_lengthen_select.SetCheck(0);
		SetDlgItemInt(IDC_NO_QUARTERS,1);

		m_no_quarters.EnableWindow(false);
		no_quarters = -1;
	}
	else
	{
		m_no_quarters.EnableWindow(false);
		m_select_vocoder_chan.EnableWindow(false);
		m_lengthen_select.EnableWindow(false);
		m_act_deact_select.EnableWindow(false);
		OnCancel();
	}
*/
//	m_delete_vocalharmony.EnableWindow(vh_sysexes_exist); /* ! */
	m_delete_vocalharmony.EnableWindow(vocoder_defined);	/* ! */
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void VHChanDlg::OnOK() 
{

	EndDialog(0);
}

void VHChanDlg::OnCancel() 
{
	EndDialog(-1);
}

void VHChanDlg::OnSelchangeVhChanList() 
{
/*
	if (m_lengthen_select.GetCheck()==0)
	{
		return;
	}
*/
	int nIndex = m_vh_chan_list.GetCurSel();
	if (nIndex >= no_vh_chans)
	{
		nIndex = 0;
		m_vh_chan_list.SetCurSel(nIndex);
	}

	act_vocoder_channel = vh_channel_index_list[nIndex];

	if (!hpmfi->vh_channel_sysex_exist[act_vocoder_channel])
	{
		m_select_vocoder_chan.EnableWindow(true);
		m_delete_vocalharmony.EnableWindow(false);
		vocoder_channel_delete = false;
	}
	else
	{
		m_select_vocoder_chan.EnableWindow(false);
		m_delete_vocalharmony.EnableWindow(true);
		vocoder_channel_delete = true;
	}


	if (!hpmfi->vh_channel_sysex_exist[act_vocoder_channel] ||
		!hpmfi->vocoder_sysex_exist)
	{
		SetDlgItemText(IDC_VH_ACT_DEACT,GlobalUtilities::get_resource_string(IDS_ACTIVATE_VH_CHANNEL));
		vocoder_channel_act = -1;
	}
	else
	{
		SetDlgItemText(IDC_VH_ACT_DEACT,GlobalUtilities::get_resource_string(IDS_DEACTIVATE_VH_CHANNEL));
		vocoder_channel_act = -1;
	}
}

void VHChanDlg::OnCheckActDeakt() 
{
	if (m_act_deact_select.GetCheck()==0)
	{
		vocoder_channel_act = -1;
	}
	else
	{
		if (vocoder_channel_set) // new vocoder channel selected
		{
			vocoder_channel_act = 1; // activate
		}
		else
		{	// no set
			if (hpmfi->vh_ad_on_sysex_exist)
			{
				vocoder_channel_act = 0; // deactivate
			}
			else
			{
				vocoder_channel_act = 1; // activate
			}
		}
	}	
}

void VHChanDlg::OnCheckSelectLengthen() 
{
	if (m_lengthen_select.GetCheck()==1)
	{
		m_no_quarters.EnableWindow(true);
		no_quarters = GetDlgItemInt(IDC_NO_QUARTERS);
	}
	else
	{
		m_no_quarters.EnableWindow(true);
		SetDlgItemInt(IDC_NO_QUARTERS,1);
		no_quarters = -1;
	}
}

void VHChanDlg::OnUpdateNoQuarters() 
{
	int no = GetDlgItemInt(IDC_NO_QUARTERS);
	if( no < 0)
	{
		SetDlgItemInt(IDC_NO_QUARTERS,1);
	}
	no_quarters = no;
}

void VHChanDlg::OnSelectVocoderChan() 
{
	if (act_vocoder_channel<0)
	{
		vocoder_channel_set = false;
		vocoder_channel_delete = false;
		m_select_vocoder_chan.SetCheck(0);
		return;
	}
	if (m_select_vocoder_chan.GetCheck()==1)
	{
		vocoder_channel_set = true;
		vocoder_channel_delete = false;
		m_act_deact_select.EnableWindow(true);
		m_lengthen_select.EnableWindow(true);
		m_delete_vocalharmony.SetCheck(0);
	}
	else
	{
		vocoder_channel_set = false;
	}
}

void VHChanDlg::OnDeleteVocalHarmony() 
{
	if (m_delete_vocalharmony.GetCheck()==1)
	{
		vocoder_channel_delete = true;
		vocoder_channel_set = false;
		m_act_deact_select.SetCheck(0);
		m_act_deact_select.EnableWindow(false);
	}
	else
	{
		vocoder_channel_delete = false;
		m_act_deact_select.EnableWindow(vocoder_defined);
	}
}
