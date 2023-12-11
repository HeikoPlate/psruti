// VoicefileRevoicingDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "VoicefileRevoicingDlg.h"
#include "InsdefDlg.h"
#include "InsDefOnOffDlg.h"
#include "VoiceFileBrowseDlg.h"
#include "GlobalUtilities.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld VoicefileRevoicingDlg 


VoicefileRevoicingDlg::VoicefileRevoicingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(VoicefileRevoicingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(VoicefileRevoicingDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	
	int chan;

	bankno_idlist[0] = IDC_BANKNO1;
	bankno_idlist[1] = IDC_BANKNO2;
	bankno_idlist[2] = IDC_BANKNO3;
	bankno_idlist[3] = IDC_BANKNO4;
	bankno_idlist[4] = IDC_BANKNO5;
	bankno_idlist[5] = IDC_BANKNO6;
	bankno_idlist[6] = IDC_BANKNO7;
	bankno_idlist[7] = IDC_BANKNO8;
	bankno_idlist[8] = IDC_BANKNO9;
	bankno_idlist[9] = IDC_BANKNO10;
	bankno_idlist[10] = IDC_BANKNO11;
	bankno_idlist[11] = IDC_BANKNO12;
	bankno_idlist[12] = IDC_BANKNO13;
	bankno_idlist[13] = IDC_BANKNO14;
	bankno_idlist[14] = IDC_BANKNO15;
	bankno_idlist[15] = IDC_BANKNO16;

	bankno_list[0] = &m_bankno1;
	bankno_list[1] = &m_bankno2;
	bankno_list[2] = &m_bankno3;
	bankno_list[3] = &m_bankno4;
	bankno_list[4] = &m_bankno5;
	bankno_list[5] = &m_bankno6;
	bankno_list[6] = &m_bankno7;
	bankno_list[7] = &m_bankno8;
	bankno_list[8] = &m_bankno9;
	bankno_list[9] = &m_bankno10;
	bankno_list[10] = &m_bankno11;
	bankno_list[11] = &m_bankno12;
	bankno_list[12] = &m_bankno13;
	bankno_list[13] = &m_bankno14;
	bankno_list[14] = &m_bankno15;
	bankno_list[15] = &m_bankno16;

	voiceno_idlist[0] = IDC_VOICENO1;
	voiceno_idlist[1] = IDC_VOICENO2;
	voiceno_idlist[2] = IDC_VOICENO3;
	voiceno_idlist[3] = IDC_VOICENO4;
	voiceno_idlist[4] = IDC_VOICENO5;
	voiceno_idlist[5] = IDC_VOICENO6;
	voiceno_idlist[6] = IDC_VOICENO7;
	voiceno_idlist[7] = IDC_VOICENO8;
	voiceno_idlist[8] = IDC_VOICENO9;
	voiceno_idlist[9] = IDC_VOICENO10;
	voiceno_idlist[10] = IDC_VOICENO11;
	voiceno_idlist[11] = IDC_VOICENO12;
	voiceno_idlist[12] = IDC_VOICENO13;
	voiceno_idlist[13] = IDC_VOICENO14;
	voiceno_idlist[14] = IDC_VOICENO15;
	voiceno_idlist[15] = IDC_VOICENO16;

	voiceno_list[0] = &m_voiceno1;
	voiceno_list[1] = &m_voiceno2;
	voiceno_list[2] = &m_voiceno3;
	voiceno_list[3] = &m_voiceno4;
	voiceno_list[4] = &m_voiceno5;
	voiceno_list[5] = &m_voiceno6;
	voiceno_list[6] = &m_voiceno7;
	voiceno_list[7] = &m_voiceno8;
	voiceno_list[8] = &m_voiceno9;
	voiceno_list[9] = &m_voiceno10;
	voiceno_list[10] = &m_voiceno11;
	voiceno_list[11] = &m_voiceno12;
	voiceno_list[12] = &m_voiceno13;
	voiceno_list[13] = &m_voiceno14;
	voiceno_list[14] = &m_voiceno15;
	voiceno_list[15] = &m_voiceno16;

	voicename_idlist[0] = IDC_VOICENAME1;
	voicename_idlist[1] = IDC_VOICENAME2;
	voicename_idlist[2] = IDC_VOICENAME3;
	voicename_idlist[3] = IDC_VOICENAME4;
	voicename_idlist[4] = IDC_VOICENAME5;
	voicename_idlist[5] = IDC_VOICENAME6;
	voicename_idlist[6] = IDC_VOICENAME7;
	voicename_idlist[7] = IDC_VOICENAME8;
	voicename_idlist[8] = IDC_VOICENAME9;
	voicename_idlist[9] = IDC_VOICENAME10;
	voicename_idlist[10] = IDC_VOICENAME11;
	voicename_idlist[11] = IDC_VOICENAME12;
	voicename_idlist[12] = IDC_VOICENAME13;
	voicename_idlist[13] = IDC_VOICENAME14;
	voicename_idlist[14] = IDC_VOICENAME15;
	voicename_idlist[15] = IDC_VOICENAME16;

	voicename_list[0] = &m_voicename1;
	voicename_list[1] = &m_voicename2;
	voicename_list[2] = &m_voicename3;
	voicename_list[3] = &m_voicename4;
	voicename_list[4] = &m_voicename5;
	voicename_list[5] = &m_voicename6;
	voicename_list[6] = &m_voicename7;
	voicename_list[7] = &m_voicename8;
	voicename_list[8] = &m_voicename9;
	voicename_list[9] = &m_voicename10;
	voicename_list[10] = &m_voicename11;
	voicename_list[11] = &m_voicename12;
	voicename_list[12] = &m_voicename13;
	voicename_list[13] = &m_voicename14;
	voicename_list[14] = &m_voicename15;
	voicename_list[15] = &m_voicename16;

	block_idlist[0] = IDC_BLOCK_CHAN1;
	block_idlist[1] = IDC_BLOCK_CHAN2;
	block_idlist[2] = IDC_BLOCK_CHAN3;
	block_idlist[3] = IDC_BLOCK_CHAN4;
	block_idlist[4] = IDC_BLOCK_CHAN5;
	block_idlist[5] = IDC_BLOCK_CHAN6;
	block_idlist[6] = IDC_BLOCK_CHAN7;
	block_idlist[7] = IDC_BLOCK_CHAN8;
	block_idlist[8] = IDC_BLOCK_CHAN9;
	block_idlist[9] = IDC_BLOCK_CHAN10;
	block_idlist[10] = IDC_BLOCK_CHAN11;
	block_idlist[11] = IDC_BLOCK_CHAN12;
	block_idlist[12] = IDC_BLOCK_CHAN13;
	block_idlist[13] = IDC_BLOCK_CHAN14;
	block_idlist[14] = IDC_BLOCK_CHAN15;
	block_idlist[15] = IDC_BLOCK_CHAN16;

	revoice_list[0] = &m_revoice1;
	revoice_list[1] = &m_revoice2;
	revoice_list[2] = &m_revoice3;
	revoice_list[3] = &m_revoice4;
	revoice_list[4] = &m_revoice5;
	revoice_list[5] = &m_revoice6;
	revoice_list[6] = &m_revoice7;
	revoice_list[7] = &m_revoice8;
	revoice_list[8] = &m_revoice9;
	revoice_list[9] = &m_revoice10;
	revoice_list[10] = &m_revoice11;
	revoice_list[11] = &m_revoice12;
	revoice_list[12] = &m_revoice13;
	revoice_list[13] = &m_revoice14;
	revoice_list[14] = &m_revoice15;
	revoice_list[15] = &m_revoice16;

	block_list[0] = &m_block_chan1;
	block_list[1] = &m_block_chan2;
	block_list[2] = &m_block_chan3;
	block_list[3] = &m_block_chan4;
	block_list[4] = &m_block_chan5;
	block_list[5] = &m_block_chan6;
	block_list[6] = &m_block_chan7;
	block_list[7] = &m_block_chan8;
	block_list[8] = &m_block_chan9;
	block_list[9] = &m_block_chan10;
	block_list[10] = &m_block_chan11;
	block_list[11] = &m_block_chan12;
	block_list[12] = &m_block_chan13;
	block_list[13] = &m_block_chan14;
	block_list[14] = &m_block_chan15;
	block_list[15] = &m_block_chan16;

	ctrl_list[0] = &m_ctrl1;
	ctrl_list[1] = &m_ctrl2;
	ctrl_list[2] = &m_ctrl3;
	ctrl_list[3] = &m_ctrl4;
	ctrl_list[4] = &m_ctrl5;
	ctrl_list[5] = &m_ctrl6;
	ctrl_list[6] = &m_ctrl7;
	ctrl_list[7] = &m_ctrl8;
	ctrl_list[8] = &m_ctrl9;
	ctrl_list[9] = &m_ctrl10;
	ctrl_list[10] = &m_ctrl11;
	ctrl_list[11] = &m_ctrl12;
	ctrl_list[12] = &m_ctrl13;
	ctrl_list[13] = &m_ctrl14;
	ctrl_list[14] = &m_ctrl15;
	ctrl_list[15] = &m_ctrl16;

	testchan_list[0] = &m_test_chan1;
	testchan_list[1] = &m_test_chan2;
	testchan_list[2] = &m_test_chan3;
	testchan_list[3] = &m_test_chan4;
	testchan_list[4] = &m_test_chan5;
	testchan_list[5] = &m_test_chan6;
	testchan_list[6] = &m_test_chan7;
	testchan_list[7] = &m_test_chan8;
	testchan_list[8] = &m_test_chan9;
	testchan_list[9] = &m_test_chan10;
	testchan_list[10] = &m_test_chan11;
	testchan_list[11] = &m_test_chan12;
	testchan_list[12] = &m_test_chan13;
	testchan_list[13] = &m_test_chan14;
	testchan_list[14] = &m_test_chan15;
	testchan_list[15] = &m_test_chan16;

	for (chan=0; chan<16; chan++)
	{
		voicefilepath_list[chan].voicename = "";
		voicefilepath_list[chan].filepath = "";
	}

	mf_voiceplay_melody = NULL;
	mf_voiceplay_drum = NULL;

	m_nTimer = NULL;
	time_first_playnote = 2*480; // notes start after 2 quarters
}


void VoicefileRevoicingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VoicefileRevoicingDlg)
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_TEST_CHAN1, m_test_chan1);
	DDX_Control(pDX, IDC_TEST_CHAN2, m_test_chan2);
	DDX_Control(pDX, IDC_TEST_CHAN3, m_test_chan3);
	DDX_Control(pDX, IDC_TEST_CHAN4, m_test_chan4);
	DDX_Control(pDX, IDC_TEST_CHAN5, m_test_chan5);
	DDX_Control(pDX, IDC_TEST_CHAN6, m_test_chan6);
	DDX_Control(pDX, IDC_TEST_CHAN7, m_test_chan7);
	DDX_Control(pDX, IDC_TEST_CHAN8, m_test_chan8);
	DDX_Control(pDX, IDC_TEST_CHAN9, m_test_chan9);
	DDX_Control(pDX, IDC_TEST_CHAN10, m_test_chan10);
	DDX_Control(pDX, IDC_TEST_CHAN11, m_test_chan11);
	DDX_Control(pDX, IDC_TEST_CHAN12, m_test_chan12);
	DDX_Control(pDX, IDC_TEST_CHAN13, m_test_chan13);
	DDX_Control(pDX, IDC_TEST_CHAN14, m_test_chan14);
	DDX_Control(pDX, IDC_TEST_CHAN15, m_test_chan15);
	DDX_Control(pDX, IDC_TEST_CHAN16, m_test_chan16);
	DDX_Control(pDX, IDC_VOICENAME1, m_voicename1);
	DDX_Control(pDX, IDC_VOICENAME2, m_voicename2);
	DDX_Control(pDX, IDC_VOICENAME3, m_voicename3);
	DDX_Control(pDX, IDC_VOICENAME4, m_voicename4);
	DDX_Control(pDX, IDC_VOICENAME5, m_voicename5);
	DDX_Control(pDX, IDC_VOICENAME6, m_voicename6);
	DDX_Control(pDX, IDC_VOICENAME7, m_voicename7);
	DDX_Control(pDX, IDC_VOICENAME8, m_voicename8);
	DDX_Control(pDX, IDC_VOICENAME9, m_voicename9);
	DDX_Control(pDX, IDC_VOICENAME10, m_voicename10);
	DDX_Control(pDX, IDC_VOICENAME11, m_voicename11);
	DDX_Control(pDX, IDC_VOICENAME12, m_voicename12);
	DDX_Control(pDX, IDC_VOICENAME13, m_voicename13);
	DDX_Control(pDX, IDC_VOICENAME14, m_voicename14);
	DDX_Control(pDX, IDC_VOICENAME15, m_voicename15);
	DDX_Control(pDX, IDC_VOICENAME16, m_voicename16);
	DDX_Control(pDX, IDC_BLOCK_CHAN1, m_block_chan1);
	DDX_Control(pDX, IDC_BLOCK_CHAN2, m_block_chan2);
	DDX_Control(pDX, IDC_BLOCK_CHAN3, m_block_chan3);
	DDX_Control(pDX, IDC_BLOCK_CHAN4, m_block_chan4);
	DDX_Control(pDX, IDC_BLOCK_CHAN5, m_block_chan5);
	DDX_Control(pDX, IDC_BLOCK_CHAN6, m_block_chan6);
	DDX_Control(pDX, IDC_BLOCK_CHAN7, m_block_chan7);
	DDX_Control(pDX, IDC_BLOCK_CHAN8, m_block_chan8);
	DDX_Control(pDX, IDC_BLOCK_CHAN9, m_block_chan9);
	DDX_Control(pDX, IDC_BLOCK_CHAN10, m_block_chan10);
	DDX_Control(pDX, IDC_BLOCK_CHAN11, m_block_chan11);
	DDX_Control(pDX, IDC_BLOCK_CHAN12, m_block_chan12);
	DDX_Control(pDX, IDC_BLOCK_CHAN13, m_block_chan13);
	DDX_Control(pDX, IDC_BLOCK_CHAN14, m_block_chan14);
	DDX_Control(pDX, IDC_BLOCK_CHAN15, m_block_chan15);
	DDX_Control(pDX, IDC_BLOCK_CHAN16, m_block_chan16);
	DDX_Control(pDX, IDC_CTRL1, m_ctrl1);
	DDX_Control(pDX, IDC_CTRL2, m_ctrl2);
	DDX_Control(pDX, IDC_CTRL3, m_ctrl3);
	DDX_Control(pDX, IDC_CTRL4, m_ctrl4);
	DDX_Control(pDX, IDC_CTRL5, m_ctrl5);
	DDX_Control(pDX, IDC_CTRL6, m_ctrl6);
	DDX_Control(pDX, IDC_CTRL7, m_ctrl7);
	DDX_Control(pDX, IDC_CTRL8, m_ctrl8);
	DDX_Control(pDX, IDC_CTRL9, m_ctrl9);
	DDX_Control(pDX, IDC_CTRL10, m_ctrl10);
	DDX_Control(pDX, IDC_CTRL11, m_ctrl11);
	DDX_Control(pDX, IDC_CTRL12, m_ctrl12);
	DDX_Control(pDX, IDC_CTRL13, m_ctrl13);
	DDX_Control(pDX, IDC_CTRL14, m_ctrl14);
	DDX_Control(pDX, IDC_CTRL15, m_ctrl15);
	DDX_Control(pDX, IDC_CTRL16, m_ctrl16);
	DDX_Control(pDX, IDC_REVOICE1, m_revoice1);
	DDX_Control(pDX, IDC_REVOICE2, m_revoice2);
	DDX_Control(pDX, IDC_REVOICE3, m_revoice3);
	DDX_Control(pDX, IDC_REVOICE4, m_revoice4);
	DDX_Control(pDX, IDC_REVOICE5, m_revoice5);
	DDX_Control(pDX, IDC_REVOICE6, m_revoice6);
	DDX_Control(pDX, IDC_REVOICE7, m_revoice7);
	DDX_Control(pDX, IDC_REVOICE8, m_revoice8);
	DDX_Control(pDX, IDC_REVOICE9, m_revoice9);
	DDX_Control(pDX, IDC_REVOICE10, m_revoice10);
	DDX_Control(pDX, IDC_REVOICE11, m_revoice11);
	DDX_Control(pDX, IDC_REVOICE12, m_revoice12);
	DDX_Control(pDX, IDC_REVOICE13, m_revoice13);
	DDX_Control(pDX, IDC_REVOICE14, m_revoice14);
	DDX_Control(pDX, IDC_REVOICE15, m_revoice15);
	DDX_Control(pDX, IDC_REVOICE16, m_revoice16);
	DDX_Control(pDX,    IDC_BANKNO1,   m_bankno1);
	DDX_Control(pDX,   IDC_VOICENO1,   m_voiceno1);
	DDX_Control(pDX,    IDC_BANKNO2,   m_bankno2);
	DDX_Control(pDX,   IDC_VOICENO2,   m_voiceno2);
	DDX_Control(pDX,    IDC_BANKNO3,   m_bankno3);
	DDX_Control(pDX,   IDC_VOICENO3,   m_voiceno3);
	DDX_Control(pDX,    IDC_BANKNO4,   m_bankno4);
	DDX_Control(pDX,   IDC_VOICENO4,   m_voiceno4);
	DDX_Control(pDX,    IDC_BANKNO5,   m_bankno5);
	DDX_Control(pDX,   IDC_VOICENO5,   m_voiceno5);
	DDX_Control(pDX,    IDC_BANKNO6,   m_bankno6);
	DDX_Control(pDX,   IDC_VOICENO6,   m_voiceno6);
	DDX_Control(pDX,    IDC_BANKNO7,   m_bankno7);
	DDX_Control(pDX,   IDC_VOICENO7,   m_voiceno7);
	DDX_Control(pDX,    IDC_BANKNO8,   m_bankno8);
	DDX_Control(pDX,   IDC_VOICENO8,   m_voiceno8);
	DDX_Control(pDX,    IDC_BANKNO9,   m_bankno9);
	DDX_Control(pDX,   IDC_VOICENO9,   m_voiceno9);
	DDX_Control(pDX,    IDC_BANKNO10,  m_bankno10);
	DDX_Control(pDX,   IDC_VOICENO10,  m_voiceno10);
	DDX_Control(pDX,    IDC_BANKNO11,  m_bankno11);
	DDX_Control(pDX,   IDC_VOICENO11,  m_voiceno11);
	DDX_Control(pDX,    IDC_BANKNO12,  m_bankno12);
	DDX_Control(pDX,   IDC_VOICENO12,  m_voiceno12);
	DDX_Control(pDX,    IDC_BANKNO13,  m_bankno13);
	DDX_Control(pDX,   IDC_VOICENO13,  m_voiceno13);
	DDX_Control(pDX,    IDC_BANKNO14,  m_bankno14);
	DDX_Control(pDX,   IDC_VOICENO14,  m_voiceno14);
	DDX_Control(pDX,    IDC_BANKNO15,  m_bankno15);
	DDX_Control(pDX,   IDC_VOICENO15,  m_voiceno15);
	DDX_Control(pDX,    IDC_BANKNO16,  m_bankno16);
	DDX_Control(pDX,   IDC_VOICENO16,  m_voiceno16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VoicefileRevoicingDlg, CDialog)
	//{{AFX_MSG_MAP(VoicefileRevoicingDlg)
	ON_BN_CLICKED(IDC_REVOICE1, OnRevoice1)
	ON_BN_CLICKED(IDC_REVOICE2, OnRevoice2)
	ON_BN_CLICKED(IDC_REVOICE3, OnRevoice3)
	ON_BN_CLICKED(IDC_REVOICE4, OnRevoice4)
	ON_BN_CLICKED(IDC_REVOICE5, OnRevoice5)
	ON_BN_CLICKED(IDC_REVOICE6, OnRevoice6)
	ON_BN_CLICKED(IDC_REVOICE7, OnRevoice7)
	ON_BN_CLICKED(IDC_REVOICE8, OnRevoice8)
	ON_BN_CLICKED(IDC_REVOICE9, OnRevoice9)
	ON_BN_CLICKED(IDC_REVOICE10, OnRevoice10)
	ON_BN_CLICKED(IDC_REVOICE11, OnRevoice11)
	ON_BN_CLICKED(IDC_REVOICE12, OnRevoice12)
	ON_BN_CLICKED(IDC_REVOICE13, OnRevoice13)
	ON_BN_CLICKED(IDC_REVOICE14, OnRevoice14)
	ON_BN_CLICKED(IDC_REVOICE15, OnRevoice15)
	ON_BN_CLICKED(IDC_REVOICE16, OnRevoice16)
	ON_BN_CLICKED(IDC_TEST_CHAN1, OnTestChan1)
	ON_BN_CLICKED(IDC_TEST_CHAN2, OnTestChan2)
	ON_BN_CLICKED(IDC_TEST_CHAN3, OnTestChan3)
	ON_BN_CLICKED(IDC_TEST_CHAN4, OnTestChan4)
	ON_BN_CLICKED(IDC_TEST_CHAN5, OnTestChan5)
	ON_BN_CLICKED(IDC_TEST_CHAN6, OnTestChan6)
	ON_BN_CLICKED(IDC_TEST_CHAN7, OnTestChan7)
	ON_BN_CLICKED(IDC_TEST_CHAN8, OnTestChan8)
	ON_BN_CLICKED(IDC_TEST_CHAN9, OnTestChan9)
	ON_BN_CLICKED(IDC_TEST_CHAN10, OnTestChan10)
	ON_BN_CLICKED(IDC_TEST_CHAN11, OnTestChan11)
	ON_BN_CLICKED(IDC_TEST_CHAN12, OnTestChan12)
	ON_BN_CLICKED(IDC_TEST_CHAN13, OnTestChan13)
	ON_BN_CLICKED(IDC_TEST_CHAN14, OnTestChan14)
	ON_BN_CLICKED(IDC_TEST_CHAN15, OnTestChan15)
	ON_BN_CLICKED(IDC_TEST_CHAN16, OnTestChan16)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten VoicefileRevoicingDlg 

void VoicefileRevoicingDlg::OnRevoice1() 
{
	revoice(0);
}

void VoicefileRevoicingDlg::OnRevoice2() 
{
	revoice(1);
}

void VoicefileRevoicingDlg::OnRevoice3() 
{
	revoice(2);
}

void VoicefileRevoicingDlg::OnRevoice4() 
{
	revoice(3);
}

void VoicefileRevoicingDlg::OnRevoice5() 
{
	revoice(4);
}

void VoicefileRevoicingDlg::OnRevoice6() 
{
	revoice(5);
}

void VoicefileRevoicingDlg::OnRevoice7() 
{
	revoice(6);
}

void VoicefileRevoicingDlg::OnRevoice8() 
{
	revoice(7);
}

void VoicefileRevoicingDlg::OnRevoice9() 
{
	revoice(8);
}

void VoicefileRevoicingDlg::OnRevoice10() 
{
	revoice(9);
}

void VoicefileRevoicingDlg::OnRevoice11() 
{
	revoice(10);
}

void VoicefileRevoicingDlg::OnRevoice12() 
{
	revoice(11);
}

void VoicefileRevoicingDlg::OnRevoice13() 
{
	revoice(12);
}

void VoicefileRevoicingDlg::OnRevoice14() 
{
	revoice(13);
}

void VoicefileRevoicingDlg::OnRevoice15() 
{
	revoice(14);
}

void VoicefileRevoicingDlg::OnRevoice16() 
{
	revoice(15);
}

void VoicefileRevoicingDlg::revoice(int chan)
{
	int i;
	VoiceFileBrowseDlg dlg;
	dlg.hpmfi = hpmfi;
	dlg.chan = chan;
	dlg.p_inifile = p_inifile;
	for (i=0; i<16; i++)
	{
		dlg.blocklist[i] = internal_blocklist[i];
	}

	int result = dlg.DoModal();
	if (result != 0) return;
	if (dlg.block>=0)
	{
		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_BLOCK_USED),dlg.block+1);

		external_blocklist[chan] = -1;

		int i;
		for (i=0; i<16; i++)
		{
			if (external_blocklist[i]==dlg.block)
			{
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
				return;
			}
		}
		
		for (i=0; i<16; i++)
		{
			if ((internal_blocklist[i]==dlg.block)&&(i!=chan))
			{
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
				return;
			}
		}
	}
	else
	{
		external_blocklist[chan] = -1;
	}

	SetDlgItemText(bankno_idlist[chan],"");
	SetDlgItemText(voiceno_idlist[chan],"");
	SetDlgItemText(voicename_idlist[chan],dlg.voicename);
	SetDlgItemText(block_idlist[chan],"");
	voicefilepath_list[chan].voicename = dlg.voicename;
	voicefilepath_list[chan].filepath = dlg.voicefile_path;
	voicefilepath_list[chan].block = dlg.block;
	internal_blocklist[chan] = dlg.block; // remember block used
	if (dlg.block >= 0)
	{
		SetDlgItemInt(block_idlist[chan],dlg.block+1,FALSE);
	}
	ctrl_list[chan]->EnableWindow(TRUE);

// neu
	(testchan_list[chan])->EnableWindow(TRUE);
	(block_list[chan])->EnableWindow(TRUE);
}


BOOL VoicefileRevoicingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int chan;
	for (chan=0; chan<16; chan++)
	{
		ctrl_list[chan]->SetCheck(0);
		ctrl_list[chan]->EnableWindow(FALSE);
		(testchan_list[chan])->EnableWindow(FALSE);
		(revoice_list[chan])->EnableWindow(TRUE);
		(block_list[chan])->EnableWindow(FALSE);
	}

	act_testchan = -1;

	CString text = "Voicefile Revoicing:  ";
	text += hpmfi->proposed_songname;
	SetWindowText(text);
	SetCursor(hCursorWait);	
	get_init_data();

	SetDlgItemText(IDC_CHANNELTXT,GlobalUtilities::get_resource_string(IDS_CHANNEL));
	SetDlgItemText(IDC_BANKNUMBER,"Bank");
	SetDlgItemText(IDC_VOICENOTXT,"Voice");
	SetDlgItemText(IDC_VOICENAMETXT,GlobalUtilities::get_resource_string(IDS_VOICENAME));
	SetDlgItemText(IDC_REVOICETXT,GlobalUtilities::get_resource_string(IDS_REVOICING_SHORT));
	SetDlgItemText(IDC_EFF_BLOCK_TEXT,"Eff. Block");
	SetDlgItemText(IDC_PLUS_CTRL,"+Ctrl");
	SetDlgItemText(IDC_TEST_TXT,"Test");

	SetDlgItemText(IDC_1TXT,"1");
	SetDlgItemText(IDC_2TXT,"2");
	SetDlgItemText(IDC_3TXT,"3");
	SetDlgItemText(IDC_4TXT,"4");
	SetDlgItemText(IDC_5TXT,"5");
	SetDlgItemText(IDC_6TXT,"6");
	SetDlgItemText(IDC_7TXT,"7");
	SetDlgItemText(IDC_8TXT,"8");
	SetDlgItemText(IDC_9TXT,"9");
	SetDlgItemText(IDC_10TXT,"10");
	SetDlgItemText(IDC_11TXT,"11");
	SetDlgItemText(IDC_12TXT,"12");
	SetDlgItemText(IDC_13TXT,"13");
	SetDlgItemText(IDC_14TXT,"14");
	SetDlgItemText(IDC_15TXT,"15");
	SetDlgItemText(IDC_16TXT,"16");


	
	int blocklist[16]; // index part; value block
	int block_chanlist[16]; // index block, value chan, can be used to examine different
	// blocks at only one chan. PSRUTI ignores the list at this time
	hpmfi->update_blocklist(hpmfi->mf,blocklist);
	hpmfi->update_chan_blocklist(blocklist, external_blocklist, block_chanlist);
	for (chan=0; chan<16; chan++)
	{
		if (external_blocklist[chan] != -1)
		{
			SetDlgItemInt(block_idlist[chan],external_blocklist[chan]+1,FALSE);
		}
		internal_blocklist[chan] = external_blocklist[chan];
	}
	
	SetCursor(hCursorOld);
	
	// initialize test sequence
	//	mf_voiceplay_melody = hpmfi->create_testsequence_melody();
	//	mf_voiceplay_drum = hpmfi->create_testsequence_drum();

	mf_voiceplay_melody = HP_Init();	// starts a MIDI-file session
	if (mf_voiceplay_melody != NULL)   // do nothing if not possible
	{
		const int PPQN = 480;
		int i;
		
		// note-length
		const int whole = PPQN*4;	// ticks of a whole note
		const int quaver = PPQN/2;	// ticks of 1/8 note
		
		HP_ChangePPQN(mf_voiceplay_melody,HP_PPQN480);	// set PPQN
		
		HP_SetFirst(mf_voiceplay_melody,HP_FIRST);	// add events of same time at the end
		HP_InsertTimeSignature(mf_voiceplay_melody,0x00,4,4);
		time_first_play_effect_event = 100;
		HP_InsertSysEx(mf_voiceplay_melody,time_first_play_effect_event,GlobalUtilities::gm_on_data);
		time_first_play_effect_event += 100;
		HP_InsertSysEx(mf_voiceplay_melody,time_first_play_effect_event,GlobalUtilities::xg_on_data);
		time_first_play_effect_event += 100;
		HP_InsertTempo(mf_voiceplay_melody,time_first_play_effect_event,120);	// BPM = 360
		time_first_play_effect_event += 10;
		
		// add standard variations
		
		/* Insert following sysex
		F0 43 10 4C 02 01 00 01 11 F7  ; (XG) Reverb Type HALL 3
		F0 43 10 4C 02 01 20 42 10 F7  ; (XG) Chorus Type CHORUS 3
		*/
		
		unsigned char reverb_hall3[] = {0xf0,0x43,0x10,0x4c,0x02,0x01,0x00,0x01,0x11,0xf7};
		unsigned char chorus3[]      = {0xf0,0x43,0x10,0x4c,0x02,0x01,0x20,0x42,0x10,0xf7};
		
		HP_SetFirst(mf_voiceplay_melody, HP_LAST);
		HP_InsertSysEx(mf_voiceplay_melody,time_first_play_effect_event,reverb_hall3);
		time_first_play_effect_event += 5;
		HP_InsertSysEx(mf_voiceplay_melody,time_first_play_effect_event,chorus3);
		time_first_play_effect_event += 5;
		
		// prepare notes
		
		struct	{	int time;
					int length;
					int note;
					int chan;
					int vel;	
				} note[] =
		{
			{time_first_playnote,			quaver, 0x30,0,100},	// c
			{time_first_playnote+quaver,	quaver, 0x34,0,70},		// e		
			{time_first_playnote+quaver*2,	quaver, 0x37,0,70},		// g
			{time_first_playnote+quaver*3,	quaver, 0x3c,0,100},	// c
			{time_first_playnote+quaver*4,	quaver, 0x40,0,70},		// e		
			{time_first_playnote+quaver*5,	quaver, 0x43,0,70},		// g
			{time_first_playnote+quaver*6,	quaver, 0x48,0,100},	// c
			{time_first_playnote+quaver*7,	quaver, 0x4c,0,70},		// e
			{time_first_playnote+quaver*8,	quaver, 0x4f,0,70},		// g
			{time_first_playnote+quaver*9,	whole  , 0x54,0,127},	// c
			{time_first_playnote+quaver*9,	whole  , 0x43,0,127},	// g
			{time_first_playnote+quaver*9,	whole  , 0x40,0,127},	// e
			{time_first_playnote+quaver*9,	whole  , 0x30,0,127},	// c
			{-1,		quaver, 0x00,0,0  }
		};
		
		// insert notes (chan 0)
		
		for (i=0; true; i++)
		{
			if (note[i].time == -1) break;
			HP_InsertNote(mf_voiceplay_melody,note[i].time,note[i].length,note[i].note,note[i].chan,note[i].vel);
		}
	}

	mf_voiceplay_drum = HP_Init();
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void VoicefileRevoicingDlg::get_init_data()
{
	int chan;
	bool result = false;
	bool found = false;

	CString insdeffile = p_inifile->get_insdeffile();
	CString insdef = p_inifile->get_insdef();

	// open file and insdef

	if (!hpmfi->with_insdef)
	{
		SetDlgItemText(IDC_INSDEFFILENAME,"");
	}
	
	if (hpmfi->with_insdef)
	{
		// display insdeffile and insdef
		CString short_filename = insdeffile;
		if (insdeffile.GetLength()>57)
		{
			short_filename = "..."+insdeffile.Right(54);
		}
		SetDlgItemText(IDC_INSDEFFILENAME,short_filename+" ("+insdef+")");
	}

	// set banks and voices
	hpmfi->get_initialvoices(voicelist);

	if ((hpmfi->with_insdef) && (hpmfi->bank_list == NULL))
	{
		HP_CWInsGetBanks(hpmfi->mf,&hpmfi->bank_list,&hpmfi->no_banks);
	}

	for (chan=0; chan<16; chan++)
	{
		if (!voicelist[chan].with_note)
		{
			SetDlgItemText(bankno_idlist[chan],"");
			bankno_list[chan]->EnableWindow(false);
			block_list[chan]->EnableWindow(false);
			ctrl_list[chan]->EnableWindow(false);
			voicename_list[chan]->EnableWindow(false);
			testchan_list[chan]->EnableWindow(false);
		}
		else
		{
			SetDlgItemInt(bankno_idlist[chan],128*voicelist[chan].msb+voicelist[chan].lsb,FALSE);
			ctrl_list[chan]->EnableWindow(false);
		}

		if (!voicelist[chan].with_note)
		{
			SetDlgItemText(voiceno_idlist[chan],"");
			voiceno_list[chan]->EnableWindow(false);
		}
		else
		{
			SetDlgItemInt(voiceno_idlist[chan],voicelist[chan].voice,FALSE);
		}

		(revoice_list[chan])->EnableWindow(hpmfi->mute[chan]?FALSE:TRUE);
	}
	set_voicenames();
	hpmfi->find_insfile_bank_voicenames();
}

void VoicefileRevoicingDlg::set_voicenames()
{
	int chan;
	char *bank_name;
	char *voice_name;
	char *note_name;
	CString short_voicename;

	for (chan=0; chan<16;chan++)
	{
	
		if ((!hpmfi->with_insdef)||(hpmfi->mute[chan]))
		{
			SetDlgItemText(voicename_idlist[chan],"");
			continue;
		}


		HP_CWInsGetBankVoiceNoteName(hpmfi->mf,
			128*voicelist[chan].msb+voicelist[chan].lsb,
			voicelist[chan].voice,
			0,
			&bank_name,&voice_name,&note_name);

		short_voicename = voice_name;
		GlobalUtilities::reduce_voicename(&short_voicename);

		SetDlgItemText(voicename_idlist[chan],short_voicename);
		HP_Delete(bank_name);
		HP_Delete(voice_name);
		HP_Delete(note_name);
	}
}

void VoicefileRevoicingDlg::OnCancel() 
{
	if (mf_voiceplay_melody != NULL)
	{
		HP_Free(mf_voiceplay_melody);
		mf_voiceplay_melody = NULL;
	}
	if (mf_voiceplay_drum != NULL)
	{
		HP_Free(mf_voiceplay_drum);
		mf_voiceplay_drum = NULL;
	}

	EndDialog(-1);
}

void VoicefileRevoicingDlg::OnOK() 
{
	int chan;
	for (chan=0; chan<16; chan++)
	{
		(voicefilepath_list[chan]).with_controller = (ctrl_list[chan]->GetCheck() == 1);
	}

	if (mf_voiceplay_melody != NULL)
	{
		HP_Free(mf_voiceplay_melody);
		mf_voiceplay_melody = NULL;
	}
	if (mf_voiceplay_drum != NULL)
	{
		HP_Free(mf_voiceplay_drum);
		mf_voiceplay_drum = NULL;
	}

	EndDialog(0);
}

void VoicefileRevoicingDlg::OnTestChan1() 
{
	voicetest(0);
}

void VoicefileRevoicingDlg::OnTestChan2() 
{
	voicetest(1);
}

void VoicefileRevoicingDlg::OnTestChan3() 
{
	voicetest(2);
}

void VoicefileRevoicingDlg::OnTestChan4() 
{
	voicetest(3);
}

void VoicefileRevoicingDlg::OnTestChan5() 
{
	voicetest(4);
}

void VoicefileRevoicingDlg::OnTestChan6() 
{
	voicetest(5);
}


void VoicefileRevoicingDlg::OnTestChan7() 
{
	voicetest(6);
}


void VoicefileRevoicingDlg::OnTestChan8() 
{
	voicetest(7);
}


void VoicefileRevoicingDlg::OnTestChan9() 
{
	voicetest(8);
}

void VoicefileRevoicingDlg::OnTestChan10() 
{
	voicetest(9);
}


void VoicefileRevoicingDlg::OnTestChan11() 
{
	voicetest(10);
}


void VoicefileRevoicingDlg::OnTestChan12() 
{
	voicetest(11);
}


void VoicefileRevoicingDlg::OnTestChan13() 
{
	voicetest(12);
}

void VoicefileRevoicingDlg::OnTestChan14() 
{
	voicetest(13);
}


void VoicefileRevoicingDlg::OnTestChan15() 
{
	voicetest(14);
}


void VoicefileRevoicingDlg::OnTestChan16() 
{
	voicetest(15);
}


void VoicefileRevoicingDlg::voicetest(int voice_chan)
{

	int id, chan, time, type;
	int partmode = 0; // Mode normal
	int channel;
	CString voicefilepath;
	unsigned char mp_notused_data[]  = {0xf0,0x43,0x10,0x4c,0x08,0x00,0x00,0x08,0xf7};
	unsigned char mp_partmode_data[] = {0xf0,0x43,0x10,0x4c,0x08,0x00,0x07,0x00,0xf7};

	if (mf_voiceplay_melody == NULL) return; // do nothing if not possible
	voicefilepath = voicefilepath_list[voice_chan].filepath;

	m_ok.EnableWindow(FALSE);
	m_cancel.EnableWindow(FALSE);

	// delete all events between time_first_play_effect_event and time_first_playnote 
	HP_Rewind(mf_voiceplay_melody);
	while (HP_ReadEvent(mf_voiceplay_melody,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (time < time_first_play_effect_event) continue;
		if (time >= time_first_playnote) break;
		HP_DeleteEvent(mf_voiceplay_melody,id);
	}

	/* */
	/* set effect events between time_first_play_effect_event and time_first_playnote */ 
    /* */

	act_effect_event_time = time_first_play_effect_event;

	HP_MIDIFILE_MODULE* mf_voice;
	unsigned char* data_voice;
  	int id_voice, chan_voice, time_voice, type_voice;
	int	length_voice;
	int number_voice, value_voice;

	bool is_drum = false;

	if (voicefilepath=="")
	{
		for (channel=0; channel<16; channel++)
		{
			(testchan_list[channel])->EnableWindow(FALSE);
			(ctrl_list[channel])->EnableWindow(FALSE);
			(revoice_list[channel])->EnableWindow(TRUE);
		}
		m_ok.EnableWindow(TRUE);
		m_cancel.EnableWindow(TRUE);
		return; // no voicefile selected
	}
	else
	{
		(testchan_list[voice_chan])->EnableWindow(FALSE);
	}

	mf_voice = HP_Init();
	HP_Load(mf_voice,voicefilepath);
	HP_SetFirst(mf_voiceplay_melody,HP_LAST);

	// insert events only for chan 0, because notes lie on chan 0

	// search and insert controller + program change
	HP_Rewind(mf_voice);
	while (HP_ReadEvent(mf_voice,&id_voice,&chan_voice,&time_voice,&type_voice)==HP_ERR_NONE)
	{
		if ((type_voice&HP_TYPE_MASK)==HP_CONTROLLER_TYPE)
		{
			HP_ReadController(mf_voice,id_voice,&time_voice,&chan_voice,&number_voice,&value_voice);
			if ((number_voice==0)&&(value_voice==127))
			{
				partmode = 0x02; // mode Drums
				is_drum = true;
			}
			if (type_voice != HP_RELEASE_TIME)
			{   // too high release in voicefile
				HP_InsertController(mf_voiceplay_melody,act_effect_event_time,0,type_voice,value_voice,number_voice);
				act_effect_event_time++;
			}
		}
		if (type_voice==HP_PROGRAM_CHANGE)
		{
			HP_ReadProgramChange(mf_voice,id_voice,&time_voice,&chan_voice,&number_voice);
			HP_InsertProgramChange(mf_voiceplay_melody,act_effect_event_time,0,number_voice);
			act_effect_event_time++;
		}
	}

	// insert insertions

	if (voicefilepath_list[voice_chan].block >= 0)
	{
		add_insertions_play(mf_voice,voice_chan);
	}
		
	// search amd insert OrganFlute
	HP_Rewind(mf_voice);
	while (HP_ReadEvent(mf_voice,&id_voice,&chan_voice,&time_voice,&type_voice)==HP_ERR_NONE)
	{
		if (type_voice==HP_SYSEX)
		{
			HP_ReadSysex(mf_voice, id_voice, &time_voice, &data_voice, &length_voice);
			if ((data_voice[1]==0x43)&&
				(data_voice[2]==0x73)&&
				(data_voice[3]==0x01)&&
				(data_voice[4]==0x06)&&
				(data_voice[5]==0x0b))
			{
				CString r;
				int check=0;
				int i;

				data_voice[10]=0;
				// a bad Organ Flute Bulk Dump in voicefiles:
				unsigned char correct_data[34];
				for (i=0; i<28; i++)
				{
					correct_data[i] = data_voice[i];
				}
				correct_data[28] = 0;
				correct_data[29] = 0;
				correct_data[30] = 0;
				correct_data[31] = 0;
				correct_data[32] = 0; // -> check
				correct_data[33] = 0xf7;

				// checksum
				for (i=10; i<=31; i++)
				{
					check += (int)correct_data[i];
					check &= 0x7f;
				}
				check = (128-check)&0x7f;
				correct_data[32]= check;
				HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,correct_data);
				act_effect_event_time += 5;
			}
		}
	}

	// search and insert MultiPart and OffSet Level SysEx
	add_multipart_play(mf_voice,voice_chan);

	if (is_drum)
	{
		add_standard_drum_sysex_play(mf_voice);
	}

	HP_Free(mf_voice);


	if (!HP_IsPlaying(mf_voiceplay_melody))
	{
		SetCursor(hCursorWait);

		HP_Play(mf_voiceplay_melody,HP_ALL);

		// activate timer
		m_nTimer = SetTimer(1, 500, 0);
		SetCursor(hCursorOld);
		act_testchan = voice_chan;
	}
	else
	{
		m_ok.EnableWindow(FALSE);
		m_cancel.EnableWindow(FALSE);
	}

//	HP_Save(mf_voiceplay_melody,"c:/temp/melody_voice_test.mid",HP_SMF0);
}

void VoicefileRevoicingDlg::add_insertions_play(HP_MIDIFILE_MODULE* mf_voice, int voice_chan)
{
	int id, chan, type, time;
	int i;

	int block = voicefilepath_list[voice_chan].block;
	{
		// for instance:
		// F0 43 10 4C 03 bb 00 01 11 F7; (XG) Insertion Type, Eff. Block bb, HALL 3 
		// F0 43 10 4C 03 bb 0B 1E F7 	; (XG) Insertion Eff. Block bb, Dry/Wet D34>W
		// F0 43 10 4C 03 bb 0C pp F7 	; (XG) Insertion Part, Eff. Block bb, Part pp 
		
		unsigned char insertion_top[] = {0xf0, 0x43, 0x10, 0x4c, 0x03};
		int length;
		unsigned char* data;
		
		unsigned char* insertion_data_list[128];
		int no_insertion = 0;
		unsigned char* dry_wet_data = NULL;
		unsigned char assign_block[] = {0xf0, 0x43, 0x10, 0x4c, 0x03, 0x7f, 0x0c, 0x7f, 0xf7};
		
		HP_Rewind(mf_voice);
		while (HP_ReadEvent(mf_voice,&id,&chan,&time,&type)==HP_ERR_NONE)
		{
			if (type != HP_SYSEX) continue;
			HP_ReadSysex(mf_voice,id,&time,&data,&length);
			if (!GlobalUtilities::compare_data(insertion_top,5,data,5))
			{
				HP_Delete(data);
				continue;
			}
			
			data[5] = block;
			
			if (data[6] == 0x0b)
			{
				if (dry_wet_data != NULL)
				{
					HP_Delete(dry_wet_data);
				}
				dry_wet_data = data;
			}
			else
			{
				insertion_data_list[no_insertion] = data;
				no_insertion++;
			}
		}
		
		// insert insertions
		HP_SetFirst(mf_voiceplay_melody, HP_LAST);
		for (i=0; i<no_insertion; i++)
		{
			HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,insertion_data_list[i]);
			act_effect_event_time +=5;
			HP_Delete(insertion_data_list[i]);
		}
		
		if (no_insertion > 0)
		{
			if (dry_wet_data != NULL)
			{
				HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,dry_wet_data);
				act_effect_event_time += 5;
				HP_Delete(dry_wet_data);
			}
			
			assign_block[5] = block;
			assign_block[7] = 0;
			HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,assign_block);
			act_effect_event_time += 5;
		}
		else
		{
			if (dry_wet_data != NULL)
			{
				HP_Delete(dry_wet_data);
			}
		}
	}
}

void VoicefileRevoicingDlg::add_multipart_play(HP_MIDIFILE_MODULE* mf_voice, int voice_chan)
{
/*
#define VELOCITY_SENSE_DEPTH		0x80c
#define VELOCITY_SENSE_OFFSET		0x80d
#define MW_FILTER_CONTROL			0x81e
#define MW_LFO_PMOD					0x820			
#define MW_LFO_FMOD					0x821			
#define MW_LFO_AMOD					0x822			
#define OFFSET_LEVEL_CONTROL_MW		0xa40
#define OFFSET_LEVEL_CONTROL_CAT	0xa42			
#define CAT_FILTER_CONTROL			0x84e			
#define CAT_LFO_PMOD				0x850
#define CAT_LFO_FMOD				0x851
#define CAT_LFO_AMOD				0x852
#define EQ_BASS_GAIN				0x872	
#define EQ_TREBLE_GAIN				0x873
#define EQ_BASS_FREQU				0x876
#define EQ_TREBLE_FREQU				0x877	
*/

	struct{int type; unsigned char* data; bool is_default;} mp_list[512];
	int no_mp = 0;
	unsigned char sysex_top[] = {0xf0, 0x43, 0x10, 0x4c};
	unsigned char rcvchannel_data[]  = {0xf0,0x43,0x10,0x4c,0x08,0x00,0x04,0x00,0xf7};

	int id, chan, time, type, length;
	unsigned char* data;

	HP_Rewind(mf_voice);
	while (HP_ReadEvent(mf_voice,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf_voice,id,&time,&data,&length);
		if (!GlobalUtilities::compare_data(sysex_top,4,data,4))
		{
			HP_Delete(data);
			continue;
		}
		if ((data[4]!=0x08)&&(data[4]!=0x0a))
		{
			HP_Delete(data);
			continue;
		}


		if (data[4]==0x08)
		{
			switch (data[6])
			{
			case 0x0c:
				mp_list[no_mp].type = VELOCITY_SENSE_DEPTH;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x40;
				no_mp++;
				continue;
			case 0x0d:
				mp_list[no_mp].type = VELOCITY_SENSE_OFFSET;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x40;
				no_mp++;
				continue;
			case 0x1e:
				mp_list[no_mp].type = MW_FILTER_CONTROL;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x40;
				no_mp++;
				continue;
			case 0x20:
				mp_list[no_mp].type = MW_LFO_PMOD;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x0a;
				no_mp++;
				continue;
			case 0x21:
				mp_list[no_mp].type = MW_LFO_FMOD;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x00;
				no_mp++;
				continue;
			case 0x22:
				mp_list[no_mp].type = MW_LFO_AMOD;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x00;
				no_mp++;
				continue;
			case 0x4e:
				mp_list[no_mp].type =  CAT_FILTER_CONTROL;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x40;
				no_mp++;
				continue;
			case 0x50:
				mp_list[no_mp].type =  CAT_LFO_PMOD;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x00;
				no_mp++;
				continue;
			case 0x51:
				mp_list[no_mp].type =  CAT_LFO_FMOD;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x00;
				no_mp++;
				continue;
			case 0x52:
				mp_list[no_mp].type =  CAT_LFO_AMOD;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x00;
				no_mp++;
				continue;
			case 0x72:
				mp_list[no_mp].type =  EQ_BASS_GAIN;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x40;
				no_mp++;
				continue;
			case 0x73:
				mp_list[no_mp].type =  EQ_TREBLE_GAIN;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x40;
				no_mp++;
				continue;
			case 0x76:
				mp_list[no_mp].type =  EQ_BASS_FREQU;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x0c;
				no_mp++;
				continue;
			case 0x77:
				mp_list[no_mp].type =  EQ_TREBLE_FREQU;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x36;
				no_mp++;
				continue;
			default:
				HP_Delete(data);
				continue;
 			}
		}// end data[4] == 0x08
		else if(data[4]==0x0a)
		{
			switch(data[6])
			{
			case 0x40:
				mp_list[no_mp].type =  OFFSET_LEVEL_CONTROL_MW;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x40;
				no_mp++;
				continue;
			case 0x42:
				mp_list[no_mp].type =  OFFSET_LEVEL_CONTROL_CAT;
				mp_list[no_mp].data = data;
				mp_list[no_mp].is_default = data[7]==0x40;
				no_mp++;
				continue;
			default:
				HP_Delete(data);
				continue;
 			}
		} // end data[4] == 0x0a
	} // end loop voicefile 
	// mp_list is filled

	// Set 0 in all multi_part-sysex

	int i;

	for (i=0; i<no_mp; i++)
	{
		(mp_list[i].data)[5] = 0;
	}

	// insert multiparts:
	
	HP_SetFirst(mf_voiceplay_melody, HP_LAST);

	// 1. EQ Bass Gain
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==EQ_BASS_GAIN) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf_voiceplay_melody, act_effect_event_time, mp_list[i].data);
			act_effect_event_time += 5;
			break;
		}
	}
	// 2. EQ Treble Gain
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==EQ_TREBLE_GAIN) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf_voiceplay_melody, act_effect_event_time, mp_list[i].data);
			act_effect_event_time += 5;
			break;
		}
	}
	// 3. EQ Bass Frequ.
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==EQ_BASS_FREQU) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf_voiceplay_melody, act_effect_event_time, mp_list[i].data);
			act_effect_event_time += 5;
			break;
		}
	}
	// 4. EQ Treble Frequ.
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==EQ_TREBLE_FREQU) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf_voiceplay_melody, act_effect_event_time, mp_list[i].data);
			act_effect_event_time += 5;
			break;
		}
	}

	// 5. Velocity Sense Depth
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==VELOCITY_SENSE_DEPTH) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf_voiceplay_melody, act_effect_event_time, mp_list[i].data);
			act_effect_event_time += 5;
			break;
		}
	}

	// 6. Velocity Sense Offset
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==VELOCITY_SENSE_OFFSET) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf_voiceplay_melody, act_effect_event_time, mp_list[i].data);
			act_effect_event_time += 5;
			break;
		}
	}

	// 7. CAT LFO Pmod.
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==CAT_LFO_PMOD) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf_voiceplay_melody, act_effect_event_time, mp_list[i].data);
			act_effect_event_time += 5;
			break;
		}
	}

	// 8. CAT LFO Fmod.
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==CAT_LFO_FMOD) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf_voiceplay_melody, act_effect_event_time, mp_list[i].data);
			act_effect_event_time += 5;
			break;
		}
	}

	// 9. CAT LFO Amod
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==CAT_LFO_AMOD) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf_voiceplay_melody, act_effect_event_time, mp_list[i].data);
			act_effect_event_time += 5;
			break;
		}
	}

	// 10. MW LFO Pmod
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==MW_LFO_PMOD) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf_voiceplay_melody, act_effect_event_time, mp_list[i].data);
			act_effect_event_time += 5;
			break;
		}
	}

	// 11. MW LFO Fmod
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==MW_LFO_FMOD) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf_voiceplay_melody, act_effect_event_time, mp_list[i].data);
			act_effect_event_time += 5;
			break;
		}
	}

	// 12. MW LFO Amod
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==MW_LFO_AMOD) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf_voiceplay_melody, act_effect_event_time, mp_list[i].data);
			act_effect_event_time += 5;
			break;
		}
	}

	// 13. CAT Filter Control
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==CAT_FILTER_CONTROL) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf_voiceplay_melody, act_effect_event_time, mp_list[i].data);
			act_effect_event_time += 5;
			break;
		}
	}

	// 14. Offset Level Control CAT
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==OFFSET_LEVEL_CONTROL_CAT) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf_voiceplay_melody, act_effect_event_time, mp_list[i].data);
			act_effect_event_time += 5;
			break;
		}
	}

	// 15. MW Filter Control
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==MW_FILTER_CONTROL) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf_voiceplay_melody, act_effect_event_time, mp_list[i].data);
			act_effect_event_time += 5;
			break;
		}
	}

	// 16. Offset Level Control MW
	for (i=0; i<no_mp; i++)
	{
		if ((mp_list[i].type==OFFSET_LEVEL_CONTROL_MW) && (!mp_list[i].is_default))
		{
			HP_InsertSysEx(mf_voiceplay_melody, act_effect_event_time, mp_list[i].data);
			act_effect_event_time += 5;
			break;
		}
	}

	for (i=0; i<no_mp; i++)
	{
		HP_Delete(mp_list[i].data);
	}

	rcvchannel_data[5] = 0;
	rcvchannel_data[7] = 0;
	HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,rcvchannel_data);
	act_effect_event_time += 5;
}

void VoicefileRevoicingDlg::add_standard_drum_sysex_play(HP_MIDIFILE_MODULE* mf_voice)
{
	int id, chan, time, type, length;
	unsigned char* data;

	unsigned char drum1[]  = {0xF0,0x43,0x10,0x4C,0x30,0x24,0x05,0x00,0xF7}; 	// (XG) Drum Setup (no 0) Note C3 , Reverb Send Level  0
	unsigned char drum2[]  = {0xF0,0x43,0x10,0x4C,0x30,0x2A,0x05,0x5C,0xF7}; 	// (XG) Drum Setup (no 0) Note F#3, Reverb Send Level 92
	unsigned char drum3[]  = {0xF0,0x43,0x10,0x4C,0x30,0x2C,0x05,0x5C,0xF7}; 	// (XG) Drum Setup (no 0) Note G#3, Reverb Send Level 92
	unsigned char drum4[]  = {0xF0,0x43,0x10,0x4C,0x30,0x2E,0x05,0x5C,0xF7}; 	// (XG) Drum Setup (no 0) Note A#3, Reverb Send Level 92
	unsigned char drum5[]  = {0xF0,0x43,0x10,0x4C,0x30,0x2A,0x02,0x66,0xF7}; 	// (XG) Drum Setup (no 0) Note F#3, Level 102
	unsigned char drum6[]  = {0xF0,0x43,0x10,0x4C,0x30,0x2C,0x02,0x70,0xF7}; 	// (XG) Drum Setup (no 0) Note G#3, Level 112
	unsigned char drum7[]  = {0xF0,0x43,0x10,0x4C,0x30,0x2E,0x02,0x7A,0xF7}; 	// (XG) Drum Setup (no 0) Note A#3, Level 122
	unsigned char drum8[]  = {0xF0,0x43,0x10,0x4C,0x31,0x45,0x02,0x32,0xF7}; 	// (XG) Drum Setup (no 1) Note A5 , Level 50
	unsigned char drum9[]  = {0xF0,0x43,0x10,0x4C,0x31,0x52,0x02,0x49,0xF7}; 	// (XG) Drum Setup (no 1) Note A#6, Level 73
	unsigned char drum10[] = {0xF0,0x43,0x10,0x4C,0x30,0x24,0x02,0x68,0xF7}; 	// (XG) Drum Setup (no 0) Note C3 , Level 104
	unsigned char drum11[] = {0xF0,0x43,0x10,0x4C,0x30,0x26,0x02,0x7C,0xF7}; 	// (XG) Drum Setup (no 0) Note D3 , Level 124
	unsigned char drum12[] = {0xF0,0x43,0x10,0x4C,0x31,0x36,0x05,0x7F,0xF7}; 	// (XG) Drum Setup (no 1) Note F#4, Reverb Send Level 127

	HP_Rewind(mf_voice);
	while (HP_ReadEvent(mf_voice,&id,&chan,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_NOTE) break;
		if (type != HP_SYSEX) continue;
		HP_ReadSysex(mf_voice,id,&time,&data,&length);

		if (GlobalUtilities::compare_data(drum1,4,data,4))
		{
			if ((data[4]&0x30)==0x30)
			{
				HP_Delete(data);
				return;
			}
		}
		HP_Delete(data);
	}

	HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,drum1);
	act_effect_event_time += 5;
	HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,drum2);
	act_effect_event_time += 5;
	HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,drum3);
	act_effect_event_time += 5;
	HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,drum4);
	act_effect_event_time += 5;
	HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,drum5);
	act_effect_event_time += 5;
	HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,drum6);
	act_effect_event_time += 5;
	HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,drum7);
	act_effect_event_time += 5;
	HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,drum8);
	act_effect_event_time += 5;
	HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,drum9);
	act_effect_event_time += 5;
	HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,drum10);
	act_effect_event_time += 5;
	HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,drum11);
	act_effect_event_time += 5;
	HP_InsertSysEx(mf_voiceplay_melody,act_effect_event_time,drum12);
	act_effect_event_time += 5;
}


void VoicefileRevoicingDlg::OnTimer(UINT nIDEvent) 
{
	if (!HP_IsPlaying(mf_voiceplay_melody))
	{	// play done
		KillTimer(m_nTimer);
		m_nTimer = NULL;

		(testchan_list[act_testchan])->EnableWindow(TRUE);
		(ctrl_list[act_testchan])->EnableWindow(TRUE);
		(revoice_list[act_testchan])->EnableWindow(TRUE);
		(block_list[act_testchan])->EnableWindow(TRUE);
		act_testchan = -1;
		m_ok.EnableWindow(TRUE);
		m_cancel.EnableWindow(TRUE);
	}

	CDialog::OnTimer(nIDEvent);
}
