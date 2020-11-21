// QuantizeDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "QuantizeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CQuantizeDlg 


CQuantizeDlg::CQuantizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQuantizeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQuantizeDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT

	m_pToolTip = NULL;

	int i;

	// inializes membervariable list m_voice_type

	m_voice_type[0] = &m_type1;
	m_voice_type[1] = &m_type2;
	m_voice_type[2] = &m_type3;
	m_voice_type[3] = &m_type4;
	m_voice_type[4] = &m_type5;
	m_voice_type[5] = &m_type6;
	m_voice_type[6] = &m_type7;
	m_voice_type[7] = &m_type8;
	m_voice_type[8] = &m_type9;
	m_voice_type[9] = &m_type10;
	m_voice_type[10] = &m_type11;
	m_voice_type[11] = &m_type12;
	m_voice_type[12] = &m_type13;
	m_voice_type[13] = &m_type14;
	m_voice_type[14] = &m_type15;
	m_voice_type[15] = &m_type16;

	m_check_chan[0] = &m_check_chan1;
	m_check_chan[1] = &m_check_chan2;
	m_check_chan[2] = &m_check_chan3;
	m_check_chan[3] = &m_check_chan4;
	m_check_chan[4] = &m_check_chan5;
	m_check_chan[5] = &m_check_chan6;
	m_check_chan[6] = &m_check_chan7;
	m_check_chan[7] = &m_check_chan8;
	m_check_chan[8] = &m_check_chan9;
	m_check_chan[9] = &m_check_chan10;
	m_check_chan[10] = &m_check_chan11;
	m_check_chan[11] = &m_check_chan12;
	m_check_chan[12] = &m_check_chan13;
	m_check_chan[13] = &m_check_chan14;
	m_check_chan[14] = &m_check_chan15;
	m_check_chan[15] = &m_check_chan16;

	m_check_raster[0] = &m_check_whole;
	m_check_raster[1] = &m_check_half;
	m_check_raster[2] = &m_check_half_triole;
	m_check_raster[3] = &m_check_quarter;
	m_check_raster[4] = &m_check_quarter_triole;
	m_check_raster[5] = &m_check_eightteenth;
	m_check_raster[6] = &m_check_eightteenth_triole;
	m_check_raster[7] = &m_check_16th;
	m_check_raster[8] = &m_check_16th_triole;
	m_check_raster[9] = &m_check_32th;
	m_check_raster[10] = &m_check_64th;

	for (i=0; i<16; i++)
	{
		destroyed_check[i] = false;
	}

	raster_code[0] = 1;
	raster_code[1] = 2;
	raster_code[2] = 23;
	raster_code[3] = 4;
	raster_code[4] = 43;
	raster_code[5] = 8;
	raster_code[6] = 83;
	raster_code[7] = 16;
	raster_code[8] = 163;
	raster_code[9] = 32;
	raster_code[10] = 64;

	raster_ticks[0] = 1920;
	raster_ticks[1] = 960;
	raster_ticks[2] = 640;
	raster_ticks[3] = 480;
	raster_ticks[4] = 320;
	raster_ticks[5] = 240;
	raster_ticks[6] = 160;
	raster_ticks[7] = 120;
	raster_ticks[8] = 80;
	raster_ticks[9] = 60;
	raster_ticks[10] = 30;

	chan = -1;
	length_code = -1;
	starts = false;
	note_length = false;
}


void CQuantizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQuantizeDlg)
	DDX_Control(pDX, IDC_CHECK_16TH_TRIOLE, m_check_16th_triole);
	DDX_Control(pDX, IDC_CHECK_START_TIME, m_check_start_time);
	DDX_Control(pDX, IDC_CHECK_NOTE_LENGTH, m_check_note_length);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_CHECK_64TH, m_check_64th);
	DDX_Control(pDX, IDC_CHECK_32th, m_check_32th);
	DDX_Control(pDX, IDC_CHECK_16TH, m_check_16th);
	DDX_Control(pDX, IDC_CHECK_EIGHTTEENTH_TRIOLE, m_check_eightteenth_triole);
	DDX_Control(pDX, IDC_CHECK_EIGHTTEENTH, m_check_eightteenth);
	DDX_Control(pDX, IDC_CHECK_QUARTER_TRIOLE, m_check_quarter_triole);
	DDX_Control(pDX, IDC_CHECK_HALF_TRIOLE, m_check_half_triole);
	DDX_Control(pDX, IDC_CHECK_QUARTER, m_check_quarter);
	DDX_Control(pDX, IDC_CHECK_HALF, m_check_half);
	DDX_Control(pDX, IDC_CHECK_WHOLE, m_check_whole);
	DDX_Control(pDX, IDC_CHECK_CHAN1, m_check_chan1);
	DDX_Control(pDX, IDC_CHECK_CHAN2, m_check_chan2);
	DDX_Control(pDX, IDC_CHECK_CHAN3, m_check_chan3);
	DDX_Control(pDX, IDC_CHECK_CHAN4, m_check_chan4);
	DDX_Control(pDX, IDC_CHECK_CHAN5, m_check_chan5);
	DDX_Control(pDX, IDC_CHECK_CHAN6, m_check_chan6);
	DDX_Control(pDX, IDC_CHECK_CHAN7, m_check_chan7);
	DDX_Control(pDX, IDC_CHECK_CHAN8, m_check_chan8);
	DDX_Control(pDX, IDC_CHECK_CHAN9, m_check_chan9);
	DDX_Control(pDX, IDC_CHECK_CHAN10, m_check_chan10);
	DDX_Control(pDX, IDC_CHECK_CHAN11, m_check_chan11);
	DDX_Control(pDX, IDC_CHECK_CHAN12, m_check_chan12);
	DDX_Control(pDX, IDC_CHECK_CHAN13, m_check_chan13);
	DDX_Control(pDX, IDC_CHECK_CHAN14, m_check_chan14);
	DDX_Control(pDX, IDC_CHECK_CHAN15, m_check_chan15);
	DDX_Control(pDX, IDC_CHECK_CHAN16, m_check_chan16);
	DDX_Control(pDX, IDC_TYPE1, m_type1);
	DDX_Control(pDX, IDC_TYPE2, m_type2);
	DDX_Control(pDX, IDC_TYPE3, m_type3);
	DDX_Control(pDX, IDC_TYPE4, m_type4);
	DDX_Control(pDX, IDC_TYPE5, m_type5);
	DDX_Control(pDX, IDC_TYPE6, m_type6);
	DDX_Control(pDX, IDC_TYPE7, m_type7);
	DDX_Control(pDX, IDC_TYPE8, m_type8);
	DDX_Control(pDX, IDC_TYPE9, m_type9);
	DDX_Control(pDX, IDC_TYPE10, m_type10);
	DDX_Control(pDX, IDC_TYPE11, m_type11);
	DDX_Control(pDX, IDC_TYPE12, m_type12);
	DDX_Control(pDX, IDC_TYPE13, m_type13);
	DDX_Control(pDX, IDC_TYPE14, m_type14);
	DDX_Control(pDX, IDC_TYPE15, m_type15);
	DDX_Control(pDX, IDC_TYPE16, m_type16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQuantizeDlg, CDialog)
	//{{AFX_MSG_MAP(CQuantizeDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_CHAN1, OnCheckChan1)
	ON_BN_CLICKED(IDC_CHECK_CHAN2, OnCheckChan2)
	ON_BN_CLICKED(IDC_CHECK_CHAN3, OnCheckChan3)
	ON_BN_CLICKED(IDC_CHECK_CHAN4, OnCheckChan4)
	ON_BN_CLICKED(IDC_CHECK_CHAN5, OnCheckChan5)
	ON_BN_CLICKED(IDC_CHECK_CHAN6, OnCheckChan6)
	ON_BN_CLICKED(IDC_CHECK_CHAN7, OnCheckChan7)
	ON_BN_CLICKED(IDC_CHECK_CHAN8, OnCheckChan8)
	ON_BN_CLICKED(IDC_CHECK_CHAN9, OnCheckChan9)
	ON_BN_CLICKED(IDC_CHECK_CHAN10, OnCheckChan10)
	ON_BN_CLICKED(IDC_CHECK_CHAN11, OnCheckChan11)
	ON_BN_CLICKED(IDC_CHECK_CHAN12, OnCheckChan12)
	ON_BN_CLICKED(IDC_CHECK_CHAN13, OnCheckChan13)
	ON_BN_CLICKED(IDC_CHECK_CHAN14, OnCheckChan14)
	ON_BN_CLICKED(IDC_CHECK_CHAN15, OnCheckChan15)
	ON_BN_CLICKED(IDC_CHECK_CHAN16, OnCheckChan16)
	ON_BN_CLICKED(IDC_CHECK_WHOLE, OnCheckWhole)
	ON_BN_CLICKED(IDC_CHECK_HALF, OnCheckHalf)
	ON_BN_CLICKED(IDC_CHECK_QUARTER, OnCheckQuarter)
	ON_BN_CLICKED(IDC_CHECK_HALF_TRIOLE, OnCheckHalfTriole)
	ON_BN_CLICKED(IDC_CHECK_EIGHTTEENTH, OnCheckEightteenth)
	ON_BN_CLICKED(IDC_CHECK_EIGHTTEENTH_TRIOLE, OnCheckEightteenthTriole)
	ON_BN_CLICKED(IDC_CHECK_16TH, OnCheck16th)
	ON_BN_CLICKED(IDC_CHECK_32th, OnCHECK32th)
	ON_BN_CLICKED(IDC_CHECK_64TH, OnCheck64th)
	ON_BN_CLICKED(IDC_CHECK_QUARTER_TRIOLE, OnCheckQuarterTriole)
	ON_BN_CLICKED(IDC_CHECK_NOTE_LENGTH, OnCheckNoteLength)
	ON_BN_CLICKED(IDC_CHECK_START_TIME, OnCheckStartTime)
	ON_BN_CLICKED(IDC_CHECK_16TH_TRIOLE, OnCheck16thTriole)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CQuantizeDlg 

BOOL CQuantizeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int i;

	// Set channel number text
	SetDlgItemText(IDC_TEXT_CHANNEL,GlobalUtilities::get_resource_string(IDS_CHANNEL));
	SetDlgItemText(IDC_TYPETEXT,"Voice");

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

	SetDlgItemText(IDC_WHOLE_TXT,"1");
	SetDlgItemText(IDC_HALF_TXT,"1/2");
	SetDlgItemText(IDC_HALF_TRIOLE_TXT,"1/2 Triole");
	SetDlgItemText(IDC_QUARTER_TXT,"1/4");
	SetDlgItemText(IDC_QUARTER_TRIOLE_TXT,"1/4 Triole");
	SetDlgItemText(IDC_EIGHTTEENTH_TXT,"1/8");
	SetDlgItemText(IDC_EIGHTTEENTH_TRIOLE_TXT,"1/8 Triole");
	SetDlgItemText(IDC_16TH_TXT,"1/16");
	SetDlgItemText(IDC_16TH_TRIOLE_TXT,"1/16 Triole");
	SetDlgItemText(IDC_32TH_TXT,"1/32");
	SetDlgItemText(IDC_64TH_TXT,"1/64");

	// initialize IDC Typetext-array

	idc_type[0] = IDC_TYPE1;
	idc_type[1] = IDC_TYPE2;
	idc_type[2] = IDC_TYPE3;
	idc_type[3] = IDC_TYPE4;
	idc_type[4] = IDC_TYPE5;
	idc_type[5] = IDC_TYPE6;
	idc_type[6] = IDC_TYPE7;
	idc_type[7] = IDC_TYPE8;
	idc_type[8] = IDC_TYPE9;
	idc_type[9] = IDC_TYPE10;
	idc_type[10] = IDC_TYPE11;
	idc_type[11] = IDC_TYPE12;
	idc_type[12] = IDC_TYPE13;
	idc_type[13] = IDC_TYPE14;
	idc_type[14] = IDC_TYPE15;
	idc_type[15] = IDC_TYPE16;

	for (i=0; i<16; i++)
	{
		mute_val[i] = (hpmfi->mute)[i];

		if (mute_val[i])
		{
			SetDlgItemText(idc_type[i],"");
			m_check_chan[i]->DestroyWindow();
//			m_check_chan[i]->EnableWindow(FALSE);
			destroyed_check[i] = true;
		}
		else
		{
			SetDlgItemText(idc_type[i],(hpmfi->patchname)[i]);
			if (!((hpmfi->mlv_list[i]).melody))
			{
			m_check_chan[i]->DestroyWindow();
//				m_check_chan[i]->EnableWindow(FALSE);
				destroyed_check[i] = true;
			}
		}
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
	chan = -1;
	length_code = -1;
	starts = false;
	note_length = false;

	m_OK.EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CQuantizeDlg::OnOK() 
{
	if (m_pToolTip != NULL)
	{
		delete m_pToolTip;
		m_pToolTip = NULL;
	}
	
	EndDialog(1);
}

void CQuantizeDlg::OnCancel() 
{
	chan = -1;
	length_code = -1;
	starts = false;
	note_length = false;

	if (m_pToolTip != NULL)
	{
		delete m_pToolTip;
		m_pToolTip = NULL;
	}

	EndDialog(0);
}

void CQuantizeDlg::OnClose() 
{
	OnCancel();
}

BOOL CQuantizeDlg::PreTranslateMessage(MSG* pMsg)
{
	if (NULL != m_pToolTip)
	{
		m_pToolTip->RelayEvent(pMsg);
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CQuantizeDlg::check_chan(int selected_chan)
{
	int i, raster_index;
	for (i=0; i<16; i++)
	{
		if (destroyed_check[i])
		{
			continue;
		}
		if (i!=selected_chan)
		{
			m_check_chan[i]->SetCheck(0);
		}
	}

	int min_note_length = hpmfi->least_note_length(selected_chan);

	for (raster_index=1; raster_index<10; raster_index++)
	{ // Toleranz 10 Ticks
		if ((min_note_length>raster_ticks[raster_index]+10) && 
			(min_note_length<=raster_ticks[raster_index-1]+10))
		{
			break;
		}
	}

	for (i=0; i<10; i++)
	{
		m_check_raster[i]->SetCheck(0);
	}

	if (raster_index > 0)
	{
		m_check_raster[raster_index-1]->SetCheck(1);
		check_raster(raster_index-1);
	}
	chan = selected_chan;

	if (chan==-1||length_code==-1||(!starts&&!note_length))
	{
		m_OK.EnableWindow(false);
	}
	else
	{
		m_OK.EnableWindow(true);
	}
}

void CQuantizeDlg::OnCheckChan1() 
{
	if (m_check_chan[0]->GetCheck()==1)
	{
		check_chan(0);
	}
}

void CQuantizeDlg::OnCheckChan2() 
{
	if (m_check_chan[1]->GetCheck()==1)
	{
		check_chan(1);	
	}
}

void CQuantizeDlg::OnCheckChan3() 
{
	if (m_check_chan[2]->GetCheck()==1)
	{
		check_chan(2);	
	}
}

void CQuantizeDlg::OnCheckChan4() 
{
	if (m_check_chan[3]->GetCheck()==1)
	{
		check_chan(3);
	}
}

void CQuantizeDlg::OnCheckChan5() 
{
	if (m_check_chan[4]->GetCheck()==1)
	{
		check_chan(4);	
	}
}


void CQuantizeDlg::OnCheckChan6() 
{
	if (m_check_chan[5]->GetCheck()==1)
	{
		check_chan(5);	
	}
}


void CQuantizeDlg::OnCheckChan7() 
{
	if (m_check_chan[6]->GetCheck()==1)
	{
		check_chan(6);	
	}
}


void CQuantizeDlg::OnCheckChan8() 
{
	if (m_check_chan[7]->GetCheck()==1)
	{
		check_chan(7);	
	}
}


void CQuantizeDlg::OnCheckChan9() 
{
	if (m_check_chan[8]->GetCheck()==1)
	{
		check_chan(8);	
	}
}



void CQuantizeDlg::OnCheckChan10() 
{
	if (m_check_chan[9]->GetCheck()==1)
	{
		check_chan(9);	
	}
}


void CQuantizeDlg::OnCheckChan11() 
{
	if (m_check_chan[10]->GetCheck()==1)
	{
		check_chan(10);	
	}
}


void CQuantizeDlg::OnCheckChan12() 
{
	if (m_check_chan[11]->GetCheck()==1)
	{
		check_chan(11);	
	}
}


void CQuantizeDlg::OnCheckChan13() 
{
	if (m_check_chan[12]->GetCheck()==1)
	{
		check_chan(12);	
	}
}


void CQuantizeDlg::OnCheckChan14() 
{
	if (m_check_chan[13]->GetCheck()==1)
	{
		check_chan(13);	
	}
}


void CQuantizeDlg::OnCheckChan15() 
{
	if (m_check_chan[14]->GetCheck()==1)
	{
		check_chan(14);	
	}
}


void CQuantizeDlg::OnCheckChan16() 
{
	if (m_check_chan[15]->GetCheck()==1)
	{
		check_chan(15);	
	}
}


void CQuantizeDlg::check_raster(int raster_index)
{
	if (m_check_raster[raster_index]->GetCheck() != 1) return;

	int i;
	for (i=0; i<10; i++)
	{
		if (i != raster_index)
		{
			m_check_raster[i]->SetCheck(0);
		}
	}
	length_code = raster_code[raster_index];

	if (chan==-1||length_code==-1||(!starts&&!note_length))
	{
		m_OK.EnableWindow(false);
	}
	else
	{
		m_OK.EnableWindow(true);
	}
}



void CQuantizeDlg::OnCheckWhole() 
{
	check_raster(0);	
}

void CQuantizeDlg::OnCheckHalf() 
{
	check_raster(1);	
}

void CQuantizeDlg::OnCheckHalfTriole() 
{
	check_raster(2);	
}

void CQuantizeDlg::OnCheckQuarter() 
{
	check_raster(3);	
}

void CQuantizeDlg::OnCheckQuarterTriole() 
{
	check_raster(4);
}

void CQuantizeDlg::OnCheckEightteenth() 
{
	check_raster(5);	
}

void CQuantizeDlg::OnCheckEightteenthTriole() 
{
	check_raster(6);	
}

void CQuantizeDlg::OnCheck16th() 
{
	check_raster(7);	
}

void CQuantizeDlg::OnCheck16thTriole() 
{
	check_raster(8);	
}


void CQuantizeDlg::OnCHECK32th() 
{
	check_raster(9);	
}

void CQuantizeDlg::OnCheck64th() 
{
	check_raster(10);	
}


void CQuantizeDlg::OnCheckNoteLength() 
{
	note_length = (m_check_note_length.GetCheck()==1);

	if (chan==-1||length_code==-1||(!starts&&!note_length))
	{
		m_OK.EnableWindow(false);
	}
	else
	{
		m_OK.EnableWindow(true);
	}	
}

void CQuantizeDlg::OnCheckStartTime() 
{
	starts = (m_check_start_time.GetCheck()==1);

	if (chan==-1||length_code==-1||(!starts&&!note_length))
	{
		m_OK.EnableWindow(false);
	}
	else
	{
		m_OK.EnableWindow(true);
	}	
}

