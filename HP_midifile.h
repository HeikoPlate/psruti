/************************************************************************/
/************************************************************************/
/*                                                                      */
/* HP_midifile.h: Headerfile for HP_MIDIFILE                            */
/*                                                                      */
/************************************************************************/
/************************************************************************/

#if !defined(HP_MIDIFILE_H__ECEFB402_C6DA_11D5_9348_0080AD7896CF__INCLUDED_)
#define HP_MIDIFILE_H__ECEFB402_C6DA_11D5_9348_0080AD7896CF__INCLUDED_

// Der folgende ifdef-Block zeigt die Standardlösung zur Erstellung von Makros,
// die das Exportieren aus einer DLL vereinfachen.
// Alle Dateien in dieser DLL wurden mit dem in der Befehlszeile definierten
// Symbol HP_MIDIFILE_EXPORTS kompiliert. Dieses Symbol sollte für kein Projekt
// definiert werden, das
// diese DLL verwendet. Auf diese Weise betrachtet jedes andere Projekt, dessen
// Quellcodedateien diese Datei
// einbeziehen, HP_MIDIFILE_API-Funktionen als aus einer DLL importiert, während diese
// DLL mit diesem  Makro definierte Symbole als exportiert betrachtet.
#ifdef HP_MIDIFILE_EXPORTS
#define HP_MIDIFILE_API __declspec(dllexport)
#else
#define HP_MIDIFILE_API __declspec(dllimport)
#endif

// Includes

// #include <afx.h>

// Typedefs

typedef class MIDIFile HP_MIDIFILE_MODULE;

typedef struct HP_device {int device_id; char device_name[32];} HP_DEVICE;
typedef struct HP_cwdef { char def_name[80];} HP_CWDEF;
typedef struct HP_cwbank {long bank_number; char bank_name[64];} HP_CWBANK;
typedef struct HP_cwcontroller {char controller_name[64];} HP_CWCONTROLLER;
typedef struct HP_cwrpn {long rpn_number; char rpn_name[64];} HP_CWRPN;
typedef struct HP_cwnrpn {long nrpn_number; char nrpn_name[64];} HP_CWNRPN;
typedef struct HP_cwvoice {char voice_name[64];} HP_CWVOICE;
typedef struct HP_cwbankvoice {char bank_name[64]; long bank_number;
                               char voice_name[64]; long voice_number;} HP_CWBANKVOICE;
typedef struct HP_cwnote {char note_name[64];} HP_CWNOTE;
typedef struct HP_cwdrum {long bank_no; int voice_no; int is_drum;} HP_CWDRUM;

// MIDI File Formats

#define HP_SMF0		0	/* Standard MIDI file-format 0 */
#define	HP_SMF1		1	/* Standard MIDI file-format 1 */

// Allowed PPQN

#define HP_PPQN48         48
#define HP_PPQN72         72
#define HP_PPQN96         96
#define HP_PPQN120       120
#define HP_PPQN144       144
#define HP_PPQN168       168
#define HP_PPQN192       192
#define HP_PPQN216       216
#define HP_PPQN240       240
#define HP_PPQN360       360
#define HP_PPQN384       384
#define HP_PPQN480       480
#define HP_PPQN960       960
#define HP_PPQN1920     1920

// MIDI Events

#define HP_NOTE						0x000200
#define HP_AFTERTOUCH				0x000300
	// Control Change Events
	#define HP_CONTROLLER_TYPE	    0x000400
	#define HP_BANK_SELECT_MSB		0x010400
	#define HP_MODULATION			0x020400
	#define HP_BREATH				0x030400
	#define HP_PORTAMENTO_TIME		0x040400
	#define HP_MAIN_VOLUME			0x050400
	#define HP_PANPOT				0x060400
	#define HP_EXPRESSION			0x070400
	#define HP_BANK_SELECT_LSB		0x080400
	#define HP_SUSTAIN				0x090400
	#define HP_PORTAMENTO			0x0a0400
	#define HP_SOSTENUTO			0x0b0400
	#define HP_SOFT_PEDAL			0x0c0400
	#define HP_HARMONIC_CONTENT		0x0d0400
	#define HP_RELEASE_TIME			0x0e0400
	#define HP_ATTACK_TIME			0x0f0400
	#define HP_BRIGHTNESS			0x100400
	#define HP_DECAY_TIME			0x110400
	#define HP_VIBRATO_RATE			0x120400
	#define HP_VIBRATO_DEPTH		0x130400
	#define HP_VIBRATO_DELAY		0x140400
	#define HP_PORTAMENTO_CONTROL	0x150400
	#define HP_REVERB_SEND_LEVEL	0x160400
	#define HP_CHORUS_SEND_LEVEL	0x170400
	#define HP_VARIATION_SEND_LEVEL	0x180400
	#define HP_NRPN					0x190400
	#define HP_RPN					0x1a0400
	#define HP_ALL_SOUND_OFF		0x1b0400
	#define HP_RESET_ALL_CONTROLLERS	0x1c0400
	#define HP_ALL_NOTES_OFF		0x1d0400
	#define HP_OMNI_OFF				0x1e0400
	#define HP_OMNI_ON				0x1f0400
	#define HP_MONO					0x200400
	#define HP_POLY					0x210400
#define HP_PROGRAM_CHANGE			0x000500
#define HP_CHANNEL_PRESSURE			0x000600
#define HP_PITCH_WHEEL				0x000700
#define HP_SYSEX					0x000800

// Meta-Events

#define HP_SEQUENCE_NUMBER			0x000101
#define HP_TEXT						0x000201
#define HP_COPYRIGHT				0x000301
#define HP_SONG_TRACK_NAME			0x000401
#define HP_INSTRUMENT				0x000501
#define HP_LYRIC					0x000601
#define HP_MARKER					0x000701
#define HP_CUE_POINT				0x000801
#define HP_CHANNEL_PREFIX			0x000901
#define HP_MIDI_PORT				0x000a01
#define HP_END_OF_TRACK				0x000b01
#define HP_TEMPO					0x000c01
#define HP_SMPTE_OFFSET				0x000d01
#define HP_TIME_SIGNATURE			0x000e01
#define HP_KEY_SIGNATURE			0x000f01
#define HP_OTHER_META				0x00fe01

// YAMAHA Meta Events

#define HP_SCORE_START_BAR			0x01ff01
#define HP_QUICK_START				0x02ff01
#define HP_SCORE_LAYOUT				0x03ff01
#define HP_KEYBOARD_VOICE			0x04ff01
#define HP_XF_VERSION_ID			0x41ff01
#define HP_CHORD_NAME				0x42ff01
#define HP_REHEARSAL_MARK			0x43ff01
#define HP_PHRASE_MARK				0x44ff01
#define HP_MAX_PHRASE_MARK			0x45ff01
#define HP_FINGERING_NUMBER			0x46ff01
#define HP_GUIDE_TRACK_FLAG			0x47ff01
#define HP_GUITAR_INFORMATION_FLAG  0x48ff01
#define HP_CHORD_VOICING_FOR_GUITAR 0x49ff01
#define HP_LYRICS_BITMAP			0x4aff01
#define HP_OTHER_YAMAHA_META		0x00ff01

// User Defined Event

#define HP_RAW_EVENT				0x000002

#define HP_TYPE_MASK				0x00ffff

// Switches for Functions

#define HP_FIRST				true
#define HP_LAST					false
#define HP_DELETE				true
#define HP_NO_DELETE			false
#define HP_ALL_CHAN				-1
#define HP_NO_CHAN				-1
#define HP_NO_TRACK				-1
#define HP_ALL_EVENTS			-2
#define HP_PERCENT				true
#define HP_NO_PERCENT			false
#define HP_NO_NOTE				-1
#define HP_ALL_NOTES			-2
#define HP_ABSOLUTE				true
#define HP_RELATIVE				false
#define HP_NO_TIME_LIMIT        -1
#define HP_ASSEMBLE				true
#define HP_NO_ASSEMBLE			false
#define HP_NO_CONTROLLER_NUMBER -1
#define HP_SEND_EFFECT_EVENTS_BEFORE	true
#define HP_NO_SEND_BEFORE				false
#define HP_GO_PLAY				0
#define HP_STOP_PLAY			1
#define HP_WAIT_PLAY            2
#define HP_ALL					1
#define HP_SELECTED				2
#define HP_GM_VOICE_BANK        -128
#define HP_GM_PERC_BANK         -256

// Errors

#define HP_ERR_NONE                0   /* No error */
#define HP_ERR_BUSY                1   /* Cannot call this command after #define HP_Init.  Call #define HP_Free first. */
#define HP_ERR_UNINITIALIZED       2   /* This command failed because #define HP_Init was not called */
#define HP_ERR_MIDI_DEVICE         3   /* Error bad MIDI output device. */
#define HP_ERR_ALLOCATED_DEVICE    4   /* Error initializing output device but more specifically the output device is already in use and cannot be reused. */
#define HP_ERR_PLAY                5   /* Playing the sound failed. */
#define HP_ERR_OUTPUT_FORMAT       6   /* Soundcard does not support the features needed for this soundsystem (16bit stereo output) */
#define HP_ERR_LOAD                7   /* only one load allowed */
#define HP_ERR_FILE_NOTFOUND       8   /* File not found */
#define HP_ERR_FILE_NOTOPEN        9   /* Open File (destination) not successful */
#define HP_ERR_FILE_FORMAT        10   /* Unknown file format */
#define HP_ERR_FILE_BAD           11   /* Error loading file */
#define HP_ERR_MEMORY             12   /* Not enough memory or resources */
#define HP_ERR_INVALID_PARAM      13   /* An invalid parameter was passed to this function */
#define HP_ERR_INVALID_DENUM      14   /* Must be 1 <= denum <= 16 */
#define HP_ERR_INVALID_PPQN       15   /* invalid ppqn */
#define HP_ERR_NO_PPQN            16   /* ppqn not defined */
#define HP_ERR_INVALID_SYSEX      17   /* invalid sysex */
#define HP_ERR_EVENTTYPE          18   /* invalid event type */
#define HP_ERR_EVENTDATA          19   /* invalid event data */
#define HP_ERR_SEQUENCENUMBER     20   /* more than one sequence number */
#define HP_ERR_KEY                21   /* bad denotation of key */
#define HP_ERR_BAD_ID             22   /* bad identifikation number of event */
#define HP_ERR_DELETE             23   /* delete not allowed for NoteOff and similar events */
#define HP_ERR_BAD_CONTROLLER     24   /* bad type of controller-event */
#define HP_ERR_BAD_NEW_NOTE       25   /* bad value of new note */
#define HP_ERR_BAD_SMPTE_OFFSET   26   /* bad parameter for smpte offset */
#define HP_ERR_BAD_SHIFT          27   /* bad parameter for shift */
#define HP_ERR_BAD_TRANSPOSE      28   /* transpose steps result in bad note-values */
#define HP_ERR_QUANTISIZE         29   /* bad quantisize-parameters*/
#define HP_ERR_RANGE_EVENTLIST    30   /* eventlist out of range*/
#define HP_ERR_CWINSFILE_NOTFOUND 31   /* CW-Ins-File not found */
#define HP_ERR_CWINSFILE          32   /* Bad CW-Ins-File */
#define HP_ERR_CWINS_DEF_INDEX    33   /* Bad def_index selected */
#define HP_ERR_CWINS_FILE_MISSED  34   /* No CW-Ins-File loaded  */
#define HP_ERR_CWINS_LABEL_MISSED 35   /* Label error */
#define HP_ERR_CWINS_NO_INSTRUMENT_DEFINITION_LIST 36  /* Insfile error */
#define HP_ERR_CWINS_NO_NAME      37   /* No name found */
#define HP_ERR_CWINS_NO_INSTRUMENT 38  /* Instrument not correct */
#define HP_ERR_CWINS_NO_DRUM_LINES 39  /* No Drum lines */
#define HP_ERR_PLAY_NO_MIDIEVENT  40   /* Meta Events not allowed */

// Version
extern HP_MIDIFILE_API char* HP_GetVersion();

// Delete memory, allocated by HP MIDIFILE
extern HP_MIDIFILE_API void HP_Delete(void* pointer);

// Init/Free
extern HP_MIDIFILE_API	HP_MIDIFILE_MODULE*	HP_Init();
extern HP_MIDIFILE_API	UINT	HP_Free(HP_MIDIFILE_MODULE * hphandle);

// Load/Save/New
extern HP_MIDIFILE_API	UINT	HP_Load(HP_MIDIFILE_MODULE * hphandle, const char *name);
extern HP_MIDIFILE_API	UINT	HP_Save(HP_MIDIFILE_MODULE * hphandle, const char *name, int format = HP_SMF0); // HP_SMF0 oder HP_SMF1
extern HP_MIDIFILE_API	UINT	HP_MoreChunks(HP_MIDIFILE_MODULE * hphandle);

// Set Switches
extern HP_MIDIFILE_API	UINT	HP_SetFirst(HP_MIDIFILE_MODULE * hphandle, bool first = HP_FIRST);

// Insert Standard Events
extern HP_MIDIFILE_API UINT HP_InsertNote(HP_MIDIFILE_MODULE * hphandle, int time, int length, int note, int chan, int velocity);
extern HP_MIDIFILE_API UINT HP_InsertAftertouch(HP_MIDIFILE_MODULE * hphandle, int time, int chan, int note, int pressure);
extern HP_MIDIFILE_API UINT HP_InsertController(HP_MIDIFILE_MODULE * hphandle, int time, int chan, int type, int value, int controller_number = HP_NO_CONTROLLER_NUMBER);
extern HP_MIDIFILE_API UINT	HP_InsertRPNAbsolute(HP_MIDIFILE_MODULE * hphandle, int time, int chan, int number, int value);
extern HP_MIDIFILE_API UINT	HP_InsertRPNRelative(HP_MIDIFILE_MODULE * hphandle, int time, int chan, int number, int value);
extern HP_MIDIFILE_API UINT	HP_InsertNRPNAbsolute(HP_MIDIFILE_MODULE * hphandle, int time, int chan, int number, int value);
extern HP_MIDIFILE_API UINT	HP_InsertNRPNRelative(HP_MIDIFILE_MODULE * hphandle, int time, int chan, int number, int value);
extern HP_MIDIFILE_API UINT HP_InsertProgramChange(HP_MIDIFILE_MODULE * hphandle, int time, int chan, int number);
extern HP_MIDIFILE_API UINT	HP_InsertChannelPressure(HP_MIDIFILE_MODULE * hphandle, int time, int chan, int pressure);
extern HP_MIDIFILE_API UINT	HP_InsertPitchWheel(HP_MIDIFILE_MODULE * hphandle, int time, int chan, int value);
extern HP_MIDIFILE_API UINT HP_InsertSysEx(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char* data);

// Insert Meta Events
extern HP_MIDIFILE_API UINT	HP_InsertSequenceNumber(HP_MIDIFILE_MODULE * hphandle, int number);
extern HP_MIDIFILE_API UINT	HP_InsertText(HP_MIDIFILE_MODULE * hphandle, int time, char* text);
extern HP_MIDIFILE_API UINT	HP_InsertCopyright(HP_MIDIFILE_MODULE * hphandle, int time, char* text);
extern HP_MIDIFILE_API UINT	HP_InsertSongTrackName(HP_MIDIFILE_MODULE * hphandle, char* text, int chan = HP_ALL_CHAN);
extern HP_MIDIFILE_API UINT	HP_InsertInstrument(HP_MIDIFILE_MODULE * hphandle, int time, char* text, int chan = HP_ALL_CHAN);
extern HP_MIDIFILE_API UINT	HP_InsertLyric(HP_MIDIFILE_MODULE * hphandle, int time, char* text);
extern HP_MIDIFILE_API UINT	HP_InsertMarker(HP_MIDIFILE_MODULE * hphandle, int time, char* text);
extern HP_MIDIFILE_API UINT	HP_InsertCuePoint(HP_MIDIFILE_MODULE * hphandle, int time, char* text);
extern HP_MIDIFILE_API UINT	HP_InsertMIDIPort(HP_MIDIFILE_MODULE * hphandle, int time, int track, int port);
extern HP_MIDIFILE_API UINT	HP_InsertTempo(HP_MIDIFILE_MODULE * hphandle, int time, int bpm);
extern HP_MIDIFILE_API UINT	HP_InsertTempo(HP_MIDIFILE_MODULE * hphandle, int time, double bpm);
extern HP_MIDIFILE_API UINT HP_InsertSmpteOffset(HP_MIDIFILE_MODULE * hphandle, int hr, int mn, int se, int fr, int ff);
extern HP_MIDIFILE_API UINT	HP_InsertTimeSignature(HP_MIDIFILE_MODULE * hphandle, int time, int num, int denum, int metronome_click = 24, int n32 = 8);
extern HP_MIDIFILE_API UINT	HP_InsertKeySignature(HP_MIDIFILE_MODULE * hphandle, int time, char * key);

// Insert YAMAHA Meta Events
extern HP_MIDIFILE_API UINT HP_InsertScoreStartBar(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char *event_data, int length);
extern HP_MIDIFILE_API UINT HP_InsertQuickStart(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char *event_data, int length);
extern HP_MIDIFILE_API UINT HP_InsertScoreLayout(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char *event_data, int length);
extern HP_MIDIFILE_API UINT HP_InsertKeyboardVoice(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char *event_data, int length);
extern HP_MIDIFILE_API UINT HP_InsertXFVersionID(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char *event_data, int length);
extern HP_MIDIFILE_API UINT HP_InsertChord(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char cr, unsigned char ct, unsigned char bn, unsigned char bt);
extern HP_MIDIFILE_API UINT HP_InsertRehearsalMark(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char *event_data, int length);
extern HP_MIDIFILE_API UINT HP_InsertPhraseMark(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char *event_data, int length);
extern HP_MIDIFILE_API UINT HP_InsertMaxPhraseMark(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char *event_data, int length);
extern HP_MIDIFILE_API UINT HP_InsertFingeringNumber(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char *event_data, int length);
extern HP_MIDIFILE_API UINT HP_InsertGuideTrackFlag(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char *event_data, int length);
extern HP_MIDIFILE_API UINT HP_InsertGuitarInformationFlag(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char *event_data, int length);
extern HP_MIDIFILE_API UINT HP_InsertChordVoicingForGuitar(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char *event_data, int length);
extern HP_MIDIFILE_API UINT HP_InsertLyricsBitmap(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char *event_data, int length);
extern HP_MIDIFILE_API UINT HP_InsertOtherYamahaMeta(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char *event_data, int length);

// Insert User Defined Event
extern HP_MIDIFILE_API UINT	HP_InsertRawEvent(HP_MIDIFILE_MODULE * hphandle, int time, unsigned char *data, int length, int chan = HP_ALL_CHAN);

// Changing Notes
extern HP_MIDIFILE_API UINT HP_ChangeNote(HP_MIDIFILE_MODULE *hphandle, int id, int chan, int note, bool absolute);
extern HP_MIDIFILE_API UINT HP_ChangeVelocity(HP_MIDIFILE_MODULE *hphandle, int id, int chan, int note, int value, bool percent);
extern HP_MIDIFILE_API UINT HP_ChangeVelocitySelected(HP_MIDIFILE_MODULE *hphandle, int value, bool percent);
extern HP_MIDIFILE_API UINT HP_ChangeNoteLength(HP_MIDIFILE_MODULE *hphandle, int id, int chan, int note, int value, bool percent);
extern HP_MIDIFILE_API UINT HP_TransposeSelected(HP_MIDIFILE_MODULE *hphandle, int steps);
extern HP_MIDIFILE_API UINT HP_QuantisizeSelected(HP_MIDIFILE_MODULE *hphandle, int resolution, bool start, bool length);
extern HP_MIDIFILE_API UINT HP_SettleOverlappingNotes(HP_MIDIFILE_MODULE *hphandle, bool method);
extern HP_MIDIFILE_API UINT HP_ShiftNotesSelected(HP_MIDIFILE_MODULE *hphandle, int ticks);

// Other Change Functions
extern HP_MIDIFILE_API UINT HP_ChangePPQN(HP_MIDIFILE_MODULE *hphandle, int ppqn);
extern HP_MIDIFILE_API UINT HP_ChangeChannel(HP_MIDIFILE_MODULE *hphandle, int chan);
extern HP_MIDIFILE_API void HP_ChangeChannelInBuffer(int chan);
extern HP_MIDIFILE_API UINT HP_ChangeAftertouch(HP_MIDIFILE_MODULE *hphandle, int id, int note, int value, bool percent);
extern HP_MIDIFILE_API UINT HP_ChangeController(HP_MIDIFILE_MODULE *hphandle, int id , UINT type, int value, bool percent);
extern HP_MIDIFILE_API UINT HP_ChangeControllerSelected(HP_MIDIFILE_MODULE *hphandle, UINT type,int value, bool percent);
extern HP_MIDIFILE_API UINT HP_ChangeRPNAbsolute(HP_MIDIFILE_MODULE *hphandle, int id , int value, bool percent);
extern HP_MIDIFILE_API UINT HP_ChangeRPNRelative(HP_MIDIFILE_MODULE *hphandle, int id , int value);
extern HP_MIDIFILE_API UINT HP_ChangeNRPNAbsolute(HP_MIDIFILE_MODULE *hphandle, int id , int value, bool percent);
extern HP_MIDIFILE_API UINT HP_ChangeNRPNRelative(HP_MIDIFILE_MODULE *hphandle, int id , int value);
extern HP_MIDIFILE_API UINT HP_ChangeProgram(HP_MIDIFILE_MODULE *hphandle, int id ,int number);
extern HP_MIDIFILE_API UINT HP_ChangeChannelPressure(HP_MIDIFILE_MODULE *hphandle, int id ,int pressure);
extern HP_MIDIFILE_API UINT HP_ChangePitchWheel(HP_MIDIFILE_MODULE *hphandle, int id ,int value);
extern HP_MIDIFILE_API UINT HP_ChangeSysex(HP_MIDIFILE_MODULE *hphandle, int id, unsigned char* data);
extern HP_MIDIFILE_API UINT HP_ChangeSequenceNumber(HP_MIDIFILE_MODULE *hphandle, int id, int number);
extern HP_MIDIFILE_API UINT HP_ChangeText(HP_MIDIFILE_MODULE *hphandle, int id,char* new_text);
extern HP_MIDIFILE_API UINT HP_ChangeCopyright(HP_MIDIFILE_MODULE *hphandle, int id,char* new_text);
extern HP_MIDIFILE_API UINT HP_ChangeSongTrackName(HP_MIDIFILE_MODULE *hphandle, int id,char* new_text);
extern HP_MIDIFILE_API UINT HP_ChangeInstrument(HP_MIDIFILE_MODULE *hphandle, int id,char* new_text);
extern HP_MIDIFILE_API UINT HP_ChangeLyric(HP_MIDIFILE_MODULE *hphandle, int id, char* new_text);
extern HP_MIDIFILE_API UINT HP_ChangeMarker(HP_MIDIFILE_MODULE *hphandle, int id, char* new_text);
extern HP_MIDIFILE_API UINT HP_ChangeCuePoint(HP_MIDIFILE_MODULE *hphandle, int id, char* new_text);
extern HP_MIDIFILE_API UINT HP_ChangeMidiPort(HP_MIDIFILE_MODULE *hphandle, int id, int track, int port);
extern HP_MIDIFILE_API UINT HP_ChangeTempo(HP_MIDIFILE_MODULE *hphandle, int id, int value, bool percent);
extern HP_MIDIFILE_API UINT HP_ChangeTempo(HP_MIDIFILE_MODULE *hphandle, int id, double value, bool percent);
extern HP_MIDIFILE_API UINT HP_ChangeSmpteOffset(HP_MIDIFILE_MODULE *hphandle, int id, int hr, int mn, int se, int fr, int ff);
extern HP_MIDIFILE_API UINT HP_ChangeTimeSignature(HP_MIDIFILE_MODULE *hphandle, int id, int new_num, int new_denum, int new_m_click, int new_n32);
extern HP_MIDIFILE_API UINT HP_ChangeKeySignature(HP_MIDIFILE_MODULE *hphandle, int id, char *key);
extern HP_MIDIFILE_API UINT HP_ChangeChord(HP_MIDIFILE_MODULE *hphandle, int id, unsigned char cr, unsigned char ct, unsigned char bn, unsigned char bt);

// General Shift Events
extern HP_MIDIFILE_API UINT HP_ShiftEvent(HP_MIDIFILE_MODULE *hphandle, int id, int ticks);
extern HP_MIDIFILE_API UINT HP_ShiftSelected(HP_MIDIFILE_MODULE *hphandle, int ticks);

// Read Functions
extern HP_MIDIFILE_API UINT HP_ReadEventData(HP_MIDIFILE_MODULE *hphandle, int id, int *time, unsigned char** event_data, int *event_length);
extern HP_MIDIFILE_API UINT HP_ReadPPQN(HP_MIDIFILE_MODULE *hphandle, int *ppqn);
extern HP_MIDIFILE_API UINT HP_ReadNote(HP_MIDIFILE_MODULE *hphandle, int id , int *time, int *chan, int *note, int *velocity, int *length);
extern HP_MIDIFILE_API UINT HP_ReadAftertouch(HP_MIDIFILE_MODULE *hphandle, int id, int *time, int *chan, int *note, int *pressure);
extern HP_MIDIFILE_API UINT HP_ReadController(HP_MIDIFILE_MODULE *hphandle, int id, int *time, int *chan, int *number, int *value);
extern HP_MIDIFILE_API UINT HP_ReadRPN(HP_MIDIFILE_MODULE *hphandle, int id, int *time, int *chan, bool *absolute, int *number, int *value);
extern HP_MIDIFILE_API UINT HP_ReadNRPN(HP_MIDIFILE_MODULE *hphandle, int id, int *time, int *chan, bool *absolute, int *number, int *value);
extern HP_MIDIFILE_API UINT HP_ReadProgramChange(HP_MIDIFILE_MODULE *hphandle, int id, int *time, int *chan, int *number);
extern HP_MIDIFILE_API UINT HP_ReadChannelPressure(HP_MIDIFILE_MODULE *hphandle, int id, int *time, int *chan, int *pressure);
extern HP_MIDIFILE_API UINT HP_ReadPitchWheel(HP_MIDIFILE_MODULE *hphandle, int id, int *time, int *chan, int *value);
extern HP_MIDIFILE_API UINT HP_ReadSysex(HP_MIDIFILE_MODULE *hphandle, int id, int *time, unsigned char** data, int *length);
extern HP_MIDIFILE_API UINT HP_ReadSequenceNumber(HP_MIDIFILE_MODULE *hphandle, int id, int *time, int *number);
extern HP_MIDIFILE_API UINT HP_ReadText(HP_MIDIFILE_MODULE *hphandle, int id, int *time, char **text);
extern HP_MIDIFILE_API UINT HP_ReadCopyright(HP_MIDIFILE_MODULE *hphandle, int id, int *time, char **text);
extern HP_MIDIFILE_API UINT HP_ReadSongTrackName(HP_MIDIFILE_MODULE *hphandle, int id, int *time, char **text);
extern HP_MIDIFILE_API UINT HP_ReadInstrument(HP_MIDIFILE_MODULE *hphandle, int id, int *time, char **text);
extern HP_MIDIFILE_API UINT HP_ReadLyric(HP_MIDIFILE_MODULE *hphandle, int id, int *time, char **text);
extern HP_MIDIFILE_API UINT HP_ReadMarker(HP_MIDIFILE_MODULE *hphandle, int id, int *time, char **text);
extern HP_MIDIFILE_API UINT HP_ReadCuePoint(HP_MIDIFILE_MODULE *hphandle, int id, int *time, char **text);
extern HP_MIDIFILE_API UINT HP_ReadMidiPort(HP_MIDIFILE_MODULE *hphandle, int id, int *time, int *track, int *port);
extern HP_MIDIFILE_API UINT HP_ReadTempo(HP_MIDIFILE_MODULE *hphandle, int id , int *time, int *bpm, int *cps);
extern HP_MIDIFILE_API UINT HP_ReadTempo(HP_MIDIFILE_MODULE *hphandle, int id , int *time, double *bpm, int *cps);
extern HP_MIDIFILE_API UINT HP_ReadSmpteOffset(HP_MIDIFILE_MODULE *hphandle, int id , int *hr, int *mn, int *se, int *fr, int *ff);
extern HP_MIDIFILE_API UINT HP_ReadTimeSignature(HP_MIDIFILE_MODULE *hphandle, int id, int *time, int *num, int *denum, int *metronome_click, int *n32);
extern HP_MIDIFILE_API UINT HP_ReadKeySignature(HP_MIDIFILE_MODULE *hphandle, int id, int *time, char **key);

// Read YAMAHA Meta Events
extern HP_MIDIFILE_API UINT HP_ReadScoreStartBar(HP_MIDIFILE_MODULE * hphandle, int id, int *time, unsigned char **event_data, int *length);
extern HP_MIDIFILE_API UINT HP_ReadQuickStart(HP_MIDIFILE_MODULE * hphandle, int id, int *time, unsigned char **event_data, int *length);
extern HP_MIDIFILE_API UINT HP_ReadScoreLayout(HP_MIDIFILE_MODULE * hphandle, int id, int *time, unsigned char **event_data, int *length);
extern HP_MIDIFILE_API UINT HP_ReadKeyboardVoice(HP_MIDIFILE_MODULE * hphandle, int id, int *time, unsigned char **event_data, int *length);
extern HP_MIDIFILE_API UINT HP_ReadXFVersionID(HP_MIDIFILE_MODULE * hphandle, int id, int *time, unsigned char **event_data, int *length);
extern HP_MIDIFILE_API UINT HP_ReadChord(HP_MIDIFILE_MODULE *hphandle, int id, int *time, unsigned char* cr, unsigned char* ct, unsigned char* bn, unsigned char* bt,char** chord);
extern HP_MIDIFILE_API UINT HP_ReadRehearsalMark(HP_MIDIFILE_MODULE * hphandle, int id, int *time, unsigned char **event_data, int *length);
extern HP_MIDIFILE_API UINT HP_ReadPhraseMark(HP_MIDIFILE_MODULE * hphandle, int id, int *time, unsigned char **event_data, int *length);
extern HP_MIDIFILE_API UINT HP_ReadMaxPhraseMark(HP_MIDIFILE_MODULE * hphandle, int id, int *time, unsigned char **event_data, int *length);
extern HP_MIDIFILE_API UINT HP_ReadFingeringNumber(HP_MIDIFILE_MODULE * hphandle, int id, int *time, unsigned char **event_data, int *length);
extern HP_MIDIFILE_API UINT HP_ReadGuideTrackFlag(HP_MIDIFILE_MODULE * hphandle, int id, int *time, unsigned char **event_data, int *length);
extern HP_MIDIFILE_API UINT HP_ReadGuitarInformationFlag(HP_MIDIFILE_MODULE * hphandle, int id, int *time, unsigned char **event_data, int *length);
extern HP_MIDIFILE_API UINT HP_ReadChordVoicingForGuitar(HP_MIDIFILE_MODULE * hphandle, int id, int *time, unsigned char **event_data, int *length);
extern HP_MIDIFILE_API UINT HP_ReadLyricsBitmap(HP_MIDIFILE_MODULE * hphandle, int id, int *time, unsigned char **event_data, int *length);
extern HP_MIDIFILE_API UINT HP_ReadOtherYamahaMeta(HP_MIDIFILE_MODULE * hphandle, int id, int *time, unsigned char **event_data, int *length);

// Utilities
extern HP_MIDIFILE_API UINT HP_GetTaktBeatTick(HP_MIDIFILE_MODULE * hphandle, int time, int *takt, int *beat, int *tick);
extern HP_MIDIFILE_API UINT HP_GetTaktBeatTick(HP_MIDIFILE_MODULE * hphandle,
												int time,
												int time_of_last_time_signature,
												int takt_of_last_time_signature,
												int num,
												int denum,
												int *takt, int *beat, int *tick);
extern HP_MIDIFILE_API UINT HP_GetTimeFromTaktBeatTick(HP_MIDIFILE_MODULE * hphandle, int takt, int beat, int tick, int *time);
extern HP_MIDIFILE_API UINT HP_GetLastTime(HP_MIDIFILE_MODULE * hphandle, int *time);
extern HP_MIDIFILE_API char* HP_TypeName(UINT type);
extern HP_MIDIFILE_API char* HP_ErrText(int err_no);
extern HP_MIDIFILE_API UINT HP_ConvertChordToText(unsigned char cr,
												  unsigned char ct,
												  unsigned char bn,
												  unsigned char bt,
												  char ** chord_name);

// Stream-Functions
extern HP_MIDIFILE_API UINT HP_Rewind(HP_MIDIFILE_MODULE * hphandle);
extern HP_MIDIFILE_API UINT HP_ReadEvent(HP_MIDIFILE_MODULE * hphandle, int *id, int *chan, int *time, int *type);
extern HP_MIDIFILE_API UINT HP_DeleteShortNotesSelected(HP_MIDIFILE_MODULE * hphandle, int limit_length);
extern HP_MIDIFILE_API UINT HP_DeleteEvent(HP_MIDIFILE_MODULE * hphandle, int id);

// Select, Copy, Paste
extern HP_MIDIFILE_API UINT HP_Select(HP_MIDIFILE_MODULE * hphandle, int id = HP_ALL_EVENTS);
extern HP_MIDIFILE_API UINT HP_SelectChanTime(HP_MIDIFILE_MODULE * hphandle, int chan, int time1=0, int time2=HP_NO_TIME_LIMIT);
extern HP_MIDIFILE_API UINT HP_Deselect(HP_MIDIFILE_MODULE * hphandle, int id = HP_ALL_EVENTS);
extern HP_MIDIFILE_API UINT HP_DeselectChan(HP_MIDIFILE_MODULE * hphandle, int chan);
extern HP_MIDIFILE_API UINT HP_Copy(HP_MIDIFILE_MODULE * hphandle);
extern HP_MIDIFILE_API UINT HP_Paste(HP_MIDIFILE_MODULE * hphandle,int time, bool delete_in_dest, int del_events_chan);

// Play Functions

extern HP_MIDIFILE_API UINT HP_GetMIDIDevices(HP_DEVICE **devices, int *no_devices);
extern HP_MIDIFILE_API UINT HP_SelectMIDIDevice(int id);
extern HP_MIDIFILE_API UINT HP_Play(HP_MIDIFILE_MODULE * hphandle, int selected, bool send_before = HP_SEND_EFFECT_EVENTS_BEFORE);
extern HP_MIDIFILE_API UINT HP_SetPlayStopWait(HP_MIDIFILE_MODULE * hphandle, int modus);
extern HP_MIDIFILE_API UINT HP_SetPlayTime(HP_MIDIFILE_MODULE * hphandle, int new_time);
extern HP_MIDIFILE_API bool HP_IsPlaying(HP_MIDIFILE_MODULE * hphandle);
extern HP_MIDIFILE_API long HP_Duration(HP_MIDIFILE_MODULE * hphandle, int modus = HP_ALL);
extern HP_MIDIFILE_API long HP_PlayTime(HP_MIDIFILE_MODULE * hphandle);
extern HP_MIDIFILE_API long HP_PlayEventTime(HP_MIDIFILE_MODULE * hphandle);
extern HP_MIDIFILE_API UINT HP_PlayTempo(HP_MIDIFILE_MODULE * hphandle, int percent = 100);
extern HP_MIDIFILE_API UINT HP_PlayMute(HP_MIDIFILE_MODULE * hphandle, const bool mute_list[16]);
extern HP_MIDIFILE_API UINT HP_PlayTranspose(HP_MIDIFILE_MODULE * hphandle, int steps, const bool transp_list[16]);
extern HP_MIDIFILE_API UINT HP_PlaySingleEvent(HP_MIDIFILE_MODULE * hphandle, unsigned char* event_data, int length);

// Abstract Play Monitor Class HP_PLAY_MONITOR
class HP_PLAY_MONITOR
{
public:
	// takt/beat monitor
	virtual void HP_PlayTBMonitor(int takt, int beat) = 0;
	// chord monitor
	virtual void HP_PlayChMonitor(char* chord_text) = 0;
	// lyric monitor
	virtual void HP_PlayLyMonitor(char* lyric_text) = 0;
};

// Initialize Play Takt Beat Monitor
extern HP_MIDIFILE_API UINT HP_InitPlayMonitor(HP_MIDIFILE_MODULE * hphandle, HP_PLAY_MONITOR * pm_instance);

// Functions for Cakewalk Instrument-Definition-Files

extern HP_MIDIFILE_API UINT HP_CWInsLoad(HP_MIDIFILE_MODULE * hphandle, const char* name);
extern HP_MIDIFILE_API UINT HP_CWInsGetDefs(HP_MIDIFILE_MODULE * hphandle, HP_CWDEF** defs, int *no_defs);
extern HP_MIDIFILE_API UINT HP_CWInsSetDef(HP_MIDIFILE_MODULE * hphandle, int def_index);
extern HP_MIDIFILE_API UINT HP_CWInsGetBankVoiceNoteName(HP_MIDIFILE_MODULE* hphandle,
		long bank, int voice, int note, char** bank_name,char** voice_name, char** note_name);
extern HP_MIDIFILE_API UINT HP_CWInsGetNoteNames(HP_MIDIFILE_MODULE* hphandle, long bank, int voice, char** bankname, char** voice_name, HP_CWNOTE **note_names);
extern HP_MIDIFILE_API UINT HP_CWInsGetBanks(HP_MIDIFILE_MODULE* hphandle, HP_CWBANK** banks, int* no_banks);
extern HP_MIDIFILE_API UINT HP_CWInsGetBankVoices(HP_MIDIFILE_MODULE* hphandle,
						long bank, char** bank_name,HP_CWVOICE** voices);
extern HP_MIDIFILE_API UINT HP_CWInsGetBankVoiceList(HP_MIDIFILE_MODULE* hphandle,
						char *search_string, HP_CWBANKVOICE** bank_voice_list,long *bank_voice_list_len);
extern HP_MIDIFILE_API UINT HP_CWInsGetRPNName(HP_MIDIFILE_MODULE* hphandle, long rpn, char** rpn_name);
extern HP_MIDIFILE_API UINT HP_CWInsGetRPNNames(HP_MIDIFILE_MODULE* hphandle, HP_CWRPN** rpn_names, long *no_rpn);
extern HP_MIDIFILE_API UINT HP_CWInsGetNRPNName(HP_MIDIFILE_MODULE* hphandle, long nrpn, char** nrpn_name);
extern HP_MIDIFILE_API UINT HP_CWInsGetNRPNNames(HP_MIDIFILE_MODULE* hphandle, HP_CWNRPN** nrpn_names, long *no_nrpn);
extern HP_MIDIFILE_API UINT HP_CWInsGetControllerName(HP_MIDIFILE_MODULE* hphandle, int controller, char** controller_name);
extern HP_MIDIFILE_API UINT HP_CWInsGetControllerNames(HP_MIDIFILE_MODULE* hphandle, HP_CWCONTROLLER** controller_names);
extern HP_MIDIFILE_API UINT HP_CWInsIsDrumVoice(HP_MIDIFILE_MODULE* hphandle, long bank_no, int voice_no, int *is_drum);


#endif // HP_MIDIFILE_H__ECEFB402_C6DA_11D5_9348_0080AD7896CF__INCLUDED_