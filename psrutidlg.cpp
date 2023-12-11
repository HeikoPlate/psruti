// psrutiDlg.cpp : Implementierungsdatei
//


#include "stdafx.h"
#include "psruti.h"
#include "psrutiDlg.h"

#include "SelectMIDIDevice.h"
#include "SelectFillLyrics.h"
#include "Expr_MainVolume.h"

#include "IniFile.h"
#include "Select_Language.h"
#include "Play.h"
#include "Extras_Dlg.h"
#include "Print.h"
#include "QuantisizeChords.h"
#include "VelCompress.h"
#include "RevoicingMethodDlg.h"
#include "RevoicingDlg.h"
#include "VoicefileRevoicingDlg.h"
#include "ComputeBanknumberMsbLsb.h"
#include "StartBeat.h"
#include "SysexDlg.h"
#include "ImportLyricsAtChannelNotes.h"
#include "ChordsLyricsImportExport.h"
#include "SlctChordChan.h"
#include "Transpose_no.h"
#include "Drums.h"
#include "ExchangeChannelsDlg.h"
#include "SaveChangesDlg.h"
#include "QuantisizeLyricsDlg.h"
#include "tempo_dlg.h"
#include "SysexPasteDlg.h"
#include "FillLyricMethodDlg.h"
#include "ChangeDrumVoicesDlg.h"
#include "VolumeMethodDlg.h"
#include "ControllerEffectsDlg.h"
#include "EffectFilterDlg.h"
#include "ChordsLyricsEditor.h"
#include "FileAttributesDlg.h"
#include "PreferencesDlg.h"
#include "DrumVoicesTemplateDlg.h"
#include "Delete_Fill_Lyrics_Dlg.h"



/*********************************************************************************/
/** SysEx XG effects from file Test **********************************************/
/*********************************************************************************/

#include "XgEffects.h"

/*********************************************************************************/
/**  End SysEx XG effects from file Test *****************************************/
/*********************************************************************************/


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// to be defined if debugging wanted under Vista
// #define DEBUG_SOURCE "C:\\Users\\Heiko\\Desktop\\test.mid"

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogfelddaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPsrutiDlg Dialogfeld


IMPLEMENT_DYNAMIC(CPsrutiDlg, CDialog);

CPsrutiDlg::CPsrutiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPsrutiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPsrutiDlg)
	m_filename = _T("");
	m_destination = _T("");
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pToolTip = NULL;
	hCursorOld = GetCursor();
	hCursorWait = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
	hpmfi = NULL;
	hpmfi_save = NULL;
	batch_running = false;
	xg_convert_folder_running = false;
	xg_convert_folder_abort_wanted = false;
	gm_convert_folder_running = false;
	gm_convert_folder_abort_wanted = false;
	revoicefile_folder_running = false;
	revoicefile_folder_abort_wanted = false;
	print_folder_running = false;
	print_folder_abort_wanted = false;
	fileformat_folder_running = false;
	fileformat_folder_abort_wanted = false;
	count_in_folder_running = false;
	count_in_folder_abort_wanted = false;
	count_in_dlg = NULL;
	fill_lyric_folder_running = false;
	fill_lyric_folder_abort_wanted = false;
	drum_folder_running = false;
	drum_folder_abort_wanted = false;
	fill_lyric_dlg = NULL;


	expr_main_volume_folder_running = false;
	expr_main_volume_folder_abort_wanted = false;

	from_close = false;
	command_line = new char[32];
	command_line[0] = 0;
}


CPsrutiDlg::~CPsrutiDlg()
{
	if (m_pToolTip != NULL)
	{
		delete m_pToolTip;
		m_pToolTip = NULL;
	}

	if (o_inifile != NULL)
	{
		delete o_inifile;
		o_inifile = NULL;
	}
}

IniFile *CPsrutiDlg::o_inifile;

CString CPsrutiDlg::hlpfilename_germ	= "psruti_germ.pdf";
CString CPsrutiDlg::hlpfilename_eng		= "psruti_eng.pdf";

Log * CPsrutiDlg::lf = NULL;

void CPsrutiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPsrutiDlg)
	DDX_Control(pDX, IDC_CONVERT_GM, m_convert_gm);
	DDX_Control(pDX, IDC_SOURCE_CLOSE, m_source_close);
	DDX_Control(pDX, IDC_DRUMS, m_drums);
	DDX_Control(pDX, IDC_PREFERENCES, m_preferences);
	DDX_Control(pDX, IDC_FILE_FORMAT, m_file_format);
	DDX_Control(pDX, IDC_SAVE, m_save);
	DDX_Control(pDX, IDC_CHORDS_LYRICS_EDITOR, m_chord_lyric_editor);
	DDX_Control(pDX, IDC_QUANTISIZE_LYRICS, m_quantisize_lyrics);
	DDX_Control(pDX, IDC_EXCHANGE_CHANNELS, m_exchange_channels);
	DDX_Control(pDX, IDC_EXTRAS, m_extras);
	DDX_Control(pDX, IDC_CONTROLLER, m_controller_effects);
	DDX_Control(pDX, IDC_CHORDS_LYRICS_IMPORT_EXPORT, m_chords_lyrics_import_export);
	DDX_Control(pDX, IDC_LYRICS_AT_CHANNEL_NOTES, m_lyrics_at_channel_notes);
	DDX_Control(pDX, IDC_UNDO, m_undo);
	DDX_Control(pDX, IDC_REVOICING, m_revoicing);
	DDX_Control(pDX, IDC_PRINT, m_print);
	DDX_Control(pDX, IDC_START_BEAT, m_start_beat);
	DDX_Control(pDX, IDC_VEL_COMPRESS, m_vel_compress);
	DDX_Control(pDX, IDC_QUANTISIZE_CHORDS, m_quantisize_chords);
	DDX_Control(pDX, IDC_PLAY_BUTTON, m_play);
	DDX_Control(pDX, IDC_LINEFEED_NEWPAGE, m_select_fill_lyrics_linefeed);
	DDX_Control(pDX, IDC_FILLLYRICS, m_insert_fill_lyrics);
	DDX_Control(pDX, IDC_INSERT_CHORDS, m_compute_chords);
	DDX_Control(pDX, IDC_SYSEX, m_sysex_import_export);
	DDX_Control(pDX, IDC_VOLUME, m_expr_mvolume);
	DDX_Control(pDX, IDC_LANGUAGE, m_language);
	DDX_Control(pDX, IDC_PSRUTI_HELP, m_help);
	DDX_Control(pDX, IDC_SAVE_AS, m_save_as);
	DDX_Control(pDX, IDC_TEMPO, m_tempo);
	DDX_Control(pDX, IDC_TRANSPOSE, m_transpose);
	DDX_Control(pDX, IDC_XG_CONVERT, m_xg_convert);
	DDX_Control(pDX, IDOK, m_exit);
	DDX_Control(pDX, IDC_SELECTSOURCE, m_selectsource);
	DDX_Control(pDX, IDC_INFO, m_info);
	DDX_Text(pDX, IDC_FILENAME, m_filename);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPsrutiDlg, CDialog)
	//{{AFX_MSG_MAP(CPsrutiDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INFO, OnInfo)
	ON_BN_CLICKED(IDC_TRANSPOSE, OnTranspose)
	ON_BN_CLICKED(IDC_INSERT_CHORDS, OnInsertChords)
	ON_BN_CLICKED(IDC_HELP, OnHelp)
	ON_BN_CLICKED(IDC_LANGUAGE, OnLanguage)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SAVE_AS, OnSaveAs)
	ON_BN_CLICKED(IDC_SELECTSOURCE, OnSelectsource)
	ON_BN_CLICKED(IDC_FILLLYRICS, OnFilllyrics)
	ON_BN_CLICKED(IDC_LINEFEED_NEWPAGE, OnSelectFillLyricsLinefeed)
	ON_BN_CLICKED(IDC_XG_CONVERT, OnXgConvert)
	ON_BN_CLICKED(IDC_TEMPO, OnTempo)
	ON_BN_CLICKED(IDC_VOLUME, OnVolume)
	ON_BN_CLICKED(IDC_PLAY_BUTTON, OnPlayButton)
	ON_BN_CLICKED(IDC_PRINT, OnPrint)
	ON_BN_CLICKED(IDC_START_BEAT, OnStartBeat)
	ON_BN_CLICKED(IDC_QUANTISIZE_CHORDS, OnQuantisizeChords)
	ON_BN_CLICKED(IDC_VEL_COMPRESS, OnVelCompress)
	ON_BN_CLICKED(IDC_REVOICING, OnRevoicing)
	ON_BN_CLICKED(IDC_UNDO, OnUndo)
	ON_BN_CLICKED(IDC_SYSEX, OnSysex)
	ON_BN_CLICKED(IDC_LYRICS_AT_CHANNEL_NOTES, OnLyricsAtChannelNotes)
	ON_BN_CLICKED(IDC_CHORDS_LYRICS_IMPORT_EXPORT, OnChordsLyricsImportExport)
	ON_BN_CLICKED(IDC_CONTROLLER, OnController)
	ON_BN_CLICKED(IDC_EXTRAS, OnExtras)
	ON_BN_CLICKED(IDC_EXCHANGE_CHANNELS, OnExchangeChannels)
	ON_BN_CLICKED(IDC_QUANTISIZE_LYRICS, OnQuantisizeLyrics)
	ON_BN_CLICKED(IDC_CHORDS_LYRICS_EDITOR, OnLyricsChordsEditor)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_FILE_FORMAT, OnFileFormat)
	ON_BN_CLICKED(IDC_PREFERENCES, OnPreferences)
	ON_BN_CLICKED(IDC_SOURCE_CLOSE, OnSourceClose)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_DRUMS, OnDrums)
	ON_BN_CLICKED(IDC_CONVERT_GM, OnGmConvert)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PSRUTI_HELP, OnHelp)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_DELETE_FILL_LYRICS, OnDeleteFillLyrics)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipDlg Nachrichten-Handler


BOOL CPsrutiDlg::PreTranslateMessage(MSG* pMSG)
{
	if(pMSG->message == WM_KEYDOWN)
	{
		// ESC-Taste abfangen
		if(pMSG->wParam == VK_ESCAPE)
		{
			OnOK();
			return TRUE;
		}
	}

	if (NULL != m_pToolTip)
	{
		m_pToolTip->RelayEvent(pMSG);
	}
	return CDialog::PreTranslateMessage(pMSG);
}

void CPsrutiDlg::OnDropFiles(HDROP hDropInfo)
{
    UINT nFiles = ::DragQueryFile(hDropInfo, (UINT) -1, NULL, 0);
	if (nFiles == 1)
	{
        TCHAR szFileName[_MAX_PATH];
        ::DragQueryFile(hDropInfo, 0, szFileName, _MAX_PATH);
		load_dropped_file(szFileName);
    }
	::DragFinish(hDropInfo);
}


void CPsrutiDlg::fill_sourcefile_list_from_command_line()
{
	int no_zero = 0;
	int i;
	int k = 0;
	char temp_file_path[MAX_PATH];
	char long_file_path[MAX_PATH+512];
	sourcefile_list.clear();
	bool first_quote_arrived = false;
	int len = (int)strlen(command_line);

	bool shortname = false;

	for (i=0; i<len; i++)
	{
		if (command_line[i]=='\"')
		{
			if (!first_quote_arrived)
			{
				first_quote_arrived = true;
				continue;
			}
			else
			{
				first_quote_arrived = false;
				temp_file_path[k] = 0;
				if (shortname)
				{
					GetLongPathName(temp_file_path, long_file_path,512);
					strcpy(temp_file_path,long_file_path);
					shortname = false;
				}
				sourcefile_list.add(temp_file_path);
				k = 0;
				continue;
			}
		}

		if ((command_line[i]==' ')&&(!first_quote_arrived))
		{
			if (k==0) continue;
			temp_file_path[k] = 0;
			if (shortname)
			{
				GetLongPathName(temp_file_path, long_file_path,512);
				strcpy(temp_file_path,long_file_path);
				shortname = false;
			}
			sourcefile_list.add(temp_file_path);
			k = 0;
			continue;
		}

		temp_file_path[k] = command_line[i];
		if (command_line[i]=='~') shortname = true;
		k++;

		if (i == len-1)
		{
			temp_file_path[k] = 0;
			if (shortname)
			{
				GetLongPathName(temp_file_path, long_file_path,512);
				strcpy(temp_file_path,long_file_path);
				shortname = false;
			}
			sourcefile_list.add(temp_file_path);
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPsrutiDlg Nachrichten-Handler

BOOL CPsrutiDlg::OnInitDialog()
{

	CDialog::OnInitDialog();
	SetWindowText("PSRUTI");

	lf = new Log("psruti_log.txt");
	o_inifile = new IniFile;
	o_inifile->lf = lf;

	source_changed = false;
	pdlg = NULL;

	int i;

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// Find path for hlp-file and open
	char hlpfile_path[255];
	CString hlpfile;

	GetModuleFileName(GetModuleHandle(NULL), hlpfile_path, sizeof(hlpfile_path));
	for( i = strlen(hlpfile_path)-1; i>0; i--)
	{
		if (hlpfile_path[i]=='\\')
		{
			hlpfile_path[i] = '\0';
			break;
		}
	}
	strcat(hlpfile_path,"\\");
	hlpfile_germ = hlpfile_path + hlpfilename_germ;
	hlpfile_eng = hlpfile_path + hlpfilename_eng;

	// Language

	CString lang_str = o_inifile->get_language();

	if (lang_str=="GERMAN")
	{
		language = "GERMAN";
	}
	else
	{
		language = "ENGLISH";
	}

	// initialize midiport
	int id = GlobalUtilities::get_id(o_inifile->get_midiport());
	HP_SelectMIDIDevice(id);

/*
	// start with commandline?
	if (sourcefile[0] != 0x0)
	{
		CString scrpath = sourcefile;
		scrpath.MakeLower();
		scrpath = scrpath.Right(4);
		if ((scrpath==".mid")||(scrpath==".kar"))
		{
			initialize_source();
			if (hpmfi==NULL) return FALSE;
			source_changed = hpmfi->is_source_changed();
		}
	}
*/

	// start with commandline?
	fill_sourcefile_list_from_command_line();

	if (sourcefile_list.get_length() > 0)
	{
		sourcefile_list_index = 0;
		strcpy(sourcefile,sourcefile_list.get_name(sourcefile_list_index));
		sourcefile_list_index++;
		CString scrpath = sourcefile;
		scrpath.MakeLower();
		scrpath = scrpath.Right(4);
		if ((scrpath==".mid")||(scrpath==".kar"))
		{
			initialize_source();
			if (hpmfi==NULL) return FALSE;
			source_changed = hpmfi->is_source_changed();
		}
	}

	// Tool Tips
	m_pToolTip = new CToolTipCtrl;
	m_pToolTip->Create(this);
	m_pToolTip->SetDelayTime(TTDT_AUTOPOP,4000);
	m_pToolTip->SetMaxTipWidth(200);

	m_pToolTip->AddTool(&m_selectsource,GlobalUtilities::get_resource_string(IDS_SELECTSOURCE));
	m_pToolTip->AddTool(&m_save,GlobalUtilities::get_resource_string(IDS_SAVE));
	m_pToolTip->AddTool(&m_save_as,GlobalUtilities::get_resource_string(IDS_SAVE_AS));
	m_pToolTip->AddTool(&m_source_close,GlobalUtilities::get_resource_string(IDS_CLOSE));
	m_pToolTip->AddTool(&m_controller_effects,GlobalUtilities::get_resource_string(IDS_CONTROLLER_EFFECTS));
	m_pToolTip->AddTool(&m_extras,GlobalUtilities::get_resource_string(IDS_EXTRAS));
	m_pToolTip->AddTool(&m_transpose,GlobalUtilities::get_resource_string(IDS_TRANSPOSE));
	m_pToolTip->AddTool(&m_compute_chords,GlobalUtilities::get_resource_string(IDS_COMPUTE_CHORDS));
	m_pToolTip->AddTool(&m_insert_fill_lyrics,GlobalUtilities::get_resource_string(IDS_INSERT_FILL_LYRICS));
	m_pToolTip->AddTool(&m_select_fill_lyrics_linefeed,GlobalUtilities::get_resource_string(IDS_SELECT_FILL_LYRICS_LINEFEED));
	m_pToolTip->AddTool(&m_tempo,GlobalUtilities::get_resource_string(IDS_TEMPO));
	m_pToolTip->AddTool(&m_expr_mvolume,GlobalUtilities::get_resource_string(IDS_VOLUME));
	m_pToolTip->AddTool(&m_sysex_import_export,GlobalUtilities::get_resource_string(IDS_SYSEX_IMPORT_EXPORT));
	m_pToolTip->AddTool(&m_info,GlobalUtilities::get_resource_string(IDS_INFO));
	m_pToolTip->AddTool(&m_help,GlobalUtilities::get_resource_string(IDS_HELP));
	m_pToolTip->AddTool(&m_language,GlobalUtilities::get_resource_string(IDS_LANGUAGE));
	m_pToolTip->AddTool(&m_preferences,GlobalUtilities::get_resource_string(IDS_PREFERENCES));
	m_pToolTip->AddTool(&m_play,GlobalUtilities::get_resource_string(IDS_START_PLAY));
	m_pToolTip->AddTool(&m_exit,GlobalUtilities::get_resource_string(IDS_EXIT));
	m_pToolTip->AddTool(&m_xg_convert,GlobalUtilities::get_resource_string(IDS_XG_CONVERT));
	m_pToolTip->AddTool(&m_vel_compress,GlobalUtilities::get_resource_string(IDS_VEL_COMPRESS));
	m_pToolTip->AddTool(&m_print,GlobalUtilities::get_resource_string(IDS_PRINT));
	m_pToolTip->AddTool(&m_start_beat,GlobalUtilities::get_resource_string(IDS_START_BEAT));
	m_pToolTip->AddTool(&m_quantisize_chords,GlobalUtilities::get_resource_string(IDS_QUANTISIZE_CHORD));
	m_pToolTip->AddTool(&m_revoicing,GlobalUtilities::get_resource_string(IDS_REVOICING));
	m_pToolTip->AddTool(&m_lyrics_at_channel_notes,GlobalUtilities::get_resource_string(IDS_GLUE_LYRICS));
	m_pToolTip->AddTool(&m_chords_lyrics_import_export,GlobalUtilities::get_resource_string(IDS_CHORDS_LYRICS_IMPORT_EXPORT));
	m_pToolTip->AddTool(&m_exchange_channels,GlobalUtilities::get_resource_string(IDS_EXCHANGE_CHANNELS_TOOLTIP));
	m_pToolTip->AddTool(&m_quantisize_lyrics,GlobalUtilities::get_resource_string(IDS_QUANTISIZE_LYRICS));
	m_pToolTip->AddTool(&m_undo,GlobalUtilities::get_resource_string(IDS_UNDO));
	m_pToolTip->AddTool(&m_chord_lyric_editor,GlobalUtilities::get_resource_string(IDS_CHORD_LYRIC_EDITOR));
	m_pToolTip->AddTool(&m_file_format,GlobalUtilities::get_resource_string(IDS_FILE_FORMAT));
	m_pToolTip->AddTool(&m_drums,GlobalUtilities::get_resource_string(IDS_DRUMS));
	m_pToolTip->AddTool(&m_convert_gm,GlobalUtilities::get_resource_string(IDS_CONVERT_GM_TT));

	m_pToolTip->Activate(true);

	// Icons for SelectSource-Button
	HICON hIcon;
    hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
    m_selectsource.SetIcon(hIcon);
	m_undo.EnableWindow(false);
	m_selectsource.SetFocus(); // does not work

	// Drag and Drop
	CWnd::DragAcceptFiles(TRUE);

	
/*********************************************************************************/
/** SysEx XG effects from file Test **********************************************/
/*********************************************************************************/

/*
	CString effect;
	int msb, lsb, epl; 
	CString type;
	CString r;

	effect = "EffectReverb";
	DataReverbArray data_reverb_array;
	data_reverb_array.add(111,222,effect,333);
	data_reverb_array.get(0,&msb,&lsb,&type,&epl);
	r.Format("msb %i, lsb %i, type %s, epl %i",msb, lsb, type, epl);
	MessageBox(r);

	effect = "EffectChorus";
	DataChorusArray data_chorus_array;
	data_chorus_array.add(444,555,effect,666);
	data_chorus_array.get(0,&msb,&lsb,&type,&epl);
	r.Format("msb %i, lsb %i, type %s, epl %i",msb, lsb, type, epl);
	MessageBox(r);

	effect = "EffectDsps";
	DataChorusArray data_dsps_array;
	data_dsps_array.add(777,888,effect,999);
	data_dsps_array.get(0,&msb,&lsb,&type,&epl);
	r.Format("msb %i, lsb %i, type %s, epl %i",msb, lsb, type, epl);
	MessageBox(r);
*/

/*

	EffectParameterArray eff_param_array;

	EFF_PARAM_ELEM *test = eff_param_array.add(12);

//	eff_param_array.get(12, test);

	test[0].name = "0"; test[0].data_list = 0;
	test[1].name = "1"; test[1].data_list = 1;
	test[2].name = "2"; test[2].data_list = 2;
	test[3].name = "3"; test[3].data_list = 3;
	test[4].name = "4"; test[4].data_list = 4;
	test[5].name = "5"; test[5].data_list = 5;
	test[6].name = "6"; test[6].data_list = 6;
	test[7].name = "7"; test[7].data_list = 7;
	test[8].name = "8"; test[8].data_list = 8;
	test[9].name = "9"; test[9].data_list = 9;
	test[10].name = "10"; test[10].data_list = 10;
	test[11].name = "11"; test[11].data_list = 11;
	test[12].name = "12"; test[12].data_list = 12;
	test[13].name = "13"; test[13].data_list = 13;
	test[14].name = "14"; test[14].data_list = 14;
	test[15].name = "15"; test[15].data_list = 15;

	CString r;
	r.Format("name %s, data_list %i",test[12].name,test[12].data_list);
	MessageBox(r);

	EFF_PARAM_ELEM *test1 = eff_param_array.get(12);
	r.Format("name %s, data_list %i",test1[12].name,test1[12].data_list);
	MessageBox(r);
*/
/*
	EffectTableArray table_array;
	table_array.add();
	table_array.add();
	CString table[MAX_TABLE_LEN];

	table_array.get(1,table);
	table[0] = "table1/0";
	table[1] = "table1/1";

	CString r;
	r.Format("table1/0 = %s, table/1/1 = %s", table[0], table[1]);
	MessageBox(r);
*/

	
/*	
	
	{
		XgEffects *xg_effects = new XgEffects("C:/PSR8000/InsFiles/SysEditor_DataList_4.4xg");
		CArray<CString, CString> instruments;
		if (xg_effects->get_instruments(&instruments))
		{
			CString instrument;
			for (i=0; i<=instruments.GetUpperBound(); i++)
			{
				instrument = instruments.GetAt(i);
			}
			xg_effects->ReadEffectFile(instruments.GetAt(2)); // Tyros 3
		}
	

		int act_reverb_param_list_no;
		int act_reverb_type_msb;
		int act_reverb_type_lsb;
		CString act_type;
		CString text;
	
		int act_chorus_param_list_no;
		int act_chorus_type_msb;
		int act_chorus_type_lsb;

		int act_dsp_param_list_no;
		int act_dsp_type_msb;
		int act_dsp_type_lsb;

		
		CString r;

		text = "no text";

		xg_effects->reverb_effect_type(2,2,
									  &act_reverb_param_list_no,
									  &act_reverb_type_msb,
									  &act_reverb_type_lsb,
									  &act_type);
		text = xg_effects->reverb_data_text(0x02, // int AdrH
											0x05, // int AdrL
										    0x02, // = DataMSB 
											-1,   // = DataLSB
									       act_reverb_param_list_no);

		r.Format ("Reverb %s Param %s",act_type,text);
		MessageBox(r);

		text = "no text";

		xg_effects->chorus_effect_type(0x41,0x00,
									  &act_chorus_param_list_no,
									  &act_chorus_type_msb,
									  &act_chorus_type_lsb,
									  &act_type);
		text = xg_effects->chorus_data_text(0x02, // int AdrH
											0x23, // int AdrL
									        0x02, // = DataMSB of this sysex
										    -1,   // = DataLSB of this sysex 
									        act_chorus_param_list_no);

		r.Format ("Chorus %s Param %s",act_type,text);
		MessageBox(r);


		text = "no text";

		xg_effects->dsp_effect_type(	0x63,0x10,0x00,
  									&act_dsp_param_list_no,
									&act_dsp_type_msb,
									&act_dsp_type_lsb,
									&act_type);

		text = xg_effects->dsp_data_text(0x01, -1, 0x03, 0x01, 0x25, act_dsp_param_list_no);

		r.Format ("DSP %s Param %s",act_type,text);
		MessageBox(r);

		delete xg_effects;
	}
*/


/*********************************************************************************/
/**  End SysEx XG effects from file Test *****************************************/
/*********************************************************************************/
    return FALSE;
}

void CPsrutiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CPsrutiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// draw icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CPsrutiDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPsrutiDlg::OnInfo()
{
	CAboutDlg info;
	info.DoModal();
}


DWORD CPsrutiDlg::xg_convert_thread_run(CPsrutiDlg *this_thread)
{
	this_thread->xg_convert_folder();
	return 1; // Return with any value. The thread will be ended implicitely.
}

DWORD CPsrutiDlg::gm_convert_thread_run(CPsrutiDlg *this_thread)
{
	this_thread->gm_convert_folder();
	return 1; // Return with any value. The thread will be ended implicitely.
}

DWORD CPsrutiDlg::revoicefile_thread_run(CPsrutiDlg *this_thread)
{
	this_thread->revoicefile_folder();
	return 1; // Return with any value. The thread will be ended implicitely.
}

DWORD CPsrutiDlg::drum_thread_run(CPsrutiDlg *this_thread)
{
	this_thread->drum_folder();
	return 1; // Return with any value. The thread will be ended implicitely.
}

DWORD CPsrutiDlg::print_thread_run(CPsrutiDlg *this_thread)
{
	this_thread->print_folder();
	return 1; // Return with any value. The thread will be ended implicitely.
}

DWORD CPsrutiDlg::fileformat_thread_run(CPsrutiDlg *this_thread)
{
	this_thread->fileformat_folder();
	return 1; // Return with any value. The thread will be ended implicitely.
}

DWORD CPsrutiDlg::count_in_thread_run(CPsrutiDlg *this_thread)
{
	this_thread->count_in_folder();
	return 1; // Return with any value. The thread will be ended implicitely.
}

DWORD CPsrutiDlg::fill_lyric_thread_run(CPsrutiDlg *this_thread)
{
	this_thread->fill_lyric_folder();
	return 1; // Return with any value. The thread will be ended implicitely.
}

void CPsrutiDlg::OnHelp()
{
	CString hlpfile =
		(language=="GERMAN")?hlpfile_germ:(language=="ENGLISH")?hlpfile_eng:"";

	if (hlpfile != "")
	{
		ShellExecute(this->m_hWnd,"open",hlpfile,NULL,NULL,SW_SHOWNORMAL);

	}
}

void CPsrutiDlg::load_dropped_file(char* source)
{
	if (batch_running) return;
	if (hpmfi != NULL)	return;
	source_changed = false;
	strcpy(sourcefile,source);
	initialize_source();
	source_changed = (hpmfi==NULL)?false:hpmfi->is_source_changed();
}

void CPsrutiDlg::OnSelectsource()
{
	int i;

	if (batch_running) return;
	if (hpmfi != NULL)
	{
		if (HP_IsPlaying(hpmfi->mf))
		{
			Stop();
		}
	}

	if (source_changed)
	{
		SaveChangesDlg dlg;
		int result = dlg.DoModal();

		if (result == 1)
		{
			OnSaveAs();
			return;
		}
		if (result == -1)
		{
			return;
		}

		// result == 0: Save not wanted
	}

	source_changed = false;

	char BASED_CODE szFilter[] =
		"MIDI Files (*.mid)|*.mid|Karaoke Files (*.kar)|*.kar|All Files (*.*)|*.*||";

	// Clear Function-Texts

	CFileDialog openfile_dlg(TRUE,
						  "mid",
						  NULL,
						  OFN_FILEMUSTEXIST |
						  OFN_PATHMUSTEXIST,
						  szFilter,
						  NULL);

	// Get last_source
	CString last_source = o_inifile->get_sourcefile();

	if (last_source != "")
	{
	   openfile_dlg.m_ofn.lpstrInitialDir = last_source;
	   char ls[MAX_PATH];
	   for (i=0; i<last_source.GetLength(); i++)
	   {
		   ls[i] = last_source[i];
	   }
	   ls[last_source.GetLength()] = (char)0;
	   openfile_dlg.m_ofn.lpstrFile = ls;
	}

//	MessageBox(HP_GetVersion());

// Visual C++(6.0) CFileDialog DoModal() does not work with Debugging under Vista
// For debugging a midifile define DEBUG_SOURCE in CPsrutiDlg.cpp with a source path

#ifndef DEBUG_SOURCE
	int return_value = openfile_dlg.DoModal();
	if (return_value == IDOK)
	{
		strcpy(sourcefile,openfile_dlg.m_ofn.lpstrFile);
	}
	else if (return_value == IDCANCEL)
	{
		return;
	}
#endif

#if defined DEBUG_SOURCE	
	strcpy(sourcefile,DEBUG_SOURCE);
#endif

	if (hpmfi != NULL)
	{
		delete hpmfi;
		hpmfi = NULL;
	}

	initialize_source();
	source_changed = (hpmfi==NULL)?false:hpmfi->is_source_changed();
}

HPMF_Interface* CPsrutiDlg::Selectsource()
{
	OnSelectsource();
	return hpmfi;
}

void CPsrutiDlg::initialize_source()
{
	int i;

	char user1_beat_lyric[80];
	char user1_takt_lyric[80];
	char user1_end_lyric[80];
	int  user1_linefeedlyrictick;
	char user2_beat_lyric[80];
	char user2_takt_lyric[80];
	char user2_end_lyric[80];
	int  user2_linefeedlyrictick;
	char user3_beat_lyric[80];
	char user3_takt_lyric[80];
	char user3_end_lyric[80];
	int  user3_linefeedlyrictick;
	int is_user;
	char linefeed_char = GlobalUtilities::get_linefeed_char();

	CString tl, bl, el;

	SetDlgItemText(IDC_FILENAME,"");
	Invalidate();   
	UpdateWindow();

	//
	// Read sourcefile
	//

    // Set the predefined Windows "Wait" cursor.
	SetCursor(hCursorWait);

	hpmfi = new HPMF_Interface(lf,sourcefile,o_inifile);
	
	if (hpmfi->bad_error)
	{
		delete hpmfi;
		hpmfi = NULL;
		SetDlgItemText(IDC_FILENAME,"");
		SetCursor(hCursorOld);
		return;
	}

	if (hpmfi->with_additional_chunks && !batch_running)
	{
		CString r = GlobalUtilities::get_resource_string(IDS_MORE_CHUNKS);
		::MessageBox(AfxGetMainWnd()->m_hWnd,r,"",MB_OK|MB_TASKMODAL);
	}

	//
	// Fill Lyrics user1
	//

	// initalize user1_takt_lyric
	tl = o_inifile->get_user1_taktlyric();
	if (tl == "default")
	{
		tl = GlobalUtilities::init_takt_lyric;
		o_inifile->set_user1_taktlyric(GlobalUtilities::convert_string_to_printable(tl));
	}
	else
	{
		tl = GlobalUtilities::convert_printable_to_string(tl,linefeed_char);
	}

	for (i=0; i<tl.GetLength(); i++)
	{
		user1_takt_lyric[i] = tl[i];
	}

	user1_takt_lyric[tl.GetLength()] = 0x00;

	// initialize user1_beat_lyric
	bl = o_inifile->get_user1_beatlyric();
	if (bl == "default")
	{
		bl = GlobalUtilities::init_beat_lyric;
		o_inifile->set_user1_beatlyric(GlobalUtilities::convert_string_to_printable(bl));
	}
	else
	{
		bl = GlobalUtilities::convert_printable_to_string(bl,linefeed_char);
	}

	for (i=0; i<bl.GetLength(); i++)
	{
		user1_beat_lyric[i] = bl[i];
	}
	user1_beat_lyric[bl.GetLength()] = 0x00;

	// initialize user1_end_lyric
	el = o_inifile->get_user1_endlyric();
	if (el == "default")
	{
		el = GlobalUtilities::init_end_lyric;
		o_inifile->set_user1_endlyric(GlobalUtilities::convert_string_to_printable(el));
	}
	else
	{
		el = GlobalUtilities::convert_printable_to_string(el,linefeed_char);
	}

	for (i=0; i<el.GetLength(); i++)
	{
		user1_end_lyric[i] = el[i];
	}
	user1_end_lyric[el.GetLength()] = 0x00;

	// initalize linefeedlyrictick
	user1_linefeedlyrictick = o_inifile->get_user1_linefeedlyrictick();

	// send fill-lyric-dat of inifile to instance of HPMF_Interface
	hpmfi->set_user1_fill_lyric_data(user1_takt_lyric, user1_beat_lyric, user1_end_lyric, user1_linefeedlyrictick);


	//
	// Fill Lyrics user2
	//

	// initalize user2_takt_lyric
	tl = o_inifile->get_user2_taktlyric();
	if (tl == "default")
	{
		tl = GlobalUtilities::init_takt_lyric;
		o_inifile->set_user2_taktlyric(GlobalUtilities::convert_string_to_printable(tl));
	}
	else
	{
		tl = GlobalUtilities::convert_printable_to_string(tl,linefeed_char);
	}

	for (i=0; i<tl.GetLength(); i++)
	{
		user2_takt_lyric[i] = tl[i];
	}

	user2_takt_lyric[tl.GetLength()] = 0x00;

	// initialize user2_beat_lyric
	bl = o_inifile->get_user2_beatlyric();
	if (bl == "default")
	{
		bl = GlobalUtilities::init_beat_lyric;
		o_inifile->set_user2_beatlyric(GlobalUtilities::convert_string_to_printable(bl));
	}
	else
	{
		bl = GlobalUtilities::convert_printable_to_string(bl,linefeed_char);
	}

	for (i=0; i<bl.GetLength(); i++)
	{
		user2_beat_lyric[i] = bl[i];
	}
	user2_beat_lyric[bl.GetLength()] = 0x00;

	// initialize user2_end_lyric
	el = o_inifile->get_user2_endlyric();
	if (el == "default")
	{
		el = GlobalUtilities::init_end_lyric;
		o_inifile->set_user2_endlyric(GlobalUtilities::convert_string_to_printable(el));
	}
	else
	{
		el = GlobalUtilities::convert_printable_to_string(el,linefeed_char);
	}

	for (i=0; i<el.GetLength(); i++)
	{
		user2_end_lyric[i] = el[i];
	}
	user2_end_lyric[el.GetLength()] = 0x00;

	// initalize linefeedlyrictick
	user2_linefeedlyrictick = o_inifile->get_user2_linefeedlyrictick();

	// send fill-lyric-dat of inifile to instance of HPMF_Interface
	hpmfi->set_user2_fill_lyric_data(user2_takt_lyric, user2_beat_lyric, user2_end_lyric, user2_linefeedlyrictick);
	
	//
	// Fill Lyrics user3
	//

	// initalize user3_takt_lyric
	tl = o_inifile->get_user3_taktlyric();
	if (tl == "default")
	{
		tl = GlobalUtilities::init_takt_lyric;
		o_inifile->set_user3_taktlyric(GlobalUtilities::convert_string_to_printable(tl));
	}
	else
	{
		tl = GlobalUtilities::convert_printable_to_string(tl,linefeed_char);
	}

	for (i=0; i<tl.GetLength(); i++)
	{
		user3_takt_lyric[i] = tl[i];
	}

	user3_takt_lyric[tl.GetLength()] = 0x00;

	// initialize user3_beat_lyric
	bl = o_inifile->get_user3_beatlyric();
	if (bl == "default")
	{
		bl = GlobalUtilities::init_beat_lyric;
		o_inifile->set_user3_beatlyric(GlobalUtilities::convert_string_to_printable(bl));
	}
	else
	{
		bl = GlobalUtilities::convert_printable_to_string(bl,linefeed_char);
	}

	for (i=0; i<bl.GetLength(); i++)
	{
		user3_beat_lyric[i] = bl[i];
	}
	user3_beat_lyric[bl.GetLength()] = 0x00;

	// initialize user3_end_lyric
	el = o_inifile->get_user3_endlyric();
	if (el == "default")
	{
		el = GlobalUtilities::init_end_lyric;
		o_inifile->set_user3_endlyric(GlobalUtilities::convert_string_to_printable(el));
	}
	else
	{
		el = GlobalUtilities::convert_printable_to_string(el,linefeed_char);
	}

	for (i=0; i<el.GetLength(); i++)
	{
		user3_end_lyric[i] = el[i];
	}
	user3_end_lyric[el.GetLength()] = 0x00;

	// initalize linefeedlyrictick
	user3_linefeedlyrictick = o_inifile->get_user3_linefeedlyrictick();

	// send fill-lyric-dat of inifile to instance of HPMF_Interface
	hpmfi->set_user3_fill_lyric_data(user3_takt_lyric, user3_beat_lyric, user3_end_lyric, user3_linefeedlyrictick);


	// initalize is_user
	is_user = o_inifile->get_user();

	hpmfi->set_is_user(is_user);
	
	// Insert sourcefile in psruti.ini
	o_inifile->set_sourcefile(sourcefile);

	free_saved_state();

	// Set the old cursor back
	SetCursor(hCursorOld);

	set_new_sourcefile(sourcefile);
	strcpy(destfile,sourcefile);
	m_destination = "";
	Invalidate();   
	UpdateWindow();

	// Drag and Drop not allowed
	CWnd::DragAcceptFiles(FALSE);
}

void CPsrutiDlg::set_new_sourcefile(CString new_sourcefile)
{
	m_filename = new_sourcefile;

	// shorten sourcefile to max 70 chars
	CString sourcename = new_sourcefile; // convert to CString
	CString short_sourcename = sourcename;
	if (sourcename.GetLength()>70)
	{
		short_sourcename = "..."+sourcename.Right(67);
	}
	SetDlgItemText(IDC_FILENAME,short_sourcename);
}

void CPsrutiDlg::xg_convert_folder()
{
	CString source_title = GlobalUtilities::get_resource_string(IDS_SOURCE_FOLDER);
	CString dest_title = GlobalUtilities::get_resource_string(IDS_DEST_FOLDER);
	char sel_path[MAX_PATH];

	// source folder
	
	ITEMIDLIST *sourceitemidlist;
	BROWSEINFO path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		source_title, // Select the path for source-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	sourceitemidlist = SHBrowseForFolder(&path_info);
	if(!SHGetPathFromIDList(sourceitemidlist,sel_path))
	{
		return;
	}
	
	// Conversion to CString
	CString selected_source_path = (CString)sel_path;

	// destination folder
	ITEMIDLIST *destitemidlist;
	BROWSEINFO dest_path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		dest_title, // Select the path for the destination-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	destitemidlist = SHBrowseForFolder(&dest_path_info);
	if(!SHGetPathFromIDList(destitemidlist,sel_path))
	{
		return;
	}

	CString selected_dest_path = (CString)sel_path;
	
	int last_index = selected_source_path.GetLength()-1;
	if (selected_source_path.GetAt(last_index)=='\\')
	{
		selected_source_path = selected_source_path.Left(last_index);
	}


	// Look for midifiles
	CFileFind mid_finder;
	if (mid_finder.FindFile(selected_source_path+"\\"+"*.mid"))
	{
		int nextfile;
		while (true)
		{
			if (xg_convert_folder_abort_wanted)
			{
				break;
			}
			nextfile = mid_finder.FindNextFile();
			CString midifile = mid_finder.GetFilePath();
			xg_convert_folder_file(midifile,selected_dest_path);
			if (nextfile==0) break;
		}
	}

	// Look for kar-files
	CFileFind kar_finder;
	if (!kar_finder.FindFile(selected_source_path+"\\"+"*.kar"))
	{
		return;
	}
	else
	{
		int nextfile;
		while (true)
		{
			if (xg_convert_folder_abort_wanted)
			{
				break;
			}
			nextfile = kar_finder.FindNextFile();
			CString midifile = kar_finder.GetFilePath();
			xg_convert_folder_file(midifile,selected_dest_path);
			if (nextfile==0) break;
		}
	}
}

void CPsrutiDlg::gm_convert_folder()
{
	CString source_title = GlobalUtilities::get_resource_string(IDS_SOURCE_FOLDER);
	CString dest_title = GlobalUtilities::get_resource_string(IDS_DEST_FOLDER);
	char sel_path[MAX_PATH];

	// source folder
	
	ITEMIDLIST *sourceitemidlist;
	BROWSEINFO path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		source_title, // Select the path for source-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	sourceitemidlist = SHBrowseForFolder(&path_info);
	if(!SHGetPathFromIDList(sourceitemidlist,sel_path))
	{
		return;
	}
	
	// Conversion to CString
	CString selected_source_path = (CString)sel_path;

	// destination folder
	ITEMIDLIST *destitemidlist;
	BROWSEINFO dest_path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		dest_title, // Select the path for the destination-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	destitemidlist = SHBrowseForFolder(&dest_path_info);
	if(!SHGetPathFromIDList(destitemidlist,sel_path))
	{
		return;
	}

	CString selected_dest_path = (CString)sel_path;
	
	int last_index = selected_source_path.GetLength()-1;
	if (selected_source_path.GetAt(last_index)=='\\')
	{
		selected_source_path = selected_source_path.Left(last_index);
	}


	// Look for midifiles
	CFileFind mid_finder;
	if (mid_finder.FindFile(selected_source_path+"\\"+"*.mid"))
	{
		int nextfile;
		while (true)
		{
			if (gm_convert_folder_abort_wanted)
			{
				break;
			}
			nextfile = mid_finder.FindNextFile();
			CString midifile = mid_finder.GetFilePath();
			gm_convert_folder_file(midifile,selected_dest_path);
			if (nextfile==0) break;
		}
	}

	// Look for kar-files
	CFileFind kar_finder;
	if (!kar_finder.FindFile(selected_source_path+"\\"+"*.kar"))
	{
		return;
	}
	else
	{
		int nextfile;
		while (true)
		{
			if (gm_convert_folder_abort_wanted)
			{
				break;
			}
			nextfile = kar_finder.FindNextFile();
			CString midifile = kar_finder.GetFilePath();
			gm_convert_folder_file(midifile,selected_dest_path);
			if (nextfile==0) break;
		}
	}
}

void CPsrutiDlg::xg_convert_folder_file(CString midifile,CString dest_path)
{
	int i;
	for (i=0; i<midifile.GetLength();i++)
	{
		sourcefile[i] = midifile.GetAt(i);
	}
	sourcefile[i] = 0x00;
	initialize_source();
	if (hpmfi == NULL) return;
	set_new_sourcefile(midifile);

	int no_double_notes;
	int no_pitch_wheels;
	hpmfi->eval_xg_convert(&no_double_notes,&no_pitch_wheels);

	midifile = midifile.Left(midifile.GetLength()-4);
	char title[MAX_PATH];
	GetFileTitle(midifile,title,MAX_PATH);
	CString destination = dest_path+"\\";
	destination += title;
	destination += ".mid";

	hpmfi->eval_save(destination);
	if (hpmfi != NULL)
	{
		delete hpmfi;
		hpmfi = NULL;
	}
}

void CPsrutiDlg::gm_convert_folder_file(CString midifile,CString dest_path)
{
	int i;
	for (i=0; i<midifile.GetLength();i++)
	{
		sourcefile[i] = midifile.GetAt(i);
	}
	sourcefile[i] = 0x00;
	initialize_source();
	if (hpmfi == NULL) return;
	set_new_sourcefile(midifile);

	hpmfi->eval_gm_convert();

	midifile = midifile.Left(midifile.GetLength()-4);
	char title[MAX_PATH];
	GetFileTitle(midifile,title,MAX_PATH);
	CString destination = dest_path+"\\";
	destination += title;
	destination += ".mid";

	hpmfi->eval_save(destination);
	if (hpmfi != NULL)
	{
		delete hpmfi;
		hpmfi = NULL;
	}
}

void CPsrutiDlg::revoicefile_folder()
{
	CString source_title = GlobalUtilities::get_resource_string(IDS_SOURCE_FOLDER);
	CString dest_title = GlobalUtilities::get_resource_string(IDS_DEST_FOLDER);
	char sel_path[MAX_PATH];
	char revoicefile[MAX_PATH];

	if (!ask_for_revoicefile(revoicefile))
	{
		return;
	}


	// source folder
	
	ITEMIDLIST *sourceitemidlist;
	BROWSEINFO path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		source_title, // Select the path for source-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	sourceitemidlist = SHBrowseForFolder(&path_info);
	if(!SHGetPathFromIDList(sourceitemidlist,sel_path))
	{
		return;
	}
	
	// Conversion to CString
	CString selected_source_path = (CString)sel_path;

	// destination folder
	ITEMIDLIST *destitemidlist;
	BROWSEINFO dest_path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		dest_title, // Select the path for the destination-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	destitemidlist = SHBrowseForFolder(&dest_path_info);
	if(!SHGetPathFromIDList(destitemidlist,sel_path))
	{
		return;
	}

	CString selected_dest_path = (CString)sel_path;
	
	int last_index = selected_source_path.GetLength()-1;
	if (selected_source_path.GetAt(last_index)=='\\')
	{
		selected_source_path = selected_source_path.Left(last_index);
	}


	// Look for midifiles
	CFileFind mid_finder;
	if (mid_finder.FindFile(selected_source_path+"\\"+"*.mid"))
	{
		int nextfile;
		while (true)
		{
			if (revoicefile_folder_abort_wanted)
			{
				break;
			}
			nextfile = mid_finder.FindNextFile();
			CString midifile = mid_finder.GetFilePath();
			revoicefile_folder_file(midifile,revoicefile,selected_dest_path);
			if (nextfile==0) break;
		}
	}

	// Look for kar-files
	CFileFind kar_finder;
	if (!kar_finder.FindFile(selected_source_path+"\\"+"*.kar"))
	{
		return;
	}
	else
	{
		int nextfile;
		while (true)
		{
			if (revoicefile_folder_abort_wanted)
			{
				break;
			}
			nextfile = kar_finder.FindNextFile();
			CString midifile = kar_finder.GetFilePath();
			revoicefile_folder_file(midifile,revoicefile,selected_dest_path);
			if (nextfile==0) break;
		}
	}
}


void CPsrutiDlg::drum_folder()
{

	CString source_title = GlobalUtilities::get_resource_string(IDS_SOURCE_FOLDER);
	CString dest_title = GlobalUtilities::get_resource_string(IDS_DEST_FOLDER);
	char sel_path[MAX_PATH];
	char drumfile[MAX_PATH];

	if (!ask_for_drumfile(drumfile))
	{
		return;
	}


	// source folder
	
	ITEMIDLIST *sourceitemidlist;
	BROWSEINFO path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		source_title, // Select the path for source-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	sourceitemidlist = SHBrowseForFolder(&path_info);
	if(!SHGetPathFromIDList(sourceitemidlist,sel_path))
	{
		return;
	}
	
	// Conversion to CString
	CString selected_source_path = (CString)sel_path;

	// destination folder
	ITEMIDLIST *destitemidlist;
	BROWSEINFO dest_path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		dest_title, // Select the path for the destination-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	destitemidlist = SHBrowseForFolder(&dest_path_info);
	if(!SHGetPathFromIDList(destitemidlist,sel_path))
	{
		return;
	}

	CString selected_dest_path = (CString)sel_path;
	
	int last_index = selected_source_path.GetLength()-1;
	if (selected_source_path.GetAt(last_index)=='\\')
	{
		selected_source_path = selected_source_path.Left(last_index);
	}

	// Look for midifiles
	CFileFind mid_finder;
	if (mid_finder.FindFile(selected_source_path+"\\"+"*.mid"))
	{
		int nextfile;
		while (true)
		{
			if (drum_folder_abort_wanted)
			{
				break;
			}
			nextfile = mid_finder.FindNextFile();
			CString midifile = mid_finder.GetFilePath();
			if (!drum_folder_file(midifile,drumfile,selected_dest_path))
			{
				break;
			}
			if (nextfile==0) break;
		}
	}

	// Look for kar-files
	CFileFind kar_finder;
	if (!kar_finder.FindFile(selected_source_path+"\\"+"*.kar"))
	{
		return;
	}
	else
	{
		int nextfile;
		while (true)
		{
			if (drum_folder_abort_wanted)
			{
				break;
			}
			nextfile = kar_finder.FindNextFile();
			CString midifile = kar_finder.GetFilePath();
			drum_folder_file(midifile,drumfile,selected_dest_path);
			if (nextfile==0) break;
		}
	}

}

bool CPsrutiDlg::drum_folder_file(CString midifile, char* drumfile, CString dest_path)
{
	bool result = true;
	int i;
	for (i=0; i<midifile.GetLength();i++)
	{
		sourcefile[i] = midifile.GetAt(i);
	}
	sourcefile[i] = 0x00;
	initialize_source();
	if (hpmfi == NULL) return false;

	if (!hpmfi->eval_drum_from_file(drumfile,drum_folder_running))
	{
		result = false;
	}

	midifile = midifile.Left(midifile.GetLength()-4);
	char title[MAX_PATH];
	GetFileTitle(midifile,title,MAX_PATH);
	CString destination = dest_path+"\\";
	destination += title;
	destination += ".mid";

	hpmfi->eval_save(destination);
	if (hpmfi != NULL)
	{
		delete hpmfi;
		hpmfi = NULL;
	}
	return result;
}


void CPsrutiDlg::revoicefile_folder_file(CString midifile,char* revoicefile,CString dest_path)
{
	int i;
	for (i=0; i<midifile.GetLength();i++)
	{
		sourcefile[i] = midifile.GetAt(i);
	}
	sourcefile[i] = 0x00;
	initialize_source();
	if (hpmfi == NULL) return;

	hpmfi->eval_revoice_from_file(revoicefile);

	midifile = midifile.Left(midifile.GetLength()-4);
	char title[MAX_PATH];
	GetFileTitle(midifile,title,MAX_PATH);
	CString destination = dest_path+"\\";
	destination += title;
	destination += ".mid";

	hpmfi->eval_save(destination);
	if (hpmfi != NULL)
	{
		delete hpmfi;
		hpmfi = NULL;
	}
}

void CPsrutiDlg::print_folder()
{
	CString source_title = GlobalUtilities::get_resource_string(IDS_SOURCE_FOLDER_PRINT);
	CString dest_title = GlobalUtilities::get_resource_string(IDS_DEST_FOLDER_PRINT);
	char sel_path[MAX_PATH];

	// source folder
	
	ITEMIDLIST *sourceitemidlist;
	BROWSEINFO path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		source_title, // Select the path for source-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	sourceitemidlist = SHBrowseForFolder(&path_info);
	if(!SHGetPathFromIDList(sourceitemidlist,sel_path))
	{
		return;
	}
	
	// Conversion to CString
	CString selected_source_path = (CString)sel_path;

	// destination folder
	ITEMIDLIST *destitemidlist;
	BROWSEINFO dest_path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		dest_title, // Select the path for the destination-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	destitemidlist = SHBrowseForFolder(&dest_path_info);
	if(!SHGetPathFromIDList(destitemidlist,sel_path))
	{
		return;
	}

	CString selected_dest_path = (CString)sel_path;
	
	int last_index = selected_source_path.GetLength()-1;
	if (selected_source_path.GetAt(last_index)=='\\')
	{
		selected_source_path = selected_source_path.Left(last_index);
	}


	// Look for midifiles
	CFileFind mid_finder;
	if (mid_finder.FindFile(selected_source_path+"\\"+"*.mid"))
	{
		int nextfile;
		while (true)
		{
			if (print_folder_abort_wanted)
			{
				break;
			}
			nextfile = mid_finder.FindNextFile();
			CString midifile = mid_finder.GetFilePath();
			print_folder_file(midifile,selected_dest_path);
			if (nextfile==0) break;
		}
	}

	// Look for kar-files
	CFileFind kar_finder;
	if (!kar_finder.FindFile(selected_source_path+"\\"+"*.kar"))
	{
		return;
	}
	else
	{
		int nextfile;
		while (true)
		{
			if (print_folder_abort_wanted)
			{
				break;
			}
			nextfile = kar_finder.FindNextFile();
			CString midifile = kar_finder.GetFilePath();
			print_folder_file(midifile,selected_dest_path);
			if (nextfile==0) break;
		}
	}
}

void CPsrutiDlg::print_folder_file(CString midifile,CString dest_path)
{
	int i;
	for (i=0; i<midifile.GetLength();i++)
	{
		sourcefile[i] = midifile.GetAt(i);
	}
	sourcefile[i] = 0x00;
	initialize_source();
	if (hpmfi == NULL) return;

	CPrint *print= new CPrint(hpmfi);

	CString protfile = midifile.Left(midifile.GetLength()-4);
	char title[MAX_PATH];
	GetFileTitle(protfile,title,MAX_PATH);
	CString destination = dest_path+"\\";
	destination += title;
	destination += ".txt";
	if (destination!="")
	{
		print->print(destination, false); // print and do not show textfile
	}

	delete print;
	print = NULL;

	if (hpmfi != NULL)
	{
		delete hpmfi;
		hpmfi = NULL;
	}
}

void CPsrutiDlg::fileformat_folder_file(CString midifile,CStdioFile *pf_f)
{
	int i;
	for (i=0; i<midifile.GetLength();i++)
	{
		sourcefile[i] = midifile.GetAt(i);
	}
	sourcefile[i] = 0x00;
	initialize_source();
	if (hpmfi == NULL) return;
	set_new_sourcefile(midifile);

	CString sourcefile_cstring;
	CString songname;
	CString copyright;
	bool with_additional_chunks;
	CString format;
	CString sub_format;
	int ppqn;
	CString takt;
	double tempo;
	CString key;
	bool lyrics;
	bool chords;
	bool count_in;
	int no_measures, duration;
	CString vh_channels;

	hpmfi->source_attributes(&sourcefile_cstring, &songname, &copyright, &with_additional_chunks, &format,&sub_format,
		&ppqn,&takt,&tempo,&key,&lyrics,&chords,&count_in,&no_measures,&duration,&vh_channels);
	
	CString text, r;
	CString tab = "\t";

	// Sourcefile

	text = sourcefile_cstring;

	// Songname

	if (songname != "")
	{
		text += " (" + songname + ")";
	}

	if(with_additional_chunks)
	{
		text += ", "+ GlobalUtilities::get_resource_string(IDS_MORE_CHUNKS_SHORT);
	}


	text += "\n";

	pf_f->WriteString(text);

	// Copyright

	text = "Copyright: ";
	text += copyright;
	text += "\n\n";

	pf_f->WriteString(text);

	// Format

	//	text+= format +"/" + sub_format + tab;
	text = format +"/" + sub_format + "  ";

	// PPQN

	r.Format("%-4i",hpmfi->original_ppqn);
	text+= r + "   ";

	// Timesignature (Takt)

	text+= takt + "    ";

/* Test
CString r1;
r1.Format("takt %s, length %i",takt, takt.GetLength());
MessageBox (r1);
*/

	// Tempo

	if (tempo != -1.0) 
	{
		r.Format("%-6.2f",tempo);
	}
	else
	{
		r = "--  ";
	}

	text+= r + "   ";

	// Keysignature (key)

	text+= key + "         ";

	// Lyrics

	text += (lyrics?GlobalUtilities::get_resource_string(IDS_YES):
		GlobalUtilities::get_resource_string(IDS_NO)) + "       ";

	// Chords

	text += (chords?GlobalUtilities::get_resource_string(IDS_YES):
		GlobalUtilities::get_resource_string(IDS_NO)) + "         ";

	// VH channels

	text += vh_channels +"        ";


	// Score channels

	{
		int score_chan_left;
		int score_chan_right;
		CString rl, rr;
		hpmfi->get_scorechan(&score_chan_left, &score_chan_right);

		if (score_chan_left >=0)
		{
			rl.Format("L = %-2i, ",score_chan_left+1);
		}
		else 
		{
			rl.Format("L = %s, ","--");
		}

		if (score_chan_right >=0)
		{
			rr.Format("R = %-2i",score_chan_right+1);
		}
		else 
		{
			rr.Format("R = %s","--");
		}

		text+= rl +rr + "     ";
	}


	// CountIn


	text += (count_in?GlobalUtilities::get_resource_string(IDS_YES):
		GlobalUtilities::get_resource_string(IDS_NO)) + "         ";

	
	// Measures

	r.Format("%-3i",no_measures);
	text+= r + "        ";

	// Duration

	r.Format("%i:%2.2i min",duration/60,duration%60);
	text+= r + "\n\n"; 
	pf_f->WriteString(text);

	text = "===================================================================================\n\n";
	
	pf_f->WriteString(text);

	if (hpmfi != NULL)
	{
		delete hpmfi;
		hpmfi = NULL;
	}
}

void CPsrutiDlg::fileformat_folder()
{

	CString source_title = GlobalUtilities::get_resource_string(IDS_SOURCE_FOLDER_FILEFORMAT);
	char sel_path[MAX_PATH];

	// source folder
	
	ITEMIDLIST *sourceitemidlist;
	BROWSEINFO path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		source_title, // Select the path for source-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	sourceitemidlist = SHBrowseForFolder(&path_info);
	if(!SHGetPathFromIDList(sourceitemidlist,sel_path))
	{
		return;
	}
	
	// Conversion to CString
	CString selected_source_path = (CString)sel_path;

	CString protfile = GlobalUtilities::SelectProtFile(o_inifile->get_protfile());
	if (protfile!="")
	{
		o_inifile->set_protfile(protfile);
	}

	CStdioFile *pf_f;
	CFileException e;
	CFileStatus status;
	
	if (CFile::GetStatus( protfile,status))
	{
		CFile::Remove(protfile);
	}
	
	pf_f = new CStdioFile;
	if (!pf_f->Open(protfile, CFile::modeCreate | CFile::modeNoTruncate | 
		CFile::modeReadWrite | CFile::shareExclusive, &e))
	{
		return;
    }
	
	pf_f->SetLength(0);
	pf_f->SeekToBegin();

	CString first_line = 
		GlobalUtilities::get_resource_string(IDS_CURRENT_FOLDER) + 	
		":  " + selected_source_path + " \n\n";

	first_line += GlobalUtilities::get_resource_string(IDS_FILE_DATA_TEXT) + "\n\n";
/*		
	first_line += "Format       ";
	first_line += "PPQN  "; 
	first_line += GlobalUtilities::get_resource_string(IDS_TIME) + "     ";
	first_line += "Tempo     "; 
	first_line += GlobalUtilities::get_resource_string(IDS_KEY) + "      ";
	first_line += "Lyrics     "; 
	first_line += GlobalUtilities::get_resource_string(IDS_CHORDS) + "     ";
	first_line += GlobalUtilities::get_resource_string(IDS_VH_CH) + "          ";
	first_line += GlobalUtilities::get_resource_string(IDS_SCORE_CHANNELS) + "            ";
	first_line += GlobalUtilities::get_resource_string(IDS_COUNT_IN) + "       ";
	first_line += GlobalUtilities::get_resource_string(IDS_NO_MEASURES) + "       ";
	first_line += GlobalUtilities::get_resource_string(IDS_DURATION) + "\n\n";
*/	
	pf_f->WriteString(first_line);

	int last_index = selected_source_path.GetLength()-1;
	if (selected_source_path.GetAt(last_index)=='\\')
	{
		selected_source_path = selected_source_path.Left(last_index);
	}

	// Look for midifiles
	CFileFind mid_finder;
	if (mid_finder.FindFile(selected_source_path+"\\"+"*.mid"))
	{
		int nextfile;
		while (true)
		{
			if (fileformat_folder_abort_wanted)
			{
				break;
			}
			nextfile = mid_finder.FindNextFile();
			CString midifile = mid_finder.GetFilePath();
			fileformat_folder_file(midifile,pf_f);
			if (nextfile==0) break;
		}
	}

	// Look for kar-files
	CFileFind kar_finder;
	if (kar_finder.FindFile(selected_source_path+"\\"+"*.kar"))
	{
		int nextfile;
		while (true)
		{
			if (fileformat_folder_abort_wanted)
			{
				break;
			}
			nextfile = kar_finder.FindNextFile();
			CString midifile = kar_finder.GetFilePath();
			fileformat_folder_file(midifile,pf_f);
			if (nextfile==0) break;
		}
	}
	pf_f->Close();

    ShellExecute(this->m_hWnd,"open",protfile,NULL,NULL,SW_SHOWNORMAL);
}

void CPsrutiDlg::count_in_folder()
{	
	if (count_in_dlg == NULL) return;
	bool start_beat_delete = count_in_dlg->get_start_beat_delete();
	int drum = count_in_dlg->get_drum();
	int velocity = count_in_dlg->get_velocity();
	int time_first_note = -1;
	bool on_all_beats = count_in_dlg->on_all_beats;
	bool only_one_measure = count_in_dlg->only_one_measure;

	CString source_title = GlobalUtilities::get_resource_string(IDS_SOURCE_FOLDER_EXECUTE);
	CString dest_title = GlobalUtilities::get_resource_string(IDS_DEST_FOLDER_EXECUTE);
	char sel_path[MAX_PATH];

	// source folder
	
	ITEMIDLIST *sourceitemidlist;
	BROWSEINFO path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		source_title, // Select the path for source-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	sourceitemidlist = SHBrowseForFolder(&path_info);
	if(!SHGetPathFromIDList(sourceitemidlist,sel_path))
	{
		return;
	}
	
	// Conversion to CString
	CString selected_source_path = (CString)sel_path;

	// destination folder
	ITEMIDLIST *destitemidlist;
	BROWSEINFO dest_path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		dest_title, // Select the path for the destination-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	destitemidlist = SHBrowseForFolder(&dest_path_info);
	if(!SHGetPathFromIDList(destitemidlist,sel_path))
	{
		return;
	}

	CString selected_dest_path = (CString)sel_path;
	
	int last_index = selected_source_path.GetLength()-1;
	if (selected_source_path.GetAt(last_index)=='\\')
	{
		selected_source_path = selected_source_path.Left(last_index);
	}


	// Look for midifiles
	CFileFind mid_finder;
	if (mid_finder.FindFile(selected_source_path+"\\"+"*.mid"))
	{
		int nextfile;
		while (true)
		{
			if (count_in_folder_abort_wanted)
			{
				break;
			}
			nextfile = mid_finder.FindNextFile();
			CString midifile = mid_finder.GetFilePath();
			count_in_folder_file(midifile,selected_dest_path,start_beat_delete,
				time_first_note, drum, velocity,on_all_beats, only_one_measure);
			if (nextfile==0) break;
		}
	}

	// Look for kar-files
	CFileFind kar_finder;
	if (!kar_finder.FindFile(selected_source_path+"\\"+"*.kar"))
	{
		return;
	}
	else
	{
		int nextfile;
		while (true)
		{
			if (count_in_folder_abort_wanted)
			{
				break;
			}
			nextfile = kar_finder.FindNextFile();
			CString midifile = kar_finder.GetFilePath();
			count_in_folder_file(midifile,selected_dest_path,start_beat_delete,
				time_first_note, drum, velocity,on_all_beats, only_one_measure);
			if (nextfile==0) break;
		}
	}
}


void CPsrutiDlg::count_in_folder_file(CString midifile,CString dest_path,
									  bool start_beat_delete, int time_first_note,
									  int drum, int velocity,bool on_all_beats, bool only_one_measure)
{
	int i;
	for (i=0; i<midifile.GetLength();i++)
	{
		sourcefile[i] = midifile.GetAt(i);
	}
	sourcefile[i] = 0x00;
	initialize_source();
	if (hpmfi == NULL) return;
	set_new_sourcefile(midifile);

	int no_double_notes;
	int no_pitch_wheels;
	hpmfi->eval_xg_convert(&no_double_notes,&no_pitch_wheels);

	int time_start_beat_start, time_start_beat_end;
	bool with_count_in = hpmfi->with_start_beats(&time_start_beat_start, &time_start_beat_end);	
	if (!start_beat_delete)
	{
		int chan;
		if (!with_count_in)
		{
			int no_double_notes;
			hpmfi->eval_xg_convert(&no_double_notes,&no_pitch_wheels);
			// midifile without any melody-notes? Do nothing
			
			bool is_stddrum = (hpmfi->mlv_list[9].msb==127);
			if (!is_stddrum)
			{
				if (hpmfi != NULL)
				{
					delete hpmfi;
					hpmfi = NULL;
				}
				return;
			}

			bool is_melody = false;
			for (chan=0; chan<16; chan++)
			{
				if (hpmfi->mlv_list[chan].melody && (hpmfi->no_notes[chan]!=0))
				{
					is_melody = true;
					break;
				}
			}
			if (!is_melody)
			{
				if (hpmfi != NULL)
				{
					delete hpmfi;
					hpmfi = NULL;
				}
				return;
			}
			hpmfi->eval_insert_start_beats(drum,velocity,on_all_beats, only_one_measure);
		}
	}
	if (start_beat_delete)
	{
		if (with_count_in)
		{
			hpmfi->eval_delete_start_beats(time_start_beat_start, time_start_beat_end);
		}
	}

	hpmfi->eval_xg_convert(&no_double_notes,&no_pitch_wheels);

	midifile = midifile.Left(midifile.GetLength()-4);
	char title[MAX_PATH];
	GetFileTitle(midifile,title,MAX_PATH);
	CString destination = dest_path+"\\";
	destination += title;
	destination += ".mid";

	hpmfi->eval_save(destination);
	if (hpmfi != NULL)
	{
		delete hpmfi;
		hpmfi = NULL;
	}
}

void CPsrutiDlg::fill_lyric_folder()
{
	
	if (fill_lyric_dlg == NULL) return;
	int actual_user = fill_lyric_dlg->get_actual_user();
	int method = fill_lyric_dlg->method;
	int is_user = actual_user;
	if (hpmfi != NULL)
	{
		hpmfi->set_is_user(actual_user);
	}
	o_inifile->set_user(actual_user);

	CString source_title = GlobalUtilities::get_resource_string(IDS_SOURCE_FOLDER_EXECUTE);
	CString dest_title = GlobalUtilities::get_resource_string(IDS_DEST_FOLDER_EXECUTE);
	char sel_path[MAX_PATH];

	// source folder
	
	ITEMIDLIST *sourceitemidlist;
	BROWSEINFO path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		source_title, // Select the path for source-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	sourceitemidlist = SHBrowseForFolder(&path_info);
	if(!SHGetPathFromIDList(sourceitemidlist,sel_path))
	{
		return;
	}
	
	// Conversion to CString
	CString selected_source_path = (CString)sel_path;

	// destination folder
	ITEMIDLIST *destitemidlist;
	BROWSEINFO dest_path_info = 
	{
		m_hWnd, // Owner, -> Window gets modal 
		NULL,	// pdlr bei Test
		sel_path,
		dest_title, // Select the path for the destination-files
		NULL,
		NULL,
		NULL,
		NULL
	};

	destitemidlist = SHBrowseForFolder(&dest_path_info);
	if(!SHGetPathFromIDList(destitemidlist,sel_path))
	{
		return;
	}

	CString selected_dest_path = (CString)sel_path;
	
	int last_index = selected_source_path.GetLength()-1;
	if (selected_source_path.GetAt(last_index)=='\\')
	{
		selected_source_path = selected_source_path.Left(last_index);
	}


	// Look for midifiles
	CFileFind mid_finder;
	if (mid_finder.FindFile(selected_source_path+"\\"+"*.mid"))
	{
		int nextfile;
		while (true)
		{
			if (fill_lyric_folder_abort_wanted)
			{
				break;
			}
			nextfile = mid_finder.FindNextFile();
			CString midifile = mid_finder.GetFilePath();
			fill_lyric_folder_file(midifile,selected_dest_path,method);
			if (nextfile==0) break;
		}
	}

	// Look for kar-files
	CFileFind kar_finder;
	if (!kar_finder.FindFile(selected_source_path+"\\"+"*.kar"))
	{
		return;
	}
	else
	{
		int nextfile;
		while (true)
		{
			if (fill_lyric_folder_abort_wanted)
			{
				break;
			}
			nextfile = kar_finder.FindNextFile();
			CString midifile = kar_finder.GetFilePath();
			fill_lyric_folder_file(midifile,selected_dest_path,method);
			if (nextfile==0) break;
		}
	}
}



void CPsrutiDlg::fill_lyric_folder_file(CString midifile, CString dest_path, int method)
{
	int i;
	for (i=0; i<midifile.GetLength();i++)
	{
		sourcefile[i] = midifile.GetAt(i);
	}
	sourcefile[i] = 0x00;
	initialize_source();
	if (hpmfi == NULL) return;
	set_new_sourcefile(midifile);

	int no_double_notes;
	int no_pitch_wheels;
	hpmfi->eval_xg_convert(&no_double_notes,&no_pitch_wheels);

	hpmfi->eval_fill_lyrics(fill_lyric_dlg->method);

	hpmfi->eval_xg_convert(&no_double_notes,&no_pitch_wheels);

	midifile = midifile.Left(midifile.GetLength()-4);
	char title[MAX_PATH];
	GetFileTitle(midifile,title,MAX_PATH);
	CString destination = dest_path+"\\";
	destination += title;
	destination += ".mid";

	hpmfi->eval_save(destination);
	if (hpmfi != NULL)
	{
		delete hpmfi;
		hpmfi = NULL;
	}
}


void CPsrutiDlg::OnTranspose()
{
	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	// Clear Player from last MIDI-File
	Stop();

	// transpose melody channels
	Transpose_no transpose_dlg;
	transpose_dlg.hpmfi = hpmfi;
	int no = transpose_dlg.DoModal();
	if (no == 20)
	{	// no tr selected
		return;
	}
	save_state();
		
	// Set the predefined Windows "Wait" cursor.
	SetCursor(hCursorWait);
	
	hpmfi->eval_transpose(no,transpose_dlg.send_new_key(),transpose_dlg.transpose_chords());
	analyse_changes();
		
	// Set the old cursor back
	SetCursor(hCursorOld);
	return;
}

void CPsrutiDlg::OnInsertChords()
{
	int i;
	CString t;

	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	// Clear Player from last MIDI-File
	Stop();

	int no_list[NO_CHORDLIST_CHAN];
	bool sel_list[16];

	for (i=0; i<16; i++)
	{
		sel_list[i] = false;
	}

	if (!hpmfi->pre_eval_chords(no_list, sel_list,true,-1))
	{
		if (IDYES != AfxMessageBox(GlobalUtilities::get_resource_string(IDS_WITH_XF_CHORDS),MB_YESNO,0))
		{
			return;
		}
		hpmfi->remove_chords();
		if (!hpmfi->pre_eval_chords(no_list, sel_list, true,-1))
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,"internal bug",NULL,MB_OK|MB_TASKMODAL);
			return;
		}
	}

	int chord_chan;
	int bass_channel;

	SlctChordChan scc;

	scc.hpmfi = hpmfi;

	for (i=0; i<NO_CHORDLIST_CHAN; i++)
	{
		scc.no_list[i] = no_list[i];
	}

	int dlg_result = scc.DoModal();
	if (dlg_result==-1) return;
	
	bass_channel = scc.bass_channel;

	bool chan_list[16];
	scc.get_chan_list(chan_list);
	chords_save = scc.chords_save;
	chords_print = scc.chords_print;
	chords_print_lyric = scc.chords_print_lyric;

	// mapping sel->CHORD_INDEX_SEL, all->CHORD_INDEX_ALL, chan -> 0,...15
	chord_chan = dlg_result;

	hpmfi->chord_protocol = chords_print;
	hpmfi->chord_protocol_lyric = chords_print_lyric;
	if (chords_print || chords_print_lyric)
	{
		CString protfile = GlobalUtilities::SelectProtFile(o_inifile->get_protfile());
		if (protfile == "") return;
		o_inifile->set_protfile(protfile);
		hpmfi->protfile = protfile;
	}

    // Set the predefined Windows "Wait" cursor.
	SetCursor(hCursorWait);

	save_state();

	int result = hpmfi->eval_chords(chord_chan, chan_list, bass_channel);
	if (result == 0)
	{
		int no_chords = hpmfi->no_chords;
		if (no_chords > 0)
		{
			if (!chords_print && !chords_print_lyric)
			{
				CString r;
				r.Format(GlobalUtilities::get_resource_string(IDS_CHORDS_QUANTISIZED),no_chords);
				::MessageBox(AfxGetMainWnd()->m_hWnd,r,"",MB_OK|MB_TASKMODAL);
			}
		}
	}
	else
	{
		t = "";
		if (result == -1)
		{
			CString s = GlobalUtilities::get_resource_string(IDS_no_chords_on_chan)+" %2.2d";
			t.Format(s,	hpmfi->selected_chord_chan+1);
		}

		else

		if (result == -2)
		{
			t = GlobalUtilities::get_resource_string(IDS_no_chords_in_song);
		}

		::MessageBox(AfxGetMainWnd()->m_hWnd,t,NULL,MB_OK|MB_TASKMODAL);
	}
	analyse_changes();

	// Set the old cursor back
	SetCursor(hCursorOld);
	chords_print = false;
}

void CPsrutiDlg::OnQuantisizeChords()
{
	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	if (!hpmfi->with_xfchords)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_no_chords_in_song),NULL,MB_OK|MB_TASKMODAL);
		return;
	}

	Stop();

    // Set the predefined Windows "Wait" cursor.

	QuantisizeChords *qch = new QuantisizeChords();
	int dlg_result = qch->DoModal();

	if (dlg_result==IDOK)
	{
		SetCursor(hCursorWait);
		save_state();

		hpmfi->eval_quantize_chords(qch->get_beat_resolution());
		int no_chords = hpmfi->get_no_chords();
		SetCursor(hCursorOld);

		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_CHORDS_QUANTISIZED),no_chords);
		::MessageBox(AfxGetMainWnd()->m_hWnd,r,"",MB_OK|MB_TASKMODAL);
	}
	delete qch;
	qch = NULL;
	analyse_changes();
}


void CPsrutiDlg::OnQuantisizeLyrics() 
{
	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	if (!hpmfi->with_lyrics)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_NO_LYRICS_IN_SONG),NULL,MB_OK|MB_TASKMODAL);
		return;
	}

	Stop();

    // Set the predefined Windows "Wait" cursor.

	QuantisizeLyricsDlg *qch = new QuantisizeLyricsDlg();
	qch->ppqn = hpmfi->ppqn;

	int dlg_result = qch->DoModal();

	if (dlg_result==IDOK)
	{
		SetCursor(hCursorWait);
		save_state();

		if (qch->is_lyrics_at_chords)
		{
			hpmfi->eval_shift_chordlyrics(qch->resolution);
		}
		else
		{
			hpmfi->eval_quantize_lyrics(qch->resolution);
		}
		SetCursor(hCursorOld);
	}
	delete qch;
	qch = NULL;
	analyse_changes();
}


void CPsrutiDlg::OnFilllyrics()
{
	bool singlefile_wanted = false;

	if (revoicefile_folder_running || 
		xg_convert_folder_running || 
		gm_convert_folder_running ||
		print_folder_running ||
		fileformat_folder_running ||
		count_in_folder_running ||
		expr_main_volume_folder_running ||
		drum_folder_running)
	{
		return;
	}

	if (fill_lyric_folder_running)
	{
		if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_FILL_LYRIC_ABORT),MB_YESNO,0)) return;
		fill_lyric_folder_abort_wanted = true;
		return;
	}

	int is_user = o_inifile->get_user();
	CString u1_takt_lyric, u1_beat_lyric, u1_end_lyric;
	CString u2_takt_lyric, u2_beat_lyric, u2_end_lyric;
	CString u3_takt_lyric, u3_beat_lyric, u3_end_lyric;

	u1_takt_lyric = o_inifile->get_user1_taktlyric();
	u1_takt_lyric = u1_takt_lyric.Mid(1,u1_takt_lyric.GetLength()-2);
	u1_beat_lyric = o_inifile->get_user1_beatlyric();
	u1_beat_lyric = u1_beat_lyric.Mid(1,u1_beat_lyric.GetLength()-2);
	u1_end_lyric = o_inifile->get_user1_endlyric();
	u1_end_lyric = u1_end_lyric.Mid(1,u1_end_lyric.GetLength()-2);
			
	u2_takt_lyric = o_inifile->get_user2_taktlyric();
	u2_takt_lyric = u2_takt_lyric.Mid(1,u2_takt_lyric.GetLength()-2);
	u2_beat_lyric = o_inifile->get_user2_beatlyric();
	u2_beat_lyric = u2_beat_lyric.Mid(1,u2_beat_lyric.GetLength()-2);
	u2_end_lyric = o_inifile->get_user2_endlyric();
	u2_end_lyric = u2_end_lyric.Mid(1,u2_end_lyric.GetLength()-2);

	u3_takt_lyric = o_inifile->get_user3_taktlyric();
	u3_takt_lyric = u3_takt_lyric.Mid(1,u3_takt_lyric.GetLength()-2);
	u3_beat_lyric = o_inifile->get_user3_beatlyric();
	u3_beat_lyric = u3_beat_lyric.Mid(1,u3_beat_lyric.GetLength()-2);
	u3_end_lyric = o_inifile->get_user3_endlyric();
	u3_end_lyric = u3_end_lyric.Mid(1,u3_end_lyric.GetLength()-2);

	if (hpmfi == NULL)
	{
		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_FILL_LYRIC_FOLDER));
		if (IDYES != AfxMessageBox(r,MB_YESNO,0))
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
			hpmfi = Selectsource();
			if (hpmfi==NULL)
			{
				return;
			}
			else
			{
				singlefile_wanted = true;
			}
		}
		
		if ((hpmfi==NULL) && !singlefile_wanted)
		{
			// initiate batch
			MSG msg;
			fill_lyric_folder_running = true;
			fill_lyric_folder_abort_wanted = false;
			batch_running = true;
			CString batch_running_text = GlobalUtilities::get_resource_string(IDS_BATCH_RUNNING);
			SetWindowText("PSRUTI         "+batch_running_text);

			fill_lyric_dlg = new FillLyricMethodDlg;
			fill_lyric_dlg->set_fill_lyric_data(u1_takt_lyric,u1_beat_lyric,u1_end_lyric,
							u2_takt_lyric,u2_beat_lyric,u2_end_lyric,
							u3_takt_lyric,u3_beat_lyric,u3_end_lyric,
							is_user);
			int return_value = fill_lyric_dlg->DoModal();

			if (return_value == 0)
			{
				delete fill_lyric_dlg;
				fill_lyric_dlg = NULL;
				fill_lyric_folder_running = false;
				fill_lyric_folder_abort_wanted = false;
				batch_running = false;
				SetDlgItemText(IDC_FILENAME,"");
				SetWindowText("PSRUTI");
				Invalidate();   
				UpdateWindow();
				o_inifile->set_sourcefile("");
				return;
			}

			hThread = CreateThread(
				NULL,	// Security attribute
				0,		// Initial stacksize
				(LPTHREAD_START_ROUTINE)fill_lyric_thread_run, // start function in the thread
				this,	// Argument for the start function, here pointer to the actual object
				0,		// Creation flags
				&threadID // Pointer of the thread identifier
							);	
			SetThreadPriority(hThread,THREAD_PRIORITY_BELOW_NORMAL);

			// The thread is interrupted all 50 milliseconds.
			// to look for and pump messages.  
			while (WaitForSingleObject(hThread,50) != WAIT_OBJECT_0)
			{
				while ( ::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) 
				{ 
					if (!AfxGetApp()->PumpMessage()) 
					{ 
						break; 
					} 
				}
			}

			CloseHandle(hThread);


			delete fill_lyric_dlg;
			fill_lyric_dlg = NULL;
			fill_lyric_folder_running = false;
			fill_lyric_folder_abort_wanted = false;
			batch_running = false;
			SetDlgItemText(IDC_FILENAME,"");
			SetWindowText("PSRUTI");
			Invalidate();   
			UpdateWindow();
			o_inifile->set_sourcefile("");
			::MessageBox(AfxGetMainWnd()->m_hWnd,
				GlobalUtilities::get_resource_string(IDS_BATCH_PERFORMED),"",MB_OK|MB_TASKMODAL);
			return;
		}
	}

	// single file

	// Clear Player from last MIDI-File
	Stop();

	FillLyricMethodDlg dlg;
	dlg.set_fill_lyric_data(u1_takt_lyric,u1_beat_lyric,u1_end_lyric,
							u2_takt_lyric,u2_beat_lyric,u2_end_lyric,
							u3_takt_lyric,u3_beat_lyric,u3_end_lyric,
							is_user);
	
	if (dlg.DoModal()==0)
	{ // Cancel
		return;
	}

	int actual_user = dlg.get_actual_user();
	if (actual_user != is_user)
	{
		is_user = actual_user;
		if (hpmfi != NULL)
		{
			hpmfi->set_is_user(is_user);
		}
		o_inifile->set_user(is_user);
	}

	SetCursor(hCursorWait);
	save_state();
	hpmfi->eval_fill_lyrics(dlg.method);
	analyse_changes();

	SetCursor(hCursorOld);
	::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_FILL_LYRICS_INSERTED),"",MB_OK|MB_TASKMODAL);

}

void CPsrutiDlg::OnSelectFillLyricsLinefeed() // Now only Lyrics/Linefeed/Newpage
{
	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}


	// Clear Player from last MIDI-File
	Stop();

	SelectFillLyrics dlg;
	dlg.logf = hpmfi->lf;
	dlg.hpmfi = hpmfi;

	if (dlg.DoModal() == IDCANCEL) return;

	SetCursor(hCursorWait);

	bool is_linefeed = dlg.linefeed_selected(); // linefeed and newpage!

	if (is_linefeed)
	{
		save_state();

		int shift_linefeed_ticks = dlg.get_shift_ticks();
		int shift_linefeed_ticks_at = dlg.get_shift_ticks_at();
		if ((shift_linefeed_ticks>0)||(shift_linefeed_ticks_at>0))
		{
			hpmfi->eval_shift_linefeeds(shift_linefeed_ticks,shift_linefeed_ticks_at);
		}

		analyse_changes();
		m_undo.EnableWindow(true);
		SetCursor(hCursorOld);
		return;
	}
	
	bool is_cuepoint_lyrc = dlg.cuepoint_lyrc_selected();
	if (is_cuepoint_lyrc)
	{
		save_state();
		int cuepoint_lyric_tick = dlg.get_cuepoint_lyrc_tick();
		hpmfi->eval_cuepoint_lyric(cuepoint_lyric_tick);
		analyse_changes();
		SetCursor(hCursorOld);
		return;
	}
	SetCursor(hCursorOld);
}

void CPsrutiDlg::OnXgConvert()
{
	bool singlefile_wanted = false;

	if (revoicefile_folder_running ||
		gm_convert_folder_running ||
		print_folder_running || 
		fileformat_folder_running ||
		count_in_folder_running ||
		expr_main_volume_folder_running ||
		fill_lyric_folder_running ||
		drum_folder_running)
	{
		return;
	}

	if (xg_convert_folder_running)
	{
		if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_XG_OPTIMIZE_ABORT),MB_YESNO,0))
		{
			return;
		}
			
		xg_convert_folder_abort_wanted = true;
		return;
	}
	
	if (hpmfi == NULL)
	{
		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_CONVERT_FOLDER));
		if (IDYES != AfxMessageBox(r,MB_YESNO,0))
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
			hpmfi = Selectsource();
			if (hpmfi==NULL)
			{
				return;
			}
			else
			{
				singlefile_wanted = true;
			}
		}
		
		if ((hpmfi==NULL) && !singlefile_wanted)
		{
			// initiate batch
			MSG msg;
			xg_convert_folder_running = true;
			batch_running = true;
			xg_convert_folder_abort_wanted = false;
			CString batch_running_text = GlobalUtilities::get_resource_string(IDS_BATCH_RUNNING);
			SetWindowText("PSRUTI         "+batch_running_text);

			hThread = CreateThread(
				NULL,	// Security attribute
				0,		// Initial stacksize
				(LPTHREAD_START_ROUTINE)xg_convert_thread_run, // start function in the thread
				this,	// Argument for the start function, here pointer to the actual object
				0,		// Creation flags
				&threadID // Pointer of the thread identifier
							);	
			SetThreadPriority(hThread,THREAD_PRIORITY_BELOW_NORMAL);

			// The thread is interrupted all 50 milliseconds.
			// to look for and pump messages.  
			while (WaitForSingleObject(hThread,50) != WAIT_OBJECT_0)
			{
				while ( ::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) 
				{ 
					if (!AfxGetApp()->PumpMessage()) 
					{ 
						break; 
					} 
				}
			}

			CloseHandle(hThread);

			xg_convert_folder_running = false;
			xg_convert_folder_abort_wanted = false;
			batch_running = false;
			SetDlgItemText(IDC_FILENAME,"");
			SetWindowText("PSRUTI");
			Invalidate();
			UpdateWindow();
			o_inifile->set_sourcefile("");
			::MessageBox(AfxGetMainWnd()->m_hWnd,
				GlobalUtilities::get_resource_string(IDS_BATCH_PERFORMED),"",MB_OK|MB_TASKMODAL);
			return;
		}
	}
	
	if (hpmfi != NULL)
	{

	   // Set the predefined Windows "Wait" cursor.
		SetCursor(hCursorWait);

		// Clear Player from last MIDI-File
		Stop();
		save_state();

		int no_double_notes;
		int no_double_pitch_wheels;
		int no_controller_deleted = hpmfi->eval_xg_convert(&no_double_notes,&no_double_pitch_wheels);

		analyse_changes();
		SetCursor(hCursorOld);

		CString r;
		if ((no_controller_deleted==0) && (no_double_notes==0) && (no_double_pitch_wheels==0))
		{
			r = GlobalUtilities::get_resource_string(IDS_XG_CONVERTED);
		}
		else
		{
			CString s = GlobalUtilities::get_resource_string(IDS_XG_CONVERTED_CONTROLLER_DELETED);
			r.Format(s,no_controller_deleted,no_double_notes,no_double_pitch_wheels);
		}
		::MessageBox(AfxGetMainWnd()->m_hWnd,r,"",MB_OK|MB_TASKMODAL);
	}
}

void CPsrutiDlg::OnLanguage()
{
	if (batch_running) return;
	if (source_changed)
	{
		SaveChangesDlg dlg;
		int result = dlg.DoModal();

		if (result == 1)
		{
			OnSaveAs();
			return;
		}
		if (result == -1)
		{
			return;
		}

		// result == 0: Save not wanted
	}

	Select_Language dlg;
	dlg.initial_language = language;
	int result = dlg.DoModal();
	if (result == 0) return;

	CString new_language = dlg.language;
	if (new_language!=language)
	{
		o_inifile->set_language(new_language);

		if (hpmfi != NULL)
		{
			Stop(); // stop play
			delete hpmfi;
			hpmfi = NULL;
		}

		delete o_inifile;
		o_inifile = NULL;

		if (lf != NULL)
		{
			delete lf;
			lf = NULL;
		}
		EndDialog(IDNEWSTART);
	}
}

void CPsrutiDlg::OnClose()
{
	if (batch_running) return;
	from_close = true;
	OnOK();
}

void CPsrutiDlg::OnOK()
{
	if (batch_running) return;
	if (hpmfi != NULL)
	{
		if (HP_IsPlaying(hpmfi->mf))
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_STOP_PLAY),NULL,MB_OK|MB_TASKMODAL);
			return;
		}
	}

	if (source_changed)
	{
		SaveChangesDlg dlg;
		int result = dlg.DoModal();

		if (result == 1) 
		{
			OnSaveAs();
		}

		if (result == -1) 
		{
			return;
		}
	}

	source_changed = false;


	if (hpmfi != NULL)
	{
		Stop(); // stop play
		delete hpmfi;
		hpmfi = NULL;
	}

	if (hpmfi_save != NULL)
	{
		delete hpmfi_save;
		hpmfi_save = NULL;
	}

	int sourcefile_list_length = sourcefile_list.get_length();
	if (sourcefile_list_length>0 && 
		sourcefile_list_index<sourcefile_list_length &&
		!from_close)
	{
		strcpy(sourcefile,sourcefile_list.get_name(sourcefile_list_index));
		sourcefile_list_index++;
		CString scrpath = sourcefile;
		scrpath.MakeLower();
		scrpath = scrpath.Right(4);
		if ((scrpath==".mid")||(scrpath==".kar"))
		{
			initialize_source();
			if (hpmfi==NULL) return;
			source_changed = hpmfi->is_source_changed();
		}
		return;
	}

	delete o_inifile;
	o_inifile = NULL;

	if (lf != NULL)
	{
		delete lf;
		lf = NULL;
	}
	
    CDialog::OnOK();
}

void CPsrutiDlg::OnSourceClose() 
{
	if (batch_running) return;
	if (hpmfi != NULL)
	{
		if (HP_IsPlaying(hpmfi->mf))
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_STOP_PLAY),NULL,MB_OK|MB_TASKMODAL);
			return;
		}
	}

	if (source_changed)
	{
		SaveChangesDlg dlg;
		int result = dlg.DoModal();

		if (result == 1) 
		{
			OnSaveAs();
		}

		if (result == -1) 
		{
			return;
		}
	}

	source_changed = false;

	if (hpmfi != NULL)
	{
		Stop(); // stop play
		delete hpmfi;
		hpmfi = NULL;
	}

	if (hpmfi_save != NULL)
	{
		delete hpmfi_save;
		hpmfi_save = NULL;
	}

	int sourcefile_list_length = sourcefile_list.get_length();
	if (sourcefile_list_length>0)
	{
		sourcefile_list.clear();
	}

	SetDlgItemText(IDC_FILENAME,"");
	m_undo.EnableWindow(false);

	// Drag and Drop allowed
	CWnd::DragAcceptFiles(TRUE);
}

void CPsrutiDlg::OnTempo()
{
	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	// Clear Player from last MIDI-File
	Stop();

	Tempo_Dlg dlg;
	dlg.max_tempo = hpmfi->get_max_tempo();

	if (dlg.DoModal() == 0) return; // 0: cancelled, 1: OK
	double tempo = dlg.get_tempo();

	// Set the predefined Windows "Wait" cursor.
	hCursorOld = GetCursor();
	hCursorWait = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
	SetCursor(hCursorWait);

	save_state();
	hpmfi->eval_tempo(tempo);
	hpmfi->set_max_tempo(tempo); // for the next OnTempo
	analyse_changes();

	// Set the old cursor back
	SetCursor(hCursorOld);
}

void CPsrutiDlg::OnVolume()
{
	if (batch_running) return;
/*
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		return;
	}
*/
	// Clear Player from last MIDI-File
	Stop();

	VolumeMethodDlg dlg;
	dlg.hpmfi = hpmfi;
	dlg.mainfun = this;
	dlg.hCursorOld = hCursorOld;
	dlg.hCursorWait = hCursorWait;
	dlg.o_inifile = o_inifile;
	dlg.lf = lf;

	int result = dlg.DoModal();
	if (result == 0) return;	//0: cancelled, 1: OK
}

void CPsrutiDlg::OnSave() 
{
	UINT result;
	int i;

	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	if (HP_IsPlaying(hpmfi->mf))
	{
		Stop();
	}

	m_destination = sourcefile;
	// offer only files with extension mid
	if (m_destination.Find('.')>0)
	{
		// delete all extensions and add new extension ,mid
		int no_ext = 0;
		int len = m_destination.GetLength();
		for (i=len-1; i>1; i--)
		{
			if (m_destination[i]=='.') break;
			no_ext++;
		}
		m_destination = m_destination.Left(len-no_ext)+"mid";
	}
	else
	{
		// file without extension: add .mid
		m_destination += ".mid";
	}

    // Set the predefined Windows "Wait" cursor.
	hCursorOld = GetCursor();
	hCursorWait = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
	SetCursor(hCursorWait);

	result = hpmfi->eval_save(m_destination);

	// Set the old cursor back
	SetCursor(hCursorOld);

	if (result != HP_ERR_NONE)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_ERROR_DEST),NULL,MB_OK|MB_TASKMODAL);
		return;
	}

	for (i=0; i<m_destination.GetLength(); i++)
	{
		destfile[i] = m_destination[i];
	}
	destfile[m_destination.GetLength()] = 0;

	source_changed = false;

	CString sourcefile_cstring = sourcefile;
	if (m_destination != sourcefile_cstring)
	{
		set_new_sourcefile(m_destination);
		Invalidate();   
		UpdateWindow();
	}
}


void CPsrutiDlg::OnSaveAs()
{
	UINT result;
	int i;

	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	if (HP_IsPlaying(hpmfi->mf))
	{
		Stop();
	}

	bool source_allowed = false;

	char BASED_CODE szFilter[] =
		"MIDI File (*.mid)|*.mid|All Files (*.*)|*.*||";

	CFileDialog openfile_dlg(FALSE,
						  "mid",
						  NULL,
						  OFN_PATHMUSTEXIST,
						  szFilter,
						  NULL);

	if (destfile[0] != 0)
	{
		// change extension to .mid
		int len = strlen(destfile);
		int p_index = -1;
		for (i=len-1; i>=0; i--)
		{
			if (destfile[i]=='.')
			{
				p_index = i;
				break;
			}
		}

		if (p_index >=0)
		{
			destfile[p_index] = 0;
		}
		strcat(destfile,".mid");
		
		openfile_dlg.m_ofn.lpstrFile = destfile;
	}
	else
	{
		// Get last source
		CString last_file = o_inifile->get_sourcefile();
		if (last_file != "")
		{
			// offer only files with extension mid
			if (last_file.Find('.')>0)
			{
				// delete all extensions and add new extension ,mid
				int no_ext = 0;
				int len = last_file.GetLength();
				for (i=len-1; i>1; i--)
				{
					if (last_file[i]=='.') break;
					no_ext++;
				}
				last_file = last_file.Left(len-no_ext)+"mid";
			}
 			else
			{
				// file without extension: add .mid
				last_file += ".mid";
			}

			char ld[MAX_PATH];

			for (i=0; i<last_file.GetLength(); i++)
			{
				ld[i] = last_file[i];
			}
			ld[last_file.GetLength()] = (char)0;
			openfile_dlg.m_ofn.lpstrFile = ld;
			openfile_dlg.m_ofn.lpstrInitialDir = ld; // works with full path
		}
		else
		{
			openfile_dlg.m_ofn.lpstrFile = "";
		}
	}

	CString sourcefile_cstr = sourcefile;

	int return_value = openfile_dlg.DoModal();
	if (return_value == IDOK)
	{
		m_destination = openfile_dlg.m_ofn.lpstrFile;
	}
	else
	{
		if (return_value == IDCANCEL)
		{
			m_destination = "";
			return;
		}
	}

	if (m_destination==sourcefile_cstr)
	{
			if (IDYES == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_overwrite_source),MB_YESNO,0))
			{
				source_allowed = true;
			}
			else
			{
				m_destination = "";
				return;
			}
	}

	if (!source_allowed)
	{
		CFile mf_newf;
		CFileException e;
		if (mf_newf.Open(m_destination, CFile::modeRead,&e))
		{
			int length = mf_newf.GetLength();
			mf_newf.Close();
			if (length>0)
			{
				CString r;
				r.Format(GlobalUtilities::get_resource_string(IDS_UseExistingFile)+"\"%s\" ?",m_destination);
				if (IDYES != AfxMessageBox(r,MB_YESNO,0))
				{
					m_destination = "";
					return;
				}
			}
		}
	}

	if (m_destination == "") return;

    // Set the predefined Windows "Wait" cursor.
	hCursorOld = GetCursor();
	hCursorWait = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
	SetCursor(hCursorWait);

	result = hpmfi->eval_save(m_destination);

	// Set the old cursor back
	SetCursor(hCursorOld);

	if (result != HP_ERR_NONE)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_ERROR_DEST),NULL,MB_OK|MB_TASKMODAL);
		return;
	}

	for (i=0; i<m_destination.GetLength(); i++)
	{
		destfile[i] = m_destination[i];
	}
	destfile[m_destination.GetLength()] = 0;

	source_changed = false;

	CString sourcefile_cstring = sourcefile;
	if (m_destination != sourcefile_cstring)
	{
		set_new_sourcefile(m_destination);
		Invalidate();   
		UpdateWindow();
		o_inifile->set_sourcefile(m_destination);
		for (i=0; i<m_destination.GetLength(); i++)
		{
			sourcefile[i] = m_destination[i];
		}
		sourcefile[m_destination.GetLength()] = 0;
		hpmfi->sourcefile = m_destination;
	}


}

void CPsrutiDlg::Stop()
{
	if (hpmfi != NULL)
	{
		if (pdlg != NULL)
		{
			pdlg->Stop();
		}
	}
}

//***********************************************************************
//
// save hpmfi to hpmfi_save
//
//***********************************************************************

void CPsrutiDlg::save_state()
{
	if (hpmfi == NULL) return;

	if (hpmfi_save != NULL)
	{
		delete hpmfi_save;
		hpmfi_save = NULL;
	}
	hpmfi_save = new HPMF_Interface(*hpmfi);
}

//***********************************************************************
//
//  restore hpmfi from hpmfi_save
//
//***********************************************************************

void CPsrutiDlg::restore_state()
{
	if (hpmfi_save == NULL) return;
	SetCursor(hCursorWait);
	if (hpmfi != NULL)
	{
		delete hpmfi;
		hpmfi = NULL;
	}
	hpmfi = new HPMF_Interface(*hpmfi_save);
	delete hpmfi_save;
	hpmfi_save = NULL;

	char beat_lyric[80];
	char takt_lyric[80];
	char end_lyric[80];
	int  linefeedlyrictick;

	hpmfi->get_user1_fill_lyric_data(takt_lyric,beat_lyric,end_lyric,&linefeedlyrictick);
	o_inifile->set_user1_taktlyric(GlobalUtilities::convert_cstring_to_printable(takt_lyric));
	o_inifile->set_user1_beatlyric(GlobalUtilities::convert_cstring_to_printable(beat_lyric));
	o_inifile->set_user1_endlyric(GlobalUtilities::convert_cstring_to_printable(end_lyric));

	hpmfi->get_user2_fill_lyric_data(takt_lyric,beat_lyric,end_lyric,&linefeedlyrictick);
	o_inifile->set_user2_taktlyric(GlobalUtilities::convert_cstring_to_printable(takt_lyric));
	o_inifile->set_user2_beatlyric(GlobalUtilities::convert_cstring_to_printable(beat_lyric));
	o_inifile->set_user2_endlyric(GlobalUtilities::convert_cstring_to_printable(end_lyric));

	hpmfi->get_user3_fill_lyric_data(takt_lyric,beat_lyric,end_lyric,&linefeedlyrictick);
	o_inifile->set_user3_taktlyric(GlobalUtilities::convert_cstring_to_printable(takt_lyric));
	o_inifile->set_user3_beatlyric(GlobalUtilities::convert_cstring_to_printable(beat_lyric));
	o_inifile->set_user3_endlyric(GlobalUtilities::convert_cstring_to_printable(end_lyric));
	
	m_undo.EnableWindow(false);
	SetCursor(hCursorOld);
}

//***********************************************************************
//
//  free hpmfi_save
//
//***********************************************************************

void CPsrutiDlg::free_saved_state()
{
	if (hpmfi_save == NULL) return;
	delete hpmfi_save;
	hpmfi_save = NULL;
	m_undo.EnableWindow(false);
}

//***********************************************************************
//
//  analyse_changes
//
//***********************************************************************

void CPsrutiDlg::analyse_changes()
{
	if (!source_changed)
	{
		source_changed = hpmfi->is_source_changed();
		if (!source_changed) free_saved_state();
	}
	if (source_changed)
	{
		m_undo.EnableWindow(true);
	}
}

void CPsrutiDlg::OnPlayButton()
{
	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	// Clear Player from last MIDI-File
	Stop();

	pdlg = new CPlay;
	pdlg->hpmfi = hpmfi;
	pdlg->mainfun = this;
	pdlg->mf = hpmfi->mf;
	pdlg->with_lyrics = hpmfi->with_lyrics;
	pdlg->logf = lf;
	pdlg->o_inifile = o_inifile;

	int i;
	for (i=0; i<16; i++)
	{
		(pdlg->chan_transpose_list)[i] = (hpmfi->mlv_list)[i].melody;
		(pdlg->chan_mute_list)[i] = false;
	}

	int dlg_result = pdlg->DoModal();
	if (dlg_result==-1)
	{
		delete pdlg;
		pdlg = NULL;
		return;
	}

	if (!source_changed)
	{
		source_changed = pdlg->source_changed;
	}

	delete pdlg;
	pdlg = NULL;
}

void CPsrutiDlg::OnPrint()
{
	bool singlefile_wanted = false;

	// Clear Player from last MIDI-File
	Stop();

	if (revoicefile_folder_running || 
		xg_convert_folder_running || 
		gm_convert_folder_running ||
		fileformat_folder_running ||
		count_in_folder_running ||
		expr_main_volume_folder_running ||
		fill_lyric_folder_running ||
		drum_folder_running )
	{
		return;
	}

	if (print_folder_running)
	{
		if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_PRINT_ABORT),MB_YESNO,0)) return;
		print_folder_abort_wanted = true;
		return;
	}
	
	if (hpmfi == NULL)
	{
		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_PRINT_FOLDER));
		if (IDYES != AfxMessageBox(r,MB_YESNO,0))
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
			hpmfi = Selectsource();
			if (hpmfi==0)
			{
				return;
			}
			else
			{
				singlefile_wanted = true;
			}
		}
		
		if ((hpmfi==NULL) && !singlefile_wanted)
		{
			// initiate batch
			MSG msg;
			print_folder_running = true;
			print_folder_abort_wanted = false;
			batch_running = true;
			CString batch_running_text = GlobalUtilities::get_resource_string(IDS_BATCH_RUNNING);
			SetWindowText("PSRUTI         "+batch_running_text);

			hThread = CreateThread(
				NULL,	// Security attribute
				0,		// Initial stacksize
				(LPTHREAD_START_ROUTINE)print_thread_run, // start function in the thread
				this,	// Argument for the start function, here pointer to the actual object
				0,		// Creation flags
				&threadID // Pointer of the thread identifier
							);	
			SetThreadPriority(hThread,THREAD_PRIORITY_BELOW_NORMAL);

			// The thread is interrupted all 50 milliseconds.
			// to look for and pump messages.  
			while (WaitForSingleObject(hThread,50) != WAIT_OBJECT_0)
			{
				while ( ::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) 
				{ 
					if (!AfxGetApp()->PumpMessage()) 
					{ 
						break; 
					} 
				}
			}

			CloseHandle(hThread);

			print_folder_running = false;
			print_folder_abort_wanted = false;
			batch_running = false;
			SetDlgItemText(IDC_FILENAME,"");
			SetWindowText("PSRUTI");
			Invalidate();   
			UpdateWindow();
			o_inifile->set_sourcefile("");
			::MessageBox(AfxGetMainWnd()->m_hWnd,
				GlobalUtilities::get_resource_string(IDS_BATCH_PERFORMED),"",MB_OK|MB_TASKMODAL);
			return;
		}
	}

	// Clear Player from last MIDI-File

	CPrint *print= new CPrint(hpmfi);

	CString protfile = GlobalUtilities::SelectProtFile(o_inifile->get_protfile());

	if (protfile!="")
	{
		o_inifile->set_protfile(protfile);
		print->print(protfile, true); // print and show
	}

	delete print;
	print = NULL;
}

void CPsrutiDlg::OnStartBeat()
{
	bool singlefile_wanted = false;

	// Clear Player from last MIDI-File
	Stop();

	if (revoicefile_folder_running || 
		xg_convert_folder_running || 
		gm_convert_folder_running ||
		fileformat_folder_running ||
		print_folder_running ||
		expr_main_volume_folder_running ||
		fill_lyric_folder_running ||
		drum_folder_running)
	{
		return;
	}

	if (count_in_folder_running)
	{
		if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_COUNT_IN_ABORT),MB_YESNO,0)) return;
		count_in_folder_abort_wanted = true;
		return;
	}
	
	if (hpmfi == NULL)
	{
		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_COUNT_IN_FOLDER));
		if (IDYES != AfxMessageBox(r,MB_YESNO,0))
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
			hpmfi = Selectsource();
			if (hpmfi==NULL)
			{
				return;
			}
			else
			{
				singlefile_wanted = true;
			}
		}
		
		if ((hpmfi==NULL) && !singlefile_wanted)
		{
			// initiate batch
			MSG msg;
			count_in_folder_running = true;
			count_in_folder_abort_wanted = false;
			batch_running = true;
			CString batch_running_text = GlobalUtilities::get_resource_string(IDS_BATCH_RUNNING);
			SetWindowText("PSRUTI         "+batch_running_text);

			count_in_dlg = new StartBeatFolderDlg;
			count_in_dlg->set_drum(o_inifile->get_countin_drum());
			count_in_dlg->set_velocity(o_inifile->get_countin_vel());

			int return_value = count_in_dlg->DoModal();

			if (return_value == -1)
			{
				delete count_in_dlg;
				count_in_dlg = NULL;
				count_in_folder_running = false;
				count_in_folder_abort_wanted = false;
				batch_running = false;
				SetDlgItemText(IDC_FILENAME,"");
				SetWindowText("PSRUTI");
				Invalidate();   
				UpdateWindow();
				o_inifile->set_sourcefile("");
				return;
			}

			hThread = CreateThread(
				NULL,	// Security attribute
				0,		// Initial stacksize
				(LPTHREAD_START_ROUTINE)count_in_thread_run, // start function in the thread
				this,	// Argument for the start function, here pointer to the actual object
				0,		// Creation flags
				&threadID // Pointer of the thread identifier
							);	
			SetThreadPriority(hThread,THREAD_PRIORITY_BELOW_NORMAL);

			// The thread is interrupted all 50 milliseconds.
			// to look for and pump messages.  
			while (WaitForSingleObject(hThread,50) != WAIT_OBJECT_0)
			{
				while ( ::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) 
				{ 
					if (!AfxGetApp()->PumpMessage()) 
					{ 
						break; 
					} 
				}
			}

			CloseHandle(hThread);

			delete count_in_dlg;
			count_in_dlg = NULL;
			count_in_folder_running = false;
			count_in_folder_abort_wanted = false;
			batch_running = false;
			SetDlgItemText(IDC_FILENAME,"");
			SetWindowText("PSRUTI");
			Invalidate();   
			UpdateWindow();
			o_inifile->set_sourcefile("");
			::MessageBox(AfxGetMainWnd()->m_hWnd,
				GlobalUtilities::get_resource_string(IDS_BATCH_PERFORMED),"",MB_OK|MB_TASKMODAL);
			return;
		}
	}

	// only single file

	int chan;

	int time_start_beat_start;
	int time_start_beat_end;

	// midifile without any melody-notes? Do nothing
	bool is_stddrum = !(hpmfi->mlv_list[9]).melody;
	if (!is_stddrum)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,
				GlobalUtilities::get_resource_string(IDS_CHAN_10_NO_DRUMS),"",MB_OK|MB_TASKMODAL);
		return;
	}

	bool is_melody = false;
	for (chan=0; chan<16; chan++)
	{
		if (hpmfi->mlv_list[chan].melody && (hpmfi->no_notes[chan]!=0))
		{
			is_melody = true;
			break;
		}
	}
	if (!is_melody) return;

	SetCursor(hCursorWait);

	int no_double_notes;
	int no_pitch_wheels;

	hpmfi->eval_xg_convert(&no_double_notes,&no_pitch_wheels);

	SetCursor(hCursorOld);

	bool with_start_beats = hpmfi->with_start_beats(&time_start_beat_start,&time_start_beat_end);

	StartBeat *dlg = new StartBeat();

	dlg->start_beat_delete = with_start_beats;
	dlg->hpmfi = hpmfi;

	if (!with_start_beats)
	{
		dlg->set_drum(o_inifile->get_countin_drum());
		dlg->set_velocity(o_inifile->get_countin_vel());
	}

	int return_value = dlg->DoModal();

	if (return_value == -1)
	{
		delete dlg;
		dlg = NULL;
		return;
	}

	bool done;

	SetCursor(hCursorWait);


	if (with_start_beats)
	{
		save_state();
		done = hpmfi->eval_delete_start_beats(time_start_beat_start,time_start_beat_end);
	}
	else
	{
		int drum = dlg->get_drum();
		int vel = dlg->get_velocity();

		save_state();
		done = hpmfi->eval_insert_start_beats(drum,vel,dlg->on_all_beats, dlg->only_one_measure);
		if (done)
		{
			o_inifile->set_countin_drum(drum);
			o_inifile->set_countin_vel(vel);
		}
	}


	delete dlg;
	dlg = NULL;

	hpmfi->eval_xg_convert(&no_double_notes,&no_pitch_wheels);

	analyse_changes();
	SetCursor(hCursorOld);

	if (done)
	{
		CString r;
		if (with_start_beats)
		{
			r = GlobalUtilities::get_resource_string(IDS_COUNT_IN_DELETED);
		}
		else
		{
			r = GlobalUtilities::get_resource_string(IDS_COUNT_IN_INSERTED);
		}
		::MessageBox(AfxGetMainWnd()->m_hWnd,r,"",MB_OK|MB_TASKMODAL);
	}
}

void CPsrutiDlg::OnVelCompress()
{
	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	// Clear Player from last MIDI-File
	Stop();

	VelCompress vel_compress_dlg;
	vel_compress_dlg.hpmfi = hpmfi;

	if (vel_compress_dlg.DoModal() == IDCANCEL)
	{
		return;
	}

    // Set the predefined Windows "Wait" cursor.
	SetCursor(hCursorWait);
	save_state();
	hpmfi->eval_vel_compress(vel_compress_dlg.final_vel_compress_list);

	analyse_changes();

	// Set the old cursor back
	SetCursor(hCursorOld);
}

bool CPsrutiDlg::ask_for_revoicefile(char* revoicefile)
{
	int i;
	// File Dialog
	char BASED_CODE szFilter[] =
		"Text Files (*.txt)|*.txt||";
		
	// Clear Function-Texts
		
	CFileDialog openfile_dlg(TRUE,
		"txt",
		NULL,
		OFN_FILEMUSTEXIST |
		OFN_PATHMUSTEXIST,
		szFilter,
		NULL);
	
	CString last_file = o_inifile->get_revoicefile();
	if (last_file != "")
	{
		openfile_dlg.m_ofn.lpstrInitialDir = last_file;
		char lf[MAX_PATH];
		for (i=0; i<last_file.GetLength(); i++)
		{
			lf[i] = last_file[i];
		}
		lf[last_file.GetLength()] = (char)0;
		openfile_dlg.m_ofn.lpstrFile = lf;
	}
	
	CString cstrtitle = GlobalUtilities::get_resource_string(IDS_REVOICEFILE_BOXTITLE);
	char* ctitle;
	GlobalUtilities::convert_CString_to_cstring(&ctitle, cstrtitle);
	openfile_dlg.m_ofn.lpstrTitle = ctitle;
	int return_value = openfile_dlg.DoModal();
	delete[] ctitle;
	
	if (return_value == IDCANCEL)
	{
		return false;
	}
	
	strcpy(revoicefile,openfile_dlg.m_ofn.lpstrFile);
	return true;
}

void CPsrutiDlg::OnRevoicing()
{
	if (xg_convert_folder_running || 
		gm_convert_folder_running ||
		print_folder_running || 
		fileformat_folder_running ||
		count_in_folder_running ||
		expr_main_volume_folder_running ||
		fill_lyric_folder_running ||
		drum_folder_running)
    return;
	
	RevoicingMethodDlg dlg;
	
	int result = dlg.DoModal();
	if ((result==IDCANCEL)||(result==-1))
	{
		return;
	}
	
	if (result==0)
	{	// Standard Revoicing
		if (revoicefile_folder_running) return;

		if (hpmfi == NULL)
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
			hpmfi = Selectsource();
			if (hpmfi == NULL)
			{
				return;
			}
		}

		// Clear Player from last MIDI-File
		Stop();

		RevoicingDlg revoicing_dlg;
		revoicing_dlg.p_inifile = o_inifile;
		revoicing_dlg.hpmfi = hpmfi;
		revoicing_dlg.hCursorWait = hCursorWait;
		revoicing_dlg.hCursorOld = hCursorOld;
		
		if (revoicing_dlg.DoModal() == IDCANCEL)
		{
			return;
		}
		
		SetCursor(hCursorWait);
		save_state();
		hpmfi->eval_standard_revoice(revoicing_dlg.voicelist);
		hpmfi->fill_patchname_list(); // the short names may be changed
		hpmfi->update_mlv_list();
		analyse_changes();
		
		SetCursor(hCursorOld);
		return;
	}
	
	if (result==1)
	{	// Voicefile Revoicing
		int result;
		if (revoicefile_folder_running) return;
		if (hpmfi == NULL)
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
			hpmfi = Selectsource();
			if (hpmfi == NULL)
			{
				return;
			}
		}
		
		// Clear Player from last MIDI-File
		Stop();

		VoicefileRevoicingDlg dlg;
		dlg.p_inifile = o_inifile;
		dlg.hpmfi = hpmfi;
		dlg.hCursorWait = hCursorWait;
		dlg.hCursorOld = hCursorOld;
		result = dlg.DoModal();
		
		if (result != 0)
		{
			return;
		}
		
		save_state();
		SetCursor(hCursorWait);
		hpmfi->eval_voicefile_revoice(dlg.voicefilepath_list);
		analyse_changes();
		SetCursor(hCursorOld);

		// Effect_Filter? 		
		if (hpmfi->is_source_changed())
		{ // ask, if effect-controller (91, 93, 94) and Dry-Level-SysEx should be changed
			if (IDYES == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_CHECK_EFFECT_INTENSENESS),MB_YESNO,0))
			{
				EffectFilterDlg dlg_eff;
				dlg_eff.hpmfi = hpmfi;
				dlg_eff.hCursorWait = hCursorWait;
				dlg_eff.hCursorOld = hCursorOld;
				dlg_eff.DoModal();
			}
			m_undo.EnableWindow(true);
		}
		else
		{
			free_saved_state();
		}
		return;
	}
	
	if (result==10)
	{
		bool singlefile_wanted = false;

		if (revoicefile_folder_running)
		{
			if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_REVOICEFILE_ABORT),MB_YESNO,0)) return;
			revoicefile_folder_abort_wanted = true;
			return;
		}
		
		if (hpmfi == NULL)
		{	// batch wanted?
			CString r;
			r.Format(GlobalUtilities::get_resource_string(IDS_REVOICE_FOLDER));
			if (IDYES != AfxMessageBox(r,MB_YESNO,0))
			{
				::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
				hpmfi = Selectsource();
				if (hpmfi==NULL)
				{
					return;
				}
				else
				{
					singlefile_wanted = true;
				}
			}
			
			if ((hpmfi==NULL) && !singlefile_wanted)
			{
				// initialize batch
				MSG msg;
				revoicefile_folder_running = true;
				revoicefile_folder_abort_wanted = false;
				batch_running = true;
				CString batch_running_text = GlobalUtilities::get_resource_string(IDS_BATCH_RUNNING);
				SetWindowText("PSRUTI         "+batch_running_text);
				
				hThread = CreateThread(
					NULL,	// Security attribute
					0,		// Initial stacksize
					(LPTHREAD_START_ROUTINE)revoicefile_thread_run, // start function in the thread
					this,	// Argument for the start function, here pointer to the actual object
					0,		// Creation flags
					&threadID // Pointer of the thread identifier
					);	
				SetThreadPriority(hThread,THREAD_PRIORITY_BELOW_NORMAL);
				
				// The thread is interrupted all 50 milliseconds.
				// to look for and pump messages.  
				while (WaitForSingleObject(hThread,50) != WAIT_OBJECT_0)
				{
					while ( ::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) 
					{ 
						if (!AfxGetApp()->PumpMessage()) 
						{ 
							break; 
						} 
					}
				}
				
				CloseHandle(hThread);
				
				revoicefile_folder_running = false;
				revoicefile_folder_abort_wanted = false;
				batch_running = false;
				SetDlgItemText(IDC_FILENAME,"");
				SetWindowText("PSRUTI");
				Invalidate();   
				UpdateWindow();
				o_inifile->set_sourcefile("");
				::MessageBox(AfxGetMainWnd()->m_hWnd,
					GlobalUtilities::get_resource_string(IDS_BATCH_PERFORMED),"",MB_OK|MB_TASKMODAL);
				return;
			}
		}
		
		char revoicefile[MAX_PATH];
		if (!ask_for_revoicefile(revoicefile))
		{
			return;
		}
		
		SetCursor(hCursorWait);
		save_state();

		hpmfi->eval_revoice_from_file(revoicefile);
		if (hpmfi->is_source_changed())
		{
			o_inifile->set_revoicefile(revoicefile);
		}
		
		analyse_changes();
		SetCursor(hCursorOld);
		return;
	}

	if (result==11)
	{
		CComputeBanknumberMsbLsb dlg;
		dlg.DoModal();
		return;
	}
}

void CPsrutiDlg::OnUndo()
{
	if (batch_running) return;
	restore_state();
}

void CPsrutiDlg::OnLyricsAtChannelNotes()
{
	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	if (hpmfi->with_lyrics)
	{
		if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_LYRICSREMOVE),MB_YESNO,0))
		{
			return;
		}
		else
		{
			hpmfi->remove_lyrics_chords(LYRICS);
			hpmfi->with_lyrics = false;
		}
	}

	// Clear Player from last MIDI-File
	Stop();

	ImportLyricsAtChannelNotes dlg;

	dlg.hpmfi = hpmfi;

	if (dlg.DoModal() == 0) return; // 0: cancelled, 1: OK

	SetCursor(hCursorWait);
	save_state();

	hpmfi->eval_lyrics_at_channel_notes(dlg.lyricfile, dlg.selected_chan);

	analyse_changes();
	SetCursor(hCursorOld);
}

void CPsrutiDlg::OnChordsLyricsImportExport()
{
	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	// Clear Player from last MIDI-File
	Stop();

	ChordsLyricsImportExport dlg;
	dlg.o_inifile = o_inifile;

	if (dlg.DoModal() == 0) return; // 0: cancelled, 1: OK

	SetCursor(hCursorWait);
	save_state();

	if (dlg.is_import)
	{
		if (dlg.is_chords && hpmfi->with_xfchords)
		{
			if (IDYES != AfxMessageBox(GlobalUtilities::get_resource_string(IDS_WITH_XF_CHORDS),MB_YESNO,0))
			{
				SetCursor(hCursorOld);
				return;
			}
			hpmfi->remove_chords();
		}
		if (dlg.is_lyrics && hpmfi->with_lyrics)
		{
			if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_ADD_LYRICS_TO_OTHERS),MB_YESNO,0))
			{
				SetCursor(hCursorOld);
				return;
			}
		}

		hpmfi->eval_chords_lyrics_from_file(dlg.chord_lyricfile,dlg.is_chords, 
			dlg.is_lyrics, dlg.is_chord_sysex);
	}
	else
	{
		hpmfi->eval_chords_lyrics_export(dlg.chord_lyricfile,dlg.is_chords, 
			dlg.is_lyrics, dlg.is_remove_after, dlg.is_export, dlg.is_export_as_lyrics);
	}
	analyse_changes();
	SetCursor(hCursorOld);
}

void CPsrutiDlg::OnSysex()
{
	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	char sysexfile[MAX_PATH];

	// Clear Player from last MIDI-File
	Stop();
	CSysexDlg dlg;
	dlg.hpmfi = hpmfi;

	if (dlg.DoModal() == 0)
	{
		return;
	}

	bool is_import_file_selected = dlg.selected_file_import();
	bool is_import_paste_selected = dlg.selected_paste_import();
	bool is_export_selected = dlg.selected_export();
	bool with_delete = dlg.with_delete();
	bool is_note_area = dlg.selected_note_area();

	if (!is_import_file_selected &&!is_import_paste_selected && !is_export_selected && !with_delete) return;

	int pos_measure = -1;
	int pos_beat = -1;
	int pos_tick = -1;
	int position = -1;
	bool is_mbt_file;

	if (is_import_file_selected)
	{	// open file
		int i;

		// File Dialog
		char BASED_CODE szFilter[] =
			"Text Files (*.txt)|*.txt||";

		// Clear Function-Texts

		CFileDialog openfile_dlg(TRUE,
			"txt",
			NULL,
			OFN_FILEMUSTEXIST |
			OFN_PATHMUSTEXIST,
			szFilter,
			NULL);

		CString last_prot = o_inifile->get_protfile();
		if (last_prot != "")
		{
			openfile_dlg.m_ofn.lpstrInitialDir = last_prot;
			char lp[MAX_PATH];
			for (i=0; i<last_prot.GetLength(); i++)
			{
				lp[i] = last_prot[i];
			}
			lp[last_prot.GetLength()] = (char)0;
			openfile_dlg.m_ofn.lpstrFile = lp;
		}

		int return_value = openfile_dlg.DoModal();

		if (return_value == IDCANCEL)
		{
			return;
		}
		strcpy(sysexfile,openfile_dlg.m_ofn.lpstrFile);

		// look if mbt file
		is_mbt_file = true; // test
	}

	if (is_note_area && !is_export_selected)
	{
		dlg.new_position(&is_mbt_file,&pos_measure,&pos_beat,&pos_tick);
		if (!is_mbt_file)
		{
			position = hpmfi->get_time_from_takt_bar_tick(pos_measure, pos_beat, pos_tick);
		}
	}

	if (is_import_file_selected)
	{

		SetCursor(hCursorWait);
		save_state();

		if (is_note_area)
		{
			if (is_mbt_file)
			{
				hpmfi->eval_sysex_file_import_mbt(sysexfile);
			}
			else
			{
				hpmfi->eval_sysex_file_import_position(sysexfile,position);
			}
		}
		else
		{
			hpmfi->eval_sysex_file_import(sysexfile);
		}
		if (hpmfi->is_source_changed())
		{
			o_inifile->set_protfile(sysexfile);
		}

		analyse_changes();
		SetCursor(hCursorOld);
		return;
	}

	if (is_import_paste_selected)
	{
		SysexPasteDlg paste_dlg;

		if (paste_dlg.DoModal() == 0) return;
		if (paste_dlg.sysex_chain=="") return;
		
		SetCursor(hCursorWait);
		save_state();

		if (is_note_area)
		{
			hpmfi->eval_sysex_paste_import_note_area(paste_dlg.sysex_chain, position);
		}
		else
		{
			hpmfi->eval_sysex_paste_import(paste_dlg.sysex_chain);
		}

		analyse_changes();
		SetCursor(hCursorOld);

		return;
	}

	if (is_export_selected || with_delete)
	{
		CString protfile;

		if (is_export_selected)
		{
	 		protfile = dlg.get_protfile();
			if (protfile == "") return;
		}
		else
		{
			protfile = "";
		}

		SetCursor(hCursorWait);
		if (with_delete)
		{
			save_state();
		}
		char *pf;
		GlobalUtilities::convert_CString_to_cstring(&pf,protfile);
		if (is_note_area)
		{
			hpmfi->eval_sysex_export_note_area(pf, with_delete);
		}
		else
		{
			hpmfi->eval_sysex_export(pf, with_delete);
		}

		delete[] pf;
		analyse_changes();
		SetCursor(hCursorOld);
		return;
	}
}


void CPsrutiDlg::OnController() 
{
	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	// Clear Player from last MIDI-File
	Stop();

	CControllerEffectsDlg dlg;
	dlg.hpmfi = hpmfi;
	dlg.hCursorWait = hCursorWait;
	dlg.hCursorOld = hCursorOld;
	save_state();
	if (dlg.DoModal() == 0)
	{  // no _changes
		free_saved_state();
	}
	else
	{	// changes
		m_undo.EnableWindow(true);
		source_changed = true;
	}
}


void CPsrutiDlg::OnExchangeChannels() 
{
	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	// Clear Player from last MIDI-File
	Stop();

	ExchangeChannelsDlg dlg;
	dlg.hpmfi = hpmfi;

	if (dlg.DoModal() == 0) return; // 0: cancelled, 1: OK
    // Set the predefined Windows "Wait" cursor.

	SetCursor(hCursorWait);

	save_state();
	hpmfi->eval_exchange_channels(dlg.selection, dlg.source_channels, dlg.dest_channel);
	analyse_changes();

	// Set the old cursor back
	SetCursor(hCursorOld);
	
	
}

void CPsrutiDlg::OnExtras() 
{
	if (batch_running) return;

	Extras_Dlg dlg;
	dlg.hpmfi = hpmfi;
	dlg.mainfun = this;
	dlg.hCursorWait = hCursorWait;
	dlg.hCursorOld = hCursorOld;
	dlg.batch_running = batch_running;
	dlg.o_inifile = o_inifile;
	dlg.DoModal();
}


void CPsrutiDlg::OnLyricsChordsEditor() 
{

	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	// Clear Player from last MIDI-File
	Stop();


	CChordsLyricsEditor dlg;
	dlg.hpmfi = hpmfi;
	dlg.logf = lf;
	dlg.o_inifile = o_inifile;
	dlg.linefeed_char = GlobalUtilities::get_linefeed_char();

	int result = dlg.DoModal();
	if (result == -1) return;

	SetCursor(hCursorWait);
	save_state();
	hpmfi->eval_lyrics_chords_editor(&dlg.lce_array);
	analyse_changes();

	// Set the old cursor back
	SetCursor(hCursorOld);
}


void CPsrutiDlg::OnFileFormat() 
{
	bool singlefile_wanted = false;
	
	// Clear Player from last MIDI-File
	Stop();

	if (revoicefile_folder_running || 
		xg_convert_folder_running || 
		gm_convert_folder_running || 
		print_folder_running ||
		count_in_folder_running ||
		expr_main_volume_folder_running ||
		fill_lyric_folder_running ||
		drum_folder_running) 
	{
		return;
	}

	if (fileformat_folder_running)
	{
		if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_FILEFORMAT_ABORT),MB_YESNO,0)) return;
		fileformat_folder_abort_wanted = true;
		return;
	}

	if (hpmfi == NULL)
	{
		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_FILEFORMAT_FOLDER));

		if (IDYES != AfxMessageBox(r,MB_YESNO,0))
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
			hpmfi = Selectsource();
			if (hpmfi==NULL)
			{
				return;
			}
			else
			{
				singlefile_wanted = true;
			}

		}

		if ((hpmfi==NULL) && !singlefile_wanted)
		{
			// initiate batch
			MSG msg;
			fileformat_folder_running = true;
			fileformat_folder_abort_wanted = false;
			batch_running = true;
			CString batch_running_text = GlobalUtilities::get_resource_string(IDS_BATCH_RUNNING);
			SetWindowText("PSRUTI         "+batch_running_text);

			hThread = CreateThread(
				NULL,	// Security attribute
				0,		// Initial stacksize
				(LPTHREAD_START_ROUTINE)fileformat_thread_run, // start function in the thread
				this,	// Argument for the start function, here pointer to the actual object
				0,		// Creation flags
				&threadID // Pointer of the thread identifier
							);	
			SetThreadPriority(hThread,THREAD_PRIORITY_BELOW_NORMAL);

			// The thread is interrupted all 50 milliseconds.
			// to look for and pump messages.  
			while (WaitForSingleObject(hThread,50) != WAIT_OBJECT_0)
			{
				while ( ::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) 
				{ 
					if (!AfxGetApp()->PumpMessage()) 
					{ 
						break; 
					} 
				}
			}

			CloseHandle(hThread);

			fileformat_folder_running = false;
			fileformat_folder_abort_wanted = false;
			batch_running = false;
			SetDlgItemText(IDC_FILENAME,"");
			SetWindowText("PSRUTI");
			Invalidate();   
			UpdateWindow();
			o_inifile->set_sourcefile("");
			::MessageBox(AfxGetMainWnd()->m_hWnd,
				GlobalUtilities::get_resource_string(IDS_BATCH_PERFORMED),"",MB_OK|MB_TASKMODAL);
			return;
		}
	}

	// Analyse single file
	CString sourcefile;
	CString songname;
	CString copyright;
	bool with_additional_chunks;
	CString format;
	CString sub_format;
	int ppqn;
	CString takt;
	double tempo;
	CString key;
	bool lyrics;
	bool chords;
	bool count_in;
	int no_measures, duration;
	CString vh_channels;

	hpmfi->source_attributes(&sourcefile, &songname, &copyright, &with_additional_chunks, &format,&sub_format,
		&ppqn,&takt,&tempo,&key,&lyrics,&chords,&count_in,&no_measures,&duration,&vh_channels);

	FileAttributesDlg dlg;

	CString r = sourcefile;
/*
	if(with_additional_chunks)
	{
		CString newline = "\n";
		r += newline + GlobalUtilities::get_resource_string(IDS_MORE_CHUNKS_SHORT);
	}
*/
//	MessageBox(r);
	dlg.hpmfi = hpmfi;
	dlg.sourcefile = r;
	dlg.copyright = copyright;
	dlg.with_additional_chunks = with_additional_chunks;
	dlg.songname = songname;
	dlg.format = format;
	dlg.sub_format = sub_format;
	dlg.original_ppqn = hpmfi->original_ppqn;
	dlg.takt = takt;
	dlg.tempo = tempo;
	dlg.key = key;
	dlg.lyrics = lyrics;
	dlg.chords = chords;
	dlg.vh_channels = vh_channels;
	dlg.count_in = count_in;
	dlg.no_measures = no_measures;
	dlg.duration = duration;
	dlg.DoModal();
	analyse_changes();
/*
	r.Format("%s, %s, %s, %s, PPQN=%i, %s, tempo %4.2f, takt %s, key %s, %s, %s, last measure %i, duration %i sec, vh_channels %s",
		sourcefile, copyright, format, sub_format, ppqn, 
		hpmfi->with_additional_chunks?"with additional chunks":"no additional chunks",
		tempo,takt,key, (CString)(lyrics?"with":"without")+" lyrics",
		(CString)(chords?"with":"without")+" chords",no_measures, duration,vh_channels);
	MessageBox(r);
*/


}


void CPsrutiDlg::OnPreferences() 
{
	CPreferencesDlg dlg;
	dlg.batch_running = batch_running;
	dlg.hpmfi = hpmfi;
	dlg.pdlg = pdlg;
	dlg.o_inifile = o_inifile;
	dlg.hCursorOld = hCursorOld;
	dlg.hCursorWait = hCursorWait;
	dlg.mainfun = this;
	dlg.DoModal();
}

bool CPsrutiDlg::ask_for_drumfile(char* drumfile)
{

	int i;
	// File Dialog
	char BASED_CODE szFilter[] =
		"Text Files (*.txt)|*.txt||";
		
	// Clear Function-Texts
		
	CFileDialog openfile_dlg(TRUE,
		"txt",
		NULL,
		OFN_FILEMUSTEXIST |
		OFN_PATHMUSTEXIST,
		szFilter,
		NULL);
	
	CString last_file = o_inifile->get_drumfile();

	if (last_file != "")
	{
		openfile_dlg.m_ofn.lpstrInitialDir = last_file;
		char lf[MAX_PATH];
		for (i=0; i<last_file.GetLength(); i++)
		{
			lf[i] = last_file[i];
		}
		lf[last_file.GetLength()] = (char)0;
		openfile_dlg.m_ofn.lpstrFile = lf;
	}
	
	CString cstrtitle = GlobalUtilities::get_resource_string(IDS_DRUMFILE_BOXTITLE);
	char* ctitle;
	GlobalUtilities::convert_CString_to_cstring(&ctitle, cstrtitle);
	openfile_dlg.m_ofn.lpstrTitle = ctitle;
	int return_value = openfile_dlg.DoModal();
	delete[] ctitle;
	
	if (return_value == IDCANCEL)
	{
		return false;
	}
	
	strcpy(drumfile,openfile_dlg.m_ofn.lpstrFile);
	return true;
}


void CPsrutiDlg::OnDrums() 
{
	if (revoicefile_folder_running || 
		xg_convert_folder_running || 
		gm_convert_folder_running || 
		print_folder_running ||
		count_in_folder_running ||
		expr_main_volume_folder_running ||
		fill_lyric_folder_running ||
		fileformat_folder_running ) 
	{
		return;
	}

	if (drum_folder_running)
	{
		if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_DRUMFOLDER_ABORT),MB_YESNO,0)) return;
		drum_folder_abort_wanted = true;
		return;
	}

	Drums dlg;

	int funct = dlg.DoModal();

	if (funct == -1)
	{	// Cancel
		return;
	}

	if (funct == 0) 
	{	// Change Drums from drumfile

		bool singlefile_wanted = false;

		if (hpmfi == NULL)
		{
			CString r;
			r.Format(GlobalUtilities::get_resource_string(IDS_DRUMFOLDER));
			if (IDYES != AfxMessageBox(r,MB_YESNO,0))
			{
				::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
				hpmfi = Selectsource();

				if (hpmfi==NULL)
				{
					return;
				}
				else
				{
					singlefile_wanted = true;
				}
			}
			
			if ((hpmfi==NULL) && !singlefile_wanted)
			{
				// initialize batch
				MSG msg;
				drum_folder_running = true;
				drum_folder_abort_wanted = false;
				batch_running = true;
				CString batch_running_text = GlobalUtilities::get_resource_string(IDS_BATCH_RUNNING);
				SetWindowText("PSRUTI         "+batch_running_text);
				
				hThread = CreateThread(
					NULL,	// Security attribute
					0,		// Initial stacksize
					(LPTHREAD_START_ROUTINE)drum_thread_run, // start function in the thread
					this,	// Argument for the start function, here pointer to the actual object
					0,		// Creation flags
					&threadID // Pointer of the thread identifier
					);

				SetThreadPriority(hThread,THREAD_PRIORITY_BELOW_NORMAL);
				
				// The thread is interrupted all 50 milliseconds.
				// to look for and pump messages.  
				while (WaitForSingleObject(hThread,50) != WAIT_OBJECT_0)
				{
					while ( ::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) 
					{ 
						if (!AfxGetApp()->PumpMessage()) 
						{ 
							break; 
						} 
					}
				}
				
				CloseHandle(hThread);
				
				drum_folder_running = false;
				drum_folder_abort_wanted = false;
				batch_running = false;
				SetDlgItemText(IDC_FILENAME,"");
				SetWindowText("PSRUTI");
				Invalidate();   
				UpdateWindow();
				o_inifile->set_sourcefile("");
				::MessageBox(AfxGetMainWnd()->m_hWnd,
					GlobalUtilities::get_resource_string(IDS_BATCH_PERFORMED),"",MB_OK|MB_TASKMODAL);
				return;
			}
		}

		// single file
		
		char drumfile[MAX_PATH];
		if (!ask_for_drumfile(drumfile))
		{
			return;
		}
	
		SetCursor(hCursorWait);
		save_state();
		hpmfi->eval_drum_from_file(drumfile, drum_folder_running);

		o_inifile->set_drumfile(drumfile);
		
		analyse_changes();
		SetCursor(hCursorOld);
		return;
	}

	if (funct == 1)
	{	// Change Drums (Dialog)
		if (batch_running) return;

		if (hpmfi == NULL)
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
			hpmfi = Selectsource();
			if (hpmfi == NULL)
			{
				return;
			}
		}

		ChangeDrumVoicesDlg drum_dlg;
		drum_dlg.hpmfi = hpmfi;
		drum_dlg.p_inifile = o_inifile;
		drum_dlg.hCursorWait = hCursorWait;
		drum_dlg.hCursorOld = hCursorOld;

		save_state();
		int result = drum_dlg.DoModal();
		if (result==0)
		{
			analyse_changes();
		}
		return;
	}
}

void CPsrutiDlg::OnGmConvert() 
{
	bool singlefile_wanted = false;

	if (revoicefile_folder_running || 
		xg_convert_folder_running || 
		drum_folder_running || 
		print_folder_running ||
		count_in_folder_running ||
		expr_main_volume_folder_running ||
		fill_lyric_folder_running ||
		fileformat_folder_running ) 
	{
		return;
	}

	if (gm_convert_folder_running)
	{
		if (IDNO == AfxMessageBox(GlobalUtilities::get_resource_string(IDS_GM_CONVERT_ABORT),MB_YESNO,0)) return;
		gm_convert_folder_abort_wanted = true;
		return;
	}

	if (hpmfi == NULL)
	{
		CString r;
		r.Format(GlobalUtilities::get_resource_string(IDS_GM_CONVERT_FOLDER));
		if (IDYES != AfxMessageBox(r,MB_YESNO,0))
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
			hpmfi = Selectsource();
			if (hpmfi==NULL)
			{
				return;
			}
			else
			{
				singlefile_wanted = true;
			}
		}
		
		if ((hpmfi==NULL) && !singlefile_wanted)
		{
			// initiate batch
			MSG msg;
			gm_convert_folder_running = true;
			batch_running = true;
			gm_convert_folder_abort_wanted = false;
			CString batch_running_text = GlobalUtilities::get_resource_string(IDS_BATCH_RUNNING);
			SetWindowText("PSRUTI         "+batch_running_text);

			hThread = CreateThread(
				NULL,	// Security attribute
				0,		// Initial stacksize
				(LPTHREAD_START_ROUTINE)gm_convert_thread_run, // start function in the thread
				this,	// Argument for the start function, here pointer to the actual object
				0,		// Creation flags
				&threadID // Pointer of the thread identifier
							);	
			SetThreadPriority(hThread,THREAD_PRIORITY_BELOW_NORMAL);

			// The thread is interrupted all 50 milliseconds.
			// to look for and pump messages.  
			while (WaitForSingleObject(hThread,50) != WAIT_OBJECT_0)
			{
				while ( ::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) 
				{ 
					if (!AfxGetApp()->PumpMessage()) 
					{ 
						break; 
					} 
				}
			}

			CloseHandle(hThread);

			gm_convert_folder_running = false;
			gm_convert_folder_abort_wanted = false;
			batch_running = false;
			SetDlgItemText(IDC_FILENAME,"");
			SetWindowText("PSRUTI");
			Invalidate();   
			UpdateWindow();
			o_inifile->set_sourcefile("");
			::MessageBox(AfxGetMainWnd()->m_hWnd,
				GlobalUtilities::get_resource_string(IDS_BATCH_PERFORMED),"",MB_OK|MB_TASKMODAL);
			return;
		}
	}

	// single file

    // Set the predefined Windows "Wait" cursor.
	SetCursor(hCursorWait);

	// Clear Player from last MIDI-File
	Stop();
	save_state();

	bool done = hpmfi->eval_gm_convert();

	SetCursor(hCursorOld);
	if (done)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,
			GlobalUtilities::get_resource_string(IDS_CONVERSION_ACCOMPLISHED),"",MB_OK|MB_TASKMODAL);
		OnSaveAs();
	}
}

void CPsrutiDlg::OnDeleteFillLyrics() 
{
	if (batch_running) return;
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = Selectsource();
		if (hpmfi == NULL)
		{
			return;
		}
	}

	// Clear Player from last MIDI-File
	Stop();

	CString taktlyric = "";
	CString beatlyric = "";
	CString endlyric  = "";

	int user = o_inifile->get_user();

	if (user==1)
	{
		taktlyric = o_inifile->get_user1_taktlyric();
		beatlyric = o_inifile->get_user1_beatlyric();
		endlyric  = o_inifile->get_user1_endlyric();
	}
	else if (user==2)
	{
		taktlyric = o_inifile->get_user2_taktlyric();
		beatlyric = o_inifile->get_user2_beatlyric();
		endlyric  = o_inifile->get_user2_endlyric();
	}
	else if (user==3)
	{
		taktlyric = o_inifile->get_user3_taktlyric();
		beatlyric = o_inifile->get_user3_beatlyric();
		endlyric  = o_inifile->get_user3_endlyric();
	}

	CDelete_Fill_Lyrics_Dlg dlg;
	dlg.hpmfi = hpmfi;
	dlg.taktlyric = taktlyric;
	dlg.beatlyric = beatlyric;
	dlg.endlyric = endlyric;

	if (dlg.DoModal() == -1) return;

	taktlyric = dlg.taktlyric;
	beatlyric = dlg.beatlyric;
	endlyric = dlg.endlyric;

	taktlyric.Delete(taktlyric.GetLength()-1,1);
	taktlyric.Delete(0,1);
	beatlyric.Delete(beatlyric.GetLength()-1,1);
	beatlyric.Delete(0,1);
	endlyric.Delete(endlyric.GetLength()-1,1);
	endlyric.Delete(0,1);

	int no_deleted = hpmfi->eval_delete_fill_lyrics(taktlyric, beatlyric, endlyric);

	CString r;
	r.Format(GlobalUtilities::get_resource_string(IDS_NO_FL_DELETED), no_deleted);

	::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);

	analyse_changes();
}
