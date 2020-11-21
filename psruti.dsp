# Microsoft Developer Studio Project File - Name="psruti" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=psruti - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "psruti.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "psruti.mak" CFG="psruti - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "psruti - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "psruti - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "psruti - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 HP_midifile.lib /nologo /subsystem:windows /incremental:yes /debug /machine:I386

!ELSEIF  "$(CFG)" == "psruti - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /I "D" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 HP_midifile.lib /nologo /subsystem:windows /profile /debug /machine:I386

!ENDIF 

# Begin Target

# Name "psruti - Win32 Release"
# Name "psruti - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BrowseDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangeDrumVoicesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangeKeyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Chd.cpp
# End Source File
# Begin Source File

SOURCE=.\ChordsLyricsEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\ChordsLyricsImportExport.cpp
# End Source File
# Begin Source File

SOURCE=.\ComputeBanknumberMsbLsb.cpp
# End Source File
# Begin Source File

SOURCE=.\Controller_Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ControllerEffectsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CopyrightDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Delete_Fill_Lyrics_Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\delete_keyboard_events.cpp
# End Source File
# Begin Source File

SOURCE=.\Delete_MIDI_Events.cpp
# End Source File
# Begin Source File

SOURCE=.\Delete_short_notes.cpp
# End Source File
# Begin Source File

SOURCE=.\Drums.cpp
# End Source File
# Begin Source File

SOURCE=.\DrumsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DrumVoicesTemplateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EffectFilterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ExchangeChannelsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Expr_MainVolume.cpp
# End Source File
# Begin Source File

SOURCE=.\Extras_Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FileAttributesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FillLyricMethodDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FillLyricsLinefeedDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GlobalUtilities.cpp
# End Source File
# Begin Source File

SOURCE=.\HPMF_Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\HPMF_Interface2.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportLyricsAtChannelNotes.cpp
# End Source File
# Begin Source File

SOURCE=.\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\InsdefDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\InsDefOnOffDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\InsertChordLyrics.cpp
# End Source File
# Begin Source File

SOURCE=.\Lengthen_Notes.cpp
# End Source File
# Begin Source File

SOURCE=.\lickChanDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Log.cpp
# End Source File
# Begin Source File

SOURCE=.\LyricChordEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LyricChordEditElement.cpp
# End Source File
# Begin Source File

SOURCE=.\LyricFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MainVolume_Expression_Folder_Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Master_Volume_Folder_Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MasterVolume.cpp
# End Source File
# Begin Source File

SOURCE=.\MyArrays.cpp
# End Source File
# Begin Source File

SOURCE=.\Play.cpp
# End Source File
# Begin Source File

SOURCE=.\PreferencesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Print.cpp
# End Source File
# Begin Source File

SOURCE=.\psruti.cpp
# End Source File
# Begin Source File

SOURCE=.\psruti.rc
# End Source File
# Begin Source File

SOURCE=.\psrutidlg.cpp
# End Source File
# Begin Source File

SOURCE=.\QuantisizeChords.cpp
# End Source File
# Begin Source File

SOURCE=.\QuantisizeLyricsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\QuantizeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Quickstart.cpp
# End Source File
# Begin Source File

SOURCE=.\RevoicingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RevoicingMethodDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveChangesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Score.cpp
# End Source File
# Begin Source File

SOURCE=.\ScoreChanDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ScoreLayout.cpp
# End Source File
# Begin Source File

SOURCE=.\ScoreNotesOptDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Select_Language.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectFillLyrics.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectMIDIDevice.cpp
# End Source File
# Begin Source File

SOURCE=.\SlctChordChan.cpp
# End Source File
# Begin Source File

SOURCE=.\Songname.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecialPreferences.cpp
# End Source File
# Begin Source File

SOURCE=.\StartBeat.cpp
# End Source File
# Begin Source File

SOURCE=.\StartBeatFolderDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\sysex_event_data.cpp
# End Source File
# Begin Source File

SOURCE=.\sysex_event_prot.cpp
# End Source File
# Begin Source File

SOURCE=.\SysexDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SysexPasteDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Tempo_Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Time_Signature.cpp
# End Source File
# Begin Source File

SOURCE=.\Transpose_no.cpp
# End Source File
# Begin Source File

SOURCE=.\VelCompress.cpp
# End Source File
# Begin Source File

SOURCE=.\VhActDeactDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VHChanDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VoiceFileBrowseDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VoiceFileElement.cpp
# End Source File
# Begin Source File

SOURCE=.\VoicefileRevoicingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VolumeMethodDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\XBrowseForFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\XG_effectdef_on_of_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\XG_effectdefdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\XgEffects.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BrowseDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChangeDrumVoicesDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChangeKeyDlg.h
# End Source File
# Begin Source File

SOURCE=.\Chd.h
# End Source File
# Begin Source File

SOURCE=.\ChordsLyricsEditor.h
# End Source File
# Begin Source File

SOURCE=.\ChordsLyricsImportExport.h
# End Source File
# Begin Source File

SOURCE=.\ComputeBanknumberMsbLsb.h
# End Source File
# Begin Source File

SOURCE=.\Controller_Dlg.h
# End Source File
# Begin Source File

SOURCE=.\ControllerEffectsDlg.h
# End Source File
# Begin Source File

SOURCE=.\copyrightDlg.h
# End Source File
# Begin Source File

SOURCE=.\Delete_Fill_Lyrics_Dlg.h
# End Source File
# Begin Source File

SOURCE=.\delete_keyboard_events.h
# End Source File
# Begin Source File

SOURCE=.\Delete_MIDI_Events.h
# End Source File
# Begin Source File

SOURCE=.\Delete_short_notes.h
# End Source File
# Begin Source File

SOURCE=.\Drums.h
# End Source File
# Begin Source File

SOURCE=.\DrumsDlg.h
# End Source File
# Begin Source File

SOURCE=.\DrumVoicesTemplateDlg.h
# End Source File
# Begin Source File

SOURCE=.\EffectFilterDlg.h
# End Source File
# Begin Source File

SOURCE=.\ElementChordList.h
# End Source File
# Begin Source File

SOURCE=.\ExchangeChannelsDlg.h
# End Source File
# Begin Source File

SOURCE=.\Expr_MainVolume.h
# End Source File
# Begin Source File

SOURCE=.\Extras_Dlg.h
# End Source File
# Begin Source File

SOURCE=.\FileAttributesDlg.h
# End Source File
# Begin Source File

SOURCE=.\FillLyricMethodDlg.h
# End Source File
# Begin Source File

SOURCE=.\FillLyricsLinefeedDlg.h
# End Source File
# Begin Source File

SOURCE=.\GlobalUtilities.h
# End Source File
# Begin Source File

SOURCE=.\HP_midifile.h
# End Source File
# Begin Source File

SOURCE=.\HPMF_Interface.h
# End Source File
# Begin Source File

SOURCE=.\ImportLyricsAtChannelNotes.h
# End Source File
# Begin Source File

SOURCE=.\IniFile.h
# End Source File
# Begin Source File

SOURCE=.\InsdefDlg.h
# End Source File
# Begin Source File

SOURCE=.\InsDefOnOffDlg.h
# End Source File
# Begin Source File

SOURCE=.\InsertChordLyrics.h
# End Source File
# Begin Source File

SOURCE=.\Lengthen_Notes.h
# End Source File
# Begin Source File

SOURCE=.\lickChanDlg.h
# End Source File
# Begin Source File

SOURCE=.\Log.h
# End Source File
# Begin Source File

SOURCE=.\LyricChordEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\LyricChordEditElement.h
# End Source File
# Begin Source File

SOURCE=.\LyricFrame.h
# End Source File
# Begin Source File

SOURCE=.\MainFunctions.h
# End Source File
# Begin Source File

SOURCE=.\MainVolume_Expression_Folder_Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Master_Volume_Folder_Dlg.h
# End Source File
# Begin Source File

SOURCE=.\MasterVolume.h
# End Source File
# Begin Source File

SOURCE=.\MyArrays.h
# End Source File
# Begin Source File

SOURCE=.\Play.h
# End Source File
# Begin Source File

SOURCE=.\PreferencesDlg.h
# End Source File
# Begin Source File

SOURCE=.\Print.h
# End Source File
# Begin Source File

SOURCE=.\psruti.h
# End Source File
# Begin Source File

SOURCE=.\psrutiDlg.h
# End Source File
# Begin Source File

SOURCE=.\QuantisizeChords.h
# End Source File
# Begin Source File

SOURCE=.\QuantisizeLyricsDlg.h
# End Source File
# Begin Source File

SOURCE=.\QuantizeDlg.h
# End Source File
# Begin Source File

SOURCE=.\Quickstart.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RevoicingDlg.h
# End Source File
# Begin Source File

SOURCE=.\RevoicingMethodDlg.h
# End Source File
# Begin Source File

SOURCE=.\SaveChangesDlg.h
# End Source File
# Begin Source File

SOURCE=.\Score.h
# End Source File
# Begin Source File

SOURCE=.\ScoreChanDlg.h
# End Source File
# Begin Source File

SOURCE=.\ScoreLayout.h
# End Source File
# Begin Source File

SOURCE=.\ScoreNotesOptDlg.h
# End Source File
# Begin Source File

SOURCE=.\Select_Language.h
# End Source File
# Begin Source File

SOURCE=.\SelectFillLyrics.h
# End Source File
# Begin Source File

SOURCE=.\SelectMIDIDevice.h
# End Source File
# Begin Source File

SOURCE=.\SlctChordChan.h
# End Source File
# Begin Source File

SOURCE=.\Songname.h
# End Source File
# Begin Source File

SOURCE=.\SpecialPreferences.h
# End Source File
# Begin Source File

SOURCE=.\StartBeat.h
# End Source File
# Begin Source File

SOURCE=.\StartBeatFolderDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\sysex_event_prot.h
# End Source File
# Begin Source File

SOURCE=.\SysexDlg.h
# End Source File
# Begin Source File

SOURCE=.\SysexPasteDlg.h
# End Source File
# Begin Source File

SOURCE=.\Tempo_Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Time_Signature.h
# End Source File
# Begin Source File

SOURCE=.\Transpose_no.h
# End Source File
# Begin Source File

SOURCE=.\VelCompress.h
# End Source File
# Begin Source File

SOURCE=.\VhActDeactDlg.h
# End Source File
# Begin Source File

SOURCE=.\VHChanDlg.h
# End Source File
# Begin Source File

SOURCE=.\VoiceFileBrowseDlg.h
# End Source File
# Begin Source File

SOURCE=.\VoiceFileElement.h
# End Source File
# Begin Source File

SOURCE=.\VoicefileRevoicingDlg.h
# End Source File
# Begin Source File

SOURCE=.\VolumeMethodDlg.h
# End Source File
# Begin Source File

SOURCE=.\XBrowseForFolder.h
# End Source File
# Begin Source File

SOURCE=.\XG_effectdef_on_of_dlg.h
# End Source File
# Begin Source File

SOURCE=.\XG_effectdefdlg.h
# End Source File
# Begin Source File

SOURCE=.\XgEffects.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\beat_1.ico
# End Source File
# Begin Source File

SOURCE=.\res\beat_1_3.ico
# End Source File
# Begin Source File

SOURCE=.\res\beat_all.ico
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\eighth_note.ico
# End Source File
# Begin Source File

SOURCE=.\res\eighth_triole_note.ico
# End Source File
# Begin Source File

SOURCE=.\res\half_note.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon17.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon18.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon19.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon20.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon21.ico
# End Source File
# Begin Source File

SOURCE=.\res\noten.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pause.ico
# End Source File
# Begin Source File

SOURCE=.\res\play.ico
# End Source File
# Begin Source File

SOURCE=.\res\play_green.ico
# End Source File
# Begin Source File

SOURCE=.\res\psruti.ico
# End Source File
# Begin Source File

SOURCE=.\res\quarter_note.ico
# End Source File
# Begin Source File

SOURCE=.\res\record_green.ico
# End Source File
# Begin Source File

SOURCE=.\res\record_red.ico
# End Source File
# Begin Source File

SOURCE=.\res\record_transparent.ico
# End Source File
# Begin Source File

SOURCE=.\res\record_yellow.ico
# End Source File
# Begin Source File

SOURCE=.\res\sixteenth.ico
# End Source File
# Begin Source File

SOURCE=.\res\stop.ico
# End Source File
# Begin Source File

SOURCE=.\res\threedot.ico
# End Source File
# Begin Source File

SOURCE=.\res\whole_note.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\Entwicklungsstand.doc
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section psruti : {20D4F5E0-5475-11D2-9774-0000F80855E6}
# 	2:5:Class:CMediaPlayer2
# 	2:10:HeaderFile:mediaplayer2.h
# 	2:8:ImplFile:mediaplayer2.cpp
# End Section
# Section psruti : {22D6F312-B0F6-11D0-94AB-0080C74C7E95}
# 	2:21:DefaultSinkHeaderFile:mediaplayer2.h
# 	2:16:DefaultSinkClass:CMediaPlayer2
# End Section
