#if !defined(AFX_MAINVOLUME_EXPRESSION_FOLDER_DLG_H__C18885BB_0EE8_411D_BAC8_75107EF18A13__INCLUDED_)
#define AFX_MAINVOLUME_EXPRESSION_FOLDER_DLG_H__C18885BB_0EE8_411D_BAC8_75107EF18A13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainVolume_Expression_Folder_Dlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld MainVolume_Expression_Folder_Dlg 

class MainVolume_Expression_Folder_Dlg : public CDialog
{
// Konstruktion
public:
	MainVolume_Expression_Folder_Dlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(MainVolume_Expression_Folder_Dlg)
	enum { IDD = IDD_MAINVOLUME_EXPRESSION_FOLDER_DLG };
	CButton	m_mainvolume_to_expression_check;
	CButton	m_expression_to_mainvolume_check;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(MainVolume_Expression_Folder_Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(MainVolume_Expression_Folder_Dlg)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnExpressionToMainvolumeCheck();
	afx_msg void OnMainvolumeToExpressionCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	bool get_mainvolume_to_expression();

private:
	bool mainvolume_to_expression_val;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_MAINVOLUME_EXPRESSION_FOLDER_DLG_H__C18885BB_0EE8_411D_BAC8_75107EF18A13__INCLUDED_
