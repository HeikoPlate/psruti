// ChangeKeyDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "ChangeKeyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CChangeKeyDlg 

// Static const data

const CString CChangeKeyDlg::keylistelement[15] =
	{"Cb","C ","Db","D ","Eb","E ","F ","F#","Gb","G ","Ab","A ","Bb","B "};

const CString CChangeKeyDlg::majminlistelement[2] = {"maj","min"};


CChangeKeyDlg::CChangeKeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeKeyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeKeyDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CChangeKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeKeyDlg)
	DDX_Control(pDX, IDC_MAJMINLIST, m_majminlist);
	DDX_Control(pDX, IDC_KEYLIST, m_keylist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeKeyDlg, CDialog)
	//{{AFX_MSG_MAP(CChangeKeyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CChangeKeyDlg 

void CChangeKeyDlg::OnCancel() 
{
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	EndDialog(-1);
}

void CChangeKeyDlg::OnOK() 
{
	int key_note_indx = m_keylist.GetCurSel();
	int key_majmin_indx = m_majminlist.GetCurSel();

	if((key_note_indx==-1)||(key_majmin_indx==-1))
	{
		return;
	}

	CString defined_type =
		keylistelement[key_note_indx]+" "+majminlistelement[key_majmin_indx];

	if (defined_type != "** ***")
	{
		int i;

		key = "";
		for (i=0; i<defined_type.GetLength(); i++)
		{
			if (defined_type[i] == ' ') continue;
			if (i+2 < defined_type.GetLength())
			{
				if ((defined_type[i]  =='m') &&
					(defined_type[i+1]=='a') &&
					(defined_type[i+2]=='j'))
				{
					break;
				}
			}

			key += defined_type[i];
			if (i+2 < defined_type.GetLength())
			{
				if ((defined_type[i]  =='m') &&
					(defined_type[i+1]=='i') &&
					(defined_type[i+2]=='n'))
				{
					break;
				}
			}
		}

		new_key = key;
		CString tonart = GlobalUtilities::get_resource_string(IDS_KeySignature);
//		SetDlgItemText(IDC_NEW_KEY,tonart+new_key);
		// Change or insert new KeySignature in Destination
	}

	EndDialog(1);
}


BOOL CChangeKeyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i;
	int init_key_index = 1;
	int init_type_index = 0;

	computed_key = hpmfi->find_key();
	CString keynote = computed_key.Left(2);
	CString keymajmin = computed_key.Right(3);

	if (keynote!="**")
	{
		CString comp_key = keynote + "         " + keymajmin;
		SetDlgItemText(IDC_COMPUTED_KEY,comp_key);
	}

	// Initialize Lists for computed key

	// keynote-list
	m_keylist.InitStorage(15,3);
	for (i=0; i<15; i++)
	{
		m_keylist.AddString(keylistelement[i]);
		if (keylistelement[i]==init_key)
		{
			init_key_index = i;
		}
	}

	// key maj/min-list
	m_majminlist.InitStorage(2,4);
	for (i=0; i<2; i++)
	{
		m_majminlist.AddString(majminlistelement[i]);
		if (majminlistelement[i]==init_type)
		{
			init_type_index = i;
		}
	}

	// init position to old tonart and key

	m_keylist.SetCurSel(init_key_index);
	m_majminlist.SetCurSel(init_type_index);

	if ((keynote != "**")&&(keymajmin !="***"))
	{
		for (i=0; i<15; i++)
		{
			if (keylistelement[i]==keynote)
			{
				m_keylist.SetCurSel(i);
				break;
			}
		}
		for (i=0; i<2; i++)
		{
			if (majminlistelement[i]==keymajmin)
			{
				m_majminlist.SetCurSel(i);
				break;
			}
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}