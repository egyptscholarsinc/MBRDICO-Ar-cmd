                           MBRDICO 
    Another speaking dictionary for the MBROLA Speech Synthesizer
              Faculté Polytechnique of Mons - Belgium
					 		08/03/00, release 1.05
							
				home: http://tcts.fpms.ac.be/synthesis/mbrdico

This is the fourth release of the MBRDICO talking dictionary for
American English, Arabic, British English, Dutch, French and Spanish.
It is intended to respectivelly run with the Mbrola us, ar, en, nl, fr
and es databases, that you should separetely download from:
				 http://tcts.fpms.ac.be/synthesis

For those of you who want to directly play with the toy, the BINARY
directory contains precompiled binaries for Windows and Linux.

At the moment it compiles under Windows and Unix platforms. The
sources are provided with a VisualC++ project, as well as a Unix
makefile so that you can play with the program and develop new
languages. It is heavily based on the Stantard Template Library (the
one provided by Visual, or by GNU CC work).

A novelty in this release is the possibility to insert words into a
carrier sentence, if you want to use this feature, please read the file
00ReadmeCarrier.txt

All the sources are in the SRC directory. DATA contains resources
necessary to utter different languages ( .zs is a Zscore table for
duration computation, .tree is a decision tree for letter to phoneme
conversion, and .dic is an exception dictionary). 

If you want to understand how the letter to phoneme alogrithm works
you can read "LETTER TO SOUND RULES FOR ACCENTED LEXICON COMPRESSION"
Vincent Pagel, Kevin Lenzo and Alan W. Black Proc ICSLP98 Sydney
(http://tcts.fpms.ac.be/publications/papers/1998/icslp98_vpklab.zip) 

Then you can build your own dictionary by downloading the decision
tree package on http://tcts.fpms.ac.be/synthesis/mbrdico

Copyright
=========

Please read the GNU Copyright and distribution notice in the file
copying.txt 

Installation on MS-WINDOWS platforms
====================================

1) Download the MBROLA database you need on:
              http://tcts.fpms.ac.be/synthesis 

2) Download the MbrolaTools for Windows on the same site

3) Register your Mbrola database with the Wizard in the control panel

4) Verify you are able to play demo pho-files provided in the TEST
  directory of the diphone database.

5) Launch mbrdico.exe in the BINARY directory, it should talk (or go
  in the VISUALC++ project to compile your home tuned version).

WARNING : if you don't have Visual installed, mbrdico.exe will complain
it does'nt find MSVCRT*.DLL something... Those system dll are provided
at ftp://tcts.fpms.ac.be/pub/mbrola/tts/MBRDICO/system32.zip

Talking about compilers:

C:\Program Files\DevStudio\VC\INCLUDE\xtree(522) : warning C4786: '?_Lmost@?$_Tree@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$pair@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@2@U_Kfn@?$map@V?$basic_string @DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@2@U?$less@V?$basic_string@DU?$char_traits@D@st d@@V?$allocator@D@2@@std@@@2@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@IAEAAPAU_Node@12@XZ' : identifier was truncated to '255' characters in the browser information

this message is just everyday life under Microsoft Visual, since it's
not able to handle names longer that 255 chars, ha ha ha (still you
can stain your code with pragmas :-p). Bashers would say that
Microsoft strategy to eliminate free software is to make them sick of
fun.

Installation for UNIX platforms
===============================

When you finish cheering and clapping hands about the above mentioned
255 char limit, you can test Mbrdico on SUN/Solaris and PC/Linux and
probably any other Unix box supporting latest gcc sources (many C++
compilers are not ANSI yet).

1) Download the MBROLA database you need on:
              http://tcts.fpms.ac.be/synthesis 

  Also download the mbrola binary for your platform *:-)

2) check you can play demo sentence with a line such as 
	  mbrola us1 TEST/alice.pho -.au | audioplay
		
		NOTE: replace audioplay by your local audioplayer... The linux
		version of Mbrola provide an audioplayer called "rawplay".

3) define the "us1", "fr1" and "ar1" environment variable which should
   look like (csh) : 

   setenv us1 "mbrola /usr/local/lib/mbrola/us1/us1 - -.au | audioplay"
   setenv fr1 "mbrola /usr/local/lib/mbrola/fr1/fr1 - -.au | audioplay"

on Linux use something like (with bash) :

	export us1="mbrola /usr/local/lib/mbrola/us1/us1 - -.raw | rawplay"
   setenv fr1="mbrola /usr/local/lib/mbrola/fr1/fr1 - -.raw | rawplay"


If you don't have Mbrola yet, and that you simply want to visualize
the phonetic output try:

	  setenv us1 "cat > /dev/null"

4) Go in SRC, close your eyes, type "make", press enter, open an eye,
  then both if you see something like:

> ------------------------
> The binary is in ../BINARY/mbrdico.solaris
> Try something like ../BINARY/mbrdico.solaris ../BINARY/us.ini

In this case follow the advise. In the other situation, if the
compiler is whining about STL, the best thing is probably to download
GCC latest version, I personaly use GCC 2.8.1 on SUN, and egcs-1.0.3
under Linux (note that the same STL code compile with GCC and Visual
C++, this is too seldom seen to be unnoticed!). 

Outline Description of Program
==============================
The program convert the word to a phonologic representation thanks to
a decision tree or an exception dictionary. It applies then language
dependent rules to generate a "dictionary-like" prosody, then it calls
the Mbrola synthesizer with MBR_Play DLL, or the mbrola binary. 

Recent feature in the dictionary: you can now indicate a grammatical
tag giving the nature of the word so that we can disambiguate
heterophone / homographs -> the decision tree can then take this tag
into account during the learning procedure (* actually the GNU ID3
implementation we provide with Kevin Lenzo handles Part of Speech, so
this point is a piece of cake... the only problem is to find a
dictionary providing such tags: CMU does not :-( So don't expect
"record" to be correctly pronounced *), on the contrary OALD does.

Ok, mbrdico was primarily intended for isolated words, though it will
successfully utter in French :

	les poules du \NVERB couvent \VERB couvent 

The escape sequence '\' indicate that the following must be passed as
a tag for the next word. In the above example "\NVERB couvent"
indicate that the word is not a verb (actually a noun pronounced
[kuva~]) and "\VERB couvent" indicate a verb (pronounced [kuv]). The
convention chosen here are purely at your convenience and depend on
the choice you've made during the training phase with ID3 (cf
above). Actually for French, the distinction VERB and NON VERB is
generally enough to remove ambiguities.

Hacking the sources
===================
1) Architecture independent part of the Program is in the SRC
    directory:

    SRC/Engine: prosody generation
    SRC/Letter2Phone: letter to sound convertion
    SRC/PhoFile: structure for handling phoneme, accents, pitch
          points ... 
    SRC/VisualC++ -> the project for Visual.
    SRC/UNIX   -> the main file for UNIX platforms

You can develop new languages by deriving a new heir from the
Speak.cpp class and define symbolic accentuation rules, and prosodic
parameter generation. At the moment the special character '1' has been
used to indicate lexical stress. If you need more diacritics using '0'
and '1' sounds sensible... Please don't use '4' as it  may be confused
with the X-SAMPA representation of the flapped t, and '2' is a SAMPA
rounded [e].

Algorithm of the talking dictionary
====================================
sub MAIN
  0) downcase letter and tranform separators into '-'
  1) Substrings= split against - / .  ( like in x-ray ac/dc I.B.M )
  2) foreach $i (Substrings) Transcription+=graphon($i)
  3) tones-to-f0(Transcription)

sub GRAPHON(Grapheme)
  1) if (Solution=exception_dictionary(Grapheme) 
      return Solution
   else 
  2)    Solution=apply_rule(Grapheme)
  7) return Solution

The rules are encoded in a decision tree... generating an "if then
else" binary was too huge for many compilers to handle (deeply
imbricated code needed for the CMU American dictionary is a nightmare
for GCC and Visual C++ and a warranty for a aching core dump and
curses from your colleagues working on the same machine as you). The
problem here is to prevent optimization of if-then-else structures,
though doing so the resulting tree occupies 7Mb for English. The
human-readble tree encoded in .tree files is an acceptable and
portable compromise at the moment, though I wait for your propositions
and patches.

The tone-to-f0 rules depends on the zscore file, which can of course
be fine-tuned. A crude set of prosodic diacritics are used, ':' for
lengthening, '>' for final  downstepping, '0' for French secondary
accent.

Possible enhancements
=====================
Many !!!

Todo: include morphological rules in the algorithm above (the decision
tree can use morphological boundary tags for example), add a tagger,
and a fix-it-yourself Text-to-Speech. The EULER project developped at
the TCTS lab will put shortly that spare code into a more general
(multi-lingual) frame. 

I've got another new-born (yep a real one, tiny hands and pretty
smile!) to care for, so I cowardly leave above mentionned developments
as an exercise to the reader. 

Acknowledgements
================

Thanks to:

   * Kevin Lenzo (CMU) for his amazing Perl implementation of the ID3
     algorithm and research that introduced me to the field and
     initiated this project

   * Alan Black (CSTR) for his help in testing different letter to
     phoneme + stress strategies, his impressive WAGON toolkit, and
     for his popular Festival Text to Speech synthesizer

   * Nawfal Tounsi (FPMS) for providing an Arabic system

   * Fabrice Malfrere (FPMS) for providing a Spanish and Dutch
     system

   * Richard Beaufort (DEC2 student) who heavily corrected our French
     phonetic dictionary thanks to his welcome linguistics knowledge.

   * Michel Bagein and Alain Ruelle (FPMS) for helping with C++/STL
     and Visual C++.

	* Philippe Devallois for spotting bugs !

Bugs
====

Doubtless a lot :-)

			 Have fun

					 Vincent PAGEL ( http://tcts.fpms.ac.be/~pagel )
------------------------------------------------------------------------------
Vincent PAGEL               Labo. Traitement du Signal et Theorie des Circuits
email: pagel@tcts.fpms.ac.be                     Faculte Polytechnique de Mons
tel: /32/65/374133  fax:374129             31, bvd Dolez, B-7000 Mons, Belgium
