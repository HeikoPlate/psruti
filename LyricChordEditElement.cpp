// LyricChordEditElement.cpp: Implementierung der Klasse LyricChordEditElement.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "LyricChordEditElement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

LyricChordEditElement::LyricChordEditElement()
{
	rect.SetRectEmpty();
	cr = 0;
	ct = 0;
	bn = 0;
	bt = 0;
}

LyricChordEditElement::~LyricChordEditElement()
{

}
