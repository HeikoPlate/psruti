// MyArrays.h: Schnittstelle für die Klasse VoiceArray, ArrayChord.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYARRAYS_H__29FC5D00_1CA9_498D_8F4D_A10F6B5759D1__INCLUDED_)
#define AFX_MYARRAYS_H__29FC5D00_1CA9_498D_8F4D_A10F6B5759D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "VoiceFileElement.h"
#include "ElementChordList.h"
#include "LyricChordEditElement.h"
#include "HP_midifile.h"


class VoiceArray  
{

public:
	VoiceArray();
	VoiceArray(const VoiceArray& v);

	virtual ~VoiceArray();

private:
	VoiceFileElement *elems;	// dynamic array of voicename and filename
	int size;		// actual length
	int numElems;	// actual number of elements

public:
	int get_length();				// get num_elements 
	VoiceFileElement* get(int index);
	char* get_voicename(int index); // get voicename
	char* get_filename(int index);  // get filename
	void add(char* voicename, char* filename);	// add at the end
	void sort();					// sort list by voicename
	void reduce(VoiceArray *va_source, char *incl_str);
};


class ArrayChord  
{
public:
	ArrayChord();
	virtual ~ArrayChord();
private:
	ElementChordList *elems;	// dynamic array of chords
	int size;		// actual length
	int numElems;	// actual number of elements

public:
	int get_length();				// get num_elements 
	void add(ElementChordList *elem);	// add at the end
	void get(int index, ElementChordList *elem);
};

class ArrayTwoInts
{
public:
	typedef struct source_dest {int source; int dest;}SOURCE_DEST; 

	ArrayTwoInts();
	virtual ~ArrayTwoInts();
private:
	SOURCE_DEST **elems; // dynamic array of two ints
	int size;			// actual length
	int numElems;		// actual number of elements

public:
	int get_length();				// get num_elements 
	void add(int source, int dest);	// add at the end
	void get(int index, int *source, int *dest);
};

class ArraySixInts
{
public:
	typedef struct six_ints {int i1; int i2; int i3; int i4; int i5; int i6;}SIX_INTS; 

	ArraySixInts();
	virtual ~ArraySixInts();
private:
	SIX_INTS **elems;   // dynamic array of six ints
	int size;			// actual length
	int numElems;		// actual number of elements

public:
	int get_length();				// get num_elements 
	void add(int i1, int i2, int i3, int i4, int i5, int i6);	// add at the end
	void get(int index, int *i1, int *i2, int *i3, int *i4, int *i5, int *i6);
	void sort();		  // sort i1 in descending order
};

class ArrayNotesAtSameTime
{
public:
	typedef struct note_element {int id; int note; int length;}NOTE_ELEMENT;

	ArrayNotesAtSameTime();
	virtual ~ArrayNotesAtSameTime();
private:
	NOTE_ELEMENT *elems; // dynamic array of two ints
	int size;			  // actual length;
	int numElems;		  // actual number of elements
	int chan;			  // channel	
public:					  	
	int get_length();			// get num_elems
	void add(int id, int note, int length);	// add at the end
	void get(int index, int *id, int *note, int *length);
	void sort();		  // sort by length in descending order
	void clear_list();
};

class ArrayLinefeeds
{
public:
	typedef struct linefeeds {int time; int type; char* text; char lf_char;} LINEFEEDS; 

	ArrayLinefeeds();
	virtual ~ArrayLinefeeds();
private:
	LINEFEEDS **elems;	// dynamic array of three ints
	int size;			// actual length
	int numElems;		// actual number of elements

public:
	int get_length();				// get num_elements 
	void add(int time, int type, char* text, char lf_char);	// add at the end
	void get(int index, int *time, int *type, char** text, char* lf_char);

	static const int without_lf;
	static const int single_lf;
	static const int with_lf;
};

class LyricChordEditArray  
{

public:
	LyricChordEditArray();
	virtual ~LyricChordEditArray();

private:
	LyricChordEditElement *elems;	// dynamic array  
	int size;						// actual length
	int numElems;					// actual number of elements
	int no_chords;
	int no_lyrics;

public:
	int get_length();							// get num_elements
	int get_no_chords();
	int get_no_lyrics();
	LyricChordEditElement* get(int index);
	int get_time(int index); 
	int get_type(int index);
	void get_takt_beat_tick(int index,int *takt, int *beat, int *tick);
	void get_cr_ct_bn_bt(int index, unsigned char *cr,
				unsigned char *ct, unsigned char *bn, unsigned char *bt);
	CRect *get_rect(int index);
	CString get_text(int index);
	void set_time (int index, int time);
	void set_takt_beat_tick(int index, int takt, int beat, int tick);
	void set_cr_ct_bn_bt(int index, unsigned char cr,
				unsigned char ct, unsigned char bn, unsigned char bt);
	void set_text(int index, CString text);
	void set_rect(int index, int x1, int y1, int x2, int y2);
	void add(LyricChordEditElement* lce_elem, bool with_sort);	// add at the end
	void delete_elem(int index);
	void sort();								// sort list by time
};

class DynArray
{

public:
	DynArray();
	DynArray(const DynArray& v);

	virtual ~DynArray();

private:
	int size;		// actual length
	int numElems;	// actual number of elements
	char **elems;

public:
	int get_length();				// get num_elements
	char* get_name(int index);
	void add(char* name);	        // add at the end
	void sort();					// sort list by name
	void clear();
};


/** SysEx XG effects from file ***********************************************/


class DataReverbArray
{
public:
	typedef struct data_reverb_elem {int msb; int lsb; CString type; int epl;} DATA_REVERB_ELEM;
 	DataReverbArray();
	virtual ~DataReverbArray();
private:
	DATA_REVERB_ELEM **elems; // dynamic array
	int size;				 // actual length
	int numElems;			 // actual number of elements
public:
	int get_length();		 // get num_elements 
	void add(int msb, int lsb, CString type, int epl);	// add at the end
	void get(int index, int *msb, int *lsb, CString *type, int *epl);
};

class DataChorusArray
{
public:
	typedef struct data_chorus_elem {int msb; int lsb; CString type; int epl;} DATA_CHORUS_ELEM;
 
	DataChorusArray();
	virtual ~DataChorusArray();
private:
	DATA_CHORUS_ELEM **elems; // dynamic array
	int size;				 // actual length
	int numElems;			 // actual number of elements
public:
	int get_length();		 // get num_elements 
	void add(int msb, int lsb, CString type, int epl);	// add at the end
	void get(int index, int *msb, int *lsb, CString *type, int *epl);
};

class DataDspsArray
{
public:
	typedef struct data_chorus_elem {int msb; int lsb; CString type; int epl;} DATA_DSPS_ELEM;
 
	DataDspsArray();
	virtual ~DataDspsArray();
private:
	DATA_DSPS_ELEM **elems; // dynamic array
	int size;				 // actual length
	int numElems;			 // actual number of elements
public:
	int get_length();		 // get num_elements 
	void add(int msb, int lsb, CString type, int epl);	// add at the end
	void get(int index, int *msb, int *lsb, CString *type, int *epl);
};

typedef struct eff_param_elem {CString name; int data_list;} EFF_PARAM_ELEM;


class EffectParameterArray
{
public:
	EffectParameterArray();
	virtual ~EffectParameterArray();
private:
	EFF_PARAM_ELEM **elems;  // dynamic array
	int size;				 // actual length
	int numElems;			 // actual number of elements
public:
	int get_length();		 // get num_elements 
	EFF_PARAM_ELEM * add(int index, EFF_PARAM_ELEM *table);	 // add datalist at index 
	EFF_PARAM_ELEM * get(int index); // get pointer from index
};


#define MAX_TABLE_LEN 250

// the define cannot be used in class EffectTableArray

class EffectTableArray
{
public:
	EffectTableArray();
	virtual ~EffectTableArray();
private:
	CString **elems; // dynamic array
	int size;		 // actual length
	int numElems;	 // actual number of elements
public:
	int get_length();	// get num_elements 
	CString * add(int index);	// add pointer of empty table list at end 
	CString * get(int index);	// get pointer from index
};

#endif // !defined(AFX_MYARRAYS_H__29FC5D00_1CA9_498D_8F4D_A10F6B5759D1__INCLUDED_)
