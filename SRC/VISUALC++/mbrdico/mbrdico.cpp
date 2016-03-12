// mbrdico.cpp : Defines the class behaviors for the application.
// Updated by Amr on 17/2/2016 to convert it to Console application
//

#include "stdafx.h"
#include "mbrdico.h"
#include "Txt2Speech.hpp"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMbrdicoApp

BEGIN_MESSAGE_MAP(CMbrdicoApp, CWinApp)
	//{{AFX_MSG_MAP(CMbrdicoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMbrdicoApp construction

CMbrdicoApp::CMbrdicoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMbrdicoApp object

CMbrdicoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMbrdicoApp initialization

BOOL CMbrdicoApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif



	// This part is copied from the removed mbrdicoDlg dialog class to intialiaze
	// mbrdico and convert it from Windows to Console application

	CString tmp=GetCommandLine();
	
	// Eventual correction if the path include a space
	if (tmp[0]==34)
		tmp=tmp.Mid(1); 
	tmp.MakeUpper();

	// Name of the binary
	CString fname=AfxGetApp()->m_pszExeName;
	fname+=".exe";
	fname.MakeUpper();
	
	// pos gives the size of the prelude path
	int pos=tmp.Find(fname); 
	char path_mask[_MAX_PATH]="";  // to get the language .ini files
	if (pos>=0)
	{
		memcpy(path_mask,LPCTSTR(tmp),pos);
		path_mask[pos]=0; 
	}

	// IMPORTANT: the path to data .tree .zs and so on are generally relative
	SetCurrentDirectory(path_mask);
	
	// Find all available languages in the directory
	strcat(path_mask,"*.ini");
	WIN32_FIND_DATA my_dir;
	HANDLE my_handle=FindFirstFile(path_mask,&my_dir);
	BOOL go=(my_handle!=NULL);
	// ~ruelle

	//reading from file instead *************************** ////////////////////////
	// This part of calling utter() is copied from the OK() part in the removed dialog
	ifstream myfile;
    myfile.open(__argv[1]); //TODO: check errors & handle exceptions
    string output;
    while(getline(myfile, output))
	{
		//cout << output << endl;
		string transliterated = transliterate(output);
		// Vincent
        //UpdateData(TRUE);   // Fill the member variables
        tts.utter(transliterated.c_str(), "arabic", 0, __argv[2]); //TODO: remove hard-coded file name
        // ~Vincent
	}
    myfile.close();
	//reading from file instead **********END************** ////////////////////////
	// ----------------------------------------- //

	return FALSE;
	
}

string CMbrdicoApp::transliterate(string txt)
{
	string transliterated;
	for(int i=0; i<txt.length(); i++)
	{
		switch (txt.at(i))
		{
			case '�': transliterated.append("b"); break;
			case '�': transliterated.append("t"); break;
			case '�': transliterated.append("T"); break;
			case '�': transliterated.append("Z"); break;
			case '�': transliterated.append("X"); break;
			case '�': transliterated.append("x"); break;
			case '�': transliterated.append("d"); break;
			case '�': transliterated.append("D"); break;
			case '�': transliterated.append("r"); break;
			case '�': transliterated.append("z"); break;
			case '�': transliterated.append("s"); break;
			case '�': transliterated.append("S"); break;
			case '�': transliterated.append("s."); break;
			case '�': transliterated.append("d."); break;
			case '�': transliterated.append("t."); break;
			case '�': transliterated.append("z."); break;
			case '�': transliterated.append("H"); break;
			case '�': transliterated.append("G"); break;
			case '�': transliterated.append("f"); break;
			case '�': transliterated.append("q"); break;
			case '�': transliterated.append("k"); break;
			case '�': transliterated.append("l"); break;
			case '�': transliterated.append("m"); break;
			case '�': transliterated.append("n"); break;
			case '�': transliterated.append("h"); break;
			case '�': 
				if(i>0 && txt.at(i-1)=='�')
					transliterated.append("uu");	//mad
				else
					transliterated.append("w");		//waw
				break;
			case '�': 
				if(i>0 && txt.at(i-1)=='�')
					transliterated.append("ii");	//mad
				else
					transliterated.append("j");		//ya2
				break;
			case '�': 
				if(i>0 && txt.at(i-1)=='�')
					transliterated.append("aa");	//mad
				else
					transliterated.append("a");		//alef
				break;
			case '�': transliterated.append("?"); break;
			case '�': transliterated.append("?"); break;
			case '�': transliterated.append("?"); break;
			case '�': transliterated.append("?"); break;
			case '�': transliterated.append("?"); break;
			case '�': transliterated.append("?aa"); break;
			case '�': transliterated.append("a"); break;
			case '�': transliterated.append("i"); break;
			case '�': transliterated.append("u"); break;
			case '�': transliterated.append("un"); break;
			case '�': transliterated.append("in"); break;
			case '�': transliterated.append("an"); break;
			case '�': transliterated.append(""); break;
			case '�': transliterated.append("t"); break;
			case '�':
				if(i>0)
					transliterated.append(transliterate(txt.substr(i-1,1)));
				break;
			default: transliterated.append("_"); break;
		}
	}
	return transliterated;
}
