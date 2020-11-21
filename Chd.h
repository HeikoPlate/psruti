// Chd.h: Schnittstelle für die Klasse Chd.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHD_H__74CA6860_D389_11D5_9348_0080AD7896CF__INCLUDED_)
#define AFX_CHD_H__74CA6860_D389_11D5_9348_0080AD7896CF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>
#include "HP_midifile.h" 

#define NO_CHORDLIST_CHAN  18 // length of several chord-lists
#define CHORD_INDEX_ALL    16 // index of "all" in chord-lists
#define CHORD_INDEX_SEL    17 // index of "sel" in chord-lists

class Chrd  
{

public:

	typedef struct chord_event
	{
		int event_time;
		unsigned char event[10];
		int takt;
		int bar;
		int tick;
		CString text;
	} CHORD_EVENT;
	
	typedef struct chordtag
	{	
      int takt;
	  int bar;
	  int tick;
	  int resulting_time;
	  CString text;
	  unsigned char cr; // chord root in event
	  unsigned char ct; // chord type in event
	  unsigned char bn; // base note;
	} CHORD_ELEMENT;

	typedef struct chord_note_elem
	{
		int note;
		bool is_flat;
	} CHORD_NOTE_ELEM;

	typedef struct bass_note_elem
	{
		int event_time;
		unsigned char bn;
	} BASS_NOTE_ELEM;

	Chrd(HP_MIDIFILE_MODULE* mfile);
	Log *lf;

	virtual ~Chrd();

	void add_chord_note(short note,
		                short channel, 
						bool is_flat, 
						int takt,
						int bar,
						int delta_tick, 
						int event_time, 
						bool percussion, 
						bool sel_list[16]);

	void remove_chord_note(short note, short channel, bool sel_list[16]);

	bool analyze_from_line(int takt, int bar, int tick, int time, CString chord_text);


	int fill_chordeventlist(int chan,
							  CArray<CHORD_EVENT,CHORD_EVENT> *cevlist, int *cevlist_free);
	void analyze_chord(bool is_simple_chords,
						 CArray<BASS_NOTE_ELEM,BASS_NOTE_ELEM> *bass_note_list,
						 int bass_note_list_free);
	CString get_last_chord_text();
	int get_no_chords(int chan);

private:
	
	// private functions
//	void better_chord(unsigned char cr, unsigned char ct, char b, 
//		unsigned char *new_cr, unsigned char *new_ct, char *new_b, bool is_flat);
	void simple_chord(unsigned char cr, unsigned char ct, char b, 
		unsigned char *new_cr, unsigned char *new_ct, char *new_b, bool is_flat);
	void sort_notes(short channel);

	// private attributes

	HP_MIDIFILE_MODULE* mf;	// hp midifile handle for working, 
	                        // initialized with source-file

	static const char *note_list_sharp[12], *note_list_flat[12];
	static const unsigned char event_crlist_sharp[12], event_crlist_flat[12]; 

	CHORD_NOTE_ELEM chord_note[NO_CHORDLIST_CHAN][32];	// enthält der Größe nach geordnet 
												// die aktuell spielenden Noten
	int  no_chord_notes[NO_CHORDLIST_CHAN];	// Anzahl der Noten der chords (über alle channel)

	// remember the time of last chord-notes
	int chord_takt[NO_CHORDLIST_CHAN];	
	int chord_bar[NO_CHORDLIST_CHAN];
	int chord_delta_tick[NO_CHORDLIST_CHAN];
	int chord_event_time[NO_CHORDLIST_CHAN];

	bool is_drum[NO_CHORDLIST_CHAN];
	bool is_flat;
	
	CString last_chord_text[NO_CHORDLIST_CHAN];	// enthält den zuletzt ausgegebenen Chord (Text)
	int last_takt[NO_CHORDLIST_CHAN];
	int last_bar[NO_CHORDLIST_CHAN];
	int last_delta_tick[NO_CHORDLIST_CHAN];


    CArray<CHORD_ELEMENT,CHORD_ELEMENT> chordlist[NO_CHORDLIST_CHAN];
	int chordlist_free[NO_CHORDLIST_CHAN];
	
	//
	// Chord Typen
	//
	static const char chord3_list[12][12][3];     // chords with three notes
	static const char chord4_list[12][12][12][3]; // chords with four notes

	static const char* chord_type[];
	static const int tr_simple_chord_type[][2];
};

#endif // !defined(AFX_CHD_H__74CA6860_D389_11D5_9348_0080AD7896CF__INCLUDED_)
