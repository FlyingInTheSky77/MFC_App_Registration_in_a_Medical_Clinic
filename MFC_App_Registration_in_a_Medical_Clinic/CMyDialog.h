#pragma once
#include "afxdialogex.h"

#include "MFC_App_Registration_in_a_Medical_ClinicDlg.h"

class CMyDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialog)

public:
	CMyDialog(CMFCAppRegistrationinaMedicalClinicDlg* pParentDlg, CWnd* pParent = nullptr);
	virtual ~CMyDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

private:
	CComboBox m_ComboBox_add_doctor;
	CComboBox m_ComboBox_add_patient;
	CEdit mEdit_doctors_schedule;
	CDateTimeCtrl mDateTimeCtrl_Time;
	CDateTimeCtrl mDateTimeCtrl_Date;
	CEdit mEdit_comment;

	void LoadDoctorNamesFromDB();
	void LoadPatientsFromDB();

	void LoadDoctorDetailsFromDB(const CString& doctorName);

	DECLARE_MESSAGE_MAP()

	CMFCAppRegistrationinaMedicalClinicDlg* m_pParentDlg;

public:	
	afx_msg void OnBnClickedOk();
	void OnCbnSelchangeComboAddDoctorDoctor();
};
