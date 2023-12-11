// psruti.h : Haupt-Header-Datei f�r die Anwendung PSRUTI
//

#if !defined(AFX_PSRMIDI_H__F24E2685_C3E6_11D5_9348_0080AD7896CF__INCLUDED_)
#define AFX_PSRMIDI_H__F24E2685_C3E6_11D5_9348_0080AD7896CF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole
#include "psrutiDlg.h"      // Dialog

/////////////////////////////////////////////////////////////////////////////
// CPsrmidiApp:
// Siehe psruti.cpp f�r die Implementierung dieser Klasse
//

class CPsrutiApp : public CWinApp
{
public:
	CPsrutiApp();

protected:

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CPsrutiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

private:

	CString language;


// Implementierung

	//{{AFX_MSG(CPsrutiApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
		afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_PSRMIDI_H__F24E2685_C3E6_11D5_9348_0080AD7896CF__INCLUDED_)
