// ChordsLyricsImportExport.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "ChordsLyricsImportExport.h"
#include "IniFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld ChordsLyricsImportExport


ChordsLyricsImportExport::ChordsLyricsImportExport(CWnd* pParent /*=NULL*/)
	: CDialog(ChordsLyricsImportExport::IDD, pParent)
{
	//{{AFX_DATA_INIT(ChordsLyricsImportExport)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT

	is_chords = false;
	is_lyrics = false;
	is_import = false;
	is_export = false;
	is_chord_sysex = false;
	is_remove_after = false;
	chord_lyricfile = "";
}


void ChordsLyricsImportExport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ChordsLyricsImportExport)
	DDX_Control(pDX, IDC_CHECK_SELECT_LYRIC_CHORDS, m_check_lyric_chords);
	DDX_Control(pDX, IDC_CHECK_SELECT_IMPORT, m_check_select_import);
	DDX_Control(pDX, IDC_CHECK_SELECT_EXPORT, m_check_select_export);
	DDX_Control(pDX, IDC_CHECK_REMOVE_AFTER, m_check_remove_after);
	DDX_Control(pDX, IDC_CHECK_CHORD_SYSEX, m_check_chord_sysex);
	DDX_Control(pDX, IDC_CHORD_CHECK, m_chord_check);
	DDX_Control(pDX, IDC_LYRIC_CHECK, m_lyric_check);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ChordsLyricsImportExport, CDialog)
	//{{AFX_MSG_MAP(ChordsLyricsImportExport)
	ON_BN_CLICKED(IDC_CHORD_CHECK, OnChordCheck)
	ON_BN_CLICKED(IDC_LYRIC_CHECK, OnLyricCheck)
	ON_BN_CLICKED(IDC_CHECK_SELECT_EXPORT, OnCheckSelectExport)
	ON_BN_CLICKED(IDC_CHECK_SELECT_IMPORT, OnCheckSelectImport)
	ON_BN_CLICKED(IDC_CHECK_SELECT_LYRIC_CHORDS, OnCheckSelectLyricChords)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten ChordsLyricsImportExport


BOOL ChordsLyricsImportExport::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_chord_check.EnableWindow(true);
	m_chord_check.SetCheck(0);
	m_lyric_check.EnableWindow(true);
	m_lyric_check.SetCheck(0);

	m_check_select_import.SetCheck(0);
	m_check_chord_sysex.SetCheck(0);
	m_check_chord_sysex.EnableWindow(false);

	m_check_select_export.SetCheck(0);
	m_check_lyric_chords.SetCheck(0);
	m_check_remove_after.SetCheck(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void ChordsLyricsImportExport::OnChordCheck()
{
	if (m_chord_check.GetCheck()==1)
	{
		if (m_check_select_import.GetCheck()==1)
		{
			m_check_chord_sysex.EnableWindow(true);
		}
		else
		{
			m_check_chord_sysex.EnableWindow(false);
		}
	}
	else
	{
		m_check_chord_sysex.EnableWindow(false);
	}
}

void ChordsLyricsImportExport::OnLyricCheck()
{
	if (m_lyric_check.GetCheck()==1)
	{
		if (m_check_select_import.GetCheck()==1)
		{
			m_check_remove_after.EnableWindow(false);
		}
		else
		{
			m_check_remove_after.EnableWindow(true);
		}
	}
	else
	{
		m_check_remove_after.EnableWindow(true);
	}
}

void ChordsLyricsImportExport::OnCheckSelectExport() 
{
	m_check_remove_after.EnableWindow(true);

	if (m_check_select_export.GetCheck()==1)
	{
		m_check_select_import.SetCheck(0);
		m_check_chord_sysex.SetCheck(0);
		m_check_chord_sysex.EnableWindow(false);
	}
}

void ChordsLyricsImportExport::OnCheckSelectLyricChords() 
{	// export XF-chords as lyrics
	m_check_remove_after.EnableWindow(true);

	if (m_check_lyric_chords.GetCheck()==1)
	{
		m_check_select_import.SetCheck(0);
		m_check_chord_sysex.SetCheck(0);
		m_check_chord_sysex.EnableWindow(false);
	}
}

void ChordsLyricsImportExport::OnCheckSelectImport() 
{
	m_check_chord_sysex.SetCheck(0);
	m_check_remove_after.SetCheck(0);

	if (m_check_select_import.GetCheck()==1)
	{
		m_check_select_export.SetCheck(0);
		m_check_lyric_chords.SetCheck(0);
		m_check_remove_after.EnableWindow(false);
		if (m_chord_check.GetCheck()==1)
		{
			m_check_chord_sysex.EnableWindow(true);
		}
		else
		{
			m_check_chord_sysex.EnableWindow(false);
		}
	}
	else
	{
		m_check_remove_after.EnableWindow(true);
		m_check_chord_sysex.EnableWindow(false);
	}
}

void ChordsLyricsImportExport::OnOK()
{
	int i;

	is_chords = m_chord_check.GetCheck()==1;
	is_lyrics = m_lyric_check.GetCheck()==1;
	
	if (!is_chords && !is_lyrics)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SELECT_CHORDS_LYRICS),NULL,MB_OK|MB_TASKMODAL);
		return;
	}
	is_import = m_check_select_import.GetCheck()==1;
	is_export = m_check_select_export.GetCheck()==1;
	is_export_as_lyrics = m_check_lyric_chords.GetCheck()==1;
	is_remove_after = m_check_remove_after.GetCheck()==1;

	if (!is_import && !is_export && !is_remove_after)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SELECT_IMPORT_EXPORT),NULL,MB_OK|MB_TASKMODAL);
		return;
	}
	
	is_chord_sysex = m_check_chord_sysex.GetCheck()==1;

	if (is_import || is_export)
	{
		char BASED_CODE szFilter[] = 
			"Chord/Lyric-File (*.txt)|*.txt||";

		CFileDialog openfile_dlg(is_import,
							  "txt",
							  NULL,
							  is_import?OFN_FILEMUSTEXIST:OFN_PATHMUSTEXIST,
							  szFilter,
							  NULL);
	
		// Get last_chordlyricfile
		CString last_chordlyric = o_inifile->get_chordlyricfile();
		if (last_chordlyric != "")
		{
			char lcl[MAX_PATH];
			for (i=0; i<last_chordlyric.GetLength(); i++)
			{
				lcl[i] = last_chordlyric[i];
			}
			lcl[last_chordlyric.GetLength()] = (char)0;
			openfile_dlg.m_ofn.lpstrFile = lcl;
		}

		int return_value = openfile_dlg.DoModal();
		if (return_value == IDOK)
		{
			chord_lyricfile = openfile_dlg.m_ofn.lpstrFile;
			if (is_export)
			{
				// allowed to overwrite existing file?
				CFile f;
				CFileException e;
				if (f.Open(chord_lyricfile, CFile::modeRead,&e))
				{
					int length = f.GetLength();
					f.Close();
					if (length>0)
					{
						CString r;
						r.Format(GlobalUtilities::get_resource_string(IDS_UseExistingFile)+"\"%s\" ?",chord_lyricfile);
						if (IDYES != AfxMessageBox(r,MB_YESNO,0))
						{
							chord_lyricfile = "";
						}
					}
				}
			}
		}
		else 
		{
			chord_lyricfile = "";
		}

		if (chord_lyricfile=="")
		{
			EndDialog(0);
		}
		else
		{
			o_inifile->set_chordlyricfile(chord_lyricfile);
		}
	}
	else
	{
		chord_lyricfile= "";
	}
	EndDialog(1);
}

void ChordsLyricsImportExport::OnCancel()
{
	EndDialog(0);
}
