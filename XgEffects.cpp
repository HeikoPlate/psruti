// XgEffects.cpp: Implementierung der Klasse XgEffects.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "XgEffects.h"
#include "GlobalUtilities.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


// Statics
const CString XgEffects::instrument_label =			"[Instrumente]";
const CString XgEffects::end_instrument_label =		"[EndInstrumente]";
const CString XgEffects::data_reverb_label =		"[DataReverb]";
const CString XgEffects::end_data_reverb_label =	"[EndDataReverb]";
const CString XgEffects::data_chorus_label =		"[DataChorus]";
const CString XgEffects::end_data_chorus_label =	"[EndDataChorus]";
const CString XgEffects::data_dsps_label =			"[DataDSPs]";
const CString XgEffects::end_data_dsps_label =		"[EndDataDSPs]";
const CString XgEffects::data_dsp1_label =			"[DataDSP1]";
const CString XgEffects::end_data_dsp1_label =		"[EndDataDSPs]";
const CString XgEffects::parameter_listen_label =				"[ParameterListen]";
const CString XgEffects::parameter_table_label_start =			"[ParameterTabelle";
const CString XgEffects::end_parameter_table_label_start =		"[EndParameter";
const CString XgEffects::table_listen_label =					"[TableListen]";			
const CString XgEffects::end_table_listen_label =				"[EndTableListen]";



//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

XgEffects::XgEffects(CString file_path)
{
	effect_data_file = file_path;
}

XgEffects::~XgEffects()
{

}

bool XgEffects::get_instruments(CArray<CString,CString> *instruments)
{
	if (!data_file.Open(effect_data_file, CFile::modeRead))   
	{
		return false;
	}

	CString line;
	bool found;
	CString searchstring;
	CString instrument_line;
		
	// Look for source

	found = false;	
	searchstring = instrument_label;
	data_file.SeekToBegin();
	while (data_file.ReadString(line))
	{
		if (line == searchstring)
		{
			if (data_file.ReadString(line)) // get string of instruments				
			{
				found = true;
			}
			break;
		}
	}
	instrument_line = found?line:"";
	if (!found)
	{
		data_file.Close();
		return false; // error
	}
    
	searchstring = end_instrument_label;
	found = false;
	while (data_file.ReadString(line))
	{
		if (line == searchstring)
		{
			found = true;
			break;
		}
		else
		{
			instrument_line += line;
		}
	}
	if (!found)
	{
		data_file.Close();
		return false; // error
	}

	int pos = 0;
	int next_pos = -1;
	CString instrument;
	while (pos >= 0)
	{
		instrument = get_cstring_from_line(instrument_line, pos, &next_pos);
		if (instrument=="")
		{
			break;
		}
		instruments->Add(instrument);
		pos = next_pos;
	}
	data_file.Close();
	return true;;
}


bool XgEffects::ReadEffectFile(CString instrument)
{
	
	if (!data_file.Open(effect_data_file, CFile::modeRead))   
	{
		return false;
	}

	CString line;
	bool found;
	CString searchstring;
	CString effect;
	int msb, lsb, epl;
	CString type;
		
	// Look for source

	selected_instrument_label = '['+instrument+']';
	selected_instrument_end_label = "[End"+instrument+']';



	searchstring = selected_instrument_label;

	found = false;
	while (data_file.ReadString(line))
	{
		if (line == searchstring)
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		data_file.Close();
		return false; // error
	}

	/******** analyze Data Reverb List ************************************/

	searchstring = data_reverb_label;
	found = false;
	while (data_file.ReadString(line))
	{
		if (line == searchstring)
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		data_file.Close();
		return false; // error
	}

	line = "";

	while (line != end_data_reverb_label)
	{
		data_file.ReadString(line);

		msb = get_int_from_line(line,3);
		lsb = get_int_from_line(line,4);
		type = get_cstring_from_line(line,1);
		epl = get_int_from_line(line,5);

		data_reverb_array.add(msb, lsb, type, epl);
	}

	/******** analyze Data Chorus List ************************************/

	data_file.SeekToBegin();
	searchstring = selected_instrument_label;;
	
	while (data_file.ReadString(line))
	{
		if (line == searchstring)
		{
			break;
		}
	}

	searchstring = data_chorus_label;
	found = false;
	while (data_file.ReadString(line))
	{
		if (line == searchstring)
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		data_file.Close();
		return false; // error
	}

	line = "";

	while (line != end_data_chorus_label)
	{
		data_file.ReadString(line);

		msb = get_int_from_line(line,3);
		lsb = get_int_from_line(line,4);
		type = get_cstring_from_line(line,1);
		epl = get_int_from_line(line,5);

		data_chorus_array.add(msb, lsb, type, epl);
	}

	/******** analyze Data DSPs List ************************************/

	data_file.SeekToBegin();
	searchstring = selected_instrument_label;
	
	while (data_file.ReadString(line))
	{
		if (line == searchstring)
		{
			break;
		}
	}

	searchstring = data_dsps_label;
	found = false;
	while (data_file.ReadString(line))
	{
		if (line == searchstring)
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		data_file.Close();
		return false; // error
	}

	line = "";

	while (line != end_data_dsps_label)
	{
		data_file.ReadString(line);

		msb = get_int_from_line(line,3);
		lsb = get_int_from_line(line,4);
		type = get_cstring_from_line(line,1);
		epl = get_int_from_line(line,5);

		data_dsps_array.add(msb, lsb, type, epl);
	}

	/******** analyze Data DSP1 List ************************************/

	data_file.SeekToBegin();
	searchstring = selected_instrument_label;
	
	while (data_file.ReadString(line))
	{
		if (line == searchstring)
		{
			break;
		}
	}

	searchstring = data_dsp1_label;
	found = false;
	while (data_file.ReadString(line))
	{
		if (line == searchstring)
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		data_file.Close();
		return false; // error
	}

	line = "";

	while (line != end_data_dsp1_label)
	{
		data_file.ReadString(line);

		msb = get_int_from_line(line,3);
		lsb = get_int_from_line(line,4);
		type = get_cstring_from_line(line,1);
		epl = get_int_from_line(line,5);

		data_dsp1_array.add(msb, lsb, type, epl);
	}


	/******** analyze Param Tables ************************************/

	
	while (true)
	{
		int table_index = 0;
		bool end_table = false;
		int len = 13;
		int table_no = get_next_param_table_no();
		if (table_no == -1) break;
		
		EFF_PARAM_ELEM *table = new EFF_PARAM_ELEM[16]; 

		// fill table with data
		while (true)
		{
			data_file.ReadString(line);
			if ((line.Left(len)=="[EndParameter")||(table_index > 15))
			{
				end_table = true;
				break;
			}

			CString name = get_cstring_from_line(line,1);
			table[table_index].name = (name=="-1")?"":name;
			table[table_index].data_list = get_int_from_line(line,5);
			table_index++;
		}
		if (end_table)
		{
			eff_param_array.add(table_no, table);
			continue;
		}
	}

	/******** analyze Table-Listen ************************************/

	searchstring = table_listen_label;
	while (true)
	{
		data_file.ReadString(line);
		if (line == table_listen_label)
		{
			break;
		}
	}

//	int max_table_length = 0;

	while (true)
	{
		int table_index = 0;
		int old_table_index = 0;
		bool end_table = false;
		int len = 9;
		
		int table_no = get_next_table_no();
		if (table_no == -1) break;
		CString *table = eff_table_array.add(table_no);

		data_file.ReadString(line);

		// fill table with data
		while (true)
		{
			if (line.Left(len)=="[EndTable")
			{
				end_table = true;
				break;
			}
			CString name = get_cstring_from_line(line,table_index);
			if (name!="")
			{
				table[table_index+old_table_index]= name;
				table_index++;
//				if (table_index >= max_table_length)
//				{
//					max_table_length = table_index;
//				}
			}
			else
			{
				data_file.ReadString(line);
				old_table_index = table_index;
				table_index = 0;
			}
		}
		if (end_table)
		{
			continue;
		}

	}
//	CString r;
//	r.Format("max_table_length = %i",max_table_length);
//	MessageBox(NULL,r,"",0);
	return true;
}


CString XgEffects::get_cstring_from_line(CString line, int param_no)
{
	CString empty = "";
	int act_no = 0;
	int next_pos;

	int i;
	
	if (param_no == 0)
	{
		return get_cstring_from_line(line, 0, &next_pos);
	}

	int par_no = 0;

	for (i=0; i<line.GetLength(); i++)
	{
		if (line[i] == ';')
		{
			act_no++;
			if (act_no == param_no)
			{
				return get_cstring_from_line(line, i+1, &next_pos);
			}
		}
	}
	return empty;
}


CString XgEffects::get_cstring_from_line(CString line, int pos, int *next_pos)
{
	CString param;
	int i;
	char ch;
	for (i=pos; i<line.GetLength(); i++)
	{
		ch = line[i];
		if ((ch == ' ') && (param == ""))
		{
			continue;
		}

		if (ch == ';')
		{
			*next_pos = i+1;

			break;
		}
		else
		{
			param += ch;
		}
	}
	return param;
}

int XgEffects::get_int_from_line(CString line, int param_no)
{
	char ch;
	int value = 0;
	bool minus = false;
	int i;
	int act_param_no = 0;
	int act_pos = 0;

	for (i=0; i<line.GetLength(); i++)
	{
		if (act_param_no == param_no)
		{
			break;
		}
		else
		{
			ch = line[i];
			if (ch == ';')
			{
				act_pos = i+1;
				act_param_no++;
			}
		}
	}
	
	for (i=act_pos; i<line.GetLength(); i++)
	{
		ch = line[i];
		if (ch == ' ')
		{
			continue;
		}

		if (ch == '-')
		{
			minus = true;
			continue;
		}

		if (ch == ';')
		{
			break;
		}

		if (value==0)
		{
			value = (int)ch - (int)'0';
		}
		else
		{
			value = 10*value + ((int)ch - (int)'0');
		}
	}

	if (minus)
	{
		value = -value;
	}

	return value;
}

int XgEffects::get_next_param_table_no()
{
	CString line;
	int i;
	int table_no = 0;
	int len_start = 17;
	char ch;

	while (data_file.ReadString(line))
	{
		if (line.Left(len_start)=="[ParameterTabelle")
		{
			for (i=len_start; i<line.GetLength(); i++)
			{
				ch = line[i];
				if (ch==']')
				{
					break;
				}
				if(((int)ch<(int)'0')||((int)ch>(int)'9'))
				{
					return -1;
				}
				table_no = table_no*10+ (int)ch - (int)'0';
			}
			return table_no;
		}
	}
	return -1;
}

int XgEffects::get_next_table_no()
{
	CString line;
	int i;
	int table_no = 0;
	int len_start = 6;
	int ch;

	while (data_file.ReadString(line))
	{
		if (line.Left(len_start)=="[Table")
		{
			for(i=len_start; i<line.GetLength();i++)
			{
				ch = line[i];
				if (ch==']')
				{
					break;
				}
				if(((int)ch<(int)'0')||((int)ch>(int)'9'))
				{
					return -1;
				}
				table_no = table_no*10+ (int)ch - (int)'0';
			}
			return table_no;
		}
	}
	return -1;
}

//**************************************************************************
//*
//*		reverb_effect_type
//*		Analyze Effect Type. DataMSB and DataLSB of Address 02 01 00
//*
//**************************************************************************

bool XgEffects::reverb_effect_type(int DataMSB, int DataLSB, 
									  int *act_reverb_param_list_no,
									  int *act_reverb_type_msb,
									  int *act_reverb_type_lsb,
									  CString *act_type)
{
	*act_reverb_param_list_no = -1;
	*act_reverb_type_msb = -1;
	*act_reverb_type_lsb = -1;
	*act_type = "Unknown Type";

	int i;
	int msb, lsb, epl;
	CString type;
	bool found = false;

	for (i = 0; i< data_reverb_array.get_length(); i++)
	{
		data_reverb_array.get(i, &msb, &lsb, &type, &epl);
		if ((DataMSB != msb) ||  (DataLSB != lsb))
		{
			continue;
		}

		*act_reverb_param_list_no = epl;			
		found = true;
		break;
	}
	if (found)
	{
		*act_reverb_type_msb = DataMSB;
		*act_reverb_type_lsb = DataLSB;
		*act_type = type;
	}
	return found;
}

//**************************************************************************
//*
//*		chorus_effect_type
//*		Analyze Effect Type. DataMSB and DataLSB of Address 02 01 20
//*
//**************************************************************************

bool XgEffects::chorus_effect_type(	int DataMSB, int DataLSB, 
										int *act_chorus_param_list_no,
										int *act_chorus_type_msb,
										int *act_chorus_type_lsb,
										CString *act_type)
{
	CString type = "Unknown Type ";

	int i;
	int msb, lsb, epl;

	bool found = false;
	*act_chorus_param_list_no = -1;
	*act_chorus_type_msb = -1;
	*act_chorus_type_lsb = -1;

	for (i = 0; data_chorus_array.get_length(); i++)
	{
		data_chorus_array.get(i, &msb, &lsb, &type, &epl);

		if ((DataMSB != msb) ||  (DataLSB != lsb))
		{
			continue;
		}

		*act_chorus_param_list_no = epl;			
		found = true;
		break;

	}
	*act_chorus_type_msb = DataMSB;
	*act_chorus_type_lsb = DataLSB;
	*act_type = type;

	return found;
}


//**************************************************************************
//*
//*		dsp_effect_type
//*		Analyze Effect Type. DataMSB and DataLSB of Address 03 0n 00, 02 01 40
//*
//**************************************************************************

bool XgEffects::dsp_effect_type( int DataMSB, int DataLSB, int AdrM,
								    int *act_dsp_param_list_no,
								    int *act_dsp_type_msb,
									int *act_dsp_type_lsb,
									CString *act_type)
{

	CString type = "Unknown Type ";

	int i;
	int msb, lsb, epl;

	bool found = false;

	for (i = 0; i < data_dsps_array.get_length(); i++)
	{
		data_dsps_array.get(i,&msb,&lsb,&type,&epl);

		if ((DataMSB != msb) ||  (DataLSB != lsb))
		{
			continue;
		}
		found = true;
		break;
	}
		
#define NO_DSP_BLOCKS 32 // ???
	if ((AdrM < NO_DSP_BLOCKS) && (AdrM >= 0))
	{

		*act_dsp_type_msb = DataMSB;
		*act_dsp_type_lsb = DataLSB;
		*act_dsp_param_list_no = found? epl: -1;

	}
	if (type == "")
	{
		type = "Unknown Type ";
	}

	*act_type = type;

	return found;
}


//**************************************************************************
//*
//*		reverb_data_text
//*		analyze reverb parameter and data
//*		Address 02 01 00... (EFFECT 1 Reverb)
//*
//**************************************************************************

CString XgEffects::reverb_data_text(int AdrH, int AdrL, int DataMSB, int DataLSB, int act_reverb_param_list_no)
{
	CString text = "";
	CString simple_text;
	CString par_text;
	CString data_text;
	int eff_data;

	int par_no;
	int data_list_no;

	simple_text.Format(" Par %2.1x, Data %2.1x ",AdrL, DataMSB);

	// effect parameter list number = act_reverb_param_list_no
	
	if ((act_reverb_param_list_no < 0) ||
		(act_reverb_param_list_no >= eff_param_array.get_length()))
	{
		text += simple_text;
		return text;
	}

	// get effect parameter list
	EFF_PARAM_ELEM *epl = eff_param_array.get(act_reverb_param_list_no);

	// get reverb parameter no
	bool result = GlobalUtilities::get_sysex_parno_effectno(AdrH, AdrL, DataMSB, DataLSB, &par_no, &eff_data);

	
	if ((!result) || (epl == NULL))
	{
		text += simple_text;
		return text;
	}

	par_no--; // par lists start with index 0

	// get parameter text and data list number
	par_text = (epl[par_no]).name;
	data_list_no = (epl[par_no]).data_list;
	if (par_text=="")
	{
		text += simple_text;
		return text;
	}
	else
	{
		text += par_text;
	}

	if ((data_list_no<0)||(data_list_no>=eff_table_array.get_length()))
	{
		if (data_list_no == -1)
		{
			data_text.Format(" %i",eff_data);
			text += data_text;
		}
		else
		{
			text += simple_text;
		}
		return text;
	}

	if ((data_list_no==50) ||
		(data_list_no==51) ||
		(data_list_no==52) ||
		(data_list_no==53) ||
		(data_list_no==59) ||
		(data_list_no==72) )
	{
		float data = (float)eff_data/(float(10));
		data_text.Format(" %f ms",data);
		text += data_text;
		return text;
	}
	
	CString *edl = eff_table_array.get(data_list_no);
	int len = 250;

	if (eff_data >= len)
	{
		// no data text found
		text += simple_text;
	}
	else
	{
		if ((data_list_no==70) && (eff_data==127))
		{
			eff_data = 16;
		}
		if (( data_list_no ==71) && (eff_data==64))
		{
			eff_data = 0;
		}
		if (( data_list_no ==71) && (eff_data==127))
		{
			eff_data = 1;
		}

		data_text = edl[eff_data];
		text += (" "+data_text);
	}
	return text;
}

//**************************************************************************
//*
//*		chorus_data_text
//*		analyze chorus parameter and data
//*		Address 02 01 20... (EFFECT 1 Chorus)
//*
//**************************************************************************

CString XgEffects::chorus_data_text(int AdrH, int AdrL, int DataMSB, int DataLSB, int act_chorus_param_list_no)
{
	CString text = "";
	CString simple_text;
	CString par_text;
	CString data_text;
	int eff_data;

	int par_no;
	int data_list_no;

	simple_text.Format(" Par %2.1x, Data %2.1x ",AdrL, DataMSB);

	if ((act_chorus_param_list_no < 0) ||
		(act_chorus_param_list_no >= eff_param_array.get_length()))
	{
		text += simple_text;
		return text;
	}

	// get effect parameter list
	EFF_PARAM_ELEM *epl = eff_param_array.get(act_chorus_param_list_no);

	// get reverb parameter no
	bool result = GlobalUtilities::get_sysex_parno_effectno(AdrH, AdrL, DataMSB, DataLSB, &par_no, &eff_data);

	if (!result || (epl == NULL))
	{
		text += simple_text;
		return text;
	}

	par_no--; // par_no counts from 0

	// get parameter text and data list number
	par_text = (epl[par_no]).name;
	if (par_text=="")
	{
		text += simple_text;
		return text;
	}
	else
	{
		text += par_text;
	}

	data_list_no = (epl[par_no]).data_list;
	if ((data_list_no<0)||(data_list_no>=eff_table_array.get_length()))
	{
		if (data_list_no == -1)
		{
			data_text.Format(" %i",eff_data);
			text += data_text;
		}
		else
		{
			text += simple_text;
		}
		return text;
	}

	if ((data_list_no==50) ||
		(data_list_no==51) ||
		(data_list_no==52) ||
		(data_list_no==53) ||
		(data_list_no==59) ||
		(data_list_no==72) )
	{
		float data = (float)eff_data/(float(10));
		data_text.Format(" %f ms",data);
		text += data_text;
		return text;
	}
	
	CString *edl = eff_table_array.get(data_list_no);
	int len = 250;

	if (eff_data >= len)
	{
		// no data text found
		text += simple_text;
	}
	else
	{
		if ((data_list_no==70) && (eff_data==127))
		{
			eff_data = 16;
		}
		if (( data_list_no ==71) && (eff_data==64))
		{
			eff_data = 0;
		}
		if (( data_list_no ==71) && (eff_data==127))
		{
			eff_data = 1;
		}
		data_text = edl[eff_data];
		text += (" "+data_text);
	}
	return text;
}


//**************************************************************************
//*
//*		dsp_data_text
//*		analyze variation and dsp parameter and data
//*		Address 02 01 40...	(EFFECT 1 Variation)
//*		Address 03 0n 00... (EFFECT 2)
//*
//**************************************************************************

CString XgEffects::dsp_data_text(int DataMSB, int DataLSB, int AdrH, int AdrM, int AdrL, 
								 int act_dsp_param_list_no_eff_block)
{
	CString text = "";
	CString simple_text;
	CString par_text;
	CString data_text;

	int par_no;
	int data_list_no;
	int eff_data; // = DataMSB or 128*DataMSB + DataLSB, set later 

	int eff_block = AdrM;

	simple_text.Format("Par %2.1x, Data %2.1x ",AdrL, DataMSB);

	// effect parameter list number = act_dsp_param_list_no[eff_block];
		
	if ((act_dsp_param_list_no_eff_block < 0) ||
		(act_dsp_param_list_no_eff_block >= eff_param_array.get_length()))
	{
		text += simple_text;
		return text;
	}

	// get effect parameter list
	EFF_PARAM_ELEM *epl = eff_param_array.get(act_dsp_param_list_no_eff_block);

	// get dsp parameter no

	if (AdrH==2)
	{	// variation
		bool result = GlobalUtilities::get_sysex_parno_effectno(AdrH, AdrL, DataMSB, DataLSB, &par_no, &eff_data);
		if (!result)
		{
			text += simple_text;
			return text;
		}
	}
	else
	{	// dsp effects, address = 03 0n 00...

		bool result = GlobalUtilities::get_sysex_parno_effectno(AdrH, AdrL, DataMSB, DataLSB, &par_no, &eff_data);
		if (!result)
		{
			text += simple_text;
			return text;
		}
	}

	par_no--; // par lists start with index 0

	if (epl == NULL)
	{
			text += simple_text;
			return text;
	}


	// get parameter text and data list number
	par_text = (epl[par_no]).name;
	data_list_no = (epl[par_no]).data_list;
	if (par_text=="")
	{
		text += simple_text;
		return text;
	}
	else
	{
		text += par_text;
	}

	if ((data_list_no<0)||(data_list_no>=eff_table_array.get_length()))
	{
		text += simple_text;
		return text;
	}

	if ((data_list_no==50) ||
		(data_list_no==51) ||
		(data_list_no==52) ||
		(data_list_no==53) ||
		(data_list_no==59) ||
		(data_list_no==72) )
	{
		float data = (float)(eff_data)/(float(10));
		data_text.Format(" %4.1fms",data);
		text += data_text;
		return text;
	}
	
	CString *edl = eff_table_array.get(data_list_no);
	int len = 250;

	if (DataMSB >= len)
	{
		// no data text found
		text += simple_text;
	}
	else
	{
		if ((data_list_no==70) && (eff_data==127))
		{
			eff_data = 16;
		}
		if (( data_list_no ==71) && (eff_data==64))
		{
			eff_data = 0;
		}
		if (( data_list_no ==71) && (eff_data==127))
		{
			eff_data = 1;
		}
		data_text = edl[DataMSB];
		text += (" "+data_text);
	}
	return text;
}




	
		



