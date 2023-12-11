/////////////////////////////////////////////////////////////////////////////
// Dialogfeld QuantisizeChords 

#include "stdafx.h"
#include "psruti.h"
#include "QuantisizeChords.h"
#include "HP_midifile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


QuantisizeChords::QuantisizeChords(CWnd* pParent /*=NULL*/)
	: CDialog(QuantisizeChords::IDD, pParent)
{
	//{{AFX_DATA_INIT(QuantisizeChords)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void QuantisizeChords::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(QuantisizeChords)
	DDX_Control(pDX, IDC_BEAT_1_3_QUANTISIZE, m_beat_1_3_quantisize);
	DDX_Control(pDX, IDC_BEAT_ALL_QUANTISIZE, m_beat_all_quantisize);
	DDX_Control(pDX, IDC_BEAT1_QUANTISIZE, m_beat1_quantisize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(QuantisizeChords, CDialog)
	//{{AFX_MSG_MAP(QuantisizeChords)
	ON_BN_CLICKED(IDC_BEAT1_QUANTISIZE, OnBeat1Quantisize)
	ON_BN_CLICKED(IDC_BEAT_ALL_QUANTISIZE, OnBeatAllQuantisize)
	ON_BN_CLICKED(IDC_BEAT_1_3_QUANTISIZE, OnBeat13Quantisize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten QuantisizeChords 

void QuantisizeChords::OnOK() 
{
	CDialog::OnOK();
}

BOOL QuantisizeChords::OnInitDialog() 
{
	CDialog::OnInitDialog();

	HICON hIcon;
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON14);
	m_beat1_quantisize.SetIcon(hIcon);	
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON15);
	m_beat_1_3_quantisize.SetIcon(hIcon);	
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON16);
	m_beat_all_quantisize.SetIcon(hIcon);	

	m_beat_1_3_quantisize.SetState(TRUE);		
	beat_resolution = BEAT_RESOLUTION_13;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

#define BEAT_RESOLUTION_1	1
#define BEAT_RESOLUTION_13	2
#define BEAT_RESOLUTION_ALL	3

void QuantisizeChords::OnBeat1Quantisize() 
{
	beat_resolution = BEAT_RESOLUTION_1;

	m_beat1_quantisize.SetState(TRUE);
	m_beat_1_3_quantisize.SetState(FALSE);
	m_beat_all_quantisize.SetState(FALSE);
}

void QuantisizeChords::OnBeat13Quantisize() 
{
	beat_resolution = BEAT_RESOLUTION_13;

	m_beat1_quantisize.SetState(FALSE);
	m_beat_1_3_quantisize.SetState(TRUE);
	m_beat_all_quantisize.SetState(FALSE);
}

void QuantisizeChords::OnBeatAllQuantisize() 
{
	beat_resolution = BEAT_RESOLUTION_ALL;

	m_beat1_quantisize.SetState(FALSE);
	m_beat_1_3_quantisize.SetState(FALSE);
	m_beat_all_quantisize.SetState(TRUE);
}

int QuantisizeChords::get_beat_resolution()
{
	return beat_resolution;
}

