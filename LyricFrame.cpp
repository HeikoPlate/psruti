/*
Module : LyricFrame.cpp
Purpose: Defines the code implementation for the LyricFrame class
*/

#include "stdafx.h"
#include "LyricFrame.h"
#include "GlobalUtilities.h"
#include "resource.h"

const int LyricFrame::char_width_lyric = 16;
const int LyricFrame::char_width_chord = 12;
const COLORREF LyricFrame::color_lyric = RGB(128,128,128);
const COLORREF LyricFrame::color_chord = RGB(192,96,96);
const COLORREF LyricFrame::color_lyric_light = RGB(255,255,255);
const COLORREF LyricFrame::color_chord_light = RGB(255,180,180);

// The constructor of the class
LyricFrame::LyricFrame()
{
	no_lyric_lines = 0;
	pdc = NULL;
//	lyricframelist = new LYRICFRAME_ELEM[NO_LIST_LINES][NO_LYRICS_LINE];

}

// Destroy the GDI objects
LyricFrame::~LyricFrame()
{
	m_bmp.DeleteObject();
	m_bkbrush.DeleteObject();

	if (pdc != NULL)
	{
		delete pdc;
		pdc = NULL;
	}
}

// Initialize the display from a rectangle coordinates
// Asociate to it a memory bitmap
// Show the display in black background
LyricFrame::InitDisplay(CWnd *Wnd,int xp,int yp,int wp,int hp)
{
	wnd = Wnd;
	m_x=xp;
	m_y=yp;
	m_w=wp;
	m_h=hp;

	pdc = new CClientDC(Wnd);
	m_memDC.CreateCompatibleDC(pdc);
	m_bmp.CreateCompatibleBitmap(pdc,m_w,m_h);
	
	
	m_memDC.SelectObject(&m_bmp);
	m_bkbrush.CreateStockObject(BLACK_BRUSH);
	m_memDC.SelectObject(&m_bkbrush);
	m_memDC.PatBlt(0,0,m_w,m_h,PATCOPY);
	m_memDC.SetBkColor(RGB(0,0,0));
}

int LyricFrame::ly_of_line(int line)
{
	return 40+line*60;
}

int LyricFrame::cy_of_line(int line)
{
	return 19+line*60;
}

void LyricFrame::blit()
{
	pdc->BitBlt(m_x, m_y, m_w, m_h, &m_memDC, 0,0, SRCCOPY);
}


void LyricFrame::display_title(char* songname, char* copyrightname, char* composername, char* lyricistname)
{
	int max_chars_line;
    int no_chars_name;
	char *new_name;
	int x, y;
	int i;
	int line_number = 1;
	
	max_chars_line = m_w/char_width_lyric;
	no_chars_name = strlen(songname);
	new_name = new char[no_chars_name+1];
	strcpy(new_name, songname);

	if (no_chars_name > max_chars_line-1)
	{
		new_name[max_chars_line-4] = '.';
		new_name[max_chars_line-3] = '.';
		new_name[max_chars_line-2] = '.';
		new_name[max_chars_line-1] = 0x00;
		no_chars_name = strlen(new_name);
	}

	x = (m_w-char_width_lyric*no_chars_name)/2;
	y = ly_of_line(line_number);
	line_number++;
	
	SetText(new_name,x,y,color_chord_light,char_width_lyric, true);

	delete[] new_name;

	if (strlen(lyricistname)!=0)
	{
		char lyricist_text[80];
		strcpy(lyricist_text,GlobalUtilities::get_resource_string(IDS_LYRICIST));
		strcat(lyricist_text,"  ");
		strcat(lyricist_text,lyricistname);
		no_chars_name = strlen(lyricist_text);

		x = (m_w-char_width_chord*no_chars_name)/2;
		y = ly_of_line(line_number);
		line_number++;
		
		SetText(lyricist_text,x,y,color_chord_light,char_width_chord, false);
	}

	if (strlen(composername)!=0)
	{
		char composer_text[80];
		strcpy(composer_text,GlobalUtilities::get_resource_string(IDS_COMPOSER));
		strcat(composer_text,"  ");
		strcat(composer_text,composername);
		no_chars_name = strlen(composer_text);

		x = (m_w-char_width_chord*no_chars_name)/2;
		y = ly_of_line(line_number);
		line_number++;
		SetText(composer_text,x,y,color_chord_light,char_width_chord, false);
	}

	if (strlen(copyrightname)!=0)
	{
		max_chars_line = m_w/char_width_chord;
		no_chars_name = strlen(copyrightname);
		new_name = new char[no_chars_name+1];
		strcpy(new_name, copyrightname);

		for (i=0; i<(int)strlen(new_name); i++)
		{
			if (new_name[i] == (char)0x0d) new_name[i] = ' ';
		}

		if (no_chars_name > max_chars_line-1)
		{
			new_name[max_chars_line-4] = '.';
			new_name[max_chars_line-3] = '.';
			new_name[max_chars_line-2] = '.';
			new_name[max_chars_line-1] = 0x00;
			no_chars_name = strlen(new_name);
		}

		x = (m_w-char_width_chord*no_chars_name)/2;
		y = ly_of_line(line_number);
		line_number++;
	
		SetText(new_name,x,y,color_chord_light,char_width_chord, false);
		delete[] new_name;
	}

	blit();
}

void LyricFrame::posit_time(int new_time)
{
	if (no_lyric_lines <= 0) return;
	
	int i, k;
	int scr_time;
	int old_time = lyricframelist[l_no][syll_no].time;

	for (i=0; i<NO_LIST_LINES; i++)
	{
		for (k=0; k<NO_LYRICS_LINE; k++)
		{
			scr_time = lyricframelist[i][k].time;
			if (scr_time==-1) break; // end of i
			if ((k==0)&&(i==0)&&(scr_time>=new_time))
			{
				initialize_first_frame(0,0);
				return;
			}
			if (scr_time >= new_time)
			{
				initialize_first_frame(i,k);
				return;
			}
		}
	}
}


void LyricFrame::initialize_first_frame(int lineno, int syllno)
{
	int i,k;
	int time;
	int cwl = char_width_lyric; // the width of one displayed char (pixel) of lyric
	int cwc = char_width_chord; // the width of one displayed char (pixel) of chord
	
	//
	// initialize lyricframelist for playing
	//
	
	for (i=0; i<NO_LIST_LINES; i++)
	{
		for (k=0; k<NO_LYRICS_LINE; k++)
		{
			if (lyricframelist[i][k].time == -1)
			{
				lyricframelist[i][k].l_printed = true;
				lyricframelist[i][k].c_printed = true;
			}
			else
			{
				char* chord = lyricframelist[i][k].chord;
				char* lyric = lyricframelist[i][k].lyric;
				lyricframelist[i][k].l_printed = (strcmp(lyric,"")==0)?true:false;
				lyricframelist[i][k].c_printed = (strcmp(chord,"")==0)?true:false;
			}
		}
	}
	
	l_no = lineno;		// actual line-number when playing
	syll_no = syllno;	// actual syllable number when playing
	
	
	last_lightened_lyric = NULL;
	last_lightened_lyric_line = -1;
	last_lightened_lyric_x = -1;
	
	last_lightened_chord = NULL;
	last_lightened_chord_line = -1;
	last_lightened_chord_x = -1;
	
	EraseRegion();
	
	// display the first lyric-lines
	
	if (no_lyric_lines > 0)
	{
		for (i=lineno; (i<NO_FRAME_LINES+lineno)&&(i<no_lyric_lines); i++)
		{
			for (k=0; k<NO_LYRICS_LINE; k++)
			{
				time = lyricframelist[i][k].time;
				if (time==-1) break; // end of i
				
				SetText(lyricframelist[i][k].chord,
					lyricframelist[i][k].x,cy_of_line(i-lineno),color_chord,cwc, false);
				SetText(lyricframelist[i][k].lyric,
					lyricframelist[i][k].x,ly_of_line(i-lineno),color_lyric,cwl, false);
			}
			line_map[i]=i-lineno;
		}
	}
	blit();
}

void LyricFrame::display_next_frame()
{
	int i, k;
	int time;

	EraseRegion();

	for (i=l_no-FRAME_LINE_SWITCH; (i<l_no) && (i>=0); i++)
	{
		line_map[i] = -1;
	}

	for (i=l_no; (i<l_no+NO_FRAME_LINES); i++)
	{
		if (i<no_lyric_lines)
		{
			line_map[i] = i-l_no;
		}
		else
		{
			line_map[i] = -1;
		}
	}
	if (no_lyric_lines > 0)
	{
		for (i=l_no; i<l_no+NO_FRAME_LINES; i++)
		{
			for (k=0; k<NO_LYRICS_LINE; k++)
			{
				time = lyricframelist[i][k].time;
				if (time==-1) break; // end of i

				SetText(lyricframelist[i][k].chord,
				   lyricframelist[i][k].x,cy_of_line(line_map[i]),color_chord,char_width_chord,false);
				SetText(lyricframelist[i][k].lyric,
				   lyricframelist[i][k].x,ly_of_line(line_map[i]),color_lyric,char_width_lyric,false);
			}
		}
	}
	blit();
}

// callback functions, initiated by MY_PLAY_MONITOR
void LyricFrame::display_next_lyric(char* lyric)
{
	int fr_line;

	if (lyricframelist[l_no][syll_no].l_printed)
	{
		syll_no++;
		if (lyricframelist[l_no][syll_no].time==-1)
		{
			l_no++;
			syll_no = 0;
		}
	}

	fr_line = line_map[l_no];
	if (fr_line == FRAME_LINE_SWITCH)
	{
		display_next_frame();
	}

	fr_line = line_map[last_lightened_lyric_line];

	// restore color of last lightened lyric
	if (last_lightened_lyric != NULL)
	{
		if (fr_line==-1)
		{
			last_lightened_lyric = NULL;
		}
		else
		{
			if (last_lightened_lyric[0] != 0x00)
			{
				SetText(last_lightened_lyric, last_lightened_lyric_x,
					ly_of_line(line_map[last_lightened_lyric_line]),
					color_lyric,char_width_lyric, false);
			}
		}
	}

    // lighten lyric

	SetText(lyricframelist[l_no][syll_no].lyric,
			lyricframelist[l_no][syll_no].x,ly_of_line(line_map[l_no]),
			color_lyric_light,char_width_lyric, false);

	last_lightened_lyric = lyricframelist[l_no][syll_no].lyric;
	last_lightened_lyric_line = l_no;
	last_lightened_lyric_x = lyricframelist[l_no][syll_no].x,

	lyricframelist[l_no][syll_no].l_printed = true;

	blit();
}

void LyricFrame::display_next_chord(char* chord)
{
//	logf->add("chord line %i \"%s\"",l_no,chord);
	
	int fr_line;

	while (lyricframelist[l_no][syll_no].c_printed)
	{
		syll_no++;

		if (syll_no>=NO_LYRICS_LINE)
		{
			l_no++;
			syll_no = 0;
		} 
		
		else
		
		if (lyricframelist[l_no][syll_no].time==-1)
		{
			l_no++;
			syll_no = 0;
		}
	}

	fr_line = line_map[l_no];
	if (fr_line == FRAME_LINE_SWITCH)
	{
		display_next_frame();
	}
	
	fr_line = line_map[last_lightened_chord_line];

	// restore color of last lightened chord
	if ((last_lightened_chord!=NULL)&&(last_lightened_chord_line>=0))
	{
		if (fr_line == -1)
		{
			last_lightened_chord = NULL;
		}
		else
		{
			if (last_lightened_chord[0]!=0x00)
			{
				SetText(last_lightened_chord,last_lightened_chord_x,
					cy_of_line(line_map[last_lightened_chord_line]),
					color_chord,char_width_chord, false);
			}
		}
	}

    // lighten chord
	
	SetText(lyricframelist[l_no][syll_no].chord,
			lyricframelist[l_no][syll_no].x,cy_of_line(line_map[l_no]),
			color_chord_light,char_width_chord, false);

	last_lightened_chord = lyricframelist[l_no][syll_no].chord;
	last_lightened_chord_line = l_no;
	last_lightened_chord_x = lyricframelist[l_no][syll_no].x,

	lyricframelist[l_no][syll_no].c_printed = true;

	blit();
}


// Member function to put text on the display
LyricFrame::SetText(CString strText,int x,int y,COLORREF crColor, int width, bool with_bitblt)
{
	CRect rect;
	rect.left=x;
	rect.top=y;

	m_memDC.SetTextColor(crColor);

	// Initialize a CFont object with the characteristics given
	// in a LOGFONT structure.

	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));	// clear out structure
	lf.lfHeight = (3*width/2);			// request a 25-pixel-height font
	lf.lfWidth  = width-1;				// request a width-pixel-width font							
	lf.lfWeight = FW_BOLD;					  // request a very bold weight	
	strcpy(lf.lfFaceName, "Lucida Console");  // request a face name "Lucida Console"

	HFONT hfont = ::CreateFontIndirect(&lf);  // create the font
	CFont* cfont = CFont::FromHandle(hfont);

	// Do something with the font just created...
	CFont* def_font = m_memDC.SelectObject(cfont);

	m_memDC.DrawText(strText,&rect,DT_CALCRECT|DT_SINGLELINE);


	rect.left+=m_x;
	rect.top+=m_y;
	rect.bottom+=m_y;
	rect.right+=m_x;

	m_memDC.TextOut(x, y, strText);

	m_memDC.SelectObject(def_font);

	// Done with the font. Delete the font object.
	::DeleteObject(hfont);

	if (with_bitblt)
	{
		blit();
	}
}


// Member function to erase text on the display
LyricFrame::EraseText(CString strText,int x,int y, int width)
{
	SetText(strText,x,y,RGB(0,0,0),width, true);
}

LyricFrame::EraseRegion()
{
	CRect rect;
	rect.left=0;
	rect.top=0;
	rect.bottom=m_y+m_h;
	rect.right=m_x+m_w;
	m_memDC.FillSolidRect(&rect,RGB(0,0,0));
}

void LyricFrame::print(CString protfile, bool show, bool with_xfchords)
{
	// initialize protfile
	
	CStdioFile *pf_f;
	CFileException e;
	CString t;
	
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
	
	// fill the file with chords and lyrics

	int i, k, l;

	// Write title
	pf_f->WriteString(songname+"\n\n");

	CString chordline = "";
	CString lyricline = "";
	for (l=0; l<80; l++)
	{
		chordline+=" ";
		lyricline+=" ";
	}

	if (no_lyric_lines > 0)
	{
		for (i=0; i<no_lyric_lines; i++)
		{
			for (k=0; k<NO_LYRICS_LINE; k++)
			{
				if (k==NO_LYRICS_LINE-1) 
				{
					chordline.TrimRight();
					lyricline.TrimRight();
					if (with_xfchords)
					{
						pf_f->WriteString(chordline+"\n");
						pf_f->WriteString(lyricline+"\n\n");
					}
					else
					{
						pf_f->WriteString(lyricline+"\n");
					}

					chordline = "";
					lyricline = "";
					for (l=0; l<80; l++)
					{
						chordline+=" ";
						lyricline+=" ";
					}
					break;
				}

				// insert chord/lyric in chord/lyricline
				if (lyricframelist[i][k].chord!=NULL)
				{
					chordline.Insert(lyricframelist[i][k].char_pos,lyricframelist[i][k].chord);					
				}
				
				if (lyricframelist[i][k].lyric!=NULL)
				{
					lyricline.Insert(lyricframelist[i][k].char_pos,lyricframelist[i][k].lyric);
				}
			}
		}
	}

	//
	pf_f->Close();

	for (i=0; i<no_lyric_lines; i++)
	{
		for (k=0; k<NO_LYRICS_LINE;k++)
		{
			if (lyricframelist[i][k].lyric != NULL) 
				delete[] lyricframelist[i][k].lyric;
			if (lyricframelist[i][k].chord != NULL) 
				delete[] lyricframelist[i][k].chord;
		}
	}

	if (show) ShellExecute(NULL,"open",protfile,NULL,NULL,SW_SHOWNORMAL);
}
