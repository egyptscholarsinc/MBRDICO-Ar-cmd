/*
 * File:    Txt2Speech
 * Purpose: Windows front end
 * Author:  Vincent Pagel ( pagel@tcts.fpms.ac.be )
 * Version : 0.99
 * Time-stamp: <1998-11-05 11:11:32 pagel>
 * 
 * Copyright (c) 1998 Faculte Polytechnique de Mons (TCTS lab)
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 1
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef TXT2SPEECH_HPP
#define TXT2SPEECH_HPP

#include "Speak.hpp"


class Txt2Speech
{
public:
	Txt2Speech(): phonet(0) { cur_lang= strdup("none");	}

	~Txt2Speech()
	{
		if (phonet)
			phonet->~Speak();
		free(cur_lang);
	}

	void utter(const char *target, const char* lang, BOOL display);

private:
	Speak* phonet;  // length, exceptions, decision tree for phonetization
	char* cur_lang; // init file of phonet
};

extern Txt2Speech tts;


#endif