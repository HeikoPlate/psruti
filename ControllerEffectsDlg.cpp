// ControllerEffectsDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "ControllerEffectsDlg.h"
#include "Controller_Dlg.h"
#include "EffectFilterDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CControllerEffectsDlg 


CControllerEffectsDlg::CControllerEffectsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CControllerEffectsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControllerEffectsDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	source_changed = false;
}


void CControllerEffectsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControllerEffectsDlg)
	DDX_Control(pDX, IDC_EFFECTS, m_effects);
	DDX_Control(pDX, IDC_CONTROLLER, m_controller);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CControllerEffectsDlg, CDialog)
	//{{AFX_MSG_MAP(CControllerEffectsDlg)
	ON_BN_CLICKED(IDC_CONTROLLER, OnSelectController)
	ON_BN_CLICKED(IDC_EFFECTS, OnSelectEffects)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipDlg Nachrichten-Handler


BOOL CControllerEffectsDlg::PreTranslateMessage(MSG* pMSG)
{
	m_pToolTip.RelayEvent(pMSG);
	return CDialog::PreTranslateMessage(pMSG);
}


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CControllerEffectsDlg 

void CControllerEffectsDlg::OnSelectController() 
{
	Controller_Dlg dlg;
	dlg.hpmfi = hpmfi;
	dlg.hCursorWait = hCursorWait;
	dlg.hCursorOld = hCursorOld;
	source_changed = (dlg.DoModal()!=0);
	OnOK();
}

void CControllerEffectsDlg::OnSelectEffects() 
{
	EffectFilterDlg dlg;
	dlg.hpmfi = hpmfi;
	dlg.hCursorWait = hCursorWait;
	dlg.hCursorOld = hCursorOld;
	source_changed = (dlg.DoModal()!=0);
	OnOK();
}

void CControllerEffectsDlg::OnOK() 
{
	EndDialog(source_changed?1:0);
}

BOOL CControllerEffectsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Tool Tips
	m_pToolTip.Create(this);
	m_pToolTip.SetDelayTime(TTDT_AUTOPOP,4000);
	m_pToolTip.SetMaxTipWidth(200);

	m_pToolTip.AddTool(&m_controller,GlobalUtilities::get_resource_string(IDS_CONTROLLER));
	m_pToolTip.AddTool(&m_effects,GlobalUtilities::get_resource_string(IDS_EFFECTS));
	
	m_pToolTip.Activate(true);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
