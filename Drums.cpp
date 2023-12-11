// Drums.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Drums.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Drums 


Drums::Drums(CWnd* pParent /*=NULL*/)
	: CDialog(Drums::IDD, pParent)
{
	//{{AFX_DATA_INIT(Drums)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	m_pToolTip = NULL;

}


void Drums::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Drums)
	DDX_Control(pDX, IDC_CHANGE_DRUMS_DIALOG, m_drums_dialog);
	DDX_Control(pDX, IDC_CHANGE_DRUMS_BATCH, m_drums_batch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Drums, CDialog)
	//{{AFX_MSG_MAP(Drums)
	ON_BN_CLICKED(IDC_CHANGE_DRUMS_DIALOG, OnChangeDrumsDialog)
	ON_BN_CLICKED(IDC_CHANGE_DRUMS_BATCH, OnChangeDrumsBatch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Drums 


BOOL Drums::PreTranslateMessage(MSG* pMSG)
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



void Drums::OnChangeDrumsBatch() 
{
	EndDialog(0);
}

void Drums::OnChangeDrumsDialog() 
{
	EndDialog(1);
}

void Drums::OnCancel() 
{
	EndDialog(-1);
}

BOOL Drums::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Tool Tips
	m_pToolTip = new CToolTipCtrl;
	m_pToolTip->Create(this);
	m_pToolTip->SetDelayTime(TTDT_AUTOPOP,4000);
	m_pToolTip->SetMaxTipWidth(200);

	m_pToolTip->AddTool(&m_drums_dialog,GlobalUtilities::get_resource_string(IDS_DRUMS_DIALOG));
	m_pToolTip->AddTool(&m_drums_batch,GlobalUtilities::get_resource_string(IDS_DRUMS_BATCH));

	m_pToolTip->Activate(true);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
