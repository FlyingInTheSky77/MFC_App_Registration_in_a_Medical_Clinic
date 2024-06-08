#pragma once
#include "afxdialogex.h"

class CAddDoctorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddDoctorDlg)

public:
	CAddDoctorDlg(CWnd* pParent = nullptr);
	virtual ~CAddDoctorDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_DOCTOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();

private:
	CEdit mEdit_name;
	CEdit mEdit_position;
	CEdit mEdit_specialization;
	CComboBox mComboBox_gender;
	CEdit mEdit_age;
	CEdit mEdit_schedule;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
