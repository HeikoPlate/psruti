// SelectMIDIDevice.cpp: Implementation
//

#include "stdafx.h"
#include "Resource.h"
#include "SelectMIDIDevice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Dialog SelectMIDIDevice 

SelectMIDIDevice::SelectMIDIDevice(CWnd* pParent /*=NULL*/)
	: CDialog(SelectMIDIDevice::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelectMIDIDevice)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void SelectMIDIDevice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelectMIDIDevice)
	DDX_Control(pDX, IDC_DEVICE_LIST, m_device_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelectMIDIDevice, CDialog)
	//{{AFX_MSG_MAP(SelectMIDIDevice)
	ON_WM_CANCELMODE()
	ON_WM_CAPTURECHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//***********************************************************************
//
//	fill data in dlg
//
//***********************************************************************

BOOL SelectMIDIDevice::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString ini_device = p_inifile->get_midiport();
	int ini_port_id = -1;
	int ini_port_index = 0;
	int k;

	// get list available of MIDI-devices
	HP_GetMIDIDevices(&devices,&no_devices);

	// save id's local and  device-names in dlg-list
	for (k=0; k<no_devices; k++)
	{
		int id = devices[k].device_id;
		char* name = devices[k].device_name;
		CString cname = name;
		if (cname == ini_device)
		{
			ini_port_id = id;
			ini_port_index = k;
		}
		id_list[k] = id;
		m_device_list.AddString(name);
	}

	m_device_list.SetCurSel(ini_port_index);
	id = ini_port_id;
	old_id = id;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

//***********************************************************************
//
//	OK, send selected id
//
//***********************************************************************

void SelectMIDIDevice::OnOK() 
{
	int gcs = m_device_list.GetCurSel();
	CString port_name;

	if (gcs != LB_ERR)
	{
		id = id_list[gcs];
		port_name = devices[gcs].device_name;
		p_inifile->set_midiport(port_name);
	}

	// must be done!
	HP_Delete(devices);
	EndDialog(id);
}

//***********************************************************************
//
//	Cancel
//
//***********************************************************************

void SelectMIDIDevice::OnCancel() 
{
	HP_Delete(devices);
	EndDialog(old_id); // return the old id
}
