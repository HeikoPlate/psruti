// PreferencesDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "GlobalUtilities.h"
#include "PreferencesDlg.h"
#include "SelectMIDIDevice.h"
#include "InsDefOnOffDlg.h"
#include "InsdefDlg.h"
#include "XG_effectdef_on_of_dlg.h"
#include "XG_effectdefdlg.h"
#include "FillLyricsLinefeedDlg.h"
#include "SpecialPreferences.h"
#include "XgEffects.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPreferencesDlg 


CPreferencesDlg::CPreferencesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPreferencesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPreferencesDlg)
	//}}AFX_DATA_INIT
	local_mf = NULL;
	m_pToolTip = NULL;
}


void CPreferencesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreferencesDlg)
	DDX_Control(pDX, IDC_XG_EFFECTDEF, m_xg_effectdef);
	DDX_Control(pDX, IDC_INSDEF, m_insdef);
	DDX_Control(pDX, IDC_SPECIAL_PREFERENCES, m_special_preferences);
	DDX_Control(pDX, IDC_FILL_LYRICS_LINEFEED, m_fill_lyrics_linefeed);
	DDX_Control(pDX, IDC_SELECT_MIDI_DEVICE, m_select_midi_device);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreferencesDlg, CDialog)
	//{{AFX_MSG_MAP(CPreferencesDlg)
	ON_BN_CLICKED(IDC_SELECT_MIDI_DEVICE, OnSelectMidiDevice)
	ON_BN_CLICKED(IDC_INSDEF, OnInsdef)
	ON_BN_CLICKED(IDC_FILL_LYRICS_LINEFEED, OnFillLyricsLinefeed)
	ON_BN_CLICKED(IDC_SPECIAL_PREFERENCES, OnSpecialPreferences)
	ON_BN_CLICKED(IDC_XG_EFFECTDEF, OnXgEffectdef)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CPreferencesDlg 


BOOL CPreferencesDlg::PreTranslateMessage(MSG* pMSG)
{
	if (NULL != m_pToolTip)
	{
		m_pToolTip->RelayEvent(pMSG);
	}
	return CDialog::PreTranslateMessage(pMSG);
}

BOOL CPreferencesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString midiport = o_inifile->get_midiport();
	SetDlgItemText(IDC_MIDI_PORT,midiport);
	
	
	CString insfile = o_inifile->get_insdeffile();
	CString insdef = o_inifile->get_insdef();
	
	if ((insfile != "") && (insdef != ""))
	{
		CString short_filename = insfile;
		if (insfile.GetLength()>55)
		{
			short_filename = "..."+insfile.Right(52);
		}
		SetDlgItemText(IDC_INSDEFFILENAME,short_filename + " (" + insdef + ")");
	}
	else
	{
		SetDlgItemText(IDC_INSDEFFILENAME,"");
	}

	CString xgeffectfile = o_inifile->get_xgeffectfile();
	CString keyboardmodel = o_inifile->get_keyboardmodel();

	if (xgeffectfile!="")
	{
		CFileFind finder;
		if (!finder.FindFile(xgeffectfile))
		{ // file does not exist
			o_inifile->set_xgeffectfile("");
			o_inifile->set_keyboardmodel("");
			xgeffectfile = "";
			keyboardmodel = "";
		}
	}
	
	if ((xgeffectfile != "") && (keyboardmodel != ""))
	{
		CString short_filename = xgeffectfile;
		if (xgeffectfile.GetLength()>55)
		{
			short_filename = "..."+xgeffectfile.Right(52);
		}
		SetDlgItemText(IDC_XG_DEF_FILENAME,short_filename + " (" + keyboardmodel + ")");
	}
	else
	{
		SetDlgItemText(IDC_XG_DEF_FILENAME,"");
	}

	// Tool Tips
	m_pToolTip = new CToolTipCtrl;
	m_pToolTip->Create(this);
	m_pToolTip->SetDelayTime(TTDT_AUTOPOP,4000);
	m_pToolTip->SetMaxTipWidth(400);

	m_pToolTip->AddTool(&m_select_midi_device,GlobalUtilities::get_resource_string(IDS_SELECT_MIDI_DEVICE));
	m_pToolTip->AddTool(&m_insdef,GlobalUtilities::get_resource_string(IDS_INSDEF));
	m_pToolTip->AddTool(&m_fill_lyrics_linefeed,GlobalUtilities::get_resource_string(IDS_FILL_LYRICS_LINEFEED));
	m_pToolTip->AddTool(&m_special_preferences,GlobalUtilities::get_resource_string(IDS_SPECIAL_PREFERENCES));
	m_pToolTip->AddTool(&m_xg_effectdef,GlobalUtilities::get_resource_string(IDS_XG_EFFECTDEF));

	m_pToolTip->Activate(true);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CPreferencesDlg::OnSpecialPreferences() 
{
	if (hpmfi != NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_DONT_LOAD_SOURCE),NULL,MB_OK|MB_TASKMODAL);
		return;
	}
	CSpecialPreferences dlg;
	dlg.o_inifile = o_inifile;
	dlg.DoModal();
}

void CPreferencesDlg::OnOK() 
{
	if (m_pToolTip != NULL)
	{
		delete m_pToolTip;
		m_pToolTip = NULL;
	}

	CDialog::OnOK();
}





void CPreferencesDlg::OnSelectMidiDevice() 
{

	if (batch_running) return;
	if (hpmfi != NULL)
	{
		if (hpmfi->mf != NULL)
		{
			if (HP_IsPlaying(hpmfi->mf)&&(pdlg != NULL))
			{
				pdlg->Stop();
			}
		}
	}

	int id;

	// open dlg for selection and get back the device-id
	// look at class SelectMIDIDevice

	SelectMIDIDevice dlg;
	dlg.p_inifile = o_inifile;

	id = dlg.DoModal();

	// select device
	HP_SelectMIDIDevice(id);

	CString midiport = o_inifile->get_midiport();
	SetDlgItemText(IDC_MIDI_PORT,midiport);
}

void CPreferencesDlg::OnInsdef() 
{
	CString insfile;
	bool result;
	int i;

	InsDefOnOffDlg dlg;
	int what_to_do = dlg.DoModal();

	if (what_to_do == -1) return; // Cancel

	if ( what_to_do == 0) // free
	{
		SetDlgItemText(IDC_INSDEFFILENAME,"");
		SetDlgItemText(IDC_INSDEFNAME,"");
		o_inifile->set_insdeffile("");
		o_inifile->set_insdef("");

		if (hpmfi != NULL)
		{

			if (hpmfi->bank_list != NULL)
			{
				HP_Delete(hpmfi->bank_list);
				hpmfi->bank_list = NULL;
				hpmfi->no_banks = 0;
			}

			hpmfi->with_insdef = false;
			hpmfi->find_insfile_bank_voicenames();
			hpmfi->bank_voices_list_free = 0;
			return;
		}
		return;
	}

	// what_to_do == 1: import

	char BASED_CODE szFilter[] = 
		"Cakewalk Instrument Definition Files (*.ins)|*.ins|All Files (*.*)|*.*||";
		
	CFileDialog openfile_dlg(TRUE,
						  "mid",
						  NULL,
						  OFN_FILEMUSTEXIST |
						  OFN_PATHMUSTEXIST,
						  szFilter,
						  NULL);

	// Get last_insfile
	CString last_insfile = o_inifile->get_insdeffile();

	if (last_insfile != "")
	{
	   openfile_dlg.m_ofn.lpstrInitialDir = last_insfile;
	   char ls[MAX_PATH];
	   for (i=0; i<last_insfile.GetLength(); i++)
	   {
		   ls[i] = last_insfile[i];
	   }
	   ls[last_insfile.GetLength()] = (char)0;
	   openfile_dlg.m_ofn.lpstrFile = ls;
	}
	
	int return_value = openfile_dlg.DoModal();

	if (return_value == IDOK)
	{
		insfile = openfile_dlg.m_ofn.lpstrFile;

		SetCursor(hCursorWait);
		if (hpmfi != NULL)
		{
			result = hpmfi->open_insdeffile(insfile);
		}
		else
		{
			char *cfile;
			local_mf = HP_Init();
			if (local_mf == NULL) return;
			GlobalUtilities::convert_CString_to_cstring(&cfile,insfile);
			result = (HP_CWInsLoad(local_mf,cfile)==HP_ERR_NONE);
			delete[] cfile;
		}


		SetCursor(hCursorOld);	

		if (!result)
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_OPEN_INSDEFFILE),NULL,MB_OK|MB_TASKMODAL);
			return;
		}
	}
	else if (return_value == IDCANCEL)
	{
		return;
	}

	InsdefDlg insdef_dlg;
	insdef_dlg.hCursorWait = hCursorWait;
	insdef_dlg.hCursorOld = hCursorOld;
	insdef_dlg.hpmfi = hpmfi;
	insdef_dlg.local_mf = local_mf;

	if ((insdef_dlg.DoModal() == IDCANCEL) || (insdef_dlg.insdef==""))
	{
		return;
	}

	if ((insfile != "") && (insdef_dlg.insdef != ""))
	{

		CString short_filename = insfile;
		if (insfile.GetLength()>55)
		{
			short_filename = "..."+insfile.Right(52);
		}

		CString insdef = insdef_dlg.insdef;
		SetDlgItemText(IDC_INSDEFFILENAME,short_filename + " (" + insdef + ")");
	
		o_inifile->set_insdeffile(insfile);
		o_inifile->set_insdef(insdef_dlg.insdef);
		if (hpmfi != NULL)
		{
			hpmfi->with_insdef = true;
		}
	}
	else
	{

		SetDlgItemText(IDC_INSDEFFILENAME,"");

		if (hpmfi != NULL)
		{
			if (hpmfi->bank_list != NULL)
			{
				HP_Delete(hpmfi->bank_list);
				hpmfi->bank_list = NULL;
				hpmfi->no_banks = 0;
			}
			hpmfi->with_insdef = false;
		}
	}
	if (hpmfi != NULL)
	{
		if (hpmfi->bank_list != NULL)
		{
			HP_Delete(hpmfi->bank_list);
			hpmfi->bank_list = NULL;
			hpmfi->no_banks = 0;
		}
		hpmfi->bank_voices_list_free = 0;
		hpmfi->find_insfile_bank_voicenames();
	}

	if (local_mf != NULL) HP_Free(local_mf);
	local_mf = NULL;
}

void CPreferencesDlg::OnXgEffectdef() 
{
	CString xg_effectfile;
	int i;
	XG_effectdef_on_of_dlg dlg;
	int what_to_do = dlg.DoModal();
	if (what_to_do == -1) return; // Cancel

	
	if (hpmfi == NULL)
	{
		/**** free XG effectfile and keyboardmodel ********/
		if ( what_to_do == 0) 
		{ 
			SetDlgItemText(IDC_XG_DEF_FILENAME,"");
			o_inifile->set_xgeffectfile("");
			o_inifile->set_keyboardmodel("");
			return;
		} // end free XG effectfile and keyboardmodel

		/**** select XG effectfile and keyboardmodel ******/
		if ( what_to_do == 1) 
		{ 
			char BASED_CODE szFilter[] = 
			"XG Effect Definition Files (*.4xg)|*.4xg|All Files (*.*)|*.*||";

			CFileDialog openfile_dlg(TRUE,
								    "4xg",
								    NULL,
								    OFN_HIDEREADONLY |
								    OFN_FILEMUSTEXIST |
								    OFN_PATHMUSTEXIST,
							        szFilter,
		   					        NULL);

			SetDlgItemText(IDC_XG_DEF_FILENAME,"");

			CString last_xg_effectfile = o_inifile->get_xgeffectfile();

			if (last_xg_effectfile != "")
			{
				openfile_dlg.m_ofn.lpstrInitialDir = last_xg_effectfile;
				char ls[MAX_PATH];
				for (i=0; i<last_xg_effectfile.GetLength(); i++)
				{
					ls[i] = last_xg_effectfile[i];
				}
				ls[last_xg_effectfile.GetLength()] = (char)0;
				openfile_dlg.m_ofn.lpstrFile = ls;
			}

			int return_value = openfile_dlg.DoModal();

			if (return_value == IDOK)
			{
				xg_effectfile = openfile_dlg.m_ofn.lpstrFile;
			}
			else
			{
				return;
			}

			XgEffects *xg_effects = new XgEffects(xg_effectfile);
			CArray <CString,CString> instruments;
			xg_effects->get_instruments(&instruments);

			XG_effectdefdlg effectdefdlg;
			effectdefdlg.instruments = &instruments;

			return_value = effectdefdlg.DoModal();

			if (return_value == -1)
			{
				SetDlgItemText(IDC_XG_DEF_FILENAME,"");
				delete xg_effects;
				return;
			}

			if (return_value == 1)
			{
				CString keyboardmodel = effectdefdlg.get_keyboardmodel();

				o_inifile->set_xgeffectfile(xg_effectfile);
				o_inifile->set_keyboardmodel(keyboardmodel);

				CString short_filename = xg_effectfile;
				if (xg_effectfile.GetLength()>55)
				{
					short_filename = "..."+xg_effectfile.Right(52);
				}
				SetDlgItemText(IDC_XG_DEF_FILENAME,short_filename + " (" + keyboardmodel + ")");
				delete xg_effects;
				return;
			}
			delete xg_effects;
			return;
		}
		return;
	}
	else
	{
		/**** free XG effectfile and keyboardmodel ********/
		if ( what_to_do == 0) 
		{ 
			if (hpmfi->xg_effects != NULL)
			{
				SetDlgItemText(IDC_XG_DEF_FILENAME,"");
				o_inifile->set_xgeffectfile("");
				o_inifile->set_keyboardmodel("");
				delete (hpmfi->xg_effects);
				hpmfi->xg_effects = NULL;
			}
			else
			{
				// nothing to do
			}
			return;
		} // end free XG effectfile and keyboardmodel

		/**** select XG effectfile and keyboardmodel ******/
		if ( what_to_do == 1) 
		{ 
			char BASED_CODE szFilter[] = 
			"XG Effect Definition Files (*.4xg)|*.4xg|All Files (*.*)|*.*||";

			CFileDialog openfile_dlg(TRUE,
								    "4xg",
								    NULL,
								    OFN_HIDEREADONLY |
								    OFN_FILEMUSTEXIST |
								    OFN_PATHMUSTEXIST,
							        szFilter,
		   					        NULL);

			if (hpmfi->xg_effects != NULL)
			{
				delete (hpmfi->xg_effects);
				hpmfi->xg_effects = NULL;
				SetDlgItemText(IDC_XG_DEF_FILENAME,"");
			}

			CString last_xg_effectfile = o_inifile->get_xgeffectfile();

			if (last_xg_effectfile != "")
			{
				openfile_dlg.m_ofn.lpstrInitialDir = last_xg_effectfile;
				char ls[MAX_PATH];
				for (i=0; i<last_xg_effectfile.GetLength(); i++)
				{
					ls[i] = last_xg_effectfile[i];
				}
				ls[last_xg_effectfile.GetLength()] = (char)0;
				openfile_dlg.m_ofn.lpstrFile = ls;
			}

			int return_value = openfile_dlg.DoModal();

			if (return_value == IDOK)
			{
				xg_effectfile = openfile_dlg.m_ofn.lpstrFile;
			}
			else
			{
				return;
			}

			hpmfi->xg_effects = new XgEffects(xg_effectfile);
			CArray <CString,CString> instruments;
			(hpmfi->xg_effects)->get_instruments(&instruments);

			XG_effectdefdlg effectdefdlg;
			effectdefdlg.instruments = &instruments;

			return_value = effectdefdlg.DoModal();
			if (return_value == -1)
			{
				delete (hpmfi->xg_effects);
				hpmfi->xg_effects = NULL;
				SetDlgItemText(IDC_XG_DEF_FILENAME,"");
				return;
			}

			if (return_value == 1)
			{
				CString keyboardmodel = effectdefdlg.get_keyboardmodel();
				(hpmfi->xg_effects)->ReadEffectFile(keyboardmodel);
				o_inifile->set_xgeffectfile(xg_effectfile);
				o_inifile->set_keyboardmodel(keyboardmodel);

				CString short_filename = xg_effectfile;
				if (xg_effectfile.GetLength()>55)
				{
					short_filename = "..."+xg_effectfile.Right(52);
				}
				SetDlgItemText(IDC_XG_DEF_FILENAME,short_filename + " (" + keyboardmodel + ")");

				return;
			}
			return;
		}
	}
}


void CPreferencesDlg::OnFillLyricsLinefeed() 
{
	CFillLyricsLinefeedDlg dlg;
	int is_user = o_inifile->get_user();
	CString user1_takt_lyric, user1_beat_lyric, user1_end_lyric;
	int user1_linefeedlyrictick;
	CString user2_takt_lyric, user2_beat_lyric, user2_end_lyric;
	int user2_linefeedlyrictick;
	CString user3_takt_lyric, user3_beat_lyric, user3_end_lyric;
	int user3_linefeedlyrictick;

	// fill lyrics
	user1_takt_lyric = o_inifile->get_user1_taktlyric();
	user1_takt_lyric = user1_takt_lyric.Mid(1,user1_takt_lyric.GetLength()-2);
	user1_beat_lyric = o_inifile->get_user1_beatlyric();
	user1_beat_lyric = user1_beat_lyric.Mid(1,user1_beat_lyric.GetLength()-2);
	user1_end_lyric = o_inifile->get_user1_endlyric();
	user1_end_lyric = user1_end_lyric.Mid(1,user1_end_lyric.GetLength()-2);
	user1_linefeedlyrictick = o_inifile->get_user1_linefeedlyrictick();

	user2_takt_lyric = o_inifile->get_user2_taktlyric();
	user2_takt_lyric = user2_takt_lyric.Mid(1,user2_takt_lyric.GetLength()-2);
	user2_beat_lyric = o_inifile->get_user2_beatlyric();
	user2_beat_lyric = user2_beat_lyric.Mid(1,user2_beat_lyric.GetLength()-2);
	user2_end_lyric = o_inifile->get_user2_endlyric();
	user2_end_lyric = user2_end_lyric.Mid(1,user2_end_lyric.GetLength()-2);
	user2_linefeedlyrictick = o_inifile->get_user2_linefeedlyrictick();

	user3_takt_lyric = o_inifile->get_user3_taktlyric();
	user3_takt_lyric = user3_takt_lyric.Mid(1,user3_takt_lyric.GetLength()-2);
	user3_beat_lyric = o_inifile->get_user3_beatlyric();
	user3_beat_lyric = user3_beat_lyric.Mid(1,user3_beat_lyric.GetLength()-2);
	user3_end_lyric = o_inifile->get_user3_endlyric();
	user3_end_lyric = user3_end_lyric.Mid(1,user3_end_lyric.GetLength()-2);
	user3_linefeedlyrictick = o_inifile->get_user3_linefeedlyrictick();

	dlg.set_user(is_user);
	dlg.set_user1_fill_lyric_data(user1_takt_lyric, user1_beat_lyric, user1_end_lyric, user1_linefeedlyrictick);
	dlg.set_user2_fill_lyric_data(user2_takt_lyric, user2_beat_lyric, user2_end_lyric, user2_linefeedlyrictick);
	dlg.set_user3_fill_lyric_data(user3_takt_lyric, user3_beat_lyric, user3_end_lyric, user3_linefeedlyrictick);
	
	dlg.hpmfi = hpmfi;
	if (hpmfi != NULL)
	{
		dlg.logf = hpmfi->lf;
	}
	else
	{
		dlg.logf = NULL;
	}


	int return_value = dlg.DoModal();

	if (return_value==-1)
	{
		return;
	}

	SetCursor(hCursorWait);
	if (hpmfi != NULL)
	{
		mainfun->save_state();
	}

	is_user = dlg.is_user;
	if (hpmfi != NULL)
	{
		hpmfi->set_is_user(is_user);
	}
	o_inifile->set_user(is_user);


	switch(is_user)
	{
	case 1:
		{
			// fill takt_lyric
			CString tl = dlg.get_user1_takt_lyric();
			CString tl_ini = "\""+tl+"\"";
			o_inifile->set_user1_taktlyric(tl_ini);

			// fill beat_lyric
			CString bl = dlg.get_user1_beat_lyric();
			CString bl_ini = "\""+bl+"\"";
			o_inifile->set_user1_beatlyric(bl_ini);

			// fill end_lyric
			CString el = dlg.get_user1_end_lyric();
			CString el_ini = "\""+el+"\"";
			o_inifile->set_user1_endlyric(el_ini);

			// fill linefeedlyrictick
			int user1_linefeedlyrictick = dlg.get_user1_linefeedlyrictick();
			o_inifile->set_user1_linefeedlyrictick(user1_linefeedlyrictick);

			if (hpmfi != NULL)
			{
				char* tl_str; 
				char* bl_str; 
				char* el_str;

				GlobalUtilities::convert_CString_to_cstring(&tl_str,tl);
				GlobalUtilities::convert_CString_to_cstring(&bl_str,bl);
				GlobalUtilities::convert_CString_to_cstring(&el_str,el);
				hpmfi->set_user1_fill_lyric_data(tl_str, bl_str, el_str, user1_linefeedlyrictick);
				delete[] tl_str;
				delete[] bl_str;
				delete[] el_str;
			}
			break;
		}

	case 2:
		{
			// fill takt_lyric
			CString tl = dlg.get_user2_takt_lyric();
			CString tl_ini = "\""+tl+"\"";
			o_inifile->set_user2_taktlyric(tl_ini);

			// fill beat_lyric
			CString bl = dlg.get_user2_beat_lyric();
			CString bl_ini = "\""+bl+"\"";
			o_inifile->set_user2_beatlyric(bl_ini);

			// fill end_lyric
			CString el = dlg.get_user2_end_lyric();
			CString el_ini = "\""+el+"\"";
			o_inifile->set_user2_endlyric(el_ini);

			// fill linefeedlyrictick
			int user2_linefeedlyrictick = dlg.get_user2_linefeedlyrictick();
			o_inifile->set_user2_linefeedlyrictick(user2_linefeedlyrictick);

			if (hpmfi != NULL)
			{
				char* tl_str; 
				char* bl_str; 
				char* el_str;

				GlobalUtilities::convert_CString_to_cstring(&tl_str,tl);
				GlobalUtilities::convert_CString_to_cstring(&bl_str,bl);
				GlobalUtilities::convert_CString_to_cstring(&el_str,el);
				hpmfi->set_user2_fill_lyric_data(tl_str, bl_str, el_str, user2_linefeedlyrictick);
				delete[] tl_str;
				delete[] bl_str;
				delete[] el_str;
			}
			break;
		}
	case 3:
		{
			// fill takt_lyric
			CString tl = dlg.get_user3_takt_lyric();
			CString tl_ini = "\""+tl+"\"";
			o_inifile->set_user3_taktlyric(tl_ini);

			// fill beat_lyric
			CString bl = dlg.get_user3_beat_lyric();
			CString bl_ini = "\""+bl+"\"";
			o_inifile->set_user3_beatlyric(bl_ini);

			// fill end_lyric
			CString el = dlg.get_user3_end_lyric();
			CString el_ini = "\""+el+"\"";
			o_inifile->set_user3_endlyric(el_ini);

			// fill linefeedlyrictick
			int user3_linefeedlyrictick = dlg.get_user3_linefeedlyrictick();
			o_inifile->set_user3_linefeedlyrictick(user3_linefeedlyrictick);

			if (hpmfi != NULL)
			{
				char* tl_str; 
				char* bl_str; 
				char* el_str;

				GlobalUtilities::convert_CString_to_cstring(&tl_str,tl);
				GlobalUtilities::convert_CString_to_cstring(&bl_str,bl);
				GlobalUtilities::convert_CString_to_cstring(&el_str,el);
				hpmfi->set_user3_fill_lyric_data(tl_str, bl_str, el_str, user3_linefeedlyrictick);
				delete[] tl_str;
				delete[] bl_str;
				delete[] el_str;
			}
			break;
		}
	}

	SetCursor(hCursorOld);
	return;
}

