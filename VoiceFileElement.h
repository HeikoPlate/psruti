// VoiceFileElement.h
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#if !defined(VOICEFILEELEMENT_H__76FC731D_5B92_414A_9B89_7B1C26949F11__INCLUDED_)
#define VOICEFILEELEMENT_H__76FC731D_5B92_414A_9B89_7B1C26949F11__INCLUDED_

class VoiceFileElement
{
public:
	VoiceFileElement();
	virtual ~VoiceFileElement();
	char* voicename;
	char* filename;
};

class VoiceFilePathElement
{
public:
	VoiceFilePathElement();
	virtual ~VoiceFilePathElement();
	CString voicename;
	CString filepath;
	int block;
	bool with_controller;
};
#endif
