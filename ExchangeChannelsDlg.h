#if !defined(AFX_EXCHANGECHANNELSDLG_H__8F6F4F93_78DF_4A9A_823A_0EC135C7EA9D__INCLUDED_)
#define AFX_EXCHANGECHANNELSDLG_H__8F6F4F93_78DF_4A9A_823A_0EC135C7EA9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExchangeChannelsDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld ExchangeChannelsDlg 

class ExchangeChannelsDlg : public CDialog
{

// Konstruktion
public:
	ExchangeChannelsDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(ExchangeChannelsDlg)
	enum { IDD = IDD_EXCHANGE_CHANNELS };
	CEdit	m_channel_patch1;
	CEdit	m_channel_patch2;
	CEdit	m_channel_patch3;
	CEdit	m_channel_patch4;
	CEdit	m_channel_patch5;
	CEdit	m_channel_patch6;
	CEdit	m_channel_patch7;
	CEdit	m_channel_patch8;
	CEdit	m_channel_patch9;
	CEdit	m_channel_patch10;
	CEdit	m_channel_patch11;
	CEdit	m_channel_patch12;
	CEdit	m_channel_patch13;
	CEdit	m_channel_patch14;
	CEdit	m_channel_patch15;
	CEdit	m_channel_patch16;
	CButton	m_source_1;
	CButton	m_source_2;
	CButton	m_source_3;
	CButton	m_source_4;
	CButton	m_source_5;
	CButton	m_source_6;
	CButton	m_source_7;
	CButton	m_source_8;
	CButton	m_source_9;
	CButton	m_source_10;
	CButton	m_source_11;
	CButton	m_source_12;
	CButton	m_source_13;
	CButton	m_source_14;
	CButton	m_source_15;
	CButton	m_source_16;
	CButton	m_dest_1;
	CButton	m_dest_2;
	CButton	m_dest_3;
	CButton	m_dest_4;
	CButton	m_dest_5;
	CButton	m_dest_6;
	CButton	m_dest_7;
	CButton	m_dest_8;
	CButton	m_dest_9;
	CButton	m_dest_10;
	CButton	m_dest_11;
	CButton	m_dest_12;
	CButton	m_dest_13;
	CButton	m_dest_14;
	CButton	m_dest_15;
	CButton	m_dest_16;
	CListBox	m_list_copy_exchange;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(ExchangeChannelsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(ExchangeChannelsDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListCopyExchange();
	afx_msg void OnSource1();
	afx_msg void OnSource2();
	afx_msg void OnSource3();
	afx_msg void OnSource4();
	afx_msg void OnSource5();
	afx_msg void OnSource6();
	afx_msg void OnSource7();
	afx_msg void OnSource8();
	afx_msg void OnSource9();
	afx_msg void OnSource10();
	afx_msg void OnSource11();
	afx_msg void OnSource12();
	afx_msg void OnSource13();
	afx_msg void OnSource14();
	afx_msg void OnSource15();
	afx_msg void OnSource16();
	afx_msg void OnDest1();
	afx_msg void OnDest2();
	afx_msg void OnDest3();
	afx_msg void OnDest4();
	afx_msg void OnDest5();
	afx_msg void OnDest6();
	afx_msg void OnDest7();
	afx_msg void OnDest8();
	afx_msg void OnDest9();
	afx_msg void OnDest10();
	afx_msg void OnDest11();
	afx_msg void OnDest12();
	afx_msg void OnDest13();
	afx_msg void OnDest14();
	afx_msg void OnDest15();
	afx_msg void OnDest16();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	HPMF_Interface *hpmfi;
	int selection;
	bool source_channels[16];
	int dest_channel;

private:
	CButton *source_check[16];
	CButton *dest_check[16];
	int	idc_voice_name[16]; // voice names

	CToolTipCtrl* m_pToolTip;
	CEdit   *m_voice_type[16];	
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void SourceClicked(int chan, int checked); 
	void DestClicked(int chan, int checked); 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_EXCHANGECHANNELSDLG_H__8F6F4F93_78DF_4A9A_823A_0EC135C7EA9D__INCLUDED_
