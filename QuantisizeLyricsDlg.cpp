// QuantisizeLyricsDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "QuantisizeLyricsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld QuantisizeLyricsDlg 


QuantisizeLyricsDlg::QuantisizeLyricsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(QuantisizeLyricsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(QuantisizeLyricsDlg)
	//}}AFX_DATA_INIT
}


void QuantisizeLyricsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(QuantisizeLyricsDlg)
	DDX_Control(pDX, IDC_EIGHTH_TRIOLE_QUANTISIZE, m_eighth_triole_quantisize);
	DDX_Control(pDX, IDC_LYRICS_AT_CHORDS, m_lyrics_at_chords);
	DDX_Control(pDX, IDC_SIXTEENTH_QUANTISIZIE, m_sixteenth_quantisize);
	DDX_Control(pDX, IDC_QUARTER_QUANTISIZE, m_quarter_quantisize);
	DDX_Control(pDX, IDC_EIGHTH_QUANTISIZE, m_eighth_quantisize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(QuantisizeLyricsDlg, CDialog)
	//{{AFX_MSG_MAP(QuantisizeLyricsDlg)
	ON_BN_CLICKED(IDC_QUARTER_QUANTISIZE, OnQuarterQuantisize)
	ON_BN_CLICKED(IDC_EIGHTH_QUANTISIZE, OnEighthQuantisize)
	ON_BN_CLICKED(IDC_SIXTEENTH_QUANTISIZIE, OnSixteenthQuantisize)
	ON_BN_CLICKED(IDC_LYRICS_AT_CHORDS, OnLyricsAtChords)
	ON_BN_CLICKED(IDC_EIGHTH_TRIOLE_QUANTISIZE, OnEighthTrioleQuantisize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten QuantisizeLyricsDlg 

void QuantisizeLyricsDlg::OnQuarterQuantisize() 
{
	resolution = ppqn;	
	m_quarter_quantisize.SetState(TRUE);
	m_eighth_quantisize.SetState(FALSE);
	m_eighth_triole_quantisize.SetState(FALSE);
	m_sixteenth_quantisize.SetState(FALSE);
}

void QuantisizeLyricsDlg::OnEighthQuantisize() 
{
	resolution = ppqn/2;
	m_quarter_quantisize.SetState(FALSE);
	m_eighth_quantisize.SetState(TRUE);
	m_eighth_triole_quantisize.SetState(FALSE);
	m_sixteenth_quantisize.SetState(FALSE);
}

void QuantisizeLyricsDlg::OnEighthTrioleQuantisize() 
{
	resolution = ppqn/3;	
	m_quarter_quantisize.SetState(FALSE);
	m_eighth_quantisize.SetState(FALSE);
	m_eighth_triole_quantisize.SetState(TRUE);
	m_sixteenth_quantisize.SetState(FALSE);
}


void QuantisizeLyricsDlg::OnSixteenthQuantisize() 
{
	resolution = ppqn/4;	
	m_quarter_quantisize.SetState(FALSE);
	m_eighth_quantisize.SetState(FALSE);
	m_eighth_triole_quantisize.SetState(FALSE);
	m_sixteenth_quantisize.SetState(TRUE);
}

void QuantisizeLyricsDlg::OnLyricsAtChords() 
{
	is_lyrics_at_chords = (m_lyrics_at_chords.GetCheck() == 1);
}

void QuantisizeLyricsDlg::OnOK() 
{
	CDialog::OnOK();
}

void QuantisizeLyricsDlg::OnCancel() 
{
	CDialog::OnCancel();
}

BOOL QuantisizeLyricsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON hIcon;
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON12);
	m_quarter_quantisize.SetIcon(hIcon);	
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON13);
	m_eighth_quantisize.SetIcon(hIcon);	
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON18);
	m_sixteenth_quantisize.SetIcon(hIcon);
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON19);
	m_eighth_triole_quantisize.SetIcon(hIcon);
	
	m_sixteenth_quantisize.SetState(TRUE);
	resolution = ppqn/4; 
	is_lyrics_at_chords = false;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

