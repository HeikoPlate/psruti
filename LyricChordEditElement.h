// LyricChordEditElement.h: Schnittstelle für die Klasse LyricChordEditElement.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LYRICCHORDEDITELEMENT_H__C614C3CF_52BD_42DC_8806_A6FEAAEC4D50__INCLUDED_)
#define AFX_LYRICCHORDEDITELEMENT_H__C614C3CF_52BD_42DC_8806_A6FEAAEC4D50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

#define LYRIC_TYPE 1
#define LINEFEED_TYPE 2
#define NEWPAGE_TYPE 3
#define CHORD_TYPE 4
#define TAKT_TYPE  5
#define BEAT_TYPE  6

class LyricChordEditElement  
{
public:
	LyricChordEditElement();
	virtual ~LyricChordEditElement();
	int type; // LYRIC_TYPE, CHORD_TYPE or TAKT_TYPE
	int time; // event time
	int	takt;
	int beat;
	int tick;
	unsigned char cr;
	unsigned char ct;
	unsigned char bn;
	unsigned char bt;
	CString text;
	CRect rect;
};

#endif // !defined(AFX_LYRICCHORDEDITELEMENT_H__C614C3CF_52BD_42DC_8806_A6FEAAEC4D50__INCLUDED_)
