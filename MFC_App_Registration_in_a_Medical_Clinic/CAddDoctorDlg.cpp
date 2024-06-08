// CAddDoctorDlg.cpp : implementation file
//

#include "pch.h"
#include "MFC_App_Registration_in_a_Medical_Clinic.h"
#include "afxdialogex.h"
#include "CAddDoctorDlg.h"

#include "sqlite3.h"


// CAddDoctorDlg dialog

IMPLEMENT_DYNAMIC(CAddDoctorDlg, CDialogEx)

CAddDoctorDlg::CAddDoctorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_DOCTOR, pParent)
{
}

CAddDoctorDlg::~CAddDoctorDlg()
{
}

void CAddDoctorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADD_DOCTOR_NAME, mEdit_name);
	DDX_Control(pDX, IDC_ADD_DOCTOR_POSITION, mEdit_position);
	DDX_Control(pDX, IDC_ADD_DOCTOR_SPECIALIZATION, mEdit_specialization);
	DDX_Control(pDX, IDC_ADD_DOCTOR_GEDER, mComboBox_gender);
	DDX_Control(pDX, IDC_ADD_DOCTOR_AGE, mEdit_age);
	DDX_Control(pDX, IDC_ADD_DOCTOR_SCHEDULE, mEdit_schedule);
}

BEGIN_MESSAGE_MAP(CAddDoctorDlg, CDialogEx)
	ON_BN_CLICKED(ID_SAVE, &CAddDoctorDlg::OnBnClickedOk)	
END_MESSAGE_MAP()


// CAddDoctorDlg message handlers

BOOL CAddDoctorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mComboBox_gender.AddString(_T("male"));
	mComboBox_gender.AddString(_T("female"));

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CAddDoctorDlg::OnBnClickedOk()
{
	CString strName;
	mEdit_name.GetWindowText(strName); // Get the text from the CEdit control
	
	// Check if a doctor is selected
	if (strName.IsEmpty())
	{
		AfxMessageBox(_T("Enter name"));
		return; // Exit the function to prevent further processing
	}
	
	CString strPosition;
	mEdit_position.GetWindowText(strPosition);

	// Check if a position isn't selected
	if (strPosition.IsEmpty())
	{
		AfxMessageBox(_T("Enter position"));
		return;
	}

	CString strSpecialization;
	mEdit_specialization.GetWindowText(strSpecialization);

	// Check if specialization isn't selected
	if (strSpecialization.IsEmpty())
	{
		AfxMessageBox(_T("Enter specialization"));
		return;
	}

	const int choosen_gender = mComboBox_gender.GetCurSel();
	
	// Check if a gender isn't selected
	if (choosen_gender == CB_ERR)
	{
		AfxMessageBox(_T("Select gender"));
		return;
	}

	CString strGender;
	mComboBox_gender.GetLBText(choosen_gender, strGender);

	CString strAge;
	mEdit_age.GetWindowText(strAge);

	if (strAge.IsEmpty())
	{
		AfxMessageBox(_T("Enter age"));
		return;
	}

	CString strSchedule;
	mEdit_schedule.GetWindowText(strSchedule);

	// Check if specialization isn't selected
	if (strSchedule.IsEmpty())
	{
		AfxMessageBox(_T("Enter schedule"));
		return;
	}

	// Prepare SQL insert statement
	CString sql;
	sql.Format(_T("INSERT INTO Doctors (name, position, specialization, gender, age, shedule) VALUES ('%s', '%s', '%s', '%s', '%s', '%s');"),
		strName, strPosition, strSpecialization, strGender, strAge, strSchedule);

	// Open the SQLite database
	sqlite3* db;
	int rc = sqlite3_open("../../example.db", &db);
	if (rc)
	{
		AfxMessageBox(_T("Can't open database"));
		return;
	}

	// Execute SQL insert statement
	char* errMsg = nullptr;
	rc = sqlite3_exec(db, CT2A(sql), nullptr, nullptr, &errMsg);
	if (rc != SQLITE_OK)
	{
		CString errorMsg = CString("SQL error: ") + CString(errMsg);
		AfxMessageBox(errorMsg);
		sqlite3_free(errMsg);
		sqlite3_close(db);
		return;
	}

	// Close the SQLite database
	sqlite3_close(db);

	CDialogEx::OnOK();
}
