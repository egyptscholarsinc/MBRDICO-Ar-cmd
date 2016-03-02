#if !defined(AFX_LOADING_H__367BDA81_C041_11D2_834B_0020AFB6E89F__INCLUDED_)
#define AFX_LOADING_H__367BDA81_C041_11D2_834B_0020AFB6E89F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Loading.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoading dialog

class CLoading : public CDialog
{
// Construction
public:
	CLoading(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoading)
	enum { IDD = IDD_LOADING };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoading)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoading)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADING_H__367BDA81_C041_11D2_834B_0020AFB6E89F__INCLUDED_)
