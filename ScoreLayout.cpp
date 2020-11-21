// ScoreLayout.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "ScoreLayout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld ScoreLayout 


ScoreLayout::ScoreLayout(CWnd* pParent /*=NULL*/)
	: CDialog(ScoreLayout::IDD, pParent)
{
	//{{AFX_DATA_INIT(ScoreLayout)
	//}}AFX_DATA_INIT
}


void ScoreLayout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ScoreLayout)
	DDX_Control(pDX, IDC_SIZECOMBOBOX, m_sizecombo);
	DDX_Control(pDX, IDC_QUANTIZETRIOLECOMBO, m_quantizetriolecombo);
	DDX_Control(pDX, IDC_NOTENAMESCOMBO, m_notenamescombo);
	DDX_Control(pDX, IDC_LYRICCOMBOBOX, m_lyricscombo);
	DDX_Control(pDX, IDC_NOTECOLOURCOMBO, m_notecolourcombo);
	DDX_Control(pDX, IDC_CHORDSCOMBO, m_chordscombo);
	DDX_Control(pDX, IDC_NOTENAMESTYPECOMBO, m_notenamestypecombo);
	DDX_Control(pDX, IDC_QUANTIZECOMBO, m_quantizecombo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ScoreLayout, CDialog)
	//{{AFX_MSG_MAP(ScoreLayout)
	ON_CBN_SELCHANGE(IDC_CHORDSCOMBO, OnSelchangeChordscombo)
	ON_CBN_SELCHANGE(IDC_SIZECOMBOBOX, OnSelchangeSizecombobox)
	ON_CBN_SELCHANGE(IDC_NOTECOLOURCOMBO, OnSelchangeNotecolourcombo)
	ON_CBN_SELCHANGE(IDC_NOTENAMESCOMBO, OnSelchangeNotenamescombo)
	ON_CBN_SELCHANGE(IDC_NOTENAMESTYPECOMBO, OnSelchangeNotenamestypecombo)
	ON_CBN_SELCHANGE(IDC_QUANTIZECOMBO, OnSelchangeQuantizecombo)
	ON_CBN_SELCHANGE(IDC_QUANTIZETRIOLECOMBO, OnSelchangeQuantizetriolecombo)
	ON_CBN_SELCHANGE(IDC_LYRICCOMBOBOX, OnSelchangeLyriccombobox)
	ON_WM_CLOSE()
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten ScoreLayout 

BOOL ScoreLayout::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_lyricscombo.InsertString(0,"---");
	m_lyricscombo.InsertString(1,"On");
	m_lyricscombo.InsertString(2,"Off");

	m_chordscombo.InsertString(0,"---");
	m_chordscombo.InsertString(1,"On");
	m_chordscombo.InsertString(2,"Off");

	m_notecolourcombo.InsertString(0,"---");
	m_notecolourcombo.InsertString(1,"On");
	m_notecolourcombo.InsertString(2,"Off");

	m_notenamescombo.InsertString(0,"---");
	m_notenamescombo.InsertString(1,"On");
	m_notenamescombo.InsertString(2,"Off");

	m_notenamestypecombo.InsertString(0,"---");
	m_notenamestypecombo.InsertString(1,"ABC");
	m_notenamestypecombo.InsertString(2,"FixedDo");
	m_notenamestypecombo.InsertString(3,"MovableDo");

	m_sizecombo.InsertString(0,"---");
	m_sizecombo.InsertString(1,"Small");
	m_sizecombo.InsertString(2,"Middle");
	m_sizecombo.InsertString(3,"Large");
	m_sizecombo.InsertString(4,"X-Large");

	m_quantizecombo.InsertString(0,"---");
	m_quantizecombo.InsertString(1,"1/4");
	m_quantizecombo.InsertString(2,"1/8");
	m_quantizecombo.InsertString(3,"1/16");
	m_quantizecombo.InsertString(4,"1/32");

	m_quantizetriolecombo.InsertString(0,"---");
	m_quantizetriolecombo.InsertString(1,"On");
	m_quantizetriolecombo.InsertString(2,"Off");

	if (hpmfi != NULL)
	{
		// get initial values form midifile
		hpmfi->get_layout_sysex_values(&lyrics_value, 
			                           &chords_value, 
									   &notenames_value, 
									   &size_value,
									   &quantize_triole_value, 
									   &quantize_value, 
									   &notenamestype_value,
									   &notecolour_value
									   );
	}

	// posit all combos at initial values:

	// lyricscombo:
	{
		switch (lyrics_value)
		{
		case 0xff:
			{
				m_lyricscombo.SetCurSel(0);
				break;
			}
		case 0x7f:
			{
				m_lyricscombo.SetCurSel(1);
				break;
			}
		case 0x00:
			{
				m_lyricscombo.SetCurSel(2);
				break;
			}
		}
	}

	// chordscombo:
	{
		switch (chords_value)
		{
		case 0xff:
			{
				m_chordscombo.SetCurSel(0);
				break;
			}
		case 0x7f:
			{
				m_chordscombo.SetCurSel(1);
				break;
			}
		case 0x00:
			{
				m_chordscombo.SetCurSel(2);
				break;
			}
		}
	}

	// notenamescombo:
	{
		switch (notenames_value)
		{
		case 0xff:
			{
				m_notenamescombo.SetCurSel(0);
				break;
			}
		case 0x7f:
			{
				m_notenamescombo.SetCurSel(1);
				break;
			}
		case 0x00:
			{
				m_notenamescombo.SetCurSel(2);
				break;
			}
		}
	}

	// sizecombo:
	{
		switch (size_value)
		{
		case 0xff:
			{
				m_sizecombo.SetCurSel(0); // ---
				break;
			}
		case 0x00:
			{
				m_sizecombo.SetCurSel(1); // Small
				break;
			}
		case 0x01:
			{
				m_sizecombo.SetCurSel(2); // Middle
				break;
			}
		case 0x02:
			{
				m_sizecombo.SetCurSel(3); // Large
				break;
			}
		case 0x03:
			{
				m_sizecombo.SetCurSel(4); // X-Large
				break;
			}
		}
	}

	// quantizetriolecombo:
	{
		switch (quantize_triole_value)
		{
		case 0xff:
			{
				m_quantizetriolecombo.SetCurSel(0);
				break;
			}
		case 0x7f:
			{
				m_quantizetriolecombo.SetCurSel(1);
				break;
			}
		case 0x00:
			{
				m_quantizetriolecombo.SetCurSel(2);
				break;
			}
		}
	}

	// quantizecombo:
	{
		switch (quantize_value)
		{
		case 0xff:
			{
				m_quantizecombo.SetCurSel(0);
				break;
			}
		case 0x00:
			{
				m_quantizecombo.SetCurSel(1);
				break;
			}
		case 0x01:
			{
				m_quantizecombo.SetCurSel(2);
				break;
			}
		case 0x02:
			{
				m_quantizecombo.SetCurSel(3);
				break;
			}
		case 0x03:
			{
				m_quantizecombo.SetCurSel(4);
				break;
			}
		}
	}


	// notenamestypecombo:
	{
		switch (notenamestype_value)
		{
		case 0xff:
			{
				m_notenamestypecombo.SetCurSel(0);
				break;
			}
		case 0x00:
			{
				m_notenamestypecombo.SetCurSel(1);
				break;
			}
		case 0x01:
			{
				m_notenamestypecombo.SetCurSel(2);
				break;
			}
		case 0x02:
			{
				m_notenamestypecombo.SetCurSel(3);
				break;
			}
		}
	}

	// notecolourcombo:
	{
		switch (notecolour_value)
		{
		case 0xff:
			{
				m_notecolourcombo.SetCurSel(0);
				break;
			}
		case 0x7f:
			{
				m_notecolourcombo.SetCurSel(1);
				break;
			}
		case 0x00:
			{
				m_notecolourcombo.SetCurSel(2);
				break;
			}
		}
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben

}


// Selection in layout combos


void ScoreLayout::OnSelchangeLyriccombobox() 
{
	int value_index = m_lyricscombo.GetCurSel();
	switch (value_index)
	{
	case 0:
		{
			lyrics_value = 0xff; // undef
			break;
		}
	case 1:
		{
			lyrics_value = 0x7f; // On
			break;
		}
	case 2:
		{
			lyrics_value = 0x00; // Off
			break;
		}
	}
}


void ScoreLayout::OnSelchangeChordscombo() 
{
	int value_index = m_chordscombo.GetCurSel();
	switch (value_index)
	{
	case 0:
		{
			chords_value = 0xff; // undef
			break;
		}
	case 1:
		{
			chords_value = 0x7f; // On
			break;
		}
	case 2:
		{
			chords_value = 0x00; // Off
			break;
		}
	}	
}

void ScoreLayout::OnSelchangeNotenamescombo() 
{
	int value_index = m_notenamescombo.GetCurSel();
	switch (value_index)
	{
	case 0:
		{
			notenames_value = 0xff; // undef
			break;
		}
	case 1:
		{
			notenames_value = 0x7f; // On
			break;
		}
	case 2:
		{
			notenames_value = 0x00; // Off
			break;
		}
	}	
}

void ScoreLayout::OnSelchangeSizecombobox() 
{
	int value_index = m_sizecombo.GetCurSel();
	switch (value_index)
	{
	case 0:
		{
			size_value = 0xff; // undef
			break;
		}
	case 1:
		{
			size_value = 0x00; // small
			break;
		}
	case 2:
		{
			size_value = 0x01; // middle
			break;
		}
	case 3:
		{
			size_value = 0x02; // large
			break;
		}
	case 4:
		{
			size_value = 0x03; // x-large
			break;
		}
	}		
}


void ScoreLayout::OnSelchangeQuantizetriolecombo() 
{
	int value_index = m_quantizetriolecombo.GetCurSel();
	switch (value_index)
	{
	case 0:
		{
			quantize_triole_value = 0xff; // undef
			break;
		}
	case 1:
		{
			quantize_triole_value = 0x7f; // On
			break;
		}
	case 2:
		{
			quantize_triole_value = 0x00; // Off
			break;
		}
	}	
}

void ScoreLayout::OnSelchangeQuantizecombo() 
{
	int value_index = m_quantizecombo.GetCurSel();
	switch (value_index)
	{
	case 0:
		{
			quantize_value = 0xff; // undef
			break;
		}
	case 1:
		{
			quantize_value = 0x00; // quarter
			break;
		}
	case 2:
		{
			quantize_value = 0x01; // eighth
			break;
		}
	case 3:
		{
			quantize_value = 0x02; // sixteenth
			break;
		}
	case 4:
		{
			quantize_value = 0x03; // thirty-second
			break;
		}
	}	
}

void ScoreLayout::OnSelchangeNotenamestypecombo() 
{
	int value_index = m_notenamestypecombo.GetCurSel();
	switch (value_index)
	{
	case 0:
		{
			notenamestype_value = 0xff; // undef
			break;
		}
	case 1:
		{
			notenamestype_value = 0x00; // ABC
			break;
		}
	case 2:
		{
			notenamestype_value = 0x01; // FxedDo
			break;
		}
	
	case 3:
		{
			notenamestype_value = 0x02; // MovableDo
			break;
		}
	}
}

void ScoreLayout::OnSelchangeNotecolourcombo() 
{
	int value_index = m_notecolourcombo.GetCurSel();
	switch (value_index)
	{
	case 0:
		{
			notecolour_value = 0xff; // undef
			break;
		}
	case 1:
		{
			notecolour_value = 0x7f; // On
			break;
		}
	case 2:
		{
			notecolour_value = 0x00; // Off
			break;
		}
	}	
}


void ScoreLayout::OnOK() 
{
	if ((quantize_triole_value!=0xff)&&(quantize_value==0xff))
	{
		quantize_triole_value=0xff;
	}
	EndDialog(1);
}


void ScoreLayout::OnCancel() 
{
	EndDialog(-1);
}


void ScoreLayout::OnClose() 
{
	OnCancel();
}

