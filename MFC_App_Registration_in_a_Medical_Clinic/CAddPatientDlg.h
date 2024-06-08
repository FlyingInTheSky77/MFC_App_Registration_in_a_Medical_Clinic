#pragma once
#include "afxdialogex.h"

class CAddPatientDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddPatientDlg)

public:
	CAddPatientDlg(CWnd* pParent = nullptr);
	virtual ~CAddPatientDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_PATIENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();

private:
	CEdit mEdit_name;
	CComboBox mComboBox_gender;
	CEdit mEdit_age;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSave();
};
