// ChordsLyricsEditor.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "ChordsLyricsEditor.h"
#include "LyricChordEditDlg.h"
#include "math.h"
#include "IniFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const COLORREF CChordsLyricsEditor::color_lyric = RGB(0,0,255);
const COLORREF CChordsLyricsEditor::color_chord = RGB(255,0,0);
const COLORREF CChordsLyricsEditor::color_black = RGB(0,0,0);
const COLORREF CChordsLyricsEditor::color_green = RGB(0,255,0);
const COLORREF CChordsLyricsEditor::color_lyric_light = RGB(180,180,255);
const COLORREF CChordsLyricsEditor::color_chord_light = RGB(255,180,180);

const int CChordsLyricsEditor::max_zoom = 40;
const double CChordsLyricsEditor::max_factor = 8.0;


int CChordsLyricsEditor::max_rel_time_in_rgn_init = 2880;
int CChordsLyricsEditor::rel_pos_act_time_in_rgn_init = 80;


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CChordsLyricsEditor 


CChordsLyricsEditor::CChordsLyricsEditor(CWnd* pParent /*=NULL*/)
	: CDialog(CChordsLyricsEditor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChordsLyricsEditor)
//	m_select_lyric_lines = FALSE;
	//}}AFX_DATA_INIT

	l_button_down = false;
	l_button_paste_down = false;
	scroll_pos = 0;
	clicked_array_index = -1;
	m_nTimer = NULL;
	is_lyric_insert = false;

	rasterize = false;
}


void CChordsLyricsEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChordsLyricsEditor)
	DDX_Control(pDX, IDC_SELECT_WORDS_SYLLABLES, m_select_words);
	DDX_Control(pDX, IDC_LYRIC_LINES, m_lyric_lines_box);
	DDX_Control(pDX, IDC_ZOOM_SLIDER, m_zoom_slider);
	DDX_Control(pDX, IDC_CHORD_RASTER_COMBO, m_chord_raster_combo);
	DDX_Control(pDX, IDC_EDIT_SLIDER_TEMPO, m_edit_slider_tempo);
	DDX_Control(pDX, IDC_CHORD_LYRIC_SYLLABLE,m_chord_lyric_syllable);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_EDIT_SLIDER_TIME, m_edit_slider_time);
	DDX_Control(pDX, IDC_EDIT_STOP, m_edit_stop);
	DDX_Control(pDX, IDC_EDIT_PLAY, m_edit_play);
	DDX_Control(pDX, IDC_RGN_SLIDER, m_rgn_slider);
	DDX_Control(pDX, IDC_SELECT_LYRIC_LINES, m_select_lyric_lines);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChordsLyricsEditor, CDialog)
	//{{AFX_MSG_MAP(CChordsLyricsEditor)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_RGN_SLIDER, OnCustomdrawRgnSlider)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_EDIT_PLAY, OnEditPlay)
	ON_BN_CLICKED(IDC_EDIT_STOP, OnEditStop)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_EDIT_SLIDER_TIME, OnReleasedcaptureEditSliderTime)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_EDIT_SLIDER_TIME, OnCustomdrawEditSliderTime)
	ON_EN_CHANGE(IDC_EDIT_SLIDER_POS, OnChangeEditSliderPos)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_EDIT_DEFAULT_TEMPO, OnEditDefaultTempo)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_EDIT_SLIDER_TEMPO, OnCustomdrawEditSliderTempo)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_EDIT_SLIDER_TEMPO, OnReleasedcaptureEditSliderTempo)
	ON_WM_MOUSEWHEEL()
	ON_CBN_SELCHANGE(IDC_CHORD_RASTER_COMBO, OnSelchangeChordRasterCombo)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ZOOM_SLIDER, OnCustomdrawZoomSlider)
	ON_BN_CLICKED(IDC_INIT_ZOOM, OnInitZoom)
	ON_BN_CLICKED(IDC_SELECT_LYRIC_LINES, OnSelectLyricLines)
	ON_BN_CLICKED(IDC_SELECT_WORDS_SYLLABLES, OnSelectWordsSyllables)
	ON_WM_CANCELMODE()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_START_RECORD, OnStartRecord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CChordsLyricsEditor 

BOOL CChordsLyricsEditor::PreTranslateMessage(MSG* pMSG)
{
    if ((pMSG->message==WM_KEYDOWN)&&(pMSG->wParam==VK_SPACE))
    {
		OnEditPlay();
		return TRUE;		
	}
/*
    if ((pMSG->message==WM_LBUTTONDOWN)&&(pMSG->wParam==MK_LBUTTON))
    {
//		MessageBox("PreTranslate");
		int xPos = LOWORD(pMSG->lParam); 
		int yPos = HIWORD(pMSG->lParam);
		if((xPos<=23)&&(yPos<=19))
		{


//			CString r;
//			r.Format("xPos %x, yPos %x",xPos,yPos);
//			MessageBox(r);
//			OnEditPlay();
			return CDialog::PreTranslateMessage(pMSG);
		}
	}
*/



	return CDialog::PreTranslateMessage(pMSG);
}


BOOL CChordsLyricsEditor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	dc = this->GetDC();
	wnd = this;
	mf = hpmfi->mf;

	RECT rect;
    GetClientRect(&rect);
/*
	CString r;
	r.Format("left %i, right %i, top %i, bottom %i",rect.left,rect.right,rect.top,rect.bottom);
    MessageBox(r);
*/

	rgn_x1 = 20;		// upper-left corner
    rgn_y1 = 30;
 	rgn_x2 = 790;		// lower_right corner
    rgn_y2 = 150;

	pos_x = 13;
    pos_y = 35;

    m_x = 0;							// upper left corner of m_memDC 
    m_y = 0;

    m_w = 790-20;	// width and height of m_memDC 
    m_h = 150-30;

	lenx = -1;

    lyric_y = 105;    // y-position of all lyrics 
    linefeed_y = 126; // y-position of all single linefeeds 
    chord_y = 50;     // y-position of all chords 
	height_of_text_line = 20;

	// Icons for Play, Pause- and Stop-Buttons

	hIcon_play = AfxGetApp()->LoadIcon(IDI_ICON3);
	m_edit_play.SetIcon(hIcon_play);
	hIcon_pause = AfxGetApp()->LoadIcon(IDI_ICON2);
	hIcon_stop = AfxGetApp()->LoadIcon(IDI_ICON4);
	m_edit_stop.SetIcon(hIcon_stop);
	m_edit_stop.EnableWindow(FALSE);
	
	// Paint white background
	rgn.CreateRectRgn(rgn_x1, rgn_y1, rgn_x2, rgn_y2);
	white.CreateSolidBrush(0x00ffffff);
	red.CreateSolidBrush(0x000000ff);

	// zoom slider
	m_zoom_slider.SetRange(0,max_zoom,TRUE);
	init_zoom_factor = 1.0;
	m_zoom_slider.SetPos(max_zoom/2);

	max_rel_time_in_rgn = max_rel_time_in_rgn_init;
	rel_pos_act_time_in_rgn = rel_pos_act_time_in_rgn_init;

	// rgn pos slider
	HP_GetLastTime(hpmfi->mf,&last_time);
	m_rgn_slider.SetRange(0,last_time,TRUE);
	m_rgn_slider.SetPos(0);
	act_time = 0;
	SetDlgItemText(IDC_CHORD_POS,"");

	// time slider
	new_edit_slider_time = 0;
	play_time = 0;
	m_edit_slider_time.SetRange(0,last_time,TRUE);
	m_edit_slider_time.SetPos(0);

	// tempo slider
	m_edit_slider_tempo.SetRange(1,30,TRUE);
	m_edit_slider_tempo.SetPos(10);
	SetDlgItemText(IDC_EDIT_TEMPO_DISPLAY,"100%");

	// chord raster list

	m_chord_raster_combo.InsertString(0,"---");
	m_chord_raster_combo.InsertString(1,"1/4");
	m_chord_raster_combo.InsertString(2,"1/8");
	m_chord_raster_combo.InsertString(3,"1/16");
	m_chord_raster_combo.InsertString(4,"1/32");
	
	m_chord_raster_combo.SetCurSel(4);
	chord_raster_ticks = 60;  

	hpmfi->fill_lyric_chord_edit_list(&lce_array);
/*
 // array test
	CString r;
	r.Format("no_chords %i, no_lyrics %i",lce_array.get_no_chords(),lce_array.get_no_lyrics());
	MessageBox(r);
	int i,k;
	for (i=0; (i<lce_array.get_length())&&(i<20); i++)
	{
		int type = lce_array.get_type(i);
		CString type_cstr = (type==CHORD_TYPE)?"chord":
							(type==LYRIC_TYPE)?"lyric":
							(type==LINEFEED_TYPE)?"linefeed":
							(type==TAKT_TYPE)?"takt":
							(type==BEAT_TYPE)?"beat":"";
		CString text = lce_array.get_text(i);
		for (k=0; k<text.GetLength();k++)
		{
			unsigned char ch = text.GetAt(k);
			if (ch==0x0d) text.SetAt(k,'/');
		}
		int takt, beat, tick;
		lce_array.get_takt_beat_tick(i,&takt,&beat,&tick);
		r.Format("lce_array[%i]: type %s, time %i, takt %i, beat %i, tick %i, text %s",
			i,
			type_cstr,
			lce_array.get_time(i),
			takt+1,
			beat+1,
			tick,
			text);
		MessageBox(r);
	}
*/

	InitDisplay(this);
	
	// MY_EDIT_PLAY_MONITOR initialization
	is_pause = false;
	pm.whandle = this->m_hWnd;
	pm.hpmfi = hpmfi;

	// initialize the monitor
	HP_InitPlayMonitor(hpmfi->mf,&pm);


	SetDlgItemText(IDC_EDIT_SLIDER_POS,"0001:01:000");

    // Record Lyrics
	m_select_lyric_lines.SetCheck(false);
	m_select_words.SetCheck(false);
	is_record = false;



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

// Initialize the display from a rectangle coordinates

void CChordsLyricsEditor::InitDisplay(CWnd *Wnd)
{
	wnd = Wnd;

	pdc = new CClientDC(Wnd);
	m_memDC.CreateCompatibleDC(pdc);

	m_bmp.CreateCompatibleBitmap(pdc,m_w,m_h);
	m_memDC.SelectObject(&m_bmp);

	m_cpen_black.CreatePen(PS_SOLID,0,RGB(0,0,0));
	m_cpen_grey.CreatePen(PS_DOT,0,RGB(30,30,30));
	m_cpen_green.CreatePen(PS_SOLID,0,RGB(0,255,0));
	
	m_bkbrush.CreateStockObject(WHITE_BRUSH);
	m_memDC.SelectObject(&m_bkbrush);
	
	m_memDC.PatBlt(m_x,m_y,m_w,m_h,PATCOPY);
	m_memDC.SetBkColor(RGB(255,255,255));
}

void CChordsLyricsEditor::OnPaint() 
{
//	CPaintDC dc(this); // device context for painting

	FillRgn();
	CDialog::OnPaint();
	
	// Kein Aufruf von CDialog::OnPaint() für Zeichnungsnachrichten
}


void CChordsLyricsEditor::blit()
{
	if (!pdc->BitBlt(pos_x+m_x, pos_y+m_y, m_w, m_h, &m_memDC, 0,0, SRCCOPY))
	{
		MessageBox("Internal Error BitBlt");
		return;
	}
}

int	CChordsLyricsEditor::compute_rgn_x(int rgn_time)
{
	double factor = (double)m_w/(double)max_rel_time_in_rgn;
	return ((int)((double)rgn_time*factor));
}

int	CChordsLyricsEditor::compute_rgn_x_midi_time(int time)
{
	if ((time<left_time_in_rgn)||(time>left_time_in_rgn+max_rel_time_in_rgn)) return -1;
	return compute_rgn_x(time-left_time_in_rgn);
}

int	CChordsLyricsEditor::compute_rgn_time(int x)
{
	double factor = (double)m_w/(double)max_rel_time_in_rgn;
	return ((int)((double)x/factor));
}

int	CChordsLyricsEditor::compute_midi_time_from_x(int x)
{	
	int rgn_x = x-pos_x;
	return(compute_rgn_time(rgn_x)+left_time_in_rgn);
}

void CChordsLyricsEditor::FillRgn()
{
	int i;
	for (i=0; i<lce_array.get_length(); i++)
	{
		(lce_array.get_rect(i))->SetRectEmpty();
	}

	m_memDC.PatBlt(m_x,m_y,m_w,m_h,PATCOPY); // clear region

	left_time_in_rgn = act_time-rel_pos_act_time_in_rgn; // may be < 0
	right_time_in_rgn = left_time_in_rgn+max_rel_time_in_rgn;

	Lines();
	Chords_Lyrics();
	PlayLine();
	blit();
}

void CChordsLyricsEditor::Lines()
{
	int start_time_line = rel_pos_act_time_in_rgn-act_time;
	if (start_time_line < 0) start_time_line = 0;
	int end_of_line = compute_rgn_x_midi_time(last_time);
	if (end_of_line==-1) end_of_line = m_w;

	// draw song line	
	m_memDC.SelectObject(&m_cpen_black);
	m_memDC.MoveTo(compute_rgn_x(start_time_line),m_h/2);
	m_memDC.LineTo(end_of_line,m_h/2);

    int i;
	CString meas_cstr;
	
	for (i=0; i<lce_array.get_length(); i++)
	{
		int type = lce_array.get_type(i);
		if ((type != TAKT_TYPE) && (type != BEAT_TYPE)) continue;
		if (type==TAKT_TYPE)
		{
			int takt_time = lce_array.get_time(i);
			if ((takt_time<left_time_in_rgn)||(takt_time>right_time_in_rgn)) continue;
			meas_cstr = lce_array.get_text(i);
			int x = compute_rgn_x_midi_time(takt_time);
			m_memDC.MoveTo(x,m_h/2-2);
			m_memDC.LineTo(x,m_h/2+7);
			set_meas_no_in_rgn(meas_cstr,x-3,m_h/2-13,color_black,8);
		}
		if (type==BEAT_TYPE)
		{
			int beat_time = lce_array.get_time(i);
			if ((beat_time<left_time_in_rgn)||(beat_time>right_time_in_rgn)) continue;
			int x = compute_rgn_x_midi_time(beat_time);
			m_memDC.MoveTo(x,m_h/2-1);
			m_memDC.LineTo(x,m_h/2+3);
		}
	}

	// draw dotted line between lyrics and linefeeds
	m_memDC.SelectObject(&m_cpen_grey); // color does not work!
	m_memDC.MoveTo(compute_rgn_x(start_time_line),(3*m_h)/4);
	m_memDC.LineTo(end_of_line,(3*m_h)/4);

}

void CChordsLyricsEditor::PlayLine()
{
	if ((play_time<left_time_in_rgn)||(play_time>right_time_in_rgn))
	{
		return;
	}
	int x = compute_rgn_x_midi_time(play_time);
	m_memDC.MoveTo(x,0);
	m_memDC.SelectObject(&m_cpen_green);
	m_memDC.LineTo(x,m_h);
}

	
void CChordsLyricsEditor::Chords_Lyrics()
{
	int i;
	int type;
	CString text;
	int chord_lyric_time;
	int x;
	
	for (i=0; i<lce_array.get_length(); i++)
	{
		type = lce_array.get_type(i);
		if (type==TAKT_TYPE) continue;
		chord_lyric_time = lce_array.get_time(i);
		if ((chord_lyric_time<left_time_in_rgn)||
			(chord_lyric_time>right_time_in_rgn)) continue;
		text = lce_array.get_text(i);
		x = compute_rgn_x_midi_time(chord_lyric_time);
		SetText(i,x,text);
	}
}


void CChordsLyricsEditor::SetText(int array_i, int x, CString text)
{
	// x,y local in region
	int type = lce_array.get_type(array_i);
	if ((type==LYRIC_TYPE)||(type==LINEFEED_TYPE))
	{
		m_memDC.SetTextColor(color_lyric);
		int y = (type==LYRIC_TYPE)?lyric_y-pos_y:linefeed_y-pos_y;
		CRect m_rect(x, y, 0,0); // local in m_memDC
		if (array_i == clicked_array_index)
		{
			m_memDC.SetTextColor(color_lyric_light);
		}
		else
		{
			m_memDC.SetTextColor(color_lyric);
		}
		m_memDC.DrawText(text,m_rect,DT_CALCRECT|DT_SINGLELINE);
		if (m_rect.right-m_rect.left<10) m_rect.right = m_rect.left+10;
		m_memDC.DrawText(text,m_rect,DT_SINGLELINE);

//      m_memDC.FillRect(&m_rect,&red);
		lce_array.set_rect(array_i,m_rect.left+pos_x-20, m_rect.top+pos_y, 
			                       m_rect.right+pos_x, m_rect.bottom+pos_y);
	}

	if (type==CHORD_TYPE)
	{
		CRect m_rect(x, chord_y-pos_y, 0,0); // local in m_memDC
		if (array_i == clicked_array_index)
		{
			m_memDC.SetTextColor(color_chord_light);
		}
		else
		{
			m_memDC.SetTextColor(color_chord);
		}
		m_memDC.DrawText(text,m_rect,DT_CALCRECT|DT_SINGLELINE);
		if (m_rect.right-m_rect.left<10) m_rect.right = m_rect.left+10;
		lce_array.set_rect(array_i,m_rect.left+pos_x-20, m_rect.top+pos_y, 
			                       m_rect.right+pos_x, m_rect.bottom+pos_y);
		
//		CRect p_rect = lce_array.get_rect(array_i);
//		m_memDC.FillRect(&p_rect,&red);
		
		m_memDC.DrawText(text,m_rect,DT_SINGLELINE);
	}
}


void CChordsLyricsEditor::set_meas_no_in_rgn(CString meas_cstr,int x,int y,COLORREF crColor, int width)
{
	m_memDC.SetTextColor(crColor);

	// Initialize a CFont object with the characteristics given
	// in a LOGFONT structure.
	memset(&lf, 0, sizeof(LOGFONT));	// clear out structure
	lf.lfHeight = (3*width/2);			// request a 25-pixel-height font
	lf.lfWidth  = width-1;				// request a width-pixel-width font							
	lf.lfWeight = FW_BOLD;					  // request a very bold weight	
	strcpy(lf.lfFaceName, "Lucida Console");  // request a face name "Lucida Console"

	hfont = ::CreateFontIndirect(&lf);  // create the font
	cfont = CFont::FromHandle(hfont);

	// Do something with the font just created...
	def_font = m_memDC.SelectObject(cfont);

	if (!m_memDC.TextOut(x, y, meas_cstr))
	{
		MessageBox("Internal Error TextOut");
		return;
	}

	m_memDC.SelectObject(def_font);

	// Done with the font. Delete the font object.
	::DeleteObject(hfont);
}

void CChordsLyricsEditor::OnMouseMove(UINT nFlags, CPoint point) 
{
	int i;
	CRect *p_rect;
	int takt, beat, tick;
	CString r;
	clicked_array_index = -1;

	if (l_button_down || l_button_paste_down)
	{
		// Cursor at the right limit of rgn? 
		if (point.x+80>=pos_x+m_w)
		{
			CPoint p;
			GetCursorPos(&p);
			act_time = compute_rgn_time(m_w+80)-(max_rel_time_in_rgn-left_time_in_rgn);
			m_rgn_slider.SetPos(act_time);
			FillRgn();
			SetCursorPos(p.x-80,p.y);
			return;
		}
		// Cursor at the left limit of rgn?
		int left_limit = pos_x + compute_rgn_x_midi_time(left_time_in_rgn)+20;
		if (left_limit < pos_x+20) left_limit = pos_x;
		if (point.x+20<=left_limit)
		{
			CPoint p;
			GetCursorPos(&p);
			act_time = compute_midi_time_from_x(point.x-60);
			m_rgn_slider.SetPos(act_time);
			FillRgn();
			SetCursorPos(rel_pos_act_time_in_rgn+p.x,p.y);
			return;
		}
	}

	if (l_button_down)
	{
		CPoint upper_left_point(point.x,point.y);
		if (rgn.PtInRegion(upper_left_point))
		{
			int array_index = -1;
			for (i=lce_array.get_length(); i>=0; i--)
			{
				p_rect = lce_array.get_rect(i);
				if (p_rect->IsRectEmpty()) continue;
				if (p_rect->PtInRect(point))
				{
					array_index = i;
					clicked_array_index = array_index;
					break;
				}
			}
			if (array_index != -1)
			{
				int dist = p_rect->right-p_rect->left;
				p_rect->left = point.x-7;
				p_rect->right = p_rect->left+dist;
				// change time
				int time = compute_midi_time_from_x(point.x);
				if (time > last_time) time = last_time;
				if (time < 0) time = 0;

				if (chord_raster_ticks!=-1)
				{
					rasterize = true;
					int check_time = lce_array.get_time(clicked_array_index) + chord_raster_ticks/2;
					int rastered_time = (check_time/chord_raster_ticks)*chord_raster_ticks;
					hpmfi->get_takt_bar_tick_from_time(rastered_time,&takt, &beat, &tick);
					r.Format("%4.4i:%2.2i:%3.3i",takt+1,beat+1,tick);
					SetDlgItemText(IDC_CHORD_POS,r);
				}
				else
				{
					rasterize = false;
				}


				lce_array.set_time(array_index,time);  
				hpmfi->get_takt_bar_tick_from_time(time,&takt, &beat, &tick);
				lce_array.set_takt_beat_tick(array_index,takt,beat,tick);
				if (!rasterize)
				{
					r.Format("%4.4i:%2.2i:%3.3i",takt+1,beat+1,tick);
					SetDlgItemText(IDC_CHORD_POS,r);
				}
				OnPaint();
			}
		}
	}

	if	(l_button_paste_down)
	{
		CPoint upper_left_point(point.x,point.y);
		if (rgn.PtInRegion(upper_left_point))
		{
			int time = compute_midi_time_from_x(point.x);
			if (time > last_time) time = last_time;
			if (time < 0) time = 0;
			hpmfi->get_takt_bar_tick_from_time(time,&takt, &beat, &tick);
			r.Format("%4.4i:%2.2i:%3.3i",takt+1,beat+1,tick);
			SetDlgItemText(IDC_CHORD_POS,r);
			OnPaint();
		}
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CChordsLyricsEditor::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if ((nFlags&MK_CONTROL)!=0)
	{
		is_lyric_insert = true;
	}
	else
	{
		is_lyric_insert = false;
	}

	if (!is_lyric_insert)
	{
		l_button_down = true;
	}
	else
	{

		if (actual_lyric_event_array_index >= lyric_event_array_len)
		{
//			actual_lyric_event_array_index = 0;
			lyric_event_text = "";
			return;
		}
		else
		{
			lyric_event_text = 	lyric_event_array[actual_lyric_event_array_index];
		}

		int takt, beat, tick;
		CString r;
		l_button_paste_down = true;
		// display time position
		CPoint upper_left_point(point.x,point.y);
		if (rgn.PtInRegion(upper_left_point))
		{
			int time = compute_midi_time_from_x(point.x);
			if (time > last_time) time = last_time;
			if (time < 0) time = 0;
			hpmfi->get_takt_bar_tick_from_time(time,&takt, &beat, &tick);
			r.Format("%4.4i:%2.2i:%3.3i",takt+1,beat+1,tick);
			SetDlgItemText(IDC_CHORD_POS,r);
			OnPaint();
		}
		SetDlgItemText(IDC_CHORD_LYRIC_SYLLABLE,"");

//		lyric_event_text = 	lyric_event_array[actual_lyric_event_array_index];

		CString shortened_text = lyric_event_text;
		if (shortened_text.GetLength()>27)
		{
			shortened_text = shortened_text.Left(26);
			shortened_text = shortened_text+"...";
		}
		
		SetDlgItemText(IDC_CHORD_LYRIC_SYLLABLE,shortened_text);
		actual_lyric_event_array_index++;
		OnPaint();
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CChordsLyricsEditor::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (!is_lyric_insert)
	{
		if (rasterize)
		{
			int takt, beat, tick;
			rasterize = false;
			int check_time = lce_array.get_time(clicked_array_index) + chord_raster_ticks/2;
			int time = (check_time/chord_raster_ticks)*chord_raster_ticks;
			lce_array.set_time(clicked_array_index,time);  
			hpmfi->get_takt_bar_tick_from_time(time,&takt, &beat, &tick);
			lce_array.set_takt_beat_tick(clicked_array_index,takt,beat,tick);
		}
		l_button_down = false;
		clicked_array_index = -1;
		SetDlgItemText(IDC_CHORD_POS,"");
		FillRgn();
	}
	else
	{
		if (actual_lyric_event_array_index >= lyric_event_array_len)
		{
//			return;
		}

		LyricChordEditElement lce_elem;	

		l_button_paste_down = false;
		int takt, beat, tick;
		unsigned char cr, ct, bn, bt;

		// set text at chord/lyric position
		int time = compute_midi_time_from_x(point.x);
		if (time > last_time) time = last_time;
		if (time < 0) time = 0;
		hpmfi->get_takt_bar_tick_from_time(time,&takt, &beat, &tick);
		SetDlgItemText(IDC_CHORD_POS,"");

		if (lyric_event_text=="")
		{
			CDialog::OnLButtonUp(nFlags, point);
			return;
		}
		
		m_chord_lyric_syllable.SetWindowText("");


		lce_elem.time = time;
		if (point.y < pos_y + m_h/2)
		{
			lce_elem.type = CHORD_TYPE;
		}
		else
		{
			lce_elem.type = LYRIC_TYPE;
		}

		lce_elem.takt = takt;
		lce_elem.beat = beat;
		lce_elem.tick = tick;

		if (lce_elem.type == CHORD_TYPE)
		{
			if (!GlobalUtilities::find_cr_ct_bn_bt(lyric_event_text, &cr, &ct, &bn, &bt))
			{
				CDialog::OnLButtonUp(nFlags, point);
				return;
			}
		}
		lce_elem.cr = cr;
		lce_elem.ct = ct;
		lce_elem.bn = bn;
		lce_elem.bt = bt;

		lce_elem.text = lyric_event_text;

		lce_array.add(&lce_elem,false);
		lce_array.sort();

		FillRgn();

		if (lyric_event_text.Right(1) == "/")
		{
			m_lyric_lines_box.DeleteString(0);
			m_lyric_lines_box.SetCurSel(0);
		}

	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CChordsLyricsEditor::OnRButtonDown(UINT nFlags, CPoint point) 
{
	int i;
	CRect *p_rect;
	CString r;
	clicked_array_index = -1;

	int end_of_line = compute_rgn_x_midi_time(last_time);
	if (end_of_line==-1) end_of_line = m_w;
	if (point.x > end_of_line+pos_x) return;
	int begin_of_line = compute_rgn_x_midi_time(0);
	if (point.x < begin_of_line+pos_x) return;

	if (rgn.PtInRegion(point))
	{
		int array_index = -1;
		for (i=lce_array.get_length(); i>=0; i--)
		{
			p_rect = lce_array.get_rect(i);
			if (p_rect->IsRectEmpty()) continue;
			if (p_rect->PtInRect(point))
			{
				array_index = i;
				clicked_array_index = array_index;
				FillRgn();
				break;
			}
		}
		if (array_index != -1)
		{
			LyricChordEditDlg dlg;
			dlg.type = lce_array.get_type(array_index);
			dlg.text = lce_array.get_text(array_index);
			dlg.last_time = last_time;
			dlg.hpmfi = hpmfi;
			lce_array.get_takt_beat_tick(array_index,&dlg.takt,&dlg.beat,&dlg.tick);
			r.Format("%4.4i:%2.2i:%3.3i",dlg.takt+1,dlg.beat+1,dlg.tick);
			SetDlgItemText(IDC_CHORD_POS,r);
			int result = dlg.DoModal();
			clicked_array_index = -1;

			if ((result==0)&&(dlg.text!=""))
			{
				if (dlg.delete_event)
				{
					lce_array.delete_elem(array_index);
				}
				else
				{
					lce_array.set_takt_beat_tick(array_index,dlg.takt, dlg.beat, dlg.tick);
					lce_array.set_text(array_index,dlg.text);
					lce_array.set_cr_ct_bn_bt(array_index,dlg.cr, dlg.ct,dlg.bn, dlg.bt);
					lce_array.set_time(array_index, 
						hpmfi->get_time_from_takt_bar_tick(dlg.takt, dlg.beat,dlg.tick));
					lce_array.sort();
				}
			}
		}
		else
		{
			// click outside any rect
			LyricChordEditDlg dlg;
			if (point.y < pos_y + m_h/2)
			{
				dlg.type = CHORD_TYPE;
			}
			else
			{
				dlg.type = (point.y < linefeed_y)?LYRIC_TYPE:LINEFEED_TYPE;
			}
			dlg.hpmfi = hpmfi;
			dlg.last_time = last_time;
			int time = compute_midi_time_from_x(point.x);
			if (time > last_time) time = last_time;
			if (time < 0) time = 0;

			if (chord_raster_ticks!=-1)
			{
				int check_time = time + chord_raster_ticks/2;
				time = (check_time/chord_raster_ticks)*chord_raster_ticks;
			}

			hpmfi->get_takt_bar_tick_from_time(time,&dlg.takt, &dlg.beat, &dlg.tick);

			r.Format("%4.4i:%2.2i:%3.3i",dlg.takt+1,dlg.beat+1,dlg.tick);
			SetDlgItemText(IDC_CHORD_POS,r);
			dlg.text = "";

			int result = dlg.DoModal();
			if ((result==0)&&(dlg.text!=""))
			{
				LyricChordEditElement lce_elem;	
				lce_elem.time = hpmfi->get_time_from_takt_bar_tick(dlg.takt, dlg.beat,dlg.tick);
				lce_elem.type = dlg.type;
				lce_elem.takt = dlg.takt;
				lce_elem.beat = dlg.beat;
				lce_elem.tick = dlg.tick;
				lce_elem.text = dlg.text;
				lce_elem.cr = dlg.cr;
				lce_elem.ct = dlg.ct;
				lce_elem.bn = dlg.bn;
				lce_elem.bt = dlg.bt;
				lce_array.add(&lce_elem,false);
				lce_array.sort();
			}
		}
	}
	SetDlgItemText(IDC_CHORD_POS,"");

	FillRgn();
	CDialog::OnRButtonDown(nFlags, point);
}

void CChordsLyricsEditor::OnRButtonUp(UINT nFlags, CPoint point) 
{
	clicked_array_index = -1;
	FillRgn();
	CDialog::OnRButtonUp(nFlags, point);
}

void CChordsLyricsEditor::OnOK() 
{
	HP_InitPlayMonitor(hpmfi->mf,NULL);
	red.DeleteObject();
	white.DeleteObject();
	
	EndDialog(0);
}

void CChordsLyricsEditor::OnCancel() 
{
	HP_InitPlayMonitor(hpmfi->mf,NULL);
	red.DeleteObject();
	white.DeleteObject();
	
	EndDialog(-1);
}

void CChordsLyricsEditor::OnCustomdrawRgnSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	act_time = m_rgn_slider.GetPos();
	int takt, bar, tick;
	hpmfi->get_takt_bar_tick_from_time(act_time, &takt, &bar, &tick);
	FillRgn();
	m_edit_play.SetFocus();
	*pResult = 0;
}


void CChordsLyricsEditor::OnCustomdrawZoomSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	double pos = (float)(m_zoom_slider.GetPos());
	double ln_max_factor_m = log(max_factor)/(double)(max_zoom/2);
	double factor = exp(pos*ln_max_factor_m)/max_factor;
	double max_rel_time_in_rgn_float = max_rel_time_in_rgn_init;
	double rel_pos_act_time_in_rgn_float = rel_pos_act_time_in_rgn_init;
	max_rel_time_in_rgn_float /= factor; 
	rel_pos_act_time_in_rgn_float /= factor;
	max_rel_time_in_rgn = (int)max_rel_time_in_rgn_float;
	rel_pos_act_time_in_rgn = (int)rel_pos_act_time_in_rgn_float;
	m_edit_play.SetFocus();
	FillRgn();
}


void CChordsLyricsEditor::OnInitZoom() 
{
	m_zoom_slider.SetPos(max_zoom/2);	
}


BOOL CChordsLyricsEditor::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	m_rgn_slider.SetFocus();
	act_time -= zDelta;
	if (act_time < 0) act_time = 0;
	if (act_time > last_time) act_time = last_time;
	m_rgn_slider.SetPos(act_time);
	FillRgn();
	int return_val = CDialog::OnMouseWheel(nFlags, zDelta, pt);
	m_rgn_slider.SetFocus();
	return return_val;
}


void CChordsLyricsEditor::OnReleasedcaptureEditSliderTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	new_edit_slider_time = m_edit_slider_time.GetPos();

	if (HP_IsPlaying(hpmfi->mf))
	{
		if (!is_pause) is_pause = hpmfi->Pause();
		is_pause = hpmfi->Pause();
		HP_SetPlayTime(hpmfi->mf,new_edit_slider_time);
		m_edit_play.SetIcon(is_pause?hIcon_play:hIcon_pause);
	}

	*pResult = 0;
}

void CChordsLyricsEditor::OnCustomdrawEditSliderTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int edit_slider_time = m_edit_slider_time.GetPos();
	if (edit_slider_time > last_time) edit_slider_time = last_time;
	int takt, bar, tick;

	hpmfi->get_takt_bar_tick_from_time(edit_slider_time, &takt, &bar, &tick);
	int new_play_time = hpmfi->get_time_from_takt_bar_tick(takt,bar,tick);
	if (new_play_time != play_time)
	{
		int middle_time = (max_rel_time_in_rgn-rel_pos_act_time_in_rgn)/2;
		CString r;
		r.Format("%4.4i:%2.2i:%3.3i",takt+1,bar+1,tick);
		SetDlgItemText(IDC_EDIT_SLIDER_POS,r);
		play_time = new_play_time;
		act_time = new_play_time<middle_time?0:new_play_time-middle_time;
		m_rgn_slider.SetPos(act_time);
		FillRgn();
	}
	m_edit_play.SetFocus();
	*pResult = 0;
}


void CChordsLyricsEditor::OnEditPlay() 
{
	if (hpmfi == NULL)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		return;
	}

	CString r;
//	logf->add("OnEditPlay");

	if (HP_IsPlaying(hpmfi->mf))
	{
		is_pause = hpmfi->Pause();
		if (is_pause)
		{
			m_edit_play.SetIcon(hIcon_play);
//			logf->add("hIcon_play");

		}
		else
		{
			m_edit_play.SetIcon(hIcon_pause);
//			logf->add("hIcon_pause");
		}
		return;
	}
	is_pause = false;
//	logf->add("Start Play");


	UINT result;

//	int edit_slider_time = m_edit_slider_time.GetPos();

	result = HP_Play(hpmfi->mf,HP_ALL);
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

//	HP_SetPlayTime(hpmfi->mf,new_edit_slider_time);


	// activate timer
	m_nTimer = SetTimer(1, 500, 0);

	set_edit_tempo();

	int takt, bar, tick;
	hpmfi->get_takt_bar_tick_from_time(new_edit_slider_time, &takt, &bar, &tick);
	int middle_time = (max_rel_time_in_rgn-rel_pos_act_time_in_rgn)/2;
	r.Format("%4.4i:%2.2i:%3.3i",takt+1,bar+1,tick);
	SetDlgItemText(IDC_EDIT_SLIDER_POS,r);
	play_time = new_edit_slider_time;
	act_time = play_time<middle_time?0:play_time-middle_time;
	m_rgn_slider.SetPos(act_time);

	FillRgn();

	m_edit_play.SetIcon(hIcon_pause);
	m_ok.EnableWindow(FALSE);
	m_cancel.EnableWindow(FALSE);
	m_edit_stop.EnableWindow(TRUE);
	m_edit_stop.SetFocus();

	HP_SetPlayTime(hpmfi->mf,new_edit_slider_time);
}

void CChordsLyricsEditor::OnEditStop() 
{
	if (hpmfi != NULL)
	{
		hpmfi->Stop();
	}
	else
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SelectSourceFirst),NULL,MB_OK|MB_TASKMODAL);
		return;
	}

	m_edit_play.SetIcon(hIcon_play);
	m_ok.EnableWindow(TRUE);
	m_cancel.EnableWindow(TRUE);
	m_edit_stop.EnableWindow(FALSE);
	m_edit_play.SetFocus();
}

void CChordsLyricsEditor::OnChangeEditSliderPos() 
{
	int i;
	CString time_cstr;
	GetDlgItemText(IDC_EDIT_SLIDER_POS,time_cstr);
	
	int takt = 0;
	int beat = 0;
	int no_colon = 0;
	char ch;

	for (i=0; i<time_cstr.GetLength(); i++)
	{
		if (no_colon==2) break;
		ch = time_cstr[i];
		if (ch == ':')
		{
			no_colon++;
			continue;
		}
		if (no_colon ==0)
		{
			takt = 10*takt + (ch-'0');
		}
		else
		{
			beat = 10*beat + (ch-'0');
		}
	}

	takt--;
	beat--;

	int new_play_time = hpmfi->get_time_from_takt_bar_tick(takt,beat,0);
	if (new_play_time != play_time)
	{
		int middle_time = (max_rel_time_in_rgn-rel_pos_act_time_in_rgn)/2;
		CString r;
		play_time = new_play_time;
		act_time = new_play_time<middle_time?0:new_play_time-middle_time;
		m_rgn_slider.SetPos(act_time);
		FillRgn();
	}
}


void MY_EDIT_PLAY_MONITOR::HP_PlayTBMonitor(int takt, int beat)
{
/*
	if ((takt<0) || (beat<0))
	{
		CString r;
		r.Format("%4.4i:%2.2i:%3.3i",1,1,0);
		SetDlgItemText(whandle,IDC_EDIT_SLIDER_POS,r);
		return;
	}
*/
	if ((takt<=0)&&(beat<=0)) return;	
	CString r;
	r.Format("%4.4i:%2.2i:%3.3i",takt+1,beat+1,0);
	SetDlgItemText(whandle,IDC_EDIT_SLIDER_POS,r);
}

void MY_EDIT_PLAY_MONITOR::HP_PlayChMonitor(char* chord_text)
{
	HP_Delete(chord_text); 
}

void MY_EDIT_PLAY_MONITOR::HP_PlayLyMonitor(char* lyric_text)
{
	HP_Delete(lyric_text); // always needed !
}


void CChordsLyricsEditor::OnTimer(UINT nIDEvent) 
{
	if (!HP_IsPlaying(hpmfi->mf))
	{	// play done
		KillTimer(m_nTimer);
		m_nTimer = NULL;
		m_edit_play.SetIcon(hIcon_play);
		m_ok.EnableWindow(TRUE);
		m_cancel.EnableWindow(TRUE);
		m_edit_stop.EnableWindow(FALSE);
		m_edit_play.SetFocus();

		int new_play_time = m_edit_slider_time.GetPos();
		int middle_time = (max_rel_time_in_rgn-rel_pos_act_time_in_rgn)/2;
		CString r;
		int takt, bar, tick;
		hpmfi->get_takt_bar_tick_from_time(new_play_time, &takt, &bar, &tick);
		r.Format("%4.4i:%2.2i:%3.3i",takt+1,bar+1,tick);
		SetDlgItemText(IDC_EDIT_SLIDER_POS,r);
		play_time = new_play_time;
		act_time = new_play_time<middle_time?0:new_play_time-middle_time;
		m_rgn_slider.SetPos(act_time);
		FillRgn();
	}
	CDialog::OnTimer(nIDEvent);
}

void CChordsLyricsEditor::OnEditDefaultTempo() 
{
	m_edit_slider_tempo.SetPos(10);
	set_edit_tempo();	
}

void CChordsLyricsEditor::OnCustomdrawEditSliderTempo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int nTempo=m_edit_slider_tempo.GetPos()*10;
	CString r;
	r.Format("%i%%",nTempo);
	SetDlgItemText(IDC_EDIT_TEMPO_DISPLAY,r);
	m_edit_play.SetFocus();
	*pResult = 0;
}

void CChordsLyricsEditor::OnReleasedcaptureEditSliderTempo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	set_edit_tempo();
	*pResult = 0;
}

void CChordsLyricsEditor::set_edit_tempo() 
{
	int nTempo=m_edit_slider_tempo.GetPos()*10;
	CString r;
	r.Format("%i%%",nTempo);
	SetDlgItemText(IDC_EDIT_TEMPO_DISPLAY,r);
	HP_PlayTempo(hpmfi->mf,nTempo);		
}

void CChordsLyricsEditor::OnSelchangeChordRasterCombo() 
{
	int raster_ticks[5] = {-1,480,240,120,60};
	int index = m_chord_raster_combo.GetCurSel();
	chord_raster_ticks = raster_ticks[index];
}

// Record Lyrics


void CChordsLyricsEditor::OnStartRecord() 
{
	if (!load_lyric_file()) 
	{
		return;
	}

	UpdateWindow();
}

bool CChordsLyricsEditor::load_lyric_file()
{
	// Load Lyric File and check
	
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
		lyric_file = openfile_dlg.m_ofn.lpstrFile;
	}
	else 
	{
		if (return_value == IDCANCEL)
		{
			// Error open record File
			return false;
		}
	}

	// Try lyric_file

	CFile mf_newf;
	CFileException e;

	if (mf_newf.Open(lyric_file, CFile::modeRead,&e))
	{
		int length = mf_newf.GetLength();

		if (length==0)
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_FILE_EMPTY),NULL,MB_OK|MB_TASKMODAL);
			mf_newf.Close();
			// empty record file
			return false;
		}
	}
	else
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_NO_ACCESS_TO_FILE),NULL,MB_OK|MB_TASKMODAL);
		// error open Record file
		return false;
	}
	mf_newf.Close();
	return true;
}


bool CChordsLyricsEditor::fill_lyric_list()
{
	if (lyric_file=="")
	{
//		MessageBox("Load Lyric File before");
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_SELECT_LYRIC_FILE_BEFORE),NULL,MB_OK|MB_TASKMODAL);

		
		m_select_lyric_lines.SetCheck(false);
		m_select_words.SetCheck(false);
		return (false);
	}

	m_lyric_lines_box.ResetContent();

	record_lyric_length = 0;
	lyric_event_array_len = 0;			
	actual_lyric_event_array_index = 0;

	CStdioFile *cf_f = new CStdioFile;
	if (!cf_f->Open(lyric_file, CFile::shareExclusive | CFile::modeRead | CFile::typeText, &e))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_FILE_MISSED),NULL,MB_OK|MB_TASKMODAL);
		delete cf_f;
		cf_f = NULL;
		return false; // file does not exist
    }

	line_number = 0;
	list_number = 0;

	CString line;
	is_lyric_record = false;

	while (true)
	{
		if (!cf_f->ReadString(line)) 
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_NO_START_LYRICLIST),NULL,MB_OK|MB_TASKMODAL);
			cf_f->Close();		
			delete cf_f;
			cf_f = NULL;
			return false;
		}

		line.TrimRight();

		CString line1 = line;
//		line1.TrimRight();

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
		int i;

		if (!cf_f->ReadString(line)) 
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_NO_END_LIST),NULL,MB_OK|MB_TASKMODAL);
			cf_f->Close();		
			delete cf_f;
			cf_f = NULL;
			// error record file
			return false;
		}
		if (list_number >= NO_CHORDS_LYRICS)
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd,GlobalUtilities::get_resource_string(IDS_OVERFLOW_LYRICS),NULL,MB_OK|MB_TASKMODAL);
			cf_f->Close();		
			delete cf_f;
			cf_f = NULL;
			return false;
		}
		line.TrimRight();
		
		// exchange '_' by ' ' of lyrictest files
		for (i=0; i<line.GetLength(); i++)
		{
			if (line[i]=='_')
			{
				line.SetAt(i,' ');
			}
		}

		if (line == GlobalUtilities::end_list)
		{
			break;
		}

		if (is_lyric_record)
		{
			if (!lyricline_check_and_add_words_in_list(line))
			{
				// error check and add in list
				cf_f->Close();		
				delete cf_f;
				cf_f = NULL;
				return false;
			}
		}
	}

	if(m_select_words.GetCheck())
	{
		int i;
		for(i=0; i<record_lyric_length;i++)
		{
			lyric_event_array[i] = record_chord_lyric_list[i].text;
			lyric_event_array_len++;
// Test: nur words
		CString r;
		r.Format("words: lyric_event_array %i, [%s]", i, lyric_event_array[i]);
//		MessageBox(r);
		}
	}

	
	int no_lines = line_number;		  // no of relevant textlines of lyrics
	int no_list_numbers = list_number; // no of words for recording,

	cf_f->Close();
	delete cf_f;
	cf_f = NULL;

	if (record_lyric_length > 0)
	{	// Display text
//		SetDlgItemText(IDC_ACTUAL_LYRIC_CHORD,"");
		o_inifile->set_recordfile(lyric_file);
		signal_record_text = true;
		return true;
	}
	else
	{
		return false;
	}
}


bool CChordsLyricsEditor::lyricline_check_and_add_words_in_list(CString line)
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
		if (char_no >= line.GetLength())
		{ 
			lyrictxt += "/";
		}
		record_chord_lyric_list[list_number].text = lyrictxt;
		record_chord_lyric_list[list_number].time = -1;
		list_number++;
		record_lyric_length++;
		if (char_no >= line.GetLength()) break;
	}
	// end of line
	lyric_list[line_number] = line;

	if(m_select_lyric_lines.GetCheck())
	{
		for (int i=0; i<lyric_list[line_number].GetLength(); i++)
		{   // '-' no need in Editor for lines
			if (lyric_list[line_number].GetAt(i)=='-')
			{
				lyric_list[line_number].Delete(i);
			}
		}
		
		lyric_event_array[line_number] = lyric_list[line_number];
		lyric_event_array[line_number]+="/";
		lyric_event_array_len++;

// Test:nur lines
		CString r;
		r.Format("lines: lyric_event_array line_number %i, [%s]", line_number, lyric_event_array[line_number]);
//		MessageBox(r);
	}

	m_lyric_lines_box.InsertString(line_number,lyric_list[line_number]);
	m_lyric_lines_box.SetCurSel(0);
		
	line_number++;
	last_ch = (char)0;
	next_ch = (char)0;
	return true;
}

void CChordsLyricsEditor::OnSelectLyricLines() 
{
	if (m_select_lyric_lines.GetCheck())
	{
		m_select_lyric_lines.SetCheck(true);
		m_select_words.SetCheck(false);
	}
	else
	{
		m_select_lyric_lines.SetCheck(false);
		m_select_words.SetCheck(true);
	}

	fill_lyric_list();
}

void CChordsLyricsEditor::OnSelectWordsSyllables() 
{
	if (m_select_words.GetCheck())
	{
		m_select_lyric_lines.SetCheck(false);
		m_select_words.SetCheck(true);
	}
	else
	{
		m_select_lyric_lines.SetCheck(true);
		m_select_words.SetCheck(false);
	}
	fill_lyric_list();
}

