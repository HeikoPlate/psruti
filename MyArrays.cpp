// MyArrays.cpp: Implementierung der Klasse VoiceArray, ArrayChord.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyArrays.h"
#include "afx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

VoiceArray::VoiceArray()
{
	size = 1500;
	numElems = 0; // empty
	elems = new VoiceFileElement[size];
}


VoiceArray::VoiceArray(const VoiceArray& v)
{
	int i;
	size = v.size;
	numElems = v.numElems;
	elems = new VoiceFileElement[size];
	for (i=0; i<numElems; i++)
	{
		elems[i].filename = new char[strlen((v.elems[i]).filename)+1];
		strcpy(elems[i].filename,(v.elems[i]).filename);
		elems[i].voicename = new char[strlen((v.elems[i]).voicename)+1];
		strcpy(elems[i].voicename,(v.elems[i]).voicename);
	}
}


VoiceArray::~VoiceArray()
{
	int i;
	for (i=0; i<numElems; i++)
	{
		delete[] (elems[i].voicename);
		delete[] (elems[i].filename);
	}
	delete[] elems;
	elems = NULL;
}

int VoiceArray::get_length()				
{
	return numElems;
}

VoiceFileElement* VoiceArray::get(int index)
{
	if ((index<0)||(index>=numElems))
	{
		return NULL;
	}
	return &elems[index];
}

char* VoiceArray::get_voicename(int index)
{
	if ((index<0)||(index>=numElems))
	{
		return NULL;
	}
	return (elems[index]).voicename;
}

char* VoiceArray::get_filename(int index)
{
	if ((index<0)||(index>=numElems))
	{
		return NULL;
	}
	return (elems[index]).filename;
}

void VoiceArray::add(char* voicename, char* filename)
{
	int i;
	if (size <= numElems)
	{
		VoiceFileElement* tmp = elems; // hold old elems
		size += 500;		        // double size
		elems = new VoiceFileElement[size];
		for (i=0; i<numElems; i++)
		{
			elems[i] = tmp[i];
		}
		delete [] tmp;
	}
	elems[numElems].voicename = new char[strlen(voicename)+1];
	strcpy(elems[numElems].voicename,voicename);
	elems[numElems].filename = new char[strlen(filename)+1];
	strcpy(elems[numElems].filename,filename);
	numElems++;
}

void VoiceArray::reduce(VoiceArray *va_source, char *incl_str)
{
	// incl_str -> search_str with upper chars
	char *search_str = new char[strlen(incl_str)+1];
	strcpy(search_str,incl_str);
	_strupr(search_str);

	// voicename with upper chars
	char * compare_voicename;

	int i;

	// copy all voiceelements in a new array
	VoiceFileElement *temp_elems = new VoiceFileElement[va_source->numElems];
	for (i=0; i<va_source->numElems; i++)
	{
		temp_elems[i].voicename = (va_source->elems[i]).voicename;
		temp_elems[i].filename  = (va_source->elems[i]).filename;
	}

	int temp_numElems = va_source->numElems; // save length of new array temp_elems
	char *voicename;
	char *pdest;
	bool success;

	numElems = 0; // clear list

	for (i=0; i<temp_numElems; i++)
	{
		voicename = temp_elems[i].voicename;

		// upper chars in compare_voicename:
		compare_voicename = new char[strlen(voicename)+1];
		strcpy(compare_voicename,voicename);
		_strupr(compare_voicename);

		// compare
		pdest = strstr(compare_voicename,search_str);
	    success = search_str[0]==0?true:(pdest!=0);
		if (success)
		{
			add(voicename,temp_elems[i].filename);
		}
		delete[] compare_voicename;
	}
    delete[] temp_elems;

	delete[] search_str;
}


void VoiceArray::sort()
{
	int i,j;
	for (i=1; i<numElems; i++)
	{
		VoiceFileElement vce = elems[i];
		j = i-1;
		while ((j>=0) && (strcmp(elems[j].voicename,vce.voicename)>0))
		{
			elems[j+1] = elems[j];
			j--;
		}
		elems[j+1] = vce;
	}
}

//////////////////////////////////////////////////////////////////////
// ArrayChord Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////


ArrayChord::ArrayChord()
{
	size = 500;
	numElems = 0; // empty
	elems = new ElementChordList[size];
}

ArrayChord::~ArrayChord()
{
	delete[] elems;
	elems = NULL;
}

int ArrayChord::get_length()
{
	return numElems;
}

void ArrayChord::add(ElementChordList *elem)
{
	int i;
	if (size <= numElems)
	{
		ElementChordList* tmp = elems; // hold old elems
		size += 200;		        // double size
		elems = new ElementChordList[size];
		for (i=0; i<numElems; i++)
		{
			elems[i] = tmp[i];
		}
		delete [] tmp;
	}
	elems[numElems].time			= elem->time; 
	elems[numElems].takt			= elem->takt; 
	elems[numElems].beat			= elem->beat; 
	elems[numElems].tick			= elem->tick; 
	elems[numElems].ticks_per_beat	= elem->ticks_per_beat; 
	elems[numElems].num				= elem->num;
	elems[numElems].cr				= elem->cr; 
	elems[numElems].ct				= elem->ct; 
	elems[numElems].bn				= elem->bn; 
	elems[numElems].bt				= elem->bt;
	elems[numElems].is_sysex		= elem->is_sysex;
	if (elem->is_sysex)
	{
		for (i=0; i<9; i++)
		{
			elems[numElems].data[i] = elem->data[i];
		}
	}
	numElems++;
}

void ArrayChord::get(int index, ElementChordList *elem)
{
	int i;
	if (index>= numElems)
	{
		MessageBox(NULL,"Internal Error: Out of ArrayChord",NULL,MB_OK);
		return;
	}
	elem->time				= elems[index].time;
	elem->takt				= elems[index].takt;
	elem->beat				= elems[index].beat;
	elem->tick				= elems[index].tick;
	elem->ticks_per_beat	= elems[index].ticks_per_beat;
	elem->num				= elems[index].num;
	elem->cr				= elems[index].cr;
	elem->ct				= elems[index].ct;
	elem->bn				= elems[index].bn;
	elem->bt				= elems[index].bt;
	elem->is_sysex			= elems[index].is_sysex;
	if (elem->is_sysex)
	{
		for (i=0; i<9; i++)
		{
			elem->data[i] = elems[index].data[i];
		}
	}
}


//////////////////////////////////////////////////////////////////////
// ArrayTwoInts Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////


ArrayTwoInts::ArrayTwoInts()
{
	size = 130;
	numElems = 0; // empty
	elems = new SOURCE_DEST*[size];
}

ArrayTwoInts::~ArrayTwoInts()
{
	int i;
	for (i=0; i<numElems; i++) delete elems[i];
	delete[] elems;
	elems = NULL;
}

int ArrayTwoInts::get_length()
{
	return numElems;
}

void ArrayTwoInts::add(int source, int dest)	// add at the end
{
	SOURCE_DEST *elem = new SOURCE_DEST;
	elem->source = source;
	elem->dest = dest;

	if (size <= numElems)
	{
		int i;
		SOURCE_DEST** tmp = elems; // hold old elems
		size += 50 ;		       // enlarge size
		elems = new SOURCE_DEST*[size];
		for (i=0; i<numElems; i++)
		{
			elems[i] = tmp[i];
		}
		delete [] tmp;
	}

	elems[numElems] = elem;
	numElems++;
}

void ArrayTwoInts::get(int index, int *source, int *dest)
{
	*source = (elems[index])->source;
	*dest = (elems[index])->dest;
}

//////////////////////////////////////////////////////////////////////
// ArraySixInts Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////


ArraySixInts::ArraySixInts()
{
	size = 130;
	numElems = 0; // empty
	elems = new SIX_INTS *[size];
}

ArraySixInts::~ArraySixInts()
{
	int i;
	for (i=0; i<numElems; i++) delete elems[i];
	delete[] elems;
	elems = NULL;
}

int ArraySixInts::get_length()
{
	return numElems;
}

void ArraySixInts::add(int i1, int i2, int i3, int i4, int i5, int i6)	// add at the end
{
	SIX_INTS *elem = new SIX_INTS;
	elem->i1 = i1;
	elem->i2 = i2;
	elem->i3 = i3;
	elem->i4 = i4;
	elem->i5 = i5;
	elem->i6 = i6;

	if (size <= numElems)
	{
		int i;
		SIX_INTS** tmp = elems;    // hold old elems
		size += 50 ;		       // enlarge size
		elems = new SIX_INTS*[size];
		for (i=0; i<numElems; i++)
		{
			elems[i] = tmp[i];
		}
		delete [] tmp;
	}

	elems[numElems] = elem;
	numElems++;
}

void ArraySixInts::get(int index, int *i1, int *i2, int *i3, int *i4, int *i5, int *i6)
{
	*i1 = (elems[index])->i1;
	*i2 = (elems[index])->i2;
	*i3 = (elems[index])->i3;
	*i4 = (elems[index])->i4;
	*i5 = (elems[index])->i5;
	*i6 = (elems[index])->i6;
}


void ArraySixInts::sort() // sort by i1 in descending order
{
	int i,j;
	for (i=1; i<numElems; i++)
	{
		SIX_INTS *ele = elems[i];
		j = i-1;
		while ((j>=0) && (ele->i1 > elems[j]->i1))
		{
			elems[j+1] = elems[j];
			j--;
		}
		elems[j+1] = ele;
	}
}


//////////////////////////////////////////////////////////////////////
// ArrayNotesAtSameTime Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////


ArrayNotesAtSameTime::ArrayNotesAtSameTime()
{
	size = 30;
	numElems = 0; // empty
	elems = new NOTE_ELEMENT[size];
}

ArrayNotesAtSameTime::~ArrayNotesAtSameTime()
{
	delete[] elems;
	elems = NULL;
}

int ArrayNotesAtSameTime::get_length()
{
	return numElems;
}

void ArrayNotesAtSameTime::add(int id, int note, int length)	// add at the end
{
	NOTE_ELEMENT *elem = new NOTE_ELEMENT;
	elem->id = id;
	elem->note = note;
	elem->length = length;

	if (size <= numElems)
	{
		int i;
		NOTE_ELEMENT* tmp = elems; // hold old elems
		size += 20 ;		       // enlarge size
		elems = new NOTE_ELEMENT[size];
		for (i=0; i<numElems; i++)
		{
			elems[i] = tmp[i];
		}
		delete [] tmp;
	}

	elems[numElems] = *elem;
	numElems++;
}

void ArrayNotesAtSameTime::get(int index, int *id, int *note, int *length)
{
	*id = (elems[index]).id;
	*note = (elems[index]).note;
	*length = (elems[index]).length;
}

void ArrayNotesAtSameTime::sort() // sort by length in descending order
{
	int i,j;
	for (i=1; i<numElems; i++)
	{
		NOTE_ELEMENT note_ele = elems[i];
		j = i-1;
		while ((j>=0) && (note_ele.length > elems[j].length))
		{
			elems[j+1] = elems[j];
			j--;
		}
		elems[j+1] = note_ele;
	}
}

void ArrayNotesAtSameTime::clear_list()
{
	delete[] elems;
	size = 30;
	numElems = 0; // empty
	elems = new NOTE_ELEMENT [size];
}

//////////////////////////////////////////////////////////////////////
// ArrayLinefeeds Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

const int ArrayLinefeeds::without_lf = 0;
const int ArrayLinefeeds::single_lf = 1;
const int ArrayLinefeeds::with_lf = 2;


ArrayLinefeeds::ArrayLinefeeds()
{
	size = 1000;
	numElems = 0; // empty
	elems = new LINEFEEDS*[size];
}

ArrayLinefeeds::~ArrayLinefeeds()
{
	int i;
	for (i=0; i<numElems; i++)
	{
		HP_Delete((elems[i])->text);
		delete elems[i];
	}
	delete[] elems;
	elems = NULL;
}

int ArrayLinefeeds::get_length()
{
	return numElems;
}

void ArrayLinefeeds::add(int time, int type, char* text, char lf_char)	// add at the end
{
	LINEFEEDS *elem = new LINEFEEDS;
	elem->time = time;
	elem->type = type;
	elem->text = text;
	elem->lf_char = lf_char;

	if (size <= numElems)
	{
		int i;
		LINEFEEDS** tmp = elems; // hold old elems
		size += 100 ;		     // enlarge size
		elems = new LINEFEEDS*[size];
		for (i=0; i<numElems; i++)
		{
			elems[i] = tmp[i];
		}
		delete [] tmp;
	}

	elems[numElems] = elem;
	numElems++;
}

void ArrayLinefeeds::get(int index, int *time, int *type, char **text, char* lf_char)
{
	*time = (elems[index])->time;
	*type = (elems[index])->type;
	*text = (elems[index])->text;
	*lf_char = (elems[index])->lf_char;
}


//////////////////////////////////////////////////////////////////////
// LyricChordEditArray Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////


LyricChordEditArray::LyricChordEditArray()
{
	size = 1500;
	numElems = 0; // empty
	no_chords = 0;
	no_lyrics = 0;
	elems = new LyricChordEditElement[size];
}

LyricChordEditArray::~LyricChordEditArray()
{
	delete[] elems;
	elems = NULL;
	numElems = 0;
}

int LyricChordEditArray::get_length()				// get num_elements 
{
	return numElems;
}

int LyricChordEditArray::get_no_chords()			
{
	return no_chords;
}

int LyricChordEditArray::get_no_lyrics()			
{
	return no_lyrics;
}

LyricChordEditElement* LyricChordEditArray::get(int index)
{
	if ((index<0)||(index>=numElems))
	{
		return NULL;
	}
	return &(elems[index]);
}

int LyricChordEditArray::get_time(int index) 
{
	if ((index<0)||(index>=numElems))
	{
		return -1;
	}
	return (elems[index]).time;
}

int LyricChordEditArray::get_type(int index)
{
	if ((index<0)||(index>=numElems))
	{
		return -1;
	}
	return (elems[index]).type;
}

void LyricChordEditArray::get_takt_beat_tick(int index,int *takt, int *beat, int *tick)
{
	if ((index<0)||(index>=numElems))
	{
		return;
	}
	*takt = (elems[index]).takt;
	*beat = (elems[index]).beat;
	*tick = (elems[index]).tick;
}

void LyricChordEditArray::get_cr_ct_bn_bt(int index, unsigned char *cr,
				unsigned char *ct, unsigned char *bn, unsigned char *bt)
{
	if ((index<0)||(index>=numElems))
	{
		return;
	}
	*cr = (elems[index]).cr;
	*ct = (elems[index]).ct;
	*bn = (elems[index]).bn;
	*bt = (elems[index]).bt;
}



CString LyricChordEditArray::get_text(int index)
{
	if ((index<0)||(index>=numElems))
	{
		return "";
	}
	return (elems[index]).text;
}

CRect *LyricChordEditArray::get_rect(int index)
{
	if ((index<0)||(index>=numElems))
	{
		return NULL;
	}
	return &((elems[index]).rect);
}


void LyricChordEditArray::set_time (int index, int time)
{
	if ((index<0)||(index>=numElems))
	{
		return;
	}
	(elems[index]).time = time;
	sort();
}

void LyricChordEditArray::set_takt_beat_tick(int index, int takt, int beat, int tick)
{
	if ((index<0)||(index>=numElems))
	{
		return;
	}
	(elems[index]).takt = takt;
	(elems[index]).beat = beat;
	(elems[index]).tick = tick;
}

void LyricChordEditArray::set_cr_ct_bn_bt(int index, unsigned char cr,
				unsigned char ct, unsigned char bn, unsigned char bt)
{
	if ((index<0)||(index>=numElems))
	{
		return;
	}
	(elems[index]).cr = cr;
	(elems[index]).ct = ct;
	(elems[index]).bn = bn;
	(elems[index]).bt = bt;
}

void LyricChordEditArray::set_text(int index, CString text)
{
	if ((index<0)||(index>=numElems))
	{
		return;
	}
	(elems[index]).text = text;
}

void LyricChordEditArray::set_rect(int index, int x1, int y1, int x2, int y2)
{
	if ((index<0)||(index>=numElems))
	{
		return;
	}
	((elems[index]).rect).left   = x1;
	((elems[index]).rect).top    = y1;
	((elems[index]).rect).right  = x2;
	((elems[index]).rect).bottom = y2;
}

void LyricChordEditArray::add(LyricChordEditElement* lce_elem, bool with_sort)	// add at the end
{
	int i;
	if (size <= numElems)
	{
		LyricChordEditElement* tmp = elems; // hold old elems
		size += 200;		        // double size
		elems = new LyricChordEditElement[size];
		for (i=0; i<numElems; i++)
		{
			elems[i] = tmp[i];
		}
		delete [] tmp;
	}
	elems[numElems].time			= lce_elem->time; 
	elems[numElems].takt			= lce_elem->takt; 
	elems[numElems].beat			= lce_elem->beat; 
	elems[numElems].tick			= lce_elem->tick; 
	elems[numElems].text			= lce_elem->text; 
	elems[numElems].type			= lce_elem->type;
	elems[numElems].rect			= lce_elem->rect;
	elems[numElems].cr				= lce_elem->cr;
	elems[numElems].ct				= lce_elem->ct;
	elems[numElems].bn				= lce_elem->bn;
	elems[numElems].bt				= lce_elem->bt;
	
	numElems++;

	if (lce_elem->type==CHORD_TYPE)
	{
		no_chords++;
	}
	if (lce_elem->type==LYRIC_TYPE)
	{
		no_lyrics++;
	}

	if (with_sort) sort();
}

void LyricChordEditArray::delete_elem(int index)
{
	int i;
	for (i=index+1; i<numElems; i++)
	{
		elems[i-1] = elems[i];
	}
	numElems--;
}

void LyricChordEditArray::sort()					// sort list by voicename
{
	int i,j;
	for (i=1; i<numElems; i++)
	{
		LyricChordEditElement lce = elems[i];
		j = i-1;
		while ((j>=0) && (elems[j].time > lce.time))
		{
			elems[j+1] = elems[j];
			j--;
		}
		elems[j+1] = lce;
	}
}

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion DynArray
//////////////////////////////////////////////////////////////////////

DynArray::DynArray()
{
	int i;
	size = 1500;
	numElems = 0; // empty
	elems = new char*[size];
	for (i=0; i<size; i++)
	{
		elems[i] = NULL;
	}
}


DynArray::~DynArray()
{
	int i;
	for (i=0; i<numElems; i++)
	{
		delete[] elems[i];
	}
	delete[] elems;
	elems = NULL;
	numElems = 0;
}

int DynArray::get_length()
{
	return numElems;
}

char* DynArray::get_name(int index)
{
	if ((index<0)||(index>=numElems))
	{
		return NULL;
	}
	return elems[index];
}

void DynArray::add(char* name)
{
	int i;
	if (size <= numElems)
	{
		char** tmp = elems; // hold old elems
		size += 500;		        // double size
		elems = new char*[size];
		for (i=0; i<numElems; i++)
		{
			elems[i] = new char[strlen(tmp[i])];
			strcpy(elems[i],tmp[i]);
		}
		for (i=numElems; i<size;i++)
		{
			elems[i] = NULL;
		}
		for (i=0; i<numElems; i++)
		{
			if (tmp[i] != NULL)
			{
				delete[] tmp[i];
			}
		}
		delete [] tmp;
	}

	elems[numElems] = new char[strlen(name)+1];
	strcpy(elems[numElems],name);
	numElems++;
}

void DynArray::sort()
{
	int i,j;
	for (i=1; i<numElems; i++)
	{
		char* elem = elems[i];
		j = i-1;
		while ((j>=0) && (strcmp(elems[j],elem)>0))
		{
			elems[j+1] = elems[j];
			j--;
		}
		elems[j+1] = elem;
	}
}

void DynArray::clear()
{
	int i;
	for (i=0; i<numElems; i++)
	{
		if (elems[i] != NULL)
		{
			delete[] elems[i];
			elems[i] = NULL;
		}
	}
	numElems=0;
}


/** SysEx XG effects from file ***********************************************/


//////////////////////////////////////////////////////////////////////
// DataReverbArray Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////


DataReverbArray::DataReverbArray()
{
	size = 50;
	numElems = 0; // empty
	elems = new DATA_REVERB_ELEM*[size];
}

DataReverbArray::~DataReverbArray()
{
	int i;
	for (i=0; i<numElems; i++)
	{
		if (elems[i] != NULL)
		{
			delete elems[i];
		}
	}
	delete[] elems;
	elems = NULL;
}

int DataReverbArray::get_length()
{
	return numElems;
}

void DataReverbArray::add(int msb, int lsb, CString type, int epl)	// add at the end
{
	DATA_REVERB_ELEM *elem = new DATA_REVERB_ELEM;
	elem->msb = msb;
	elem->lsb = lsb;
	elem->type = type;
	elem->epl = epl;

	if (size <= numElems)
	{
		int i;
		DATA_REVERB_ELEM** tmp = elems; // hold old elems
		size += 50 ;		       // enlarge size
		elems = new DATA_REVERB_ELEM*[size];
		for (i=0; i<numElems; i++)
		{
			elems[i] = tmp[i];
		}
		delete [] tmp;
	}

	elems[numElems] = elem;
	numElems++;
}

void DataReverbArray::get(int index, int *msb, int *lsb, CString *type, int *epl)
{
	*msb = (elems[index])->msb;
	*lsb = (elems[index])->lsb;
	*type = (elems[index])->type;
	*epl = (elems[index])->epl;
}

//////////////////////////////////////////////////////////////////////
// DataChorusArray Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////


DataChorusArray::DataChorusArray()
{
	size = 120;
	numElems = 0; // empty
	elems = new DATA_CHORUS_ELEM*[size];
}

DataChorusArray::~DataChorusArray()
{
	int i;
	for (i=0; i<numElems; i++)
	{
		if (elems[i] != NULL)
		{
			delete elems[i];
		}
	}
	delete[] elems;
	elems = NULL;
}

int DataChorusArray::get_length()
{
	return numElems;
}

void DataChorusArray::add(int msb, int lsb, CString type, int epl)	// add at the end
{
	DATA_CHORUS_ELEM *elem = new DATA_CHORUS_ELEM;
	elem->msb = msb;
	elem->lsb = lsb;
	elem->type = type;
	elem->epl = epl;

	if (size <= numElems)
	{
		int i;
		DATA_CHORUS_ELEM** tmp = elems; // hold old elems
		size += 50 ;		       // enlarge size
		elems = new DATA_CHORUS_ELEM*[size];
		for (i=0; i<numElems; i++)
		{
			elems[i] = tmp[i];
		}
		delete [] tmp;
	}

	elems[numElems] = elem;
	numElems++;
}

void DataChorusArray::get(int index, int *msb, int *lsb, CString *type, int *epl)
{
	*msb = (elems[index])->msb;
	*lsb = (elems[index])->lsb;
	*type = (elems[index])->type;
	*epl = (elems[index])->epl;
}

//////////////////////////////////////////////////////////////////////
// DataDspsArray Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////


DataDspsArray::DataDspsArray()
{
	size = 300;
	numElems = 0; // empty
	elems = new DATA_DSPS_ELEM*[size];
}

DataDspsArray::~DataDspsArray()
{
	int i;
	for (i=0; i<numElems; i++)
	{
		if (elems[i] != NULL)
		{
			delete elems[i];
		}
	}
	delete[] elems;
	elems = NULL;
}

int DataDspsArray::get_length()
{
	return numElems;
}

void DataDspsArray::add(int msb, int lsb, CString type, int epl)	// add at the end
{
	DATA_DSPS_ELEM *elem = new DATA_DSPS_ELEM;
	elem->msb = msb;
	elem->lsb = lsb;
	elem->type = type;
	elem->epl = epl;

	if (size <= numElems)
	{
		int i;
		DATA_DSPS_ELEM** tmp = elems; // hold old elems
		size += 50 ;		       // enlarge size
		elems = new DATA_DSPS_ELEM*[size];
		for (i=0; i<numElems; i++)
		{
			elems[i] = tmp[i];
		}
		delete [] tmp;
	}

	elems[numElems] = elem;
	numElems++;
}

void DataDspsArray::get(int index, int *msb, int *lsb, CString *type, int *epl)
{
	*msb = (elems[index])->msb;
	*lsb = (elems[index])->lsb;
	*type = (elems[index])->type;
	*epl = (elems[index])->epl;
}

//////////////////////////////////////////////////////////////////////
// EffectParameterArray Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////


EffectParameterArray::EffectParameterArray()
{
	
	int i;
	size = 180;
	elems = new EFF_PARAM_ELEM*[size];

	for (i=0; i < size; i++)
	{
		elems[i] = NULL;
	}
	numElems = size;
}

EffectParameterArray::~EffectParameterArray()
{
	int i;
	for (i=0; i<numElems; i++)
	{
		if (elems[i] != NULL)
		{
			delete[] elems[i];
		}
	}
	delete[] elems;
	elems = NULL;
}

int EffectParameterArray::get_length()
{
	return numElems;
}

EFF_PARAM_ELEM * EffectParameterArray::add(int index, EFF_PARAM_ELEM *table)	// add data-list at index
{
	if (size <= index)
	{
		int i;
		EFF_PARAM_ELEM ** tmp = elems;	// hold old elems
		size = index+1;					// enlarge size
		elems = new EFF_PARAM_ELEM*[size];
		for (i=0; i<numElems; i++)
		{
			elems[i] = tmp[i];
		}
		for (i=numElems; i<size; i++)
		{
			elems[i] = NULL;
		}
		numElems = size;
		delete [] tmp;
	}

    if (elems[index] != NULL)
	{
		delete[] elems[index];
	}

	elems[index] = table;

	return elems[index];
}

EFF_PARAM_ELEM * EffectParameterArray::get(int index)
{
	return elems[index];
}


//////////////////////////////////////////////////////////////////////
// EffectTableArray Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

EffectTableArray::EffectTableArray()
{
	
	int i;
	size = 100;
	elems = new CString*[size];

	for (i=0; i < size; i++)
	{
		elems[i] = NULL;
	}
	numElems = 0;
}

EffectTableArray::~EffectTableArray()
{
	int i;
	for (i=0; i<numElems; i++)
	{
		if (elems[i] != NULL)
		{
			delete[] elems[i];
		}
	}
	delete[] elems;
	elems = NULL;
}

int EffectTableArray::get_length()
{
	return numElems;
}

CString* EffectTableArray::add(int index)	// add empty table at position index
{

	if (size <= index)
	{
		int i;
		CString ** tmp = elems;		// hold old elems
		int old_size = size;
		size = index+10;			// enlarge size
		elems = new CString*[size];
		for (i=0; i<old_size; i++)
		{
			elems[i] = tmp[i];
		}

		for (i=old_size; i<size; i++)
		{
			elems[i] = NULL;
		}

		delete [] tmp;
	}

    if (elems[index] != NULL)
	{
		delete[] elems[index];
	}

	if (index >= numElems)
	{
		numElems = index+1;
	}

	elems[index] = new CString[250];
	if (index >= numElems)
	{
		numElems = index+1;
	}

	return elems[index];
}

CString* EffectTableArray::get(int index)
{
	return elems[index];
}





