// Play.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Play.h"
#include "Chd.h"
#include "IniFile.h"
#include "InsertChordLyrics.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//**************************************************************************
//**************************************************************************
//*
//*		Dialogfeld CPlay
//*
//**************************************************************************
//**************************************************************************

const CString CPlay::start_chordlist = "[start chordlist]";

CPlay::CPlay(CWnd* pParent /*=NULL*/) : CDialog(CPlay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlay)
	//}}AFX_DATA_INIT

	hpmfi = NULL;
	mf = NULL;
	with_lyrics = false;
	m_nTimer = NULL;
	linefeed_char = GlobalUtilities::get_linefeed_char();

	posx = -1;
	lenx = -1;
	posy = -1;
	leny = -1;


	check_chan_ctrl[0] = &m_check_eins;
	check_chan_ctrl[1] = &m_check_zwei;
	check_chan_ctrl[2] = &m_check_drei;
	check_chan_ctrl[3] = &m_check_vier;
	check_chan_ctrl[4] = &m_check_fuenf;
	check_chan_ctrl[5] = &m_check_sechs;
	check_chan_ctrl[6] = &m_check_sieben;
	check_chan_ctrl[7] = &m_check_acht;
	check_chan_ctrl[8] = &m_check_neun;
	check_chan_ctrl[9] = &m_check_zehn;
	check_chan_ctrl[10] = &m_check_elf;
	check_chan_ctrl[11] = &m_check_zwoelf;
	check_chan_ctrl[12] = &m_check_dreizehn;
	check_chan_ctrl[13] = &m_check_vierzehn;
	check_chan_ctrl[14] = &m_check_fuenfzehn;
	check_chan_ctrl[15] = &m_check_sechzehn;

	idc_voice_type[0] = IDC_V1;
	idc_voice_type[1] = IDC_V2;
	idc_voice_type[2] = IDC_V3;
	idc_voice_type[3] = IDC_V4;
	idc_voice_type[4] = IDC_V5;
	idc_voice_type[5] = IDC_V6;
	idc_voice_type[6] = IDC_V7;
	idc_voice_type[7] = IDC_V8;
	idc_voice_type[8] = IDC_V9;
	idc_voice_type[9] = IDC_V10;
	idc_voice_type[10] = IDC_V11;
	idc_voice_type[11] = IDC_V12;
	idc_voice_type[12] = IDC_V13;
	idc_voice_type[13] = IDC_V14;
	idc_voice_type[14] = IDC_V15;
	idc_voice_type[15] = IDC_V16;

	// inializes membervariable list m_voice_type

	m_voice_type[0] = &m_v1;
	m_voice_type[1] = &m_v2;
	m_voice_type[2] = &m_v3;
	m_voice_type[3] = &m_v4;
	m_voice_type[4] = &m_v5;
	m_voice_type[5] = &m_v6;
	m_voice_type[6] = &m_v7;
	m_voice_type[7] = &m_v8;
	m_voice_type[8] = &m_v9;
	m_voice_type[9] = &m_v10;
	m_voice_type[10] = &m_v11;
	m_voice_type[11] = &m_v12;
	m_voice_type[12] = &m_v13;
	m_voice_type[13] = &m_v14;
	m_voice_type[14] = &m_v15;
	m_voice_type[15] = &m_v16;

	m_pToolTip = NULL;
 }


void CPlay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlay)
	DDX_Control(pDX, IDC_V1, m_v1);
	DDX_Control(pDX, IDC_V2, m_v2);
	DDX_Control(pDX, IDC_V3, m_v3);
	DDX_Control(pDX, IDC_V4, m_v4);
	DDX_Control(pDX, IDC_V5, m_v5);
	DDX_Control(pDX, IDC_V6, m_v6);
	DDX_Control(pDX, IDC_V7, m_v7);
	DDX_Control(pDX, IDC_V8, m_v8);
	DDX_Control(pDX, IDC_V9, m_v9);
	DDX_Control(pDX, IDC_V10, m_v10);
	DDX_Control(pDX, IDC_V11, m_v11);
	DDX_Control(pDX, IDC_V12, m_v12);
	DDX_Control(pDX, IDC_V13, m_v13);
	DDX_Control(pDX, IDC_V14, m_v14);
	DDX_Control(pDX, IDC_V15, m_v15);
	DDX_Control(pDX, IDC_V16, m_v16);
	DDX_Control(pDX, IDC_SLIDER_TIME_POS, m_slider_time_pos);
	DDX_Control(pDX, IDC_CHECK_EINS, m_check_eins);
	DDX_Control(pDX, IDC_CHECK_ZWEI, m_check_zwei);
	DDX_Control(pDX, IDC_CHECK_DREI, m_check_drei);
	DDX_Control(pDX, IDC_CHECK_VIER, m_check_vier);
	DDX_Control(pDX, IDC_CHECK_FUENF, m_check_fuenf);
	DDX_Control(pDX, IDC_CHECK_SECHS, m_check_sechs);
	DDX_Control(pDX, IDC_CHECK_SIEBEN, m_check_sieben);
	DDX_Control(pDX, IDC_CHECK_ACHT, m_check_acht);
	DDX_Control(pDX, IDC_CHECK_NEUN, m_check_neun);
	DDX_Control(pDX, IDC_CHECK_ZEHN, m_check_zehn);
	DDX_Control(pDX, IDC_CHECK_ELF, m_check_elf);
	DDX_Control(pDX, IDC_CHECK_ZWOELF, m_check_zwoelf);
	DDX_Control(pDX, IDC_CHECK_DREIZEHN, m_check_dreizehn);
	DDX_Control(pDX, IDC_CHECK_VIERZEHN, m_check_vierzehn);
	DDX_Control(pDX, IDC_CHECK_FUENFZEHN, m_check_fuenfzehn);
	DDX_Control(pDX, IDC_CHECK_SECHZEHN, m_check_sechzehn);
	DDX_Control(pDX, IDC_CHECK_PLAY_ALL, m_check_play_all);
	DDX_Control(pDX, IDC_SLIDER_TIME, m_slider_time);
	DDX_Control(pDX, IDC_INSERT_CHORDS_LYRICS, m_insert_chords_lyrics);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_RECORD_CHORDS, m_record_chords);
	DDX_Control(pDX, IDC_SLIDER_TEMPO, m_slider_tempo);
	DDX_Control(pDX, IDC_SLIDER_TRANSPOSE, m_slider_transpose);
	DDX_Control(pDX, IDC_SLIDER_MASTER_VOLUME, m_slider_volume);
	DDX_Control(pDX, IDC_STOP, m_stop);
	DDX_Control(pDX, IDC_PLAY, m_play);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlay, CDialog)
	//{{AFX_MSG_MAP(CPlay)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_DEFAULT_TEMPO, OnDefaultTempo)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_DEFAULT_TRANSPOSE, OnDefaultTranspose)
	ON_BN_CLICKED(IDC_RECORD_CHORDS, OnRecordChordsLyrics)
	ON_BN_CLICKED(IDC_INSERT_CHORDS_LYRICS, OnInsertChordsLyrics)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TIME, OnReleasedcaptureSliderTime)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_TIME, OnCustomdrawSliderTime)
	ON_BN_CLICKED(IDC_CHECK_EINS, OnCheckEins)
	ON_BN_CLICKED(IDC_CHECK_ZWEI, OnCheckZwei)
	ON_BN_CLICKED(IDC_CHECK_DREI, OnCheckDrei)
	ON_BN_CLICKED(IDC_CHECK_VIER, OnCheckVier)
	ON_BN_CLICKED(IDC_CHECK_FUENF, OnCheckFuenf)
	ON_BN_CLICKED(IDC_CHECK_SECHS, OnCheckSechs)
	ON_BN_CLICKED(IDC_CHECK_SIEBEN, OnCheckSieben)
	ON_BN_CLICKED(IDC_CHECK_ACHT, OnCheckAcht)
	ON_BN_CLICKED(IDC_CHECK_NEUN, OnCheckNeun)
	ON_BN_CLICKED(IDC_CHECK_ZEHN, OnCheckZehn)
	ON_BN_CLICKED(IDC_CHECK_ELF, OnCheckElf)
	ON_BN_CLICKED(IDC_CHECK_ZWOELF, OnCheckZwoelf)
	ON_BN_CLICKED(IDC_CHECK_DREIZEHN, OnCheckDreizehn)
	ON_BN_CLICKED(IDC_CHECK_VIERZEHN, OnCheckVierzehn)
	ON_BN_CLICKED(IDC_CHECK_FUENFZEHN, OnCheckFuenfzehn)
	ON_BN_CLICKED(IDC_CHECK_SECHZEHN, OnCheckSechzehn)
	ON_BN_CLICKED(IDC_CHECK_PLAY_ALL, OnCheckPlayAll)
	ON_EN_KILLFOCUS(IDC_SLIDER_TIME_POS, OnKillFocusSliderTimePos)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_MASTER_VOLUME, OnReleasedcaptureSliderMasterVolume)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MASTER_VOLUME, OnCustomdrawSliderMasterVolume)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CPlay 

BOOL CPlay::PreTranslateMessage(LPMSG lpmsg)
{
	if ((NULL != m_pToolTip) && (lpmsg->message!=WM_KEYDOWN))
	{
		m_pToolTip->RelayEvent(lpmsg);
		return CDialog::PreTranslateMessage(lpmsg);
	}

    if (lpmsg->message==WM_KEYDOWN)
    {
		
		if (lpmsg->wParam==VK_SPACE)
		{
			OnPlay();
			return FALSE;		
		}

		if (lpmsg->wParam=='E')
		{
			OnStop();
			return TRUE;
		}

		if (lpmsg->wParam=='M')
		{
			m_slider_time_pos.SetFocus();
			m_slider_time_pos.SetSel(0,-1);
			return TRUE;
		}

		if (lpmsg->wParam==VK_ESCAPE)
		{
			OnOK();
			return TRUE;
		}

		if (lpmsg->wParam==VK_RETURN)
        {
			if (!is_record)
			{
				m_play.SetFocus();
				return TRUE;
			}
		
			// recording
			if (act_list_no >= record_chord_lyric_length)
			{
				// stop recording
				is_record = false;
				m_record_chords.SetIcon(hIcon_record_yellow);
				m_play.SetIcon(hIcon_play_green);
				
				SetDlgItemText(IDC_REC_CHORD_LYRIC_TEXT,record_text);
				SetDlgItemText(IDC_ACTUAL_LYRIC_CHORD,"");
				SetDlgItemText(IDC_NEXT_LYRIC_CHORD,record_chord_lyric_list[0].text);
				m_insert_chords_lyrics.EnableWindow(TRUE);
				InvalidateRect(&record_rect,FALSE);
				UpdateWindow();
				return TRUE;
			}
			
			bool insert_linefeed = (record_chord_lyric_list[act_list_no].time==-2);
			int time = HP_PlayEventTime(mf);
			if (insert_linefeed)
			{
				int lf_time = time-5>=0?time-5:0;
				record_chord_lyric_list[act_list_no].time = lf_time;
				act_list_no++;
			}
			record_chord_lyric_list[act_list_no].time = time;
			
			// Display actual played chord/lyric
			CString new_text = 
				(act_list_no<record_chord_lyric_length)?
				record_chord_lyric_list[act_list_no].text:
			"";
			SetDlgItemText(IDC_ACTUAL_LYRIC_CHORD,new_text);
			
			// Display next chord/lyric to play
			
			bool next_linefeed;
			
			if (act_list_no+1 < record_chord_lyric_length)
			{
				next_linefeed = (record_chord_lyric_list[act_list_no+1].time==-2);
			}
			else
			{
				next_linefeed = false;
			}
			
			new_text = 
				(act_list_no+(next_linefeed?2:1)<record_chord_lyric_length)?
				record_chord_lyric_list[act_list_no+(next_linefeed?2:1)].text:
			"";
			SetDlgItemText(IDC_NEXT_LYRIC_CHORD,new_text);
			
			act_list_no++;
			
			return TRUE;
			
		} // end space 
    }

    return FALSE; // don't handle other messages
}

void CPlay::PositWindow(int distance)
{
	CWnd *hwndOwner; 
	RECT rc, rcDlg, rcOwner; 

	// Get the owner window and dialog box rectangles. 

	if ((hwndOwner = CWnd::GetParent()) == NULL) 
	{
		hwndOwner = GetDesktopWindow(); 
	}
	hwndOwner->GetWindowRect(&rcOwner); 
	GetWindowRect(&rcDlg); 
	CopyRect(&rc, &rcOwner); 

	// Offset the owner and dialog box rectangles so that right and bottom 
	// values represent the width and height, and then offset the owner again 
	// to discard space taken up by the dialog box. 

	OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top); 
	OffsetRect(&rc, -rc.left, -rc.top); 
	OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom); 

	SetWindowPos(&wndTop, 
			     rcOwner.left + (rc.right / 2), 
                 rcOwner.top + (rc.bottom / 2)+distance,
                 0, 0,          // Ignores size arguments. 
                 SWP_NOSIZE); 
}

BOOL CPlay::OnInitDialog() 
{
	PositWindow(-19);
	CDialog::OnInitDialog();
	CString r;
	
	RECT rect; 
    GetClientRect(&rect);
	posx = (23*rect.right)/800;
	lenx = (753*rect.right)/800; // look at prepare_lyrics_chords!!
	posy = (9*rect.bottom)/549;
	leny = (382*rect.bottom)/549;

	int i;
	int chan;

	// TODO: Zusätzliche Initialisierung hier einfügen

	CString text = "Play:  ";
	text += hpmfi->proposed_songname;
	SetWindowText(text);

	// Icons for Play, Pause- and Stop-Buttons

	hIcon_play = AfxGetApp()->LoadIcon(IDI_ICON3);
	m_play.SetIcon(hIcon_play);
	hIcon_pause = AfxGetApp()->LoadIcon(IDI_ICON2);
	hIcon_stop = AfxGetApp()->LoadIcon(IDI_ICON4);
	m_stop.SetIcon(hIcon_stop);

	// Recording
	is_record_prepared = false;
	is_record = false;
	source_changed = false;
	act_list_no = 0;
	record_chord_lyric_length = 0;
	hIcon_record_red = AfxGetApp()->LoadIcon(IDI_ICON5);
	m_record_chords.SetIcon(hIcon_record_red);

	hIcon_record_green = AfxGetApp()->LoadIcon(IDI_ICON6);
	hIcon_record_yellow = AfxGetApp()->LoadIcon(IDI_ICON7);
	hIcon_record_darkgreen = AfxGetApp()->LoadIcon(IDI_ICON8);
	hIcon_play_green = AfxGetApp()->LoadIcon(IDI_ICON9);
	hIcon_pause_green = AfxGetApp()->LoadIcon(IDI_ICON17);

	SetDlgItemText(IDC_ACTUAL_LYRIC_CHORD,"");
	SetDlgItemText(IDC_NEXT_LYRIC_CHORD,"");


	// channel

	for (i=0; i<16; i++)
	{
		bool mute = (hpmfi->mute)[i];
		check_chan_ctrl[i]->SetCheck(mute?0:1);
		check_chan_ctrl[i]->EnableWindow(mute?false:true);
		if (!(hpmfi->mute)[i])
		{
			SetDlgItemText(idc_voice_type[i],(hpmfi->patchname)[i]);
		}
		else
		{
			SetDlgItemText(idc_voice_type[i],"");
		}
	}

	m_check_play_all.SetCheck(1);
	m_insert_chords_lyrics.EnableWindow(FALSE);

	//	m_play.SetFocus();
	// Attention: Look at recource for good values

	record_rect.left = 7;
	record_rect.right = 7+300;
	record_rect.top = 255;
	record_rect.bottom = 255+44;

	// Slider

	// Tempo
	m_slider_tempo.SetRange(1,30,TRUE);
	m_slider_tempo.SetPos(10);
	SetDlgItemText(IDC_TEMPO_DISPLAY,"100%");

	// Transpose
	m_slider_transpose.SetRange(-12,12,TRUE);
	m_slider_transpose.SetPos(0);
	SetDlgItemText(IDC_TRANSPOSE_DISPLAY,"0");

	// Volume
	orig_master_volume = hpmfi->analyze_master_volume(false);
	int volume = orig_master_volume==-1?127:orig_master_volume;
	m_slider_volume.SetRange(0,127,TRUE);
	m_slider_volume.SetPos(volume);
	r.Format("%i",volume);
	SetDlgItemText(IDC_VOLUME_DISPLAY,r);
//	m_slider_volume.SetPos(127);
//	SetDlgItemText(IDC_VOLUME_DISPLAY,"127");

	int lt, lb, tm;
	new_slider_time = 0;
	hpmfi->get_last_takt_beat(&lt,&lb,&tm);
	m_slider_time.SetRange(0,tm,TRUE);
	m_slider_time.SetPos(0);

    r.Format("%4.4i:%2.2i",1,1);
    SetDlgItemText(IDC_TAKT_BEAT,r);

	r.Format("%4.4i:%2.2i",lt+1,lb+1);
	SetDlgItemText(IDC_LAST_TKT_BEAT,r);

	// MY_PLAY_MONITOR initialization
	pm.whandle = this->m_hWnd;
	pm.hpmfi = hpmfi;
	pm.p_lfr = &m_lfr;
	pm.logf = logf;

	// initialize the monitor
	HP_InitPlayMonitor(mf,&pm);

	m_lfr.logf = logf;
	m_lfr.InitDisplay(this,posx,posy,lenx,leny);

	char *ps;
	char *cn;
	char *composer;
	char *lyricist;

	GlobalUtilities::convert_CString_to_cstring(&ps,hpmfi->proposed_songname);
	GlobalUtilities::convert_CString_to_cstring(&cn,hpmfi->copyrightname);
	GlobalUtilities::convert_CString_to_cstring(&composer,hpmfi->composer);
	GlobalUtilities::convert_CString_to_cstring(&lyricist,hpmfi->lyricist);
	m_lfr.display_title(ps,cn,composer, lyricist);
	delete[] ps;
	delete[] cn;
	delete[] composer;
	delete[] lyricist;
	
	prepare_lyrics_chords();

	SetDlgItemText(IDC_REC_CHORD_LYRIC_TEXT,"");

	m_play.SetIcon(hIcon_play);
	m_stop.EnableWindow(FALSE);
	m_slider_time_pos.SetSel(0,-1);
	m_slider_time_pos.SetFocus();


	// fill mega_channel_list
	for (chan=0; chan<16; chan++)
	{
		mega_channel_list[chan] = hpmfi->mlv_list[chan].is_mega?true:false;
//		r.Format("chan %i, is_mega %i",chan, mega_channel_list[chan]);
//		MessageBox(r);
	}

	// Tool Tips
	if (hpmfi->with_insdef)
	{
		m_pToolTip = new CToolTipCtrl;
		m_pToolTip->Create(this);
		m_pToolTip->SetDelayTime(TTDT_AUTOPOP,4000);
		m_pToolTip->SetMaxTipWidth(200);

		for (chan=0; chan<16; chan++)
		{
			if ((hpmfi->mlv_list[chan]).voicename == "") continue;
			m_pToolTip->AddTool(m_voice_type[chan],(hpmfi->mlv_list[chan]).voicename);
		}
		m_pToolTip->Activate(true);
	}

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

//**************************************************************************
//*
//*		OnPaint
//*
//**************************************************************************

void CPlay::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
//		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		dc.BitBlt(posx,posy,lenx,leny,&m_lfr.m_memDC,0,0,SRCCOPY);
		CDialog::OnPaint();
	}	
}

//**************************************************************************
//*
//*		prepare_lyrics_chords
//*		fills LyricFrame::lyricframelist with lyrics and chords
//*
//**************************************************************************

void CPlay::prepare_lyrics_chords()
{
	int i, k;

	m_lfr.songname = hpmfi->proposed_songname; // only for print
	
	int cwl = m_lfr.char_width_lyric;	// the width of one displayed char (pixel) of lyric
	int cwc = m_lfr.char_width_chord;	// the width of one displayed char (pixel) of chord

	typedef struct t_elem
	{
		int time;
		char *text;
		int len;
		int px;
	}	T_ELEM;

	const int NO_LYRICS_CHORDS = 5000;

	T_ELEM l_list[NO_LYRICS_CHORDS];
	T_ELEM c_list[NO_LYRICS_CHORDS];

	// initialize arrays
	for(i=0; i<NO_LYRICS_CHORDS; i++)
	{
		l_list[i].time = -1;
		l_list[i].text = NULL;
		c_list[i].time = -1;
		c_list[i].text = NULL;
	}

	// actual index in lists
	int l_syll = 0;
	int c_syll = 0;

	int len;
	int id, chan, time, type;
	char *text;


	HP_Rewind(mf);
	while (HP_ReadEvent(mf,&id,&chan,&time,&type)==HP_ERR_NONE)
	{

		if (type==HP_LYRIC)
		{
			if (l_syll >= NO_LYRICS_CHORDS) break;

			int start_lf = 0;	// no. of linefeeds at the beginning of lyric
			int end_lf = 0;		// no. of linefeeds at the end of lyric	

			HP_ReadLyric(mf,id,&time,&text);
			len = strlen(text);

			if (len == 0)
			{
				HP_Delete(text);
				continue; // ignore empty lyrics
			}

			// in Play no newpage; exchange newpage by linefeed
			if (text[len-1]==0x0a)
			{
				text[len-1]=0x0d;
			}
			
			// count leading linefeeds
			for (i=0; i<len; i++)
			{
				if ((text[i]==0x0d) || (text[i]=='/'))
				{
					start_lf++;
				}
				else
				{
					break;
				}
			}

			// insert only one linefeed if needed
			if (start_lf > 0)
			{
				l_list[l_syll].time = time;
				l_list[l_syll].text = new char[1];
				strcpy(l_list[l_syll].text,"");
				l_list[l_syll].len = 0;
				l_list[l_syll].px = 0;
				l_syll++;
			}

			// line with linefeeds only?
			if (len==start_lf)
			{	
				HP_Delete(text);
				continue;
			}

			if (l_syll >= NO_LYRICS_CHORDS)
			{
				HP_Delete(text);
				break;
			}

			// delete leading linefeeds...
			if (start_lf > 0)
			{
				for (i = start_lf; i < len; i++)
				{
					text[i-start_lf] = text[i];
				}
				text[len-start_lf] = (char) 0;
				len -= start_lf;
			}

			// count ending linefeeds
			int end_blanks = 0; 
			for (i=len-1; i>=0; i--)
			{
				if ((text[i]==0x0a) || 
					(text[i]==0x0d) || 
					(text[i]=='/')  || 
					(text[i]==' ')    )
				{
					if (text[i]==' ')
					{
						end_blanks++;
					}
					else
					{
						end_lf++;
					}
				}
				else
				{
					break;
				}
			}

			// delete ending linefeeds...
			if (end_lf > 0)
			{
				len -= end_lf+end_blanks;
				if (len==0) len++;
				text[len] = (char)0;
			}

			// insert lyric
			l_list[l_syll].time = time;
			l_list[l_syll].text = new char[len+1];
			strcpy(l_list[l_syll].text,text);
			l_list[l_syll].len = len;
			l_list[l_syll].px = len*cwl;
			l_syll++;

			// insert one linefeed if needed

			if (end_lf > 0)
			{
				if (l_syll >= NO_LYRICS_CHORDS)
				{
					HP_Delete(text);
					break;
				}
				l_list[l_syll].time = time;
				l_list[l_syll].text = new char[1];
				strcpy(l_list[l_syll].text,"");
				l_list[l_syll].len = 0;
				l_list[l_syll].px = 0;
				l_syll++;
			}
			HP_Delete(text);
			continue;
		}

		if (type==HP_CHORD_NAME)
		{
			unsigned char cr, ct,bn, bt;

			if (c_syll >= NO_LYRICS_CHORDS) break;

			HP_ReadChord(mf,id,&time,&cr,&ct,&bn,&bt,&text);
			
			len = strlen(text);

			c_list[c_syll].time = time;
			c_list[c_syll].text = new char[len+2];
			strcpy(c_list[c_syll].text,text);
			
			// add one blank to chord-name
			strcat(c_list[c_syll].text," ");
			len++;
			
			c_list[c_syll].len = len;
			c_list[c_syll].px = len*cwc;
			c_syll++;
			HP_Delete(text);
			continue;
		}

		if (type==HP_SYSEX)  // look for chord-sysex
		{
			unsigned char* data;
			int length;

			HP_ReadSysex(mf,id,&time,&data,&length);
			if (length == 9)
			{
				if ((data[1]==0x43)&&(data[2]==0x7e)&&(data[3]==0x02))
				{	// yamaha chord sysex 
					int cr = data[4];
					int ct = data[5];
					int bn = data[6];
					int bt = data[7];

					HP_ConvertChordToText(cr,ct,bn,bt,&text);

					len = strlen(text);
					c_list[c_syll].time = time;
					c_list[c_syll].text = new char[len+2];
					strcpy(c_list[c_syll].text,text);
			
					// add one blank to chord-name
					strcat(c_list[c_syll].text," ");
					len++;
			
					c_list[c_syll].len = len;
					c_list[c_syll].px = len*cwc;
					c_syll++;
					HP_Delete(text);
				}
			}
			HP_Delete(data);
			continue;
		}
	}

/*
	// test l_list and c_list

	logf->add("l_list and c_list");

	for (i=0; i< NO_LYRICS_CHORDS; i++)
	{
		CString r;

		if (l_list[i].time==-1) break; // list end

		if (l_list[i].px==0)
		{
			logf->add("time %i, Linefeed",l_list[i].time);

			continue;
		}

		r.Format("time=%i lyric=%s len=%i px=%i",
			l_list[i].time,l_list[i].text,l_list[i].len,l_list[i].px);
		logf->add(r);
	}

	for (i=0; i< NO_LYRICS_CHORDS; i++)
	{
		CString r;

		if (c_list[i].time==-1) break; // list end

		r.Format("time=%i chord=%s len=%i px=%i",
			c_list[i].time,c_list[i].text,c_list[i].len,c_list[i].px);
		logf->add(r);
	}
*/


	if (lenx == -1) lenx = 753; // Attention: Here only needed for function Print where InitDialog is not runned

	//
	// clear lyricframelist
	//

	for (i=0; i<NO_LIST_LINES; i++)
	{
		for (k=0; k<NO_LYRICS_LINE; k++)
		{
			m_lfr.lyricframelist[i][k].time = -1;
			m_lfr.lyricframelist[i][k].lyric = NULL;
			m_lfr.lyricframelist[i][k].chord = NULL;
		}
	}

	//
	// fill lyricframelist
	//

	m_lfr.no_lyric_lines = 0;
	int line_index = 0; // actual index in line;
	int char_pos = 0;	// position of first character in lyric/chord
	int x_l = START_X;	 // actual x in line
    l_syll = 0;		 // actual lyric syllable in l_list
	c_syll = 0;		 // actual chord syllable in c_list
	int next_time_l; // time of next lyric
	int next_time_c; // time of next chord
	int diff_time;
	bool last_linefeed = false;

	while (true)
	{

		if ((l_syll >= NO_LYRICS_CHORDS)||(c_syll >= NO_LYRICS_CHORDS)) break;
		
		// compute next_time.. and over_next_time..
		next_time_l = l_list[l_syll].time;
		next_time_c = c_list[c_syll].time;
		
		// end of lists l_list, c_list?
		if ((next_time_l==-1)&&(next_time_c==-1)) break;

		// compute difference time of next lyric and next chord
		if ((next_time_l==-1)||(next_time_c==-1))
		{
			diff_time = -1;
		}
		else
		{
			diff_time = next_time_c-next_time_l;
			if (diff_time<0) diff_time = -diff_time;
		}

		if (diff_time==0)
		{
			// insert lyric and chord at the same moment

			// look for linefeed			
			if (l_list[l_syll].px==0)
			{
				if (!last_linefeed)
				{
					m_lfr.no_lyric_lines++;
					char_pos = 0;
					x_l = START_X;
					line_index = 0;
					if (m_lfr.no_lyric_lines >= NO_LIST_LINES) break;
				}
	
				l_syll++;
				last_linefeed = true;
				continue;
			}

			last_linefeed = false;

			int length_char = 
				c_list[c_syll].len>l_list[l_syll].len? c_list[c_syll].len: l_list[l_syll].len;
			int length_px = 
				c_list[c_syll].px>l_list[l_syll].px? c_list[c_syll].px: l_list[l_syll].px;
			
			if ((x_l+length_px >=lenx)&&(x_l > START_X))
			{
				m_lfr.no_lyric_lines++;
				char_pos = 0;
				x_l = START_X;
				line_index = 0;
				if (m_lfr.no_lyric_lines >= NO_LIST_LINES) break;
			}

			m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].time = next_time_c;

			m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].lyric = 
				new char[l_list[l_syll].len+1];
			strcpy(m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].lyric,
				   l_list[l_syll].text);

			m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].chord = 
				new char[c_list[c_syll].len+1];
			strcpy(m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].chord,
				   c_list[c_syll].text);

			m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].char_pos = char_pos;
			m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].x = x_l;

			x_l += length_px;
			char_pos += length_char;
			line_index++;
			c_syll++;
			l_syll++;
			continue;
		}

		if ( ((diff_time >=0)&&(next_time_l<next_time_c)) ||
			 (next_time_c < 0))
		{	
			// look for linefeed			
			if (l_list[l_syll].px==0)
			{
				if (!last_linefeed)
				{
					m_lfr.no_lyric_lines++;
					char_pos = 0;
					x_l = START_X;
					line_index = 0;
					if (m_lfr.no_lyric_lines >= NO_LIST_LINES) break;
				}
	
				l_syll++;
				last_linefeed = true;
				continue;
			}

			last_linefeed = false;

			// insert lyric only
			int length_char = l_list[l_syll].len;
			int length_px = l_list[l_syll].px;
			
			if ((x_l+length_px >=lenx) && (x_l > START_X))
			{
				m_lfr.no_lyric_lines++;
				char_pos = 0;
				x_l = START_X;
				line_index = 0;
				if (m_lfr.no_lyric_lines >= NO_LIST_LINES) break;
			}

			m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].time = next_time_l;

			m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].lyric = 
				new char[l_list[l_syll].len+1];
			strcpy(m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].lyric,
				l_list[l_syll].text);

			m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].chord = 
				new char[1];
			strcpy(m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].chord,"");
			m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].char_pos = char_pos;
			m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].x = x_l;

			x_l += length_px;
			char_pos += length_char;
			line_index++;
			l_syll++;
			continue;
		}

		if ( ((diff_time >=0)&&(next_time_c<next_time_l)) ||
			 (next_time_l < 0))
		{
			// insert chord only
			int length_char = c_list[c_syll].len;
			int length_px = c_list[c_syll].px;
			
			if ((x_l+length_px >=lenx)&&(x_l > START_X))
			{
				m_lfr.no_lyric_lines++;
				char_pos = 0;
				x_l = START_X;
				line_index = 0;
				if (m_lfr.no_lyric_lines >= NO_LIST_LINES) break;
			}

			m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].time = next_time_c;
			
			m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].lyric = 
				new char[1];
			strcpy(m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].lyric,"");

			m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].chord = 
				new char[c_list[c_syll].len+1];
			strcpy(m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].chord,
				c_list[c_syll].text);

			m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].char_pos = char_pos;
			m_lfr.lyricframelist[m_lfr.no_lyric_lines][line_index].x = x_l;

			char_pos += length_char;
			x_l += length_px;
			line_index++;
			c_syll++;
			continue;
		}
	}

	m_lfr.no_lyric_lines++;

	// initialize line_map array
	for(i=0; i<NO_FRAME_LINES;i++)
	{
		m_lfr.line_map[i] = -1;
	}

	// destroy l_list and c_list

	for (i=0; i<NO_LYRICS_CHORDS; i++)
	{
		if (l_list[i].time==-1) break;
		delete[] l_list[i].text;
	}

	for (i=0; i<NO_LYRICS_CHORDS; i++)
	{
		if (c_list[i].time==-1) break;
		delete[] c_list[i].text;
	}

/*   Testprotocol */ 
/*
	CString r;

	for (i=0; i<m_lfr.no_lyric_lines; i++)
	{
		for (k=0; k<NO_LYRICS_LINE; k++)
		{
			int time = m_lfr.lyricframelist[i][k].time;
			if (time==-1) break; // end of line

			bool is_lyric = (m_lfr.lyricframelist[i][k].lyric)[0] !=0;
			if (is_lyric)
			{
				r.Format("line %i, time=%i, lyric=%s, char_pos= %i, x= %i",
					i, time, m_lfr.lyricframelist[i][k].lyric,
					m_lfr.lyricframelist[i][k].char_pos, m_lfr.lyricframelist[i][k].x);
			}
			else
			{
				r.Format("line %i, time=%i, chord=%s, char_pos= %i, x= %i",
					i, time, m_lfr.lyricframelist[i][k].chord, 
					m_lfr.lyricframelist[i][k].char_pos, m_lfr.lyricframelist[i][k].x);
			}
			logf->add(r);			
//			::MessageBox(AfxGetMainWnd()->m_hWnd,r,"Test",MB_OK|MB_TASKMODAL);
		}
	}
*/
}

void CPlay::print(CString protfile, bool show)
{
	m_lfr.print(protfile, show,hpmfi->with_xfchords);
}


void CPlay::set_play_tempo()
{
	nTempo=m_slider_tempo.GetPos()*10;
	CString r;
	r.Format("%i%%",nTempo);
	SetDlgItemText(IDC_TEMPO_DISPLAY,r);
	HP_PlayTempo(mf,nTempo);		
}

void CPlay::set_play_transpose()
{
	nTranspose=m_slider_transpose.GetPos();

	// channels with active mega voices nTranspose != 0 not possible
	if (nTranspose!=0)
	{
		int chan;
		for (chan=0; chan<16; chan++)
		{
			if (mega_channel_list[chan] && !chan_mute_list[chan])
			{
				OnDefaultTranspose();
				::MessageBox(AfxGetMainWnd()->m_hWnd,
					GlobalUtilities::get_resource_string(IDS_PLAY_TRANSFORM_MEGAVOICE),"",MB_OK|MB_TASKMODAL);
			}
		}
	}

	CString r;
	r.Format("%i",nTranspose);
	SetDlgItemText(IDC_TRANSPOSE_DISPLAY,r);
	HP_PlayTranspose(mf,nTranspose, chan_transpose_list);
}

void CPlay::set_play_volume(int volume)
{
	unsigned char XG_master_volume_data[9] =
		{0xf0,0x43,0x10,0x4c,0x00,0x00,0x04,0x00,0xf7};
//	unsigned char XG_ctrl7_chan1_data[3] = {0xb0, 0x07, 0x40}; Test mit Ctrl. 7

	nVolume=m_slider_volume.GetPos();

	XG_master_volume_data[7] = nVolume;
	int result = HP_PlaySingleEvent(mf,XG_master_volume_data,9);
//	XG_ctrl7_chan1_data[2] = nVolume;
//	int result = HP_PlaySingleEvent(mf,XG_ctrl7_chan1_data,3);

}

void CPlay::set_play_mute()
{
	HP_PlayMute(mf, chan_mute_list);
}

//**************************************************************************
//*
//*		OnPlay
//*		starts Playing
//*
//**************************************************************************

void CPlay::OnPlay() 
{
  	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = mainfun->Selectsource();
		if (hpmfi==NULL)
		{
			return;
		}
	}

	if (HP_IsPlaying(mf))
	{
		is_pause = hpmfi->Pause();
		if (is_pause)
		{
			m_play.SetIcon(is_record?hIcon_play_green:hIcon_play);
		}
		else
		{
			m_play.SetIcon(is_record?hIcon_pause_green:hIcon_pause);
		}
		return;
	}
	is_pause = false;

	if (hpmfi->with_lyrics || hpmfi->with_xfchords)
	{
		m_lfr.initialize_first_frame(0,0);
	}


	UINT result;

	int lt, lb, tm;
	hpmfi->get_last_takt_beat(&lt,&lb,&tm);

	CString last_takt_beat;
	last_takt_beat.Format("%4.4i:%2.2i",lt+1,lb+1);
	SetDlgItemText(IDC_LAST_TKT_BEAT,last_takt_beat);

	result = HP_Play(mf,HP_ALL);

	if (result != HP_ERR_NONE)
	{
		if (result == HP_ERR_ALLOCATED_DEVICE)
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_MIDI_PORT),NULL,MB_OK|MB_TASKMODAL);
			return;
		}
		else
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_PLAY),NULL,MB_OK|MB_TASKMODAL);
			return;
		}
	}

	// activate timer
	m_nTimer = SetTimer(1, 500, 0);


	set_play_tempo();
	set_play_transpose();
	set_play_mute();

	if (new_slider_time > 0)
	{
		if ((hpmfi->with_lyrics)||(hpmfi->with_xfchords))
		{
			m_lfr.posit_time(new_slider_time);
		}
		HP_SetPlayTime(mf,new_slider_time);
	}

	is_record = is_record_prepared;
	if (is_record)
	{
		m_record_chords.SetIcon(hIcon_record_green);
		m_play.SetIcon(hIcon_play);
		act_list_no = 0;

		// Display chords
		SetDlgItemText(IDC_ACTUAL_LYRIC_CHORD,"");
		SetDlgItemText(IDC_NEXT_LYRIC_CHORD,record_chord_lyric_list[0].text);
	}

	m_play.SetIcon(is_record?hIcon_pause_green:hIcon_pause);
	m_ok.EnableWindow(FALSE);
	m_stop.EnableWindow(TRUE);
//	m_stop.SetFocus();
}

void CPlay::Stop()
{
	OnStop();
}


void CPlay::OnStop() 
{
	if (hpmfi != NULL)
	{
		if (is_record)
		{
			is_record = false;
			m_record_chords.SetIcon(hIcon_record_yellow);
			m_play.SetIcon(hIcon_play_green);
			SetDlgItemText(IDC_ACTUAL_LYRIC_CHORD,"");
			SetDlgItemText(IDC_NEXT_LYRIC_CHORD,record_chord_lyric_list[0].text);
			SetDlgItemText(IDC_REC_CHORD_LYRIC_TEXT,record_text);

			// Test chordlist
			if (act_list_no > 0)
			{
				m_insert_chords_lyrics.EnableWindow(TRUE);
			}
		}

		hpmfi->Stop();
		if (hpmfi->with_lyrics || hpmfi->with_xfchords)
		{
			m_lfr.EraseRegion();
			char *ps;
			char *cn;
			char *composer;
			char *lyricist;

			GlobalUtilities::convert_CString_to_cstring(&ps,hpmfi->proposed_songname);
			GlobalUtilities::convert_CString_to_cstring(&cn,hpmfi->copyrightname);
			GlobalUtilities::convert_CString_to_cstring(&composer,hpmfi->composer);
			GlobalUtilities::convert_CString_to_cstring(&lyricist,hpmfi->lyricist);
			m_lfr.display_title(ps,cn,composer, lyricist);
			delete[] ps;
			delete[] cn;
			delete[] composer;
			delete[] lyricist;
		}
	}
	else
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		hpmfi = mainfun->Selectsource();
		if (hpmfi==NULL)
		{
			return;
		}
	}

	m_play.SetIcon(hIcon_play);
	m_ok.EnableWindow(TRUE);
	m_stop.EnableWindow(FALSE);
//	m_play.SetFocus();
}

void CPlay::OnTimer(UINT nIDEvent) 
{
	CString r;
	if (!HP_IsPlaying(mf))
	{	// play done
		KillTimer(m_nTimer);
		m_nTimer = NULL;
		if (hpmfi->with_lyrics || hpmfi->with_xfchords)
		{
			m_lfr.EraseRegion();
			char *ps;
			char *cn;
			char *composer;
			char *lyricist;
			
			GlobalUtilities::convert_CString_to_cstring(&ps,hpmfi->proposed_songname);
			GlobalUtilities::convert_CString_to_cstring(&cn,hpmfi->copyrightname);
			GlobalUtilities::convert_CString_to_cstring(&composer,hpmfi->composer);
			GlobalUtilities::convert_CString_to_cstring(&lyricist,hpmfi->lyricist);
			m_lfr.display_title(ps,cn,composer, lyricist);

			delete[] ps;
			delete[] cn;
			delete[] composer;
			delete[] lyricist;
		}
		if (is_record)
		{
			is_record = false;
			m_record_chords.SetIcon(hIcon_record_yellow);
			m_play.SetIcon(hIcon_play_green);
			SetDlgItemText(IDC_REC_CHORD_LYRIC_TEXT,record_text);
			m_insert_chords_lyrics.EnableWindow(TRUE);
			SetDlgItemText(IDC_ACTUAL_LYRIC_CHORD,"");
			SetDlgItemText(IDC_NEXT_LYRIC_CHORD,record_chord_lyric_list[0].text);
		}
		else
		{
			m_play.SetIcon(hIcon_play);
		}
		m_ok.EnableWindow(TRUE);
		m_stop.EnableWindow(FALSE);
		m_play.SetFocus();

		// set volume slider at original value
		int volume = orig_master_volume==-1?127:orig_master_volume;
		m_slider_volume.SetPos(volume);
		r.Format("%i",volume);
		SetDlgItemText(IDC_VOLUME_DISPLAY,r);
	}
	
	if (is_record && HP_IsPlaying(mf))
	{
		if (signal_record_text)
		{
			SetDlgItemText(IDC_REC_CHORD_LYRIC_TEXT,"Recording");
			m_record_chords.SetIcon(hIcon_record_darkgreen);
		}
		else
		{
			SetDlgItemText(IDC_REC_CHORD_LYRIC_TEXT,"");
			m_record_chords.SetIcon(hIcon_record_green);
		}
		m_play.SetIcon(is_pause?hIcon_play_green:hIcon_pause_green);
		signal_record_text = !signal_record_text;
		InvalidateRect(&record_rect,FALSE);
		UpdateWindow();
	}


	CDialog::OnTimer(nIDEvent);
}


void CPlay::OnOK() 
{
	if (HP_IsPlaying(mf))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_STOP_PLAY),NULL,MB_OK|MB_TASKMODAL);
		return;
	}

	// destroy lyricframelist
	if ((hpmfi->with_lyrics)||(hpmfi->with_xfchords))
	{
		int i,k;
		for (i=0; i<m_lfr.no_lyric_lines; i++)
		{
			for (k=0; k<NO_LYRICS_LINE;k++)
			{
				if (m_lfr.lyricframelist[i][k].lyric != NULL) 
					delete[] m_lfr.lyricframelist[i][k].lyric;
				if (m_lfr.lyricframelist[i][k].chord != NULL) 
					delete[] m_lfr.lyricframelist[i][k].chord;
			}
		}
	}
	HP_InitPlayMonitor(mf,NULL);
	CDialog::OnOK();
}

//**************************************************************************
//**************************************************************************
//*
//*		Play Monitor functions
//*
//**************************************************************************
//**************************************************************************

void MY_PLAY_MONITOR::HP_PlayTBMonitor(int takt, int beat)
{
   if ((takt<0) || (beat<0))
   {
      CString r;
      r.Format("%4.4i:%2.2i",1,1);
      SetDlgItemText(whandle,IDC_TAKT_BEAT,r);
	  return;
   }

   CString r;
   r.Format("%4.4i:%2.2i",takt+1,beat+1);
   SetDlgItemText(whandle,IDC_TAKT_BEAT,r);
}

void MY_PLAY_MONITOR::HP_PlayChMonitor(char* chord_text)
{
//	logf->add("HP_PlayChMonitor received %s",chord_text);

	if (strlen(chord_text)!=0)
	{
//		 logf->add("   HP_PlayChMonitor sent %s",chord_text);

		p_lfr->display_next_chord(chord_text);
	}
	HP_Delete(chord_text); // always needed !
}

void MY_PLAY_MONITOR::HP_PlayLyMonitor(char* lyric_text)
{
	bool is_text = false;
	int i;

//	logf->add("HP_PlayLyMonitor received %s",lyric_text);

	// skip lyrics without text
	for (i=0; i < (int) strlen(lyric_text); i++)
	{
		if ((lyric_text[i] != '/')  && 
			(lyric_text[i] != 0x0d) && 
			(lyric_text[i] != 0x0a) )
		{
			is_text = true;
			break;
		}
	}
	if ((lyric_text[0]!=0) && is_text)
	{
//		logf->add("   HP_PlayLyMonitor sent %s",lyric_text);
		p_lfr->display_next_lyric(lyric_text);
	}
	HP_Delete(lyric_text); // always needed !
}


void CPlay::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{

	if (pScrollBar==(CScrollBar*)&m_slider_tempo)
	{
		set_play_tempo();
	}
	else

	if (pScrollBar==(CScrollBar*)&m_slider_transpose)
	{
		set_play_transpose();
	}	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPlay::OnDefaultTempo() 
{
	m_slider_tempo.SetPos(10);
	set_play_tempo();	
}

void CPlay::OnDefaultTranspose() 
{
	m_slider_transpose.SetPos(0);
	set_play_transpose();	
}

void CPlay::OnClose() 
{
	OnOK();
}

void CPlay::OnRecordChordsLyrics() 
{
	SetDlgItemText(IDC_REC_CHORD_LYRIC_TEXT,"");
	SetDlgItemText(IDC_ACTUAL_LYRIC_CHORD,"");
	SetDlgItemText(IDC_NEXT_LYRIC_CHORD,"");
	m_insert_chords_lyrics.EnableWindow(FALSE);
	m_play.SetFocus();


	if (!is_record_prepared)
	{
		if (!initialize_recording())
		{
			return;
		}
		m_record_chords.SetIcon(hIcon_record_yellow);
		m_play.SetIcon(hIcon_play_green);
		is_record_prepared = true;
		SetDlgItemText(IDC_ACTUAL_LYRIC_CHORD,"");
		SetDlgItemText(IDC_NEXT_LYRIC_CHORD,record_chord_lyric_list[0].text);
	}
	else
	{
		m_record_chords.SetIcon(hIcon_record_red);
		m_play.SetIcon(hIcon_play);

		SetDlgItemText(IDC_ACTUAL_LYRIC_CHORD,"");
		SetDlgItemText(IDC_NEXT_LYRIC_CHORD,"");
		is_record = false;
		is_record_prepared = false;
	}
	InvalidateRect(&record_rect,FALSE);
	UpdateWindow();
}

bool CPlay::initialize_recording()
{
	CString recordfile;
	int i;

	char BASED_CODE szFilter[] = 
		"Chord- or Lyric-File (*.txt)|*.txt||";

	CFileDialog openfile_dlg(TRUE,
						  "txt",
						  NULL,
						  OFN_PATHMUSTEXIST,
						  szFilter,
						  NULL);

	// Get last_recordfile
	CString last_record = o_inifile->get_recordfile();
	if (last_record != "")
	{
	   char lr[MAX_PATH];
	   for (i=0; i<last_record.GetLength(); i++)
	   {
		   lr[i] = last_record[i];
	   }
	   lr[last_record.GetLength()] = (char)0;
	   openfile_dlg.m_ofn.lpstrFile = lr;
	}

	int return_value = openfile_dlg.DoModal();
	if (return_value == IDOK)
	{
		recordfile = openfile_dlg.m_ofn.lpstrFile;
	}
	else 
	{
		if (return_value == IDCANCEL)
		{
			return false;
		}
	}

	// Try recordfile

	CFile mf_newf;
	CFileException e;

	if (mf_newf.Open(recordfile, CFile::modeRead,&e))
	{
		int length = mf_newf.GetLength();

		if (length==0)
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_FILE_EMPTY),NULL,MB_OK|MB_TASKMODAL);
			mf_newf.Close();
			return false;
		}
	}
	else
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_NO_ACCESS_TO_FILE),NULL,MB_OK|MB_TASKMODAL);
		return false;
	}
	mf_newf.Close();

	// initialize record_chord_lyric_list;
	record_chord_lyric_length = 0;
	
	// check chordfile and fill record_chord_lyric_list

	CStdioFile *cf_f = new CStdioFile;
	if (!cf_f->Open(recordfile, CFile::shareExclusive | CFile::modeRead | CFile::typeText, &e))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_FILE_MISSED),NULL,MB_OK|MB_TASKMODAL);
		delete cf_f;
		cf_f = NULL;
		return false; // file does not exist
    }

	int line_number = 0;
	int list_number = 0;

	CString line;
	is_chord_record = false;
	is_lyric_record = false;

	while (true)
	{
		if (!cf_f->ReadString(line)) 
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_NO_START_CHORDLIST_OR_LYRICLIST),NULL,MB_OK|MB_TASKMODAL);
			cf_f->Close();		
			delete cf_f;
			cf_f = NULL;
			return false;
		}
		line_number ++;
		line.TrimRight();
		if (line == start_chordlist)
		{
			if (hpmfi->with_xfchords)
			{
				CString r = GlobalUtilities::get_resource_string(IDS_XFCHORDSREMOVE);
				if (IDNO==AfxMessageBox(r,MB_YESNO,0))
				{
					cf_f->Close();		
					delete cf_f;
					cf_f = NULL;
					return false;
				}
				else
				{
					hpmfi->remove_lyrics_chords(CHORDS);
					prepare_lyrics_chords();
					hpmfi->with_xfchords = false;
				}
			}
			
			is_chord_record = true;	
			break;
		}

		CString line1 = line;
		line1.TrimRight();

		if (line1 == GlobalUtilities::start_lyriclist)
		{
			if (hpmfi->with_lyrics)
			{
				CString r = GlobalUtilities::get_resource_string(IDS_LYRICSREMOVE);
				if (IDNO==AfxMessageBox(r,MB_YESNO,0))
				{
					cf_f->Close();		
					delete cf_f;
					cf_f = NULL;
					return false;
				}
				else
				{
					hpmfi->remove_lyrics_chords(LYRICS);
					prepare_lyrics_chords();
					hpmfi->with_lyrics = false;
				}
			}

			is_lyric_record = true;			
			break;
		}
	}

	// read and store chords/lyrics in list
	while (true)
	{

		if (!cf_f->ReadString(line)) 
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_NO_END_LIST),NULL,MB_OK|MB_TASKMODAL);
			cf_f->Close();		
			delete cf_f;
			cf_f = NULL;
			return false;
		}
		if (list_number >= NO_CHORDS_LYRICS)
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_OVERFLOW_CHORDS_LYRICS),NULL,MB_OK|MB_TASKMODAL);
			cf_f->Close();		
			delete cf_f;
			cf_f = NULL;
			return false;
		}
		line.TrimRight();
		if (line == GlobalUtilities::end_list)
		{
			break;
		}

		if (is_chord_record)
		{	
			// check line
			int char_no = 0;
			while (true)
			{
				CString chtxt;
				while (char_no < line.GetLength())
				{
					char ch = line.GetAt(char_no);
					if (((ch>='0')&&(ch<='9')) ||
						((ch>='A')&&(ch<='Z')) ||
						((ch>='a')&&(ch<='z')) ||
						(ch=='#')||
						(ch=='/')||
						(ch=='(')||
						(ch==')')
						)
					{
						chtxt += ch;
						char_no++;
					}
					else
					{
						char_no++;
						break;
					}
				}
					
				if (!GlobalUtilities::find_cr_ct_bn_bt(chtxt,
					    &record_chord_lyric_list[list_number].cr,
					    &record_chord_lyric_list[list_number].ct,
					    &record_chord_lyric_list[list_number].bn,
					    &record_chord_lyric_list[list_number].bt))
				{
					CString r;
					r.Format("(%i) "+line+"\n%s",line_number,GlobalUtilities::get_resource_string(IDS_ERROR_CHORDFILE));
					::MessageBox(AfxGetMainWnd()->m_hWnd,r,NULL,MB_OK|MB_TASKMODAL);
					cf_f->Close();		
					delete cf_f;
					cf_f = NULL;
					return false;
				}
				record_chord_lyric_list[list_number].text = chtxt;
				record_chord_lyric_list[list_number].time = -1;
				list_number++;
				record_chord_lyric_length++;
				if (char_no >= line.GetLength()) break;
			}
			line_number++;
		}

		if (is_lyric_record)
		{
			// check line
			int char_no = 0;
			char ch = (char)0;
			char last_ch = (char)0;
			char next_ch = (char)0;
			while (true)
			{
				CString lyrictxt;
				while (char_no < line.GetLength())
				{
					if (char_no > 0)
					{
						last_ch = ch;
					}

					ch = line.GetAt(char_no);

					if (char_no < line.GetLength()-1)
					{
						next_ch = line.GetAt(char_no+1);
					}

					if (GlobalUtilities::is_printable(ch))
					{
						if (ch=='/')
						{
							lyrictxt += linefeed_char;
						}
						else
						if (ch=='_')
						{
							lyrictxt += ' ';
						}
						else
						if (ch=='-')
						{ // display '-' sequences outside of words
							if 	(!GlobalUtilities::is_letter(last_ch) || (!GlobalUtilities::is_letter(next_ch)))
							{
								lyrictxt += ch;
								char_no++;
								continue;
							}
							else
							{
								char_no++;
								break;
							}
						}
						else
						if (ch==' ') 
						{
							lyrictxt += ch;
							char_no++;
							break;
						}
						else
						{
							lyrictxt += ch;
						}
						char_no++;
					}
					else
					{
						char_no++;
						break;
					}
				}
				record_chord_lyric_list[list_number].text = lyrictxt;
				record_chord_lyric_list[list_number].time = -1;
				list_number++;
				record_chord_lyric_length++;
				if (char_no >= line.GetLength()) break;
			}

			line_number++;
			last_ch = (char)0;

			// create implicite linefeed
			CString lf = "";
			lf += linefeed_char;
			record_chord_lyric_list[list_number].text = lf;
			record_chord_lyric_list[list_number].time = -2; // marker for implicite linefeed
			list_number++;
			record_chord_lyric_length++;
		}
	}

	cf_f->Close();
	delete cf_f;
	cf_f = NULL;

	if (record_chord_lyric_length > 0)
	{	// Display text
		SetDlgItemText(IDC_ACTUAL_LYRIC_CHORD,"");
		SetDlgItemText(IDC_NEXT_LYRIC_CHORD,record_chord_lyric_list[0].text);

		o_inifile->set_recordfile(recordfile);

		signal_record_text = true;
		record_text = is_chord_record?"Chords":"Lyrics";
		SetDlgItemText(IDC_REC_CHORD_LYRIC_TEXT,record_text);
		return true;
	}
	else
	{
		return false;
	}
}

void CPlay::OnInsertChordsLyrics() 
{
	is_record = false;
    is_record_prepared = false;
	m_record_chords.SetIcon(hIcon_record_red);
	m_play.SetIcon(hIcon_play);
	SetDlgItemText(IDC_ACTUAL_LYRIC_CHORD,"");
	SetDlgItemText(IDC_NEXT_LYRIC_CHORD,"");
	SetDlgItemText(IDC_REC_CHORD_LYRIC_TEXT,"");
	record_chord_lyric_length = 0;
	m_insert_chords_lyrics.EnableWindow(FALSE);
	m_play.SetFocus();

	if (act_list_no==0) 
	{
		return;
	}

	InsertChordLyrics *icl = new InsertChordLyrics();

	icl->hpmfi = hpmfi;
	icl->mf = mf;
	icl->record_chord_lyric_list = record_chord_lyric_list;
	icl->play_tempo = nTempo;
	icl-> act_list_no = act_list_no;
	icl->is_chord_record = is_chord_record;
	icl->is_lyric_record = is_lyric_record;
	icl->linefeed_char = linefeed_char;


	int dlg_result = icl->DoModal();
	delete icl;
	icl = NULL;

	if (dlg_result==IDOK)
	{
		if (is_chord_record) hpmfi->with_xfchords = true;
		if (is_lyric_record) 
		{
			hpmfi->with_lyrics = true;
			if ((!hpmfi->with_cuepoint_lyrics)&&(hpmfi->lyric_cuepoint))
			{
				hpmfi->eval_cuepoint_lyric(0);
			}
		}	
		prepare_lyrics_chords();
		source_changed = true;
	}
	act_list_no = 0;
}

void CPlay::OnReleasedcaptureSliderTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	new_slider_time = m_slider_time.GetPos();
	if (HP_IsPlaying(mf))
	{
		if ((hpmfi->with_lyrics)||(hpmfi->with_xfchords))
		{
			m_lfr.posit_time(new_slider_time);
		}

		if (!is_pause) is_pause = hpmfi->Pause();
		is_pause = hpmfi->Pause();
		HP_SetPlayTime(hpmfi->mf,new_slider_time);
		m_play.SetIcon(is_record?hIcon_play_green:hIcon_pause);
	}
	*pResult = 0;
}

void CPlay::OnCustomdrawSliderTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int slider_time = m_slider_time.GetPos();
	int takt, bar, tick;

	hpmfi->get_takt_bar_tick_from_time(slider_time, &takt, &bar, &tick);
    CString r;
    r.Format("%4.4i:%2.2i",takt+1,bar+1);
    SetDlgItemText(IDC_SLIDER_TIME_POS,r);
	*pResult = 0;
}

void CPlay::OnReleasedcaptureSliderMasterVolume(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int slider_volume;
	if (HP_IsPlaying(mf))
	{
		slider_volume = m_slider_volume.GetPos();
		set_play_volume(slider_volume);
		m_play.SetIcon(is_record?hIcon_play_green:hIcon_pause);
	}
	*pResult = 0;
}

void CPlay::OnCustomdrawSliderMasterVolume(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString r;
	int slider_volume = m_slider_volume.GetPos();

	if (HP_IsPlaying(mf))
	{
		r.Format("%i",slider_volume);
		SetDlgItemText(IDC_VOLUME_DISPLAY,r);
	}
/*
does not work
	else
	{
		slider_volume = orig_master_volume==-1?127:orig_master_volume;
		m_slider_volume.SetPos(slider_volume);
		r.Format("%i",slider_volume);
		SetDlgItemText(IDC_VOLUME_DISPLAY,r);
	}
*/

	*pResult = 0;
}

void CPlay::check_chan(int chan)
{
	chan_mute_list[chan] = (check_chan_ctrl[chan]->GetCheck())==0;
	set_play_mute();
}


void CPlay::OnCheckEins() 
{
	check_chan(0);	
}

void CPlay::OnCheckZwei() 
{
	check_chan(1);	
}

void CPlay::OnCheckDrei() 
{
	check_chan(2);	
}

void CPlay::OnCheckVier() 
{
	check_chan(3);	
}

void CPlay::OnCheckFuenf() 
{
	check_chan(4);	
}

void CPlay::OnCheckSechs() 
{
	check_chan(5);	
}

void CPlay::OnCheckSieben() 
{
	check_chan(6);	
}

void CPlay::OnCheckAcht() 
{
	check_chan(7);	
}

void CPlay::OnCheckNeun() 
{
	check_chan(8);	
}

void CPlay::OnCheckZehn() 
{
	check_chan(9);	
}

void CPlay::OnCheckElf() 
{
	check_chan(10);	
}

void CPlay::OnCheckZwoelf() 
{
	check_chan(11);	
}

void CPlay::OnCheckDreizehn() 
{
	check_chan(12);	
}

void CPlay::OnCheckVierzehn() 
{
	check_chan(13);	
}

void CPlay::OnCheckFuenfzehn() 
{
	check_chan(14);	
}

void CPlay::OnCheckSechzehn() 
{
	check_chan(15);	
}

void CPlay::OnCheckPlayAll()
{
	int chan;

	int check_all = m_check_play_all.GetCheck(); 
	for (chan = 0; chan < 16; chan++)
	{
		if ((hpmfi->mute)[chan]) continue;

		check_chan_ctrl[chan]->SetCheck(check_all);
		chan_mute_list[chan] = (check_all==0);
	}
	set_play_mute();
}

void CPlay::OnKillFocusSliderTimePos() 
{
	int i,k;
	char ch;
	int takt = 0;
	bool takt_ok = false;
	bool bar_ok = false;
	int bar = 0;
	int old_slider_time = m_slider_time.GetPos();

	// compute takt and bar from line
	
	char line[10];
	for (i=0; i<10; i++)
	{
		line[i] = (char)0x00;
	}
	int len = m_slider_time_pos.GetLine(0,line,10);
	line[len] = 0;

	for (i=0; i<10;i++)
	{
		ch = line[i];
		if (ch==':')
		{
			if (takt==0)
			{
				takt = 1;
			}
			takt_ok = true;
			break;
		}
		if (ch==(char)0x00)
		{
			if (takt==0)
			{
				takt = 1;
			}
			bar = 1;
			takt_ok = true;
			bar_ok = true;
			break;
		}
		if (((int)ch<(int)'0')||((int)ch>(int)'9'))
		{
			takt_ok = false;
			bar_ok = false;
			break;
		}
		else 
		{
			takt = 10*takt + (int)ch - (int)'0';
		}
	}
	if (takt != 0)
	{
		takt_ok = true;
	}
	if (takt_ok && !bar_ok)
	{
		for (k=i+1; k<10; k++)
		{
			ch = line[k];
			if (ch==(char)0x00)
			{
				if (bar==0)
				{
					bar=1;
				}
				bar_ok = true;
				break;
			}
			if (((int)ch<(int)'0')||((int)ch>(int)'9'))
			{
				bar_ok = false;
				break;
			}
			else 
			{
				bar = 10*bar + (int)ch - (int)'0';
			}
		}
	}
	if (!takt_ok || !bar_ok)
	{
		SetDlgItemText(IDC_SLIDER_TIME_POS,"0001:01");
		return;
	}
	takt = takt>0?takt-1:0;
	bar  = bar>0?bar-1:0;
	new_slider_time = hpmfi->get_time_from_takt_bar_tick(takt, bar, 0);
	if (new_slider_time == -1)
	{
		SetDlgItemText(IDC_SLIDER_TIME_POS,"0001:01");
		return;
	}

	m_slider_time.SetPos(new_slider_time);

	if (HP_IsPlaying(mf))
	{
		HP_SetPlayTime(mf,new_slider_time);
		if ((hpmfi->with_lyrics)||(hpmfi->with_xfchords))
		{
			m_lfr.posit_time(new_slider_time);
		}
	}
}

