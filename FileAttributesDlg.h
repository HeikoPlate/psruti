#if !defined(AFX_FILEATTRIBUTESDLG_H__C6827B77_132E_467B_99B2_3C29A9C29BD6__INCLUDED_)
#define AFX_FILEATTRIBUTESDLG_H__C6827B77_132E_467B_99B2_3C29A9C29BD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileAttributesDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld FileAttributesDlg 

class FileAttributesDlg : public CDialog
{
// Konstruktion
public:
	FileAttributesDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(FileAttributesDlg)
	enum { IDD = IDD_FILE_ATTRIBUTES };
	CEdit	m_text;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(FileAttributesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(FileAttributesDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString sourcefile;
    HPMF_Interface *hpmfi;
	bool with_additional_chunks;
	int original_ppqn;
	CString songname;
	CString copyright;
	CString format;
	CString sub_format;
	CString takt;
	double tempo;
	CString key;
	bool lyrics;
	bool chords;
	CString vh_channels;
	bool count_in;
	int no_measures;
	int duration;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_FILEATTRIBUTESDLG_H__C6827B77_132E_467B_99B2_3C29A9C29BD6__INCLUDED_
