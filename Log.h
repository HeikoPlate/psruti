// Log.h: Schnittstelle für die Klasse Log.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__0DBEF418_82A8_4BE8_B200_D34A21DAADDB__INCLUDED_)
#define AFX_LOG_H__0DBEF418_82A8_4BE8_B200_D34A21DAADDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//
// Standard Includes
//
#include <afx.h>
#include <afxtempl.h>
#include <stdlib.h>
#include <search.h>


class Log: public CDialog    
{
public:
	Log();
	Log(CString logfile);
	void Log::add(const char* fmt,...);
	virtual ~Log();
	CFileException e;
private:
	CStdioFile *lf;
	CString lfile;
};

#endif // !defined(AFX_LOG_H__0DBEF418_82A8_4BE8_B200_D34A21DAADDB__INCLUDED_)
