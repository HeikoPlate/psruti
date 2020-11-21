// ImportLyricsAtChannelNotes.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "ImportLyricsAtChannelNotes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld ImportLyricsAtChannelNotes 


ImportLyricsAtChannelNotes::ImportLyricsAtChannelNotes(CWnd* pParent /*=NULL*/)
	: CDialog(ImportLyricsAtChannelNotes::IDD, pParent)
{
	//{{AFX_DATA_INIT(ImportLyricsAtChannelNotes)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT

	check_chan[0] = &m_check_chan1;
	check_chan[1] = &m_check_chan2;
	check_chan[2] = &m_check_chan3;
	check_chan[3] = &m_check_chan4;
	check_chan[4] = &m_check_chan5;
	check_chan[5] = &m_check_chan6;
	check_chan[6] = &m_check_chan7;
	check_chan[7] = &m_check_chan8;
	check_chan[8] = &m_check_chan9;
	check_chan[9] = &m_check_chan10;
	check_chan[10] = &m_check_chan11;
	check_chan[11] = &m_check_chan12;
	check_chan[12] = &m_check_chan13;
	check_chan[13] = &m_check_chan14;
	check_chan[14] = &m_check_chan15;
	check_chan[15] = &m_check_chan16;

	idc_type[0] = IDC_VOICE1;
	idc_type[1] = IDC_VOICE2;
	idc_type[2] = IDC_VOICE3;
	idc_type[3] = IDC_VOICE4;
	idc_type[4] = IDC_VOICE5;
	idc_type[5] = IDC_VOICE6;
	idc_type[6] = IDC_VOICE7;
	idc_type[7] = IDC_VOICE8;
	idc_type[8] = IDC_VOICE9;
	idc_type[9] = IDC_VOICE10;
	idc_type[10] = IDC_VOICE11;
	idc_type[11] = IDC_VOICE12;
	idc_type[12] = IDC_VOICE13;
	idc_type[13] = IDC_VOICE14;
	idc_type[14] = IDC_VOICE15;
	idc_type[15] = IDC_VOICE16;

	lyricfile = "";
}


void ImportLyricsAtChannelNotes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ImportLyricsAtChannelNotes)
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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ImportLyricsAtChannelNotes, CDialog)
	//{{AFX_MSG_MAP(ImportLyricsAtChannelNotes)
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
	ON_BN_CLICKED(IDC_OPEN_LYRIC_FILE, OnOpenLyricFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten ImportLyricsAtChannelNotes 

void ImportLyricsAtChannelNotes::OnOK() 
{
	int i;
	selected_chan = -1;
	
	for (i=0; i<16; i++)
	{
		if (check_chan[i]->GetCheck()==1)
		{
			selected_chan = i;
			break;
		}
	}
	if (selected_chan==-1)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SELECT_CHANNEL),NULL,MB_OK|MB_TASKMODAL);
		return;
	}

	if (lyricfile=="")
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_OPEN_LYRICFILE),NULL,MB_OK|MB_TASKMODAL);
		return;
	}

	EndDialog(1);  // 0: cancelled, 1: OK
}

void ImportLyricsAtChannelNotes::OnCancel() 
{
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	
	EndDialog(0);  // 0: cancelled, 1: OK
}

BOOL ImportLyricsAtChannelNotes::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int i;
	for (i=0; i<16; i++)
	{

		if (((hpmfi->mute)[i])||(!(hpmfi->mlv_list)[i].melody))
		{
			check_chan[i]->SetCheck(0);
			check_chan[i]->EnableWindow(false);
		}
		else
		{
			SetDlgItemText(idc_type[i],(hpmfi->patchname)[i]);
		}
	}

	



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void ImportLyricsAtChannelNotes::CheckChan(int chan)
{
	int i;

	if (check_chan[chan]->GetCheck()==1)
	{
		for (i=0; i<16; i++)
		{
			if (i==chan) continue;
			check_chan[i]->SetCheck(0);
		}
	}
}

void ImportLyricsAtChannelNotes::OnCheckChan1() 
{
	CheckChan(0);	
}

void ImportLyricsAtChannelNotes::OnCheckChan2() 
{
	CheckChan(1);	
}

void ImportLyricsAtChannelNotes::OnCheckChan3() 
{
	CheckChan(2);	
}

void ImportLyricsAtChannelNotes::OnCheckChan4() 
{
	CheckChan(3);	
}

void ImportLyricsAtChannelNotes::OnCheckChan5() 
{
	CheckChan(4);	
}

void ImportLyricsAtChannelNotes::OnCheckChan6() 
{
	CheckChan(5);	
}

void ImportLyricsAtChannelNotes::OnCheckChan7() 
{
	CheckChan(6);	
}

void ImportLyricsAtChannelNotes::OnCheckChan8() 
{
	CheckChan(7);	
}

void ImportLyricsAtChannelNotes::OnCheckChan9() 
{
	CheckChan(8);	
}

void ImportLyricsAtChannelNotes::OnCheckChan10() 
{
	CheckChan(9);	
}

void ImportLyricsAtChannelNotes::OnCheckChan11() 
{
	CheckChan(10);	
}

void ImportLyricsAtChannelNotes::OnCheckChan12() 
{
	CheckChan(11);	
}

void ImportLyricsAtChannelNotes::OnCheckChan13() 
{
	CheckChan(12);	
}

void ImportLyricsAtChannelNotes::OnCheckChan14() 
{
	CheckChan(13);	
}

void ImportLyricsAtChannelNotes::OnCheckChan15() 
{
	CheckChan(14);	
}

void ImportLyricsAtChannelNotes::OnCheckChan16() 
{
	CheckChan(15);	
}

void ImportLyricsAtChannelNotes::OnOpenLyricFile() 
{
	char BASED_CODE szFilter[] = 
		"Lyric-File (*.txt)|*.txt||";

	CFileDialog openfile_dlg(TRUE,
						  "txt",
						  NULL,
						  OFN_FILEMUSTEXIST,
						  szFilter,
						  NULL);

	int return_value = openfile_dlg.DoModal();
	if (return_value == IDOK)
	{
		lyricfile = openfile_dlg.m_ofn.lpstrFile;
	}
	else 
	{
		lyricfile = "";
	}
}
