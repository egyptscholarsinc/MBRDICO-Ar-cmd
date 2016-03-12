# MBRDICO-Ar-cmd
This project converts the GUI-based MBRDICO projrct available here http://tcts.fpms.ac.be/synthesis/mbrdico/ to a command-line utility with the aim to build an Arabic TTS for the blind by Momken team using MBROLA.

The updates affect only the VisualC++ version and include removing the MFC forms and taking command line arguments instead.

The project assuems the Arabic dictionary databse by default, so it's not passed as an argument.

To run the executable, make sure arabic.ini is in the same path of the exe, and dictionary files are in ../Data folder.

Prerequisites: MBROLA must be installed first along with the Arabic database, both are available here:
http://www.tcts.fpms.ac.be/synthesis/mbrola/mbrcopybin.html

Arguments: input.txt file with transilitrated Arabic phonemes to be spoken + optional out.wav file

Output: speech played by MBROLA (+ the optinal played audio saved to a wave file)
