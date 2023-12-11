// stdafx.h : Include-Datei f�r Standard-System-Include-Dateien,
//  oder projektspezifische Include-Dateien, die h�ufig benutzt, aber
//      in unregelm��igen Abst�nden ge�ndert werden.
//

#if !defined(AFX_STDAFX_H__F24E268C_C3E6_11D5_9348_0080AD7896CF__INCLUDED_)
#define AFX_STDAFX_H__F24E268C_C3E6_11D5_9348_0080AD7896CF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Selten verwendete Teile der Windows-Header nicht einbinden
#define IDNEWSTART   50
#include <afxwin.h>         // MFC-Kern- und -Standardkomponenten
#include <afxext.h>         // MFC-Erweiterungen
#include <afxdisp.h>        // MFC OLE-Automatisierungsklassen
#include <afxdtctl.h>		// MFC-Unterst�tzung f�r allgemeine Steuerelemente von Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC-Unterst�tzung f�r g�ngige Windows-Steuerelemente
#include "Log.h"
#include <time.h>


#endif // _AFX_NO_AFXCMN_SUPPORT

//  #define HP_LOG // must be set if logging wanted

//  Dieses Makro ist identisch mit IMPLEMENT_OLECREATE, au�er dass es den Wert TRUE
//  f�r den Parameter bMultiInstance des Konstruktors COleObjectFactory �bergibt.
//  Wir wollen f�r jedes Proxy-Objekt der OLE-Automatisierung, das von
//  Automatisierungs-Controllern angefordert wird, eine eigene Instanz dieser Anwendung starten.
#ifndef IMPLEMENT_OLECREATE2
#define IMPLEMENT_OLECREATE2(class_name, external_name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
	AFX_DATADEF COleObjectFactory class_name::factory(class_name::guid, \
		RUNTIME_CLASS(class_name), TRUE, _T(external_name)); \
	const AFX_DATADEF GUID class_name::guid = \
		{ l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } };
#endif // IMPLEMENT_OLECREATE2

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_STDAFX_H__F24E268C_C3E6_11D5_9348_0080AD7896CF__INCLUDED_)
