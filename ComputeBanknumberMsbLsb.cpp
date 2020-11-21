// ComputeBanknumberMsbLsb.cpp : implementation file
//

#include "stdafx.h"
#include "psruti.h"
#include "ComputeBanknumberMsbLsb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComputeBanknumberMsbLsb dialog


CComputeBanknumberMsbLsb::CComputeBanknumberMsbLsb(CWnd* pParent /*=NULL*/)
	: CDialog(CComputeBanknumberMsbLsb::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComputeBanknumberMsbLsb)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CComputeBanknumberMsbLsb::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComputeBanknumberMsbLsb)
	DDX_Control(pDX, IDC_EDIT_BANKNUMBER, m_banknumber);
	DDX_Control(pDX, IDC_EDIT_LSB, m_lsb);
	DDX_Control(pDX, IDC_EDIT_MSB, m_msb);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComputeBanknumberMsbLsb, CDialog)
	//{{AFX_MSG_MAP(CComputeBanknumberMsbLsb)
	ON_BN_CLICKED(IDC_CALCULATE, OnCalculate)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComputeBanknumberMsbLsb message handlers

BOOL CComputeBanknumberMsbLsb::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetDlgItemInt(IDC_EDIT_MSB,0,FALSE);
	SetDlgItemInt(IDC_EDIT_LSB,0,FALSE);
	SetDlgItemInt(IDC_EDIT_BANKNUMBER,0,FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CComputeBanknumberMsbLsb::OnCalculate() 
{
	int bankno = GetDlgItemInt(IDC_EDIT_BANKNUMBER);
	int msb = GetDlgItemInt(IDC_EDIT_MSB);
	int lsb = GetDlgItemInt(IDC_EDIT_LSB);

	if (bankno < 0)
	{
		bankno=0;
		SetDlgItemInt(IDC_EDIT_BANKNUMBER,0,FALSE);
	}

	if (bankno > 16383)
	{
		bankno=16383;
		SetDlgItemInt(IDC_EDIT_BANKNUMBER,bankno,FALSE);
	}

	if (msb < 0)
	{	
		msb = 0;
		SetDlgItemInt(IDC_EDIT_MSB,msb,FALSE);
		
	}
	if (msb > 127)
	{
		msb = 127;
		SetDlgItemInt(IDC_EDIT_MSB,msb,FALSE);
	}
	if (lsb < 0)
	{	
		lsb = 0;
		SetDlgItemInt(IDC_EDIT_LSB,0,FALSE);
		
	}
	if (lsb > 127)
	{
		lsb = 127;
		SetDlgItemInt(IDC_EDIT_LSB,lsb,FALSE);
	}

	if ((bankno==0) &&((msb>0)||(lsb>0)))
	{
		bankno = 128*msb+lsb;
		SetDlgItemInt(IDC_EDIT_BANKNUMBER,bankno,FALSE);
		return;
	}
	if (bankno>0)
	{
		msb = bankno/128;
		SetDlgItemInt(IDC_EDIT_MSB,msb,FALSE);
		lsb = bankno%128;
		SetDlgItemInt(IDC_EDIT_LSB,lsb,FALSE);
	}
}

void CComputeBanknumberMsbLsb::OnClear() 
{
	SetDlgItemInt(IDC_EDIT_MSB,0,FALSE);
	SetDlgItemInt(IDC_EDIT_LSB,0,FALSE);
	SetDlgItemInt(IDC_EDIT_BANKNUMBER,0,FALSE);
}
