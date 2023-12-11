// VelCompress.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "VelCompress.h"
#include "psrutiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld VelCompress 


VelCompress::VelCompress(CWnd* pParent /*=NULL*/)
	: CDialog(VelCompress::IDD, pParent)
{
	//{{AFX_DATA_INIT(VelCompress)
	//}}AFX_DATA_INIT

	int i;

	m_edt_min_new_list[0] = &m_edt_min_new1;
	m_edt_max_new_list[0] = &m_edt_max_new1;
	m_edt_average_list[0] = &m_edt_average1;
	m_edt_delete_upto_list[0] = &m_edt_delete_upto1;
	m_button_default_list[0] = &m_default_button1;
	m_edt_max_list[0] = &m_edt_max1;
	m_edt_min_list[0] = &m_edt_min1;

	m_edt_min_new_list[1] = &m_edt_min_new2;
	m_edt_max_new_list[1] = &m_edt_max_new2;
	m_edt_average_list[1] = &m_edt_average2;
	m_edt_delete_upto_list[1] = &m_edt_delete_upto2;
	m_button_default_list[1] = &m_default_button2;
	m_edt_max_list[1] = &m_edt_max2;
	m_edt_min_list[1] = &m_edt_min2;

	m_edt_min_new_list[2] = &m_edt_min_new3;
	m_edt_max_new_list[2] = &m_edt_max_new3;
	m_edt_average_list[2] = &m_edt_average3;
	m_edt_delete_upto_list[2] = &m_edt_delete_upto3;
	m_button_default_list[2] = &m_default_button3;
	m_edt_max_list[2] = &m_edt_max3;
	m_edt_min_list[2] = &m_edt_min3;

	m_edt_min_new_list[3] = &m_edt_min_new4;
	m_edt_max_new_list[3] = &m_edt_max_new4;
	m_edt_average_list[3] = &m_edt_average4;
	m_edt_delete_upto_list[3] = &m_edt_delete_upto4;
	m_button_default_list[3] = &m_default_button4;
	m_edt_max_list[3] = &m_edt_max4;
	m_edt_min_list[3] = &m_edt_min4;

	m_edt_min_new_list[4] = &m_edt_min_new5;
	m_edt_max_new_list[4] = &m_edt_max_new5;
	m_edt_average_list[4] = &m_edt_average5;
	m_edt_delete_upto_list[4] = &m_edt_delete_upto5;
	m_button_default_list[4] = &m_default_button5;
	m_edt_max_list[4] = &m_edt_max5;
	m_edt_min_list[4] = &m_edt_min5;

	m_edt_min_new_list[5] = &m_edt_min_new6;
	m_edt_max_new_list[5] = &m_edt_max_new6;
	m_edt_average_list[5] = &m_edt_average6;
	m_edt_delete_upto_list[5] = &m_edt_delete_upto6;
	m_button_default_list[5] = &m_default_button6;
	m_edt_max_list[5] = &m_edt_max6;
	m_edt_min_list[5] = &m_edt_min6;

	m_edt_min_new_list[6] = &m_edt_min_new7;
	m_edt_max_new_list[6] = &m_edt_max_new7;
	m_edt_average_list[6] = &m_edt_average7;
	m_edt_delete_upto_list[6] = &m_edt_delete_upto7;
	m_button_default_list[6] = &m_default_button7;
	m_edt_max_list[6] = &m_edt_max7;
	m_edt_min_list[6] = &m_edt_min7;

	m_edt_min_new_list[7] = &m_edt_min_new8;
	m_edt_max_new_list[7] = &m_edt_max_new8;
	m_edt_average_list[7] = &m_edt_average8;
	m_edt_delete_upto_list[7] = &m_edt_delete_upto8;
	m_button_default_list[7] = &m_default_button8;
	m_edt_max_list[7] = &m_edt_max8;
	m_edt_min_list[7] = &m_edt_min8;

	m_edt_min_new_list[8] = &m_edt_min_new9;
	m_edt_max_new_list[8] = &m_edt_max_new9;
	m_edt_average_list[8] = &m_edt_average9;
	m_edt_delete_upto_list[8] = &m_edt_delete_upto9;
	m_button_default_list[8] = &m_default_button9;
	m_edt_max_list[8] = &m_edt_max9;
	m_edt_min_list[8] = &m_edt_min9;

	m_edt_min_new_list[9] = &m_edt_min_new10;
	m_edt_max_new_list[9] = &m_edt_max_new10;
	m_edt_average_list[9] = &m_edt_average10;
	m_edt_delete_upto_list[9] = &m_edt_delete_upto10;
	m_button_default_list[9] = &m_default_button10;
	m_edt_max_list[9] = &m_edt_max10;
	m_edt_min_list[9] = &m_edt_min10;

	m_edt_min_new_list[10] = &m_edt_min_new11;
	m_edt_max_new_list[10] = &m_edt_max_new11;
	m_edt_average_list[10] = &m_edt_average11;
	m_edt_delete_upto_list[10] = &m_edt_delete_upto11;
	m_button_default_list[10] = &m_default_button11;
	m_edt_max_list[10] = &m_edt_max11;
	m_edt_min_list[10] = &m_edt_min11;

	m_edt_min_new_list[11] = &m_edt_min_new12;
	m_edt_max_new_list[11] = &m_edt_max_new12;
	m_edt_average_list[11] = &m_edt_average12;
	m_edt_delete_upto_list[11] = &m_edt_delete_upto12;
	m_button_default_list[11] = &m_default_button12;
	m_edt_max_list[11] = &m_edt_max12;
	m_edt_min_list[11] = &m_edt_min12;

	m_edt_min_new_list[12] = &m_edt_min_new13;
	m_edt_max_new_list[12] = &m_edt_max_new13;
	m_edt_average_list[12] = &m_edt_average13;
	m_edt_delete_upto_list[12] = &m_edt_delete_upto13;
	m_button_default_list[12] = &m_default_button13;
	m_edt_max_list[12] = &m_edt_max13;
	m_edt_min_list[12] = &m_edt_min13;

	m_edt_min_new_list[13] = &m_edt_min_new14;
	m_edt_max_new_list[13] = &m_edt_max_new14;
	m_edt_average_list[13] = &m_edt_average14;
	m_edt_delete_upto_list[13] = &m_edt_delete_upto14;
	m_button_default_list[13] = &m_default_button14;
	m_edt_max_list[13] = &m_edt_max14;
	m_edt_min_list[13] = &m_edt_min14;

	m_edt_min_new_list[14] = &m_edt_min_new15;
	m_edt_max_new_list[14] = &m_edt_max_new15;
	m_edt_average_list[14] = &m_edt_average15;
	m_edt_delete_upto_list[14] = &m_edt_delete_upto15;
	m_button_default_list[14] = &m_default_button15;
	m_edt_max_list[14] = &m_edt_max15;
	m_edt_min_list[14] = &m_edt_min15;

	m_edt_min_new_list[15] = &m_edt_min_new16;
	m_edt_max_new_list[15] = &m_edt_max_new16;
	m_edt_average_list[15] = &m_edt_average16;
	m_edt_delete_upto_list[15] = &m_edt_delete_upto16;
	m_button_default_list[15] = &m_default_button16;
	m_edt_max_list[15] = &m_edt_max16;
	m_edt_min_list[15] = &m_edt_min16;


	min_idc_list[0] = IDC_EDT_MIN1;
	min_idc_list[1] = IDC_EDT_MIN2;
	min_idc_list[2] = IDC_EDT_MIN3;
	min_idc_list[3] = IDC_EDT_MIN4;
	min_idc_list[4] = IDC_EDT_MIN5;
	min_idc_list[5] = IDC_EDT_MIN6;
	min_idc_list[6] = IDC_EDT_MIN7;
	min_idc_list[7] = IDC_EDT_MIN8;
	min_idc_list[8] = IDC_EDT_MIN9;
	min_idc_list[9] = IDC_EDT_MIN10;
	min_idc_list[10] = IDC_EDT_MIN11;
	min_idc_list[11] = IDC_EDT_MIN12;
	min_idc_list[12] = IDC_EDT_MIN13;
	min_idc_list[13] = IDC_EDT_MIN14;
	min_idc_list[14] = IDC_EDT_MIN15;
	min_idc_list[15] = IDC_EDT_MIN16;
	
	max_idc_list[0] = IDC_EDT_MAX1;
	max_idc_list[1] = IDC_EDT_MAX2;
	max_idc_list[2] = IDC_EDT_MAX3;
	max_idc_list[3] = IDC_EDT_MAX4;
	max_idc_list[4] = IDC_EDT_MAX5;
	max_idc_list[5] = IDC_EDT_MAX6;
	max_idc_list[6] = IDC_EDT_MAX7;
	max_idc_list[7] = IDC_EDT_MAX8;
	max_idc_list[8] = IDC_EDT_MAX9;
	max_idc_list[9] = IDC_EDT_MAX10;
	max_idc_list[10] = IDC_EDT_MAX11;
	max_idc_list[11] = IDC_EDT_MAX12;
	max_idc_list[12] = IDC_EDT_MAX13;
	max_idc_list[13] = IDC_EDT_MAX14;
	max_idc_list[14] = IDC_EDT_MAX15;
	max_idc_list[15] = IDC_EDT_MAX16;


	delete_upto_idc_list[0] = IDC_EDT_DELETE_UPTO1;
	delete_upto_idc_list[1] = IDC_EDT_DELETE_UPTO2;
	delete_upto_idc_list[2] = IDC_EDT_DELETE_UPTO3;
	delete_upto_idc_list[3] = IDC_EDT_DELETE_UPTO4;
	delete_upto_idc_list[4] = IDC_EDT_DELETE_UPTO5;
	delete_upto_idc_list[5] = IDC_EDT_DELETE_UPTO6;
	delete_upto_idc_list[6] = IDC_EDT_DELETE_UPTO7;
	delete_upto_idc_list[7] = IDC_EDT_DELETE_UPTO8;
	delete_upto_idc_list[8] = IDC_EDT_DELETE_UPTO9;
	delete_upto_idc_list[9] = IDC_EDT_DELETE_UPTO10;
	delete_upto_idc_list[10] = IDC_EDT_DELETE_UPTO11;
	delete_upto_idc_list[11] = IDC_EDT_DELETE_UPTO12;
	delete_upto_idc_list[12] = IDC_EDT_DELETE_UPTO13;
	delete_upto_idc_list[13] = IDC_EDT_DELETE_UPTO14;
	delete_upto_idc_list[14] = IDC_EDT_DELETE_UPTO15;
	delete_upto_idc_list[15] = IDC_EDT_DELETE_UPTO16;
	
	min_new_idc_list[0] = IDC_EDT_MIN_NEW1;
	min_new_idc_list[1] = IDC_EDT_MIN_NEW2;
	min_new_idc_list[2] = IDC_EDT_MIN_NEW3;
	min_new_idc_list[3] = IDC_EDT_MIN_NEW4;
	min_new_idc_list[4] = IDC_EDT_MIN_NEW5;
	min_new_idc_list[5] = IDC_EDT_MIN_NEW6;
	min_new_idc_list[6] = IDC_EDT_MIN_NEW7;
	min_new_idc_list[7] = IDC_EDT_MIN_NEW8;
	min_new_idc_list[8] = IDC_EDT_MIN_NEW9;
	min_new_idc_list[9] = IDC_EDT_MIN_NEW10;
	min_new_idc_list[10] = IDC_EDT_MIN_NEW11;
	min_new_idc_list[11] = IDC_EDT_MIN_NEW12;
	min_new_idc_list[12] = IDC_EDT_MIN_NEW13;
	min_new_idc_list[13] = IDC_EDT_MIN_NEW14;
	min_new_idc_list[14] = IDC_EDT_MIN_NEW15;
	min_new_idc_list[15] = IDC_EDT_MIN_NEW16;

	max_new_idc_list[0] = IDC_EDT_MAX_NEW1;
	max_new_idc_list[1] = IDC_EDT_MAX_NEW2;
	max_new_idc_list[2] = IDC_EDT_MAX_NEW3;
	max_new_idc_list[3] = IDC_EDT_MAX_NEW4;
	max_new_idc_list[4] = IDC_EDT_MAX_NEW5;
	max_new_idc_list[5] = IDC_EDT_MAX_NEW6;
	max_new_idc_list[6] = IDC_EDT_MAX_NEW7;
	max_new_idc_list[7] = IDC_EDT_MAX_NEW8;
	max_new_idc_list[8] = IDC_EDT_MAX_NEW9;
	max_new_idc_list[9] = IDC_EDT_MAX_NEW10;
	max_new_idc_list[10] = IDC_EDT_MAX_NEW11;
	max_new_idc_list[11] = IDC_EDT_MAX_NEW12;
	max_new_idc_list[12] = IDC_EDT_MAX_NEW13;
	max_new_idc_list[13] = IDC_EDT_MAX_NEW14;
	max_new_idc_list[14] = IDC_EDT_MAX_NEW15;
	max_new_idc_list[15] = IDC_EDT_MAX_NEW16;

	voice_idc_list[0] = IDC_EDT_VOICE1;
	voice_idc_list[1] = IDC_EDT_VOICE2;
	voice_idc_list[2] = IDC_EDT_VOICE3;
	voice_idc_list[3] = IDC_EDT_VOICE4;
	voice_idc_list[4] = IDC_EDT_VOICE5;
	voice_idc_list[5] = IDC_EDT_VOICE6;
	voice_idc_list[6] = IDC_EDT_VOICE7;
	voice_idc_list[7] = IDC_EDT_VOICE8;
	voice_idc_list[8] = IDC_EDT_VOICE9;
	voice_idc_list[9] = IDC_EDT_VOICE10;
	voice_idc_list[10] = IDC_EDT_VOICE11;
	voice_idc_list[11] = IDC_EDT_VOICE12;
	voice_idc_list[12] = IDC_EDT_VOICE13;
	voice_idc_list[13] = IDC_EDT_VOICE14;
	voice_idc_list[14] = IDC_EDT_VOICE15;
	voice_idc_list[15] = IDC_EDT_VOICE16;

	m_voice_type[0] = &m_edt_voice1;
	m_voice_type[1] = &m_edt_voice2;
	m_voice_type[2] = &m_edt_voice3;
	m_voice_type[3] = &m_edt_voice4;
	m_voice_type[4] = &m_edt_voice5;
	m_voice_type[5] = &m_edt_voice6;
	m_voice_type[6] = &m_edt_voice7;
	m_voice_type[7] = &m_edt_voice8;
	m_voice_type[8] = &m_edt_voice9;
	m_voice_type[9] = &m_edt_voice10;
	m_voice_type[10] = &m_edt_voice11;
	m_voice_type[11] = &m_edt_voice12;
	m_voice_type[12] = &m_edt_voice13;
	m_voice_type[13] = &m_edt_voice14;
	m_voice_type[14] = &m_edt_voice15;
	m_voice_type[15] = &m_edt_voice16;

	average_idc_list[0] = IDC_EDT_AVERAGE1;
	average_idc_list[1] = IDC_EDT_AVERAGE2;
	average_idc_list[2] = IDC_EDT_AVERAGE3;
	average_idc_list[3] = IDC_EDT_AVERAGE4;
	average_idc_list[4] = IDC_EDT_AVERAGE5;
	average_idc_list[5] = IDC_EDT_AVERAGE6;
	average_idc_list[6] = IDC_EDT_AVERAGE7;
	average_idc_list[7] = IDC_EDT_AVERAGE8;
	average_idc_list[8] = IDC_EDT_AVERAGE9;
	average_idc_list[9] = IDC_EDT_AVERAGE10;
	average_idc_list[10] = IDC_EDT_AVERAGE11;
	average_idc_list[11] = IDC_EDT_AVERAGE12;
	average_idc_list[12] = IDC_EDT_AVERAGE13;
	average_idc_list[13] = IDC_EDT_AVERAGE14;
	average_idc_list[14] = IDC_EDT_AVERAGE15;
	average_idc_list[15] = IDC_EDT_AVERAGE16;

	for (i=0; i<16; i++)
	{
		VEL_COMPRESS_ELEM *elem = &(final_vel_compress_list[i]);
		(*elem).min = 0;
		(*elem).max = 0;
		(*elem).delete_upto = 0;
		(*elem).min_new = 0;
		(*elem).max_new = 0;
	}

	m_pToolTip = NULL;
}


void VelCompress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VelCompress)
	DDX_Control(pDX, IDC_EDT_VOICE1, m_edt_voice1);
	DDX_Control(pDX, IDC_EDT_VOICE2, m_edt_voice2);
	DDX_Control(pDX, IDC_EDT_VOICE3, m_edt_voice3);
	DDX_Control(pDX, IDC_EDT_VOICE4, m_edt_voice4);
	DDX_Control(pDX, IDC_EDT_VOICE5, m_edt_voice5);
	DDX_Control(pDX, IDC_EDT_VOICE6, m_edt_voice6);
	DDX_Control(pDX, IDC_EDT_VOICE7, m_edt_voice7);
	DDX_Control(pDX, IDC_EDT_VOICE8, m_edt_voice8);
	DDX_Control(pDX, IDC_EDT_VOICE9, m_edt_voice9);
	DDX_Control(pDX, IDC_EDT_VOICE10, m_edt_voice10);
	DDX_Control(pDX, IDC_EDT_VOICE11, m_edt_voice11);
	DDX_Control(pDX, IDC_EDT_VOICE12, m_edt_voice12);
	DDX_Control(pDX, IDC_EDT_VOICE13, m_edt_voice13);
	DDX_Control(pDX, IDC_EDT_VOICE14, m_edt_voice14);
	DDX_Control(pDX, IDC_EDT_VOICE15, m_edt_voice15);
	DDX_Control(pDX, IDC_EDT_VOICE16, m_edt_voice16);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON1, m_default_button1);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON2, m_default_button2);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON3, m_default_button3);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON4, m_default_button4);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON5, m_default_button5);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON6, m_default_button6);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON7, m_default_button7);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON8, m_default_button8);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON9, m_default_button9);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON10, m_default_button10);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON11, m_default_button11);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON12, m_default_button12);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON13, m_default_button13);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON14, m_default_button14);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON15, m_default_button15);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON16, m_default_button16);
	DDX_Control(pDX, IDC_EDT_MIN_NEW1, m_edt_min_new1);
	DDX_Control(pDX, IDC_EDT_MAX_NEW1, m_edt_max_new1);
	DDX_Control(pDX, IDC_EDT_AVERAGE1,m_edt_average1);
	DDX_Control(pDX, IDC_EDT_DELETE_UPTO1, m_edt_delete_upto1);
	DDX_Control(pDX, IDC_EDT_MAX1, m_edt_max1);
	DDX_Control(pDX, IDC_EDT_MIN1, m_edt_min1);
	DDX_Control(pDX, IDC_EDT_MIN_NEW2, m_edt_min_new2);
	DDX_Control(pDX, IDC_EDT_MAX_NEW2, m_edt_max_new2);
	DDX_Control(pDX, IDC_EDT_AVERAGE2,m_edt_average2);
	DDX_Control(pDX, IDC_EDT_DELETE_UPTO2, m_edt_delete_upto2);
	DDX_Control(pDX, IDC_EDT_MAX2, m_edt_max2);
	DDX_Control(pDX, IDC_EDT_MIN2, m_edt_min2);
	DDX_Control(pDX, IDC_EDT_MIN_NEW3, m_edt_min_new3);
	DDX_Control(pDX, IDC_EDT_MAX_NEW3, m_edt_max_new3);
	DDX_Control(pDX, IDC_EDT_AVERAGE3,m_edt_average3);
	DDX_Control(pDX, IDC_EDT_DELETE_UPTO3, m_edt_delete_upto3);
	DDX_Control(pDX, IDC_EDT_MAX3, m_edt_max3);
	DDX_Control(pDX, IDC_EDT_MIN3, m_edt_min3);
	DDX_Control(pDX, IDC_EDT_MIN_NEW4, m_edt_min_new4);
	DDX_Control(pDX, IDC_EDT_MAX_NEW4, m_edt_max_new4);
	DDX_Control(pDX, IDC_EDT_AVERAGE4,m_edt_average4);
	DDX_Control(pDX, IDC_EDT_DELETE_UPTO4, m_edt_delete_upto4);
	DDX_Control(pDX, IDC_EDT_MAX4, m_edt_max4);
	DDX_Control(pDX, IDC_EDT_MIN4, m_edt_min4);
	DDX_Control(pDX, IDC_EDT_MIN_NEW5, m_edt_min_new5);
	DDX_Control(pDX, IDC_EDT_MAX_NEW5, m_edt_max_new5);
	DDX_Control(pDX, IDC_EDT_AVERAGE5,m_edt_average5);
	DDX_Control(pDX, IDC_EDT_DELETE_UPTO5, m_edt_delete_upto5);
	DDX_Control(pDX, IDC_EDT_MAX5, m_edt_max5);
	DDX_Control(pDX, IDC_EDT_MIN5, m_edt_min5);
	DDX_Control(pDX, IDC_EDT_MIN_NEW6, m_edt_min_new6);
	DDX_Control(pDX, IDC_EDT_MAX_NEW6, m_edt_max_new6);
	DDX_Control(pDX, IDC_EDT_AVERAGE6,m_edt_average6);
	DDX_Control(pDX, IDC_EDT_DELETE_UPTO6, m_edt_delete_upto6);
	DDX_Control(pDX, IDC_EDT_MAX6, m_edt_max6);
	DDX_Control(pDX, IDC_EDT_MIN6, m_edt_min6);
	DDX_Control(pDX, IDC_EDT_MIN_NEW7, m_edt_min_new7);
	DDX_Control(pDX, IDC_EDT_MAX_NEW7, m_edt_max_new7);
	DDX_Control(pDX, IDC_EDT_AVERAGE7,m_edt_average7);
	DDX_Control(pDX, IDC_EDT_DELETE_UPTO7, m_edt_delete_upto7);
	DDX_Control(pDX, IDC_EDT_MAX7, m_edt_max7);
	DDX_Control(pDX, IDC_EDT_MIN7, m_edt_min7);
	DDX_Control(pDX, IDC_EDT_MIN_NEW8, m_edt_min_new8);
	DDX_Control(pDX, IDC_EDT_MAX_NEW8, m_edt_max_new8);
	DDX_Control(pDX, IDC_EDT_AVERAGE8,m_edt_average8);
	DDX_Control(pDX, IDC_EDT_DELETE_UPTO8, m_edt_delete_upto8);
	DDX_Control(pDX, IDC_EDT_MAX8, m_edt_max8);
	DDX_Control(pDX, IDC_EDT_MIN8, m_edt_min8);
	DDX_Control(pDX, IDC_EDT_MIN_NEW9, m_edt_min_new9);
	DDX_Control(pDX, IDC_EDT_MAX_NEW9, m_edt_max_new9);
	DDX_Control(pDX, IDC_EDT_AVERAGE9,m_edt_average9);
	DDX_Control(pDX, IDC_EDT_DELETE_UPTO9, m_edt_delete_upto9);
	DDX_Control(pDX, IDC_EDT_MAX9, m_edt_max9);
	DDX_Control(pDX, IDC_EDT_MIN9, m_edt_min9);
	DDX_Control(pDX, IDC_EDT_MIN_NEW10, m_edt_min_new10);
	DDX_Control(pDX, IDC_EDT_MAX_NEW10, m_edt_max_new10);
	DDX_Control(pDX, IDC_EDT_AVERAGE10,m_edt_average10);
	DDX_Control(pDX, IDC_EDT_DELETE_UPTO10, m_edt_delete_upto10);
	DDX_Control(pDX, IDC_EDT_MAX10, m_edt_max10);
	DDX_Control(pDX, IDC_EDT_MIN10, m_edt_min10);
	DDX_Control(pDX, IDC_EDT_MIN_NEW11, m_edt_min_new11);
	DDX_Control(pDX, IDC_EDT_MAX_NEW11, m_edt_max_new11);
	DDX_Control(pDX, IDC_EDT_AVERAGE11,m_edt_average11);
	DDX_Control(pDX, IDC_EDT_DELETE_UPTO11, m_edt_delete_upto11);
	DDX_Control(pDX, IDC_EDT_MAX11, m_edt_max11);
	DDX_Control(pDX, IDC_EDT_MIN11, m_edt_min11);
	DDX_Control(pDX, IDC_EDT_MIN_NEW12, m_edt_min_new12);
	DDX_Control(pDX, IDC_EDT_MAX_NEW12, m_edt_max_new12);
	DDX_Control(pDX, IDC_EDT_AVERAGE12,m_edt_average12);
	DDX_Control(pDX, IDC_EDT_DELETE_UPTO12, m_edt_delete_upto12);
	DDX_Control(pDX, IDC_EDT_MAX12, m_edt_max12);
	DDX_Control(pDX, IDC_EDT_MIN12, m_edt_min12);
	DDX_Control(pDX, IDC_EDT_MIN_NEW13, m_edt_min_new13);
	DDX_Control(pDX, IDC_EDT_MAX_NEW13, m_edt_max_new13);
	DDX_Control(pDX, IDC_EDT_AVERAGE13,m_edt_average13);
	DDX_Control(pDX, IDC_EDT_DELETE_UPTO13, m_edt_delete_upto13);
	DDX_Control(pDX, IDC_EDT_MAX13, m_edt_max13);
	DDX_Control(pDX, IDC_EDT_MIN13, m_edt_min13);
	DDX_Control(pDX, IDC_EDT_MIN_NEW14, m_edt_min_new14);
	DDX_Control(pDX, IDC_EDT_MAX_NEW14, m_edt_max_new14);
	DDX_Control(pDX, IDC_EDT_AVERAGE14,m_edt_average14);
	DDX_Control(pDX, IDC_EDT_DELETE_UPTO14, m_edt_delete_upto14);
	DDX_Control(pDX, IDC_EDT_MAX14, m_edt_max14);
	DDX_Control(pDX, IDC_EDT_MIN14, m_edt_min14);
	DDX_Control(pDX, IDC_EDT_MIN_NEW15, m_edt_min_new15);
	DDX_Control(pDX, IDC_EDT_MAX_NEW15, m_edt_max_new15);
	DDX_Control(pDX, IDC_EDT_AVERAGE15,m_edt_average15);
	DDX_Control(pDX, IDC_EDT_DELETE_UPTO15, m_edt_delete_upto15);
	DDX_Control(pDX, IDC_EDT_MAX15, m_edt_max15);
	DDX_Control(pDX, IDC_EDT_MIN15, m_edt_min15);
	DDX_Control(pDX, IDC_EDT_MIN_NEW16, m_edt_min_new16);
	DDX_Control(pDX, IDC_EDT_MAX_NEW16, m_edt_max_new16);
	DDX_Control(pDX, IDC_EDT_AVERAGE16,m_edt_average16);
	DDX_Control(pDX, IDC_EDT_DELETE_UPTO16, m_edt_delete_upto16);
	DDX_Control(pDX, IDC_EDT_MAX16, m_edt_max16);
	DDX_Control(pDX, IDC_EDT_MIN16, m_edt_min16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VelCompress, CDialog)
	//{{AFX_MSG_MAP(VelCompress)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON1, OnDefaultButton1)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON2, OnDefaultButton2)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON3, OnDefaultButton3)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON4, OnDefaultButton4)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON5, OnDefaultButton5)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON6, OnDefaultButton6)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON7, OnDefaultButton7)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON8, OnDefaultButton8)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON9, OnDefaultButton9)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON10, OnDefaultButton10)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON11, OnDefaultButton11)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON12, OnDefaultButton12)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON13, OnDefaultButton13)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON14, OnDefaultButton14)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON15, OnDefaultButton15)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON16, OnDefaultButton16)
	ON_EN_UPDATE(IDC_EDT_DELETE_UPTO1, OnUpdateEdtDeleteUpto1)
	ON_EN_UPDATE(IDC_EDT_DELETE_UPTO2, OnUpdateEdtDeleteUpto2)
	ON_EN_UPDATE(IDC_EDT_DELETE_UPTO3, OnUpdateEdtDeleteUpto3)
	ON_EN_UPDATE(IDC_EDT_DELETE_UPTO4, OnUpdateEdtDeleteUpto4)
	ON_EN_UPDATE(IDC_EDT_DELETE_UPTO5, OnUpdateEdtDeleteUpto5)
	ON_EN_UPDATE(IDC_EDT_DELETE_UPTO6, OnUpdateEdtDeleteUpto6)
	ON_EN_UPDATE(IDC_EDT_DELETE_UPTO7, OnUpdateEdtDeleteUpto7)
	ON_EN_UPDATE(IDC_EDT_DELETE_UPTO8, OnUpdateEdtDeleteUpto8)
	ON_EN_UPDATE(IDC_EDT_DELETE_UPTO9, OnUpdateEdtDeleteUpto9)
	ON_EN_UPDATE(IDC_EDT_DELETE_UPTO10, OnUpdateEdtDeleteUpto10)
	ON_EN_UPDATE(IDC_EDT_DELETE_UPTO11, OnUpdateEdtDeleteUpto11)
	ON_EN_UPDATE(IDC_EDT_DELETE_UPTO12, OnUpdateEdtDeleteUpto12)
	ON_EN_UPDATE(IDC_EDT_DELETE_UPTO13, OnUpdateEdtDeleteUpto13)
	ON_EN_UPDATE(IDC_EDT_DELETE_UPTO14, OnUpdateEdtDeleteUpto14)
	ON_EN_UPDATE(IDC_EDT_DELETE_UPTO15, OnUpdateEdtDeleteUpto15)
	ON_EN_UPDATE(IDC_EDT_DELETE_UPTO16, OnUpdateEdtDeleteUpto16)
	ON_EN_UPDATE(IDC_EDT_MIN_NEW1, OnUpdateEdtMinNew1)
	ON_EN_UPDATE(IDC_EDT_MIN_NEW2, OnUpdateEdtMinNew2)
	ON_EN_UPDATE(IDC_EDT_MIN_NEW3, OnUpdateEdtMinNew3)
	ON_EN_UPDATE(IDC_EDT_MIN_NEW4, OnUpdateEdtMinNew4)
	ON_EN_UPDATE(IDC_EDT_MIN_NEW5, OnUpdateEdtMinNew5)
	ON_EN_UPDATE(IDC_EDT_MIN_NEW6, OnUpdateEdtMinNew6)
	ON_EN_UPDATE(IDC_EDT_MIN_NEW7, OnUpdateEdtMinNew7)
	ON_EN_UPDATE(IDC_EDT_MIN_NEW8, OnUpdateEdtMinNew8)
	ON_EN_UPDATE(IDC_EDT_MIN_NEW9, OnUpdateEdtMinNew9)
	ON_EN_UPDATE(IDC_EDT_MIN_NEW10, OnUpdateEdtMinNew10)
	ON_EN_UPDATE(IDC_EDT_MIN_NEW11, OnUpdateEdtMinNew11)
	ON_EN_UPDATE(IDC_EDT_MIN_NEW12, OnUpdateEdtMinNew12)
	ON_EN_UPDATE(IDC_EDT_MIN_NEW13, OnUpdateEdtMinNew13)
	ON_EN_UPDATE(IDC_EDT_MIN_NEW14, OnUpdateEdtMinNew14)
	ON_EN_UPDATE(IDC_EDT_MIN_NEW15, OnUpdateEdtMinNew15)
	ON_EN_UPDATE(IDC_EDT_MIN_NEW16, OnUpdateEdtMinNew16)
	ON_EN_UPDATE(IDC_EDT_MAX_NEW1, OnUpdateEdtMaxNew1)
	ON_EN_UPDATE(IDC_EDT_MAX_NEW2, OnUpdateEdtMaxNew2)
	ON_EN_UPDATE(IDC_EDT_MAX_NEW3, OnUpdateEdtMaxNew3)
	ON_EN_UPDATE(IDC_EDT_MAX_NEW4, OnUpdateEdtMaxNew4)
	ON_EN_UPDATE(IDC_EDT_MAX_NEW5, OnUpdateEdtMaxNew5)
	ON_EN_UPDATE(IDC_EDT_MAX_NEW6, OnUpdateEdtMaxNew6)
	ON_EN_UPDATE(IDC_EDT_MAX_NEW7, OnUpdateEdtMaxNew7)
	ON_EN_UPDATE(IDC_EDT_MAX_NEW8, OnUpdateEdtMaxNew8)
	ON_EN_UPDATE(IDC_EDT_MAX_NEW9, OnUpdateEdtMaxNew9)
	ON_EN_UPDATE(IDC_EDT_MAX_NEW10, OnUpdateEdtMaxNew10)
	ON_EN_UPDATE(IDC_EDT_MAX_NEW11, OnUpdateEdtMaxNew11)
	ON_EN_UPDATE(IDC_EDT_MAX_NEW12, OnUpdateEdtMaxNew12)
	ON_EN_UPDATE(IDC_EDT_MAX_NEW13, OnUpdateEdtMaxNew13)
	ON_EN_UPDATE(IDC_EDT_MAX_NEW14, OnUpdateEdtMaxNew14)
	ON_EN_UPDATE(IDC_EDT_MAX_NEW15, OnUpdateEdtMaxNew15)
	ON_EN_UPDATE(IDC_EDT_MAX_NEW16, OnUpdateEdtMaxNew16)
	ON_BN_CLICKED(IDC_CHECK_ALL, OnCheckAll)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON1, OnDefaultButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten VelCompress 

BOOL VelCompress::PreTranslateMessage(MSG* pMsg) 
{
	if (NULL != m_pToolTip)
	{
		m_pToolTip->RelayEvent(pMsg);
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL VelCompress::OnInitDialog() 
{
	int chan;

	CDialog::OnInitDialog();

	SetDlgItemText(IDC_TXT_1,"1");
	SetDlgItemText(IDC_TXT_2,"2");
	SetDlgItemText(IDC_TXT_3,"3");
	SetDlgItemText(IDC_TXT_4,"4");
	SetDlgItemText(IDC_TXT_5,"5");
	SetDlgItemText(IDC_TXT_6,"6");
	SetDlgItemText(IDC_TXT_7,"7");
	SetDlgItemText(IDC_TXT_8,"8");
	SetDlgItemText(IDC_TXT_9,"9");
	SetDlgItemText(IDC_TXT_10,"10");
	SetDlgItemText(IDC_TXT_11,"11");
	SetDlgItemText(IDC_TXT_12,"12");
	SetDlgItemText(IDC_TXT_13,"13");
	SetDlgItemText(IDC_TXT_14,"14");
	SetDlgItemText(IDC_TXT_15,"15");
	SetDlgItemText(IDC_TXT_16,"16");
	SetDlgItemText(IDC_TXT_CHAN,GlobalUtilities::get_resource_string(IDS_CHANNEL));
	SetDlgItemText(IDC_TXT_VOICE,"Voice");
	SetDlgItemText(IDC_TXT_MIN_IST,"Min.");
	SetDlgItemText(IDC_TXT_MAX_IST,"Max.");
	SetDlgItemText(IDC_TXT_DEFAULT,"Default");
	SetDlgItemText(IDC_TXT_DELETE_UPTO,GlobalUtilities::get_resource_string(IDS_DELETE_UPTO));
	SetDlgItemText(IDC_TXT_MIN_NEW,GlobalUtilities::get_resource_string(IDS_MIN_NEW));
	SetDlgItemText(IDC_TXT_MAX_NEW,GlobalUtilities::get_resource_string(IDS_MAX_NEW));
	SetDlgItemText(IDC_TXT_AVERAGE,GlobalUtilities::get_resource_string(IDS_AVERAGE));

	init = true;
	
	int i;

	hpmfi->get_max_min_max_average_vel(min_max_average_vel_list);

	for (i=0; i<16; i++)
	{
		m_edt_delete_upto_list[i]->SetLimitText(3);
		m_edt_min_new_list[i]->SetLimitText(3);
		m_edt_max_list[i]->SetLimitText(3);
		m_edt_average_list[i]->SetLimitText(3);

		int min_vel = min_max_average_vel_list[i][0];
		int max_vel = min_max_average_vel_list[i][1];
		int average_vel = min_max_average_vel_list[i][2];
		int min_idc = min_idc_list[i];
		int max_idc = max_idc_list[i];
		int average_idc = average_idc_list[i];
		int delete_upto = delete_upto_idc_list[i];
		int min_new_idc = min_new_idc_list[i];
		int max_new_idc = max_new_idc_list[i];
		int voice_idc = voice_idc_list[i];
		
		if (min_vel==128) // and max_vel==-1 also
		{
			SetDlgItemText(min_idc,"");
			m_edt_min_list[i]->EnableWindow(false);
			SetDlgItemText(max_idc,"");
			m_edt_max_list[i]->EnableWindow(false);
			SetDlgItemText(average_idc,"");
			m_edt_average_list[i]->EnableWindow(false);
			m_edt_delete_upto_list[i]->EnableWindow(false);
			m_edt_min_new_list[i]->EnableWindow(false);
			m_edt_max_new_list[i]->EnableWindow(false);
			m_button_default_list[i]->EnableWindow(false);
		}
		else
		{
			SetDlgItemInt(min_idc, min_vel,TRUE);
			SetDlgItemInt(max_idc, max_vel,TRUE);
			SetDlgItemInt(delete_upto,1,TRUE);
			SetDlgItemInt(min_new_idc,min_vel,TRUE);
			SetDlgItemInt(max_new_idc,max_vel,TRUE);
			SetDlgItemInt(average_idc, average_vel,TRUE);
			SetDlgItemInt(max_idc,max_vel,TRUE);
			CString pn = hpmfi->patchname[i];
			SetDlgItemText(voice_idc,pn);
		}
	}

	// Tool Tips
	if (hpmfi->with_insdef)
	{
		m_pToolTip = new CToolTipCtrl;
		m_pToolTip->Create(this);
		m_pToolTip->SetDelayTime(TTDT_AUTOPOP,4000);
		m_pToolTip->SetMaxTipWidth(200);

		for (chan=0; chan<16; chan++)
		{
			if ((hpmfi->mlv_list[chan]).voicename == "") continue;
			m_pToolTip->AddTool(m_voice_type[chan],(hpmfi->mlv_list[chan]).voicename);
		}
		m_pToolTip->Activate(true);
	}


	init = false;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void VelCompress::OnDefaultButton1() 
{
	set_default(0);	
}

void VelCompress::OnDefaultButton2() 
{
	set_default(1);	
}

void VelCompress::OnDefaultButton3() 
{
	set_default(2);	
}

void VelCompress::OnDefaultButton4() 
{
	set_default(3);	
}

void VelCompress::OnDefaultButton5() 
{
	set_default(4);	
}

void VelCompress::OnDefaultButton6() 
{
	set_default(5);	
}

void VelCompress::OnDefaultButton7() 
{
	set_default(6);	
}

void VelCompress::OnDefaultButton8() 
{
	set_default(7);	
}

void VelCompress::OnDefaultButton9() 
{
	set_default(8);	
}

void VelCompress::OnDefaultButton10() 
{
	set_default(9);	
}

void VelCompress::OnDefaultButton11() 
{
	set_default(10);	
}

void VelCompress::OnDefaultButton12() 
{
	set_default(11);	
}

void VelCompress::OnDefaultButton13() 
{
	set_default(12);	
}

void VelCompress::OnDefaultButton14() 
{
	set_default(13);	
}

void VelCompress::OnDefaultButton15() 
{
	set_default(14);	
}

void VelCompress::OnDefaultButton16() 
{
	set_default(15);	
}

//*************************************************
//
// Central set_default function
//
//*************************************************

void VelCompress::set_default(int chan)
{
	// set to initial
	int min_vel = min_max_average_vel_list[chan][0];
	int max_vel = min_max_average_vel_list[chan][1];
	int average_vel = min_max_average_vel_list[chan][2];
	int delete_upto = delete_upto_idc_list[chan];
	int min_new_idc = min_new_idc_list[chan];
	int max_new_idc = max_new_idc_list[chan];
	int average_idc = average_idc_list[chan];

	SetDlgItemInt(delete_upto,1,TRUE);
	SetDlgItemInt(min_new_idc,min_vel,TRUE);
	SetDlgItemInt(max_new_idc,max_vel,TRUE);
	SetDlgItemInt(average_idc,average_vel,TRUE);
}



void VelCompress::OnUpdateEdtDeleteUpto1() 
{
	if (init) return;
	check_delete_upto(1);
	actualize_min(1);
}

void VelCompress::OnUpdateEdtDeleteUpto2() 
{
	if (init) return;
	check_delete_upto(2);
	actualize_min(2);
}

void VelCompress::OnUpdateEdtDeleteUpto3() 
{
	if (init) return;
	check_delete_upto(3);
	actualize_min(3);		
}

void VelCompress::OnUpdateEdtDeleteUpto4() 
{
	if (init) return;
	check_delete_upto(4);
	actualize_min(4);		
}

void VelCompress::OnUpdateEdtDeleteUpto5() 
{
	if (init) return;
	check_delete_upto(5);
	actualize_min(5);		
}

void VelCompress::OnUpdateEdtDeleteUpto6() 
{
	if (init) return;
	check_delete_upto(6);
	actualize_min(6);		
}

void VelCompress::OnUpdateEdtDeleteUpto7() 
{
	if (init) return;
	check_delete_upto(7);
	actualize_min(7);		
}

void VelCompress::OnUpdateEdtDeleteUpto8() 
{
	if (init) return;
	check_delete_upto(8);
	actualize_min(8);		
}

void VelCompress::OnUpdateEdtDeleteUpto9() 
{
	if (init) return;
	check_delete_upto(9);
	actualize_min(9);	
}

void VelCompress::OnUpdateEdtDeleteUpto10() 
{
	if (init) return;
	check_delete_upto(10);
	actualize_min(10);	
}

void VelCompress::OnUpdateEdtDeleteUpto11() 
{
	if (init) return;
	check_delete_upto(11);
	actualize_min(11);		
}

void VelCompress::OnUpdateEdtDeleteUpto12() 
{
	if (init) return;
	check_delete_upto(12);
	actualize_min(12);		
}

void VelCompress::OnUpdateEdtDeleteUpto13() 
{
	if (init) return;
	check_delete_upto(13);
	actualize_min(13);		
}

void VelCompress::OnUpdateEdtDeleteUpto14() 
{
	if (init) return;
	check_delete_upto(14);
	actualize_min(14);		
}

void VelCompress::OnUpdateEdtDeleteUpto15() 
{
	if (init) return;
	check_delete_upto(15);
	actualize_min(15);		
}

void VelCompress::OnUpdateEdtDeleteUpto16() 
{
	if (init) return;
	check_delete_upto(16);
	actualize_min(16);		
}

// void VelCompress::OnUpdateEdtMinNew1() 
void VelCompress::OnUpdateEdtMinNew1()
{
	if (init) return;
	check_min_new(1);
	actualize_average();	
}

void VelCompress::OnUpdateEdtMinNew2() 
{
	if (init) return;
	check_min_new(2);
	actualize_average();	
}

void VelCompress::OnUpdateEdtMinNew3() 
{
	if (init) return;
	check_min_new(3);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMinNew4() 
{
	if (init) return;
	check_min_new(4);
	actualize_average();	
}

void VelCompress::OnUpdateEdtMinNew5() 
{
	if (init) return;
	check_min_new(5);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMinNew6() 
{
	if (init) return;
	check_min_new(6);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMinNew7() 
{
	if (init) return;
	check_min_new(7);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMinNew8() 
{
	if (init) return;
	check_min_new(8);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMinNew9() 
{
	if (init) return;
	check_min_new(9);
	actualize_average();
}

void VelCompress::OnUpdateEdtMinNew10() 
{
	if (init) return;
	check_min_new(10);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMinNew11() 
{
	if (init) return;
	check_min_new(11);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMinNew12() 
{
	if (init) return;
	check_min_new(12);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMinNew13() 
{
	if (init) return;
	check_min_new(13);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMinNew14() 
{
	if (init) return;
	check_min_new(14);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMinNew15() 
{
	if (init) return;
	check_min_new(15);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMinNew16() 
{
	if (init) return;
	check_min_new(16);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMaxNew1() 
{
	if (init) return;
	check_max_new(1);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMaxNew2() 
{
	if (init) return;
	check_max_new(2);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMaxNew3() 
{
	if (init) return;
	check_max_new(3);
	actualize_average();	
}

void VelCompress::OnUpdateEdtMaxNew4() 
{
	if (init) return;
	check_max_new(4);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMaxNew5() 
{
	if (init) return;
	check_max_new(5);
	actualize_average();
}

void VelCompress::OnUpdateEdtMaxNew6() 
{
	if (init) return;
	check_max_new(6);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMaxNew7() 
{
	if (init) return;
	check_max_new(7);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMaxNew8() 
{
	if (init) return;
	check_max_new(8);
	actualize_average();
}

void VelCompress::OnUpdateEdtMaxNew9() 
{
	if (init) return;
	check_max_new(9);
	actualize_average();	
}

void VelCompress::OnUpdateEdtMaxNew10() 
{
	if (init) return;
	check_max_new(10);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMaxNew11() 
{
	if (init) return;
	check_max_new(11);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMaxNew12() 
{
	if (init) return;
	check_max_new(12);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMaxNew13() 
{
	if (init) return;
	check_max_new(13);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMaxNew14() 
{
	if (init) return;
	check_max_new(14);
	actualize_average();	
}

void VelCompress::OnUpdateEdtMaxNew15() 
{
	if (init) return;
	check_max_new(15);
	actualize_average();		
}

void VelCompress::OnUpdateEdtMaxNew16() 
{
	if (init) return;
	check_max_new(16);
	actualize_average();		
}

void VelCompress::actualize_average()
{
	int i;
	VEL_COMPRESS_ELEM actual_vel_compress_list[16];
	int actual_average_list[16];

	for (i=0; i<16; i++)
	{

		int min_vel = min_max_average_vel_list[i][0];
		if (min_vel==128) continue;

		int min_idc = min_idc_list[i];
		int max_idc = max_idc_list[i];
		int delete_upto_idc = delete_upto_idc_list[i];
		int min_new_idc = min_new_idc_list[i];
		int max_new_idc = max_new_idc_list[i];

		actual_vel_compress_list[i].min = GetDlgItemInt(min_idc);
		actual_vel_compress_list[i].max = GetDlgItemInt(max_idc);
		actual_vel_compress_list[i].delete_upto = GetDlgItemInt(delete_upto_idc);
		actual_vel_compress_list[i].min_new = GetDlgItemInt(min_new_idc);
		actual_vel_compress_list[i].max_new = GetDlgItemInt(max_new_idc);
	}
	hpmfi->compute_actual_average_vel(actual_vel_compress_list, actual_average_list);
	for (i=0; i<16; i++)
	{
		int min_vel = min_max_average_vel_list[i][0];
		if (min_vel==128) continue;

		int average_idc = average_idc_list[i];
		SetDlgItemInt(average_idc,actual_average_list[i],FALSE);
	}
}

void VelCompress::actualize_min(int chan)
{
	int min_val = GetDlgItemInt(min_new_idc_list[chan-1]);
	int max_val = GetDlgItemInt(max_new_idc_list[chan-1]);
	int del_val = GetDlgItemInt(delete_upto_idc_list[chan-1]);
	
	if (del_val < 1) 
	{
		del_val = 1;
		SetDlgItemInt(delete_upto_idc_list[chan-1],del_val);
	}
	if (del_val > max_val) 
	{
		del_val = 1;
		SetDlgItemInt(delete_upto_idc_list[chan-1],del_val);
	}

	if (min_val < del_val)
	{
		SetDlgItemInt(min_new_idc_list[chan-1],del_val);
	}
}

void VelCompress::check_delete_upto(int chan)
{
	int min_idc = min_idc_list[chan-1];
	int min = GetDlgItemInt(min_idc);
	if (min==128) return;
	int delete_upto_idc = delete_upto_idc_list[chan-1];
	int max_new_idc = max_new_idc_list[chan-1];

	int delete_upto_vel = GetDlgItemInt(delete_upto_idc);
	int max_new_vel =  GetDlgItemInt(max_new_idc);
	if (delete_upto_vel >= max_new_vel)
	{
		SetDlgItemInt(delete_upto_idc,1);
	}
}


void VelCompress::check_min_new(int chan)
{
	int min_new_idc = min_new_idc_list[chan-1];
	int max_new_idc = max_new_idc_list[chan-1];
	int delete_upto_idc = delete_upto_idc_list[chan-1];
	int min_new = GetDlgItemInt(min_new_idc);
	if (min_new < 1)
	{
		SetDlgItemInt(min_new_idc,1);
		min_new = 1;
	}
	if (min_new < 10) return; // Why?
	
	int max_new = GetDlgItemInt(max_new_idc);
	int delete_upto_vel = GetDlgItemInt(delete_upto_idc);
	if (min_new < delete_upto_vel)
	{
		SetDlgItemInt(min_new_idc,delete_upto_vel);
		min_new = delete_upto_vel;
	}

	if (min_new > max_new)
	{
		SetDlgItemInt(min_new_idc,max_new);
		min_new = max_new;
	}
}

void VelCompress::check_max_new(int chan)
{
	int min_new_idc = min_new_idc_list[chan-1];
	int max_new_idc = max_new_idc_list[chan-1];
	int min_new = GetDlgItemInt(min_new_idc);
	int max_new = GetDlgItemInt(max_new_idc);
	if (max_new > 127)
	{
		SetDlgItemInt(max_new_idc,127);
		max_new = 127;
	}
	if (max_new < 1)
	{
		SetDlgItemInt(max_new_idc,1);
		max_new = 1;
	}
}

void VelCompress::check_all(bool display)
{
	int i;
	bool original = true;

	for (i=0; i<16; i++)
	{
		int min_vel = min_max_average_vel_list[i][0];
		int max_vel = min_max_average_vel_list[i][1];
		if (min_vel == 128) continue;

		int delete_upto_idc = delete_upto_idc_list[i];
		int min_new_idc = min_new_idc_list[i];
		int max_new_idc = max_new_idc_list[i];

		int delete_upto_vel = GetDlgItemInt(delete_upto_idc);
		int min_new_vel = GetDlgItemInt(min_new_idc);
		int max_new_vel =  GetDlgItemInt(max_new_idc);

		if (delete_upto_vel < 1)
		{
			delete_upto_vel = 1;
			if (display) SetDlgItemInt(delete_upto_idc,1,FALSE);
		}
		if (delete_upto_vel > 127)
		{
			delete_upto_vel = 127;
			if (display) SetDlgItemInt(delete_upto_idc,127,FALSE);
		}

		if (min_new_vel < 1)
		{
			min_new_vel = 1;
			if (display) SetDlgItemInt(min_new_idc,1,FALSE);
		}

		if (min_new_vel > 127)
		{
			min_new_vel = 127;
			if (display) SetDlgItemInt(min_new_idc,127,FALSE);
		}

		if (max_new_vel < 1)
		{
			max_new_vel = 1;
			if (display) SetDlgItemInt(max_new_idc,1,FALSE);
		}

		if (max_new_vel > 127)
		{
			max_new_vel = 127;
			if (display) SetDlgItemInt(max_new_idc,127,FALSE);
		}

		if ((min_vel==max_vel)||(max_new_vel<min_new_vel))
		{
			max_new_vel= min_new_vel;
			if (display) SetDlgItemInt(max_new_idc,max_new_vel,FALSE);
		}
	}
}

void VelCompress::OnCheckAll() 
{
	check_all(true);
}

void VelCompress::OnOK() 
{
	check_all(false);
	int i;

	// fill list for caller
	for (i=0; i<16; i++)
	{
		int min_vel = min_max_average_vel_list[i][0];
		if (min_vel==128) continue; // no notes on channel
		int min_idc = min_idc_list[i];
		int max_idc = max_idc_list[i];
		int delete_upto_idc = delete_upto_idc_list[i];
		int min_new_idc = min_new_idc_list[i];
		int max_new_idc = max_new_idc_list[i];

		final_vel_compress_list[i].min = GetDlgItemInt(min_idc);
		final_vel_compress_list[i].max = GetDlgItemInt(max_idc);
		final_vel_compress_list[i].delete_upto = GetDlgItemInt(delete_upto_idc);
		final_vel_compress_list[i].min_new = GetDlgItemInt(min_new_idc);
		final_vel_compress_list[i].max_new = GetDlgItemInt(max_new_idc);
	}

	if (m_pToolTip != NULL)
	{
		delete m_pToolTip;
		m_pToolTip = NULL;
	}

	CDialog::OnOK();
}

void VelCompress::OnCancel() 
{
	if (m_pToolTip != NULL)
	{
		delete m_pToolTip;
		m_pToolTip = NULL;
	}

	CDialog::OnCancel();
}

