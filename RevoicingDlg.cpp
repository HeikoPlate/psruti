// RevoicingDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "RevoicingDlg.h"
#include "InsdefDlg.h"
#include "BrowseDlg.h"
#include "InsDefOnOffDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld RevoicingDlg 


RevoicingDlg::RevoicingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RevoicingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(RevoicingDlg)
	//}}AFX_DATA_INIT

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

	banknamelist[0] = &m_bankname1;
	banknamelist[1] = &m_bankname2;
	banknamelist[2] = &m_bankname3;
	banknamelist[3] = &m_bankname4;
	banknamelist[4] = &m_bankname5;
	banknamelist[5] = &m_bankname6;
	banknamelist[6] = &m_bankname7;
	banknamelist[7] = &m_bankname8;
	banknamelist[8] = &m_bankname9;
	banknamelist[9] = &m_bankname10;
	banknamelist[10] = &m_bankname11;
	banknamelist[11] = &m_bankname12;
	banknamelist[12] = &m_bankname13;
	banknamelist[13] = &m_bankname14;
	banknamelist[14] = &m_bankname15;
	banknamelist[15] = &m_bankname16;

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

	browse_list[0] = &m_voice_browse1;
	browse_list[1] = &m_voice_browse2;
	browse_list[2] = &m_voice_browse3;
	browse_list[3] = &m_voice_browse4;
	browse_list[4] = &m_voice_browse5;
	browse_list[5] = &m_voice_browse6;
	browse_list[6] = &m_voice_browse7;
	browse_list[7] = &m_voice_browse8;
	browse_list[8] = &m_voice_browse9;
	browse_list[9] = &m_voice_browse10;
	browse_list[10] = &m_voice_browse11;
	browse_list[11] = &m_voice_browse12;
	browse_list[12] = &m_voice_browse13;
	browse_list[13] = &m_voice_browse14;
	browse_list[14] = &m_voice_browse15;
	browse_list[15] = &m_voice_browse16;

	test_list[0] = &m_voice_test1;
	test_list[1] = &m_voice_test2;
	test_list[2] = &m_voice_test3;
	test_list[3] = &m_voice_test4;
	test_list[4] = &m_voice_test5;
	test_list[5] = &m_voice_test6;
	test_list[6] = &m_voice_test7;
	test_list[7] = &m_voice_test8;
	test_list[8] = &m_voice_test9;
	test_list[9] = &m_voice_test10;
	test_list[10] = &m_voice_test11;
	test_list[11] = &m_voice_test12;
	test_list[12] = &m_voice_test13;
	test_list[13] = &m_voice_test14;
	test_list[14] = &m_voice_test15;
	test_list[15] = &m_voice_test16;

	voicenamelist[0] = &m_voicename1;
	voicenamelist[1] = &m_voicename2;
	voicenamelist[2] = &m_voicename3;
	voicenamelist[3] = &m_voicename4;
	voicenamelist[4] = &m_voicename5;
	voicenamelist[5] = &m_voicename6;
	voicenamelist[6] = &m_voicename7;
	voicenamelist[7] = &m_voicename8;
	voicenamelist[8] = &m_voicename9;
	voicenamelist[9] = &m_voicename10;
	voicenamelist[10] = &m_voicename11;
	voicenamelist[11] = &m_voicename12;
	voicenamelist[12] = &m_voicename13;
	voicenamelist[13] = &m_voicename14;
	voicenamelist[14] = &m_voicename15;
	voicenamelist[15] = &m_voicename16;

	mf_voiceplay_melody = NULL;
	mf_voiceplay_drum = NULL;

	m_nTimer = NULL;
}

BOOL RevoicingDlg::PreTranslateMessage(MSG* pMSG)
{
	if(pMSG->message == WM_KEYDOWN)
	{
		// ESC-Taste abfangen
		if(pMSG->wParam == VK_ESCAPE)
		{
			OnOK();
			return TRUE;
		}
	}

	if (NULL != m_pToolTip)
	{
		m_pToolTip->RelayEvent(pMSG);
	}
	return CDialog::PreTranslateMessage(pMSG);
}

BOOL RevoicingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString text = "Revoicing:  ";
	text += hpmfi->proposed_songname;
	SetWindowText(text);
	SetCursor(hCursorWait);	
	get_init_data();
	SetCursor(hCursorOld);

	mf_voiceplay_melody = hpmfi->create_testsequence_melody();
	mf_voiceplay_drum = hpmfi->create_testsequence_drum();

	// Tool Tips
	m_pToolTip = NULL; // first call here

	return TRUE;	
}

void RevoicingDlg::get_init_data()
{
	int chan;
	bool result = false;
	bool found = false;

	SetDlgItemText(IDC_CHANNELTXT,GlobalUtilities::get_resource_string(IDS_CHANNEL));
	SetDlgItemText(IDC_BANKNUMBER,"Bank");
	SetDlgItemText(IDC_BANKNAMETXT,GlobalUtilities::get_resource_string(IDS_BANKNAME));
	SetDlgItemText(IDC_VOICENOTXT,"Voice");
	SetDlgItemText(IDC_VOICENAMETXT,GlobalUtilities::get_resource_string(IDS_VOICENAME));
	SetDlgItemText(IDC_BROWSE_TEXT,GlobalUtilities::get_resource_string(IDS_BROWSE_VOICE));
	SetDlgItemText(IDC_VOICE_TEST,"Test");

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
		if(voicelist[chan].with_note)
		{
			(bankno_list[chan])->EnableWindow(TRUE);
			(voiceno_list[chan])->EnableWindow(TRUE);
			(browse_list[chan])->EnableWindow(TRUE);
			(test_list[chan])->EnableWindow(TRUE);
		}
		else
		{
			(bankno_list[chan])->EnableWindow(FALSE);
			(voiceno_list[chan])->EnableWindow(FALSE);
			(browse_list[chan])->EnableWindow(FALSE);
			(test_list[chan])->EnableWindow(FALSE);
		}

		if (!voicelist[chan].with_note)
		{
			SetDlgItemText(bankno_idlist[chan],"");
		}
		else
		{
			SetDlgItemInt(bankno_idlist[chan],128*voicelist[chan].msb+voicelist[chan].lsb,FALSE);
		}

		if (!voicelist[chan].with_note)
		{
			SetDlgItemText(voiceno_idlist[chan],"");
		}
		else
		{
			SetDlgItemInt(voiceno_idlist[chan],voicelist[chan].voice,FALSE);
		}
	}

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
	hpmfi->find_insfile_bank_voicenames();

	SetCursor(hCursorOld);
}

void RevoicingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RevoicingDlg)
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_VOICE_BROWSE1, m_voice_browse1);
	DDX_Control(pDX, IDC_VOICE_BROWSE2, m_voice_browse2);
	DDX_Control(pDX, IDC_VOICE_BROWSE3, m_voice_browse3);
	DDX_Control(pDX, IDC_VOICE_BROWSE4, m_voice_browse4);
	DDX_Control(pDX, IDC_VOICE_BROWSE5, m_voice_browse5);
	DDX_Control(pDX, IDC_VOICE_BROWSE6, m_voice_browse6);
	DDX_Control(pDX, IDC_VOICE_BROWSE7, m_voice_browse7);
	DDX_Control(pDX, IDC_VOICE_BROWSE8, m_voice_browse8);
	DDX_Control(pDX, IDC_VOICE_BROWSE9, m_voice_browse9);
	DDX_Control(pDX, IDC_VOICE_BROWSE10, m_voice_browse10);
	DDX_Control(pDX, IDC_VOICE_BROWSE11, m_voice_browse11);
	DDX_Control(pDX, IDC_VOICE_BROWSE12, m_voice_browse12);
	DDX_Control(pDX, IDC_VOICE_BROWSE13, m_voice_browse13);
	DDX_Control(pDX, IDC_VOICE_BROWSE14, m_voice_browse14);
	DDX_Control(pDX, IDC_VOICE_BROWSE15, m_voice_browse15);
	DDX_Control(pDX, IDC_VOICE_BROWSE16, m_voice_browse16);
	DDX_Control(pDX, IDC_VOICE_TEST1, m_voice_test1);
	DDX_Control(pDX, IDC_VOICE_TEST2, m_voice_test2);
	DDX_Control(pDX, IDC_VOICE_TEST3, m_voice_test3);
	DDX_Control(pDX, IDC_VOICE_TEST4, m_voice_test4);
	DDX_Control(pDX, IDC_VOICE_TEST5, m_voice_test5);
	DDX_Control(pDX, IDC_VOICE_TEST6, m_voice_test6);
	DDX_Control(pDX, IDC_VOICE_TEST7, m_voice_test7);
	DDX_Control(pDX, IDC_VOICE_TEST8, m_voice_test8);
	DDX_Control(pDX, IDC_VOICE_TEST9, m_voice_test9);
	DDX_Control(pDX, IDC_VOICE_TEST10, m_voice_test10);
	DDX_Control(pDX, IDC_VOICE_TEST11, m_voice_test11);
	DDX_Control(pDX, IDC_VOICE_TEST12, m_voice_test12);
	DDX_Control(pDX, IDC_VOICE_TEST13, m_voice_test13);
	DDX_Control(pDX, IDC_VOICE_TEST14, m_voice_test14);
	DDX_Control(pDX, IDC_VOICE_TEST15, m_voice_test15);
	DDX_Control(pDX, IDC_VOICE_TEST16, m_voice_test16);
	DDX_Control(pDX,    IDC_BANKNO1,    m_bankno1);
	DDX_Control(pDX,   IDC_VOICENO1,   m_voiceno1);
	DDX_Control(pDX,  IDC_BANKNAME1,  m_bankname1);
	DDX_Control(pDX, IDC_VOICENAME1, m_voicename1);
	DDX_Control(pDX,    IDC_BANKNO2,    m_bankno2);
	DDX_Control(pDX,   IDC_VOICENO2,   m_voiceno2);
	DDX_Control(pDX,  IDC_BANKNAME2,  m_bankname2);
	DDX_Control(pDX, IDC_VOICENAME2, m_voicename2);
	DDX_Control(pDX,    IDC_BANKNO3,    m_bankno3);
	DDX_Control(pDX,   IDC_VOICENO3,   m_voiceno3);
	DDX_Control(pDX,  IDC_BANKNAME3,  m_bankname3);
	DDX_Control(pDX, IDC_VOICENAME3, m_voicename3);
	DDX_Control(pDX,    IDC_BANKNO4,    m_bankno4);
	DDX_Control(pDX,   IDC_VOICENO4,   m_voiceno4);
	DDX_Control(pDX,  IDC_BANKNAME4,  m_bankname4);
	DDX_Control(pDX, IDC_VOICENAME4, m_voicename4);
	DDX_Control(pDX,    IDC_BANKNO5,    m_bankno5);
	DDX_Control(pDX,   IDC_VOICENO5,   m_voiceno5);
	DDX_Control(pDX,  IDC_BANKNAME5,  m_bankname5);
	DDX_Control(pDX, IDC_VOICENAME5, m_voicename5);
	DDX_Control(pDX,    IDC_BANKNO6,    m_bankno6);
	DDX_Control(pDX,   IDC_VOICENO6,   m_voiceno6);
	DDX_Control(pDX,  IDC_BANKNAME6,  m_bankname6);
	DDX_Control(pDX, IDC_VOICENAME6, m_voicename6);
	DDX_Control(pDX,    IDC_BANKNO7,    m_bankno7);
	DDX_Control(pDX,   IDC_VOICENO7,   m_voiceno7);
	DDX_Control(pDX,  IDC_BANKNAME7,  m_bankname7);
	DDX_Control(pDX, IDC_VOICENAME7, m_voicename7);
	DDX_Control(pDX,    IDC_BANKNO8,    m_bankno8);
	DDX_Control(pDX,   IDC_VOICENO8,   m_voiceno8);
	DDX_Control(pDX,  IDC_BANKNAME8,  m_bankname8);
	DDX_Control(pDX, IDC_VOICENAME8, m_voicename8);
	DDX_Control(pDX,    IDC_BANKNO9,    m_bankno9);
	DDX_Control(pDX,   IDC_VOICENO9,   m_voiceno9);
	DDX_Control(pDX,  IDC_BANKNAME9,  m_bankname9);
	DDX_Control(pDX, IDC_VOICENAME9, m_voicename9);
	DDX_Control(pDX,    IDC_BANKNO10,    m_bankno10);
	DDX_Control(pDX,   IDC_VOICENO10,   m_voiceno10);
	DDX_Control(pDX,  IDC_BANKNAME10,  m_bankname10);
	DDX_Control(pDX, IDC_VOICENAME10, m_voicename10);
	DDX_Control(pDX,    IDC_BANKNO11,    m_bankno11);
	DDX_Control(pDX,   IDC_VOICENO11,   m_voiceno11);
	DDX_Control(pDX,  IDC_BANKNAME11,  m_bankname11);
	DDX_Control(pDX, IDC_VOICENAME11, m_voicename11);
	DDX_Control(pDX,    IDC_BANKNO12,    m_bankno12);
	DDX_Control(pDX,   IDC_VOICENO12,   m_voiceno12);
	DDX_Control(pDX,  IDC_BANKNAME12,  m_bankname12);
	DDX_Control(pDX, IDC_VOICENAME12, m_voicename12);
	DDX_Control(pDX,    IDC_BANKNO13,    m_bankno13);
	DDX_Control(pDX,   IDC_VOICENO13,   m_voiceno13);
	DDX_Control(pDX,  IDC_BANKNAME13,  m_bankname13);
	DDX_Control(pDX, IDC_VOICENAME13, m_voicename13);
	DDX_Control(pDX,    IDC_BANKNO14,    m_bankno14);
	DDX_Control(pDX,   IDC_VOICENO14,   m_voiceno14);
	DDX_Control(pDX,  IDC_BANKNAME14,  m_bankname14);
	DDX_Control(pDX, IDC_VOICENAME14, m_voicename14);
	DDX_Control(pDX,    IDC_BANKNO15,    m_bankno15);
	DDX_Control(pDX,   IDC_VOICENO15,   m_voiceno15);
	DDX_Control(pDX,  IDC_BANKNAME15,  m_bankname15);
	DDX_Control(pDX, IDC_VOICENAME15, m_voicename15);
	DDX_Control(pDX,    IDC_BANKNO16,    m_bankno16);
	DDX_Control(pDX,   IDC_VOICENO16,   m_voiceno16);
	DDX_Control(pDX,  IDC_BANKNAME16,  m_bankname16);
	DDX_Control(pDX, IDC_VOICENAME16, m_voicename16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RevoicingDlg, CDialog)
	//{{AFX_MSG_MAP(RevoicingDlg)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_BANKNAME1, OnSelchangeBankname1)
	ON_CBN_SELCHANGE(IDC_BANKNAME2, OnSelchangeBankname2)
	ON_CBN_SELCHANGE(IDC_BANKNAME3, OnSelchangeBankname3)
	ON_CBN_SELCHANGE(IDC_BANKNAME4, OnSelchangeBankname4)
	ON_CBN_SELCHANGE(IDC_BANKNAME5, OnSelchangeBankname5)
	ON_CBN_SELCHANGE(IDC_BANKNAME6, OnSelchangeBankname6)
	ON_CBN_SELCHANGE(IDC_BANKNAME7, OnSelchangeBankname7)
	ON_CBN_SELCHANGE(IDC_BANKNAME8, OnSelchangeBankname8)
	ON_CBN_SELCHANGE(IDC_BANKNAME9, OnSelchangeBankname9)
	ON_CBN_SELCHANGE(IDC_BANKNAME10, OnSelchangeBankname10)
	ON_CBN_SELCHANGE(IDC_BANKNAME11, OnSelchangeBankname11)
	ON_CBN_SELCHANGE(IDC_BANKNAME12, OnSelchangeBankname12)
	ON_CBN_SELCHANGE(IDC_BANKNAME13, OnSelchangeBankname13)
	ON_CBN_SELCHANGE(IDC_BANKNAME14, OnSelchangeBankname14)
	ON_CBN_SELCHANGE(IDC_BANKNAME15, OnSelchangeBankname15)
	ON_CBN_SELCHANGE(IDC_BANKNAME16, OnSelchangeBankname16)
	ON_CBN_SELCHANGE(IDC_VOICENAME1, OnSelchangeVoicename1)
	ON_CBN_SELCHANGE(IDC_VOICENAME2, OnSelchangeVoicename2)
	ON_CBN_SELCHANGE(IDC_VOICENAME3, OnSelchangeVoicename3)
	ON_CBN_SELCHANGE(IDC_VOICENAME4, OnSelchangeVoicename4)
	ON_CBN_SELCHANGE(IDC_VOICENAME5, OnSelchangeVoicename5)
	ON_CBN_SELCHANGE(IDC_VOICENAME6, OnSelchangeVoicename6)
	ON_CBN_SELCHANGE(IDC_VOICENAME7, OnSelchangeVoicename7)
	ON_CBN_SELCHANGE(IDC_VOICENAME8, OnSelchangeVoicename8)
	ON_CBN_SELCHANGE(IDC_VOICENAME9, OnSelchangeVoicename9)
	ON_CBN_SELCHANGE(IDC_VOICENAME10, OnSelchangeVoicename10)
	ON_CBN_SELCHANGE(IDC_VOICENAME11, OnSelchangeVoicename11)
	ON_CBN_SELCHANGE(IDC_VOICENAME12, OnSelchangeVoicename12)
	ON_CBN_SELCHANGE(IDC_VOICENAME13, OnSelchangeVoicename13)
	ON_CBN_SELCHANGE(IDC_VOICENAME14, OnSelchangeVoicename14)
	ON_CBN_SELCHANGE(IDC_VOICENAME15, OnSelchangeVoicename15)
	ON_CBN_SELCHANGE(IDC_VOICENAME16, OnSelchangeVoicename16)
	ON_EN_CHANGE(IDC_BANKNO1, OnChangeBankno1)
	ON_EN_CHANGE(IDC_BANKNO2, OnChangeBankno2)
	ON_EN_CHANGE(IDC_BANKNO3, OnChangeBankno3)
	ON_EN_CHANGE(IDC_BANKNO4, OnChangeBankno4)
	ON_EN_CHANGE(IDC_BANKNO5, OnChangeBankno5)
	ON_EN_CHANGE(IDC_BANKNO6, OnChangeBankno6)
	ON_EN_CHANGE(IDC_BANKNO7, OnChangeBankno7)
	ON_EN_CHANGE(IDC_BANKNO8, OnChangeBankno8)
	ON_EN_CHANGE(IDC_BANKNO9, OnChangeBankno9)
	ON_EN_CHANGE(IDC_BANKNO10, OnChangeBankno10)
	ON_EN_CHANGE(IDC_BANKNO11, OnChangeBankno11)
	ON_EN_CHANGE(IDC_BANKNO12, OnChangeBankno12)
	ON_EN_CHANGE(IDC_BANKNO13, OnChangeBankno13)
	ON_EN_CHANGE(IDC_BANKNO14, OnChangeBankno14)
	ON_EN_CHANGE(IDC_BANKNO15, OnChangeBankno15)
	ON_EN_CHANGE(IDC_BANKNO16, OnChangeBankno16)
	ON_EN_CHANGE(IDC_VOICENO1, OnChangeVoiceno1)
	ON_EN_CHANGE(IDC_VOICENO2, OnChangeVoiceno2)
	ON_EN_CHANGE(IDC_VOICENO3, OnChangeVoiceno3)
	ON_EN_CHANGE(IDC_VOICENO4, OnChangeVoiceno4)
	ON_EN_CHANGE(IDC_VOICENO5, OnChangeVoiceno5)
	ON_EN_CHANGE(IDC_VOICENO6, OnChangeVoiceno6)
	ON_EN_CHANGE(IDC_VOICENO7, OnChangeVoiceno7)
	ON_EN_CHANGE(IDC_VOICENO8, OnChangeVoiceno8)
	ON_EN_CHANGE(IDC_VOICENO9, OnChangeVoiceno9)
	ON_EN_CHANGE(IDC_VOICENO10, OnChangeVoiceno10)
	ON_EN_CHANGE(IDC_VOICENO11, OnChangeVoiceno11)
	ON_EN_CHANGE(IDC_VOICENO12, OnChangeVoiceno12)
	ON_EN_CHANGE(IDC_VOICENO13, OnChangeVoiceno13)
	ON_EN_CHANGE(IDC_VOICENO14, OnChangeVoiceno14)
	ON_EN_CHANGE(IDC_VOICENO15, OnChangeVoiceno15)
	ON_EN_CHANGE(IDC_VOICENO16, OnChangeVoiceno16)
	ON_BN_CLICKED(IDC_VOICE_BROWSE1, OnVoiceBrowse1)
	ON_BN_CLICKED(IDC_VOICE_BROWSE2, OnVoiceBrowse2)
	ON_BN_CLICKED(IDC_VOICE_BROWSE3, OnVoiceBrowse3)
	ON_BN_CLICKED(IDC_VOICE_BROWSE4, OnVoiceBrowse4)
	ON_BN_CLICKED(IDC_VOICE_BROWSE5, OnVoiceBrowse5)
	ON_BN_CLICKED(IDC_VOICE_BROWSE6, OnVoiceBrowse6)
	ON_BN_CLICKED(IDC_VOICE_BROWSE7, OnVoiceBrowse7)
	ON_BN_CLICKED(IDC_VOICE_BROWSE8, OnVoiceBrowse8)
	ON_BN_CLICKED(IDC_VOICE_BROWSE9, OnVoiceBrowse9)
	ON_BN_CLICKED(IDC_VOICE_BROWSE10, OnVoiceBrowse10)
	ON_BN_CLICKED(IDC_VOICE_BROWSE11, OnVoiceBrowse11)
	ON_BN_CLICKED(IDC_VOICE_BROWSE12, OnVoiceBrowse12)
	ON_BN_CLICKED(IDC_VOICE_BROWSE13, OnVoiceBrowse13)
	ON_BN_CLICKED(IDC_VOICE_BROWSE14, OnVoiceBrowse14)
	ON_BN_CLICKED(IDC_VOICE_BROWSE15, OnVoiceBrowse15)
	ON_BN_CLICKED(IDC_VOICE_BROWSE16, OnVoiceBrowse16)
	ON_BN_CLICKED(IDC_VOICE_TEST1, OnVoiceTest1)
	ON_BN_CLICKED(IDC_VOICE_TEST2, OnVoiceTest2)
	ON_BN_CLICKED(IDC_VOICE_TEST3, OnVoiceTest3)
	ON_BN_CLICKED(IDC_VOICE_TEST4, OnVoiceTest4)
	ON_BN_CLICKED(IDC_VOICE_TEST5, OnVoiceTest5)
	ON_BN_CLICKED(IDC_VOICE_TEST6, OnVoiceTest6)
	ON_BN_CLICKED(IDC_VOICE_TEST7, OnVoiceTest7)
	ON_BN_CLICKED(IDC_VOICE_TEST8, OnVoiceTest8)
	ON_BN_CLICKED(IDC_VOICE_TEST9, OnVoiceTest9)
	ON_BN_CLICKED(IDC_VOICE_TEST10, OnVoiceTest10)
	ON_BN_CLICKED(IDC_VOICE_TEST11, OnVoiceTest11)
	ON_BN_CLICKED(IDC_VOICE_TEST12, OnVoiceTest12)
	ON_BN_CLICKED(IDC_VOICE_TEST13, OnVoiceTest13)
	ON_BN_CLICKED(IDC_VOICE_TEST14, OnVoiceTest14)
	ON_BN_CLICKED(IDC_VOICE_TEST15, OnVoiceTest15)
	ON_BN_CLICKED(IDC_VOICE_TEST16, OnVoiceTest16)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten RevoicingDlg 

void RevoicingDlg::OnOK() 
{
	int chan;
	unsigned long bank;
	int voice;
	for (chan = 0; chan<16; chan++)
	{
		if (!voicelist[chan].with_note) continue;
		bank = GetDlgItemInt(bankno_idlist[chan]);
		voice = GetDlgItemInt(voiceno_idlist[chan]);
		voicelist[chan].msb = bank/128;
		voicelist[chan].lsb = bank%128;
		voicelist[chan].voice = voice;
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

	CDialog::OnOK();
}

void RevoicingDlg::OnCancel() 
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

	CDialog::OnCancel();
}


void RevoicingDlg::set_banknames(int chan)
{
	int k;
	if (!voicelist[chan].with_note) return;
	banknamelist[chan]->ResetContent();

	long bank_no = GetDlgItemInt(bankno_idlist[chan]);
	int index = -1;
	for (k=0; k<hpmfi->no_banks; k++)
	{
		CString bankname = (hpmfi->bank_list)[k].bank_name;
		CString short_bankname = bankname.GetLength()>30?"..."+bankname.Right(30): bankname;
		banknamelist[chan]->AddString(short_bankname);
		if ((hpmfi->bank_list)[k].bank_number==bank_no)
		{
			index = k;
		}
	};
	if (index >= 0) banknamelist[chan]->SetCurSel(index); 
}

void RevoicingDlg::set_voicenames(unsigned long bank, int chan)
{
	voicenamelist[chan]->ResetContent();
	char * bank_name;
	int i;
	int bank_voices_list_index;
	bool already_got = false;


	for (bank_voices_list_index = 0; 
	     bank_voices_list_index < hpmfi->bank_voices_list_free; 
		 bank_voices_list_index++)
	{
		if (((hpmfi->bank_voices_list)[bank_voices_list_index]).bank_no == bank)
		{
			already_got = true;
			break;
		}
	}

	if (!already_got && (hpmfi->bank_voices_list_free < 128))
	{
		if (HP_CWInsGetBankVoices(hpmfi->mf,bank,&bank_name,&voices) == HP_ERR_NONE)
		{
			((hpmfi->bank_voices_list)[hpmfi->bank_voices_list_free]).bank_no = bank;
			for (i=0; i<128; i++)
			{
				((hpmfi->bank_voices_list)[hpmfi->bank_voices_list_free]).voice_name[i] = (voices[i]).voice_name;
			}
			HP_Delete(voices);

			bank_voices_list_index = hpmfi->bank_voices_list_free;
			hpmfi->bank_voices_list_free++;
			already_got = true;
		}
	}

	if (already_got)
	{
		int index = -1;
		for (i=0; i<128; i++)
		{
			CString voice_name = 
//				(((hpmfi->bank_voices_list)[bank_voices_list_index]).voice_name[i]).Left(29);
				(((hpmfi->bank_voices_list)[bank_voices_list_index]).voice_name[i]);
			GlobalUtilities::reduce_voicename(&voice_name);
			voicenamelist[chan]->AddString(voice_name);
			if (i == voicelist[chan].voice)
			{
				index = i;
			}
		}
		if (index >= 0) voicenamelist[chan]->SetCurSel(index);
	}
	else
	{
		if (HP_CWInsGetBankVoices(hpmfi->mf,bank,&bank_name,&voices) != HP_ERR_NONE)
		{
			(banknamelist[chan])->EnableWindow(FALSE);
			(voicenamelist[chan])->EnableWindow(FALSE);
		}
		else
		{
			int index = -1;
			int k;

			for (i=0; i<128; i++)
			{
				char str[30];
				str[29] = 0;
				char* voice_name = (voices[i]).voice_name;
				for (k=0; k<29; k++)
				{
					str[k] = voice_name[k];
					if (str[k]=='}')
					{
						str[k+1]=0;
						break;
					}
					if (str[k]==0) break;
				}
				voicenamelist[chan]->AddString(str);
				if (i == voicelist[chan].voice)
				{
					index = i;
				}
			}
			if (index >= 0) voicenamelist[chan]->SetCurSel(index); 
			(voicenamelist[chan])->EnableWindow(TRUE);
			HP_Delete(voices);
		}
	}
}

void RevoicingDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}

void RevoicingDlg::SelchangeBankname(int chan)
{
	int index = banknamelist[chan]->GetCurSel();
	unsigned long bank_no = (hpmfi->bank_list)[index].bank_number;
	SetDlgItemInt(bankno_idlist[chan],bank_no,FALSE);
	SetCursor(hCursorWait);	
	set_voicenames(bank_no,chan);
	SetCursor(hCursorOld);
}

void RevoicingDlg::OnSelchangeBankname1() 
{
	SelchangeBankname(0);
}

void RevoicingDlg::OnSelchangeBankname2() 
{
	SelchangeBankname(1);
}

void RevoicingDlg::OnSelchangeBankname3() 
{
	SelchangeBankname(2);
}

void RevoicingDlg::OnSelchangeBankname4() 
{
	SelchangeBankname(3);
}

void RevoicingDlg::OnSelchangeBankname5() 
{
	SelchangeBankname(4);
}

void RevoicingDlg::OnSelchangeBankname6() 
{
	SelchangeBankname(5);
}

void RevoicingDlg::OnSelchangeBankname7() 
{
	SelchangeBankname(6);
}

void RevoicingDlg::OnSelchangeBankname8() 
{
	SelchangeBankname(7);
}

void RevoicingDlg::OnSelchangeBankname9() 
{
	SelchangeBankname(8);
}

void RevoicingDlg::OnSelchangeBankname10() 
{
	SelchangeBankname(9);
}

void RevoicingDlg::OnSelchangeBankname11() 
{
	SelchangeBankname(10);
}

void RevoicingDlg::OnSelchangeBankname12() 
{
	SelchangeBankname(11);
}

void RevoicingDlg::OnSelchangeBankname13() 
{
	SelchangeBankname(12);
}

void RevoicingDlg::OnSelchangeBankname14() 
{
	SelchangeBankname(13);
}

void RevoicingDlg::OnSelchangeBankname15() 
{
	SelchangeBankname(14);
}

void RevoicingDlg::OnSelchangeBankname16() 
{
	SelchangeBankname(15);
}

void RevoicingDlg::SelchangeVoicename(int chan)
{
	int voice_no = voicenamelist[chan]->GetCurSel();
	SetDlgItemInt(voiceno_idlist[chan],voice_no,FALSE);
}

void RevoicingDlg::OnSelchangeVoicename1() 
{
	SelchangeVoicename(0);
}

void RevoicingDlg::OnSelchangeVoicename2() 
{
	SelchangeVoicename(1);
}

void RevoicingDlg::OnSelchangeVoicename3() 
{
	SelchangeVoicename(2);
}

void RevoicingDlg::OnSelchangeVoicename4() 
{
	SelchangeVoicename(3);
}

void RevoicingDlg::OnSelchangeVoicename5() 
{
	SelchangeVoicename(4);
}

void RevoicingDlg::OnSelchangeVoicename6() 
{
	SelchangeVoicename(5);
}

void RevoicingDlg::OnSelchangeVoicename7() 
{
	SelchangeVoicename(6);
}

void RevoicingDlg::OnSelchangeVoicename8() 
{
	SelchangeVoicename(7);
}

void RevoicingDlg::OnSelchangeVoicename9() 
{
	SelchangeVoicename(8);
}

void RevoicingDlg::OnSelchangeVoicename10() 
{
	SelchangeVoicename(9);
}

void RevoicingDlg::OnSelchangeVoicename11() 
{
	SelchangeVoicename(10);
}

void RevoicingDlg::OnSelchangeVoicename12() 
{
	SelchangeVoicename(11);
}

void RevoicingDlg::OnSelchangeVoicename13() 
{
	SelchangeVoicename(12);
}

void RevoicingDlg::OnSelchangeVoicename14() 
{
	SelchangeVoicename(13);
}

void RevoicingDlg::OnSelchangeVoicename15() 
{
	SelchangeVoicename(14);
}

void RevoicingDlg::OnSelchangeVoicename16() 
{
	SelchangeVoicename(15);
}

void RevoicingDlg::ChangeBankno(int chan)
{
	long bank_no = GetDlgItemInt(bankno_idlist[chan]);
	
	if (bank_no > 64000)
	{
		SetDlgItemInt(bankno_idlist[chan],0,FALSE);
		return;
	}

	int index;
	int found = false;
	for (index=0; index < hpmfi->no_banks; index++)
	{
		if ((hpmfi->bank_list)[index].bank_number == bank_no)
		{
			found = true;
			break;
		}
	}
	if (found)
	{
		(banknamelist[chan])->SetCurSel(index);
		if (hpmfi->with_insdef)
		{
			set_banknames(chan);
			SetCursor(hCursorWait);	
			set_voicenames(bank_no,chan);
			SetCursor(hCursorOld);
			banknamelist[chan]->EnableWindow(TRUE);
			voicenamelist[chan]->EnableWindow(TRUE);
		}
	}
	else
	{
		if (hpmfi->with_insdef)
		{
			banknamelist[chan]->ResetContent();
			voicenamelist[chan]->ResetContent();
			banknamelist[chan]->EnableWindow(FALSE);
			voicenamelist[chan]->EnableWindow(FALSE);
		}
	}
}

void RevoicingDlg::OnChangeBankno1() 
{
	ChangeBankno(0);
}

void RevoicingDlg::OnChangeBankno2() 
{
	ChangeBankno(1);
}

void RevoicingDlg::OnChangeBankno3() 
{
	ChangeBankno(2);
}

void RevoicingDlg::OnChangeBankno4() 
{
	ChangeBankno(3);
}

void RevoicingDlg::OnChangeBankno5() 
{
	ChangeBankno(4);
}

void RevoicingDlg::OnChangeBankno6() 
{
	ChangeBankno(5);
}

void RevoicingDlg::OnChangeBankno7() 
{
	ChangeBankno(6);
}

void RevoicingDlg::OnChangeBankno8() 
{
	ChangeBankno(7);
}

void RevoicingDlg::OnChangeBankno9() 
{
	ChangeBankno(8);
}

void RevoicingDlg::OnChangeBankno10() 
{
	ChangeBankno(9);
}

void RevoicingDlg::OnChangeBankno11() 
{
	ChangeBankno(10);
}

void RevoicingDlg::OnChangeBankno12() 
{
	ChangeBankno(11);
}

void RevoicingDlg::OnChangeBankno13() 
{
	ChangeBankno(12);
}

void RevoicingDlg::OnChangeBankno14() 
{
	ChangeBankno(13);
}

void RevoicingDlg::OnChangeBankno15() 
{
	ChangeBankno(14);
}

void RevoicingDlg::OnChangeBankno16() 
{
	ChangeBankno(15);
}

void RevoicingDlg::ChangeVoiceno(int chan)
{
	if(voicelist[chan].with_note)
	{
		int voice_no = GetDlgItemInt(voiceno_idlist[chan]);
		if (voice_no > 127)
		{
			SetDlgItemInt(voiceno_idlist[chan],0,FALSE);
			return;
		}
		(voicenamelist[chan])->SetCurSel(voice_no);
	}
//	hpmfi->play_sequence(0,112,1);
}

void RevoicingDlg::OnChangeVoiceno1() 
{
	ChangeVoiceno(0);
}

void RevoicingDlg::OnChangeVoiceno2() 
{
	ChangeVoiceno(1);
}

void RevoicingDlg::OnChangeVoiceno3() 
{
	ChangeVoiceno(2);
}

void RevoicingDlg::OnChangeVoiceno4() 
{
	ChangeVoiceno(3);
}

void RevoicingDlg::OnChangeVoiceno5() 
{
	ChangeVoiceno(4);
}

void RevoicingDlg::OnChangeVoiceno6() 
{
	ChangeVoiceno(5);
}

void RevoicingDlg::OnChangeVoiceno7() 
{
	ChangeVoiceno(6);
}

void RevoicingDlg::OnChangeVoiceno8() 
{
	ChangeVoiceno(7);
}

void RevoicingDlg::OnChangeVoiceno9() 
{
	ChangeVoiceno(8);
}

void RevoicingDlg::OnChangeVoiceno10() 
{
	ChangeVoiceno(9);
}

void RevoicingDlg::OnChangeVoiceno11() 
{
	ChangeVoiceno(10);
}

void RevoicingDlg::OnChangeVoiceno12() 
{
	ChangeVoiceno(11);
}

void RevoicingDlg::OnChangeVoiceno13() 
{
	ChangeVoiceno(12);
}

void RevoicingDlg::OnChangeVoiceno14() 
{
	ChangeVoiceno(13);
}

void RevoicingDlg::OnChangeVoiceno15() 
{
	ChangeVoiceno(14);
}

void RevoicingDlg::OnChangeVoiceno16() 
{
	ChangeVoiceno(15);
}

void RevoicingDlg::VoiceBrowse(int chan)
{
	BrowseDlg dlg;
	dlg.hpmfi = hpmfi;
	dlg.chan = chan;

	int dlg_result = dlg.DoModal();
	if (dlg_result == 0) return;

	SetDlgItemInt(bankno_idlist[chan],dlg.bank_no,FALSE);
	SetDlgItemInt(voiceno_idlist[chan],dlg.voice_no,FALSE);
	// that is enough	
/*
	CString r;
	r.Format("Chan %i, Bank %i: %s, Voice %i: %s",chan,dlg.bank_no,dlg.bank_name,dlg.voice_no,dlg.voice_name);
	::MessageBox(AfxGetMainWnd()->m_hWnd,r,"Test",MB_OK|MB_TASKMODAL);
*/
}

void RevoicingDlg::OnVoiceBrowse1() 
{
	VoiceBrowse(0);
}

void RevoicingDlg::OnVoiceBrowse2() 
{
	VoiceBrowse(1);
}

void RevoicingDlg::OnVoiceBrowse3() 
{
	VoiceBrowse(2);
}

void RevoicingDlg::OnVoiceBrowse4() 
{
	VoiceBrowse(3);
}

void RevoicingDlg::OnVoiceBrowse5() 
{
	VoiceBrowse(4);
}

void RevoicingDlg::OnVoiceBrowse6() 
{
	VoiceBrowse(5);
}

void RevoicingDlg::OnVoiceBrowse7() 
{
	VoiceBrowse(6);
}

void RevoicingDlg::OnVoiceBrowse8() 
{
	VoiceBrowse(7);
}

void RevoicingDlg::OnVoiceBrowse9() 
{
	VoiceBrowse(8);
}

void RevoicingDlg::OnVoiceBrowse10() 
{
	VoiceBrowse(9);
}

void RevoicingDlg::OnVoiceBrowse11() 
{
	VoiceBrowse(10);
}

void RevoicingDlg::OnVoiceBrowse12() 
{
	VoiceBrowse(11);
}

void RevoicingDlg::OnVoiceBrowse13() 
{
	VoiceBrowse(12);
}

void RevoicingDlg::OnVoiceBrowse14() 
{
	VoiceBrowse(13);
}

void RevoicingDlg::OnVoiceBrowse15() 
{
	VoiceBrowse(14);
}

void RevoicingDlg::OnVoiceBrowse16() 
{
	VoiceBrowse(15);
}

void RevoicingDlg::VoiceTest(int chan)
{
	int channel;
	int bank = GetDlgItemInt(bankno_idlist[chan]);
	int voice = GetDlgItemInt(voiceno_idlist[chan]);
	int id, ch, time, type;
	int note, velocity, length;
	int number, value;

	if (mf_voiceplay_melody == NULL) return; // do nothing if not possible

	for(channel=0; channel<16; channel++)
    {
		(test_list[channel])->EnableWindow(FALSE);
		(banknamelist[channel])->EnableWindow(FALSE);
		(bankno_list[channel])->EnableWindow(FALSE);
		(voiceno_list[channel])->EnableWindow(FALSE);
		(browse_list[channel])->EnableWindow(FALSE);
		(voicenamelist[channel])->EnableWindow(FALSE);
	}
	m_ok.EnableWindow(FALSE);
	m_cancel.EnableWindow(FALSE);

	// set test voice
	HP_Rewind(mf_voiceplay_melody);
	while (HP_ReadEvent(mf_voiceplay_melody,&id,&ch,&time,&type)==HP_ERR_NONE)
	{
		if (type == HP_BANK_SELECT_MSB) 
		{
			HP_ReadController(mf_voiceplay_melody,id, &time, &ch, &number, &value);
			HP_DeleteEvent(mf_voiceplay_melody,id);
			HP_InsertController(mf_voiceplay_melody,time,chan,HP_BANK_SELECT_MSB,bank/128,HP_NO_CONTROLLER_NUMBER);
			continue;
		}
		if (type == HP_BANK_SELECT_LSB) 
		{
			HP_ReadController(mf_voiceplay_melody,id, &time, &ch, &number, &value);
			HP_DeleteEvent(mf_voiceplay_melody,id);
			HP_InsertController(mf_voiceplay_melody,time,chan,HP_BANK_SELECT_LSB,bank%128,HP_NO_CONTROLLER_NUMBER);
			continue;
		}
		if (type == HP_PROGRAM_CHANGE)
		{
			HP_ReadProgramChange(mf_voiceplay_melody,id, &time, &ch, &number);
			HP_DeleteEvent(mf_voiceplay_melody,id);
			HP_InsertProgramChange(mf_voiceplay_melody,time,chan,voice);
			continue;
		}

		if (type == HP_NOTE)
		{
			HP_ReadNote(mf_voiceplay_melody,id,&time, &ch, &note, &velocity, &length);
			HP_ChangeNote(mf_voiceplay_melody,id,chan,note,HP_ABSOLUTE);
		}
	}

	if (!HP_IsPlaying(mf_voiceplay_melody))
	{
		SetCursor(hCursorWait);

		HP_Play(mf_voiceplay_melody,HP_ALL);

		// activate timer
		m_nTimer = SetTimer(1, 500, 0);
		SetCursor(hCursorOld);
	}
	else
	{
		int channel;
		for (channel=0; channel<16; channel++)
		{
			if(voicelist[channel].with_note)
			{
				(test_list[channel])->EnableWindow(TRUE);
				(banknamelist[channel])->EnableWindow(TRUE);
				(bankno_list[channel])->EnableWindow(TRUE);
				(voiceno_list[channel])->EnableWindow(TRUE);
				(browse_list[channel])->EnableWindow(TRUE);
				(voicenamelist[channel])->EnableWindow(TRUE);
			}
		}
		m_ok.EnableWindow(TRUE);
		m_cancel.EnableWindow(TRUE);
	}

//	HP_Save(mf_voiceplay_melody,"c:/temp/melody_voice_test.mid",HP_SMF0);
}


void RevoicingDlg::OnVoiceTest1() 
{
	VoiceTest(0);
}

void RevoicingDlg::OnVoiceTest2() 
{
	VoiceTest(1);
}

void RevoicingDlg::OnVoiceTest3() 
{
	VoiceTest(2);
}

void RevoicingDlg::OnVoiceTest4() 
{
	VoiceTest(3);
}

void RevoicingDlg::OnVoiceTest5() 
{
	VoiceTest(4);
}

void RevoicingDlg::OnVoiceTest6() 
{
	VoiceTest(5);
}

void RevoicingDlg::OnVoiceTest7() 
{
	VoiceTest(6);
}

void RevoicingDlg::OnVoiceTest8() 
{
	VoiceTest(7);
}

void RevoicingDlg::OnVoiceTest9() 
{
	VoiceTest(8);
}

void RevoicingDlg::OnVoiceTest10() 
{
	VoiceTest(9);
}

void RevoicingDlg::OnVoiceTest11() 
{
	VoiceTest(10);
}

void RevoicingDlg::OnVoiceTest12() 
{
	VoiceTest(11);
}

void RevoicingDlg::OnVoiceTest13() 
{
	VoiceTest(12);
}

void RevoicingDlg::OnVoiceTest14() 
{
	VoiceTest(13);
}

void RevoicingDlg::OnVoiceTest15() 
{
	VoiceTest(14);
}

void RevoicingDlg::OnVoiceTest16() 
{
	VoiceTest(15);
}

void RevoicingDlg::OnTimer(UINT nIDEvent) 
{
	if (!HP_IsPlaying(mf_voiceplay_melody))
	{	// play done
		KillTimer(m_nTimer);
		m_nTimer = NULL;
		int channel;
		for (channel=0; channel<16; channel++)
		{
			if(voicelist[channel].with_note)
			{
				(test_list[channel])->EnableWindow(TRUE);
				(banknamelist[channel])->EnableWindow(TRUE);
				(bankno_list[channel])->EnableWindow(TRUE);
				(voiceno_list[channel])->EnableWindow(TRUE);
				(browse_list[channel])->EnableWindow(TRUE);
				(voicenamelist[channel])->EnableWindow(TRUE);
			}
		}
		m_ok.EnableWindow(TRUE);
		m_cancel.EnableWindow(TRUE);
	}
	else
	{
		CDialog::OnTimer(nIDEvent);
	}
}
