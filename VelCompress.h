#if !defined(AFX_VELCOMPRESS_H__101111B0_25D0_4746_AC13_F20CA8D87DD2__INCLUDED_)
#define AFX_VELCOMPRESS_H__101111B0_25D0_4746_AC13_F20CA8D87DD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VelCompress.h : Header-Datei
//

#include "HPMF_Interface.h"



/////////////////////////////////////////////////////////////////////////////
// Dialogfeld VelCompress 

class VelCompress : public CDialog
{

#define DELETE_UPTO_LIST 0
#define MIN_NEW_LIST     1
#define MAX_NEW_LIST     2
	
	// Konstruktion
public:
	VelCompress(CWnd* pParent = NULL);   // Standardkonstruktor
	HPMF_Interface * hpmfi;
	VEL_COMPRESS_ELEM final_vel_compress_list[16];
	VEL_COMPRESS_ELEM actual_vel_compress_list[16];

private:
	CToolTipCtrl* m_pToolTip;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void set_default(int chan);
	void actualize_average();
	void actualize_min(int chan);
	void check_delete_upto(int chan);
	void check_min_new(int chan);
	void check_max_new(int chan);

	void check_all(bool display);

	int min_max_average_vel_list[16][3];

	CEdit *m_edt_min_list[16];
	CEdit *m_edt_max_list[16];
	CEdit *m_edt_min_new_list[16];
	CEdit *m_edt_max_new_list[16];
	CEdit *m_edt_delete_upto_list[16];
	CEdit *m_edt_average_list[16];
	CEdit   *m_voice_type[16];	
	CButton *m_button_default_list[16];


	int voice_idc_list[16];
	int min_idc_list[16];
	int max_idc_list[16];
	int delete_upto_idc_list[16];
	int min_new_idc_list[16];
	int max_new_idc_list[16];
	int average_idc_list[16];

	bool init;

// Dialogfelddaten
	//{{AFX_DATA(VelCompress)
	enum { IDD = IDD_VEL_COMPRESS };
	CEdit	m_edt_voice1;
	CEdit	m_edt_voice2;
	CEdit	m_edt_voice3;
	CEdit	m_edt_voice4;
	CEdit	m_edt_voice5;
	CEdit	m_edt_voice6;
	CEdit	m_edt_voice7;
	CEdit	m_edt_voice8;
	CEdit	m_edt_voice9;
	CEdit	m_edt_voice10;
	CEdit	m_edt_voice11;
	CEdit	m_edt_voice12;
	CEdit	m_edt_voice13;
	CEdit	m_edt_voice14;
	CEdit	m_edt_voice15;
	CEdit	m_edt_voice16;
	CButton	m_default_button1;
	CButton	m_default_button2;
	CButton	m_default_button3;
	CButton	m_default_button4;
	CButton	m_default_button5;
	CButton	m_default_button6;
	CButton	m_default_button7;
	CButton	m_default_button8;
	CButton	m_default_button9;
	CButton	m_default_button10;
	CButton	m_default_button11;
	CButton	m_default_button12;
	CButton	m_default_button13;
	CButton	m_default_button14;
	CButton	m_default_button15;
	CButton	m_default_button16;
	CEdit	m_edt_min_new1;
	CEdit	m_edt_max_new1;
	CEdit   m_edt_average1;
	CEdit	m_edt_delete_upto1;
	CEdit	m_edt_max1;
	CEdit	m_edt_min1;
	CEdit	m_edt_min_new2;
	CEdit	m_edt_max_new2;
	CEdit   m_edt_average2;
	CEdit	m_edt_delete_upto2;
	CEdit	m_edt_max2;
	CEdit	m_edt_min2;
	CEdit	m_edt_min_new3;
	CEdit	m_edt_max_new3;
	CEdit   m_edt_average3;
	CEdit	m_edt_delete_upto3;
	CEdit	m_edt_max3;
	CEdit	m_edt_min3;
	CEdit	m_edt_min_new4;
	CEdit	m_edt_max_new4;
	CEdit   m_edt_average4;
	CEdit	m_edt_delete_upto4;
	CEdit	m_edt_max4;
	CEdit	m_edt_min4;
	CEdit	m_edt_min_new5;
	CEdit	m_edt_max_new5;
	CEdit   m_edt_average5;
	CEdit	m_edt_delete_upto5;
	CEdit	m_edt_max5;
	CEdit	m_edt_min5;
	CEdit	m_edt_min_new6;
	CEdit	m_edt_max_new6;
	CEdit   m_edt_average6;
	CEdit	m_edt_delete_upto6;
	CEdit	m_edt_max6;
	CEdit	m_edt_min6;
	CEdit	m_edt_min_new7;
	CEdit	m_edt_max_new7;
	CEdit   m_edt_average7;
	CEdit	m_edt_delete_upto7;
	CEdit	m_edt_max7;
	CEdit	m_edt_min7;
	CEdit	m_edt_min_new8;
	CEdit	m_edt_max_new8;
	CEdit   m_edt_average8;
	CEdit	m_edt_delete_upto8;
	CEdit	m_edt_max8;
	CEdit	m_edt_min8;
	CEdit	m_edt_min_new9;
	CEdit	m_edt_max_new9;
	CEdit   m_edt_average9;
	CEdit	m_edt_delete_upto9;
	CEdit	m_edt_max9;
	CEdit	m_edt_min9;
	CEdit	m_edt_min_new10;
	CEdit	m_edt_max_new10;
	CEdit   m_edt_average10;
	CEdit	m_edt_delete_upto10;
	CEdit	m_edt_max10;
	CEdit	m_edt_min10;
	CEdit	m_edt_min_new11;
	CEdit	m_edt_max_new11;
	CEdit   m_edt_average11;
	CEdit	m_edt_delete_upto11;
	CEdit	m_edt_max11;
	CEdit	m_edt_min11;
	CEdit	m_edt_min_new12;
	CEdit	m_edt_max_new12;
	CEdit   m_edt_average12;
	CEdit	m_edt_delete_upto12;
	CEdit	m_edt_max12;
	CEdit	m_edt_min12;
	CEdit	m_edt_min_new13;
	CEdit	m_edt_max_new13;
	CEdit   m_edt_average13;
	CEdit	m_edt_delete_upto13;
	CEdit	m_edt_max13;
	CEdit	m_edt_min13;
	CEdit	m_edt_min_new14;
	CEdit	m_edt_max_new14;
	CEdit   m_edt_average14;
	CEdit	m_edt_delete_upto14;
	CEdit	m_edt_max14;
	CEdit	m_edt_min14;
	CEdit	m_edt_min_new15;
	CEdit	m_edt_max_new15;
	CEdit   m_edt_average15;
	CEdit	m_edt_delete_upto15;
	CEdit	m_edt_max15;
	CEdit	m_edt_min15;
	CEdit	m_edt_min_new16;
	CEdit	m_edt_max_new16;
	CEdit   m_edt_average16;
	CEdit	m_edt_delete_upto16;
	CEdit	m_edt_max16;
	CEdit	m_edt_min16;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(VelCompress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(VelCompress)
	virtual BOOL OnInitDialog();
	afx_msg void OnDefaultButton1();
	afx_msg void OnDefaultButton2();
	afx_msg void OnDefaultButton3();
	afx_msg void OnDefaultButton4();
	afx_msg void OnDefaultButton5();
	afx_msg void OnDefaultButton6();
	afx_msg void OnDefaultButton7();
	afx_msg void OnDefaultButton8();
	afx_msg void OnDefaultButton9();
	afx_msg void OnDefaultButton10();
	afx_msg void OnDefaultButton11();
	afx_msg void OnDefaultButton12();
	afx_msg void OnDefaultButton13();
	afx_msg void OnDefaultButton14();
	afx_msg void OnDefaultButton15();
	afx_msg void OnDefaultButton16();
	afx_msg void OnUpdateEdtDeleteUpto1();
	afx_msg void OnUpdateEdtDeleteUpto2();
	afx_msg void OnUpdateEdtDeleteUpto3();
	afx_msg void OnUpdateEdtDeleteUpto4();
	afx_msg void OnUpdateEdtDeleteUpto5();
	afx_msg void OnUpdateEdtDeleteUpto6();
	afx_msg void OnUpdateEdtDeleteUpto7();
	afx_msg void OnUpdateEdtDeleteUpto8();
	afx_msg void OnUpdateEdtDeleteUpto9();
	afx_msg void OnUpdateEdtDeleteUpto10();
	afx_msg void OnUpdateEdtDeleteUpto11();
	afx_msg void OnUpdateEdtDeleteUpto12();
	afx_msg void OnUpdateEdtDeleteUpto13();
	afx_msg void OnUpdateEdtDeleteUpto14();
	afx_msg void OnUpdateEdtDeleteUpto15();
	afx_msg void OnUpdateEdtDeleteUpto16();
    afx_msg void OnUpdateEdtMinNew1();
	afx_msg void OnUpdateEdtMinNew2();
	afx_msg void OnUpdateEdtMinNew3();
	afx_msg void OnUpdateEdtMinNew4();
	afx_msg void OnUpdateEdtMinNew5();
	afx_msg void OnUpdateEdtMinNew6();
	afx_msg void OnUpdateEdtMinNew7();
	afx_msg void OnUpdateEdtMinNew8();
	afx_msg void OnUpdateEdtMinNew9();
	afx_msg void OnUpdateEdtMinNew10();
	afx_msg void OnUpdateEdtMinNew11();
	afx_msg void OnUpdateEdtMinNew12();
	afx_msg void OnUpdateEdtMinNew13();
	afx_msg void OnUpdateEdtMinNew14();
	afx_msg void OnUpdateEdtMinNew15();
	afx_msg void OnUpdateEdtMinNew16();
	afx_msg void OnUpdateEdtMaxNew1();
	afx_msg void OnUpdateEdtMaxNew2();
	afx_msg void OnUpdateEdtMaxNew3();
	afx_msg void OnUpdateEdtMaxNew4();
	afx_msg void OnUpdateEdtMaxNew5();
	afx_msg void OnUpdateEdtMaxNew6();
	afx_msg void OnUpdateEdtMaxNew7();
	afx_msg void OnUpdateEdtMaxNew8();
	afx_msg void OnUpdateEdtMaxNew9();
	afx_msg void OnUpdateEdtMaxNew10();
	afx_msg void OnUpdateEdtMaxNew11();
	afx_msg void OnUpdateEdtMaxNew12();
	afx_msg void OnUpdateEdtMaxNew13();
	afx_msg void OnUpdateEdtMaxNew14();
	afx_msg void OnUpdateEdtMaxNew15();
	afx_msg void OnUpdateEdtMaxNew16();
	afx_msg void OnCheckAll();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_VELCOMPRESS_H__101111B0_25D0_4746_AC13_F20CA8D87DD2__INCLUDED_
