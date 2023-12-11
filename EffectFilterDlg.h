#if !defined(AFX_EFFECTFILTERDLG_H__F8FFCFF8_D4E3_43DD_845A_160EF6011504__INCLUDED_)
#define AFX_EFFECTFILTERDLG_H__F8FFCFF8_D4E3_43DD_845A_160EF6011504__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EffectFilterDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld EffectFilterDlg 

class EffectFilterDlg : public CDialog
{
// Konstruktion
public:
	EffectFilterDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(EffectFilterDlg)
	enum { IDD = IDD_EFFEKT_FILTER };
	CEdit	m_voice_1;
	CEdit	m_voice_2;
	CEdit	m_voice_3;
	CEdit	m_voice_4;
	CEdit	m_voice_5;
	CEdit	m_voice_6;
	CEdit	m_voice_7;
	CEdit	m_voice_8;
	CEdit	m_voice_9;
	CEdit	m_voice_10;
	CEdit	m_voice_11;
	CEdit	m_voice_12;
	CEdit	m_voice_13;
	CEdit	m_voice_14;
	CEdit	m_voice_15;
	CEdit	m_voice_16;
	CEdit	m_drywet_text_1;
	CEdit	m_drywet_text_2;
	CEdit	m_drywet_text_3;
	CEdit	m_drywet_text_4;
	CEdit	m_drywet_text_5;
	CEdit	m_drywet_text_6;
	CEdit	m_drywet_text_7;
	CEdit	m_drywet_text_8;
	CEdit	m_drywet_text_9;
	CEdit	m_drywet_text_10;
	CEdit	m_drywet_text_11;
	CEdit	m_drywet_text_12;
	CEdit	m_drywet_text_13;
	CEdit	m_drywet_text_14;
	CEdit	m_drywet_text_15;
	CEdit	m_drywet_text_16;
	CEdit	m_reverb_1;
	CEdit	m_reverb_2;
	CEdit	m_reverb_3;
	CEdit	m_reverb_4;
	CEdit	m_reverb_5;
	CEdit	m_reverb_6;
	CEdit	m_reverb_7;
	CEdit	m_reverb_8;
	CEdit	m_reverb_9;
	CEdit	m_reverb_10;
	CEdit	m_reverb_11;
	CEdit	m_reverb_12;
	CEdit	m_reverb_13;
	CEdit	m_reverb_14;
	CEdit	m_reverb_15;
	CEdit	m_reverb_16;
	CEdit	m_chorus_1;
	CEdit	m_chorus_2;
	CEdit	m_chorus_3;
	CEdit	m_chorus_4;
	CEdit	m_chorus_5;
	CEdit	m_chorus_6;
	CEdit	m_chorus_7;
	CEdit	m_chorus_8;
	CEdit	m_chorus_9;
	CEdit	m_chorus_10;
	CEdit	m_chorus_11;
	CEdit	m_chorus_12;
	CEdit	m_chorus_13;
	CEdit	m_chorus_14;
	CEdit	m_chorus_15;
	CEdit	m_chorus_16;
	CEdit	m_variation_1;
	CEdit	m_variation_2;
	CEdit	m_variation_3;
	CEdit	m_variation_4;
	CEdit	m_variation_5;
	CEdit	m_variation_6;
	CEdit	m_variation_7;
	CEdit	m_variation_8;
	CEdit	m_variation_9;
	CEdit	m_variation_10;
	CEdit	m_variation_11;
	CEdit	m_variation_12;
	CEdit	m_variation_13;
	CEdit	m_variation_14;
	CEdit	m_variation_15;
	CEdit	m_variation_16;
	CEdit	m_drywet_1;
	CEdit	m_drywet_2;
	CEdit	m_drywet_3;
	CEdit	m_drywet_4;
	CEdit	m_drywet_5;
	CEdit	m_drywet_6;
	CEdit	m_drywet_7;
	CEdit	m_drywet_8;
	CEdit	m_drywet_9;
	CEdit	m_drywet_10;
	CEdit	m_drywet_11;
	CEdit	m_drywet_12;
	CEdit	m_drywet_13;
	CEdit	m_drywet_14;
	CEdit	m_drywet_15;
	CEdit	m_drywet_16;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(EffectFilterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(EffectFilterDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChangeReverb1();
	afx_msg void OnChangeReverb2();
	afx_msg void OnChangeReverb3();
	afx_msg void OnChangeReverb4();
	afx_msg void OnChangeReverb5();
	afx_msg void OnChangeReverb6();
	afx_msg void OnChangeReverb7();
	afx_msg void OnChangeReverb8();
	afx_msg void OnChangeReverb9();
	afx_msg void OnChangeReverb10();
	afx_msg void OnChangeReverb11();
	afx_msg void OnChangeReverb12();
	afx_msg void OnChangeReverb13();
	afx_msg void OnChangeReverb14();
	afx_msg void OnChangeReverb15();
	afx_msg void OnChangeReverb16();
	afx_msg void OnChangeChorus1();
	afx_msg void OnChangeChorus2();
	afx_msg void OnChangeChorus3();
	afx_msg void OnChangeChorus4();
	afx_msg void OnChangeChorus5();
	afx_msg void OnChangeChorus6();
	afx_msg void OnChangeChorus7();
	afx_msg void OnChangeChorus8();
	afx_msg void OnChangeChorus9();
	afx_msg void OnChangeChorus10();
	afx_msg void OnChangeChorus11();
	afx_msg void OnChangeChorus12();
	afx_msg void OnChangeChorus13();
	afx_msg void OnChangeChorus14();
	afx_msg void OnChangeChorus15();
	afx_msg void OnChangeChorus16();
	afx_msg void OnChangeVariation1();
	afx_msg void OnChangeVariation2();
	afx_msg void OnChangeVariation3();
	afx_msg void OnChangeVariation4();
	afx_msg void OnChangeVariation5();
	afx_msg void OnChangeVariation6();
	afx_msg void OnChangeVariation7();
	afx_msg void OnChangeVariation8();
	afx_msg void OnChangeVariation9();
	afx_msg void OnChangeVariation10();
	afx_msg void OnChangeVariation11();
	afx_msg void OnChangeVariation12();
	afx_msg void OnChangeVariation13();
	afx_msg void OnChangeVariation14();
	afx_msg void OnChangeVariation15();
	afx_msg void OnChangeVariation16();
	afx_msg void OnChangeDryWet1();
	afx_msg void OnChangeDryWet2();
	afx_msg void OnChangeDryWet3();
	afx_msg void OnChangeDryWet4();
	afx_msg void OnChangeDryWet5();
	afx_msg void OnChangeDryWet6();
	afx_msg void OnChangeDryWet7();
	afx_msg void OnChangeDryWet8();
	afx_msg void OnChangeDryWet9();
	afx_msg void OnChangeDryWet10();
	afx_msg void OnChangeDryWet11();
	afx_msg void OnChangeDryWet12();
	afx_msg void OnChangeDryWet13();
	afx_msg void OnChangeDryWet14();
	afx_msg void OnChangeDryWet15();
	afx_msg void OnChangeDryWet16();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	HPMF_Interface * hpmfi;
	HCURSOR hCursorWait;
	HCURSOR hCursorOld;

private:
	// Data
	CToolTipCtrl* m_pToolTip;
	CEdit   *m_voice_type[16];	

	long reverb_idlist[16];
	CEdit *reverb_list[16];
	long chorus_idlist[16];
	CEdit *chorus_list[16];
	long variation_idlist[16];
	CEdit *variation_list[16];
	long drywet_idlist[16];
	CEdit *drywet_list[16];
	long drywettext_idlist[16];
	CEdit *drywettext_list[16];
	long idc_voice_type[16];

	int reverb_changed[16];
	int chorus_changed[16];
	int variation_changed[16];
	int drywet_changed[16];
	int block_list[16];

	bool something_changed;
	bool drywet_inserted;

	// functions
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void ChangeReverb(int chan);
	void ChangeChorus(int chan);
	void ChangeVariation(int chan);
	void ChangeDryWet(int chan);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_EFFECTFILTERDLG_H__F8FFCFF8_D4E3_43DD_845A_160EF6011504__INCLUDED_
