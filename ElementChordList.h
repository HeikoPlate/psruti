// ElementChordList.h
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#if !defined(ELEMENTCHORDLIST_H__76FC731D_5B92_414A_9B89_7B1C26949F11__INCLUDED_)
#define ELEMENTCHORDLIST_H__76FC731D_5B92_414A_9B89_7B1C26949F11__INCLUDED_

class ElementChordList
{
public:
	int time;
	int takt;
	int beat; 
	int tick;
	int num;
	int ticks_per_beat;
	unsigned char cr;
	unsigned char ct;
	unsigned char bn;
	unsigned char bt;
	bool is_sysex;
	unsigned char data[9];
};

#endif