#if !defined(AFX_TRANSPOSENO_H__F529D3A7_727F_49F7_B259_71F509E13FCA__INCLUDED_)
#define AFX_TRANSPOSENO_H__F529D3A7_727F_49F7_B259_71F509E13FCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Transpose_no.h : Header-Datei
//
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Transpose_no 

class Transpose_no : public CDialog
{
// Konstruktion
public:
	Transpose_no(CWnd* pParent = NULL);   // Standardkonstruktor
	bool transpose_chords();
	CString send_new_key();

private:
// Dialogfelddaten
	//{{AFX_DATA(Transpose_no)
	enum { IDD = IDD_TRANSPOSE_NO };
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
	CButton	m_transpose_chords_check;
	CListBox	m_oct9;
	CListBox	m_oct8;
	CListBox	m_oct7;
	CListBox	m_oct6;
	CListBox	m_oct5;
	CListBox	m_oct4;
	CListBox	m_oct3;
	CListBox	m_oct2;
	CListBox	m_oct16;
	CListBox	m_oct15;
	CListBox	m_oct14;
	CListBox	m_oct13;
	CListBox	m_oct12;
	CListBox	m_oct11;
	CListBox	m_oct10;
	CListBox	m_oct1;
	CEdit	m_ll9;
	CEdit	m_ll8;
	CEdit	m_ll7;
	CEdit	m_ll6;
	CEdit	m_ll5;
	CEdit	m_ll4;
	CEdit	m_ll3;
	CEdit	m_ll2;
	CEdit	m_ll16;
	CEdit	m_ll15;
	CEdit	m_ll14;
	CEdit	m_ll12;
	CEdit	m_ll13;
	CEdit	m_ll11;
	CEdit	m_ll10;
	CEdit	m_hl9;
	CEdit	m_hl8;
	CEdit	m_hl7;
	CEdit	m_hl6;
	CEdit	m_hl5;
	CEdit	m_hl4;
	CEdit	m_hl3;
	CEdit	m_hl2;
	CEdit	m_hl16;
	CEdit	m_hl15;
	CEdit	m_hl14;
	CEdit	m_hl13;
	CEdit	m_hl12;
	CEdit	m_hl11;
	CEdit	m_hl10;
	CButton	m_mute9;
	CButton	m_mute8;
	CButton	m_mute7;
	CButton	m_mute6;
	CButton	m_mute16;
	CButton	m_mute15;
	CButton	m_mute14;
	CButton	m_mute13;
	CButton	m_mute12;
	CButton	m_mute11;
	CButton	m_mute10;
	CButton	m_mute5;
	CButton	m_mute4;
	CButton	m_mute3;
	CButton	m_mute2;
	CEdit	m_ll1;
	CEdit	m_hl1;
	CButton	m_mute1;
	CListBox	m_listtranspose_no;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Transpose_no)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung

public:
	HPMF_Interface * hpmfi;

private:
	CToolTipCtrl* m_pToolTip;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit   *m_voice_type[16];
	bool local_hpmfi_mute[16];

// protected:

	CString key, tonart, new_key;

	CButton *mute[16];
	CEdit	*hl[16];
	CEdit	*ll[16];
	CListBox *oct[16];

	int		idc_type[16];
	int		idc_hl[16];
	int		idc_ll[16];

	int		hl_val[16], ll_val[16]; // tested notevalues of low and highlimit
	int		nvl[16], nvh[16]; // notevalues of actual displayed low and highlimit 

	bool	mute_val[16];
	int		oct_val[16];
	int		tr_no;		// transpose-number
	int		tr_no_list[16];
	CString computed_key;
	bool	is_transpose_chords;
	static const CString keylistelement[16];
	static const CString majminlistelement[3];


	int compute_notevalue(CString nstr);
	void eval_sel_oct(int chan);

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Transpose_no)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck();
	afx_msg void OnSelchangeOct1();
	afx_msg void OnSelchangeOct10();
	afx_msg void OnSelchangeOct11();
	afx_msg void OnSelchangeOct12();
	afx_msg void OnSelchangeOct13();
	afx_msg void OnSelchangeOct14();
	afx_msg void OnSelchangeOct15();
	afx_msg void OnSelchangeOct16();
	afx_msg void OnSelchangeOct2();
	afx_msg void OnSelchangeOct3();
	afx_msg void OnSelchangeOct4();
	afx_msg void OnSelchangeOct5();
	afx_msg void OnSelchangeOct6();
	afx_msg void OnSelchangeOct7();
	afx_msg void OnSelchangeOct8();
	afx_msg void OnSelchangeOct9();
	afx_msg void OnSelchangeListtransposeNo();
	afx_msg void OnChangeKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



#endif // AFX_TRANSPOSENO_H__F529D3A7_727F_49F7_B259_71F509E13FCA__INCLUDED_
