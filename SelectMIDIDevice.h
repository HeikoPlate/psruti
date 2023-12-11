#if !defined(AFX_SELECTMIDIDEVICE_H__4AEA4D6B_2BD8_4846_AB8E_7DF6F1CEEE43__INCLUDED_)
#define AFX_SELECTMIDIDEVICE_H__4AEA4D6B_2BD8_4846_AB8E_7DF6F1CEEE43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectMIDIDevice.h : Header-Datei
//

#include "inifile.h"
#include "HP_midifile.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld SelectMIDIDevice 

class SelectMIDIDevice : public CDialog
{
// Konstruktion
public:
	SelectMIDIDevice(CWnd* pParent = NULL);   // Standardkonstruktor

	IniFile *p_inifile;


// Dialogfelddaten
	//{{AFX_DATA(SelectMIDIDevice)
	enum { IDD = IDD_SELECT_MIDI_DEVICE };
	CListBox	m_device_list;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(SelectMIDIDevice)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

private:

	HP_DEVICE *devices;
	int no_devices;
	int id_list[32];
	int id;
	int old_id;

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(SelectMIDIDevice)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SELECTMIDIDEVICE_H__4AEA4D6B_2BD8_4846_AB8E_7DF6F1CEEE43__INCLUDED_
