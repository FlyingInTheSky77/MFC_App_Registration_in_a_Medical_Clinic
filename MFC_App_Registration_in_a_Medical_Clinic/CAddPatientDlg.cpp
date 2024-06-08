// CAddPatientDlg.cpp : implementation file
//

#include "pch.h"
#include "MFC_App_Registration_in_a_Medical_Clinic.h"
#include "afxdialogex.h"
#include "CAddPatientDlg.h"

#include "sqlite3.h"

// CAddPatientDlg dialog

IMPLEMENT_DYNAMIC(CAddPatientDlg, CDialogEx)

CAddPatientDlg::CAddPatientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_PATIENT, pParent)
{
}

CAddPatientDlg::~CAddPatientDlg()
{
}

void CAddPatientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADD_PATIENT_NAME, mEdit_name);
	DDX_Control(pDX, IDC_ADD_PATIENT_GENDER, mComboBox_gender);
	DDX_Control(pDX, IDC_ADD_PATIENT_AGE, mEdit_age);
}


BEGIN_MESSAGE_MAP(CAddPatientDlg, CDialogEx)
	ON_BN_CLICKED(ID_SAVE, &CAddPatientDlg::OnBnClickedSave)
END_MESSAGE_MAP()

BOOL CAddPatientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mComboBox_gender.AddString(_T("male"));
	mComboBox_gender.AddString(_T("female"));

	return TRUE;
}

void CAddPatientDlg::OnBnClickedSave()
{
	CString strName;
	mEdit_name.GetWindowText(strName); // Get the text from the CEdit control

	// Check if name isn't selected
	if (strName.IsEmpty())
	{
		AfxMessageBox(_T("Enter name"));
		return; // Exit the function to prevent further processing
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

	// Check if age isn't selected
	if (strAge.IsEmpty())
	{
		AfxMessageBox(_T("Enter age"));
		return;
	}

	// Prepare SQL insert statement
	CString sql;
	sql.Format(_T("INSERT INTO Patients (name, gender, age) VALUES ('%s', '%s', '%s');"),
		strName, strGender, strAge);

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
