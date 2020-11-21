#if !defined(AFX_SCORE_H__7822548E_D20C_4BB6_9DA7_08F09929B661__INCLUDED_)
#define AFX_SCORE_H__7822548E_D20C_4BB6_9DA7_08F09929B661__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Score.h : Header-Datei
//

#include "ScoreLayout.h"
#include "ScoreChanDlg.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Score 

class Score : public CDialog
{
// Konstruktion
public:
	Score(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Score)
	enum { IDD = IDD_SCORE };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Score)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
public:

	HPMF_Interface *hpmfi;
	MainFunctions *mainfun;
	HCURSOR hCursorWait;
	HCURSOR hCursorOld;
	bool batch_running;

	bool scorechan_folder_running;
	bool scorechan_folder_abort_wanted;

	bool scorelayout_folder_running;
	bool scorelayout_folder_abort_wanted;

	IniFile *o_inifile;

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Score)
	afx_msg void OnScorechan();
	afx_msg void OnScoreLayout();
	afx_msg void OnScorenotesopt();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	HANDLE hThread;
	DWORD threadID;
	ScoreLayout *scorelayout_dlg;
	ScoreChanDlg *scorechan_dlg;

	static DWORD scorelayout_thread_run(Score *this_thread);
	void scorelayout_folder();
	void scorelayout_folder_file(CString midifile,CString dest_path);

	static DWORD scorechan_thread_run(Score *this_thread);
	void scorechan_folder();
	void scorechan_folder_file(CString midifile,CString dest_path);

	void initialize_source_reduced();

	char sourcefile[MAX_PATH+512];
	char destfile[MAX_PATH+512];

	unsigned char lyrics_value;		
	unsigned char chords_value;			
	unsigned char notenames_value;	
	unsigned char size_value;			
	unsigned char quantize_triole_value; 
	unsigned char quantize_value;
	unsigned char notenamestype_value;
	unsigned char notecolour_value;	

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SCORE_H__7822548E_D20C_4BB6_9DA7_08F09929B661__INCLUDED_
