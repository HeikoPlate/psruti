#if !defined(AFX_VHCHANDLG_H__ABFA0616_88DD_46BC_AC26_A8541B620EE2__INCLUDED_)
#define AFX_VHCHANDLG_H__ABFA0616_88DD_46BC_AC26_A8541B620EE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VHChanDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld VHChanDlg 

class VHChanDlg : public CDialog
{
// Konstruktion
public:
	VHChanDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(VHChanDlg)
	enum { IDD = IDD_VH_CHANNEL_DLG };
	CListBox	m_vh_chan_list;
	CButton	m_delete_vocalharmony;
	CButton	m_select_vocoder_chan;
	CButton	m_lengthen_select;
	CButton	m_act_deact_select;
	CEdit	m_no_quarters;
	CEdit		m_vh_act_deact;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(VHChanDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(VHChanDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeVhChanList();
	afx_msg void OnCheckActDeakt();
	afx_msg void OnCheckSelectLengthen();
	afx_msg void OnUpdateNoQuarters();
	afx_msg void OnSelectVocoderChan();
	afx_msg void OnDeleteVocalHarmony();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	HPMF_Interface * hpmfi;
	int  act_vocoder_channel;
	bool vocoder_channel_set;
	bool vocoder_channel_delete;
	int vocoder_channel_act;
	int no_quarters;	 // -1: not selected; > 0: max number of quarters

private:
	int vh_channel_index_list[16]; // vh_channel_index_list[i] = k, i = index ComboBox, k = channel
	int no_vh_chans;
	bool vh_sysexes_exist;
	bool vocoder_defined;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_VHCHANDLG_H__ABFA0616_88DD_46BC_AC26_A8541B620EE2__INCLUDED_
