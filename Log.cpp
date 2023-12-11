// Log.cpp: Implementierung der Klasse Log.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Log.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Log::Log()
{
	lf = NULL;
}


Log::Log(CString logfile)
{
	lf = NULL;
	#ifdef HP_LOG

	CString t;
	
	CFileStatus status;
/*
	// Find path for log-file in .exe folder
	int i;
	char full_logfile[255];
	GetModuleFileName( GetModuleHandle( NULL ), full_logfile, sizeof( full_logfile ) );   
	for( i = strlen( full_logfile ) - 1; i > 0; i-- ) 
	{     
		if( full_logfile[i] == '\\' ) 
		{       
			full_logfile[i] = '\0';       
			break;     
		}   
	}
	strcat(full_logfile,"\\");
	lfile = full_logfile;
	lfile += logfile;
*/

	// Find path for logfile in documents

	char path[MAX_PATH];
	SHGetSpecialFolderPath(NULL, path, CSIDL_PERSONAL, FALSE);
	strcat(path,"\\");
	lfile = path;
	lfile += logfile;

	CString r;
	r.Format("logfile path %s",lfile);
	MessageBox(r);

	if (CFile::GetStatus( lfile,status))
	{
		CFile::Remove(lfile);
	}

	lf = new CStdioFile;
	if (!lf->Open(lfile, CFile::modeCreate | CFile::modeNoTruncate | 
		                     CFile::modeReadWrite | CFile::shareExclusive, &e))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,"Logfile could not be opened",NULL,MB_OK|MB_TASKMODAL);
		lf = NULL;
		return;
    }
//	lf->SetLength(0);
	lf->SeekToEnd();

	t.Format("PSRUTI LogFile");
	lf->WriteString(t);
	lf->WriteString("\n\n");
	lf->Close();
	delete lf;
	lf = NULL;

	#endif
}

void Log::add(const char* fmt,...)
{
	#ifdef HP_LOG
	lf = new CStdioFile;
	if (!lf->Open(lfile, CFile::modeWrite, &e))
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd,"Logfile could not be opened",NULL,MB_OK|MB_TASKMODAL);
        TCHAR szError[1024];
        e.GetErrorMessage(szError, 1024);
	    CString r;
		r.Format("%s",szError);
		MessageBox(r);
 	    lf = NULL;
		return;
	}

	char buffer[256];

	lf->SeekToEnd();

	va_list args;
	va_start(args, fmt);
	_vsnprintf(buffer,255, fmt,args);
	va_end(args);

	lf->WriteString(buffer);
	lf->WriteString("\n");
	lf->Close();
	delete lf;
	lf = NULL;
	#endif
}

Log::~Log()
{
	#ifdef HP_LOG
	if (lf != NULL) lf->Close();
	lf = NULL;
	#endif
}
