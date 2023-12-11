// SysExEventProt.cpp: Implementierung der Klasse SysExEventProt. //
//
// Soll diese Datei von PSRUTI übernommen werden, müssen alle
// "hpmfi->" durch "" ersetzt werden. Zusätzlich muss ganz vorn die
// Zeile "XgEffects *SysExEventProt::xg_effects = NULL;" eingesetzt werden.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sysex_event_prot.h"
#include "GlobalUtilities.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// XgEffects *SysExEventProt::xg_effects = NULL; Nur für Verwenung in PSRMIDI
// Zusätlich müssen dann alle "hpmfi->" durch "" ersetzt werden.

//////////////////////////////////////////////////////////////////////
// SysExEventProt Klasse	status = 0xf0
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

SysExEventProt::SysExEventProt()
{
	int i;
	act_reverb_type.msb = -1;
	act_reverb_type.lsb = -1;
	act_reverb_param_list_no = -1;

	act_chorus_type.msb = -1;
	act_chorus_type.lsb = -1;
	act_chorus_param_list_no = -1;

	act_variation_type.msb = -1;
	act_variation_type.lsb = -1;
	act_variation_param_list_no = -1;

	for (i=0; i<NO_DSP_BLOCKS; i++)
	{
		act_dsp_type[i].msb = -1;
		act_dsp_type[i].lsb = -1;
		act_dsp_param_list_no[i] = -1;
	}
}

SysExEventProt::~SysExEventProt()
{
}

CString SysExEventProt::sysex_string(unsigned char* data, int length)
{
	print_str = "";

	int i;

	for (i=1; i<length; i++)
	{
		eventstr[i-1] = data[i];
	}

	slength = length-1;
	AdrH	 = eventstr[3];
	AdrM	 = eventstr[4];
	AdrL	 = eventstr[5];
	DataMSB	 = eventstr[6];
	DataLSB	 = eventstr[7];

	analyze_sysex();

	return print_str;
}


//**************************************************************************
//*
//*		analyze_sysex
//*		Analyze the MIDI-message "SysEx" (Status 0xf0, message ends by 0x7f)
//*
//**************************************************************************

void SysExEventProt::analyze_sysex() // SysEx found
{

	int i = 0;
	unsigned char c = eventstr[0];
	if (eventstr[0] != 0x43)
	{
		sysex_non_yamaha();
	}
	else
	{
		analyze_sysex_yamaha(); // Yamaha
	}
	return;
}


//**************************************************************************
//*
//*		sysex_non_yamaha
//*		Analyze the MIDI-message "SysEx" (Status 0xf0, message ends by 0x7f)
//*		others than manufactor Yamaha
//*
//**************************************************************************

void SysExEventProt::sysex_non_yamaha()
{
	CString r; // used for formatted Output
	switch (eventstr[0])
	{
	case 0x41:
		if ((eventstr[1] == 0x10) &&
			(eventstr[2] == 0x42) &&
			(eventstr[3] == 0x12) &&
			(eventstr[4] == 0x40) &&
			(eventstr[5] == 0x00) &&
			(eventstr[6] == 0x7f) &&
			(eventstr[7] == 0x00) &&
			(eventstr[8] == 0x41)    )
		{ // GS ON
			print_str += "Turn TG300B (Roland GS Emulation) On";
		}
		else
		{
			print_str += "Unknown Roland SysEx";
		}
		break;
	case 0x7e: // Non-Realtime
		if ((eventstr[2] == 0x08) && (eventstr[3] == 0x08))
		{
			// Scale/Octave Tuning (GM2)
			r.Format("Scale/Octave Tuning (GM2), byte1(hex)=%2.2x, byte2(hex)=%2.2x, byte3(hex)=%2.2x, cent=%i",
				eventstr[4],eventstr[5],eventstr[6],(char)eventstr[7]-64);
		}
		else
		{
			if (eventstr[2]==0x09)
			{
				switch (eventstr[3])
				{
				case 0x01:
					r.Format("Turn General Midi System On");
					break;
				case 0x02:
					r.Format("Turn General Midi System Off");
					break;
				case 0x03:
					r.Format("Turn General Midi2 (GM2) System On");
					break;
				default:
					r.Format("unknown Universal Non Real Time");
					break;
				}
			}
			else
			{
				r.Format("unknown Universal Non Real Time");
			}
		}
		print_str += r;
		break;
	case 0x7f: // Universal Real Time
		if (eventstr[2] == 0x04)   // Device Control Message
		{
			switch (eventstr[3])
			{
			case 0x01:
				{
					int volume = eventstr[5]*128 + eventstr[4];
					r.Format("Master Volume, val=%i",volume);
					break;
				}
			case 0x03:
				{
					int ftuning = eventstr[5]*128 + eventstr[4];
					r.Format("Master Fine Tuning, val=%i",ftuning);
					break;
				}
			case 0x04:
				{
					int ctuning = eventstr[5];
					r.Format("Master Coarse Tuning, val=%i",ctuning);
					break;
				}
			case 0x05:
				{
					switch (eventstr[8])
					{
					case 0x01:
						{
							r.Format("Reverb Parameter, pp=%i, vv=%i",
								eventstr[9],eventstr[10]);
							break;
						}
					case 0x02:
						{
							r.Format("Chorus Parameter, pp=%i, vv=%i",
								eventstr[9],eventstr[10]);
							break;
						}
					default:
						{
							r.Format("unknown Universal Real Time");
						}
					}
					break;
				}
			default:
				{
					r.Format("unknown Universal Real Time");
				}
			}
			print_str += r;
		}
		else
		{
			switch (eventstr[2])
			{
			case 0x09:
				{
					const CString ctext[7] =
					{"Pitch",
					"Filter Cutoff",
					"Amplitude",
					"LFO Pitch",
					"LFO Filter",
					"LFO Amplitude",
					"unknown"};

					switch (eventstr[3])
					{
					case 0x01:
						{
							CString type = ctext[eventstr[5]<6?eventstr[5]:6];
							r.Format("Aftertouch %s , chan=%i, data(hex)=%2.2x",
								type,eventstr[4]+1,eventstr[6]);
							break;
						}
					case 0x03:
						{
							CString type = ctext[eventstr[6]<6?eventstr[6]:6];
							r.Format("Control Change %s, chan=%i, contr-no(hex)=%2.2x, data(hex)=%2.2x",
								type, eventstr[4]+1,eventstr[5],eventstr[7]);
							break;
						}
					default:
						{
							r.Format("unknown Universal Real Time");
						}
					}
					break;
				}
			case 0x0a:
				{
					r.Format("Key-Based Instrument Control, chan=%i, key=%i, contr-no(hex)=%2.2x, data(hex)=%2.2x",
						eventstr[4]+1,eventstr[5], eventstr[6], eventstr[7]);
					break;
				}
			default:
				{
					r.Format("unknown Universal Real Time");
				}
			}
			print_str += r;
		}
		break;
	default:
		{
			// weder "Turn General Midi System On" noch Roland Emulation noch Yamaha sysex
			r.Format("Manufactor %s (%2.2x) not documented",
				manufactor[eventstr[0]],eventstr[0]);
			print_str += r;
		}
	}
}

//**************************************************************************
//*
//*		analyze_sysex_yamaha
//*		Analyze the MIDI-message "SysEx" (Status 0xf0, message ends by 0x7f)
//*		of the manufactor Yamaha (Id 0x43)
//*
//**************************************************************************

void SysExEventProt::analyze_sysex_yamaha()
{
	// eventstr[0] ist 0x43 (Yamaha Kennung)
	// Es werden jetzt die Bytes eventstr[1]
	// bis eventstr[slength-2] analysiert.

	CString r; // used for formatted Output

	// Switch über die sysex-Typen

	switch (eventstr[1])
	{
	case 0x00:
		{
			if (eventstr[2]==0x4c)
			{
				int bytecount = (eventstr[3]<<7)+eventstr[4];
				r.Format("Bulk Dump: Bytecount %i, Adress %2.2x %2.2x %2.2x, Data ...",
					bytecount, eventstr[5], eventstr[6], eventstr[7]);
			}
			else
			{
				r.Format("Adress %2.2x %2.2x %2.2x not yet documented",
					eventstr[1], eventstr[2], eventstr[3]);
			}
			print_str += r;
		}
		break;
	case 0x10:
		xg_par_change();
		break;
	case 0x20:
		if (eventstr[2]!=0x4c)
		{
			r.Format("SysEx not yet documented ");
			print_str += r;
			break;
		}
		print_str += "Dump Request ";
		switch (AdrH)
		{
		case 0x02:
			if (AdrM==0x01)
			{
				switch (AdrL)
				{
				case 0x00:
					print_str += "Reverb; no 1";
					break;
				case 0x10:
					print_str += "Reverb; no 2";
					break;
				case 0x20:
					print_str += "Chorus; no 1";
					break;
				case 0x30:
					print_str += "Chorus; no 2";
					break;
				case 0x40:
					print_str += "Variation; no 1";
					break;
				case 0x70:
					print_str += "Variation; no 2";
					break;
				default:
					print_str += "? ";
					break;
				}
			}
			else
			{
				if ((AdrM==0x40)&&(AdrL==0x00))
				{
					print_str += "Multi EQ ";
				}
				else
				{
					print_str += "? ";
				}
				break;
			}
			break;
		case 0x03:
			if ((AdrM==0xfe)||((int)AdrM<=0x0f))
			{
				CString s;
				if (AdrM==0xfe)
				{
					s = "Insertion Efx ";
				}
				else
				{
					s.Format("Insertion, Part %i; no ",AdrM+1);
				}
				print_str += s;
				switch (AdrL)
				{
				case 0x00:
					print_str += "1 ";
					break;
				case 0x20:
					print_str += "2 ";
					break;
				case 0x30:
					print_str += "3 ";
					break;
				default:
					print_str += "? ";
					break;
				}
				break;
			}
			else
			{
				r.Format("Not yet documented ");
				print_str += r;
				break;
			}
			break;
		case 0x04:
			print_str += "Vocal Harmony; no ";
			switch(AdrL)
			{
			case 0x00:
				print_str += "1 ";
				break;
			case 0x14:
				print_str += "2 ";
				break;
			case 0x20:
				print_str += "3 ";
				break;
			default:
				print_str += "? ";
				break;
			}
			break;
		case 0x08:
			print_str += "Multi Part, Part ";
			{
				CString part;
				part.Format("%i; no ",AdrM+1);
				print_str += part;
				switch (AdrL)
				{
				case 0x00:
					print_str += "1 ";
					break;
				case 0x30:
					print_str += "2 ";
					break;
				default:
					print_str += "? ";
					break;
				}
			}
			break;
		default:
			r.Format("Not yet documented ");
			print_str += r;
			break;
		}
		break;
	case 0x60: // Type unknown, I think it is as following
		if (eventstr[2]==0x7d)
		{
			print_str += "Keyboard Stop";
		}
		else
		{
			if (eventstr[2]==0x7a)
			{
				print_str += "Keyboard Start";
			}
			else undocumented_type();
		}
		break;
	case 0x73:
		clavinova();
		break;
	case 0x76:
		print_str += "Type 76 (Yamaha Style)";
		break;
	case 0x7e:
		style();
		break;
	default:
		r.Format("Type %2.2x not yet documented",eventstr[1]);
		print_str += r;
	}

	return;
}

//**************************************************************************
//*
//*		xg_par_change
//*		Analyze the MIDI-message "SysEx; Typ 0x10" 	of Yamaha
//*
//**************************************************************************

void SysExEventProt::xg_par_change()
{
	// sysex Typ eventstr[1] ist 0x10. (3-6-3-1-2)
	// Es werden jetzt die Bytes eventstr[3]
	// bis eventstr[slength-2] (AdrH, AdrM, AdrL, DataMSB, DataLSB) analysiert.

	CString r; // used for formatted Output

	if (eventstr[2]==0x4c)
	{
		print_str += "(XG) ";
	}
	else
	{
		r.Format("(unknown Mod. %2.2x) ",eventstr[2]);
		print_str += r;
	}

	// switch über High Address
	switch (AdrH)
	{
	case 0x00: // Address 00 xx xx, MIDI Par. Change table (System)
		switch (AdrM)
		{
		case 0x00: // Address 00 00 xx, SysEx System
			switch (AdrL)
			{
			case 0x00:
			case 0x01:
			case 0x02:
			case 0x03:
				prot_fmt_text("Master Tune, Data %i ",DataMSB);
				break;
			case 0x04:
				prot_fmt_text("Master Volume %i",DataMSB);
				break;
			case 0x06:
				prot_fmt_text("Transpose %i ", DataMSB-64);
				break;
			case 0x7d:
				prot_fmt_text("Drum Setup Reset, no. %i ",DataMSB);
				break;
			case 0x7e:
				prot_fmt_text("XG System On %s ",DataMSB==0?"":"??");
				break;
			case 0x7f: // Reset to factory defaults!! Never embedded in a Midi File
				prot_fmt_text("All Parameters Reset %s ",DataMSB==0?"":"unknown Data");
				break;
			default:
				prot_fmt_text("Unknown Low Address %2.2x ",AdrL);
				break;
			}
			break;
			default:
				prot_fmt_text("Unknown Mid Address %2.2x ", AdrM);
				break;
		}
		break;

		case 0x02: // Address 02 0n xx,
			xg_EFFECT1();
			break;

	case 0x03: // Address 03 0n xx
		xg_EFFECT2();
		break;
	case 0x04:
		if (AdrM != 0)
		{
			not_documented();
			break;
		}
		prot_fmt_text("(Spec. Eff.) ");
		switch (AdrL)
		{
		case 0x00:  // AdrL, Vocal Harmony
			prot_fmt_text("VH ");
			switch (DataMSB)
			{
			case 0x40:
				switch (DataLSB)
				{
				case 0x00:
					prot_fmt_text("Thru ");
					break;
				default:
					not_documented();
					break;
				}
				break;

			case 0x0c:	// F0 43 10 4C 04 00 00 0C xx F7
				switch (DataLSB)
				{
				case 0x00:
					prot_fmt_text("StandardDuet ");
					break;
				case 0x01:
					prot_fmt_text("StandardTrio ");
					break;
				case 0x02:
					prot_fmt_text("StandardQuartet ");
					break;
				case 0x03:
					prot_fmt_text("JazzyQuartet ");
					break;
				case 0x04:
					prot_fmt_text("SchlagerTrio ");
					break;
				case 0x05:
					prot_fmt_text("Destiny's Pop ");
					break;
				case 0x06:
					prot_fmt_text("Vocoder");
					break;
				case 0x07:
					prot_fmt_text("VocoderMono ");
					break;
				case 0x08:
					prot_fmt_text("DetuneVoice ");
					break;
				case 0x09:
					prot_fmt_text("PerfectFourth ");
					break;
				case 0x0A:
					prot_fmt_text("SingCMajorScale ");
					break;
				case 0x0B:
					prot_fmt_text("BalladChoir ");
					break;
				case 0x0C:
					prot_fmt_text("ChurchChoir ");
					break;
				case 0x0D:
					prot_fmt_text("GregorianChoir ");
					break;
				case 0x0E:
					prot_fmt_text("GospelChoir ");
					break;
				case 0x0F:
					prot_fmt_text("AlpenGirls ");
					break;
				case 0x10:
					prot_fmt_text("CountryRock ");
					break;
				case 0x11:
					prot_fmt_text("R&BDiva ");
					break;
				case 0x12:
					prot_fmt_text("ClosedPopChicks ");
					break;
				case 0x13:
					prot_fmt_text("Bob->Mary ");
					break;
				case 0x14:
					prot_fmt_text("Mary->Bob ");
					break;
				case 0x15:
					prot_fmt_text("JazzySisters ");
					break;
				case 0x16:
					prot_fmt_text("QuartetOnStage ");
					break;
				case 0x17:
					prot_fmt_text("KidsChoir ");
					break;
				case 0x21:
					prot_fmt_text("StudioVocals ");
					break;
				case 0x22:
					prot_fmt_text("VocalDoubler ");
					break;
				case 0x23:
					prot_fmt_text("Rock&Roll ");
					break;
				case 0x24:
					prot_fmt_text("TempoCross ");
					break;
				case 0x25:
					prot_fmt_text("HeavyVoice ");
					break;
				case 0x26:
					prot_fmt_text("TelephoneChoir ");
					break;
				case 0x27:
					prot_fmt_text("LikeThe80s ");
					break;
				case 0x28:
					prot_fmt_text("Gramophone ");
					break;
				case 0x29:
					prot_fmt_text("PokerPhaser ");
					break;
				case 0x2A:
					prot_fmt_text("CosmicChoir ");
					break;
				case 0x2B:
					prot_fmt_text("QueenOfPop ");
					break;
				case 0x2C:
					prot_fmt_text("FlangingVocals ");
					break;
				case 0x2D:
					prot_fmt_text("DelayedHarmony ");
					break;
				case 0x2E:
					prot_fmt_text("ChorusChoir ");
					break;
				case 0x2F:
					prot_fmt_text("BohemianVocod ");
					break;
				case 0x30:
					prot_fmt_text("RobotVoice ");
					break;
				default: // DataLSB
					not_documented();
					break;
				}
				break;

			case 0x0D: // Synth Vocoder Type // F0 43 10 4C 04 00 00 0D xx F7
				switch (DataLSB)
				{
				case 0x00:
					prot_fmt_text("SynthVocoder SimpleSaw ");
					break;
				case 0x01:
					prot_fmt_text("SynthVocoder FatSaw ");
					break;
				case 0x02:
					prot_fmt_text("SynthVocoder SyncSaw ");
					break;
				case 0x03:
					prot_fmt_text("SynthVocoder StrongDetune ");
					break;
				case 0x04:
					prot_fmt_text("SynthVocoder VPPad ");
					break;
				case 0x05:
					prot_fmt_text("SynthVocoder ChoirWithYou ");
					break;
				case 0x06:
					prot_fmt_text("SynthVocoder Organ ");
					break;
				case 0x07:
					prot_fmt_text("SynthVocoder Sweeping ");
					break;
				case 0x08:
					prot_fmt_text("SynthVocoder Atmosphere ");
					break;
				case 0x09:
					prot_fmt_text("SynthVocoder AmbientFX ");
					break;
				default: // DataLSB
					not_documented();
					break;
				}
				break;

			case 0x59: // Tyros:  F0 43 10 4C 04 00 00 59 xx F7
				switch (DataLSB)
				{
				case 0x00:
					prot_fmt_text("Vocoder XG ");
					break;
				case 0x10:
					prot_fmt_text("Vocoder AutoU ");
					break;
				case 0x11:
					prot_fmt_text("Vocoder AutoL ");
					break;
				case 0x12:
					prot_fmt_text("Vocoder ModeU ");
					break;
				case 0x13:
					prot_fmt_text("Vocoder ModeL ");
					break;
				case 0x14:
					prot_fmt_text("Vocoder GirlU ");
					break;
				case 0x15:
					prot_fmt_text("Vocoder GirlL ");
					break;
				case 0x16:
					prot_fmt_text("Vocoder PichU ");
					break;
				case 0x17:
					prot_fmt_text("Vocoder PichL ");
					break;
				case 0x18:
					prot_fmt_text("Vocoder KaraokeAuto ");
					break;
				case 0x19:
					prot_fmt_text("Vocoder KaraokeMode ");
					break;
				case 0x1a:
					prot_fmt_text("Vocoder KaraokeGirl ");
					break;
				case 0x1b:
					prot_fmt_text("Vocoder KaraokePich ");
					break;
				case 0x40:
					prot_fmt_text("Vocoder ChordalXG ");
					break;
				case 0x50:
					prot_fmt_text("Vocoder StandardDuet ");
					break;
				case 0x51:
					prot_fmt_text("Vocoder Closed GirlDuet ");
					break;
				case 0x52:
					prot_fmt_text("Vocoder Lisa&Tina ");
					break;
				case 0x53:
					prot_fmt_text("Vocoder CountryMen ");
					break;
				case 0x54:
					prot_fmt_text("Vocoder FalsetDuet ");
					break;
				case 0x55:
					prot_fmt_text("Vocoder ACapellaBoy ");
					break;
				case 0x56:
					prot_fmt_text("Vocoder ACapellaMix ");
					break;
				case 0x57:
					prot_fmt_text("Vocoder MenChoir ");
					break;
				case 0x58:
					prot_fmt_text("Vocoder WomenChoir ");
					break;
				case 0x59:
					prot_fmt_text("Vocoder CountryGirls ");
					break;
				case 0x5a:
					prot_fmt_text("Vocoder ClosedChoir ");
					break;
				case 0x5b:
					prot_fmt_text("Vocoder MixedChoir ");
					break;
				case 0x5c:
					prot_fmt_text("Vocoder FalsettTrio ");
					break;
				case 0x5d:
					prot_fmt_text("Vocoder SingB+G ");
					break;
				case 0x5e:
					prot_fmt_text("Vocoder DreamGirls ");
					break;
				case 0x5f:
					prot_fmt_text("Vocoder FalACapella ");
					break;
				case 0x60:
					prot_fmt_text("Vocoder BarberShop ");
					break;
				case 0x61:
					prot_fmt_text("Vocoder DiatonicJazz ");
					break;
				case 0x62:
					prot_fmt_text("Vocoder DiatonicGirl ");
					break;
				case 0x63:
					prot_fmt_text("Vocoder ACapellaDia ");
					break;
				case 0x64:
					prot_fmt_text("Vocoder FalsettoDia ");
					break;
				case 0x65:
					prot_fmt_text("Vocoder JazzMenChoir ");
					break;
				case 0x66:
					prot_fmt_text("Vocoder JazzWomenChoir ");
					break;
				case 0x67:
					prot_fmt_text("Vocoder JazzClosedChoir ");
					break;
				case 0x68:
					prot_fmt_text("Vocoder JazzMixedChoir ");
					break;
				case 0x69:
					prot_fmt_text("Vocoder FalsetJazz ");
					break;
				case 0x6a:
					prot_fmt_text("Vocoder 2UnisonLow ");
					break;
				case 0x6b:
					prot_fmt_text("Vocoder 2UnisonHigh ");
					break;
				case 0x6c:
					prot_fmt_text("Vocoder 3UnisonLow ");
					break;
				case 0x6d:
					prot_fmt_text("Vocoder 3UnisonHigh ");
					break;
				case 0x6e:
					prot_fmt_text("Vocoder Voice&Inst ");
					break;
				case 0x6f:
					prot_fmt_text("Vocoder CountryQuartet ");
					break;
				case 0x70:
					prot_fmt_text("Vocoder GospelDiva ");
					break;
				case 0x71:
					prot_fmt_text("Vocoder SistersTrio ");
					break;
				case 0x72:
					prot_fmt_text("Vocoder JazzQuartet ");
					break;
				case 0x73:
					prot_fmt_text("Vocoder HighMaleQuartet ");
					break;
				case 0x74:
					prot_fmt_text("Vocoder LadiesQuartet ");
					break;
				case 0x75:
					prot_fmt_text("Vocoder ClosedMenQuartet ");
					break;
				case 0x76:
					prot_fmt_text("Vocoder ACapellaMenQuartet ");
					break;
				case 0x77:
					prot_fmt_text("Vocoder MixACapellaQuartet ");
					break;
				case 0x78:
					prot_fmt_text("Vocoder JazzSisters ");
					break;
				case 0x79:
					prot_fmt_text("Vocoder Pop Vocal ");
					break;
				default: // DataLSB
					not_documented();
					break;
				}
				break;

				case 0x5A: // F0 43 10 4C 04 00 00 5A xx F7
					switch (DataLSB)
					{
					case 0x00:
						prot_fmt_text("ChordalXG ");
						break;
					case 0x10:
						prot_fmt_text("Chordal StdDuet ");
						break;
					case 0x11:
						prot_fmt_text("Chordal GirlDuet ");
						break;
					case 0x12:
						prot_fmt_text("Chordal Lisa&Tina ");
						break;
					case 0x13:
						prot_fmt_text("Chordal CountryMen ");
						break;
					case 0x14:
						prot_fmt_text("Chordal FalsetDuet ");
						break;
					case 0x15:
						prot_fmt_text("Chordal ACapellaBoy ");
						break;
					case 0x16:
						prot_fmt_text("Chordal ACapellaMix ");
						break;
					case 0x17:
						prot_fmt_text("Chordal MenChoir ");
						break;
					case 0x18:
						prot_fmt_text("Chordal WomenChoir ");
						break;
					case 0x19:
						prot_fmt_text("Chordal CountryGirls ");
						break;
					case 0x1a:
						prot_fmt_text("Chordal ClosedChoir ");
						break;
					case 0x1b:
						prot_fmt_text("Chordal MixedChoir ");
						break;
					case 0x1c:
						prot_fmt_text("Chordal FalsetTrio ");
						break;
					case 0x1d:
						prot_fmt_text("Chordal SingB+G ");
						break;
					case 0x1e:
						prot_fmt_text("Chordal DreamGirls ");
						break;
					case 0x1f:
						prot_fmt_text("Chordal FalsetACapella ");
						break;
					case 0x20:
						prot_fmt_text("Chordal Barbershop ");
						break;
					case 0x21:
						prot_fmt_text("Chordal DiatonicJazz ");
						break;
					case 0x22:
						prot_fmt_text("Chordal DiatonicGirl ");
						break;
					case 0x23:
						prot_fmt_text("Chordal ACapellaDiatonic ");
						break;
					case 0x24:
						prot_fmt_text("Chordal FalsettoDiatonic ");
						break;
					case 0x25:
						prot_fmt_text("Chordal JazzMenChoir ");
						break;
					case 0x26:
						prot_fmt_text("Chordal JazzWomenChoir ");
						break;
					case 0x27:
						prot_fmt_text("Chordal JazzClosedChoir ");
						break;
					case 0x28:
						prot_fmt_text("Chordal JazzMixedChoir ");
						break;
					case 0x29:
						prot_fmt_text("Chordal FalsetJazz ");
						break;
					case 0x2a:
						prot_fmt_text("Chordal 2UnisonoLow ");
						break;
					case 0x2b:
						prot_fmt_text("Chordal 2UnisonoHigh ");
						break;
					case 0x2c:
						prot_fmt_text("Chordal 3UnisonoLow ");
						break;
					case 0x2d:
						prot_fmt_text("Chordal 3UnisonoHigh ");
						break;
					case 0x2e:
						prot_fmt_text("Chordal Voice&Instrument ");
						break;
					case 0x2f:
						prot_fmt_text("Chordal CountryQuartet ");
						break;
					case 0x30:
						prot_fmt_text("Chordal GospelDiva ");
						break;
					case 0x31:
						prot_fmt_text("Chordal SistersTrio ");
						break;
					case 0x32:
						prot_fmt_text("Chordal JazzQuartet ");
						break;
					case 0x33:
						prot_fmt_text("Chordal HighMaleQuartet ");
						break;
					case 0x34:
						prot_fmt_text("Chordal LadiesQuartet ");
						break;
					case 0x35:
						prot_fmt_text("Chordal ClosedMenQuartet ");
						break;
					case 0x36:
						prot_fmt_text("Chordal ACapellaMenQuartet ");
						break;
					case 0x37:
						prot_fmt_text("Chordal MixedACapellaQuartet ");
						break;
					case 0x38:
						prot_fmt_text("Chordal JazzSisters ");
						break;
					case 0x39:
						prot_fmt_text("Chordal PopVocal ");
						break;
					case 0x40:
						prot_fmt_text("Chordal VocoderXG ");
						break;
					case 0x50:
						prot_fmt_text("Chordal VocodAutoU ");
						break;
					case 0x51:
						prot_fmt_text("Chordal VocodAutoL ");
						break;
					case 0x52:
						prot_fmt_text("Chordal VocoderModeU ");
						break;
					case 0x53:
						prot_fmt_text("Chordal VocoderModeL ");
						break;
					case 0x54:
						prot_fmt_text("Chordal VocoderGirlU ");
						break;
					case 0x55:
						prot_fmt_text("Chordal VocoderGirlL ");
						break;
					case 0x56:
						prot_fmt_text("Chordal VocoderPichU ");
						break;
					case 0x57:
						prot_fmt_text("Chordal VocoderPichL ");
						break;
					case 0x58:
						prot_fmt_text("Chordal KaraokeAuto ");
						break;
					case 0x59:
						prot_fmt_text("Chordal KaraokeMode ");
						break;
					case 0x5a:
						prot_fmt_text("Chordal KaraokeGirl ");
						break;
					case 0x5b:
						prot_fmt_text("Chordal KaraokePich ");
						break;
					default: // DataLSB
						not_documented();
						break;
				}
				break;

				case 0x5b:// F0 43 10 4C 04 00 00 5B xx F7
					switch (DataLSB)
					{
					case 0x00:
						prot_fmt_text("Detune XG ");
						break;
					default:
						not_documented();
						break;
					}
				break;

				case 0x5c: // F0 43 10 4C 04 00 00 5C xx F7
					switch (DataLSB)
					{
					case 0x00:
						prot_fmt_text("ChromaticXG ");
						break;
					case 0x09:
						prot_fmt_text("Chromat XG ");
						break;
					case 0x10:
						prot_fmt_text("Sing Bass ");
						break;
					case 0x11:
						prot_fmt_text("Speedy Mouse ");
						break;
					default:
						not_documented();
						break;
					}
				break;

				default: // DataMSB
						not_documented();
						break;
			}
			break;

			case 0x02: // AdrL, Harmony Mode
				prot_fmt_text("VH Harmony Mode %i ",DataMSB);
				break;

			case 0x03: // AdrL, Harmony Gender Type
				prot_fmt_text("VH Harmony Gender Type ");
				switch (DataMSB)
				{
				case 0x00:
					prot_fmt_text("Off ");
					break;
				case 0x01:
					prot_fmt_text("Auto ");
					break;
				default:
					not_documented();
					break;
				}
				break;

			case 0x04: // Lead Gender Type
				prot_fmt_text("VH Lead Gender Type ");
				switch (DataMSB)
				{
				case 0x00:
					prot_fmt_text("Off ");
					break;
				case 0x01:
					prot_fmt_text("Unisono ");
					break;
				case 0x02:
					prot_fmt_text("Male ");
					break;
				case 0x03:
					prot_fmt_text("Female ");
					break;
				default:
					not_documented();
					break;
				}
				break;

			case 0x05: // AdrL, Lead Gender Depth
				prot_fmt_text("VH Lead Gender Depth %i",(int)DataMSB-64);
				break;

			case 0x06: // Lead Pitch Correction
				prot_fmt_text("VH Lead Pitch Correction ");
				switch (DataMSB)
				{
				case 0x00:
					prot_fmt_text("Free ");
					break;
				case 0x01:
					prot_fmt_text("Correct ");
					break;
				default:
					not_documented();
					break;
				}
				break;

			case 0x07: // AdrL: Auto Upper Gender Threshold
				prot_fmt_text("VH Auto Upper Gender Threshold ");
				if (DataMSB>12)
				{
					not_documented();
				}
				else
				{
					prot_fmt_text("%i ",DataMSB);
				}
				break;

			case 0x08: // AdrL: Auto Lower Gender Threshold
				prot_fmt_text("VH Auto Lower Gender Threshold ");
				if (DataMSB>12)
				{
					not_documented();
				}
				else
				{
					prot_fmt_text("%i ",DataMSB);
				}
				break;

			case 0x09: // AdrL, Upper Gender Depth
				prot_fmt_text("VH Upper Gender Depth %i",(int)DataMSB-64);
				break;

			case 0x0a: // AdrL, Lower Gender Depth
				prot_fmt_text("VH Lower Gender Depth %i",(int)DataMSB-64);
				break;

			case 0x0b:  // AdrL, Mic Volume / Balance
				prot_fmt_text("Mic Volume/Balance ");
				if (DataMSB==0)
				{
					not_documented();
					break;
				}
				if (DataMSB==64)
				{
					prot_fmt_text("L=H ");
					break;
				}
				if (DataMSB<64)
				{
					prot_fmt_text("L%i>H ",64-DataMSB);
					break;
				}
				if (DataMSB>64)
				{
					prot_fmt_text("L<H%i ",DataMSB-64);
					break;
				}
				break;

			case 0x0c:  // VH On/Off
				prot_fmt_text("VH ");

				if (DataMSB==64)
				{
					prot_fmt_text("AD (On) ");
				}
				else
				{
					prot_fmt_text("Off ");
				}
				break;

			case 0x0d: // AdrL:VH MW Insertion Control Depth
				prot_fmt_text("VH MW Insertion Control Depth %i",(int)DataMSB-64);
				break;

			case 0x0e: // AdrL:VH Bend Insertion Control Depth
				prot_fmt_text("VH Bend Insertion Control Depth %i",(int)DataMSB-64);
				break;

			case 0x0f: // AdrL:VH Cat Insertion Control Depth
				prot_fmt_text("VH Cat Insertion Control Depth %i",(int)DataMSB-64);
				break;

			case 0x10: // AdrL:VH AC1 Insertion Control Depth
				prot_fmt_text("VH AC1 Insertion Control Depth %i",(int)DataMSB-64);
				break;

			case 0x11: // AdrL:VH AC2 Insertion Control Depth
				prot_fmt_text("VH AC2 Insertion Control Depth %i",(int)DataMSB-64);
				break;

			case 0x14:  // Song Channel
				prot_fmt_text("VH Song Harmony Channel ");
				if ((unsigned char)DataMSB <= 15)
				{
					prot_fmt_text("%i ",DataMSB+1);
					break;
				}
				if ((unsigned char)DataMSB == 0x7f)
				{
					prot_fmt_text("Off ");
					break;
				}
				not_documented();
				break;

			case 0x15:  // Melody Channel
				prot_fmt_text("VH Song Melody Channel ");
				if ((unsigned char)DataMSB <= 15)
				{
					prot_fmt_text("%i ",DataMSB+1);
					break;
				}
				if ((unsigned char)DataMSB == 0x7f)
				{
					prot_fmt_text("Off ");
					break;
				}
				not_documented();
				break;


			case 0x16:  // Lead Output Level
				prot_fmt_text("Lead Output Level, Value %i",DataMSB);
				break;

			case 0x17:  // Harmony Output Level
				prot_fmt_text("Harmony Output Level, Value %i",DataMSB);
				break;

			case 0x18:  // Lead Vocal Effect Dry Level
				prot_fmt_text("Lead Vocal Effect Dry Level, Value %i",DataMSB);
				break;

			case 0x19:  // Harmony Vocal Effect Dry Level
				prot_fmt_text("Harmony Vocal Effect Dry Level, Value %i",DataMSB);
				break;

			case 0x1A:  // Lead Vocal Effect Send Level
				prot_fmt_text("Lead Vocal Effect Send Level, Value %i",DataMSB);
				break;
			
			case 0x1B:  // Harmony Vocal Effect Send Level
				prot_fmt_text("Harmony Vocal Effect Send Level, Value %i",DataMSB);
				break;

			case 0x20:  // Vocal Harmony Effect Parameter 11: Vibrato
				prot_fmt_text("VH Vibrato Depth ");
				{
					float val = (unsigned char)DataMSB;
					val = (float)((val/127.)*100.);
					prot_fmt_text("%i cent ",(int)val);
				}
				break;

			case 0x21:  // Vocal Harmony Effect Parameter 12: Vibrato
				prot_fmt_text("VH Vibrato Rate ");
				{
					float val = (unsigned char)DataMSB;
					val = (float)((val/127.)*12.6+0.1);
					prot_fmt_text("%.1f Hz ",val);
				}
				break;

			case 0x22:  // Vocal Harmony Effect Parameter 13: Vibrato
				prot_fmt_text("VH Vibrato Delay ");
				{
					float val = (unsigned char)DataMSB;
					val = (float)((val/127.)*2.54);
					prot_fmt_text("%.2f sec ",val);
				}
				break;

			case 0x23:  // Vocal Harmony Effect Parameter 14
				prot_fmt_text("VH Harmony 1 Volume %i",DataMSB);
				break;

			case 0x24:  // Vocal Harmony Effect Parameter 15
				prot_fmt_text("VH Harmony 2 Volume %i",DataMSB);
				break;

			case 0x25:  // Vocal Harmony Effect Parameter 16
				prot_fmt_text("VH Harmony 3 Volume %i",DataMSB);
				break;

			case 0x26:  // Vocal Harmony Effect Parameter 17
				prot_fmt_text("VH Harmony Effect Par. 17, Value %i",DataMSB);
				break;

			case 0x27:  // Vocal Harmony Effect Parameter 18
				prot_fmt_text("VH Harmony Effect Par. 18, Value %i",DataMSB);
				break;

			case 0x28:  // Vocal Harmony Effect Parameter 19
				prot_fmt_text("VH Harmony Effect Par. 19, Value %i",DataMSB);
				break;

			case 0x29:  // Vocal Harmony Effect Parameter 20
				prot_fmt_text("VH Harmony Effect Par. 20, Value %i",DataMSB);
				break;

			case 0x2a:  // Vocal Harmony Effect Parameter 21
				prot_fmt_text("VH Harmony Effect Par. 21, Value %i",DataMSB);
				break;

			case 0x2b:  // Vocal Harmony Effect Parameter 22
				prot_fmt_text("VH Harmony Effect Par. 22, Value %i",DataMSB);
				break;

			case 0x2c:  // Vocal Harmony Effect Parameter 23
				prot_fmt_text("VH Harmony Effect Par. 23, Value %i",DataMSB);
				break;

			case 0x2d:  // Vocal Harmony Effect Parameter 24
				prot_fmt_text("VH Harmony Effect Par. 24, Value %i",DataMSB);
				break;

			case 0x2e:  // Vocal Harmony Effect Parameter 25
				prot_fmt_text("VH Harmony Effect Par. 25, Value %i",DataMSB);
				break;

			case 0x2f:  // Vocal Harmony Effect Parameter 26
				prot_fmt_text("VH Harmony Effect Par. 26, Value %i",DataMSB);
				break;

			case 0x30:  // Vocal Harmony Effect Parameter 27
				prot_fmt_text("VH Harmony Effect Par. 27, Value %i",DataMSB);
				break;

			case 0x31:  // Vocal Harmony Effect Parameter 28
				prot_fmt_text("VH Harmony Effect Par. 28, Value %i",DataMSB);
				break;

			case 0x32:  // Vocal Harmony Effect Parameter 29
				prot_fmt_text("VH Harmony Effect Par. 29, Value %i",DataMSB);
				break;

			case 0x33:  // Vocal Harmony Effect Parameter 30
				prot_fmt_text("VH Harmony Effect Par. 30, Value %i",DataMSB);
				break;

			case 0x34:  // Vocal Harmony Effect Parameter 31
				prot_fmt_text("VH Harmony Effect Par. 31, Value %i",DataMSB);
				break;

			case 0x35:  // Vocal Harmony Effect Parameter 32
				prot_fmt_text("VH Harmony Effect Par. 32, Value %i",DataMSB);
				break;

			case 0x36:  // Vocal Harmony Effect Parameter 33
				prot_fmt_text("VH Harmony Effect Par. 33, Value %i",DataMSB);
				break;

			case 0x37:  // Vocal Harmony Effect Parameter 34
				prot_fmt_text("VH Harmony Effect Par. 34, Value %i",DataMSB);
				break;

			case 0x38:  // Vocal Harmony Effect Parameter 35
				prot_fmt_text("VH Harmony Effect Par. 35, Value %i",DataMSB);
				break;

			case 0x39:  // Vocal Harmony Effect Parameter 36
				prot_fmt_text("VH Harmony Effect Par. 36, Value %i",DataMSB);
				break;

			case 0x3a:  // Vocal Harmony Effect Parameter 37
				prot_fmt_text("VH Harmony Effect Par. 37, Value %i",DataMSB);
				break;

			case 0x3b:  // Vocal Harmony Effect Parameter 38
				prot_fmt_text("VH Harmony Effect Par. 38, Value %i",DataMSB);
				break;

			case 0x3c:  // Vocal Harmony Effect Parameter 39
				prot_fmt_text("VH Harmony Effect Par. 39, Value %i",DataMSB);
				break;

			case 0x3d:  // Vocal Harmony Effect Parameter 40
				prot_fmt_text("VH Harmony Effect Par. 40, Value %i",DataMSB);
				break;

			case 0x3e:  // Vocal Harmony Effect Parameter 41
				prot_fmt_text("VH Harmony Effect Par. 41, Value %i",DataMSB);
				break;

			case 0x3f:  // Vocal Harmony Effect Parameter 42
				prot_fmt_text("VH Harmony Effect Par. 42, Value %i",DataMSB);
				break;

			case 0x40:  // Vocal Harmony Effect Parameter 43
				prot_fmt_text("VH Harmony Effect Par. 43, Value %i",DataMSB);
				break;

			case 0x41:  // Vocal Harmony Effect Parameter 44
				prot_fmt_text("VH Harmony Effect Par. 44, Value %i",DataMSB);
				break;

			case 0x42:  // Vocal Harmony Effect Parameter 45
				prot_fmt_text("VH Harmony Effect Par. 45, Value %i",DataMSB);
				break;

			case 0x43:  // Vocal Harmony Effect Parameter 46
				prot_fmt_text("VH Harmony Effect Par. 46, Value %i",DataMSB);
				break;

			case 0x44:  // Vocal Harmony Effect Parameter 47
				prot_fmt_text("VH Harmony Effect Par. 47, Value %i",DataMSB);
				break;

			case 0x45:  // Vocal Harmony Effect Parameter 48
				prot_fmt_text("VH Harmony Effect Par. 48, Value %i",DataMSB);
				break;

			case 0x60:	// Vocal Effect Type MSB / LSB
				prot_fmt_text("Vocal Effect Type, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			case 0x62:	// Vocal Effect Parameter 1
				prot_fmt_text("Vocal Effect Par. 1, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			case 0x64:	// Vocal Effect Parameter 2
				prot_fmt_text("Vocal Effect Par. 2, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			case 0x66:	// Vocal Effect Parameter 3
				prot_fmt_text("Vocal Effect Par. 3, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			case 0x68:	// Vocal Effect Parameter 4
				prot_fmt_text("Vocal Effect Par. 4, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			case 0x6a:	// Vocal Effect Parameter 5
				prot_fmt_text("Vocal Effect Par. 5, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			case 0x6c:	// Vocal Effect Parameter 6
				prot_fmt_text("Vocal Effect Par. 6, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			case 0x6e:	// Vocal Effect Parameter 7
				prot_fmt_text("Vocal Effect Par. 7, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			case 0x70:	// Vocal Effect Parameter 8
				prot_fmt_text("Vocal Effect Par. 8, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			case 0x72:	// Vocal Effect Parameter 9
				prot_fmt_text("Vocal Effect Par. 9, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			case 0x74:	// Vocal Effect Parameter 10
				prot_fmt_text("Vocal Effect Par. 10, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			case 0x76:
				prot_fmt_text("Vocal Effect Switch %s",DataMSB==0?"OFF":"ON");
				break;

			case 0x77:
				prot_fmt_text("Vocal Effect Output Level, Value %i",DataMSB);
				break;

			case 0x7a:  // Vocal Effect Parameter 11
				prot_fmt_text("Vocal Effect Par. 11, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			case 0x7b:  // Vocal Effect Parameter 12
				prot_fmt_text("Vocal Effect Par. 12, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			case 0x7c:  // Vocal Effect Parameter 13
				prot_fmt_text("Vocal Effect Par. 13, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			case 0x7d:  // Vocal Effect Parameter 14
				prot_fmt_text("Vocal Effect Par. 14, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			case 0x7e:  // Vocal Effect Parameter 15
				prot_fmt_text("Vocal Effect Par. 15, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			case 0x7f:  // Vocal Effect Parameter 16
				prot_fmt_text("Vocal Effect Par. 16, MSB %i, LSB %i",DataMSB,DataLSB);
				break;

			default: // AdrL
				not_documented();
				break;
		}
		break;

	case 0x08: // Address 08 nn AdrL (Table 1-8, Multipart)
		prot_fmt_text("Multi Part, Part %2.1i ",AdrM+1);
		switch (AdrL)
		{
		case 0x00: // Address 08 nn 00
			prot_fmt_text("Not Used ");
			break;
		case 0x01: // Address 08 nn 01
			prot_fmt_text("Bank Select MSB %i",DataMSB);
			break;
		case 0x02: // Address 08 nn 02
			prot_fmt_text("Bank Select LSB %i",DataMSB);
			break;
		case 0x03: // Address 08 nn 03
			prot_fmt_text("Program Number %i",DataMSB);
			break;
		case 0x04: // Address 08 nn 04
			{
				char data[10] = "";
				if ((DataMSB&0x7f)<16)
				{
					sprintf(data,"%i",(DataMSB&0x7f)+1);
				}
				else
				{
					if ((DataMSB&0x7f)==0x7f)
						strcpy(data,"OFF");
					else
						strcpy(data,"");
				}
				prot_fmt_text("Rcv Channel %s",data);
			}
			break;
		case 0x05: // Address 08 nn 05
			prot_fmt_text("%s Mode",(DataMSB==0)?"Mono":"Poly");
			break;
		case 0x06: // Address 08 nn 06
			prot_fmt_text("%s",(DataMSB==0)?"Same Note Number Single":
			(DataMSB==1)?"Key On Assign Multi":
			(DataMSB==2)?"Key On Assign Inst (for DRUM)":"");
			break;
		case 0x07: // Address 08 nn 07
			{
				char* mode =
					DataMSB==0?"normal":
				DataMSB==1?"drum":
				DataMSB==2?"drumS1":
				DataMSB==3?"drumS2":"unknown";
				prot_fmt_text("Part Mode %s",mode);
			}
			break;
		case 0x08: // Address 08 nn 08
			prot_fmt_text("Note Shift %i Semitones",DataMSB-64);
			break;
		case 0x09: // Adress 08 nn 09
			{
				unsigned char detune_coarse = DataMSB&0x0f;
				prot_fmt_text("Detune coarse %2.2x",detune_coarse);
				break;
			}
			break;
		case 0x0a: // Address 08 nn 0a
			{
				unsigned char detune_fine = DataMSB&0x0f;
				//				double value = (double)((detune_coarse<<4)|detune_fine);
				//				double hz = (25.6/255.)*value-12.85;
				prot_fmt_text("Detune fine %2.2x",detune_fine);
			}
			break;
		case 0x0b: // Address 08 nn 0b
			prot_fmt_text("Volume %i",DataMSB);
			break;
		case 0x0c: // Address 08 nn 0c
			prot_fmt_text("Velocity Sense Depth %i",DataMSB);
			break;
		case 0x0d: // Address 08 nn 0d
			prot_fmt_text("Velocity Sense Offset %i",DataMSB);
			break;
		case 0x0e: // Address 08 nn 0e
			prot_fmt_text("Pan %i",DataMSB-64);
			break;
		case 0x0f: // Address 08 nn 0f
			prot_fmt_text("Note Limit Low, Note %s",GlobalUtilities::note(DataMSB));
			break;
		case 0x10: // Address 08 nn 0f
			prot_fmt_text("Note Limit High, Note %s",GlobalUtilities::note(DataMSB));
			break;
		case 0x11: // Address 08 nn 11
			prot_fmt_text("Dry Level %i",DataMSB);
			break;
		case 0x12: // Address 08 nn 12
			prot_fmt_text("Chorus Send %i",DataMSB);
			break;
		case 0x13: // Address 08 nn 13
			prot_fmt_text("Reverb Send %i",DataMSB);
			break;
		case 0x14: // Address 08 nn 14
			prot_fmt_text("Variation Send %i",DataMSB);
			break;
		case 0x15: // Address 08 nn 15
			prot_fmt_text("Vibrato Rate %i",DataMSB-64);
			break;
		case 0x16: // Address 08 nn 16
			prot_fmt_text("Vibrato Depth %i",DataMSB-64);
			break;
		case 0x17: // Address 08 nn 17
			prot_fmt_text("Vibrato Delay %i",DataMSB-64);
			break;
		case 0x18: // Address 08 nn 18
			prot_fmt_text("Filter Cutoff Freq. %i",DataMSB-64);
			break;
		case 0x19: // Address 08 nn 19
			prot_fmt_text("Filter Resonance %i",DataMSB-64);
			break;
		case 0x1a: // Address 08 nn 1a
			prot_fmt_text("EG Attack Time %i",DataMSB-64);
			break;
		case 0x1b: // Address 08 nn 1b
			prot_fmt_text("EG Decay Time %i",DataMSB-64);
			break;
		case 0x1c: // Address 08 nn 1c
			prot_fmt_text("EG Release Time %i",DataMSB-64);
			break;
		case 0x1d: // Address 08 nn 1d
			prot_fmt_text("MW Pitch Control %i [semitones]",DataMSB-64);
			break;
		case 0x1e: // Address 08 nn 1e
			prot_fmt_text("MW Filter Control %i [cent]",(19050*DataMSB)/127-9600);
			break;
		case 0x1f: // Address 08 nn 1f
			prot_fmt_text("MW Amp. Control %i%%",(200*DataMSB)/127-100);
			break;
		case 0x20: // Address 08 nn 20
			prot_fmt_text("MW LFO PMod Depth %i",DataMSB);
			break;
		case 0x21: // Address 08 nn 21
			prot_fmt_text("MW LFO FMod Depth %i",DataMSB);
			break;
		case 0x22: // Address 08 nn 22
			prot_fmt_text("MW LFO AMod Depth %i",DataMSB);
			break;
		case 0x23: // Address 08 nn 23
			prot_fmt_text("Bend Pitch Control %i [semitones]",DataMSB-64);
			break;
		case 0x24: // Address 08 nn 24
			prot_fmt_text("Bend Filter Control %i [cent]",(19050*DataMSB)/127-9600);
			break;
		case 0x25: // Address 08 nn 25
			prot_fmt_text("Bend Amp. Control %i%%",(200*DataMSB)/127-100);
			break;
		case 0x26: // Address 08 nn 26
			prot_fmt_text("Bend LFO PMod Depth %i",DataMSB);
			break;
		case 0x27: // Address 08 nn 27
			prot_fmt_text("Bend LFO FMod Depth %i",DataMSB);
			break;
		case 0x28: // Address 08 nn 28
			prot_fmt_text("Bend LFO AMod Depth %i",DataMSB);
			break;
		case 0x30: // Address 08 nn 30
			prot_fmt_text("Rcv Pitch Bend %i ",DataMSB);
			break;
		case 0x31: // Address 08 nn 31
			prot_fmt_text("Rcv CAT %i ",DataMSB);
			break;
		case 0x32: // Address 08 nn 32
			prot_fmt_text("Rcv Program Change %i ",DataMSB);
			break;
		case 0x33: // Address 08 nn 33
			prot_fmt_text("Rcv Cntrl Change %i ",DataMSB);
			break;
		case 0x34: // Address 08 nn 34
			prot_fmt_text("Rcv Patch %i ",DataMSB);
			break;
		case 0x35: // Address 08 nn 35
			prot_fmt_text("Rcv Note Message %s",DataMSB==0?": OFF":DataMSB==1?": ON":"");
			break;
		case 0x36: // Address 08 nn 36
			prot_fmt_text("Rcv RPN %i ",DataMSB);
			break;
		case 0x37: // Address 08 nn 37
			prot_fmt_text("Rcv NRPN %i ",DataMSB);
			break;
		case 0x38: // Address 08 nn 38
			prot_fmt_text("Rcv Modulation %i ",DataMSB);
			break;
		case 0x39: // Address 08 nn 39
			prot_fmt_text("Rcv Volume %i ",DataMSB);
			break;
		case 0x3a: // Address 08 nn 3a
			prot_fmt_text("Rcv Pan %i ",DataMSB);
			break;
		case 0x3b: // Address 08 nn 3b
			prot_fmt_text("Rcv Expression %i ",DataMSB);
			break;
		case 0x3c: // Address 08 nn 3c
			prot_fmt_text("Rcv Hold1 %i ",DataMSB);
			break;
		case 0x3d: // Address 08 nn 3d
			prot_fmt_text("Rcv Portamento %i ",DataMSB);
			break;
		case 0x3e: // Address 08 nn 3e
			prot_fmt_text("Rcv Soustain %i ",DataMSB);
			break;
		case 0x3f: // Address 08 nn 3f
			prot_fmt_text("Rcv Soft Pedal %i ",DataMSB);
			break;
		case 0x40: // Address 08 nn 40
			prot_fmt_text("Rcv Bank Select %i ",DataMSB);
			break;
		case 0x41: // Address 08 nn 41
			prot_fmt_text("Scale Tuning C: %i [cent]", DataMSB-64);
			break;
		case 0x42: // Address 08 nn 42
			prot_fmt_text("Scale Tuning C#: %i [cent]", DataMSB-64);
			break;
		case 0x43: // Address 08 nn 43
			prot_fmt_text("Scale Tuning D: %i [cent]", DataMSB-64);
			break;
		case 0x44: // Address 08 nn 44
			prot_fmt_text("Scale Tuning D#: %i [cent]", DataMSB-64);
			break;
		case 0x45: // Address 08 nn 45
			prot_fmt_text("Scale Tuning E: %i [cent]", DataMSB-64);
			break;
		case 0x46: // Address 08 nn 46
			prot_fmt_text("Scale Tuning F: %i [cent]", DataMSB-64);
			break;
		case 0x47: // Address 08 nn 47
			prot_fmt_text("Scale Tuning F#: %i [cent]", DataMSB-64);
			break;
		case 0x48: // Address 08 nn 48
			prot_fmt_text("Scale Tuning G: %i [cent]", DataMSB-64);
			break;
		case 0x49: // Address 08 nn 49
			prot_fmt_text("Scale Tuning G#: %i [cent]", DataMSB-64);
			break;
		case 0x4a: // Address 08 nn 4a
			prot_fmt_text("Scale Tuning A: %i [cent]", DataMSB-64);
			break;
		case 0x4b: // Address 08 nn 4b
			prot_fmt_text("Scale Tuning A#: %i [cent]", DataMSB-64);
			break;
		case 0x4c: // Address 08 nn 4c
			prot_fmt_text("Scale Tuning B: %i [cent]", DataMSB-64);
			break;
		case 0x4d: // Address 08 nn 4d
			prot_fmt_text("CAT Pitch Control %i [semitones]",DataMSB-64);
			break;
		case 0x4e: // Address 08 nn 4e
			prot_fmt_text("CAT Filter Control %i [cent]",(19050*DataMSB)/127-9600);
			break;
		case 0x4f: // Address 08 nn 4f
			prot_fmt_text("CAT Amp. Control %i%%",(200*DataMSB)/127-100);
			break;
		case 0x50: // Address 08 nn 50
			prot_fmt_text("CAT LFO PMod Depth %i",DataMSB);
			break;
		case 0x51: // Address 08 nn 51
			prot_fmt_text("CAT LFO FMod Depth %i",DataMSB);
			break;
		case 0x52: // Address 08 nn 52
			prot_fmt_text("CAT LFO AMod Depth %i",DataMSB);
			break;
		case 0x53: // Address 08 nn 53
			prot_fmt_text("Pat Pitch Control %i",DataMSB);
			break;
		case 0x54: // Address 08 nn 54
			prot_fmt_text("Pat Filter Control %i",DataMSB);
			break;
		case 0x55: // Address 08 nn 55
			prot_fmt_text("Pat Amplitude Control %i",DataMSB);
			break;
		case 0x56: // Address 08 nn 56
			prot_fmt_text("Pat lfo pmod depth %i",DataMSB);
			break;
		case 0x57: // Address 08 nn 57
			prot_fmt_text("Pat lfo fmod depth %i",DataMSB);
			break;
		case 0x58: // Address 08 nn 58
			prot_fmt_text("Pat lfo amod depth %i",DataMSB);
			break;
		case 0x59: // Address 08 nn 59
			prot_fmt_text("AC1 controller number %i",DataMSB);
			break;
		case 0x5a: // Address 08 nn 5a
			prot_fmt_text("AC1 Pitch Control %i",DataMSB);
			break;
		case 0x5b: // Address 08 nn 5b
			prot_fmt_text("AC1 Filter Control %i",DataMSB);
			break;
		case 0x5c: // Address 08 nn 5c
			prot_fmt_text("AC1 Amplitude Control %i",DataMSB);
			break;
		case 0x5d: // Address 08 nn 5d
			prot_fmt_text("AC1 lfo pmod depth %i",DataMSB);
			break;
		case 0x5e: // Address 08 nn 5e
			prot_fmt_text("AC1 lfo fmod depth %i",DataMSB);
			break;
		case 0x5f: // Address 08 nn 5f
			prot_fmt_text("AC1 lfo amod depth %i",DataMSB);
			break;
		case 0x60: // Address 08 nn 60
			prot_fmt_text("AC2 controller number %i",DataMSB);
			break;
		case 0x61: // Address 08 nn 61
			prot_fmt_text("AC2 Pitch Control %i",DataMSB);
			break;
		case 0x62: // Address 08 nn 62
			prot_fmt_text("AC2 Filter Control %i",DataMSB);
			break;
		case 0x63: // Address 08 nn 63
			prot_fmt_text("AC2 Amplitude Control %i",DataMSB);
			break;
		case 0x64: // Address 08 nn 64
			prot_fmt_text("AC2 lfo pmod depth %i",DataMSB);
			break;
		case 0x65: // Address 08 nn 65
			prot_fmt_text("AC2 lfo fmod depth %i",DataMSB);
			break;
		case 0x66: // Address 08 nn 66
			prot_fmt_text("AC2 lfo amod depth %i",DataMSB);
			break;
		case 0x67: // Address 08 nn 67
			prot_fmt_text("Portamento Switch %s",DataMSB==0?": OFF":DataMSB==1?": ON":"");
			break;
		case 0x68: // Address 08 nn 68
			prot_fmt_text("Portamento Time %i",DataMSB);
			break;
		case 0x69: //Address 08 nn 69
			prot_fmt_text("Pitch eg initial level %i", DataMSB);
			break;
		case 0x6a: //Address 08 nn 6a
			prot_fmt_text("Pitch eg initial level %i", DataMSB);
			break;
		case 0x6b: //Address 08 nn 6b
			prot_fmt_text("Pitch eg release level %i", DataMSB);
			break;
		case 0x6c: //Address 08 nn 6c
			prot_fmt_text("Pitch eg release time %i", DataMSB);
			break;
		case 0x6d: //Address 08 nn 6d
			prot_fmt_text("Velocity limit low %i", DataMSB);
			break;
		case 0x6e: //Address 08 nn 6e
			prot_fmt_text("Velocity limit high %i", DataMSB);
			break;
		case 0x70: //Address 08 nn 70
			prot_fmt_text("Not used");
			break;
		case 0x71: //Address 08 nn 71
			prot_fmt_text("Not used");
			break;
		case 0x72: // Address 08 nn 72
			prot_fmt_text("EQ BASS GAIN %i [dB]",(3*DataMSB)/16-11);
			break;
		case 0x73: // Address 08 nn 73
			prot_fmt_text("EQ TREBLE GAIN %i [dB]",(3*DataMSB)/16-11);
			break;
		case 0x76: // Address 08 nn 76
			prot_fmt_text("EQ BASS frequ. %i [Hz]",((DataMSB-4)*1968/6+320)/36);
			break;
		case 0x77: // Address 08 nn 77
			prot_fmt_text("EQ TREBLE frequ. %i [Hz]",(int)(((float)DataMSB-28.0)*(15500.0/30.0)+500.0));
			break;
		default:
			print_str += "Not used ";
			break;
		}
		break;
	case 0x0a: // Address 0a nn ADRL data
		prot_fmt_text("Part  %2.1i Offset Level Control ",AdrM+1);
		switch (AdrL)
		{
		case 0x40: // Address 0a nn 40
			prot_fmt_text("MW, data %i", DataMSB);
			break;
		case 0x41: // Address 0a nn 41
			prot_fmt_text("BEND, data %i", DataMSB);
			break;
		case 0x42: // Address 0a nn 42
			prot_fmt_text("CAT, data %i", DataMSB);
			break;
		case 0x43: // Address 0a nn 43
			prot_fmt_text("PAT, data %i", DataMSB);
			break;
		case 0x44: // Address 0a nn 44
			prot_fmt_text("AC1, data %i", DataMSB);
			break;
		case 0x45: // Address 0a nn 45
			prot_fmt_text("AC2, data %i", DataMSB);
			break;
		default:
			print_str += "Not used ";
			break;
		}
		break;
	case 0x10: // Address 10 nn AdrL (Table 1-9, A/D Part)
		prot_fmt_text("A/D Part, Number %i, ",AdrM);
		switch (AdrL)
		{
		case 0x04:
			{
				char data[10] = "";
				if ((DataMSB%0x7f)<16)
					sprintf(data,"%i",(DataMSB%0x7f)+1);
				else
					if ((DataMSB%0x7f)==0x7f)
						strcpy(data,"OFF");
					else
						strcpy(data,"");
					prot_fmt_text("Rcv Channel %s",data);
			}
			break;
		case 0x0b:
			prot_fmt_text("Volume %i",DataMSB);
			break;
		case 0x0e:
			prot_fmt_text("Pan %i",DataMSB-64);
			break;
		case 0x11:
			prot_fmt_text("Dry Level %i",DataMSB);
			break;
		case 0x12:
			prot_fmt_text("Chorus Send %i",DataMSB);
			break;
		case 0x13:
			prot_fmt_text("Reverb Send %i",DataMSB);
			break;
		case 0x14:
			prot_fmt_text("Variation Send %i",DataMSB);
			break;
		default:
			print_str += "Not used ";
			break;
		}
		break;

		case 0x30: // Drum Setup :Address AdrH=3n (n=channel), AdrM=note, AdrL=function, DataMSB
		case 0x31:
		case 0x32:
		case 0x33:
		case 0x34:
		case 0x35:
		case 0x36:
		case 0x37:
		case 0x38:
		case 0x39:
		case 0x3a:
		case 0x3b:
		case 0x3c:
		case 0x3d:
		case 0x3e:
		case 0x3f:
			print_str += "Drum Setup: chan ";
			prot_fmt_text("%i, ",(AdrH&0x0f)+1);
			prot_fmt_text("Note %s, ",GlobalUtilities::note(AdrM));
			switch (AdrL)
			{
			case 0x00:
				prot_fmt_text("Pitch (coarse) %i ",DataMSB-0x40);
				break;
			case 0x01:
				{
					unsigned short value = DataMSB;
					value <<=7;
					prot_fmt_text("Pitch (fine) %i ",DataMSB-0x40);
				}
				break;
			case 0x02:
				prot_fmt_text("Level %i",DataMSB);
				break;
			case 0x03:
				print_str += "Alternative Group ";
				if (DataMSB==0)
				{
					print_str += "Off";
				}
				else
				{
					prot_fmt_text("%i",DataMSB);
				}
				break;
			case 0x04:
				prot_fmt_text("Pan %i",DataMSB-64);
				break;
			case 0x05:
				prot_fmt_text("Reverb Send Level %2.1i ",DataMSB);
				break;
			case 0x06:
				prot_fmt_text("Chorus Send Level %2.1i ",DataMSB);
				break;
			case 0x07:
				prot_fmt_text("Variation Send Level %2.1i ",DataMSB);
				break;
			case 0x08:
				prot_fmt_text("Key Assign %s",DataMSB==0?"Single":DataMSB==1?"Multi":"");
				break;
			case 0x09:
				prot_fmt_text("Rcv Note Off: %s",DataMSB==0?"Off":DataMSB==1?"On":"");
				break;
			case 0x0a:
				prot_fmt_text("Rcv Note On: %s",DataMSB==0?"Off":DataMSB==1?"On":"");
				break;
			case 0x0b:
				prot_fmt_text("Filter Cutoff Freq %i",DataMSB-64);
				break;
			case 0x0c:
				prot_fmt_text("Filter Resonance %i",DataMSB-64);
				break;
			case 0x0d:
				prot_fmt_text("EG Attack Rate %i",DataMSB-64);
				break;
			case 0x0e:
				prot_fmt_text("EG Decay 1 Rate %i",DataMSB-64);
				break;
			case 0x0f:
				prot_fmt_text("EG Decay 2 Rate %i",DataMSB-64);
				break;
			case 0x20:
				prot_fmt_text("EQ Bass Gain %i",DataMSB-64);
				break;
			case 0x21:
				prot_fmt_text("EQ Treble Gain %i",DataMSB-64);
				break;
			case 0x24:
				prot_fmt_text("EQ Bass Frequency, Data = hex %2.2x",DataMSB);
				break;
			case 0x25:
				prot_fmt_text("EQ Treble Frequency, Data = hex %2.2x",DataMSB);
				break;
			default:
				print_str += "Not used ";
				break;
			}
			break;
		case 0x70:
			{
				prot_fmt_text("Assign Plugin Board, Type  = hex %2.2x, Part = %i",AdrM,DataMSB+1);
				break;
			}
		default:
				prot_fmt_text("High Adress %2.2x unknown ",AdrH);
	}
	return;
}


//**************************************************************************
//*
//*		xg_EFFECT1
//*		Analyze the MIDI-message "SysEx; Typ 0x10; AdrH 02"
//*		MIDI Par. Change (EFFECT 1) Reverb, Chorus and Variation
//*
//**************************************************************************

void SysExEventProt::xg_EFFECT1() // Adress 02 0n xx
{
	switch (AdrM)
	{
	case 0x01: // XG Effect Messages "f0 43 10 4c 02 01 .. .. f7" (Table 1-4)
		{
			switch (AdrL) // Low Address
			{
				// Part: SysEx Reverb
			case 0x00: // Reverb Type MSB/LSB, Address 02 01 00
				print_str += "Reverb Type ";
				if (hpmfi->xg_effects == NULL)
				{
					reverb_effect_type();
				}
				else
				{
					reverb_effect_type_effectfile();
				}
				break;
			case 0x02: // Address 02 01 02, Reverb Par. 1
			case 0x03: // Address 02 01 03, Reverb Par. 2
			case 0x04: // Address 02 01 04, Reverb Par. 3
			case 0x05: // Address 02 01 05, Reverb Par. 4
			case 0x06: // Address 02 01 06, Reverb Par. 5
			case 0x07: // Address 02 01 07, Reverb Par. 6
			case 0x08: // Address 02 01 08, Reverb Par. 7
			case 0x09: // Address 02 01 09, Reverb Par. 8
			case 0x0a: // Address 02 01 0a, Reverb Par. 9
			case 0x0b: // Address 02 01 0b, Reverb Par. 10
				print_str += "Reverb " + ((hpmfi->xg_effects)==NULL)?reverb_data_text():reverb_data_text_effectfile();
				break;
			case 0x0c: // Address 02 01 0c
				prot_fmt_text("Reverb Return %i ",DataMSB);
				break;
			case 0x0d:
				prot_fmt_text("Reverb Pan %i", DataMSB);
				break;
			case 0x10: // Address 02 01 10, Reverb Par. 11
			case 0x11: // Address 02 01 11, Reverb Par. 12
			case 0x12: // Address 02 01 12, Reverb Par. 13
			case 0x13: // Address 02 01 13, Reverb Par. 14
			case 0x14: // Address 02 01 14, Reverb Par. 15
			case 0x15: // Address 02 01 15, Reverb Par. 16
				print_str += "Reverb " + ((hpmfi->xg_effects)==NULL)?reverb_data_text():reverb_data_text_effectfile();
				break;
				// Part: SysEx Chorus
			case 0x20: // Address 02 01 20
				print_str += "Chorus Type ";
				if (hpmfi->xg_effects == NULL)
				{
					chorus_effect_type();
				}
				else
				{
					chorus_effect_type_effectfile();
				}
				break;
			case 0x22: // Address 02 01 22, Chorus Param. 1
			case 0x23: // Address 02 01 23, Chorus Param. 2
			case 0x24: // Address 02 01 24, Chorus Param. 3
			case 0x25: // Address 02 01 25, Chorus Param. 4
			case 0x26: // Address 02 01 26, Chorus Param. 5
			case 0x27: // Address 02 01 27, Chorus Param. 6
			case 0x28: // Address 02 01 28, Chorus Param. 7
			case 0x29: // Address 02 01 29, Chorus Param. 8
			case 0x2a: // Address 02 01 2a, Chorus Param. 9
			case 0x2b: // Address 02 01 2b, Chorus Param. 10
				print_str += "Chorus " + ((hpmfi->xg_effects)==NULL)?chorus_data_text():chorus_data_text_effectfile();
				break;
			case 0x2c: // Address 02 01 2c Chorus Return
				prot_fmt_text("Chorus Return %i ", DataMSB);
				break;
			case 0x2d: // Address 02 01 2d
				prot_fmt_text("Chorus Pan %i ", DataMSB-64);
				break;
			case 0x2e: // Address 02 01 2e
				prot_fmt_text("Send Chorus to Reverb %2.2x ",DataMSB);
				break;
			case 0x30: // Address 02 01 30, Chorus Param. 11
			case 0x31: // Address 02 01 31, Chorus Param. 12
			case 0x32: // Address 02 01 32, Chorus Param. 13
			case 0x33: // Address 02 01 33, Chorus Param. 14
			case 0x34: // Address 02 01 34, Chorus Param. 15
			case 0x35: // Address 02 01 35, Chorus Param. 16
				print_str += "Chorus " + ((hpmfi->xg_effects)==NULL)?chorus_data_text():chorus_data_text_effectfile();
				break;

			// Part: SysEx Variation
			case 0x40: // Address 02 01 40 Variation Type MSB/LSB
				print_str += "Variation Type ";
				if (hpmfi->xg_effects == NULL)
				{
					dsp_effect_type();
				}
				else
				{
					dsp_effect_type_effectfile();
				}
				break;
			case 0x42: // Address 02 01 42 Variation Parameter 1 MSB/LSB
			case 0x44: // Address 02 01 44 Variation Parameter 2 MSB/LSB
			case 0x46: // Address 02 01 46 Variation Parameter 3 MSB/LSB
			case 0x48: // Address 02 01 48 Variation Parameter 4 MSB/LSB
			case 0x4a: // Address 02 01 4a Variation Parameter 5 MSB/LSB
			case 0x4c: // Address 02 01 4c Variation Parameter 6 MSB/LSB
			case 0x4e: // Address 02 01 4e Variation Parameter 7 MSB/LSB
			case 0x50: // Address 02 01 50 Variation Parameter 8 MSB/LSB
			case 0x52: // Address 02 01 52 Variation Parameter 9 MSB/LSB
			case 0x54: // Address 02 01 54 Variation Parameter 10 MSB/LSB
				print_str += "Variation "+
					((hpmfi->xg_effects)==NULL)?dsp_data_text():dsp_data_text_effectfile();
				break;
			case 0x56: // Address 02 01 56 Variation Return
				prot_fmt_text("Variation Return %i ", DataMSB);
				break;
			case 0x57: // Address 02 01 57 Variation Pan
				prot_fmt_text("Variation Pan %i ", DataMSB);
				break;
			case 0x58: // Address 02 01 58 Send Var. to Reverb
				prot_fmt_text("Send Variation to Reverb %i ", DataMSB);
				break;
			case 0x59: // Address 02 01 59 Send Var. to Chorus
				prot_fmt_text("Send Variation to Chorus %i ", DataMSB);
				break;
			case 0x5a: // Address 02 01 5a Variation Connection
				prot_fmt_text("Variation Connection: %s ",
					DataMSB==0?"Insertion":DataMSB==1?"System":"");
				break;
			case 0x5b: // Address 02 01 5b Variation Part
				print_str += "Variation Part ";
				if (DataMSB<16)
				{
					prot_fmt_text("%i ", DataMSB+1);
				}
				else
				{
					if (DataMSB==64)
					{
						print_str += "AD1 ";
					}
					else
					{
						print_str += "OFF ";
					}
				}
				if (DataMSB==9)
				{
					print_str += "(default Drum Part) ";
				}
				break;
			case 0x5c: // Address 02 01 5c MW Var. Ctrl Depth.
				prot_fmt_text("MW Var. Ctrl Depth %i ", DataMSB);
				break;
			case 0x5d: // Address 02 01 5d PB Var. Ctrl Depth
				prot_fmt_text("PB Var. Ctrl Depth %i ", DataMSB);
				break;
			case 0x5e: // Address 02 01 5e CAT Var. Ctrl Depth
				prot_fmt_text("CAT Var. Ctrl Depth %i ", DataMSB);
				break;
			case 0x5f: // Address 02 01 5f ac1V.CD
				prot_fmt_text("AC1 Var. Crtl Depth %i ",DataMSB);
				break;
			case 0x60: // Address 02 01 60 ac1V.CD
				prot_fmt_text("AC2 Var. Crtl Depth %i ",DataMSB);
				break;
			case 0x70: // Address 02 01 70 Variation Parameter 11 MSB
			case 0x71: // Address 02 01 71 Variation Parameter 12 MSB
			case 0x72: // Address 02 01 72 Variation Parameter 13 MSB
			case 0x73: // Address 02 01 73 Variation Parameter 14 MSB
			case 0x74: // Address 02 01 74 Variation Parameter 15 MSB
			case 0x75: // Address 02 01 75 Variation Parameter 16 MSB
				print_str += "Variation "+
					((hpmfi->xg_effects)==NULL)?dsp_data_text():dsp_data_text_effectfile();
				break;
			default:
				not_documented();
				break;
			}
			break;
		}
	case 0x40:
		{
			switch (AdrL) // Low Address
			{ // Table 1-5, Realisierung 02 40 xx Midi Parameter Change MULTI EQ
			case 0x00: // Address 02 40 00 EQ Type
				prot_fmt_text("EQ Type %s ",	DataMSB==0?"FLAT":
				DataMSB==1?"JAZZ":
				DataMSB==2?"POPS":
				DataMSB==3?"ROCK":
				DataMSB==4?"CLASSIC":"unknown Type");
				break;
			case 0x01: // Address 02 40 01 EQ Gain 1
				prot_fmt_text("EQ Gain 1, %2.2x ",DataMSB);
				break;
			case 0x02: // Address 02 40 02 EQ Frequency 1
				prot_fmt_text("EQ Frequency 1, %2.2x ",DataMSB);
				break;
			case 0x03: // Address 02 40 03 EQ Q1
				prot_fmt_text("EQ Q1, %2.2x ",DataMSB);
				break;
			case 0x04: // Address 02 40 04 EQ Shape 1
				prot_fmt_text("EQ Shape 1, %2.2x ",DataMSB);
				break;
			case 0x05: // Address 02 40 05 EQ Gain 2
				prot_fmt_text("EQ Gain 2, %2.2x ",DataMSB);
				break;
			case 0x06: // Address 02 40 06 EQ Frequency 2
				prot_fmt_text("EQ Frequency 2, %2.2x ",DataMSB);
				break;
			case 0x07: // Address 02 40 07 EQ Q2
				prot_fmt_text("EQ Q2, %2.2x ",DataMSB);
				break;
			case 0x09: // Address 02 40 09 EQ Gain 3
				prot_fmt_text("EQ Gain 3, %2.2x ",DataMSB);
				break;
			case 0x0a: // Address 02 40 0a EQ Frequency 3
				prot_fmt_text("EQ Frequency 3, %2.2x ",DataMSB);
				break;
			case 0x0b: // Address 02 40 0b EQ Q3
				prot_fmt_text("EQ Q3, %2.2x ",DataMSB);
				break;
			case 0x0d: // Address 02 40 0d EQ Gain 4
				prot_fmt_text("EQ Gain 4, %2.2x ",DataMSB);
				break;
			case 0x0e: // Address 02 40 0e EQ Frequency 4
				prot_fmt_text("EQ Frequency 4, %2.2x ",DataMSB);
				break;
			case 0x0f: // Address 02 40 0f EQ Q4
				prot_fmt_text("EQ Q4, %2.2x ",DataMSB);
				break;
			case 0x11: // Address 02 40 11 EQ Gain 5
				prot_fmt_text("EQ Gain 5, %2.2x ",DataMSB);
				break;
			case 0x12: // Address 02 40 12 EQ Frequency 5
				prot_fmt_text("EQ Frequency 5, %2.2x ",DataMSB);
				break;
			case 0x13: // Address 02 40 13 EQ Q5
				prot_fmt_text("EQ Q5, %2.2x ",DataMSB);
				break;
			case 0x14: // Address 02 40 14 EQ Shape 5
				prot_fmt_text("EQ Shape 5, %2.2x ",DataMSB);
				break;
			default:
				not_documented();
				break;
			}
			break;
		}
	default:
		not_documented();
		break;
	}
}

//**************************************************************************
//*
//*		xg_EFFECT2
//*		Analyze the MIDI-message "SysEx; Typ 0x10; AdrH 03"
//*		MIDI Par. Change (EFFECT 2) Insertion
//*
//**************************************************************************

void SysExEventProt::xg_EFFECT2() // Adress 03 0n xx
{
	switch (AdrL)
	{
	case 0x00:
		prot_fmt_text("Insertion Type, Eff. Block %i, ",AdrM+1);
		if (hpmfi->xg_effects == NULL)
		{
			dsp_effect_type();
		}
		else
		{
			dsp_effect_type_effectfile();
		}
		break;
	case 0x02:
	case 0x03:
	case 0x04:
	case 0x05:
	case 0x06:
	case 0x07:
	case 0x08:
	case 0x09:
	case 0x0a:
	case 0x0b:
		prot_fmt_text("Insertion Eff. Block %i, ",AdrM+1);
		print_str += ((hpmfi->xg_effects)==NULL)?dsp_data_text():dsp_data_text_effectfile();
		break;
//	case 0x0b:	// Dry/Wet, one data-byte
//		prot_fmt_text("Insertion Eff. Block %i, Dry/Wet %s",AdrM+1, effect_data_15[DataMSB]);
//		break;
	case 0x0c:
		prot_fmt_text("Insertion Part, Eff. Block %i, ",AdrM+1);
		if (DataMSB<16)
		{
			prot_fmt_text("Part  %2.1i ", DataMSB+1);
		}
		else
		{
			if (DataMSB==64)
			{
				print_str += "AD ";
			}
			else
			{
				if (DataMSB==127)
				{
					print_str += "OFF ";
				}
				else
				{
					print_str += "unknown ";
				}
			}
		}
		break;
	case 0x0d:
		prot_fmt_text("MW Insertion Control Depth, Eff. Block %i, ",AdrM+1);
		prot_fmt_text("Data %i ",DataMSB);
		break;
	case 0x0e:
		prot_fmt_text("Bend Insertion Control Depth, Eff. Block %i, ",AdrM+1);
		prot_fmt_text("Data %i ",DataMSB);
		break;
	case 0x0f:
		prot_fmt_text("Cat Insertion Control Depth, Eff. Block %i, ",AdrM+1);
		prot_fmt_text("Data %i ",DataMSB);
		break;
	case 0x10:
		prot_fmt_text("AC1 Insertion Control Depth, Eff. Block %i, ",AdrM+1);
		prot_fmt_text("Data %i ",DataMSB);
		break;
	case 0x11:
		prot_fmt_text("AC2 Insertion Control Depth, Eff. Block %i, ",AdrM+1);
		prot_fmt_text("Data %i ",DataMSB);
		break;
	case 0x20:
	case 0x21:
	case 0x22:
	case 0x23:
	case 0x24:
	case 0x25:
	case 0x30:
	case 0x32:
	case 0x34:
	case 0x36:
	case 0x38:
	case 0x3a:
	case 0x3c:
	case 0x3e:
	case 0x40:
	case 0x42:
		prot_fmt_text("Insertion Eff. Block %i, ",AdrM+1);
		print_str += ((hpmfi->xg_effects)==NULL)?dsp_data_text():dsp_data_text_effectfile();
		break;
//	case 0x42: // Dry/Wet, two data-bytes
//		prot_fmt_text("Insertion Eff. Block %i, Dry/Wet %s",AdrM+1, effect_data_15[DataLSB]);
//		break;
	default:
		not_documented();
		break;
	}
}


//**************************************************************************
//*
//*		reverb_effect_type
//*		Analyze Effect Type. DataMSB and DataLSB of Address 02 01 00
//*
//**************************************************************************

void SysExEventProt::reverb_effect_type() // "Address DataMSB DataLSB",
{
	CString type = "Unknown Type ";

	int i, k;
	bool found = false;
	act_reverb_param_list_no = -1;

	for (i = 0; reverb_effect_type_list[i].msb < 128; i++)
	{
		if (DataMSB > reverb_effect_type_list[i].msb) continue;
		if (DataMSB < reverb_effect_type_list[i].msb) break;
		for (k=i; DataMSB == reverb_effect_type_list[k].msb; k++)
		{
			if (DataLSB != reverb_effect_type_list[k].lsb) continue;
			type = reverb_effect_type_list[k].type;
			act_reverb_param_list_no = reverb_effect_type_list[k].epl;
			found = true;
			break;
		}
		if (found) break;
	}
	act_reverb_type.msb = DataMSB;
	act_reverb_type.lsb = DataLSB;

	print_str += type;
}

//**************************************************************************
//*
//*		reverb_effect_type_effectfile
//*     from effectfile only
//*		Analyze Effect Type. DataMSB and DataLSB of Address 02 01 00
//*
//**************************************************************************

void SysExEventProt::reverb_effect_type_effectfile()
{
	if (hpmfi->xg_effects == NULL)
	{
		return;
	}

	CString act_type;

	(hpmfi->xg_effects)->reverb_effect_type(DataMSB, DataLSB,
											&act_reverb_param_list_no,
											&act_reverb_type.msb,
											&act_reverb_type.lsb,
											&act_type);
	print_str += act_type;
}


//**************************************************************************
//*
//*		chorus_effect_type
//*		Analyze Effect Type. DataMSB and DataLSB of Address 02 01 20
//*
//**************************************************************************

void SysExEventProt::chorus_effect_type() // "Address DataMSB DataLSB",
{
	CString type = "Unknown Type ";

	int i, k;
	bool found = false;
	act_chorus_param_list_no = -1;

	for (i = 0; chorus_effect_type_list[i].msb < 128; i++)
	{
		if (DataMSB > chorus_effect_type_list[i].msb) continue;
		if (DataMSB < chorus_effect_type_list[i].msb) break;
		for (k=i; DataMSB == chorus_effect_type_list[k].msb; k++)
		{
			if (DataLSB != chorus_effect_type_list[k].lsb) continue;
			type = chorus_effect_type_list[k].type;
			act_chorus_param_list_no = chorus_effect_type_list[k].epl;
			found = true;
			break;
		}
		if (found) break;
	}
	act_chorus_type.msb = DataMSB;
	act_chorus_type.lsb = DataLSB;

	print_str += type;
}

//**************************************************************************
//*
//*		chorus_effect_type_effectfile
//*     from effectfile only
//*		Analyze Effect Type. DataMSB and DataLSB of Address 02 01 20
//*
//**************************************************************************

void SysExEventProt::chorus_effect_type_effectfile() // "Address DataMSB DataLSB",
{
	if (hpmfi->xg_effects == NULL)
	{
		return;
	}

	CString act_type;

	(hpmfi->xg_effects)->chorus_effect_type(DataMSB, DataLSB,
											&act_chorus_param_list_no,
											&act_chorus_type.msb,
											&act_chorus_type.lsb,
											&act_type);
	print_str += act_type;
}


//**************************************************************************
//*
//*		dsp_effect_type
//*		Analyze Effect Type. DataMSB and DataLSB of Address 03 0n 00, 02 01 40
//*
//**************************************************************************

void SysExEventProt::dsp_effect_type() // "Address DataMSB DataLSB",
{
	CString type = "Unknown Type ";

	int i, k;
	bool found = false;

	for (i = 0; dsp_effect_type_list[i].msb < 128; i++)
	{
		if (DataMSB > dsp_effect_type_list[i].msb) continue;
		if (DataMSB < dsp_effect_type_list[i].msb) break;
		for (k=i; DataMSB == dsp_effect_type_list[k].msb; k++)
		{
			if (DataLSB != dsp_effect_type_list[k].lsb) continue;
			type = dsp_effect_type_list[k].type;
			found = true;
			break;
		}
		if (found) break;
	}
	if ((AdrM < NO_DSP_BLOCKS) && (AdrM >= 0))
	{
		act_dsp_type[AdrM].msb = DataMSB;
		act_dsp_type[AdrM].lsb = DataLSB;
		act_dsp_param_list_no[AdrM] = found? dsp_effect_type_list[k].epl: -1;

	}
	print_str += type;
}

//**************************************************************************
//*
//*		dsp_effect_type_effectfile
//*     from effectfile only
//*		Analyze Effect Type. DataMSB and DataLSB of Address 03 0n 00, 02 01 40
//*
//**************************************************************************

void SysExEventProt::dsp_effect_type_effectfile() // "Address DataMSB DataLSB",
{
	if (hpmfi->xg_effects == NULL)
	{
		return;
	}

	CString act_type;
	int act_dsp_list_no, act_dsp_type_msb, act_dsp_type_lsb;

	(hpmfi->xg_effects)->dsp_effect_type(DataMSB, DataLSB, AdrM,
										 &act_dsp_list_no,
										 &act_dsp_type_msb,
										 &act_dsp_type_lsb,
										 &act_type);
	act_dsp_type[AdrM].msb = act_dsp_type_msb;
	act_dsp_type[AdrM].lsb = act_dsp_type_lsb;
	act_dsp_param_list_no[AdrM] = act_dsp_list_no;
	print_str += act_type;
}


//**************************************************************************
//*
//*		reverb_data_text
//*		analyze reverb parameter and data
//*		Address 02 01 00... (EFFECT 1 Reverb)
//*
//**************************************************************************

CString SysExEventProt::reverb_data_text()
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
		(act_reverb_param_list_no >= EFFECT_PARAM_LISTS_LEN))
	{
		text += simple_text;
		return text;
	}

	// get effect parameter list
	const EFFECT_PARAM_ELEM *epl = effect_param_lists[act_reverb_param_list_no];

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

	if ((data_list_no<0)||(data_list_no>65))
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

	const EFFECT_DATA_LISTS_ELEM edl = effect_data_lists[data_list_no];
	int len = edl.len;
	const CString *dl = edl.list; // effect data list with len elements

	if (eff_data >= len)
	{
		// no data text found
		text += simple_text;
	}
	else
	{
		data_text = dl[eff_data];
		text += (" "+data_text);
	}
	return text;
}

//**************************************************************************
//*
//*		reverb_data_text_effectfile
//*     from effectfile only
//*		analyze reverb parameter and data
//*		Address 02 01 00... (EFFECT 1 Reverb)
//*
//**************************************************************************

CString SysExEventProt::reverb_data_text_effectfile()
{
	CString text = "";

	if (hpmfi->xg_effects == NULL)
	{
		return text;
	}
	text = (hpmfi->xg_effects)->reverb_data_text(AdrH, AdrL, DataMSB, DataLSB, act_reverb_param_list_no);
	return text;
}

//**************************************************************************
//*
//*		chorus_data_text
//*		analyze chorus parameter and data
//*		Address 02 01 20... (EFFECT 1 Chorus)
//*
//**************************************************************************

CString SysExEventProt::chorus_data_text()
{
	CString text = "";
	CString simple_text;
	CString par_text;
	CString data_text;
	int eff_data;

	int par_no;
	int data_list_no;

	simple_text.Format("Par %2.1x, Data %2.1x ",AdrL, DataMSB);

	if ((act_chorus_param_list_no < 0) ||
		(act_chorus_param_list_no >= EFFECT_PARAM_LISTS_LEN))
	{
		text += simple_text;
		return text;
	}

	// get effect parameter list
	const EFFECT_PARAM_ELEM *epl = effect_param_lists[act_chorus_param_list_no];

	// get chorus parameter no
	bool result = GlobalUtilities::get_sysex_parno_effectno(AdrH, AdrL, DataMSB, DataLSB, &par_no, &eff_data);

	if (!result || (epl == NULL))
	{
		text += simple_text;
		return text;
	}

	par_no--; // par lists start with index 0

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
	if ((data_list_no<0)||(data_list_no>65))
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
		float data = (float)eff_data/(float(10));
		data_text.Format(" %f ms",data);
		text += data_text;
		return text;
	}

	const EFFECT_DATA_LISTS_ELEM edl = effect_data_lists[data_list_no];
	int len = edl.len;
	const CString *dl = edl.list; // effect data list with len elements

	if (eff_data >= len)
	{
		// no data text found
		text += simple_text;
	}
	else
	{
		data_text = dl[eff_data];
		text += (" "+data_text);
	}
	return text;
}

//**************************************************************************
//*
//*		chorus_data_text_effectfile
//*     from effectfile only
//*		analyze chorus parameter and data
//*		Address 02 01 20... (EFFECT 1 Chorus)
//*
//**************************************************************************

CString SysExEventProt::chorus_data_text_effectfile()
{
	CString text = "";

	if (hpmfi->xg_effects == NULL)
	{
		return text;
	}
	text = (hpmfi->xg_effects)->chorus_data_text(AdrH, AdrL, DataMSB, DataLSB, act_chorus_param_list_no);
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

CString SysExEventProt::dsp_data_text()
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

	if ((act_dsp_param_list_no[eff_block] < 0) ||
		(act_dsp_param_list_no[eff_block] >= EFFECT_PARAM_LISTS_LEN))
	{
		text += simple_text;
		return text;
	}

	// get effect parameter list
	const EFFECT_PARAM_ELEM *epl = effect_param_lists[act_dsp_param_list_no[eff_block]];

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

	if ((data_list_no<0)||(data_list_no>65))
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

	const EFFECT_DATA_LISTS_ELEM edl = effect_data_lists[data_list_no];
	int len = edl.len;
	const CString *dl = edl.list; // effect data list with len elements

	if (eff_data >= len)
	{
		// no data text found
		text += simple_text;
	}
	else
	{
		data_text = dl[eff_data];
		text += (" "+data_text);
	}
	return text;
}

//**************************************************************************
//*
//*		dsp_data_text_effectfile
//*     from effectfile only
//*		analyze variation and dsp parameter and data
//*		Address 02 01 40...	(EFFECT 1 Variation)
//*		Address 03 0n 00... (EFFECT 2)
//*
//**************************************************************************

CString SysExEventProt::dsp_data_text_effectfile()
{
	CString text = "";
	if (hpmfi->xg_effects == NULL)
	{
		return text;
	}

	text = (hpmfi->xg_effects)->dsp_data_text(DataMSB, DataLSB, AdrH, AdrM, AdrL,act_dsp_param_list_no[AdrM]);

	return text;
}

//**************************************************************************
//*
//*		clavinova
//*		Protocol: Yamaha SysEx Clavinova (Type 0x73)
//*
//**************************************************************************

void SysExEventProt::clavinova()
{
	CString r; // used for formatted Output

	// sysex-Typ 0x73 ( = eventstr[1] ) für Clavinova Compliance
	print_str += "Clavinova ";

	switch (eventstr[2])
	{
	case 0x01: // f0 43 73 01 ...
		{
			switch (eventstr[3])
			{
			case 0x02: // f0 43 73 01 02 ...
				{
					print_str += "Internal Clock ";
					break;
				}
			case 0x03: // f0 43 73 01 03 ...
				{
					print_str += "External Clock ";
					break;
				}
			case 0x06: // f0 43 73 01 06 ...
				{
					if ( !( (eventstr[4]==0x0b) &&
						(eventstr[5]==0x00) &&
						(eventstr[6]==0x00) &&
						(eventstr[7]==0x01) &&
						(eventstr[8]==0x06)  )    )
					{
						print_str += "unknown Clavinova SysEx ";
					}
					else
					{
						char format[512] = "Organ Flute:\n";
						strcat(format,"\t\t\tChan %i, 1' %i, 1 1/3' %i, 2' %i, 2 2/3' %i, 4' %i, 5 1/3' %i, 8' %i, 16' %i,\n");
						strcat(format,"\t\t\tAttack: 2' %i, 2 2/3' %i, 4' %i, length %i, response %i, mode %s,\n");
						strcat(format,"\t\t\twave variation %s ,volume %i");
						prot_fmt_text(format,
							eventstr[9]+1, // chan
							eventstr[10],
							eventstr[11],
							eventstr[13],
							eventstr[14],
							eventstr[15],
							eventstr[16],
							eventstr[17],
							eventstr[18],
							eventstr[19], // Attack 2'
							eventstr[20], //        2 2/3'
							eventstr[21], //        4'
							eventstr[22], // length
							eventstr[23], // response
							eventstr[24]==0?"Each":"First",		// Attack Mode
							eventstr[25]==0?"Sine":"Tone Wheel",// Wave Variation
							eventstr[26]  // Volume
							);
					}
					break;
				}
			case 0x011: // f0 43 73 01 11 00 eventstr[5] xx dd f7
				{

					switch(eventstr[5])
					{
					case 0x14: // f0 43 73 01 11 00 14 ...
						prot_fmt_text("Split Key No. %i ", eventstr[6]);
						break;
					case 0x40: // f0 43 73 01 11 00 40 ...
						print_str += "Fingering ";
						{
							unsigned char ft = eventstr[6];
							prot_fmt_text("%s ",
								ft==0?"Off ":ft==1?"Single ":ft==2?"Fingered ":
							ft==4?"Full Keyboard ":ft==7?"Multi Finger ":"");
						}
						break;
					case 0x42: // f0 43 73 01 11 00 42 ...
						{
							unsigned char p = eventstr[4]; // part
							prot_fmt_text("Part: %s ",
								p==0?"All ":p==5?"Rythm ":p==10?"Bass ":
							p==6?"Chord ":p==13?"Pad ":p==7?"Phrase ":"");
							prot_fmt_text("Part: %s ",
								p==0?"All ":p==5?"Rythm ":p==10?"Bass ":
							p==6?"Chord ":p==13?"Pad ":p==7?"Phrase ":"");
							prot_fmt_text("Accomp Volume %i ",eventstr[6]);
						}
						break;
					case 0x43: // f0 43 73 01 11 00 43 ...
						prot_fmt_text("Part  %2.1i ",eventstr[4]+1);
						prot_fmt_text("Dual Detune %i ",eventstr[6]-64);
						break;
					case 0x45:  // f0 43 73 01 11 00 45 ...
						prot_fmt_text("Part  %2.1i ",eventstr[4]+1);
						prot_fmt_text("Volume and Expression Realtime Control Off: %s ",
							eventstr[6]==0?"on ":"off: ");
						break;
					case 0x50:  // f0 43 73 01 11 00 50 ...

						print_str += "Vocal Harmony ";
						switch (eventstr[6])
						{
						case 0x00:	// f0 43 73 01 11 00 50 00 ...
							{
								print_str += "Pitch to Note ";
								print_str += eventstr[7]==0x00?"Off ":"On ";
								break;
							}
						case 0x01:	// f0 43 73 01 11 00 50 01 ...
							{
								unsigned char e7 = eventstr[7];
								print_str += "Pitch to Note Part ";
								print_str +=	e7==0x00?"Right1 ":
								e7==0x01?"Right2 ":
								e7==0x02?"Left ":
								e7==0x03?"Right3 ":
								e7==0x04?"Upper ":"unknown ";
								break;
							}
						case 0x10:	// f0 43 73 01 11 00 50 10 ...
							{
								unsigned char e7 = eventstr[7];
								print_str += "Vocoder Part ";
								print_str +=
									e7==0x00?"Off ":
									e7==0x01?"Upper ":
									e7==0x02?"Lower ":"unknown ";
								break;
							}
						default:
							{
								print_str += "unknown VH";
								break;
							}
						} // end eventstr[6]
					} // end eventstr[5]
					break;
				} // end eventstr[3] = 0x11

				case 0x1f: // f0 43 73 01 1F ...
				{
					print_str += "Guide ";
					unsigned char e5 = eventstr[5];
					unsigned char e6 = eventstr[6];
					print_str +=
						e5==0x00?"RightCh=On, LeftCh=On, ":
						e5==0x01?"RightCh=Off, LeftCh=On, ":
						e5==0x02?"RightCh=On, LeftCh=Off, ":
						e5==0x03?"RightCh=Off, LeftCh=Off, ":"Part unknown ";
					print_str +=
						e6==0x00?"Guide Off ":
						e6==0x01?"Follow Lights ":
						e6==0x02?"Any Key ":
						e6==0x03?"Karaoke Key ":
						e6==0x04?"Vocal Cue Time ":" Mode unknown ";
					break;
				}
				case 0x50:// f0 43 73 01 50...
				{
					switch(eventstr[4])
					{
					case 0x04: // Harmony/Echo f0 43 73 01 50 04 ...
						{
							CString onoff = eventstr[7]==0x00?"OFF":"ON"; // only if eventstr[6] = 0,1,2,8

							if (eventstr[5]!=0x00)
							{
								print_str += "Unknown SysEx";
								break;
							}
							switch (eventstr[6])
							{
							case 0:
								{
									if (eventstr[8] == 0xf7)
									{
										print_str += "Harmony Echo " + onoff;
										break;
									}
									else
									if (eventstr[7] == 0x02)
									{
										CString type;
										type.Format("cc %i, dd %i",eventstr[8], eventstr[9]);
										print_str += "Harmony Echo Type: " + type;
										break;
									}
									print_str += "Unknown SysEx";
									break;
								}
							case 2:
								{
									CString part = eventstr[7]==0x00?"Right1":
												   eventstr[7]==0x01?"Right2":
												   eventstr[7]==0x02?"Right3":
												   eventstr[7]==0x03?"Left":
												   "Unknown";
									print_str += "Harmony Echo Assign " + part;
									break;
								}
							case 3:
								{
									print_str += "Chord Note Only: " + onoff;
									break;
								}
							case 4:
								{
									CString value;
									value.Format("%i",eventstr[7]);
									print_str += "Touch Limit: " + value;
									break;
								}
							case 5:
								{
									CString value;
									value.Format("%i",eventstr[7]);
									print_str += "Harmony Echo Volume: " + value;
									break;
								}
							default:
								{
									print_str += "Unknown Harmony Echo SysEx";
									break;
								}
							}
							break;
						}
					case 0x07: // Multi-Pad f0 43 73 01 50 07 ...
						{
							if ((eventstr[5]!=0x00)&&(eventstr[6]!=0x00))
							{
								print_str += "Unknowm Multi-Pad SysEx";
								break;
							}
							// f0 43 73 01 50 07 00 00
							if (eventstr[8]==0xf7)
							{	// f0 43 73 50 07 00 00 xx f7
								CString volume;
								volume.Format("%i",eventstr[7]);
								print_str += "Multi-Pad Volume: " + volume;
								break;
							}

							if (eventstr[7]!=0x02)
							{
								print_str += "Unknowm Multi-Pad SysEx";
								break;
							}

							// f0 43 73 01 50 07 00 00 02 xx dd f7
							CString r;
							r.Format("cc %i, dd %i",eventstr[8],eventstr[9]);
							print_str += "Multi-Pad Number: "+r;

							break;
						}
					case 0x08: // Voice f0 43 73 01 50 08 ...
						{
							CString r;
							CString part = eventstr[5]==0x00?"Right1":
										   eventstr[5]==0x01?"Right2":
										   eventstr[5]==0x02?"Right3":
										   eventstr[5]==0x03?"Left":
										   "Unknown";
							CString onoff = eventstr[7]==0x00?"OFF":"ON"; // only if eventstr[6] = 0,1,2,8

							switch (eventstr[6])
							{
							case 0x00: // Part On/Off f0 43 73 01 50 08 cc 00 dd f7
								{
									r.Format("Part %s %s ",part, onoff);
									print_str += r;
									break;
								}
							case 0x01: // DSP Variation On/Off f0 43 73 01 50 08 cc 01 dd f7
								{
									r.Format("DSP Variation %s %s ",part, onoff);
									print_str += r;
									break;
								}
							case 0x02: // Left Hold On/Off f0 43 73 01 50 08 03 02 cc f7
								{
									if (eventstr[5]!=0x03)
									{
										break;
									}
									r.Format("Left Hold %s ", onoff);
									print_str += r;
									break;
								}
							case 0x03: // Octave f0 43 73 01 50 08 cc 03 dd f7
								{
									CString value = eventstr[7]==0x3e? "-2":
								                    eventstr[7]==0x3f? "-1":
								                    eventstr[7]==0x40? "0":
								                    eventstr[7]==0x41? "1":
								                    eventstr[7]==0x42? "2": "error";

									r.Format("Octave %s %s ",part, value);
									print_str += r;
									break;
								}
							case 0x04: // Voice Set Volume f0 43 73 01 50 08 cc 04 dd f7
								{
									CString volume;
									volume.Format(": %i",eventstr[7]);
									print_str += "Voice Set Volume " + part + volume;
									break;
								}
							case 0x08: // DSP On/Off f0 43 73 01 50 08 cc 08 dd f7
								{
									r.Format("DSP %s %s ",part, onoff);
									print_str += r;
									break;
								}
							default:
								{
									print_str += "Unknown SysEx";
									break;
								}
							}

							break;
						}
					case 0x12: // Score Layout f0 43 73 01 50 12 00 ...
						{
							if (eventstr[5]!=0x00)
							{
								print_str += "Unknown SysEx";
								break;
							}
							switch (eventstr[6])
							{
							case 0x00:
								{
									print_str += (CString)"Left Part "+(eventstr[7]==0x00?"OFF":
													   eventstr[7]==0x7f?"ON": "?");
									break;
								}
							case 0x01:
								{
									print_str += (CString)"Right Part "+(eventstr[7]==0x00?"OFF":
													   eventstr[7]==0x7f?"ON": "?");
									break;
								}
							case 0x02:
								{
									print_str += (CString)"Lyrics Part Score "+(eventstr[7]==0x00?"OFF":
													   eventstr[7]==0x7f?"ON": "?");
									break;
								}
							case 0x03:
								{
									print_str += (CString)"Chord Part Score "+(eventstr[7]==0x00?"OFF":
													   eventstr[7]==0x7f?"ON": "?");
									break;
								}
							case 0x04:
								{
									print_str += (CString)"Note Names Score "+(eventstr[7]==0x00?"OFF":
													   eventstr[7]==0x7f?"ON": "?");
									break;
								}
							case 0x05:
								{
									CString l = eventstr[7]==0?"small ":
												eventstr[7]==1?"medium ":
												eventstr[7]==2?"large ":
												eventstr[7]==3?"very large ":"?";

									print_str += (CString)"Score representation "+l;
									break;
								}
							case 0x06:
								{
									CString l;
									if (eventstr[7]<0x10)
									{
										l.Format("%i ",eventstr[7]+1);
									}
									else
									{
										l = eventstr[7]==0x7e?"OFF ":
											eventstr[7]==0x7f?"AUTO ":"?";
									}

									print_str += (CString)"Left channel "+l;
									break;
								}
							case 0x07:
								{
									CString l;
									if (eventstr[7]<0x10)
									{
										l.Format("%i ",eventstr[7]+1);
									}
									else
									{
										l = eventstr[7]==0x7e?"OFF ":
											eventstr[7]==0x7f?"AUTO ":"?";
									}

									print_str += (CString)"Right channel "+l;
									break;
								}
							case 0x08:
								{
									print_str += (CString)"Quantize Triole "+(eventstr[7]==0x00?"OFF":
													   eventstr[7]==0x7f?"ON": "?");
									break;
								}
							case 0x09:
								{
									CString l = eventstr[7]==0?"1/4 ":
												eventstr[7]==1?"1/8 ":
												eventstr[7]==2?"1/16 ":
												eventstr[7]==3?"1/32 ":"?";
									print_str += (CString)"Quantize "+l;
									break;
								}
							case 0x0A:
								{
									CString l = eventstr[7]==0?"ABC ":
												eventstr[7]==1?"Fixed Do ":
												eventstr[7]==2?"Movable Do ":"?";
									print_str += (CString)"Note Names "+l;
									break;
								}
							case 0x0B:
								{
									print_str += (CString)"Note colour "+(eventstr[7]==0x00?"OFF":
															   eventstr[7]==0x7f?"ON": "?");
									break;
								}
							default:
								{
									print_str += "Unknown SysEx";
									break;
								}
							}
							break;
						}
					case 0x19: //  Play f0 43 73 01 50 19 ...
						{
							if (eventstr[6]!=0x00)
							{
								print_str += "Unknown SysEx";
								break;
							}
							switch (eventstr[7])
							{
							case 0x00:
								{
									print_str += "Play Start ";
									break;
								}
							case 0x01:
								{
									print_str += "Play Stop ";
									break;
								}
							case 0x02:
								{
									print_str += "Play Pause ";
									break;
								}
							default:
								{
									print_str += "Unknown SysEx ";
									break;
								}
							}
						}
					default:
						{
							print_str += "Unknown SysEx";
							break;
						}
					}
				}

				case 0x51: // f0 43 73 01 51...
					{
						/*
							F0 43 73 01 51 09 00 00 00 F7    ; Clavinova Copy Display
							F0 43 73 01 51 09 00 01 00 F7    ; Clavinova Save Display FD
							F0 43 73 01 51 09 00 02 01 02 F7 ; Clavinova Save Display HD
							F0 43 73 01 51 09 00 02 01 03 F7 ; Clavinova Save Display Smart Media or USB
							F0 43 73 01 51 09 00 02 01 04 F7 ; Clavinova Save Display USB Device
						*/
						if ((eventstr[4]==0x09)&&(eventstr[5]==0x00))
						{
							print_str += (CString)"Keyboard Display";
							if ((eventstr[6]==0x00)&&(eventstr[7]==0x00))
							{
								print_str += (CString)" Copy";
							}
							if ((eventstr[6]==0x01)&&(eventstr[7]==0x00))
							{
								print_str += (CString)" Save FD";
							}
							if ((eventstr[6]==0x02)&&(eventstr[7]==0x01)&&(eventstr[8]==2))
							{
								print_str += (CString)" Save HD";
							}
							if ((eventstr[6]==0x02)&&(eventstr[7]==0x01)&&(eventstr[8]==3))
							{
								print_str += (CString)" Save Smart Media or USB";
							}
							if ((eventstr[6]==0x02)&&(eventstr[7]==0x01)&&(eventstr[8]==4))
							{
								print_str += (CString)" Save USB Device";
							}
						}
						break;
					}
/*!!*/
				break;
			} // end eventstr[2] == 0x01, eventstr[3]
			break;
		} // end eventstr[2] == 0x01
	case 0x45: // f0 43 73 45 ...
		{
			print_str += "CVP-98/96/94/92";
			break;
		}

	default:
		{
			print_str += "unknown ID";
			break;
		}
	} // end eventstr[2]

}


//**************************************************************************
//*
//*		style
//*		Analyze the SysEx "f0 43 7e ..." (Yamaha)
//*
//**************************************************************************

void SysExEventProt::style()
{
	// sysex Typ eventstr[1] ist 0x7e
	// Es werden jetzt die Bytes eventstr[2]
	// bis eventstr[slength-2] analysiert.

	CString r; // used for formatted Output


	char* sw_no;
	char* on_off;
	print_str += "Style ";

	switch (eventstr[2])
	{
	case 0x00: // (3-6-1-1) Section Control
		{
			print_str += "Section Control ";
			switch (AdrH)
			{
			case 0x00:
				sw_no = "INTRO A";
				break;
			case 0x01:
				sw_no = "INTRO B";
				break;
			case 0x02:
				sw_no = "INTRO C";
				break;
			case 0x03:
				sw_no = "INTRO D";
				break;
			case 0x07:
				sw_no = "INTRO B PSR-8000";
				break;
			case 0x08:
				sw_no = "MAIN A";
				break;
			case 0x09:
				sw_no = "MAIN B";
				break;
			case 0x0a:
				sw_no = "MAIN C";
				break;
			case 0x0b:
				sw_no = "MAIN D";
				break;
			case 0x0f:
				sw_no = "MAIN B PSR-8000";
				break;
			case 0x10:
				sw_no = "FILL IN AA";
				break;
			case 0x11:
				sw_no = "FILL IN BB";
				break;
			case 0x12:
				sw_no = "FILL IN CC";
				break;
			case 0x13:
				sw_no = "FILL IN DD";
				break;
			case 0x17:
				sw_no = "FILL IN BB";
				break;
			case 0x18:
				sw_no = "FILL IN AB PSR-8000 or BREAK FILL";
				break;
			case 0x1f:
				sw_no = "FILL IN BA PSR-8000";
				break;
			case 0x20:
				sw_no = "ENDING A";
				break;
			case 0x21:
				sw_no = "ENDING B";
				break;
			case 0x22:
				sw_no = "ENDING C";
				break;
			case 0x23:
				sw_no = "ENDING D";
				break;
			case 0x27:
				sw_no = "ENDING B PSR-8000";
				break;
			default:
				sw_no = "Unknown Switch";
				break;
			}

			if (AdrM == 0x00)
				on_off = "Off";
			else
				if (AdrM == 0x7f)
					on_off = "On";
				else
					on_off = "Unknown Switch On/Off";
				prot_fmt_text("%s %s ", sw_no, on_off);
				break;
		}
	case 0x01: // (3-6-1-2) Tempo Control
		{
			long tempo = ((eventstr[3]*128+eventstr[4])*128+eventstr[5])*128+eventstr[6];
			double bpm_double = 60000000.0/(double)tempo;
			prot_fmt_text("Tempo Control: %i Microsec per Quarter or %4.2f Beats per Minute",tempo, bpm_double);
			break;
		}
	case 0x02: // Chord Control type 1
		{
			print_str += "CHORD CONTROL type 1";
			int cr03 = (eventstr[3]>>4);
			int cr47 = (eventstr[3] & 0x0f);
			int ct   = eventstr[4];
			if ((cr03<GlobalUtilities::cr03_list_length)&&(cr47<GlobalUtilities::cr47_list_length)&&(ct<GlobalUtilities::ct_list_length))
			{
				print_str += ", "+GlobalUtilities::cr47_list[cr47]+GlobalUtilities::cr03_list[cr03]+" "+GlobalUtilities::ct_list[ct];
			}

			if (eventstr[5] != 0x7f)
			{
				cr03 = (eventstr[5]>>4);
				cr47 = (eventstr[5] & 0x0f);
				ct   = eventstr[6];
				if ((cr03<GlobalUtilities::cr03_list_length)&&(cr47<GlobalUtilities::cr47_list_length)&&(ct<GlobalUtilities::ct_list_length))
				{
					print_str += ", Bass: "+GlobalUtilities::cr47_list[cr47]+GlobalUtilities::cr03_list[cr03]+" "+GlobalUtilities::ct_list[ct];
				}
			}
		}
		break;
	case 0x03: // Chord Control type 2
		{
			int i;
			print_str += "CHORD CONTROL type 2, ";
			for (i=1; (i<=10) && (i<=slength-4); i++)
			{
				prot_fmt_text("n(%i)=%s ",i ,GlobalUtilities::note(eventstr[i+2]));
			}
		}
		break;
	default:
		unknown_type();
	}
}

void SysExEventProt::prot_fmt_text(char* fmt,...)
{
	char temp_text[256];
	va_list args;
	va_start(args, fmt);
	vsprintf(temp_text,fmt,args);
	va_end(args);
	print_str += temp_text;
}

//**************************************************************************
//*
//*		undocumented_type
//*		Protocol: used, but undcomented Yamaha-SysEx
//*
//**************************************************************************

void SysExEventProt::undocumented_type()
{
	print_str += "not documented by Yamaha ";
}

//**************************************************************************
//*
//*		not_documented
//*		Protocol: not documented at this time
//*
//**************************************************************************

void SysExEventProt::not_documented()
{
	print_str += "(not yet documented!)";
}

//**************************************************************************
//*
//*		unknown_type
//*		Protocol: unknown, perhaps not correct Yamaha-SysEx
//*
//**************************************************************************

void SysExEventProt::unknown_type()
{
	print_str += "(unkown!) ";
}


