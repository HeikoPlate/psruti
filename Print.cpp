// Print.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Print.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrint

CPrint::CPrint(HPMF_Interface *hpmf)
{
	hpmfi = hpmf;

	pdlg = new CPlay;
	pdlg->hpmfi = hpmfi;
	pdlg->mf = hpmfi->mf;
	pdlg->with_lyrics = hpmfi->with_lyrics;
	pdlg->prepare_lyrics_chords();
}

CPrint::~CPrint()
{
	delete pdlg;
	pdlg = NULL;
}

void CPrint::print(CString protfile, bool show)
{
	pdlg->print(protfile, show);
}


