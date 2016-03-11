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
		string translierated = translierate(output);
		// Vincent
        //UpdateData(TRUE);   // Fill the member variables
        tts.utter(translierated.c_str(), "arabic", 0, __argv[2]); //TODO: remove hard-coded file name
        // ~Vincent
	}
    myfile.close();
	//reading from file instead **********END************** ////////////////////////
	// ----------------------------------------- //

	return FALSE;
	
}

string CMbrdicoApp::translierate(string txt)
{
	string translierated;
	for(int i=0; i<txt.length(); i++)
	{
		switch (txt.at(i))
		{
			case '�': translierated.append("b"); break;
			case '�': translierated.append("t"); break;
			case '�': translierated.append("T"); break;
			case '�': translierated.append("Z"); break;
			case '�': translierated.append("X"); break;
			case '�': translierated.append("x"); break;
			case '�': translierated.append("d"); break;
			case '�': translierated.append("D"); break;
			case '�': translierated.append("r"); break;
			case '�': translierated.append("z"); break;
			case '�': translierated.append("s"); break;
			case '�': translierated.append("S"); break;
			case '�': translierated.append("s."); break;
			case '�': translierated.append("d."); break;
			case '�': translierated.append("t."); break;
			case '�': translierated.append("z."); break;
			case '�': translierated.append("H"); break;
			case '�': translierated.append("G"); break;
			case '�': translierated.append("f"); break;
			case '�': translierated.append("q"); break;
			case '�': translierated.append("k"); break;
			case '�': translierated.append("l"); break;
			case '�': translierated.append("m"); break;
			case '�': translierated.append("n"); break;
			case '�': translierated.append("h"); break;
			case '�': translierated.append("w"); break;
			case '�': translierated.append("j"); break;
			case '�': translierated.append("?"); break;
			case '�': translierated.append("?"); break;
			case '�': translierated.append("?"); break;
			case '�': translierated.append("?"); break;
			case '�': translierated.append("?aa"); break;
			case '�': translierated.append("a"); break;
			case '�': translierated.append("i"); break;
			case '�': translierated.append("u"); break;
			case '�': translierated.append("un"); break;
			case '�': translierated.append("in"); break;
			case '�': translierated.append("an"); break;
			case '�': translierated.append(""); break;
			case '�': translierated.append("a"); break;
			case '�': translierated.append("t"); break;
			default: translierated.append("_"); break;
		}
	}
	return translierated;
}
