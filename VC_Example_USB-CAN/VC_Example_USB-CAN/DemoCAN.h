// DemoCAN.h : main header file for the DEMOCAN application
//

#if !defined(AFX_DEMOCAN_H__85B498FA_2E86_4A57_ADE4_B8AF05D68A9F__INCLUDED_)
#define AFX_DEMOCAN_H__85B498FA_2E86_4A57_ADE4_B8AF05D68A9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDemoCANApp:
// See DemoCAN.cpp for the implementation of this class
//

class CDemoCANApp : public CWinApp
{
public:
	CDemoCANApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoCANApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDemoCANApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOCAN_H__85B498FA_2E86_4A57_ADE4_B8AF05D68A9F__INCLUDED_)
