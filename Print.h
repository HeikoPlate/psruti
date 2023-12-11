#if !defined(AFX_PRINT_H__EE151570_C593_45B6_918F_D217866FE7D3__INCLUDED_)
#define AFX_PRINT_H__EE151570_C593_45B6_918F_D217866FE7D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Print.h : Header-Datei
//

#include "HPMF_Interface.h"
#include "Play.h"
#include "LyricFrame.h"

class CPrint : public CDialog
{

public:
	CPrint(HPMF_Interface *hpmf);
	virtual ~CPrint();
	void print(CString protfile, bool show);

	HPMF_Interface *hpmfi;
	CPlay *pdlg;

protected:
};

#endif // AFX_PRINT_H__EE151570_C593_45B6_918F_D217866FE7D3__INCLUDED_
