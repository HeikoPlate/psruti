// XgEffects.h: Schnittstelle für die Klasse XgEffects.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XGEFFECTS_H__E917A300_83B7_4EB1_95C7_1BE57FADEFE1__INCLUDED_)
#define AFX_XGEFFECTS_H__E917A300_83B7_4EB1_95C7_1BE57FADEFE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyArrays.h"

class XgEffects  
{
public:
	XgEffects(CString file_path);
	virtual ~XgEffects();
	bool ReadEffectFile(CString instrument);
	bool get_instruments(CArray<CString,CString> *instruments);
	bool reverb_effect_type( int DataMSB, int DataLSB, 
								int *act_reverb_param_list_no,
								int *act_reverb_type_msb,
								int *act_reverb_type_lsb,
								CString *act_type);
	CString reverb_data_text(int AdrH, int AdrL, int DataMSB, int DataLSB, int act_reverb_param_list_no);

	bool chorus_effect_type( int DataMSB, int DataLSB, 
								int *act_chorus_param_list_no,
								int *act_chorus_type_msb,
								int *act_chorus_type_lsb,
								CString *act_type);
	CString chorus_data_text(int AdrH, int AdrL, int DataMSB, int DataLSB, int act_chorus_param_list_no);

	bool dsp_effect_type(	int DataMSB, int DataLSB, int AdrM,
							int *act_dsp_param_list_no,
							int *act_dsp_type_msb,
							int *act_dsp_type_lsb,
							CString *act_type);	

	CString dsp_data_text(	int DataMSB, int DataLSB, int AdrH, int AdrM, int AdrL, 
							int act_dsp_param_list_no_eff_block);


private:

	CStdioFile data_file;

	CString get_cstring_from_line(CString line, int param_no);
	int get_int_from_line (CString line, int param_no);
	CString get_cstring_from_line(CString line, int pos, int *next_pos);

	DataReverbArray data_reverb_array;
	DataChorusArray data_chorus_array;
	DataDspsArray data_dsps_array;
	DataDspsArray data_dsp1_array;
	EffectParameterArray eff_param_array;
	EffectTableArray eff_table_array;

	CString effect_data_file;
	CArray<CString,CString> instruments;

	CString selected_instrument_label;
	CString selected_instrument_end_label;
	int get_next_param_table_no();
	int get_next_table_no();


	static const CString instrument_label;
	static const CString end_instrument_label;
	static const CString data_reverb_label;
	static const CString end_data_reverb_label;
	static const CString data_chorus_label;
	static const CString end_data_chorus_label;
	static const CString data_dsps_label;
	static const CString end_data_dsps_label;
	static const CString data_dsp1_label;
	static const CString end_data_dsp1_label;
	static const CString parameter_listen_label;
	static const CString parameter_table_label_start;
	static const CString end_parameter_table_label_start;
	static const CString table_listen_label;
	static const CString end_table_listen_label;

};

#endif // !defined(AFX_XGEFFECTS_H__E917A300_83B7_4EB1_95C7_1BE57FADEFE1__INCLUDED_)
