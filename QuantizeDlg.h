#if !defined(AFX_QUANTIZEDLG_H__B2CD0C47_D100_4123_94BE_C1C95891A2BC__INCLUDED_)
#define AFX_QUANTIZEDLG_H__B2CD0C47_D100_4123_94BE_C1C95891A2BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QuantizeDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CQuantizeDlg 

class CQuantizeDlg : public CDialog
{
// Konstruktion
public:
	CQuantizeDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CQuantizeDlg)
	enum { IDD = IDD_QUANTIZE };
	CButton	m_check_16th_triole;
	CButton	m_check_start_time;
	CButton	m_check_note_length;
	CButton	m_OK;
	CButton	m_check_64th;
	CButton	m_check_32th;
	CButton	m_check_16th;
	CButton	m_check_eightteenth_triole;
	CButton	m_check_eightteenth;
	CButton	m_check_quarter_triole;
	CButton	m_check_half_triole;
	CButton	m_check_quarter;
	CButton	m_check_half;
	CButton	m_check_whole;
	CButton	m_check_chan1;
	CButton	m_check_chan2;
	CButton	m_check_chan3;
	CButton	m_check_chan4;
	CButton	m_check_chan5;
	CButton	m_check_chan6;
	CButton	m_check_chan7;
	CButton	m_check_chan8;
	CButton	m_check_chan9;
	CButton	m_check_chan10;
	CButton	m_check_chan11;
	CButton	m_check_chan12;
	CButton	m_check_chan13;
	CButton	m_check_chan14;
	CButton	m_check_chan15;
	CButton	m_check_chan16;
	CEdit	m_type1;
	CEdit	m_type2;
	CEdit	m_type3;
	CEdit	m_type4;
	CEdit	m_type5;
	CEdit	m_type6;
	CEdit	m_type7;
	CEdit	m_type8;
	CEdit	m_type9;
	CEdit	m_type10;
	CEdit	m_type11;
	CEdit	m_type12;
	CEdit	m_type13;
	CEdit	m_type14;
	CEdit	m_type15;
	CEdit	m_type16;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CQuantizeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CQuantizeDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnCheckChan1();
	afx_msg void OnCheckChan2();
	afx_msg void OnCheckChan3();
	afx_msg void OnCheckChan4();
	afx_msg void OnCheckChan5();
	afx_msg void OnCheckChan6();
	afx_msg void OnCheckChan7();
	afx_msg void OnCheckChan8();
	afx_msg void OnCheckChan9();
	afx_msg void OnCheckChan10();
	afx_msg void OnCheckChan11();
	afx_msg void OnCheckChan12();
	afx_msg void OnCheckChan13();
	afx_msg void OnCheckChan14();
	afx_msg void OnCheckChan15();
	afx_msg void OnCheckChan16();
	afx_msg void OnCheckWhole();
	afx_msg void OnCheckHalf();
	afx_msg void OnCheckQuarter();
	afx_msg void OnCheckHalfTriole();
	afx_msg void OnCheckEightteenth();
	afx_msg void OnCheckEightteenthTriole();
	afx_msg void OnCheck16th();
	afx_msg void OnCHECK32th();
	afx_msg void OnCheck64th();
	afx_msg void OnCheckQuarterTriole();
	afx_msg void OnCheckNoteLength();
	afx_msg void OnCheckStartTime();
	afx_msg void OnCheck16thTriole();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CToolTipCtrl* m_pToolTip;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit   *m_voice_type[16];
	CButton *m_check_chan[16];
	CButton *m_check_raster[11];
	int		idc_type[16];
	bool mute_val[16];
	bool destroyed_check[16];
	int raster_code[11];
	int raster_ticks[11];

	void check_chan(int selected_chan);
	void check_raster(int raster_index);

public:
	HPMF_Interface *hpmfi;

	int chan; 
	int length_code;
	bool starts;
	bool note_length;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_QUANTIZEDLG_H__B2CD0C47_D100_4123_94BE_C1C95891A2BC__INCLUDED_
