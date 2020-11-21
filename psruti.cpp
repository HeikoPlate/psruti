// psruti.cpp : Legt das Klassenverhalten für die Anwendung fest.
//

#include "stdafx.h"
#include "psruti.h"
#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// next statement in comment, if language dll's not to be used
#define WITH_DLL_RESOURCES

/////////////////////////////////////////////////////////////////////////////
// CPsrutiApp

BEGIN_MESSAGE_MAP(CPsrutiApp, CWinApp)
	//{{AFX_MSG_MAP(CPsrutiApp)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPsrutiApp Konstruktion

CPsrutiApp::CPsrutiApp()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
	language = "";
}

void CPsrutiApp::OnHelp()
{

	CString hlpfile =
		(language=="GERMAN")?"psruti_germ.hlp":(language=="ENGLISH")?"psruti_eng.hlp":"";
	if (hlpfile != "")
	{
		ShellExecute(NULL,"open",hlpfile,NULL,NULL,SW_SHOWNORMAL);

	}
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CPsrutiApp-Objekt




CPsrutiApp theApp;


HINSTANCE hlanguage_dll;	//Global var


/////////////////////////////////////////////////////////////////////////////
// CPsrutiApp Initialisierung

BOOL CPsrutiApp::InitInstance()
{
	// OLE-Bibliotheken initialisieren
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Größe Ihrer fertigen 
	//  ausführbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht benötigen, entfernen.

#ifdef _AFXDLL
	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
#else
	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
#endif

	// Befehlszeile parsen, um festzustellen, ob Ausführung als OLE-Server erfolgt
	if (RunEmbedded() || RunAutomated())
	{
		// Alle OLE-Server (-fabriken) als aktiv registrieren. Dies aktiviert die
		//  OLE-Bibliotheken, um Objekte von anderen Anwendungen zu erstellen.
		COleTemplateServer::RegisterAll();
	}
	else
	{
		// Wird eine Server-Anwendung im Standalone-Modus betrieben, ist es ratsam,
		//  die Systemregistrierung zu aktualisieren, falls diese beschädigt wurde.
		COleObjectFactory::UpdateRegistryAll();
	}

	// DialogBox light blue:
	SetDialogBkColor( RGB(160, 192, 192), RGB(0, 0, 0) );
	char prog_path[255];


	// Set Language
	{
		IniFile *o_inifile;
		o_inifile = new IniFile;
		
		language = o_inifile->get_language();
		
		delete o_inifile;
		o_inifile = NULL;

		CString dll_long_name;
		char dll_path[255];

		// Find path for dll Files		
		int i;
		GetModuleFileName( GetModuleHandle(NULL), prog_path, sizeof(prog_path));
		strcpy(dll_path,prog_path);
		for( i = strlen(dll_path)-1; i>0; i--) 
		{     
			if(dll_path[i] == '\\') 
			{       
				dll_path[i] = '\0';       
				break;     
			}   
		}
		strcat(dll_path,"\\");
		dll_long_name = dll_path;

		if (language=="ENGLISH")
		{
			dll_long_name += "psruti_res_eng.dll";
		}
		else
		{
			if (language=="GERMAN")
			{
				dll_long_name += "psruti_res_germ.dll";
			}
			else
			{
				dll_long_name += "psruti_res_eng.dll";
			}
		}

		hlanguage_dll = AfxLoadLibrary(dll_long_name);

#ifdef WITH_DLL_RESOURCES
		//	the next two statements activate the language dll's
		ASSERT(hlanguage_dll);
		AfxSetResourceHandle(hlanguage_dll);
#endif
	}

	// Prepare Dialog

	CPsrutiDlg *dlg = new CPsrutiDlg;
	
	m_pMainWnd = dlg;

	// start by commandline (drag&drop) ?
	if (m_lpCmdLine[0] != _T('\0'))
    {
		dlg->command_line = m_lpCmdLine;
    }
    else
    {
		strcpy(dlg->sourcefile,"");
	}


	dlg->language = language;
	int nResponse = dlg->DoModal();
	if ((nResponse == IDOK) || nResponse == IDCANCEL)
	{
		// ZU ERLEDIGEN: Fügen Sie hier Code ein, um ein Schließen des
		//  Dialogfelds über OK zu steuern
	}
	else if (nResponse == IDNEWSTART)
	{
		// ZU ERLEDIGEN: Fügen Sie hier Code ein, um ein Schließen des
		//  Dialogfelds über "Abbrechen" zu steuern
		 delete dlg;
		 dlg = NULL;
	     _execl( prog_path, NULL );
		 return FALSE;
 
	}
	delete dlg;
	dlg = NULL;

	// Da das Dialogfeld geschlossen wurde, FALSE zurückliefern, so dass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.
	return FALSE;
}

