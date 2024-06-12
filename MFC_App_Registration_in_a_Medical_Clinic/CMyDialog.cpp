// CMyDialog.cpp : implementation file
//

#include "pch.h"
#include "MFC_App_Registration_in_a_Medical_Clinic.h"
#include "afxdialogex.h"
#include "CMyDialog.h"

#include "sqlite3.h"

// CMyDialog dialog

IMPLEMENT_DYNAMIC(CMyDialog, CDialogEx)

CMyDialog::CMyDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYDIALOG, pParent)
{
}

CMyDialog::~CMyDialog()
{
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ADD_DOCTOR_DOCTOR, m_ComboBox_add_doctor);
    DDX_Control(pDX, IDC_COMBO_ADD_DOCTOR_PATIENT, m_ComboBox_add_patient);
    DDX_Control(pDX, IDC_EDIT__ADD_DOCTOR_SCHEDULE, mEdit_doctors_schedule);
    DDX_Control(pDX, IDC_DATE, mDateTimeCtrl_Date);
    DDX_Control(pDX, IDC_TIME, mDateTimeCtrl_Time);
    DDX_Control(pDX, IDC_EDIT_ADD_DOCTOR_COMMENT, mEdit_comment);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialogEx)
    ON_BN_CLICKED(IDOK, &CMyDialog::OnBnClickedOk)
    ON_CBN_SELCHANGE(IDC_COMBO_ADD_DOCTOR_DOCTOR, &CMyDialog::OnCbnSelchangeComboAddDoctorDoctor)
END_MESSAGE_MAP()

BOOL CMyDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    LoadDoctorNamesFromDB();
    LoadPatientsFromDB();

    mEdit_doctors_schedule.SetReadOnly(TRUE);    

    // Set the time control format to exclude seconds
    //mDateTimeCtrl_Date.SetFormat(_T("yyyy-MM-dd"));
    mDateTimeCtrl_Time.SetFormat(_T("HH:mm"));

    // Set the initial date and time
    COleDateTime currentDate = COleDateTime::GetCurrentTime();
    mDateTimeCtrl_Time.SetTime(currentDate);
    mDateTimeCtrl_Date.SetTime(currentDate);

    return TRUE;
}

void CMyDialog::LoadDoctorNamesFromDB()
{
    sqlite3* db;
    sqlite3_stmt* stmt;

    int rc = sqlite3_open("../../example.db", &db);
    if (rc)
    {
        AfxMessageBox(_T("Error opening database!"));
        return;
    }

    const char* sql = "SELECT id, name FROM Doctors;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        AfxMessageBox(_T("Error preparing SQL statement!"));
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int index_db = sqlite3_column_int(stmt, 0);
        const char* doctorName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        CString doctorNameStr(doctorName);
        int index_combobox = m_ComboBox_add_doctor.AddString(doctorNameStr);
        m_ComboBox_add_doctor.SetItemData(index_combobox, index_db);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void CMyDialog::LoadPatientsFromDB()
{
    sqlite3* db;
    sqlite3_stmt* stmt;

    int rc = sqlite3_open("../../example.db", &db);
    if (rc)
    {
        AfxMessageBox(_T("Error opening database!"));
        return;
    }

    const char* sql = "SELECT id, name FROM Patients;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        AfxMessageBox(_T("Error preparing SQL statementа!"));
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int index_db = sqlite3_column_int(stmt, 0);
        const char* patient_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        CString patient_name_Str(patient_name);
        int index_combobox = m_ComboBox_add_patient.AddString(patient_name_Str);
        m_ComboBox_add_patient.SetItemData(index_combobox, index_db);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void CMyDialog::OnCbnSelchangeComboAddDoctorDoctor()
{
    int selIndex = m_ComboBox_add_doctor.GetCurSel();
    if (selIndex != CB_ERR)
    {
        CString doctorName;
        m_ComboBox_add_doctor.GetLBText(selIndex, doctorName);
        
        // Load and display the doctor details
        LoadDoctorDetailsFromDB(doctorName);
    }
}

void CMyDialog::LoadDoctorDetailsFromDB(const CString& doctorName)
{
    sqlite3* db;
    sqlite3_stmt* stmt;

    // Open the database
    int rc = sqlite3_open("../../example.db", &db);
    if (rc)
    {
        AfxMessageBox(_T("Error opening database!"));
        return;
    }

    // Prepare the SQL query to select doctor details
    CStringA doctorNameA(doctorName); // Convert CString to CStringA
    CStringA sqlA;
    sqlA.Format("SELECT shedule FROM Doctors WHERE name = '%s';", doctorNameA);

    rc = sqlite3_prepare_v2(db, sqlA, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        AfxMessageBox(_T("Error preparing SQL statement!"));
        sqlite3_close(db);
        return;
    }

    // Execute the query and get the details
    CString doctor_schedule;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char* schedule = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        doctor_schedule = CString(schedule);
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // Display the details in the Edit control
   mEdit_doctors_schedule.SetWindowText(doctor_schedule);
}


void CMyDialog::OnBnClickedOk()
{
    // Check if a doctor is selected
    if (m_ComboBox_add_doctor.GetCurSel() == CB_ERR)
    {
        AfxMessageBox(_T("Select a doctor or press Cancel"));
        return;
    }

    // Check if a patient is selected
    if (m_ComboBox_add_patient.GetCurSel() == CB_ERR)
    {
        AfxMessageBox(_T("Select a patient or press Cancel"));
        return;
    }
   
    COleDateTime date;
    COleDateTime time;

    CString strOnlyDate;
    CString strTime;

    COleDateTime dtSelected;
    DWORD dwResult = mDateTimeCtrl_Date.GetTime(dtSelected);
    if (dwResult == GDT_VALID && dtSelected.GetStatus() == COleDateTime::valid)
    {
        AfxMessageBox(_T("Invalid date: " + mDateTimeCtrl_Date.GetTime(date)));
        return;
    }

    COleDateTime dtSelected2;
    DWORD dwResult2 = mDateTimeCtrl_Date.GetTime(dtSelected2);
    if (dwResult2 == GDT_VALID && dtSelected2.GetStatus() == COleDateTime::valid)
    {
        AfxMessageBox(_T("Invalid time"));
        return;
    }

    mDateTimeCtrl_Time.GetTime(time); // set time from "mDateTimeCtrl_Time" to "time"
    mDateTimeCtrl_Date.GetTime(date); // set date from "mDateTimeCtrl_Date" to "date"

    // Format date and time separately
    strOnlyDate = date.Format(_T("%m-%d-%Y"));
    strTime = time.Format(_T("%H:%M"));

    CString strComment;
    mEdit_comment.GetWindowText(strComment);

    // Check if a doctor is selected
    if (m_ComboBox_add_doctor.GetCurSel() == CB_ERR)
    {
        AfxMessageBox(_T("Select a doctor or press Cancel"));
        return;
    }

    // TODO: check in future: do we need these two line below ?
    // Get selected doctor and patient names
    CString strDoctor, strPatient;
    m_ComboBox_add_doctor.GetLBText(m_ComboBox_add_doctor.GetCurSel(), strDoctor);
    m_ComboBox_add_patient.GetLBText(m_ComboBox_add_patient.GetCurSel(), strPatient);

    // Open the SQLite database
    sqlite3* db;
    int rc = sqlite3_open("../../example.db", &db);
    if (rc)
    {
        AfxMessageBox(_T("Can't open database"));
        return;
    }

    // Get selected doctor and patient IDs
    int doctor_combo_index = m_ComboBox_add_doctor.GetCurSel();
    int patient_combo_index = m_ComboBox_add_patient.GetCurSel();

    // Get the associated data (doctor ID)
    int doctor_id = m_ComboBox_add_doctor.GetItemData(doctor_combo_index);
    int patient_id = m_ComboBox_add_patient.GetItemData(doctor_combo_index);

    // Prepare SQL insert statement
    CString sql;
    sql.Format(_T("INSERT INTO Visits (visit_date, visit_time, doctor_id, patient_id, comment) VALUES ('%s', '%s', '%d', '%d', '%s');"),
        strOnlyDate, strTime, doctor_id, patient_id, strComment);

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
