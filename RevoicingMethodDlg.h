#if !defined(AFX_REVOICINGMETHODDLG_H__1AB6F1B2_0335_47B2_AAB5_FC75100E3629__INCLUDED_)
#define AFX_REVOICINGMETHODDLG_H__1AB6F1B2_0335_47B2_AAB5_FC75100E3629__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RevoicingMethodDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld RevoicingMethodDlg 

class RevoicingMethodDlg : public CDialog
{
// Konstruktion
public:
	RevoicingMethodDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(RevoicingMethodDlg)
	enum { IDD = IDD_FILE_REVOICING };
	CButton	m_revoicefile_revoicing;
	CButton	m_voicefile_revoicing;
	CButton	m_standard_revoicing;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(RevoicingMethodDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(RevoicingMethodDlg)
	afx_msg void OnVoicefileRevoicing();
	afx_msg void OnRevoiceFile();
	afx_msg void OnStandardRevoicing();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnMsbLsbBank();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CToolTipCtrl m_pToolTip;
	virtual BOOL PreTranslateMessage(MSG* pMSG);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_REVOICINGMETHODDLG_H__1AB6F1B2_0335_47B2_AAB5_FC75100E3629__INCLUDED_
