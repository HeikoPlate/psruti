#if !defined(AFX_DRUMVOICESTEMPLATEDLG_H__DF4E3564_1972_4C71_8CBA_F362F9BE91D0__INCLUDED_)
#define AFX_DRUMVOICESTEMPLATEDLG_H__DF4E3564_1972_4C71_8CBA_F362F9BE91D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrumVoicesTemplateDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DrumVoicesTemplateDlg 

class DrumVoicesTemplateDlg : public CDialog
{
// Konstruktion
public:
	DrumVoicesTemplateDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(DrumVoicesTemplateDlg)
	enum { IDD = IDD_DRUM_TEMPLATE };
		// HINWEIS: Der Klassen-Assistent f�gt hier Datenelemente ein
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(DrumVoicesTemplateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(DrumVoicesTemplateDlg)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DRUMVOICESTEMPLATEDLG_H__DF4E3564_1972_4C71_8CBA_F362F9BE91D0__INCLUDED_
