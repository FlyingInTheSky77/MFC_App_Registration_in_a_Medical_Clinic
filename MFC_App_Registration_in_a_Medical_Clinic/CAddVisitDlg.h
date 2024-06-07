#pragma once
#include "afxdialogex.h"


// CAddVisitDlg dialog

class CAddVisitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddVisitDlg)

public:
	CAddVisitDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAddVisitDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_VISIT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	/*CString m_visitDate;
	CString m_doctor;
	CString m_patient;
	CString m_comment;*/


public: // private?
	//afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeAddVisitDlg();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();

	CEdit m_Edit1;
	CEdit m_Edit2;
	//CComboBox m_ComboBox1;
	CComboBox m_ComboBox2;
};
