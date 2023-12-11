// InsdefDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "InsdefDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld InsdefDlg 


InsdefDlg::InsdefDlg(CWnd* pParent /*=NULL*/)
	: CDialog(InsdefDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(InsdefDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	insdef = "";
}


void InsdefDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InsdefDlg)
	DDX_Control(pDX, IDC_INSDEFCOMBOBOX, m_insdefcombobox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InsdefDlg, CDialog)
	//{{AFX_MSG_MAP(InsdefDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten InsdefDlg 

void InsdefDlg::OnOK() 
{
	SetCursor(hCursorWait);	
	int nIndex = m_insdefcombobox.GetCurSel();
	int nCount = m_insdefcombobox.GetCount();

	SetCursor(hCursorOld);	

	if ((nIndex==LB_ERR) || (nIndex>=nCount))
	{
		OnCancel();
	}
	else
	{
		if (hpmfi != NULL)
		{
			hpmfi->set_insdef(nIndex);
		}
		else
		{
			HP_CWInsSetDef(local_mf,nIndex);
		}
		insdef = def_list[nIndex].def_name;
		HP_Delete(def_list);
		CDialog::OnOK();
	}
}

void InsdefDlg::OnCancel() 
{
	HP_Delete(def_list);
	CDialog::OnCancel();
}

BOOL InsdefDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetCursor(hCursorWait);	
	int i;
	int no_defs;
	bool result;
	if (hpmfi != NULL)
	{
		result = hpmfi->get_insdefs(&def_list, &no_defs);
	}
	else
	{
		UINT result = HP_CWInsGetDefs(local_mf, &def_list, &no_defs);
		if (result!=HP_ERR_NONE)
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,HP_ErrText(result),NULL,MB_OK|MB_TASKMODAL);
			return false;
		}
	}

	for (i=0; i<no_defs; i++)
	{
		m_insdefcombobox.InsertString(i, def_list[i].def_name);
	}
	m_insdefcombobox.SetCurSel(0);

	SetCursor(hCursorOld);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
