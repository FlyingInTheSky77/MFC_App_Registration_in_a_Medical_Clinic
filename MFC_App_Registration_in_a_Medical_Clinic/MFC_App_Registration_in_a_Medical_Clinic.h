
// MFC_App_Registration_in_a_Medical_Clinic.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

class CMFCAppRegistrationinaMedicalClinicApp : public CWinApp
{
public:
	CMFCAppRegistrationinaMedicalClinicApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCAppRegistrationinaMedicalClinicApp theApp;
