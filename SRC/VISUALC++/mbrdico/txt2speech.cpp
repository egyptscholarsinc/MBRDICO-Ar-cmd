/*
 * File:    Txt2Speech.cpp
 * Purpose: Front end of talking dictionnary 
 * Author: Vincent Pagel Email: pagel@tcts.fpms.ac.be
 * Version : 0.99
 * Time-stamp: <1998-10-28 12:28:56 pagel>
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
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * History:
 *
 *  10/03/98 : Created
 */
#include <stdlib.h>
#include <stdio.h>
#include <strstream>

#include "stdafx.h"
#include "mbrplay.h"

#include "VpError.hpp"
#include "Txt2Speech.hpp"
#include "LPhonemePlus.hpp"

#include "resource.h"
#include "Loading.h"

// Global variable
Txt2Speech tts;

void Txt2Speech::utter(const char *target, const char* lang, BOOL display, LPCTSTR outFile)
{
  strstream outpho;
  LPhonemePlus lpp;
  
  try
    {
      if (!strcmp(lang,cur_lang)==0)
	{		
	  if (phonet)
	    phonet->~Speak(); // forget previous data
	       
	  // Initialize from the data in the .ini file
	  char ini_file[255];
	  sprintf(ini_file,"%s.ini",lang);
	       
	  CLoading message;
	  message.Create(MAKEINTRESOURCE(IDD_LOADING),AfxGetMainWnd());
	  message.ShowWindow(SW_SHOW);
	  message.RedrawWindow(NULL,NULL,RDW_UPDATENOW);
	  phonet= load_Speak(ini_file);
	  cur_lang=strdup(lang);
	  message.ShowWindow(SW_HIDE);
	  message.DestroyWindow();
	}
	   
      phonet->transcribe(lpp,target,130,40,1);
	   int error_code= MBR_SetDatabase(phonet->get_dba());
	    
	   if (error_code != MBRERR_NOERROR)
	     {
	       char local[255];
	       MBR_LastError(local,sizeof(local));
	       fatal_message(-1,"MBROLA Init failed:%s",local);
	     }
	   
	   // End with a Flush command


	   outpho << "; Target " << target << endl << "_ 100\n" 
		  << lpp << endl << "_ 100\n _ 0" << endl << char(0);
	   if(outFile) //save wave file after playing
		   MBR_Play(CString(outpho.str()),MBROUT_WAVE,outFile,NULL);
	   int ret=MBR_Play(CString(outpho.str()),MBR_WAIT,NULL,NULL);
	   
	   // If you want to display the phonetic transcription
	   if (display)
	     MessageBox(AfxGetMainWnd()->GetSafeHwnd(), CString(outpho.str()), CString("Phonetized"), MB_OK );
	 }
  catch (int somthg_wrong)
    {
      // We'll handle this another day
    }
}
