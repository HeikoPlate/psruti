// EffectFilterDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "EffectFilterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld EffectFilterDlg 


EffectFilterDlg::EffectFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(EffectFilterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(EffectFilterDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT

	int chan;
	idc_voice_type[0] = IDC_VOICE_1;
	idc_voice_type[1] = IDC_VOICE_2;
	idc_voice_type[2] = IDC_VOICE_3;
	idc_voice_type[3] = IDC_VOICE_4;
	idc_voice_type[4] = IDC_VOICE_5;
	idc_voice_type[5] = IDC_VOICE_6;
	idc_voice_type[6] = IDC_VOICE_7;
	idc_voice_type[7] = IDC_VOICE_8;
	idc_voice_type[8] = IDC_VOICE_9;
	idc_voice_type[9] = IDC_VOICE_10;
	idc_voice_type[10] = IDC_VOICE_11;
	idc_voice_type[11] = IDC_VOICE_12;
	idc_voice_type[12] = IDC_VOICE_13;
	idc_voice_type[13] = IDC_VOICE_14;
	idc_voice_type[14] = IDC_VOICE_15;
	idc_voice_type[15] = IDC_VOICE_16;

	// inializes membervariable list m_voice_type

	m_voice_type[0] = &m_voice_1;
	m_voice_type[1] = &m_voice_2;
	m_voice_type[2] = &m_voice_3;
	m_voice_type[3] = &m_voice_4;
	m_voice_type[4] = &m_voice_5;
	m_voice_type[5] = &m_voice_6;
	m_voice_type[6] = &m_voice_7;
	m_voice_type[7] = &m_voice_8;
	m_voice_type[8] = &m_voice_9;
	m_voice_type[9] = &m_voice_10;
	m_voice_type[10] = &m_voice_11;
	m_voice_type[11] = &m_voice_12;
	m_voice_type[12] = &m_voice_13;
	m_voice_type[13] = &m_voice_14;
	m_voice_type[14] = &m_voice_15;
	m_voice_type[15] = &m_voice_16;

	reverb_idlist[0] = IDC_REVERB_1;
	reverb_idlist[1] = IDC_REVERB_2;
	reverb_idlist[2] = IDC_REVERB_3;
	reverb_idlist[3] = IDC_REVERB_4;
	reverb_idlist[4] = IDC_REVERB_5;
	reverb_idlist[5] = IDC_REVERB_6;
	reverb_idlist[6] = IDC_REVERB_7;
	reverb_idlist[7] = IDC_REVERB_8;
	reverb_idlist[8] = IDC_REVERB_9;
	reverb_idlist[9] = IDC_REVERB_10;
	reverb_idlist[10] = IDC_REVERB_11;
	reverb_idlist[11] = IDC_REVERB_12;
	reverb_idlist[12] = IDC_REVERB_13;
	reverb_idlist[13] = IDC_REVERB_14;
	reverb_idlist[14] = IDC_REVERB_15;
	reverb_idlist[15] = IDC_REVERB_16;

	reverb_list[0] = &m_reverb_1;
	reverb_list[1] = &m_reverb_2;
	reverb_list[2] = &m_reverb_3;
	reverb_list[3] = &m_reverb_4;
	reverb_list[4] = &m_reverb_5;
	reverb_list[5] = &m_reverb_6;
	reverb_list[6] = &m_reverb_7;
	reverb_list[7] = &m_reverb_8;
	reverb_list[8] = &m_reverb_9;
	reverb_list[9] = &m_reverb_10;
	reverb_list[10] = &m_reverb_11;
	reverb_list[11] = &m_reverb_12;
	reverb_list[12] = &m_reverb_13;
	reverb_list[13] = &m_reverb_14;
	reverb_list[14] = &m_reverb_15;
	reverb_list[15] = &m_reverb_16;	
	
	chorus_idlist[0] = IDC_CHORUS_1;
	chorus_idlist[1] = IDC_CHORUS_2;
	chorus_idlist[2] = IDC_CHORUS_3;
	chorus_idlist[3] = IDC_CHORUS_4;
	chorus_idlist[4] = IDC_CHORUS_5;
	chorus_idlist[5] = IDC_CHORUS_6;
	chorus_idlist[6] = IDC_CHORUS_7;
	chorus_idlist[7] = IDC_CHORUS_8;
	chorus_idlist[8] = IDC_CHORUS_9;
	chorus_idlist[9] = IDC_CHORUS_10;
	chorus_idlist[10] = IDC_CHORUS_11;
	chorus_idlist[11] = IDC_CHORUS_12;
	chorus_idlist[12] = IDC_CHORUS_13;
	chorus_idlist[13] = IDC_CHORUS_14;
	chorus_idlist[14] = IDC_CHORUS_15;
	chorus_idlist[15] = IDC_CHORUS_16;

	chorus_list[0] = &m_chorus_1;
	chorus_list[1] = &m_chorus_2;
	chorus_list[2] = &m_chorus_3;
	chorus_list[3] = &m_chorus_4;
	chorus_list[4] = &m_chorus_5;
	chorus_list[5] = &m_chorus_6;
	chorus_list[6] = &m_chorus_7;
	chorus_list[7] = &m_chorus_8;
	chorus_list[8] = &m_chorus_9;
	chorus_list[9] = &m_chorus_10;
	chorus_list[10] = &m_chorus_11;
	chorus_list[11] = &m_chorus_12;
	chorus_list[12] = &m_chorus_13;
	chorus_list[13] = &m_chorus_14;
	chorus_list[14] = &m_chorus_15;
	chorus_list[15] = &m_chorus_16;	
	
	variation_idlist[0] = IDC_VARIATION_1;
	variation_idlist[1] = IDC_VARIATION_2;
	variation_idlist[2] = IDC_VARIATION_3;
	variation_idlist[3] = IDC_VARIATION_4;
	variation_idlist[4] = IDC_VARIATION_5;
	variation_idlist[5] = IDC_VARIATION_6;
	variation_idlist[6] = IDC_VARIATION_7;
	variation_idlist[7] = IDC_VARIATION_8;
	variation_idlist[8] = IDC_VARIATION_9;
	variation_idlist[9] = IDC_VARIATION_10;
	variation_idlist[10] = IDC_VARIATION_11;
	variation_idlist[11] = IDC_VARIATION_12;
	variation_idlist[12] = IDC_VARIATION_13;
	variation_idlist[13] = IDC_VARIATION_14;
	variation_idlist[14] = IDC_VARIATION_15;
	variation_idlist[15] = IDC_VARIATION_16;

	variation_list[0] = &m_variation_1;
	variation_list[1] = &m_variation_2;
	variation_list[2] = &m_variation_3;
	variation_list[3] = &m_variation_4;
	variation_list[4] = &m_variation_5;
	variation_list[5] = &m_variation_6;
	variation_list[6] = &m_variation_7;
	variation_list[7] = &m_variation_8;
	variation_list[8] = &m_variation_9;
	variation_list[9] = &m_variation_10;
	variation_list[10] = &m_variation_11;
	variation_list[11] = &m_variation_12;
	variation_list[12] = &m_variation_13;
	variation_list[13] = &m_variation_14;
	variation_list[14] = &m_variation_15;
	variation_list[15] = &m_variation_16;
	
	drywet_idlist[0] = IDC_DRYWET_1;
	drywet_idlist[1] = IDC_DRYWET_2;
	drywet_idlist[2] = IDC_DRYWET_3;
	drywet_idlist[3] = IDC_DRYWET_4;
	drywet_idlist[4] = IDC_DRYWET_5;
	drywet_idlist[5] = IDC_DRYWET_6;
	drywet_idlist[6] = IDC_DRYWET_7;
	drywet_idlist[7] = IDC_DRYWET_8;
	drywet_idlist[8] = IDC_DRYWET_9;
	drywet_idlist[9] = IDC_DRYWET_10;
	drywet_idlist[10] = IDC_DRYWET_11;
	drywet_idlist[11] = IDC_DRYWET_12;
	drywet_idlist[12] = IDC_DRYWET_13;
	drywet_idlist[13] = IDC_DRYWET_14;
	drywet_idlist[14] = IDC_DRYWET_15;
	drywet_idlist[15] = IDC_DRYWET_16;

	drywet_list[0] = &m_drywet_1;
	drywet_list[1] = &m_drywet_2;
	drywet_list[2] = &m_drywet_3;
	drywet_list[3] = &m_drywet_4;
	drywet_list[4] = &m_drywet_5;
	drywet_list[5] = &m_drywet_6;
	drywet_list[6] = &m_drywet_7;
	drywet_list[7] = &m_drywet_8;
	drywet_list[8] = &m_drywet_9;
	drywet_list[9] = &m_drywet_10;
	drywet_list[10] = &m_drywet_11;
	drywet_list[11] = &m_drywet_12;
	drywet_list[12] = &m_drywet_13;
	drywet_list[13] = &m_drywet_14;
	drywet_list[14] = &m_drywet_15;
	drywet_list[15] = &m_drywet_16;
	
	drywettext_idlist[0] = IDC_DRYWET_TEXT_1;
	drywettext_idlist[1] = IDC_DRYWET_TEXT_2;
	drywettext_idlist[2] = IDC_DRYWET_TEXT_3;
	drywettext_idlist[3] = IDC_DRYWET_TEXT_4;
	drywettext_idlist[4] = IDC_DRYWET_TEXT_5;
	drywettext_idlist[5] = IDC_DRYWET_TEXT_6;
	drywettext_idlist[6] = IDC_DRYWET_TEXT_7;
	drywettext_idlist[7] = IDC_DRYWET_TEXT_8;
	drywettext_idlist[8] = IDC_DRYWET_TEXT_9;
	drywettext_idlist[9] = IDC_DRYWET_TEXT_10;
	drywettext_idlist[10] = IDC_DRYWET_TEXT_11;
	drywettext_idlist[11] = IDC_DRYWET_TEXT_12;
	drywettext_idlist[12] = IDC_DRYWET_TEXT_13;
	drywettext_idlist[13] = IDC_DRYWET_TEXT_14;
	drywettext_idlist[14] = IDC_DRYWET_TEXT_15;
	drywettext_idlist[15] = IDC_DRYWET_TEXT_16;

	drywettext_list[0] = &m_drywet_text_1;
	drywettext_list[1] = &m_drywet_text_2;
	drywettext_list[2] = &m_drywet_text_3;
	drywettext_list[3] = &m_drywet_text_4;
	drywettext_list[4] = &m_drywet_text_5;
	drywettext_list[5] = &m_drywet_text_6;
	drywettext_list[6] = &m_drywet_text_7;
	drywettext_list[7] = &m_drywet_text_8;
	drywettext_list[8] = &m_drywet_text_9;
	drywettext_list[9] = &m_drywet_text_10;
	drywettext_list[10] = &m_drywet_text_11;
	drywettext_list[11] = &m_drywet_text_12;
	drywettext_list[12] = &m_drywet_text_13;
	drywettext_list[13] = &m_drywet_text_14;
	drywettext_list[14] = &m_drywet_text_15;
	drywettext_list[15] = &m_drywet_text_16;

	for (chan = 0; chan < 16; chan++)
	{
		block_list[chan] = -1;
	}

	m_pToolTip = NULL;
	drywet_inserted = false;
}


void EffectFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EffectFilterDlg)
	DDX_Control(pDX, IDC_VOICE_1, m_voice_1);
	DDX_Control(pDX, IDC_VOICE_2, m_voice_2);
	DDX_Control(pDX, IDC_VOICE_3, m_voice_3);
	DDX_Control(pDX, IDC_VOICE_4, m_voice_4);
	DDX_Control(pDX, IDC_VOICE_5, m_voice_5);
	DDX_Control(pDX, IDC_VOICE_6, m_voice_6);
	DDX_Control(pDX, IDC_VOICE_7, m_voice_7);
	DDX_Control(pDX, IDC_VOICE_8, m_voice_8);
	DDX_Control(pDX, IDC_VOICE_9, m_voice_9);
	DDX_Control(pDX, IDC_VOICE_10, m_voice_10);
	DDX_Control(pDX, IDC_VOICE_11, m_voice_11);
	DDX_Control(pDX, IDC_VOICE_12, m_voice_12);
	DDX_Control(pDX, IDC_VOICE_13, m_voice_13);
	DDX_Control(pDX, IDC_VOICE_14, m_voice_14);
	DDX_Control(pDX, IDC_VOICE_15, m_voice_15);
	DDX_Control(pDX, IDC_VOICE_16, m_voice_16);
	DDX_Control(pDX, IDC_DRYWET_TEXT_1, m_drywet_text_1);
	DDX_Control(pDX, IDC_DRYWET_TEXT_2, m_drywet_text_2);
	DDX_Control(pDX, IDC_DRYWET_TEXT_3, m_drywet_text_3);
	DDX_Control(pDX, IDC_DRYWET_TEXT_4, m_drywet_text_4);
	DDX_Control(pDX, IDC_DRYWET_TEXT_5, m_drywet_text_5);
	DDX_Control(pDX, IDC_DRYWET_TEXT_6, m_drywet_text_6);
	DDX_Control(pDX, IDC_DRYWET_TEXT_7, m_drywet_text_7);
	DDX_Control(pDX, IDC_DRYWET_TEXT_8, m_drywet_text_8);
	DDX_Control(pDX, IDC_DRYWET_TEXT_9, m_drywet_text_9);
	DDX_Control(pDX, IDC_DRYWET_TEXT_10, m_drywet_text_10);
	DDX_Control(pDX, IDC_DRYWET_TEXT_11, m_drywet_text_11);
	DDX_Control(pDX, IDC_DRYWET_TEXT_12, m_drywet_text_12);
	DDX_Control(pDX, IDC_DRYWET_TEXT_13, m_drywet_text_13);
	DDX_Control(pDX, IDC_DRYWET_TEXT_14, m_drywet_text_14);
	DDX_Control(pDX, IDC_DRYWET_TEXT_15, m_drywet_text_15);
	DDX_Control(pDX, IDC_DRYWET_TEXT_16, m_drywet_text_16);
	DDX_Control(pDX, IDC_REVERB_1, m_reverb_1);
	DDX_Control(pDX, IDC_REVERB_2, m_reverb_2);
	DDX_Control(pDX, IDC_REVERB_3, m_reverb_3);
	DDX_Control(pDX, IDC_REVERB_4, m_reverb_4);
	DDX_Control(pDX, IDC_REVERB_5, m_reverb_5);
	DDX_Control(pDX, IDC_REVERB_6, m_reverb_6);
	DDX_Control(pDX, IDC_REVERB_7, m_reverb_7);
	DDX_Control(pDX, IDC_REVERB_8, m_reverb_8);
	DDX_Control(pDX, IDC_REVERB_9, m_reverb_9);
	DDX_Control(pDX, IDC_REVERB_10, m_reverb_10);
	DDX_Control(pDX, IDC_REVERB_11, m_reverb_11);
	DDX_Control(pDX, IDC_REVERB_12, m_reverb_12);
	DDX_Control(pDX, IDC_REVERB_13, m_reverb_13);
	DDX_Control(pDX, IDC_REVERB_14, m_reverb_14);
	DDX_Control(pDX, IDC_REVERB_15, m_reverb_15);
	DDX_Control(pDX, IDC_REVERB_16, m_reverb_16);
	DDX_Control(pDX, IDC_CHORUS_1, m_chorus_1);
	DDX_Control(pDX, IDC_CHORUS_2, m_chorus_2);
	DDX_Control(pDX, IDC_CHORUS_3, m_chorus_3);
	DDX_Control(pDX, IDC_CHORUS_4, m_chorus_4);
	DDX_Control(pDX, IDC_CHORUS_5, m_chorus_5);
	DDX_Control(pDX, IDC_CHORUS_6, m_chorus_6);
	DDX_Control(pDX, IDC_CHORUS_7, m_chorus_7);
	DDX_Control(pDX, IDC_CHORUS_8, m_chorus_8);
	DDX_Control(pDX, IDC_CHORUS_9, m_chorus_9);
	DDX_Control(pDX, IDC_CHORUS_10, m_chorus_10);
	DDX_Control(pDX, IDC_CHORUS_11, m_chorus_11);
	DDX_Control(pDX, IDC_CHORUS_12, m_chorus_12);
	DDX_Control(pDX, IDC_CHORUS_13, m_chorus_13);
	DDX_Control(pDX, IDC_CHORUS_14, m_chorus_14);
	DDX_Control(pDX, IDC_CHORUS_15, m_chorus_15);
	DDX_Control(pDX, IDC_CHORUS_16, m_chorus_16);
	DDX_Control(pDX, IDC_VARIATION_1, m_variation_1);
	DDX_Control(pDX, IDC_VARIATION_2, m_variation_2);
	DDX_Control(pDX, IDC_VARIATION_3, m_variation_3);
	DDX_Control(pDX, IDC_VARIATION_4, m_variation_4);
	DDX_Control(pDX, IDC_VARIATION_5, m_variation_5);
	DDX_Control(pDX, IDC_VARIATION_6, m_variation_6);
	DDX_Control(pDX, IDC_VARIATION_7, m_variation_7);
	DDX_Control(pDX, IDC_VARIATION_8, m_variation_8);
	DDX_Control(pDX, IDC_VARIATION_9, m_variation_9);
	DDX_Control(pDX, IDC_VARIATION_10, m_variation_10);
	DDX_Control(pDX, IDC_VARIATION_11, m_variation_11);
	DDX_Control(pDX, IDC_VARIATION_12, m_variation_12);
	DDX_Control(pDX, IDC_VARIATION_13, m_variation_13);
	DDX_Control(pDX, IDC_VARIATION_14, m_variation_14);
	DDX_Control(pDX, IDC_VARIATION_15, m_variation_15);
	DDX_Control(pDX, IDC_VARIATION_16, m_variation_16);
	DDX_Control(pDX, IDC_DRYWET_1, m_drywet_1);
	DDX_Control(pDX, IDC_DRYWET_2, m_drywet_2);
	DDX_Control(pDX, IDC_DRYWET_3, m_drywet_3);
	DDX_Control(pDX, IDC_DRYWET_4, m_drywet_4);
	DDX_Control(pDX, IDC_DRYWET_5, m_drywet_5);
	DDX_Control(pDX, IDC_DRYWET_6, m_drywet_6);
	DDX_Control(pDX, IDC_DRYWET_7, m_drywet_7);
	DDX_Control(pDX, IDC_DRYWET_8, m_drywet_8);
	DDX_Control(pDX, IDC_DRYWET_9, m_drywet_9);
	DDX_Control(pDX, IDC_DRYWET_10, m_drywet_10);
	DDX_Control(pDX, IDC_DRYWET_11, m_drywet_11);
	DDX_Control(pDX, IDC_DRYWET_12, m_drywet_12);
	DDX_Control(pDX, IDC_DRYWET_13, m_drywet_13);
	DDX_Control(pDX, IDC_DRYWET_14, m_drywet_14);
	DDX_Control(pDX, IDC_DRYWET_15, m_drywet_15);
	DDX_Control(pDX, IDC_DRYWET_16, m_drywet_16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EffectFilterDlg, CDialog)
	//{{AFX_MSG_MAP(EffectFilterDlg)
	ON_EN_CHANGE(IDC_REVERB_1, OnChangeReverb1)
	ON_EN_CHANGE(IDC_REVERB_2, OnChangeReverb2)
	ON_EN_CHANGE(IDC_REVERB_3, OnChangeReverb3)
	ON_EN_CHANGE(IDC_REVERB_4, OnChangeReverb4)
	ON_EN_CHANGE(IDC_REVERB_5, OnChangeReverb5)
	ON_EN_CHANGE(IDC_REVERB_6, OnChangeReverb6)
	ON_EN_CHANGE(IDC_REVERB_7, OnChangeReverb7)
	ON_EN_CHANGE(IDC_REVERB_8, OnChangeReverb8)
	ON_EN_CHANGE(IDC_REVERB_9, OnChangeReverb9)
	ON_EN_CHANGE(IDC_REVERB_10, OnChangeReverb10)
	ON_EN_CHANGE(IDC_REVERB_11, OnChangeReverb11)
	ON_EN_CHANGE(IDC_REVERB_12, OnChangeReverb12)
	ON_EN_CHANGE(IDC_REVERB_13, OnChangeReverb13)
	ON_EN_CHANGE(IDC_REVERB_14, OnChangeReverb14)
	ON_EN_CHANGE(IDC_REVERB_15, OnChangeReverb15)
	ON_EN_CHANGE(IDC_REVERB_16, OnChangeReverb16)
	ON_EN_CHANGE(IDC_CHORUS_1, OnChangeChorus1)
	ON_EN_CHANGE(IDC_CHORUS_2, OnChangeChorus2)
	ON_EN_CHANGE(IDC_CHORUS_3, OnChangeChorus3)
	ON_EN_CHANGE(IDC_CHORUS_4, OnChangeChorus4)
	ON_EN_CHANGE(IDC_CHORUS_5, OnChangeChorus5)
	ON_EN_CHANGE(IDC_CHORUS_6, OnChangeChorus6)
	ON_EN_CHANGE(IDC_CHORUS_7, OnChangeChorus7)
	ON_EN_CHANGE(IDC_CHORUS_8, OnChangeChorus8)
	ON_EN_CHANGE(IDC_CHORUS_9, OnChangeChorus9)
	ON_EN_CHANGE(IDC_CHORUS_10, OnChangeChorus10)
	ON_EN_CHANGE(IDC_CHORUS_11, OnChangeChorus11)
	ON_EN_CHANGE(IDC_CHORUS_12, OnChangeChorus12)
	ON_EN_CHANGE(IDC_CHORUS_13, OnChangeChorus13)
	ON_EN_CHANGE(IDC_CHORUS_14, OnChangeChorus14)
	ON_EN_CHANGE(IDC_CHORUS_15, OnChangeChorus15)
	ON_EN_CHANGE(IDC_CHORUS_16, OnChangeChorus16)
	ON_EN_CHANGE(IDC_VARIATION_1, OnChangeVariation1)
	ON_EN_CHANGE(IDC_VARIATION_2, OnChangeVariation2)
	ON_EN_CHANGE(IDC_VARIATION_3, OnChangeVariation3)
	ON_EN_CHANGE(IDC_VARIATION_4, OnChangeVariation4)
	ON_EN_CHANGE(IDC_VARIATION_5, OnChangeVariation5)
	ON_EN_CHANGE(IDC_VARIATION_6, OnChangeVariation6)
	ON_EN_CHANGE(IDC_VARIATION_7, OnChangeVariation7)
	ON_EN_CHANGE(IDC_VARIATION_8, OnChangeVariation8)
	ON_EN_CHANGE(IDC_VARIATION_9, OnChangeVariation9)
	ON_EN_CHANGE(IDC_VARIATION_10, OnChangeVariation10)
	ON_EN_CHANGE(IDC_VARIATION_11, OnChangeVariation11)
	ON_EN_CHANGE(IDC_VARIATION_12, OnChangeVariation12)
	ON_EN_CHANGE(IDC_VARIATION_13, OnChangeVariation13)
	ON_EN_CHANGE(IDC_VARIATION_14, OnChangeVariation14)
	ON_EN_CHANGE(IDC_VARIATION_15, OnChangeVariation15)
	ON_EN_CHANGE(IDC_VARIATION_16, OnChangeVariation16)
	ON_EN_CHANGE(IDC_DRYWET_1, OnChangeDryWet1)
	ON_EN_CHANGE(IDC_DRYWET_2, OnChangeDryWet2)
	ON_EN_CHANGE(IDC_DRYWET_3, OnChangeDryWet3)
	ON_EN_CHANGE(IDC_DRYWET_4, OnChangeDryWet4)
	ON_EN_CHANGE(IDC_DRYWET_5, OnChangeDryWet5)
	ON_EN_CHANGE(IDC_DRYWET_6, OnChangeDryWet6)
	ON_EN_CHANGE(IDC_DRYWET_7, OnChangeDryWet7)
	ON_EN_CHANGE(IDC_DRYWET_8, OnChangeDryWet8)
	ON_EN_CHANGE(IDC_DRYWET_9, OnChangeDryWet9)
	ON_EN_CHANGE(IDC_DRYWET_10, OnChangeDryWet10)
	ON_EN_CHANGE(IDC_DRYWET_11, OnChangeDryWet11)
	ON_EN_CHANGE(IDC_DRYWET_12, OnChangeDryWet12)
	ON_EN_CHANGE(IDC_DRYWET_13, OnChangeDryWet13)
	ON_EN_CHANGE(IDC_DRYWET_14, OnChangeDryWet14)
	ON_EN_CHANGE(IDC_DRYWET_15, OnChangeDryWet15)
	ON_EN_CHANGE(IDC_DRYWET_16, OnChangeDryWet16)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL EffectFilterDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (NULL != m_pToolTip)
	{
		m_pToolTip->RelayEvent(pMsg);
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL EffectFilterDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString text;

	SetDlgItemText(IDC_CHANNEL,GlobalUtilities::get_resource_string(IDS_CHANNEL));
	SetDlgItemText(IDC_VOICE_TEXT,"Voice");

	text = "Reverb";
	text+= (char)0x0d;
	text+= (char)0x0a;
	text+= "(Ctrl. 91)";
	SetDlgItemText(IDC_CTRL91,text);

	text = "Chorus";
	text+= (char)0x0d;
	text+= (char)0x0a;
	text+= "(Ctrl. 93)";
	SetDlgItemText(IDC_CTRL93,text);

	text = "Variation";
	text+= (char)0x0d;
	text+= (char)0x0a;
	text+= "(Ctrl. 94)";
	SetDlgItemText(IDC_CTRL94,text);

	text = "Insertion";
	text+= (char)0x0d;
	text+= (char)0x0a;
	text+= "(Dry/Wet)";
	SetDlgItemText(IDC_DRYWET,text);

	SetDlgItemText(IDC_TEXT_1,"1");
	SetDlgItemText(IDC_TEXT_2,"2");
	SetDlgItemText(IDC_TEXT_3,"3");
	SetDlgItemText(IDC_TEXT_4,"4");
	SetDlgItemText(IDC_TEXT_5,"5");
	SetDlgItemText(IDC_TEXT_6,"6");
	SetDlgItemText(IDC_TEXT_7,"7");
	SetDlgItemText(IDC_TEXT_8,"8");
	SetDlgItemText(IDC_TEXT_9,"9");
	SetDlgItemText(IDC_TEXT_10,"10");
	SetDlgItemText(IDC_TEXT_11,"11");
	SetDlgItemText(IDC_TEXT_12,"12");
	SetDlgItemText(IDC_TEXT_13,"13");
	SetDlgItemText(IDC_TEXT_14,"14");
	SetDlgItemText(IDC_TEXT_15,"15");
	SetDlgItemText(IDC_TEXT_16,"16");

	int chan;

	bool is_variation_sysex;
	bool is_variation_system;
	bool is_variation_insertion;
	int variation_insertion_channel;
	
	bool variation_defined = hpmfi->is_variation_effect(&is_variation_sysex, 
														&is_variation_system, 
														&is_variation_insertion, 
														&variation_insertion_channel);
	bool insertion_defined[16];

	for (chan=0; chan<16; chan++)
	{
		int block;
		insertion_defined[chan] = hpmfi->insertion_sysex_defined(chan,&block);
		if (is_variation_insertion && (variation_insertion_channel==chan))
		{
			insertion_defined[chan] = true;
		}

		reverb_list[chan]->SetLimitText(3);
		chorus_list[chan]->SetLimitText(3);
		variation_list[chan]->SetLimitText(3);
		drywet_list[chan]->SetLimitText(3);
		int reverb, chorus, variation;

		hpmfi->get_reverb_chorus_variation_value(chan, &reverb, &chorus, &variation);

		if (!(hpmfi->mute)[chan])
		{
			SetDlgItemText(idc_voice_type[chan],(hpmfi->patchname)[chan]);
			SetDlgItemInt(reverb_idlist[chan],reverb,FALSE);
			SetDlgItemInt(chorus_idlist[chan],chorus,FALSE);
			if (variation_defined)
			{ 
				SetDlgItemInt(variation_idlist[chan],variation,FALSE);
			}
			else
			{
				variation_list[chan]->SetReadOnly(true);
			}

			if (insertion_defined[chan])
			{ // init edit-box
				int drywet;
				if (is_variation_insertion && (variation_insertion_channel==chan))
				{
					block = -2;
				}
				CString drywet_text = hpmfi->get_drywet_value(block,&drywet);
				block_list[chan] = block;
				if (drywet==-1)
				{
					SetDlgItemText(drywet_idlist[chan],"---");
				}
				else
				{
					SetDlgItemInt(drywet_idlist[chan],drywet,FALSE);
				}
				SetDlgItemText(drywettext_idlist[chan],drywet_text);
			}
			else
			{
				drywet_list[chan]->SetReadOnly(true);
			}
			if (variation_defined && is_variation_insertion)
			{
				SetDlgItemText(variation_idlist[chan],"");
				variation_list[chan]->SetReadOnly(true);
				if (chan == variation_insertion_channel)
				{
					drywettext_list[chan]->SetReadOnly(true);
				}
			}
		}
		else
		{
			SetDlgItemText(idc_voice_type[chan],"");
			reverb_list[chan]->EnableWindow(false);
			chorus_list[chan]->EnableWindow(false);
			variation_list[chan]->EnableWindow(false);
			drywet_list[chan]->EnableWindow(false);
			drywettext_list[chan]->EnableWindow(false);
		}
	}

	// last init:
	for(chan=0; chan<16; chan++)
	{
		reverb_changed[chan] = -1;
		chorus_changed[chan] = -1;
		variation_changed[chan] = -1;
		drywet_changed[chan] = -1;
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



/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten EffectFilterDlg 

void EffectFilterDlg::OnOK() 
{
	if (m_pToolTip != NULL)
	{
		delete m_pToolTip;
		m_pToolTip = NULL;
	}

	if (!something_changed) EndDialog(0);

	SetCursor(hCursorWait);
	hpmfi->eval_change_effectfilter_controller(reverb_changed, chorus_changed, variation_changed);
	hpmfi->eval_change_effectfilter_drywet(block_list, drywet_changed);
	if (drywet_inserted)
	{
		int no_double_notes;
		int no_pitch_wheels;
		hpmfi->eval_xg_convert(&no_double_notes, &no_pitch_wheels);
	}
	SetCursor(hCursorOld);
	EndDialog(1);
}

void EffectFilterDlg::OnCancel() 
{
	if (m_pToolTip != NULL)
	{
		delete m_pToolTip;
		m_pToolTip = NULL;
	}

	if (drywet_inserted)
	{
		int no_double_notes;
		int no_pitch_wheels;
		hpmfi->eval_xg_convert(&no_double_notes, &no_pitch_wheels);
	}

	EndDialog(drywet_inserted?1:0);
}


void EffectFilterDlg::ChangeReverb(int chan)
{
	char val_str[10];
	int val_number;
	int l = reverb_list[chan]->LineLength();
	int len = reverb_list[chan]->GetLine(0, val_str,l);
	val_str[len] = 0;
	val_number = GlobalUtilities::compute_number(val_str,l);
	if (val_number<0 || val_number>127)
	{ // Syntax error, use 0 or 127
		val_number = val_number<0?0:127;
		SetDlgItemInt(reverb_idlist[chan],val_number);
	}
	reverb_changed[chan] = val_number;
	something_changed = true;
}

void EffectFilterDlg::OnChangeReverb1() 
{
	ChangeReverb(0);
}

void EffectFilterDlg::OnChangeReverb2() 
{
	ChangeReverb(1);
}

void EffectFilterDlg::OnChangeReverb3() 
{
	ChangeReverb(2);
}

void EffectFilterDlg::OnChangeReverb4() 
{
	ChangeReverb(3);
}

void EffectFilterDlg::OnChangeReverb5() 
{
	ChangeReverb(4);
}

void EffectFilterDlg::OnChangeReverb6() 
{
	ChangeReverb(5);
}

void EffectFilterDlg::OnChangeReverb7() 
{
	ChangeReverb(6);
}

void EffectFilterDlg::OnChangeReverb8() 
{
	ChangeReverb(7);
}

void EffectFilterDlg::OnChangeReverb9() 
{
	ChangeReverb(8);
}

void EffectFilterDlg::OnChangeReverb10() 
{
	ChangeReverb(9);
}

void EffectFilterDlg::OnChangeReverb11() 
{
	ChangeReverb(10);
}

void EffectFilterDlg::OnChangeReverb12() 
{
	ChangeReverb(11);
}

void EffectFilterDlg::OnChangeReverb13() 
{
	ChangeReverb(12);
}

void EffectFilterDlg::OnChangeReverb14() 
{
	ChangeReverb(13);
}

void EffectFilterDlg::OnChangeReverb15() 
{
	ChangeReverb(14);
}

void EffectFilterDlg::OnChangeReverb16() 
{
	ChangeReverb(15);
}

void EffectFilterDlg::ChangeChorus(int chan)
{
	char val_str[10];
	int val_number;
	int l = chorus_list[chan]->LineLength();
	int len = chorus_list[chan]->GetLine(0, val_str,l);
	val_str[len] = 0;
	val_number = GlobalUtilities::compute_number(val_str,l);
	if (val_number<0 || val_number>127)
	{ // Syntax error, use 0 or 127
		val_number = val_number<0?0:127;
		SetDlgItemInt(chorus_idlist[chan],val_number,FALSE);
	}
	chorus_changed[chan] = val_number;
	something_changed = true;
}

void EffectFilterDlg::OnChangeChorus1() 
{
	ChangeChorus(0);
}

void EffectFilterDlg::OnChangeChorus2() 
{
	ChangeChorus(1);
}

void EffectFilterDlg::OnChangeChorus3() 
{
	ChangeChorus(2);
}

void EffectFilterDlg::OnChangeChorus4() 
{
	ChangeChorus(3);
}

void EffectFilterDlg::OnChangeChorus5() 
{
	ChangeChorus(4);
}

void EffectFilterDlg::OnChangeChorus6() 
{
	ChangeChorus(5);
}

void EffectFilterDlg::OnChangeChorus7() 
{
	ChangeChorus(6);
}

void EffectFilterDlg::OnChangeChorus8() 
{
	ChangeChorus(7);
}

void EffectFilterDlg::OnChangeChorus9() 
{
	ChangeChorus(8);
}

void EffectFilterDlg::OnChangeChorus10() 
{
	ChangeChorus(9);
}

void EffectFilterDlg::OnChangeChorus11() 
{
	ChangeChorus(10);
}

void EffectFilterDlg::OnChangeChorus12() 
{
	ChangeChorus(11);
}

void EffectFilterDlg::OnChangeChorus13() 
{
	ChangeChorus(12);
}

void EffectFilterDlg::OnChangeChorus14() 
{
	ChangeChorus(13);
}

void EffectFilterDlg::OnChangeChorus15() 
{
	ChangeChorus(14);
}

void EffectFilterDlg::OnChangeChorus16() 
{
	ChangeChorus(15);
}

void EffectFilterDlg::ChangeVariation(int chan)
{
	char val_str[10];
	int val_number;
	int l = variation_list[chan]->LineLength();
	int len = variation_list[chan]->GetLine(0, val_str,l);
	val_str[len] = 0;
	val_number = GlobalUtilities::compute_number(val_str,l);
	if (val_number<0 || val_number>127)
	{ // Syntax error, use 0 or 127
		val_number = val_number<0?0:127;
		SetDlgItemInt(variation_idlist[chan],val_number,FALSE);
	}
	variation_changed[chan] = val_number;
	something_changed = true;
}

void EffectFilterDlg::OnChangeVariation1() 
{
	ChangeVariation(0);
}

void EffectFilterDlg::OnChangeVariation2() 
{
	ChangeVariation(1);
}

void EffectFilterDlg::OnChangeVariation3() 
{
	ChangeVariation(2);
}

void EffectFilterDlg::OnChangeVariation4() 
{
	ChangeVariation(3);
}

void EffectFilterDlg::OnChangeVariation5() 
{
	ChangeVariation(4);
}

void EffectFilterDlg::OnChangeVariation6() 
{
	ChangeVariation(5);
}

void EffectFilterDlg::OnChangeVariation7() 
{
	ChangeVariation(6);
}

void EffectFilterDlg::OnChangeVariation8() 
{
	ChangeVariation(7);
}

void EffectFilterDlg::OnChangeVariation9() 
{
	ChangeVariation(8);
}

void EffectFilterDlg::OnChangeVariation10() 
{
	ChangeVariation(9);
}

void EffectFilterDlg::OnChangeVariation11() 
{
	ChangeVariation(10);
}

void EffectFilterDlg::OnChangeVariation12() 
{
	ChangeVariation(11);
}

void EffectFilterDlg::OnChangeVariation13() 
{
	ChangeVariation(12);
}

void EffectFilterDlg::OnChangeVariation14() 
{
	ChangeVariation(13);
}

void EffectFilterDlg::OnChangeVariation15() 
{
	ChangeVariation(14);
}

void EffectFilterDlg::OnChangeVariation16() 
{
	ChangeVariation(15);
}

void EffectFilterDlg::ChangeDryWet(int chan)
{
	char val_str[10];
	int val_number;
	int l = drywet_list[chan]->LineLength();
	int len = drywet_list[chan]->GetLine(0, val_str,l);
	val_str[len] = 0;
	if (strcmp(val_str,"---")!=0)
	{
		val_number = GlobalUtilities::compute_number(val_str,l);
		if (val_number<0 || val_number>127)
		{ // Syntax error, use 0 or 127
			val_number = val_number<0?0:127;
			SetDlgItemInt(drywet_idlist[chan],val_number,FALSE);
		}
		drywet_inserted = drywet_inserted || hpmfi->check_and_insert_drywet(chan);
		drywet_changed[chan] = val_number;
		SetDlgItemText(drywettext_idlist[chan],hpmfi->get_drywet_text(val_number));
		something_changed = true;
	}
}

void EffectFilterDlg::OnChangeDryWet1() 
{
	ChangeDryWet(0);
}

void EffectFilterDlg::OnChangeDryWet2() 
{
	ChangeDryWet(1);
}

void EffectFilterDlg::OnChangeDryWet3() 
{
	ChangeDryWet(2);
}

void EffectFilterDlg::OnChangeDryWet4() 
{
	ChangeDryWet(3);
}

void EffectFilterDlg::OnChangeDryWet5() 
{
	ChangeDryWet(4);
}

void EffectFilterDlg::OnChangeDryWet6() 
{
	ChangeDryWet(5);
}

void EffectFilterDlg::OnChangeDryWet7() 
{
	ChangeDryWet(6);
}

void EffectFilterDlg::OnChangeDryWet8() 
{
	ChangeDryWet(7);
}

void EffectFilterDlg::OnChangeDryWet9() 
{
	ChangeDryWet(8);
}

void EffectFilterDlg::OnChangeDryWet10() 
{
	ChangeDryWet(9);
}

void EffectFilterDlg::OnChangeDryWet11() 
{
	ChangeDryWet(10);
}

void EffectFilterDlg::OnChangeDryWet12() 
{
	ChangeDryWet(11);
}

void EffectFilterDlg::OnChangeDryWet13() 
{
	ChangeDryWet(12);
}

void EffectFilterDlg::OnChangeDryWet14() 
{
	ChangeDryWet(13);
}

void EffectFilterDlg::OnChangeDryWet15() 
{
	ChangeDryWet(14);
}

void EffectFilterDlg::OnChangeDryWet16() 
{
	ChangeDryWet(15);
}


