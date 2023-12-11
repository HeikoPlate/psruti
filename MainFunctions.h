// MainFunctions.h: Schnittstelle für die Klasse MainFunctions.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFUNCTIONS_H__76FC731D_5B92_414A_9B89_7B1C26949F11__INCLUDED_)
#define AFX_MAINFUNCTIONS_H__76FC731D_5B92_414A_9B89_7B1C26949F11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MainFunctions  
{
public:
	virtual void Stop() = 0;
	virtual void save_state() = 0;		// save hpmfi to hpmfi_save
	virtual void analyse_changes() = 0;
	virtual HPMF_Interface* Selectsource() = 0;
};

#endif // !defined(AFX_MAINFUNCTIONS_H__76FC731D_5B92_414A_9B89_7B1C26949F11__INCLUDED_)
