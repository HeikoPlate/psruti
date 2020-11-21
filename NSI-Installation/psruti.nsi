##{{NSIS_PLUS_BEGIN_TODO}}##
#F0
#00Zu installierende Dateien per Drag&Drop hinzufügen
#T04.02.2018
#A01
##{{NSIS_PLUS_END_TODO}}##

!define PROJECT         "PSRUTI817"
!define FLATPROJECT     "psruti817"
!define NAME            "PSRUTI"
!define VER_MAJOR               8
!define VER_MINOR              17
!define ICON_NAME       "PSRUTI"
!define PATH            "C:\Programmierung\psruti_8-17\Lieferstand\"
!define OUTF            "${FLATPROJECT}_setup.exe"

SetOverwrite ifnewer
InstProgressFlags smooth
CRCCheck on
SetCompress auto
AutoCloseWindow false
ShowInstDetails show
ShowUninstDetails show
SilentInstall normal
SilentUnInstall normal


; XPStyle on

;--------------------------------
; Page components
Page directory
Page instfiles
;--------------------------------

; First is default
LoadLanguageFile "${NSISDIR}\Contrib\Language files\German.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\English.nlf"

; Set name using the normal interface (Name command)
;LangString Name ${LANG_ENGLISH} "English"
;LangString Name ${LANG_GERMAN} "Deutsch"
LangString Name ${LANG_ENGLISH} "PSRUTI"
LangString Name ${LANG_GERMAN} "PSRUTI"
Name $(Name)


; The language can be the last used language like above, but it can be defined using /LANG
; ComponentText /LANG=${LANG_GERMAN} "Hiermit wird PSRUTI auf ihrem Computer installiert"
; ComponentText /LANG=${LANG_ENGLISH} "This will install PSRUTI on your computer"

; Directly change the inner lang strings (Same as ComponentText)
LangString ^ComponentsText ${LANG_ENGLISH} "This will install PSRUTI on your computer"
LangString ^ComponentsText ${LANG_GERMAN} "Hiermit wird PSRUTI auf ihrem Computer installiert"


; DirText " "

; Ausgabe-Datei
OutFile ${OUTF}
#00 OutFile "${FLATPROJECT}-setup.exe"
Caption "${NAME} Installation"
; Default-Installations-Verzeichnis
; SetCompressor "lzma" /solid
InstallDir "$PROGRAMFILES\PSRUTI"
InstallDirRegKey HKLM "SOFTWARE\PSRUTI" "Path"


########################################################
################## Installations-Projekt  ########################
########################################################


Section "PSRUTI"

  ; Uninstall Part

  ; remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\PSRUTI"
  ; remove files
  Delete $INSTDIR\*.*
  ; remove shortcuts, if any.
  Delete "$SMPROGRAMS\PSRUTI\*.*"
  Delete "$DESKTOP\${ICON_NAME}.lnk"
 ; remove directories used.
  RMDir "$SMPROGRAMS\PSRUTI"
  RMDir "$INSTDIR"

  SetOutPath $INSTDIR
  File "${PATH}psruti.exe"
  File "${PATH}HP_midifile.dll"
  File "${PATH}psruti_res_germ.dll"
  File "${PATH}psruti_res_eng.dll"
  File "${PATH}psruti_germ.pdf"
  File "${PATH}psruti_eng.pdf"

  ; do not overwrite psruti.ini, if it exists in $DOCUMENTS
  
  IfFileExists $DOCUMENTS\psruti.ini file_end 0
  SetOutPath $DOCUMENTS
  StrCmp $LANGUAGE ${LANG_GERMAN} 0 +2
  File "${PATH}\germ\psruti.ini"
  StrCmp $LANGUAGE ${LANG_ENGLISH} 0 +2
  File "${PATH}\eng\psruti.ini"

  file_end:
  CreateDirectory $SMPROGRAMS\PSRUTI
  CreateShortcut "$SMPROGRAMS\PSRUTI\PSRUTI.lnk" "$INSTDIR\psruti.exe"

  ; Desktop-Icon?       
  StrCmp $LANGUAGE ${LANG_GERMAN} 0 +2
  MessageBox MB_YESNO "Soll ein Icon für PSRUTI auf das Desktop gelegt werden?" IDYES icon_yes IDNO icon_no
  StrCmp $LANGUAGE ${LANG_ENGLISH} 0 +2
  MessageBox MB_YESNO "Do you want to get an icon on the desktop?" IDYES icon_yes IDNO icon_no
  icon_yes:
  CreateShortcut "$DESKTOP\${ICON_NAME}.lnk" "$INSTDIR\psruti.exe"
  icon_no:
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\PSRUTI" "DisplayName" "${NAME} (remove only)"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\PSRUTI" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteUninstaller "uninstall.exe"
SectionEnd


Section "Uninstall"
  ; remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\PSRUTI"
  ; remove files
  Delete $INSTDIR\*.*
  ; remove shortcuts, if any.
  Delete "$SMPROGRAMS\PSRUTI\*.*"
  Delete "$DESKTOP\${ICON_NAME}.lnk"
  ; remove directories used.
  RMDir "$SMPROGRAMS\PSRUTI"
  RMDir "$INSTDIR"
SectionEnd

Function .onInit
        Push ${LANG_GERMAN}
        Push Deutsch
        Push ${LANG_ENGLISH}
        Push English
        Push 2 ; 2 is the number of languages
        LangDLL::LangDialog "Installer Language" "Sprache des Installationsprogramms wählen Select language of the installer"
        Pop $LANGUAGE
        StrCmp $LANGUAGE "cancel" 0 +2
                Abort
        !define LNG $LANGUAGE   
FunctionEnd

