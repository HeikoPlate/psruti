// VoiceFileBrowseDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "VoiceFileBrowseDlg.h"
#include "XBrowseForFolder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const VoiceFileBrowseDlg::RVC_EXT_ELE VoiceFileBrowseDlg::rvc_extension_list[] =
{
	{"VCE",""},
	{"LIV","Live! "},
	{"MGV","Mega Voice "},
	{"SWV","Sweet! "},
	{"DRM","Drums "},
	{"ORG","Organ Flutes! "},
	{"LDR","Live! Drums "},
	{"SFX","SFX "},
	{"CLV","Cool! "},
	{"LSF","Live!SFX "},
	{"SAR","S.Articulation! "},
	{"SA2","S.Articulation2! "},
	{"CWN","Custom "},
	{"CWD","Custom Drum "}
};

const int VoiceFileBrowseDlg::rvc_extension_list_len = 14;


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld VoiceFileBrowseDlg 


VoiceFileBrowseDlg::VoiceFileBrowseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(VoiceFileBrowseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(VoiceFileBrowseDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT

	voicename = "";
	voicefile_path = "";
	
	rvc_all_voicenames = NULL;
	rvc_act_voicenames = NULL;
	block = -1;
}


void VoiceFileBrowseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VoiceFileBrowseDlg)
	DDX_Control(pDX, IDC_BLOCK_LIST, m_block_list);
	DDX_Control(pDX, IDC_SEARCH_STRG, m_search_strg);
	DDX_Control(pDX, IDC_BROWSE_LIST, m_browse_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VoiceFileBrowseDlg, CDialog)
	//{{AFX_MSG_MAP(VoiceFileBrowseDlg)
	ON_BN_CLICKED(IDC_SELECT_FOLDER, OnSelectFolder)
	ON_EN_UPDATE(IDC_SEARCH_STRG, OnUpdateSearchStrg)
	ON_LBN_SELCHANGE(IDC_BROWSE_LIST, OnSelchangeBrowseList)
	ON_LBN_SELCHANGE(IDC_BLOCK_LIST, OnSelchangeBlockList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten VoiceFileBrowseDlg 

void VoiceFileBrowseDlg::OnCancel() 
{
	if (rvc_all_voicenames != NULL)
	{
		delete rvc_all_voicenames;
	}
	if (rvc_act_voicenames != NULL)
	{
		delete rvc_act_voicenames;
	}
	EndDialog(-1);
}

void VoiceFileBrowseDlg::OnOK() 
{
	if (voicefile_path=="") return;

	if (!hpmfi->check_voicefile(voicefile_path))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_ERROR_VOICEFILE),NULL,MB_OK|MB_TASKMODAL);
		return;
	}

	if (rvc_all_voicenames != NULL)
	{
		delete rvc_all_voicenames;
	}
	if (rvc_act_voicenames != NULL)
	{
		delete rvc_act_voicenames;
	}

	EndDialog(0);
}

BOOL VoiceFileBrowseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString text;
	text.Format(GlobalUtilities::get_resource_string(IDS_WTEXT_SELECT_VOICEFILE),chan+1);
	SetWindowText(text);
	voicefile_folder = p_inifile->get_voicefile_folder();

	if (voicefile_folder != "")
	{
		// does voicefile_folder exist?
        if ( _chdir(voicefile_folder) != 0)
		{
			voicefile_folder = "";
		}
	}

	display_folder(voicefile_folder);
	if (voicefile_folder != "")
	{ // fill voicelist
		rvc_fill_voicename_lists(voicefile_folder);
		display_voices();
	}

	m_block_list.AddString("--");

	int ch;
	bool used;
	int no_blocks = hpmfi->no_blocks;
	int bl;
	
	for (bl=0; bl<no_blocks; bl++)
	{
		used = false;
		CString bl_str;
		bl_str.Format("%i",bl+1);
		for (ch=0; ch<16; ch++)
		{
			if ((blocklist[ch]==bl)&&(chan!=ch))
			{
				used = true;
				break;
			}
		}
		if (!used) m_block_list.AddString(bl_str);
	}
	m_block_list.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void VoiceFileBrowseDlg::display_folder(CString long_folder)
{
	CString short_folder = long_folder;
	if (long_folder.GetLength()>46)
	{
		short_folder = "..."+long_folder.Right(43);
	}
	SetDlgItemText(IDC_VOICEFILE_FOLDER,short_folder);
}

void VoiceFileBrowseDlg::OnSelectFolder() 
{
	// voicefile folder
	CString initialfolder = p_inifile->get_voicefile_folder();

	TCHAR szFolder[MAX_PATH*2];
	szFolder[0] = _T('\0');

	BOOL bRet = XBrowseForFolder(m_hWnd,
								 initialfolder,		
								 szFolder,
								 sizeof(szFolder)/sizeof(TCHAR)-2);
	
	if (bRet)
	{

		SetDlgItemText(IDC_SEARCH_STRG,"");
		m_browse_list.ResetContent();

		// Conversion to CString szFolder
		voicefile_folder = szFolder;
		display_folder(voicefile_folder);
		if (voicefile_folder != "")
		{ // fill voicelist
			rvc_fill_voicename_lists(voicefile_folder);
			display_voices();
		}
		p_inifile->set_voicefile_folder(voicefile_folder);
	}
}

void VoiceFileBrowseDlg::OnUpdateSearchStrg() 
{
	if((rvc_all_voicenames==0)||(rvc_all_voicenames==0))
	{
		return;
	}

	char str[65];
	int len = m_search_strg.GetLine(0,str,64);
	str[len] = 0;
	rvc_act_voicenames->reduce(rvc_all_voicenames,str);
	display_voices();
}

void VoiceFileBrowseDlg::rvc_fill_voicename_lists(CString voicefile_folder)
{
	CString voicename;
	char* c_voicename;
	CString filename;
	char* c_filename;

	CString extension;
	CString attribute;
	CString short_voicename;
	int i;
	int nextfile;

	if (rvc_all_voicenames != NULL)
	{
		delete rvc_all_voicenames;
		rvc_all_voicenames = NULL;
	}
	if (rvc_act_voicenames != NULL)
	{
		delete rvc_act_voicenames;
		rvc_act_voicenames = NULL;
	}

	rvc_all_voicenames = new VoiceArray();

	// fill rvc_all_voicenames
	// Look for files
	CFileFind finder;
	if (!finder.FindFile(voicefile_folder+"\\"+"*.*"))
	{
		delete rvc_all_voicenames;
		rvc_all_voicenames = NULL;
		return;
	}
	else
	{
		while (true)
		{
			nextfile = finder.FindNextFile();
			filename = finder.GetFileName();
			if (filename[0]=='.') continue;
			GlobalUtilities::convert_CString_to_cstring(&c_filename,filename);

			extension = filename.Right(3);
			extension.MakeUpper();

			attribute = extension+" ";
			for (i=0; i<rvc_extension_list_len; i++)
			{
				CString list_ext = (rvc_extension_list[i]).extension;
				if (list_ext==extension)
				{
					CString att = (rvc_extension_list[i]).voice_attribute;
					attribute = att;
					break;
				}
			}
			short_voicename = "";
			for (i=0; i<filename.GetLength()-4;i++)
			{
				if ((filename[i]=='.')&&((filename[i+1]=='S')||(filename[i+1]=='T')) &&
					((filename[i+2]>='0')&&(filename[i+2]<='9'))) break;
				short_voicename += filename[i];
			}

			voicename = attribute + short_voicename;
			GlobalUtilities::convert_CString_to_cstring(&c_voicename,voicename);

			rvc_all_voicenames->add(c_voicename,c_filename);
			delete[] c_voicename;
			delete[] c_filename;

			if (nextfile==0) break;
		}
	}

	rvc_all_voicenames->sort();

	// double rvc_all_voicenames
	rvc_act_voicenames = new VoiceArray(*rvc_all_voicenames);

}

void VoiceFileBrowseDlg::display_voices()
{
	m_browse_list.ResetContent();
	if (rvc_act_voicenames==NULL) return;
	int i;
	for (i=0;i<rvc_act_voicenames->get_length();i++)
	{
		m_browse_list.AddString(rvc_act_voicenames->get_voicename(i));
	}
}

void VoiceFileBrowseDlg::OnSelchangeBrowseList() 
{
	int browse_list_index = m_browse_list.GetCurSel();
	if (browse_list_index == LB_ERR)
	{	
		voicename = "";
		voicefile_path = "";
		return;
	}
	voicename = rvc_act_voicenames->get_voicename(browse_list_index);
	voicefile_path =  voicefile_folder+"\\"+rvc_act_voicenames->get_filename(browse_list_index);
}

void VoiceFileBrowseDlg::OnSelchangeBlockList() 
{
	int block_list_index = m_block_list.GetCurSel();
	if (block_list_index == LB_ERR)
	{	
		block_list_index = 0;
		m_block_list.SetCurSel(0);
		block = -1;
		return;
	}

	CString block_text;
	m_block_list.GetText(block_list_index,block_text);
	block = 
		block_text=="--"?-1:
		block_text=="1"?0: 
		block_text=="2"?1: 
		block_text=="3"?2: 
		block_text=="4"?3: 
		block_text=="5"?4: 
		block_text=="6"?5: 
		block_text=="7"?6: 
		block_text=="8"?7: 
		block_text=="9"?8: 
		block_text=="10"?9: 
		block_text=="11"?10:
		block_text=="12"?11: 
		block_text=="13"?12: 
		block_text=="14"?13: 
		block_text=="15"?14: 
		block_text=="16"?15: 
		block_text=="17"?16: 
		block_text=="18"?17: 
		block_text=="19"?18: 
		block_text=="20"?19: 
		block_text=="21"?20: 
		block_text=="22"?21: 
		block_text=="23"?22: 
		block_text=="24"?23: 
		block_text=="25"?24: 
		block_text=="26"?25: 
		-1;
}
