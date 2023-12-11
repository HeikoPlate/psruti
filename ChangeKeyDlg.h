#if !defined(AFX_CHANGEKEYDLG_H__B7550394_410A_46C8_82C6_5D71FAFE361F__INCLUDED_)
#define AFX_CHANGEKEYDLG_H__B7550394_410A_46C8_82C6_5D71FAFE361F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangeKeyDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CChangeKeyDlg 

class CChangeKeyDlg : public CDialog
{
// Konstruktion
public:
	CChangeKeyDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CChangeKeyDlg)
	enum { IDD = IDD_CHANGE_KEY };
	CComboBox	m_majminlist;
	CComboBox	m_keylist;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CChangeKeyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung

public:
	HPMF_Interface * hpmfi;
	CString init_key;
	CString init_type;
	CString key, new_key;

private:
	static const CString keylistelement[15];
	static const CString majminlistelement[2];
	CString computed_key;

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CChangeKeyDlg)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_CHANGEKEYDLG_H__B7550394_410A_46C8_82C6_5D71FAFE361F__INCLUDED_
