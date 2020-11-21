// RevoicingMethodDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "RevoicingMethodDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld RevoicingMethodDlg 


RevoicingMethodDlg::RevoicingMethodDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RevoicingMethodDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(RevoicingMethodDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void RevoicingMethodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RevoicingMethodDlg)
	DDX_Control(pDX, IDC_REVOICE_FILE, m_revoicefile_revoicing);
	DDX_Control(pDX, IDC_VOICEFILE_REVOICING, m_voicefile_revoicing);
	DDX_Control(pDX, IDOK, m_standard_revoicing);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RevoicingMethodDlg, CDialog)
	//{{AFX_MSG_MAP(RevoicingMethodDlg)
	ON_BN_CLICKED(IDC_VOICEFILE_REVOICING, OnVoicefileRevoicing)
	ON_BN_CLICKED(IDC_REVOICE_FILE, OnRevoiceFile)
	ON_BN_CLICKED(IDOK, OnStandardRevoicing)
	ON_BN_CLICKED(IDC_MSB_LSB_BANK, OnMsbLsbBank)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipDlg Nachrichten-Handler

BOOL RevoicingMethodDlg::PreTranslateMessage(MSG* pMSG)
{
	m_pToolTip.RelayEvent(pMSG);
	return CDialog::PreTranslateMessage(pMSG);
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten RevoicingMethodDlg 

void RevoicingMethodDlg::OnStandardRevoicing() 
{
	EndDialog(0);
}

void RevoicingMethodDlg::OnVoicefileRevoicing() 
{
	EndDialog(1);
}

void RevoicingMethodDlg::OnRevoiceFile() 
{
	EndDialog(10);
}

void RevoicingMethodDlg::OnCancel() 
{
	EndDialog(-1);
}


BOOL RevoicingMethodDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_pToolTip.Create(this);
	m_pToolTip.SetDelayTime(TTDT_AUTOPOP,4000);
	m_pToolTip.SetMaxTipWidth(200);

	m_pToolTip.AddTool(&m_standard_revoicing,GlobalUtilities::get_resource_string(IDS_STANDARD_REVOICING_TOOLTIP));
	m_pToolTip.AddTool(&m_voicefile_revoicing,GlobalUtilities::get_resource_string(IDS_VOICEFILE_REVOICING_TOOLTIP));
	m_pToolTip.AddTool(&m_revoicefile_revoicing,GlobalUtilities::get_resource_string(IDS_REVOICEFILE_REVOICING_TOOLTIP));

	m_pToolTip.Activate(true);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void RevoicingMethodDlg::OnMsbLsbBank() 
{
	EndDialog(11);
}
