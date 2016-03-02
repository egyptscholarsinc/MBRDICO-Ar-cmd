// mbrdico.h : main header file for the MBRDICO application
//

#if !defined(AFX_MBRDICO_H__C236D5E4_B201_11D2_8349_0020AFB6E89F__INCLUDED_)
#define AFX_MBRDICO_H__C236D5E4_B201_11D2_8349_0020AFB6E89F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMbrdicoApp:
// See mbrdico.cpp for the implementation of this class
//

class CMbrdicoApp : public CWinApp
{
public:
	CMbrdicoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMbrdicoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMbrdicoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MBRDICO_H__C236D5E4_B201_11D2_8349_0020AFB6E89F__INCLUDED_)
