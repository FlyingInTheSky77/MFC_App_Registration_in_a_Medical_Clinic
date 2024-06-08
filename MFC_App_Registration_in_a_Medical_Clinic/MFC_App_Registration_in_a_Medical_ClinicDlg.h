
#pragma once

#include "sqlite3.h"
#pragma comment(lib, "sqlite3.lib")

// CMFCAppRegistrationinaMedicalClinicDlg dialog
class CMFCAppRegistrationinaMedicalClinicDlg : public CDialogEx
{
// Construction
public:
	CMFCAppRegistrationinaMedicalClinicDlg(CWnd* pParent = nullptr);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_APP_REGISTRATION_IN_A_MEDICAL_CLINIC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);

	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	
private:
	BOOL InitializeDatabase(sqlite3*& db);
	void LoadDataFromDatabase(sqlite3* db, CListCtrl& listCtrl);

	void fillVisitsList();
	void fillDoctorsList();
	void fillPatientsList();

	void ClearListCtrlColumns();

	void createrVisitsTableHeader();
	void createrDoctorsTableHeader();
	void createrPatientsTableHeader();

	CListCtrl m_listCtrl;

	enum class ViewType
	{
		Visits,
		Doctors,
		Patients
	};

	ViewType m_currentView;

	void OpenAddVisitDialog();
	void OpenAddDoctorDialog();
	void OpenAddPatientDialog();

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton4();
};
