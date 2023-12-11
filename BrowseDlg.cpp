// BrowseDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "BrowseDlg.h"
#include <mbstring.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld BrowseDlg 


BrowseDlg::BrowseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(BrowseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(BrowseDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	bank_name[0] = 0;
	bank_no = -1;
	voice_name[0] = 0;
	voice_no = -1;
	bank_voice_list = NULL;
	bank_voice_list_len = 0;
	search_string[0] = 0;
	browse_list_index = LB_ERR;
}


void BrowseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BrowseDlg)
	DDX_Control(pDX, IDC_SEARCH_STRING, m_search_string);
	DDX_Control(pDX, IDC_BROWSE_LIST, m_browse_list);
	DDX_Control(pDX, IDOK, m_ok);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BrowseDlg, CDialog)
	//{{AFX_MSG_MAP(BrowseDlg)
	ON_LBN_SELCHANGE(IDC_BROWSE_LIST, OnSelchangeBrowseList)
	ON_EN_UPDATE(IDC_SEARCH_STRING, OnUpdateSearchString)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten BrowseDlg 

void BrowseDlg::OnCancel() 
{
	// call hpmfi to delete list!
	EndDialog(0);
}

void BrowseDlg::OnOK() 
{
	strcpy(bank_name,(bank_voice_list[browse_list_index]).bank_name);
	bank_no = (bank_voice_list[browse_list_index]).bank_number;
	strcpy(voice_name,(bank_voice_list[browse_list_index]).voice_name);
	voice_no = (bank_voice_list[browse_list_index]).voice_number;

	hpmfi->delete_bank_voice_list(&bank_voice_list,&bank_voice_list_len);
	EndDialog(1);
}

BOOL BrowseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	hpmfi->eval_voice_browse(search_string,&bank_voice_list,&bank_voice_list_len);

	CString window_text;
	window_text.Format("%s %i",
		GlobalUtilities::get_resource_string(IDS_BROWSE_VOICE_FOR_CHANNEL),chan+1);
	SetWindowText(window_text);

	DisplayVoices();
	m_ok.EnableWindow(FALSE);
	
	return TRUE; 
}

void BrowseDlg::DisplayVoices()
{
	m_browse_list.ResetContent();
	int i, k;
	for (i=0;i<bank_voice_list_len;i++)
	{
		char str[30]; // before 26
		str[29] = 0;  // before 25	
		char *voice_name = (bank_voice_list[i]).voice_name;

		for (k=0; k<29; k++)
		{
			str[k] = voice_name[k];
			if (str[k] == '(')
			{
				str[k] = 0;
				break;
			}
			if (str[k] == 0)
			{
				break;
			}
		}


		for (k=0; k<(int)strlen(str); k++) 
		{
			if (str[k]=='}')
			{
				str[k+1] = 0;
				break;
			}
			if (str[k]==0)
			{
				break;
			}
		}

//		char str[65];
//		strcpy(str,(bank_voice_list[i]).voice_name);

		m_browse_list.AddString(str);
	}
}

void BrowseDlg::OnSelchangeBrowseList() 
{
	browse_list_index = m_browse_list.GetCurSel();
	if (browse_list_index == LB_ERR) return;
	m_ok.EnableWindow(TRUE);
}

void BrowseDlg::OnUpdateSearchString() 
{
	char str[65];
	char *pdest;
	bool success;
	int len = m_search_string.GetLine(0,str,64);
	str[len] = 0;
    pdest = strstr(str,search_string);
//  success = search_string[0]==0?true:(pdest==str);
    success = search_string[0]==0?true:(pdest!=NULL);

	strcpy(search_string,str);
	if(!success)
	{
		hpmfi->delete_bank_voice_list(&bank_voice_list,&bank_voice_list_len);
	}

	hpmfi->eval_voice_browse(search_string,&bank_voice_list,&bank_voice_list_len);
	DisplayVoices();
	m_ok.EnableWindow(FALSE);
}
