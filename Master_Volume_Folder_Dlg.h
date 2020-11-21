#if !defined(AFX_MASTER_VOLUME_FOLDER_DLG_H__343FB7C7_D4D4_4034_888D_A647A613CE90__INCLUDED_)
#define AFX_MASTER_VOLUME_FOLDER_DLG_H__343FB7C7_D4D4_4034_888D_A647A613CE90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Master_Volume_Folder_Dlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Master_Volume_Folder_Dlg 

class Master_Volume_Folder_Dlg : public CDialog
{
// Konstruktion
public:
	Master_Volume_Folder_Dlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Master_Volume_Folder_Dlg)
	enum { IDD = IDD_MASTER_VOLUME_FOLDER_DLG };
	CEdit	m_master_volume_edit;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Master_Volume_Folder_Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Master_Volume_Folder_Dlg)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnChangeMasterVolumEdit();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public: 
	int get_value();
private:
	int value;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_MASTER_VOLUME_FOLDER_DLG_H__343FB7C7_D4D4_4034_888D_A647A613CE90__INCLUDED_
