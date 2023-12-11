// Tempo_Dlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Tempo_Dlg.h"
#include "psrutiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Tempo_Dlg 


Tempo_Dlg::Tempo_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Tempo_Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Tempo_Dlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void Tempo_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Tempo_Dlg)
	DDX_Control(pDX, IDC_EDIT_TEMPO, m_edit_tempo);
	DDX_Control(pDX, IDC_EDIT_PERCENT, m_edit_percent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Tempo_Dlg, CDialog)
	//{{AFX_MSG_MAP(Tempo_Dlg)
	ON_BN_CLICKED(IDC_TAKE_IT, OnTakeIt)
	ON_EN_KILLFOCUS(IDC_EDIT_TEMPO, OnKillfocusEditTempo)
	ON_EN_KILLFOCUS(IDC_EDIT_PERCENT, OnKillfocusEditPercent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Tempo_Dlg 

BOOL Tempo_Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_edit_tempo.SetLimitText(6);
	m_edit_percent.SetLimitText(3);

	edit_max_tempo_val = max_tempo==-1.0?120.0:max_tempo;
	
	SetDlgItemText(IDC_EDIT_PERCENT,"100");
	CString tempo_str;
	tempo_str.Format("%4.2f",max_tempo);
	SetDlgItemText(IDC_EDIT_TEMPO,tempo_str);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

double Tempo_Dlg::get_tempo()
{
	return edit_max_tempo_val;
}

void Tempo_Dlg::OnCancel() 
{
	EndDialog(0);
}

void Tempo_Dlg::OnOK() 
{
	char tempo_str[10];
	int l = m_edit_tempo.LineLength();
	int len = m_edit_tempo.GetLine(0, tempo_str,l);
	tempo_str[len] = 0;
	edit_max_tempo_val = GlobalUtilities::compute_double_number(tempo_str,l);
	if (edit_max_tempo_val<5.0 || edit_max_tempo_val>500.0)
	{ // Syntax error, use 5 or 500
		edit_max_tempo_val = (edit_max_tempo_val<5)?0.0:500.0;
	}
	EndDialog(1);
}

void Tempo_Dlg::OnTakeIt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
}

void Tempo_Dlg::OnKillfocusEditTempo() 
{
	char tempo_str[10];
	double tempo_number;
	int l = m_edit_tempo.LineLength();
	int len =  m_edit_tempo.GetLine(0, tempo_str,l);
	tempo_str[len] = 0;
	tempo_number = GlobalUtilities::compute_double_number(tempo_str,l);;
	if (tempo_number<5.0 || tempo_number>500.0)
	{ // Syntax error, use 0 or 127
		tempo_number = tempo_number<5.0?5.0:500.0;
	}
	CString v;
	v.Format("%4.2f",tempo_number);
	SetDlgItemText(IDC_EDIT_TEMPO,v);
}

void Tempo_Dlg::OnKillfocusEditPercent() 
{
	char tempo_str[10];
	double original_value;
	double new_value;
	int percent;
	CString v;

	int l = m_edit_percent.LineLength();
	int len = m_edit_percent.GetLine(0, tempo_str,l);
	tempo_str[len] = 0;
	percent = GlobalUtilities::compute_number(tempo_str,l);;
	if (percent < 0)
	{
		percent = 100;
	}
	v.Format("%i",percent);
	SetDlgItemText(IDC_EDIT_PERCENT,v);
	if (percent == 100) return;

	l = m_edit_tempo.LineLength();
	len = m_edit_tempo.GetLine(0, tempo_str,l);
	tempo_str[len] = 0;
	original_value = GlobalUtilities::compute_double_number(tempo_str,l);;
	new_value = (original_value*(double)percent)/100.;

	if (new_value<5.0 || new_value>500.0)
	{ // Syntax error, use 0 or 127
		new_value = (new_value<5.0)?5.0:500.0;
	}
	v.Format("%4.2f",new_value);
	SetDlgItemText(IDC_EDIT_TEMPO,v);
	
	// initialize percent
	SetDlgItemText(IDC_EDIT_PERCENT,"100");
}
