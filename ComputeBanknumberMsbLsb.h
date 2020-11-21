#if !defined(AFX_COMPUTEBANKNUMBERMSBLSB_H__4C92F687_9017_4B12_9825_ABAF6CBD4D3D__INCLUDED_)
#define AFX_COMPUTEBANKNUMBERMSBLSB_H__4C92F687_9017_4B12_9825_ABAF6CBD4D3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComputeBanknumberMsbLsb.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComputeBanknumberMsbLsb dialog

class CComputeBanknumberMsbLsb : public CDialog
{
// Construction
public:
	CComputeBanknumberMsbLsb(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CComputeBanknumberMsbLsb)
	enum { IDD = IDD_COMPUTE_BANK_LSB_MSB };
	CEdit	m_banknumber;
	CEdit	m_lsb;
	CEdit	m_msb;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComputeBanknumberMsbLsb)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CComputeBanknumberMsbLsb)
	afx_msg void OnCalculate();
	afx_msg void OnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();


private:
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPUTEBANKNUMBERMSBLSB_H__4C92F687_9017_4B12_9825_ABAF6CBD4D3D__INCLUDED_)
