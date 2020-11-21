# Microsoft Developer Studio Generated NMAKE File, Based on psruti.dsp
!IF "$(CFG)" == ""
CFG=psruti - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. psruti - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "psruti - Win32 Release" && "$(CFG)" != "psruti - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "psruti.mak" CFG="psruti - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "psruti - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "psruti - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "psruti - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\psruti.exe" "$(OUTDIR)\psruti.pch" "$(OUTDIR)\psruti.bsc"


CLEAN :
	-@erase "$(INTDIR)\BrowseDlg.obj"
	-@erase "$(INTDIR)\BrowseDlg.sbr"
	-@erase "$(INTDIR)\ChangeDrumVoicesDlg.obj"
	-@erase "$(INTDIR)\ChangeDrumVoicesDlg.sbr"
	-@erase "$(INTDIR)\ChangeKeyDlg.obj"
	-@erase "$(INTDIR)\ChangeKeyDlg.sbr"
	-@erase "$(INTDIR)\Chd.obj"
	-@erase "$(INTDIR)\Chd.sbr"
	-@erase "$(INTDIR)\ChordsLyricsEditor.obj"
	-@erase "$(INTDIR)\ChordsLyricsEditor.sbr"
	-@erase "$(INTDIR)\ChordsLyricsImportExport.obj"
	-@erase "$(INTDIR)\ChordsLyricsImportExport.sbr"
	-@erase "$(INTDIR)\Controller_Dlg.obj"
	-@erase "$(INTDIR)\Controller_Dlg.sbr"
	-@erase "$(INTDIR)\ControllerEffectsDlg.obj"
	-@erase "$(INTDIR)\ControllerEffectsDlg.sbr"
	-@erase "$(INTDIR)\CopyrightDlg.obj"
	-@erase "$(INTDIR)\CopyrightDlg.sbr"
	-@erase "$(INTDIR)\EffectFilterDlg.obj"
	-@erase "$(INTDIR)\EffectFilterDlg.sbr"
	-@erase "$(INTDIR)\ExchangeChannelsDlg.obj"
	-@erase "$(INTDIR)\ExchangeChannelsDlg.sbr"
	-@erase "$(INTDIR)\Expr_MainVolume.obj"
	-@erase "$(INTDIR)\Expr_MainVolume.sbr"
	-@erase "$(INTDIR)\Extras_Dlg.obj"
	-@erase "$(INTDIR)\Extras_Dlg.sbr"
	-@erase "$(INTDIR)\FileAttributesDlg.obj"
	-@erase "$(INTDIR)\FileAttributesDlg.sbr"
	-@erase "$(INTDIR)\FillLyricMethodDlg.obj"
	-@erase "$(INTDIR)\FillLyricMethodDlg.sbr"
	-@erase "$(INTDIR)\GlobalUtilities.obj"
	-@erase "$(INTDIR)\GlobalUtilities.sbr"
	-@erase "$(INTDIR)\HPMF_Interface.obj"
	-@erase "$(INTDIR)\HPMF_Interface.sbr"
	-@erase "$(INTDIR)\HPMF_Interface2.obj"
	-@erase "$(INTDIR)\HPMF_Interface2.sbr"
	-@erase "$(INTDIR)\ImportLyricsAtChannelNotes.obj"
	-@erase "$(INTDIR)\ImportLyricsAtChannelNotes.sbr"
	-@erase "$(INTDIR)\IniFile.obj"
	-@erase "$(INTDIR)\IniFile.sbr"
	-@erase "$(INTDIR)\InsdefDlg.obj"
	-@erase "$(INTDIR)\InsdefDlg.sbr"
	-@erase "$(INTDIR)\InsDefOnOffDlg.obj"
	-@erase "$(INTDIR)\InsDefOnOffDlg.sbr"
	-@erase "$(INTDIR)\InsertChordLyrics.obj"
	-@erase "$(INTDIR)\InsertChordLyrics.sbr"
	-@erase "$(INTDIR)\Log.obj"
	-@erase "$(INTDIR)\Log.sbr"
	-@erase "$(INTDIR)\LyricChordEditDlg.obj"
	-@erase "$(INTDIR)\LyricChordEditDlg.sbr"
	-@erase "$(INTDIR)\LyricChordEditElement.obj"
	-@erase "$(INTDIR)\LyricChordEditElement.sbr"
	-@erase "$(INTDIR)\LyricFrame.obj"
	-@erase "$(INTDIR)\LyricFrame.sbr"
	-@erase "$(INTDIR)\MainVolume_Expression_Folder_Dlg.obj"
	-@erase "$(INTDIR)\MainVolume_Expression_Folder_Dlg.sbr"
	-@erase "$(INTDIR)\Master_Volume_Folder_Dlg.obj"
	-@erase "$(INTDIR)\Master_Volume_Folder_Dlg.sbr"
	-@erase "$(INTDIR)\MasterVolume.obj"
	-@erase "$(INTDIR)\MasterVolume.sbr"
	-@erase "$(INTDIR)\MyArrays.obj"
	-@erase "$(INTDIR)\MyArrays.sbr"
	-@erase "$(INTDIR)\Play.obj"
	-@erase "$(INTDIR)\Play.sbr"
	-@erase "$(INTDIR)\Print.obj"
	-@erase "$(INTDIR)\Print.sbr"
	-@erase "$(INTDIR)\psruti.obj"
	-@erase "$(INTDIR)\psruti.pch"
	-@erase "$(INTDIR)\psruti.res"
	-@erase "$(INTDIR)\psruti.sbr"
	-@erase "$(INTDIR)\psrutidlg.obj"
	-@erase "$(INTDIR)\psrutidlg.sbr"
	-@erase "$(INTDIR)\QuantisizeChords.obj"
	-@erase "$(INTDIR)\QuantisizeChords.sbr"
	-@erase "$(INTDIR)\QuantisizeLyricsDlg.obj"
	-@erase "$(INTDIR)\QuantisizeLyricsDlg.sbr"
	-@erase "$(INTDIR)\Quickstart.obj"
	-@erase "$(INTDIR)\Quickstart.sbr"
	-@erase "$(INTDIR)\RevoicingDlg.obj"
	-@erase "$(INTDIR)\RevoicingDlg.sbr"
	-@erase "$(INTDIR)\RevoicingMethodDlg.obj"
	-@erase "$(INTDIR)\RevoicingMethodDlg.sbr"
	-@erase "$(INTDIR)\SaveChangesDlg.obj"
	-@erase "$(INTDIR)\SaveChangesDlg.sbr"
	-@erase "$(INTDIR)\ScoreChanDlg.obj"
	-@erase "$(INTDIR)\ScoreChanDlg.sbr"
	-@erase "$(INTDIR)\Select_Language.obj"
	-@erase "$(INTDIR)\Select_Language.sbr"
	-@erase "$(INTDIR)\SelectFillLyrics.obj"
	-@erase "$(INTDIR)\SelectFillLyrics.sbr"
	-@erase "$(INTDIR)\SelectMIDIDevice.obj"
	-@erase "$(INTDIR)\SelectMIDIDevice.sbr"
	-@erase "$(INTDIR)\SlctChordChan.obj"
	-@erase "$(INTDIR)\SlctChordChan.sbr"
	-@erase "$(INTDIR)\Songname.obj"
	-@erase "$(INTDIR)\Songname.sbr"
	-@erase "$(INTDIR)\StartBeat.obj"
	-@erase "$(INTDIR)\StartBeat.sbr"
	-@erase "$(INTDIR)\StartBeatFolderDlg.obj"
	-@erase "$(INTDIR)\StartBeatFolderDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\sysex_event_data.obj"
	-@erase "$(INTDIR)\sysex_event_data.sbr"
	-@erase "$(INTDIR)\sysex_event_prot.obj"
	-@erase "$(INTDIR)\sysex_event_prot.sbr"
	-@erase "$(INTDIR)\SysexDlg.obj"
	-@erase "$(INTDIR)\SysexDlg.sbr"
	-@erase "$(INTDIR)\SysexPasteDlg.obj"
	-@erase "$(INTDIR)\SysexPasteDlg.sbr"
	-@erase "$(INTDIR)\Tempo_Dlg.obj"
	-@erase "$(INTDIR)\Tempo_Dlg.sbr"
	-@erase "$(INTDIR)\Transpose_Method_Dlg.obj"
	-@erase "$(INTDIR)\Transpose_Method_Dlg.sbr"
	-@erase "$(INTDIR)\Transpose_no.obj"
	-@erase "$(INTDIR)\Transpose_no.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VelCompress.obj"
	-@erase "$(INTDIR)\VelCompress.sbr"
	-@erase "$(INTDIR)\VoiceFileBrowseDlg.obj"
	-@erase "$(INTDIR)\VoiceFileBrowseDlg.sbr"
	-@erase "$(INTDIR)\VoiceFileElement.obj"
	-@erase "$(INTDIR)\VoiceFileElement.sbr"
	-@erase "$(INTDIR)\VoicefileRevoicingDlg.obj"
	-@erase "$(INTDIR)\VoicefileRevoicingDlg.sbr"
	-@erase "$(INTDIR)\VolumeMethodDlg.obj"
	-@erase "$(INTDIR)\VolumeMethodDlg.sbr"
	-@erase "$(INTDIR)\XBrowseForFolder.obj"
	-@erase "$(INTDIR)\XBrowseForFolder.sbr"
	-@erase "$(OUTDIR)\psruti.bsc"
	-@erase "$(OUTDIR)\psruti.exe"
	-@erase "$(OUTDIR)\psruti.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\psruti.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\psruti.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\psruti.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BrowseDlg.sbr" \
	"$(INTDIR)\ChangeDrumVoicesDlg.sbr" \
	"$(INTDIR)\ChangeKeyDlg.sbr" \
	"$(INTDIR)\Chd.sbr" \
	"$(INTDIR)\ChordsLyricsEditor.sbr" \
	"$(INTDIR)\ChordsLyricsImportExport.sbr" \
	"$(INTDIR)\Controller_Dlg.sbr" \
	"$(INTDIR)\ControllerEffectsDlg.sbr" \
	"$(INTDIR)\CopyrightDlg.sbr" \
	"$(INTDIR)\EffectFilterDlg.sbr" \
	"$(INTDIR)\ExchangeChannelsDlg.sbr" \
	"$(INTDIR)\Expr_MainVolume.sbr" \
	"$(INTDIR)\Extras_Dlg.sbr" \
	"$(INTDIR)\FileAttributesDlg.sbr" \
	"$(INTDIR)\FillLyricMethodDlg.sbr" \
	"$(INTDIR)\GlobalUtilities.sbr" \
	"$(INTDIR)\HPMF_Interface.sbr" \
	"$(INTDIR)\HPMF_Interface2.sbr" \
	"$(INTDIR)\ImportLyricsAtChannelNotes.sbr" \
	"$(INTDIR)\IniFile.sbr" \
	"$(INTDIR)\InsdefDlg.sbr" \
	"$(INTDIR)\InsDefOnOffDlg.sbr" \
	"$(INTDIR)\InsertChordLyrics.sbr" \
	"$(INTDIR)\Log.sbr" \
	"$(INTDIR)\LyricChordEditDlg.sbr" \
	"$(INTDIR)\LyricChordEditElement.sbr" \
	"$(INTDIR)\LyricFrame.sbr" \
	"$(INTDIR)\Master_Volume_Folder_Dlg.sbr" \
	"$(INTDIR)\MasterVolume.sbr" \
	"$(INTDIR)\MyArrays.sbr" \
	"$(INTDIR)\Play.sbr" \
	"$(INTDIR)\Print.sbr" \
	"$(INTDIR)\psruti.sbr" \
	"$(INTDIR)\psrutidlg.sbr" \
	"$(INTDIR)\QuantisizeChords.sbr" \
	"$(INTDIR)\QuantisizeLyricsDlg.sbr" \
	"$(INTDIR)\Quickstart.sbr" \
	"$(INTDIR)\RevoicingDlg.sbr" \
	"$(INTDIR)\RevoicingMethodDlg.sbr" \
	"$(INTDIR)\SaveChangesDlg.sbr" \
	"$(INTDIR)\ScoreChanDlg.sbr" \
	"$(INTDIR)\Select_Language.sbr" \
	"$(INTDIR)\SelectFillLyrics.sbr" \
	"$(INTDIR)\SelectMIDIDevice.sbr" \
	"$(INTDIR)\SlctChordChan.sbr" \
	"$(INTDIR)\Songname.sbr" \
	"$(INTDIR)\StartBeat.sbr" \
	"$(INTDIR)\StartBeatFolderDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\sysex_event_data.sbr" \
	"$(INTDIR)\sysex_event_prot.sbr" \
	"$(INTDIR)\SysexDlg.sbr" \
	"$(INTDIR)\SysexPasteDlg.sbr" \
	"$(INTDIR)\Tempo_Dlg.sbr" \
	"$(INTDIR)\Transpose_Method_Dlg.sbr" \
	"$(INTDIR)\Transpose_no.sbr" \
	"$(INTDIR)\VelCompress.sbr" \
	"$(INTDIR)\VoiceFileBrowseDlg.sbr" \
	"$(INTDIR)\VoiceFileElement.sbr" \
	"$(INTDIR)\VoicefileRevoicingDlg.sbr" \
	"$(INTDIR)\VolumeMethodDlg.sbr" \
	"$(INTDIR)\XBrowseForFolder.sbr" \
	"$(INTDIR)\MainVolume_Expression_Folder_Dlg.sbr"

"$(OUTDIR)\psruti.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=HP_midifile.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\psruti.pdb" /machine:I386 /out:"$(OUTDIR)\psruti.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BrowseDlg.obj" \
	"$(INTDIR)\ChangeDrumVoicesDlg.obj" \
	"$(INTDIR)\ChangeKeyDlg.obj" \
	"$(INTDIR)\Chd.obj" \
	"$(INTDIR)\ChordsLyricsEditor.obj" \
	"$(INTDIR)\ChordsLyricsImportExport.obj" \
	"$(INTDIR)\Controller_Dlg.obj" \
	"$(INTDIR)\ControllerEffectsDlg.obj" \
	"$(INTDIR)\CopyrightDlg.obj" \
	"$(INTDIR)\EffectFilterDlg.obj" \
	"$(INTDIR)\ExchangeChannelsDlg.obj" \
	"$(INTDIR)\Expr_MainVolume.obj" \
	"$(INTDIR)\Extras_Dlg.obj" \
	"$(INTDIR)\FileAttributesDlg.obj" \
	"$(INTDIR)\FillLyricMethodDlg.obj" \
	"$(INTDIR)\GlobalUtilities.obj" \
	"$(INTDIR)\HPMF_Interface.obj" \
	"$(INTDIR)\HPMF_Interface2.obj" \
	"$(INTDIR)\ImportLyricsAtChannelNotes.obj" \
	"$(INTDIR)\IniFile.obj" \
	"$(INTDIR)\InsdefDlg.obj" \
	"$(INTDIR)\InsDefOnOffDlg.obj" \
	"$(INTDIR)\InsertChordLyrics.obj" \
	"$(INTDIR)\Log.obj" \
	"$(INTDIR)\LyricChordEditDlg.obj" \
	"$(INTDIR)\LyricChordEditElement.obj" \
	"$(INTDIR)\LyricFrame.obj" \
	"$(INTDIR)\Master_Volume_Folder_Dlg.obj" \
	"$(INTDIR)\MasterVolume.obj" \
	"$(INTDIR)\MyArrays.obj" \
	"$(INTDIR)\Play.obj" \
	"$(INTDIR)\Print.obj" \
	"$(INTDIR)\psruti.obj" \
	"$(INTDIR)\psrutidlg.obj" \
	"$(INTDIR)\QuantisizeChords.obj" \
	"$(INTDIR)\QuantisizeLyricsDlg.obj" \
	"$(INTDIR)\Quickstart.obj" \
	"$(INTDIR)\RevoicingDlg.obj" \
	"$(INTDIR)\RevoicingMethodDlg.obj" \
	"$(INTDIR)\SaveChangesDlg.obj" \
	"$(INTDIR)\ScoreChanDlg.obj" \
	"$(INTDIR)\Select_Language.obj" \
	"$(INTDIR)\SelectFillLyrics.obj" \
	"$(INTDIR)\SelectMIDIDevice.obj" \
	"$(INTDIR)\SlctChordChan.obj" \
	"$(INTDIR)\Songname.obj" \
	"$(INTDIR)\StartBeat.obj" \
	"$(INTDIR)\StartBeatFolderDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\sysex_event_data.obj" \
	"$(INTDIR)\sysex_event_prot.obj" \
	"$(INTDIR)\SysexDlg.obj" \
	"$(INTDIR)\SysexPasteDlg.obj" \
	"$(INTDIR)\Tempo_Dlg.obj" \
	"$(INTDIR)\Transpose_Method_Dlg.obj" \
	"$(INTDIR)\Transpose_no.obj" \
	"$(INTDIR)\VelCompress.obj" \
	"$(INTDIR)\VoiceFileBrowseDlg.obj" \
	"$(INTDIR)\VoiceFileElement.obj" \
	"$(INTDIR)\VoicefileRevoicingDlg.obj" \
	"$(INTDIR)\VolumeMethodDlg.obj" \
	"$(INTDIR)\XBrowseForFolder.obj" \
	"$(INTDIR)\psruti.res" \
	"$(INTDIR)\MainVolume_Expression_Folder_Dlg.obj"

"$(OUTDIR)\psruti.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "psruti - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\psruti.exe" "$(OUTDIR)\psruti.pch" "$(OUTDIR)\psruti.bsc"


CLEAN :
	-@erase "$(INTDIR)\BrowseDlg.obj"
	-@erase "$(INTDIR)\BrowseDlg.sbr"
	-@erase "$(INTDIR)\ChangeDrumVoicesDlg.obj"
	-@erase "$(INTDIR)\ChangeDrumVoicesDlg.sbr"
	-@erase "$(INTDIR)\ChangeKeyDlg.obj"
	-@erase "$(INTDIR)\ChangeKeyDlg.sbr"
	-@erase "$(INTDIR)\Chd.obj"
	-@erase "$(INTDIR)\Chd.sbr"
	-@erase "$(INTDIR)\ChordsLyricsEditor.obj"
	-@erase "$(INTDIR)\ChordsLyricsEditor.sbr"
	-@erase "$(INTDIR)\ChordsLyricsImportExport.obj"
	-@erase "$(INTDIR)\ChordsLyricsImportExport.sbr"
	-@erase "$(INTDIR)\Controller_Dlg.obj"
	-@erase "$(INTDIR)\Controller_Dlg.sbr"
	-@erase "$(INTDIR)\ControllerEffectsDlg.obj"
	-@erase "$(INTDIR)\ControllerEffectsDlg.sbr"
	-@erase "$(INTDIR)\CopyrightDlg.obj"
	-@erase "$(INTDIR)\CopyrightDlg.sbr"
	-@erase "$(INTDIR)\EffectFilterDlg.obj"
	-@erase "$(INTDIR)\EffectFilterDlg.sbr"
	-@erase "$(INTDIR)\ExchangeChannelsDlg.obj"
	-@erase "$(INTDIR)\ExchangeChannelsDlg.sbr"
	-@erase "$(INTDIR)\Expr_MainVolume.obj"
	-@erase "$(INTDIR)\Expr_MainVolume.sbr"
	-@erase "$(INTDIR)\Extras_Dlg.obj"
	-@erase "$(INTDIR)\Extras_Dlg.sbr"
	-@erase "$(INTDIR)\FileAttributesDlg.obj"
	-@erase "$(INTDIR)\FileAttributesDlg.sbr"
	-@erase "$(INTDIR)\FillLyricMethodDlg.obj"
	-@erase "$(INTDIR)\FillLyricMethodDlg.sbr"
	-@erase "$(INTDIR)\GlobalUtilities.obj"
	-@erase "$(INTDIR)\GlobalUtilities.sbr"
	-@erase "$(INTDIR)\HPMF_Interface.obj"
	-@erase "$(INTDIR)\HPMF_Interface.sbr"
	-@erase "$(INTDIR)\HPMF_Interface2.obj"
	-@erase "$(INTDIR)\HPMF_Interface2.sbr"
	-@erase "$(INTDIR)\ImportLyricsAtChannelNotes.obj"
	-@erase "$(INTDIR)\ImportLyricsAtChannelNotes.sbr"
	-@erase "$(INTDIR)\IniFile.obj"
	-@erase "$(INTDIR)\IniFile.sbr"
	-@erase "$(INTDIR)\InsdefDlg.obj"
	-@erase "$(INTDIR)\InsdefDlg.sbr"
	-@erase "$(INTDIR)\InsDefOnOffDlg.obj"
	-@erase "$(INTDIR)\InsDefOnOffDlg.sbr"
	-@erase "$(INTDIR)\InsertChordLyrics.obj"
	-@erase "$(INTDIR)\InsertChordLyrics.sbr"
	-@erase "$(INTDIR)\Log.obj"
	-@erase "$(INTDIR)\Log.sbr"
	-@erase "$(INTDIR)\LyricChordEditDlg.obj"
	-@erase "$(INTDIR)\LyricChordEditDlg.sbr"
	-@erase "$(INTDIR)\LyricChordEditElement.obj"
	-@erase "$(INTDIR)\LyricChordEditElement.sbr"
	-@erase "$(INTDIR)\LyricFrame.obj"
	-@erase "$(INTDIR)\LyricFrame.sbr"
	-@erase "$(INTDIR)\MainVolume_Expression_Folder_Dlg.obj"
	-@erase "$(INTDIR)\MainVolume_Expression_Folder_Dlg.sbr"
	-@erase "$(INTDIR)\Master_Volume_Folder_Dlg.obj"
	-@erase "$(INTDIR)\Master_Volume_Folder_Dlg.sbr"
	-@erase "$(INTDIR)\MasterVolume.obj"
	-@erase "$(INTDIR)\MasterVolume.sbr"
	-@erase "$(INTDIR)\MyArrays.obj"
	-@erase "$(INTDIR)\MyArrays.sbr"
	-@erase "$(INTDIR)\Play.obj"
	-@erase "$(INTDIR)\Play.sbr"
	-@erase "$(INTDIR)\Print.obj"
	-@erase "$(INTDIR)\Print.sbr"
	-@erase "$(INTDIR)\psruti.obj"
	-@erase "$(INTDIR)\psruti.pch"
	-@erase "$(INTDIR)\psruti.res"
	-@erase "$(INTDIR)\psruti.sbr"
	-@erase "$(INTDIR)\psrutidlg.obj"
	-@erase "$(INTDIR)\psrutidlg.sbr"
	-@erase "$(INTDIR)\QuantisizeChords.obj"
	-@erase "$(INTDIR)\QuantisizeChords.sbr"
	-@erase "$(INTDIR)\QuantisizeLyricsDlg.obj"
	-@erase "$(INTDIR)\QuantisizeLyricsDlg.sbr"
	-@erase "$(INTDIR)\Quickstart.obj"
	-@erase "$(INTDIR)\Quickstart.sbr"
	-@erase "$(INTDIR)\RevoicingDlg.obj"
	-@erase "$(INTDIR)\RevoicingDlg.sbr"
	-@erase "$(INTDIR)\RevoicingMethodDlg.obj"
	-@erase "$(INTDIR)\RevoicingMethodDlg.sbr"
	-@erase "$(INTDIR)\SaveChangesDlg.obj"
	-@erase "$(INTDIR)\SaveChangesDlg.sbr"
	-@erase "$(INTDIR)\ScoreChanDlg.obj"
	-@erase "$(INTDIR)\ScoreChanDlg.sbr"
	-@erase "$(INTDIR)\Select_Language.obj"
	-@erase "$(INTDIR)\Select_Language.sbr"
	-@erase "$(INTDIR)\SelectFillLyrics.obj"
	-@erase "$(INTDIR)\SelectFillLyrics.sbr"
	-@erase "$(INTDIR)\SelectMIDIDevice.obj"
	-@erase "$(INTDIR)\SelectMIDIDevice.sbr"
	-@erase "$(INTDIR)\SlctChordChan.obj"
	-@erase "$(INTDIR)\SlctChordChan.sbr"
	-@erase "$(INTDIR)\Songname.obj"
	-@erase "$(INTDIR)\Songname.sbr"
	-@erase "$(INTDIR)\StartBeat.obj"
	-@erase "$(INTDIR)\StartBeat.sbr"
	-@erase "$(INTDIR)\StartBeatFolderDlg.obj"
	-@erase "$(INTDIR)\StartBeatFolderDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\sysex_event_data.obj"
	-@erase "$(INTDIR)\sysex_event_data.sbr"
	-@erase "$(INTDIR)\sysex_event_prot.obj"
	-@erase "$(INTDIR)\sysex_event_prot.sbr"
	-@erase "$(INTDIR)\SysexDlg.obj"
	-@erase "$(INTDIR)\SysexDlg.sbr"
	-@erase "$(INTDIR)\SysexPasteDlg.obj"
	-@erase "$(INTDIR)\SysexPasteDlg.sbr"
	-@erase "$(INTDIR)\Tempo_Dlg.obj"
	-@erase "$(INTDIR)\Tempo_Dlg.sbr"
	-@erase "$(INTDIR)\Transpose_Method_Dlg.obj"
	-@erase "$(INTDIR)\Transpose_Method_Dlg.sbr"
	-@erase "$(INTDIR)\Transpose_no.obj"
	-@erase "$(INTDIR)\Transpose_no.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VelCompress.obj"
	-@erase "$(INTDIR)\VelCompress.sbr"
	-@erase "$(INTDIR)\VoiceFileBrowseDlg.obj"
	-@erase "$(INTDIR)\VoiceFileBrowseDlg.sbr"
	-@erase "$(INTDIR)\VoiceFileElement.obj"
	-@erase "$(INTDIR)\VoiceFileElement.sbr"
	-@erase "$(INTDIR)\VoicefileRevoicingDlg.obj"
	-@erase "$(INTDIR)\VoicefileRevoicingDlg.sbr"
	-@erase "$(INTDIR)\VolumeMethodDlg.obj"
	-@erase "$(INTDIR)\VolumeMethodDlg.sbr"
	-@erase "$(INTDIR)\XBrowseForFolder.obj"
	-@erase "$(INTDIR)\XBrowseForFolder.sbr"
	-@erase "$(OUTDIR)\psruti.bsc"
	-@erase "$(OUTDIR)\psruti.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /I "D" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\psruti.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\psruti.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BrowseDlg.sbr" \
	"$(INTDIR)\ChangeDrumVoicesDlg.sbr" \
	"$(INTDIR)\ChangeKeyDlg.sbr" \
	"$(INTDIR)\Chd.sbr" \
	"$(INTDIR)\ChordsLyricsEditor.sbr" \
	"$(INTDIR)\ChordsLyricsImportExport.sbr" \
	"$(INTDIR)\Controller_Dlg.sbr" \
	"$(INTDIR)\ControllerEffectsDlg.sbr" \
	"$(INTDIR)\CopyrightDlg.sbr" \
	"$(INTDIR)\EffectFilterDlg.sbr" \
	"$(INTDIR)\ExchangeChannelsDlg.sbr" \
	"$(INTDIR)\Expr_MainVolume.sbr" \
	"$(INTDIR)\Extras_Dlg.sbr" \
	"$(INTDIR)\FileAttributesDlg.sbr" \
	"$(INTDIR)\FillLyricMethodDlg.sbr" \
	"$(INTDIR)\GlobalUtilities.sbr" \
	"$(INTDIR)\HPMF_Interface.sbr" \
	"$(INTDIR)\HPMF_Interface2.sbr" \
	"$(INTDIR)\ImportLyricsAtChannelNotes.sbr" \
	"$(INTDIR)\IniFile.sbr" \
	"$(INTDIR)\InsdefDlg.sbr" \
	"$(INTDIR)\InsDefOnOffDlg.sbr" \
	"$(INTDIR)\InsertChordLyrics.sbr" \
	"$(INTDIR)\Log.sbr" \
	"$(INTDIR)\LyricChordEditDlg.sbr" \
	"$(INTDIR)\LyricChordEditElement.sbr" \
	"$(INTDIR)\LyricFrame.sbr" \
	"$(INTDIR)\Master_Volume_Folder_Dlg.sbr" \
	"$(INTDIR)\MasterVolume.sbr" \
	"$(INTDIR)\MyArrays.sbr" \
	"$(INTDIR)\Play.sbr" \
	"$(INTDIR)\Print.sbr" \
	"$(INTDIR)\psruti.sbr" \
	"$(INTDIR)\psrutidlg.sbr" \
	"$(INTDIR)\QuantisizeChords.sbr" \
	"$(INTDIR)\QuantisizeLyricsDlg.sbr" \
	"$(INTDIR)\Quickstart.sbr" \
	"$(INTDIR)\RevoicingDlg.sbr" \
	"$(INTDIR)\RevoicingMethodDlg.sbr" \
	"$(INTDIR)\SaveChangesDlg.sbr" \
	"$(INTDIR)\ScoreChanDlg.sbr" \
	"$(INTDIR)\Select_Language.sbr" \
	"$(INTDIR)\SelectFillLyrics.sbr" \
	"$(INTDIR)\SelectMIDIDevice.sbr" \
	"$(INTDIR)\SlctChordChan.sbr" \
	"$(INTDIR)\Songname.sbr" \
	"$(INTDIR)\StartBeat.sbr" \
	"$(INTDIR)\StartBeatFolderDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\sysex_event_data.sbr" \
	"$(INTDIR)\sysex_event_prot.sbr" \
	"$(INTDIR)\SysexDlg.sbr" \
	"$(INTDIR)\SysexPasteDlg.sbr" \
	"$(INTDIR)\Tempo_Dlg.sbr" \
	"$(INTDIR)\Transpose_Method_Dlg.sbr" \
	"$(INTDIR)\Transpose_no.sbr" \
	"$(INTDIR)\VelCompress.sbr" \
	"$(INTDIR)\VoiceFileBrowseDlg.sbr" \
	"$(INTDIR)\VoiceFileElement.sbr" \
	"$(INTDIR)\VoicefileRevoicingDlg.sbr" \
	"$(INTDIR)\VolumeMethodDlg.sbr" \
	"$(INTDIR)\XBrowseForFolder.sbr" \
	"$(INTDIR)\MainVolume_Expression_Folder_Dlg.sbr"

"$(OUTDIR)\psruti.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=HP_midifile.lib /nologo /subsystem:windows /profile /debug /machine:I386 /out:"$(OUTDIR)\psruti.exe" /libpath:"d:/Programmierung/psruti_3-0/Debug" 
LINK32_OBJS= \
	"$(INTDIR)\BrowseDlg.obj" \
	"$(INTDIR)\ChangeDrumVoicesDlg.obj" \
	"$(INTDIR)\ChangeKeyDlg.obj" \
	"$(INTDIR)\Chd.obj" \
	"$(INTDIR)\ChordsLyricsEditor.obj" \
	"$(INTDIR)\ChordsLyricsImportExport.obj" \
	"$(INTDIR)\Controller_Dlg.obj" \
	"$(INTDIR)\ControllerEffectsDlg.obj" \
	"$(INTDIR)\CopyrightDlg.obj" \
	"$(INTDIR)\EffectFilterDlg.obj" \
	"$(INTDIR)\ExchangeChannelsDlg.obj" \
	"$(INTDIR)\Expr_MainVolume.obj" \
	"$(INTDIR)\Extras_Dlg.obj" \
	"$(INTDIR)\FileAttributesDlg.obj" \
	"$(INTDIR)\FillLyricMethodDlg.obj" \
	"$(INTDIR)\GlobalUtilities.obj" \
	"$(INTDIR)\HPMF_Interface.obj" \
	"$(INTDIR)\HPMF_Interface2.obj" \
	"$(INTDIR)\ImportLyricsAtChannelNotes.obj" \
	"$(INTDIR)\IniFile.obj" \
	"$(INTDIR)\InsdefDlg.obj" \
	"$(INTDIR)\InsDefOnOffDlg.obj" \
	"$(INTDIR)\InsertChordLyrics.obj" \
	"$(INTDIR)\Log.obj" \
	"$(INTDIR)\LyricChordEditDlg.obj" \
	"$(INTDIR)\LyricChordEditElement.obj" \
	"$(INTDIR)\LyricFrame.obj" \
	"$(INTDIR)\Master_Volume_Folder_Dlg.obj" \
	"$(INTDIR)\MasterVolume.obj" \
	"$(INTDIR)\MyArrays.obj" \
	"$(INTDIR)\Play.obj" \
	"$(INTDIR)\Print.obj" \
	"$(INTDIR)\psruti.obj" \
	"$(INTDIR)\psrutidlg.obj" \
	"$(INTDIR)\QuantisizeChords.obj" \
	"$(INTDIR)\QuantisizeLyricsDlg.obj" \
	"$(INTDIR)\Quickstart.obj" \
	"$(INTDIR)\RevoicingDlg.obj" \
	"$(INTDIR)\RevoicingMethodDlg.obj" \
	"$(INTDIR)\SaveChangesDlg.obj" \
	"$(INTDIR)\ScoreChanDlg.obj" \
	"$(INTDIR)\Select_Language.obj" \
	"$(INTDIR)\SelectFillLyrics.obj" \
	"$(INTDIR)\SelectMIDIDevice.obj" \
	"$(INTDIR)\SlctChordChan.obj" \
	"$(INTDIR)\Songname.obj" \
	"$(INTDIR)\StartBeat.obj" \
	"$(INTDIR)\StartBeatFolderDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\sysex_event_data.obj" \
	"$(INTDIR)\sysex_event_prot.obj" \
	"$(INTDIR)\SysexDlg.obj" \
	"$(INTDIR)\SysexPasteDlg.obj" \
	"$(INTDIR)\Tempo_Dlg.obj" \
	"$(INTDIR)\Transpose_Method_Dlg.obj" \
	"$(INTDIR)\Transpose_no.obj" \
	"$(INTDIR)\VelCompress.obj" \
	"$(INTDIR)\VoiceFileBrowseDlg.obj" \
	"$(INTDIR)\VoiceFileElement.obj" \
	"$(INTDIR)\VoicefileRevoicingDlg.obj" \
	"$(INTDIR)\VolumeMethodDlg.obj" \
	"$(INTDIR)\XBrowseForFolder.obj" \
	"$(INTDIR)\psruti.res" \
	"$(INTDIR)\MainVolume_Expression_Folder_Dlg.obj"

"$(OUTDIR)\psruti.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("psruti.dep")
!INCLUDE "psruti.dep"
!ELSE 
!MESSAGE Warning: cannot find "psruti.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "psruti - Win32 Release" || "$(CFG)" == "psruti - Win32 Debug"
SOURCE=.\BrowseDlg.cpp

"$(INTDIR)\BrowseDlg.obj"	"$(INTDIR)\BrowseDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ChangeDrumVoicesDlg.cpp

"$(INTDIR)\ChangeDrumVoicesDlg.obj"	"$(INTDIR)\ChangeDrumVoicesDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ChangeKeyDlg.cpp

"$(INTDIR)\ChangeKeyDlg.obj"	"$(INTDIR)\ChangeKeyDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Chd.cpp

"$(INTDIR)\Chd.obj"	"$(INTDIR)\Chd.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ChordsLyricsEditor.cpp

"$(INTDIR)\ChordsLyricsEditor.obj"	"$(INTDIR)\ChordsLyricsEditor.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ChordsLyricsImportExport.cpp

"$(INTDIR)\ChordsLyricsImportExport.obj"	"$(INTDIR)\ChordsLyricsImportExport.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Controller_Dlg.cpp

"$(INTDIR)\Controller_Dlg.obj"	"$(INTDIR)\Controller_Dlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ControllerEffectsDlg.cpp

"$(INTDIR)\ControllerEffectsDlg.obj"	"$(INTDIR)\ControllerEffectsDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CopyrightDlg.cpp

"$(INTDIR)\CopyrightDlg.obj"	"$(INTDIR)\CopyrightDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\EffectFilterDlg.cpp

"$(INTDIR)\EffectFilterDlg.obj"	"$(INTDIR)\EffectFilterDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ExchangeChannelsDlg.cpp

"$(INTDIR)\ExchangeChannelsDlg.obj"	"$(INTDIR)\ExchangeChannelsDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Expr_MainVolume.cpp

"$(INTDIR)\Expr_MainVolume.obj"	"$(INTDIR)\Expr_MainVolume.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Extras_Dlg.cpp

"$(INTDIR)\Extras_Dlg.obj"	"$(INTDIR)\Extras_Dlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FileAttributesDlg.cpp

"$(INTDIR)\FileAttributesDlg.obj"	"$(INTDIR)\FileAttributesDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FillLyricMethodDlg.cpp

"$(INTDIR)\FillLyricMethodDlg.obj"	"$(INTDIR)\FillLyricMethodDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\GlobalUtilities.cpp

"$(INTDIR)\GlobalUtilities.obj"	"$(INTDIR)\GlobalUtilities.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\HPMF_Interface.cpp

"$(INTDIR)\HPMF_Interface.obj"	"$(INTDIR)\HPMF_Interface.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\HPMF_Interface2.cpp

"$(INTDIR)\HPMF_Interface2.obj"	"$(INTDIR)\HPMF_Interface2.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ImportLyricsAtChannelNotes.cpp

"$(INTDIR)\ImportLyricsAtChannelNotes.obj"	"$(INTDIR)\ImportLyricsAtChannelNotes.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\IniFile.cpp

"$(INTDIR)\IniFile.obj"	"$(INTDIR)\IniFile.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\InsdefDlg.cpp

"$(INTDIR)\InsdefDlg.obj"	"$(INTDIR)\InsdefDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\InsDefOnOffDlg.cpp

"$(INTDIR)\InsDefOnOffDlg.obj"	"$(INTDIR)\InsDefOnOffDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\InsertChordLyrics.cpp

"$(INTDIR)\InsertChordLyrics.obj"	"$(INTDIR)\InsertChordLyrics.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Log.cpp

"$(INTDIR)\Log.obj"	"$(INTDIR)\Log.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LyricChordEditDlg.cpp

"$(INTDIR)\LyricChordEditDlg.obj"	"$(INTDIR)\LyricChordEditDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LyricChordEditElement.cpp

"$(INTDIR)\LyricChordEditElement.obj"	"$(INTDIR)\LyricChordEditElement.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LyricFrame.cpp

"$(INTDIR)\LyricFrame.obj"	"$(INTDIR)\LyricFrame.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MainVolume_Expression_Folder_Dlg.cpp

"$(INTDIR)\MainVolume_Expression_Folder_Dlg.obj"	"$(INTDIR)\MainVolume_Expression_Folder_Dlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Master_Volume_Folder_Dlg.cpp

"$(INTDIR)\Master_Volume_Folder_Dlg.obj"	"$(INTDIR)\Master_Volume_Folder_Dlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MasterVolume.cpp

"$(INTDIR)\MasterVolume.obj"	"$(INTDIR)\MasterVolume.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MyArrays.cpp

"$(INTDIR)\MyArrays.obj"	"$(INTDIR)\MyArrays.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Play.cpp

"$(INTDIR)\Play.obj"	"$(INTDIR)\Play.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Print.cpp

"$(INTDIR)\Print.obj"	"$(INTDIR)\Print.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\psruti.cpp

"$(INTDIR)\psruti.obj"	"$(INTDIR)\psruti.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\psruti.rc

"$(INTDIR)\psruti.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\psrutidlg.cpp

"$(INTDIR)\psrutidlg.obj"	"$(INTDIR)\psrutidlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\QuantisizeChords.cpp

"$(INTDIR)\QuantisizeChords.obj"	"$(INTDIR)\QuantisizeChords.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\QuantisizeLyricsDlg.cpp

"$(INTDIR)\QuantisizeLyricsDlg.obj"	"$(INTDIR)\QuantisizeLyricsDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Quickstart.cpp

"$(INTDIR)\Quickstart.obj"	"$(INTDIR)\Quickstart.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RevoicingDlg.cpp

"$(INTDIR)\RevoicingDlg.obj"	"$(INTDIR)\RevoicingDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RevoicingMethodDlg.cpp

"$(INTDIR)\RevoicingMethodDlg.obj"	"$(INTDIR)\RevoicingMethodDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SaveChangesDlg.cpp

"$(INTDIR)\SaveChangesDlg.obj"	"$(INTDIR)\SaveChangesDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ScoreChanDlg.cpp

"$(INTDIR)\ScoreChanDlg.obj"	"$(INTDIR)\ScoreChanDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Select_Language.cpp

"$(INTDIR)\Select_Language.obj"	"$(INTDIR)\Select_Language.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SelectFillLyrics.cpp

"$(INTDIR)\SelectFillLyrics.obj"	"$(INTDIR)\SelectFillLyrics.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SelectMIDIDevice.cpp

"$(INTDIR)\SelectMIDIDevice.obj"	"$(INTDIR)\SelectMIDIDevice.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SlctChordChan.cpp

"$(INTDIR)\SlctChordChan.obj"	"$(INTDIR)\SlctChordChan.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Songname.cpp

"$(INTDIR)\Songname.obj"	"$(INTDIR)\Songname.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StartBeat.cpp

"$(INTDIR)\StartBeat.obj"	"$(INTDIR)\StartBeat.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StartBeatFolderDlg.cpp

"$(INTDIR)\StartBeatFolderDlg.obj"	"$(INTDIR)\StartBeatFolderDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "psruti - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\psruti.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\psruti.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "psruti - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /I "D" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\psruti.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\psruti.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\sysex_event_data.cpp

"$(INTDIR)\sysex_event_data.obj"	"$(INTDIR)\sysex_event_data.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\sysex_event_prot.cpp

"$(INTDIR)\sysex_event_prot.obj"	"$(INTDIR)\sysex_event_prot.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SysexDlg.cpp

"$(INTDIR)\SysexDlg.obj"	"$(INTDIR)\SysexDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SysexPasteDlg.cpp

"$(INTDIR)\SysexPasteDlg.obj"	"$(INTDIR)\SysexPasteDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Tempo_Dlg.cpp

"$(INTDIR)\Tempo_Dlg.obj"	"$(INTDIR)\Tempo_Dlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Transpose_Method_Dlg.cpp

"$(INTDIR)\Transpose_Method_Dlg.obj"	"$(INTDIR)\Transpose_Method_Dlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Transpose_no.cpp

"$(INTDIR)\Transpose_no.obj"	"$(INTDIR)\Transpose_no.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VelCompress.cpp

"$(INTDIR)\VelCompress.obj"	"$(INTDIR)\VelCompress.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VoiceFileBrowseDlg.cpp

"$(INTDIR)\VoiceFileBrowseDlg.obj"	"$(INTDIR)\VoiceFileBrowseDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VoiceFileElement.cpp

"$(INTDIR)\VoiceFileElement.obj"	"$(INTDIR)\VoiceFileElement.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VoicefileRevoicingDlg.cpp

"$(INTDIR)\VoicefileRevoicingDlg.obj"	"$(INTDIR)\VoicefileRevoicingDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VolumeMethodDlg.cpp

"$(INTDIR)\VolumeMethodDlg.obj"	"$(INTDIR)\VolumeMethodDlg.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\XBrowseForFolder.cpp

"$(INTDIR)\XBrowseForFolder.obj"	"$(INTDIR)\XBrowseForFolder.sbr" : $(SOURCE) "$(INTDIR)"



!ENDIF 

