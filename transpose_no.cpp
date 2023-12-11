// Transpose_no.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "psruti.h"
#include "Transpose_no.h"
#include "ChangeKeyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Transpose_no


Transpose_no::Transpose_no(CWnd* pParent /*=NULL*/)
	: CDialog(Transpose_no::IDD, pParent)
{
	//{{AFX_DATA_INIT(Transpose_no)
	//}}AFX_DATA_INIT

	// inializes membervariable list m_voice_type

	m_voice_type[0] = &m_type1;
	m_voice_type[1] = &m_type2;
	m_voice_type[2] = &m_type3;
	m_voice_type[3] = &m_type4;
	m_voice_type[4] = &m_type5;
	m_voice_type[5] = &m_type6;
	m_voice_type[6] = &m_type7;
	m_voice_type[7] = &m_type8;
	m_voice_type[8] = &m_type9;
	m_voice_type[9] = &m_type10;
	m_voice_type[10] = &m_type11;
	m_voice_type[11] = &m_type12;
	m_voice_type[12] = &m_type13;
	m_voice_type[13] = &m_type14;
	m_voice_type[14] = &m_type15;
	m_voice_type[15] = &m_type16;

	m_pToolTip = NULL;

	int chan;

	for (chan=0; chan<16; chan++)
	{
		ll_val[chan] = 0;
		hl_val[chan] = 127;
	}
}


void Transpose_no::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Transpose_no)
	DDX_Control(pDX, IDC_TYPE1, m_type1);
	DDX_Control(pDX, IDC_TYPE2, m_type2);
	DDX_Control(pDX, IDC_TYPE3, m_type3);
	DDX_Control(pDX, IDC_TYPE4, m_type4);
	DDX_Control(pDX, IDC_TYPE5, m_type5);
	DDX_Control(pDX, IDC_TYPE6, m_type6);
	DDX_Control(pDX, IDC_TYPE7, m_type7);
	DDX_Control(pDX, IDC_TYPE8, m_type8);
	DDX_Control(pDX, IDC_TYPE9, m_type9);
	DDX_Control(pDX, IDC_TYPE10, m_type10);
	DDX_Control(pDX, IDC_TYPE11, m_type11);
	DDX_Control(pDX, IDC_TYPE12, m_type12);
	DDX_Control(pDX, IDC_TYPE13, m_type13);
	DDX_Control(pDX, IDC_TYPE14, m_type14);
	DDX_Control(pDX, IDC_TYPE15, m_type15);
	DDX_Control(pDX, IDC_TYPE16, m_type16);
	DDX_Control(pDX, IDC_TRANSPOSE_CHORDS_CHECK, m_transpose_chords_check);
	DDX_Control(pDX, IDC_OCT9, m_oct9);
	DDX_Control(pDX, IDC_OCT8, m_oct8);
	DDX_Control(pDX, IDC_OCT7, m_oct7);
	DDX_Control(pDX, IDC_OCT6, m_oct6);
	DDX_Control(pDX, IDC_OCT5, m_oct5);
	DDX_Control(pDX, IDC_OCT4, m_oct4);
	DDX_Control(pDX, IDC_OCT3, m_oct3);
	DDX_Control(pDX, IDC_OCT2, m_oct2);
	DDX_Control(pDX, IDC_OCT16, m_oct16);
	DDX_Control(pDX, IDC_OCT15, m_oct15);
	DDX_Control(pDX, IDC_OCT14, m_oct14);
	DDX_Control(pDX, IDC_OCT13, m_oct13);
	DDX_Control(pDX, IDC_OCT12, m_oct12);
	DDX_Control(pDX, IDC_OCT11, m_oct11);
	DDX_Control(pDX, IDC_OCT10, m_oct10);
	DDX_Control(pDX, IDC_OCT1, m_oct1);
	DDX_Control(pDX, IDC_EDIT_LL9, m_ll9);
	DDX_Control(pDX, IDC_EDIT_LL8, m_ll8);
	DDX_Control(pDX, IDC_EDIT_LL7, m_ll7);
	DDX_Control(pDX, IDC_EDIT_LL6, m_ll6);
	DDX_Control(pDX, IDC_EDIT_LL5, m_ll5);
	DDX_Control(pDX, IDC_EDIT_LL4, m_ll4);
	DDX_Control(pDX, IDC_EDIT_LL3, m_ll3);
	DDX_Control(pDX, IDC_EDIT_LL2, m_ll2);
	DDX_Control(pDX, IDC_EDIT_LL16, m_ll16);
	DDX_Control(pDX, IDC_EDIT_LL15, m_ll15);
	DDX_Control(pDX, IDC_EDIT_LL14, m_ll14);
	DDX_Control(pDX, IDC_EDIT_LL12, m_ll12);
	DDX_Control(pDX, IDC_EDIT_LL13, m_ll13);
	DDX_Control(pDX, IDC_EDIT_LL11, m_ll11);
	DDX_Control(pDX, IDC_EDIT_LL10, m_ll10);
	DDX_Control(pDX, IDC_EDIT_HL9, m_hl9);
	DDX_Control(pDX, IDC_EDIT_HL8, m_hl8);
	DDX_Control(pDX, IDC_EDIT_HL7, m_hl7);
	DDX_Control(pDX, IDC_EDIT_HL6, m_hl6);
	DDX_Control(pDX, IDC_EDIT_HL5, m_hl5);
	DDX_Control(pDX, IDC_EDIT_HL4, m_hl4);
	DDX_Control(pDX, IDC_EDIT_HL3, m_hl3);
	DDX_Control(pDX, IDC_EDIT_HL2, m_hl2);
	DDX_Control(pDX, IDC_EDIT_HL16, m_hl16);
	DDX_Control(pDX, IDC_EDIT_HL15, m_hl15);
	DDX_Control(pDX, IDC_EDIT_HL14, m_hl14);
	DDX_Control(pDX, IDC_EDIT_HL13, m_hl13);
	DDX_Control(pDX, IDC_EDIT_HL12, m_hl12);
	DDX_Control(pDX, IDC_EDIT_HL11, m_hl11);
	DDX_Control(pDX, IDC_EDIT_HL10, m_hl10);
	DDX_Control(pDX, IDC_CHECK_MUTE9, m_mute9);
	DDX_Control(pDX, IDC_CHECK_MUTE8, m_mute8);
	DDX_Control(pDX, IDC_CHECK_MUTE7, m_mute7);
	DDX_Control(pDX, IDC_CHECK_MUTE6, m_mute6);
	DDX_Control(pDX, IDC_CHECK_MUTE16, m_mute16);
	DDX_Control(pDX, IDC_CHECK_MUTE15, m_mute15);
	DDX_Control(pDX, IDC_CHECK_MUTE14, m_mute14);
	DDX_Control(pDX, IDC_CHECK_MUTE13, m_mute13);
	DDX_Control(pDX, IDC_CHECK_MUTE12, m_mute12);
	DDX_Control(pDX, IDC_CHECK_MUTE11, m_mute11);
	DDX_Control(pDX, IDC_CHECK_MUTE10, m_mute10);
	DDX_Control(pDX, IDC_CHECK_MUTE5, m_mute5);
	DDX_Control(pDX, IDC_CHECK_MUTE4, m_mute4);
	DDX_Control(pDX, IDC_CHECK_MUTE3, m_mute3);
	DDX_Control(pDX, IDC_CHECK_MUTE2, m_mute2);
	DDX_Control(pDX, IDC_EDIT_LL1, m_ll1);
	DDX_Control(pDX, IDC_EDIT_HL1, m_hl1);
	DDX_Control(pDX, IDC_CHECK_MUTE1, m_mute1);
	DDX_Control(pDX, IDC_LISTTRANSPOSE_NO, m_listtranspose_no);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Transpose_no, CDialog)
	//{{AFX_MSG_MAP(Transpose_no)
	ON_BN_CLICKED(IDC_CHECK, OnCheck)
	ON_LBN_SELCHANGE(IDC_OCT1, OnSelchangeOct1)
	ON_LBN_SELCHANGE(IDC_OCT10, OnSelchangeOct10)
	ON_LBN_SELCHANGE(IDC_OCT11, OnSelchangeOct11)
	ON_LBN_SELCHANGE(IDC_OCT12, OnSelchangeOct12)
	ON_LBN_SELCHANGE(IDC_OCT13, OnSelchangeOct13)
	ON_LBN_SELCHANGE(IDC_OCT14, OnSelchangeOct14)
	ON_LBN_SELCHANGE(IDC_OCT15, OnSelchangeOct15)
	ON_LBN_SELCHANGE(IDC_OCT16, OnSelchangeOct16)
	ON_LBN_SELCHANGE(IDC_OCT2, OnSelchangeOct2)
	ON_LBN_SELCHANGE(IDC_OCT3, OnSelchangeOct3)
	ON_LBN_SELCHANGE(IDC_OCT4, OnSelchangeOct4)
	ON_LBN_SELCHANGE(IDC_OCT5, OnSelchangeOct5)
	ON_LBN_SELCHANGE(IDC_OCT6, OnSelchangeOct6)
	ON_LBN_SELCHANGE(IDC_OCT7, OnSelchangeOct7)
	ON_LBN_SELCHANGE(IDC_OCT8, OnSelchangeOct8)
	ON_LBN_SELCHANGE(IDC_OCT9, OnSelchangeOct9)
	ON_LBN_SELCHANGE(IDC_LISTTRANSPOSE_NO, OnSelchangeListtransposeNo)
	ON_BN_CLICKED(IDC_CHANGE_KEY, OnChangeKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int Transpose_no::compute_notevalue(CString nstr)
{
	int val;

	CString nstr_low = nstr;
	nstr_low.MakeLower();
	int notevalue = (int)(nstr_low.GetAt(0)-'a'); // a=0, b=1, c=2, d=3, e=4, f=5, g=6
	if ((notevalue < 0) || (notevalue > 6)) return -1;

	int key = 0;
	if(nstr_low.GetAt(1)=='b')
	{
		key=-1;
	}
	else
	{
		if (nstr_low.GetAt(1)=='#')
		{
			key=+1;
		}
	}

	int octave;
	int less_zero = false;

	char och = (key==0)?nstr_low.GetAt(1):nstr_low.GetAt(2);
	if (och=='-')
	{
		less_zero = true;
		och = (key==0)?nstr_low.GetAt(2):nstr_low.GetAt(3);
	}
	octave = less_zero?-(och-'0')+2:(och-'0')+2;

	if ((octave < -2) || (octave > 8))	return -1;

	val = octave*12;
	switch( notevalue )
	{
    case 0:
        val += 9;
		break;
    case 1:
        val += 11;
		break;
    case 2:
		val += 0;
		break;
	case 3:
		val += 2;
		break;
	case 4:
		val += 4;
		break;
	case 5:
		val += 5;
		break;
	case 6:
		val += 7;
		break;
	}
	val += key;

	if ((val < 0) || (val > 127)) val = -1;
	return val;
}


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Transpose_no

void Transpose_no::OnSelchangeListtransposeNo()
{
	int i;

	tr_no = 12 - m_listtranspose_no.GetCurSel();

	for (i=0; i<16; i++)
	{
		if (((hpmfi->highlimit)[i]+tr_no>127)&&((hpmfi->lowlimit)[i]+tr_no<12))
		{
			m_listtranspose_no.SetCurSel(12);
			tr_no = 0;
		}
		if (((hpmfi->highlimit)[i]+tr_no>115)&&((hpmfi->lowlimit)[i]+tr_no<0))
		{
			m_listtranspose_no.SetCurSel(12);
			tr_no = 0;
		}
	}

	for (i=0; i<16; i++)
	{
		if (mute_val[i]) continue;
		if (!(hpmfi->mlv_list)[i].melody) continue;

		hl_val[i] = (hpmfi->highlimit)[i]+tr_no;
		ll_val[i] = (hpmfi->lowlimit)[i]+tr_no;

		if ((hl_val[i]+oct_val[i]<0)||(ll_val[i]+oct_val[i]<0))
		{
			hl_val[i]+=12;
			ll_val[i]+=12;
		}

		if ((hl_val[i]+oct_val[i]>127)||(ll_val[i]+oct_val[i]>127))
		{
			hl_val[i]-=12;
			ll_val[i]-=12;
		}

		SetDlgItemText(idc_hl[i],GlobalUtilities::compute_notestring(hl_val[i]));
		SetDlgItemText(idc_ll[i],GlobalUtilities::compute_notestring(ll_val[i]));
	}

	if (key=="")
	{
		SetDlgItemText(IDC_NEW_KEY,"");
		return;
	}

	CString scr_key;
	for (i=0; i< key.GetLength(); i++)
	{
		if (key[i]==' ') continue;
		scr_key += key[i];
	}

	new_key = GlobalUtilities::transpose_key_signature(scr_key,tr_no);
	tonart = GlobalUtilities::get_resource_string(IDS_KeySignature);
	SetDlgItemText(IDC_NEW_KEY,tonart+new_key);

}

void Transpose_no::OnOK()
{
	int i;

	// Ist eine Transpose-Nummer angewählt?
	int gcs = m_listtranspose_no.GetCurSel( );
	if (gcs == LB_ERR) return;
	tr_no = 12-gcs;

	OnCheck();

	for (i=0; i<16; i++)
	{
		mute_val[i] = mute[i]->GetCheck()==1?true:false;
		(hpmfi->new_mute)[i] = mute_val[i];
	}

	for (i=0; i<16; i++)
	{
		// HP MIDIFILE
		(hpmfi->new_highlimit)[i] = hl_val[i]+oct_val[i];
		(hpmfi->new_lowlimit)[i] = ll_val[i]+oct_val[i];
	}

	for (i=0; i<16; i++)
	{
		(hpmfi->transpose_delta_list)[i] = tr_no+oct_val[i];
	}

//	hpmfi->first_key = new_key;
	is_transpose_chords = m_transpose_chords_check.GetCheck()==1;

	if (m_pToolTip != NULL)
	{
		delete m_pToolTip;
		m_pToolTip = NULL;
	}

	EndDialog(tr_no);
}

void Transpose_no::OnCancel()
{
	if (m_pToolTip != NULL)
	{
		delete m_pToolTip;
		m_pToolTip = NULL;
	}

	EndDialog(20);
}

BOOL Transpose_no::PreTranslateMessage(MSG* pMsg)
{
	if (NULL != m_pToolTip)
	{
		m_pToolTip->RelayEvent(pMsg);
	}

	return CDialog::PreTranslateMessage(pMsg);
}


BOOL Transpose_no::OnInitDialog()
{
	CDialog::OnInitDialog();
	int i, k;
	int chan;

	hpmfi->update_low_high_limit_lists();
	for (i=0; i<16; i++)
	{
		local_hpmfi_mute[i] = hpmfi->mute[i];
	}

	const CString listelement[25] =
	{"+12","+11","+10"," +9"," +8"," +7"," +6"," +5"," +4"," +3"," +2"," +1","  0",
	" -1"," -2"," -3"," -4"," -5"," -6"," -7"," -8"," -9","-10","-11","-12"};

	for (i=0; i<25;i++)
	{
		m_listtranspose_no.AddString(listelement[i]);
	}

	m_listtranspose_no.SetCurSel(12); // Select transpose-no 0
	tr_no = 0;
	key = hpmfi->first_key;
	while (key.GetLength()<6) key += ' ';

	m_transpose_chords_check.SetCheck(1);
	is_transpose_chords = true;

	new_key = key;

	// Set channel number text
	SetDlgItemText(IDC_TEXT_CHANNEL,GlobalUtilities::get_resource_string(IDS_CHANNEL));
	SetDlgItemText(IDC_TEXT_MUTE,GlobalUtilities::get_resource_string(IDS_MUTE));
	SetDlgItemText(IDC_OCT_LIST,GlobalUtilities::get_resource_string(IDS_PLUS_OCTAVE));
	SetDlgItemText(IDC_TYPETEXT,"Voice");
	SetDlgItemText(IDC_TEXT_HIGH_LIMIT,GlobalUtilities::get_resource_string(IDS_HIGH_LIMIT));
	SetDlgItemText(IDC_TEXT_LOW_LIMIT,GlobalUtilities::get_resource_string(IDS_LOW_LIMIT));
	SetDlgItemText(IDC_TEXT_TRANSPOSE_NO,GlobalUtilities::get_resource_string(IDS_TRANSPOSE_NO));


	SetDlgItemText(IDC_TEXT_1,"1");
	SetDlgItemText(IDC_TEXT_2,"2");
	SetDlgItemText(IDC_TEXT_3,"3");
	SetDlgItemText(IDC_TEXT_4,"4");
	SetDlgItemText(IDC_TEXT_5,"5");
	SetDlgItemText(IDC_TEXT_6,"6");
	SetDlgItemText(IDC_TEXT_7,"7");
	SetDlgItemText(IDC_TEXT_8,"8");
	SetDlgItemText(IDC_TEXT_9,"9");
	SetDlgItemText(IDC_TEXT_10,"10");
	SetDlgItemText(IDC_TEXT_11,"11");
	SetDlgItemText(IDC_TEXT_12,"12");
	SetDlgItemText(IDC_TEXT_13,"13");
	SetDlgItemText(IDC_TEXT_14,"14");
	SetDlgItemText(IDC_TEXT_15,"15");
	SetDlgItemText(IDC_TEXT_16,"16");

	// initialize mute-array

	mute[0] = &m_mute1;
	mute[1] = &m_mute2;
	mute[2] = &m_mute3;
	mute[3] = &m_mute4;
	mute[4] = &m_mute5;
	mute[5] = &m_mute6;
	mute[6] = &m_mute7;
	mute[7] = &m_mute8;
	mute[8] = &m_mute9;
	mute[9] = &m_mute10;
	mute[10] = &m_mute11;
	mute[11] = &m_mute12;
	mute[12] = &m_mute13;
	mute[13] = &m_mute14;
	mute[14] = &m_mute15;
	mute[15] = &m_mute16;

	// intialize highlimit-array

	hl[0] = &m_hl1;
	hl[1] = &m_hl2;
	hl[2] = &m_hl3;
	hl[3] = &m_hl4;
	hl[4] = &m_hl5;
	hl[5] = &m_hl6;
	hl[6] = &m_hl7;
	hl[7] = &m_hl8;
	hl[8] = &m_hl9;
	hl[9] = &m_hl10;
	hl[10] = &m_hl11;
	hl[11] = &m_hl12;
	hl[12] = &m_hl13;
	hl[13] = &m_hl14;
	hl[14] = &m_hl15;
	hl[15] = &m_hl16;

	// initialize lowlimit-array

	ll[0] = &m_ll1;
	ll[1] = &m_ll2;
	ll[2] = &m_ll3;
	ll[3] = &m_ll4;
	ll[4] = &m_ll5;
	ll[5] = &m_ll6;
	ll[6] = &m_ll7;
	ll[7] = &m_ll8;
	ll[8] = &m_ll9;
	ll[9] = &m_ll10;
	ll[10] = &m_ll11;
	ll[11] = &m_ll12;
	ll[12] = &m_ll13;
	ll[13] = &m_ll14;
	ll[14] = &m_ll15;
	ll[15] = &m_ll16;

	// initialize oct-array

	oct[0] = &m_oct1;
	oct[1] = &m_oct2;
	oct[2] = &m_oct3;
	oct[3] = &m_oct4;
	oct[4] = &m_oct5;
	oct[5] = &m_oct6;
	oct[6] = &m_oct7;
	oct[7] = &m_oct8;
	oct[8] = &m_oct9;
	oct[9] = &m_oct10;
	oct[10] = &m_oct11;
	oct[11] = &m_oct12;
	oct[12] = &m_oct13;
	oct[13] = &m_oct14;
	oct[14] = &m_oct15;
	oct[15] = &m_oct16;

// initialize IDC Typetext-array

	idc_type[0] = IDC_TYPE1;
	idc_type[1] = IDC_TYPE2;
	idc_type[2] = IDC_TYPE3;
	idc_type[3] = IDC_TYPE4;
	idc_type[4] = IDC_TYPE5;
	idc_type[5] = IDC_TYPE6;
	idc_type[6] = IDC_TYPE7;
	idc_type[7] = IDC_TYPE8;
	idc_type[8] = IDC_TYPE9;
	idc_type[9] = IDC_TYPE10;
	idc_type[10] = IDC_TYPE11;
	idc_type[11] = IDC_TYPE12;
	idc_type[12] = IDC_TYPE13;
	idc_type[13] = IDC_TYPE14;
	idc_type[14] = IDC_TYPE15;
	idc_type[15] = IDC_TYPE16;

	// initialize IDC highlimit-array

	idc_hl[0] = IDC_EDIT_HL1;
	idc_hl[1] = IDC_EDIT_HL2;
	idc_hl[2] = IDC_EDIT_HL3;
	idc_hl[3] = IDC_EDIT_HL4;
	idc_hl[4] = IDC_EDIT_HL5;
	idc_hl[5] = IDC_EDIT_HL6;
	idc_hl[6] = IDC_EDIT_HL7;
	idc_hl[7] = IDC_EDIT_HL8;
	idc_hl[8] = IDC_EDIT_HL9;
	idc_hl[9] = IDC_EDIT_HL10;
	idc_hl[10] = IDC_EDIT_HL11;
	idc_hl[11] = IDC_EDIT_HL12;
	idc_hl[12] = IDC_EDIT_HL13;
	idc_hl[13] = IDC_EDIT_HL14;
	idc_hl[14] = IDC_EDIT_HL15;
	idc_hl[15] = IDC_EDIT_HL16;

	// initialize IDC Lowlimit-array

	idc_ll[0] = IDC_EDIT_LL1;
	idc_ll[1] = IDC_EDIT_LL2;
	idc_ll[2] = IDC_EDIT_LL3;
	idc_ll[3] = IDC_EDIT_LL4;
	idc_ll[4] = IDC_EDIT_LL5;
	idc_ll[5] = IDC_EDIT_LL6;
	idc_ll[6] = IDC_EDIT_LL7;
	idc_ll[7] = IDC_EDIT_LL8;
	idc_ll[8] = IDC_EDIT_LL9;
	idc_ll[9] = IDC_EDIT_LL10;
	idc_ll[10] = IDC_EDIT_LL11;
	idc_ll[11] = IDC_EDIT_LL12;
	idc_ll[12] = IDC_EDIT_LL13;
	idc_ll[13] = IDC_EDIT_LL14;
	idc_ll[14] = IDC_EDIT_LL15;
	idc_ll[15] = IDC_EDIT_LL16;

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


	for (i=0; i<16; i++)
	{
//		if (!(hpmfi->mute)[i])
		if (!local_hpmfi_mute[i])
		{
			mute_val[i] = false;
			if((hpmfi->mlv_list)[i].melody)
			{
				ll_val[i] = (hpmfi->lowlimit)[i];
				if (ll_val[i]!=127) // avoid no melody notes
				{
					SetDlgItemText(idc_ll[i],GlobalUtilities::compute_notestring(ll_val[i]));
				}

				hl_val[i] = (hpmfi->highlimit)[i];
				if (hl_val[i]!=0) // avoid no melody notes
				{
					SetDlgItemText(idc_hl[i],GlobalUtilities::compute_notestring(hl_val[i]));
				}

				if (((ll_val[i]==127) || (hl_val[i]==0)) && (hpmfi->mlv_list[i]).is_mega)
				{	// mega voice without melody notes
					ll[i]->EnableWindow(false);
					hl[i]->EnableWindow(false);
					oct[i]->EnableWindow(false);
//					hpmfi->mute[i] = false;
					local_hpmfi_mute[i] = false;
					mute_val[i] = true;
				}
			}
			else
			{
				ll[i]->EnableWindow(false);
				hl[i]->EnableWindow(false);
				oct[i]->EnableWindow(false);
			}

			ll[i]->LimitText(4);
			hl[i]->LimitText(4);

			if ((hpmfi->mlv_list)[i].melody && !((((ll_val[i]==127) || (hl_val[i]==0)) && (hpmfi->mlv_list[i]).is_mega)))
			{
				for (k=11; k<14; k++)
				{
					oct[i]->AddString(listelement[k]);
				}
				oct[i]->SetCurSel(1); // Select octave-no 0
			}
		}
		else
		{
			mute_val[i] = true;
			ll[i]->EnableWindow(false);
			hl[i]->EnableWindow(false);
			oct[i]->EnableWindow(false);
		}

		if (mute_val[i] && !(hpmfi->mlv_list)[i].is_mega)
		{
			SetDlgItemText(idc_type[i],"");
		}
		else
		{
			SetDlgItemText(idc_type[i],(hpmfi->patchname)[i]);
		}

		oct_val[i] = 0; // This is the inital value in ListBox
	}

	for (i=0; i<16; i++)
	{
//		mute[i]->SetCheck(!(hpmfi->mute)[i]);
		mute[i]->SetCheck(!local_hpmfi_mute[i]); 
		mute[i]->EnableWindow(false);
	}

	tonart = GlobalUtilities::get_resource_string(IDS_KeySignature);
	if (new_key != "")
	{
		SetDlgItemText(IDC_NEW_KEY,tonart+new_key);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void Transpose_no::OnCheck()
{
	int gcs = m_listtranspose_no.GetCurSel( );
	if (gcs == LB_ERR)
	{
		return;
	}

	// tr_no already O.K.

	// Mute always O.K.

	int i;
	CString hl_str[16], ll_str[16];

	for (i=0; i<16; i++)
	{
		if (mute_val[i]) continue;
		if (!(hpmfi->mlv_list)[i].melody) continue;

		GetDlgItemText(idc_hl[i],hl_str[i]);
		nvh[i] = compute_notevalue(hl_str[i]);
		if (nvh[i]==-1)
		{ // Syntax error, use initial value
			nvh[i] = hl_val[i];
		}

		GetDlgItemText(idc_ll[i],ll_str[i]);
		nvl[i] = compute_notevalue(ll_str[i]);
		if (nvl[i]==-1)
		{ // Syntax error, use initial value
			nvl[i] = ll_val[i];
		}

		if (nvh[i]+oct_val[i]< 0)
		{
			nvh[i] += 12;
		}
		if (nvl[i]+oct_val[i]< 0)
		{
			nvl[i] += 12;
		}

		if (nvh[i]+oct_val[i]> 127)
		{
			nvh[i] -= 12;
		}
		if (nvl[i]+oct_val[i]> 127)
		{
			nvl[i] -= 12;
		}

		int orig_interval = ((hpmfi->highlimit)[i])-((hpmfi->lowlimit)[i]);
		int new_interval = nvh[i]-nvl[i];
		if (new_interval < 0)
		{
			int scr = nvh[i];
			nvh[i] = nvl[i];
			nvl[i] = scr;
			new_interval = -new_interval;
		}

		if (orig_interval>=11)
		{	// > 1 octave
			if (new_interval<11)
			{ // new less 1 octave
				nvh[i] = hl_val[i]; // use old interval
				nvl[i] = ll_val[i];
			}
		}
		else
		{
			if (nvl[i]+oct_val[i]>ll_val[i]) nvh[i]=nvl[i]+12;
			if (nvh[i]+oct_val[i]<hl_val[i]) nvl[i]=nvh[i]-12;
			if ((nvh[i]+oct_val[i]< 0) || (nvl[i]+oct_val[i]< 0))
			{
				nvh[i] += 12;
				nvl[i] += 12;
			}

			if ((nvh[i]+oct_val[i]> 127) || (nvl[i]+oct_val[i] > 127))
			{
				nvh[i] -= 12;
				nvl[i] -= 12;
			}

		}

		ll_val[i] = nvl[i];
		hl_val[i] = nvh[i];
		SetDlgItemText(idc_hl[i],GlobalUtilities::compute_notestring(hl_val[i]));
		SetDlgItemText(idc_ll[i],GlobalUtilities::compute_notestring(ll_val[i]));
	}
}


void Transpose_no::eval_sel_oct(int chan)
{
	oct_val[chan] = (1 - oct[chan]->GetCurSel())*12;
	int new_hl = hl_val[chan]+oct_val[chan];
	int new_ll = ll_val[chan]+oct_val[chan];

	if ((new_hl<0)||(new_ll<0)||(new_hl>127)||(new_ll>127))
	{
		oct[chan]->SetCurSel(1); // Selection not possible, set to octave-no 0
		oct_val[chan] = 0;
	}
	else
	{
		OnCheck();
	}
}

bool Transpose_no::transpose_chords()
{
	return is_transpose_chords;
}

CString Transpose_no::send_new_key()
{
	int i;
	CString nk = "";
	for (i=0; i<new_key.GetLength(); i++)
	{
		if (new_key[i]==' ') continue;
		nk += new_key[i];
	}
	return nk;
}

void Transpose_no::OnSelchangeOct1()
{
	eval_sel_oct(0);
}

void Transpose_no::OnSelchangeOct10()
{
	eval_sel_oct(9);
}

void Transpose_no::OnSelchangeOct11()
{
	eval_sel_oct(10);
}

void Transpose_no::OnSelchangeOct12()
{
	eval_sel_oct(11);
}

void Transpose_no::OnSelchangeOct13()
{
	eval_sel_oct(12);
}

void Transpose_no::OnSelchangeOct14()
{
	eval_sel_oct(13);
}

void Transpose_no::OnSelchangeOct15()
{
	eval_sel_oct(14);
}

void Transpose_no::OnSelchangeOct16()
{
	eval_sel_oct(15);
}

void Transpose_no::OnSelchangeOct2()
{
	eval_sel_oct(1);
}

void Transpose_no::OnSelchangeOct3()
{
	eval_sel_oct(2);
}

void Transpose_no::OnSelchangeOct4()
{
	eval_sel_oct(3);
}

void Transpose_no::OnSelchangeOct5()
{
	eval_sel_oct(4);
}

void Transpose_no::OnSelchangeOct6()
{
	eval_sel_oct(5);
}

void Transpose_no::OnSelchangeOct7()
{
	eval_sel_oct(6);
}

void Transpose_no::OnSelchangeOct8()
{
	eval_sel_oct(7);
}

void Transpose_no::OnSelchangeOct9()
{
	eval_sel_oct(8);
}

// Static const data

const CString Transpose_no::keylistelement[16] =
	{"**","Cb","C ","C#","Db","D ","Eb","E ","F ","F#","Gb","G ","Ab","A ","Bb","B "};
const CString Transpose_no::majminlistelement[3] = {"***","min","maj"};


void Transpose_no::OnChangeKey()
{
	int i;
	m_listtranspose_no.SetCurSel(12); // Select transpose-no 0
	tr_no = 0;

	CString key, type;
	type="maj";
	for (i=0; i<new_key.GetLength(); i++)
	{
		if (new_key[i]==' ')
		{
			break;
		}
		if (new_key[i]=='m')
		{
			type="min";
			break;
		}
		key = new_key[i];
	}
	if (key.GetLength()<2)
	{
		key += ' ';
	}

	CChangeKeyDlg dlg;
	dlg.hpmfi = hpmfi;
	dlg.init_key = key;
	dlg.init_type = type;
	if (dlg.DoModal() == -1) return;
	new_key = dlg.new_key;
	key = new_key;
	tonart = GlobalUtilities::get_resource_string(IDS_KeySignature);
	SetDlgItemText(IDC_NEW_KEY,tonart+new_key);
}
