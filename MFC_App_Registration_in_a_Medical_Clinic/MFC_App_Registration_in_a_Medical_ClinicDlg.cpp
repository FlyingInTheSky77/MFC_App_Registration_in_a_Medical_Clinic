
// MFC_App_Registration_in_a_Medical_ClinicDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFC_App_Registration_in_a_Medical_Clinic.h"
#include "MFC_App_Registration_in_a_Medical_ClinicDlg.h"
#include "afxdialogex.h"

#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCAppRegistrationinaMedicalClinicDlg dialog

CMFCAppRegistrationinaMedicalClinicDlg::CMFCAppRegistrationinaMedicalClinicDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_APP_REGISTRATION_IN_A_MEDICAL_CLINIC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCAppRegistrationinaMedicalClinicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCAppRegistrationinaMedicalClinicDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMFCAppRegistrationinaMedicalClinicDlg::OnLvnItemchangeLIST1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCAppRegistrationinaMedicalClinicDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCAppRegistrationinaMedicalClinicDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCAppRegistrationinaMedicalClinicDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDCANCEL, &CMFCAppRegistrationinaMedicalClinicDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CMFCAppRegistrationinaMedicalClinicDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCAppRegistrationinaMedicalClinicDlg::OnBnClickedButton4)
END_MESSAGE_MAP()

void CMFCAppRegistrationinaMedicalClinicDlg::OnLvnItemchangeLIST1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// Your code for handling list item change
	*pResult = 0;
}

// CMFCAppRegistrationinaMedicalClinicDlg message handlers

BOOL CMFCAppRegistrationinaMedicalClinicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	sqlite3* db = nullptr;
	if (InitializeDatabase(db))
	{
		LoadDataFromDatabase(db, m_listCtrl);
	}

	// Closing a database connection
	sqlite3_close(db);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void checkTableIfExistAndCreateIfNot(const char* table)
{

}

BOOL CMFCAppRegistrationinaMedicalClinicDlg::InitializeDatabase(sqlite3*& db)
{
	// Opening a new database connection
	int rc = sqlite3_open("../../example.db", &db);
	if (rc)
	{
		AfxMessageBox(CString("Can't open database: ") + sqlite3_errmsg(db));
		return false;
	}

	const char* sqlCheckTable = "SELECT Name FROM sqlite_master WHERE type='table' AND name='Doctors';";
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(db, sqlCheckTable, -1, &stmt, nullptr);
	if (rc != SQLITE_OK)
	{
		AfxMessageBox(CString("SQL error: ") + sqlite3_errmsg(db));
		return false;
	}
	rc = sqlite3_step(stmt);
	bool tableDoctorsExists = (rc == SQLITE_ROW);
	sqlite3_finalize(stmt);

	// Create the table if it does not exist
	if (!tableDoctorsExists)
	{
		const char* sqlCreateTableDoctors = "CREATE TABLE IF NOT EXISTS Doctors ("
			"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"Name TEXT NOT NULL,"
			"Position TEXT NOT NULL,"
			"Specialization TEXT NOT NULL,"
			"Gender TEXT NOT NULL,"
			"Age INTEGER,"
			"Shedule TEXT NOT NULL);";

		char* errMsg = nullptr;
		rc = sqlite3_exec(db, sqlCreateTableDoctors, nullptr, nullptr, &errMsg);
		if (rc != SQLITE_OK)
		{
			AfxMessageBox(CString("SQL error: ") + errMsg);
			sqlite3_free(errMsg);
			return false;
		}

		// Insert initial data in Doctors table
		
		const char* insertSQLDoctors = "INSERT INTO Doctors (Name, Position, Specialization, Gender, Age, Shedule) VALUES "
			"('Alexander Fleming', 'therapist', 'adult therapist', 'male', 40, 'from 9:00 to 13:00 every day'),"
			"('Helen Brooke Taussig', 'dentist', 'dentist', 'female', 33, 'from 14:00 to 18:00 every day'),"
			"('Helene D. Gayle', 'surgeon','general surgeon','female', 40, 'from 14:00 to 18:00 every day'),"
			"('Charles Richard Drew', 'therapist', 'childrens therapist', 'male', 25, 'from 9:00 to 13:00 every day');";

		rc = sqlite3_exec(db, insertSQLDoctors, nullptr, nullptr, &errMsg);
		if (rc != SQLITE_OK)
		{
			AfxMessageBox(CString("SQL error: ") + errMsg);
			sqlite3_free(errMsg);
			return false;
		}
	}

	// Patients
	
	const char* sqlCheckPatientsTable = "SELECT Name FROM sqlite_master WHERE type='table' AND name='Patients';";
	sqlite3_stmt* stmtP;
	rc = sqlite3_prepare_v2(db, sqlCheckPatientsTable, -1, &stmtP, nullptr);
	if (rc != SQLITE_OK)
	{
		AfxMessageBox(CString("SQL error: ") + sqlite3_errmsg(db));
		return false;
	}
	rc = sqlite3_step(stmtP);
	bool tablePatientsExists = (rc == SQLITE_ROW);
	sqlite3_finalize(stmtP);

	// Create the table if it does not exist
	if (!tablePatientsExists)
	{
		const char* sqlCreateTablePatients = "CREATE TABLE IF NOT EXISTS Patients ("
			"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"Name TEXT NOT NULL,"
			"Gender TEXT NOT NULL,"
			"Age INTEGER);";

		char* errMsg = nullptr;
		rc = sqlite3_exec(db, sqlCreateTablePatients, nullptr, nullptr, &errMsg);
		if (rc != SQLITE_OK)
		{
			AfxMessageBox(CString("SQL error: ") + errMsg);
			sqlite3_free(errMsg);
			return false;
		}

		// Insert initial data in Doctors table

		const char* insertSQLPatients = "INSERT INTO Patients (Name, Gender, Age) VALUES "
			"('Elon Musk', 'male', 52),"
			"('Mark Zuckerberg', 'male', 40),"
			"('Elizabeth Olsen', 'female', 35),"
			"('Emily Blunt', 'female', 41);";

		rc = sqlite3_exec(db, insertSQLPatients, nullptr, nullptr, &errMsg);
		if (rc != SQLITE_OK)
		{
			AfxMessageBox(CString("SQL error: ") + errMsg);
			sqlite3_free(errMsg);
			return false;
		}
	}

	// Visits

	const char* sqlCheckVisitsTable = "SELECT Name FROM sqlite_master WHERE type='table' AND name='Visits';";
	sqlite3_stmt* stmtV;
	rc = sqlite3_prepare_v2(db, sqlCheckVisitsTable, -1, &stmtV, nullptr);
	if (rc != SQLITE_OK)
	{
		AfxMessageBox(CString("SQL error: ") + sqlite3_errmsg(db));
		return false;
	}
	rc = sqlite3_step(stmtV);
	bool tableVisitsExists = (rc == SQLITE_ROW);
	sqlite3_finalize(stmtV);

	// Create the table if it does not exist
	if (!tableVisitsExists)
	{
		//AfxMessageBox(CString("table Doctors doen't exist"));
		const char* sqlCreateTableVisits = "CREATE TABLE IF NOT EXISTS Visits ("
			"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"visit_date TEXT NOT NULL,"
			"doctor_id INTEGER NOT NULL,"
			"patient_id INTEGER NOT NULL,"
			"comment TEXT,"
			"FOREIGN KEY (doctor_id) REFERENCES doctors(id),"
			"FOREIGN KEY (patient_id) REFERENCES patients(id));";

		char* errMsg = nullptr;
		rc = sqlite3_exec(db, sqlCreateTableVisits, nullptr, nullptr, &errMsg);
		if (rc != SQLITE_OK)
		{
			AfxMessageBox(CString("SQL error: ") + errMsg);
			sqlite3_free(errMsg);
			return false;
		}

		const char* insertSQLVisits = "INSERT INTO Visits (visit_date, doctor_id, patient_id, comment) VALUES "
			"('06-04-2024', 1, 1, 'Routine check-up'),"
			"('05-04-2024', 2, 4, 'Follow-up visit'),"
			"('04-04-2024', 4, 2, 'Routine check-up'),"
			"('03-04-2024', 3, 3, 'Emergency visit');";

		rc = sqlite3_exec(db, insertSQLVisits, nullptr, nullptr, &errMsg);
		if (rc != SQLITE_OK)
		{
			AfxMessageBox(CString("SQL error: ") + errMsg);
			sqlite3_free(errMsg);
			return false;
		}
	}
	return true;
}

void CMFCAppRegistrationinaMedicalClinicDlg::createrVisitsTableHeader()
{
	m_listCtrl.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 50);
	m_listCtrl.InsertColumn(1, _T("visit_date"), LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, _T("Doctor"), LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, _T("Patient"), LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(4, _T("Comment"), LVCFMT_LEFT, 150);
}

void CMFCAppRegistrationinaMedicalClinicDlg::createrDoctorsTableHeader()
{
	m_listCtrl.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 50);
	m_listCtrl.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, _T("Position"), LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, _T("Specialization"), LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(4, _T("Gender"), LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(5, _T("Age"), LVCFMT_LEFT, 50);
	m_listCtrl.InsertColumn(6, _T("Shedule"), LVCFMT_LEFT, 150);
}
void CMFCAppRegistrationinaMedicalClinicDlg::createrPatientsTableHeader()
{
	m_listCtrl.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 50);
	m_listCtrl.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, _T("Gender"), LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(4, _T("Age"), LVCFMT_LEFT, 50);
}

void CMFCAppRegistrationinaMedicalClinicDlg::LoadDataFromDatabase(sqlite3* db, CListCtrl& listCtrl)
{
	
	// Find the control
	m_listCtrl.SubclassDlgItem(IDC_VISITS_LIST, this);

	// Set ListView style to Report View
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// Setting the LVS_REPORT style to display headers
	m_listCtrl.ModifyStyle(0, LVS_REPORT);

	createrVisitsTableHeader();
	fillVisitsList();
}

void CMFCAppRegistrationinaMedicalClinicDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCAppRegistrationinaMedicalClinicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCAppRegistrationinaMedicalClinicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCAppRegistrationinaMedicalClinicDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CMFCAppRegistrationinaMedicalClinicDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	m_listCtrl.DeleteAllItems();
	ClearListCtrlColumns();
	
	createrVisitsTableHeader();
	fillVisitsList();	
}


void CMFCAppRegistrationinaMedicalClinicDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	m_listCtrl.DeleteAllItems();	
	ClearListCtrlColumns();

	createrPatientsTableHeader();
	fillPatientsList();
	
}

void CMFCAppRegistrationinaMedicalClinicDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	m_listCtrl.DeleteAllItems();
	ClearListCtrlColumns();

	createrDoctorsTableHeader();
	fillDoctorsList();
}

void CMFCAppRegistrationinaMedicalClinicDlg::fillVisitsList()
{

	m_currentView = ViewType::Visits;

	m_listCtrl.DeleteAllItems();

	sqlite3* db;
	char* errMsg = nullptr;

	// Opening a new database connection
	int rc = sqlite3_open("../../example.db", &db);
	if (rc)
	{
		AfxMessageBox(CString("Can't open database: ") + sqlite3_errmsg(db));
		return;
	}

	// Query to retrieve visits with doctor and patient names
	const char* query = "SELECT Visits.id, Visits.visit_date, Doctors.name AS doctor_name, patients.name AS patient_name, visits.comment "
		"FROM Visits "
		"JOIN Doctors ON Visits.doctor_id = doctors.id "
		"JOIN Patients ON Visits.patient_id = patients.id;";

	sqlite3_stmt* stmt;
	if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK)
	{
		int row = 0;
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			int id = sqlite3_column_int(stmt, 0);
			const char* visit_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
			const char* doctor_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
			const char* patient_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
			const char* comment = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

			m_listCtrl.InsertItem(row, std::to_wstring(id).c_str());
			m_listCtrl.SetItemText(row, 1, CA2T(visit_date));
			m_listCtrl.SetItemText(row, 2, CA2T(doctor_name));
			m_listCtrl.SetItemText(row, 3, CA2T(patient_name));
			m_listCtrl.SetItemText(row, 4, CA2T(comment));
			row++;
		}
		sqlite3_finalize(stmt);
	}
}

void CMFCAppRegistrationinaMedicalClinicDlg::fillPatientsList()
{
	m_currentView = ViewType::Patients;
	
	sqlite3* db;
	// Opening a new database connection
	int rc = sqlite3_open("../../example.db", &db);
	if (rc)
	{
		AfxMessageBox(CString("Can't open database: ") + sqlite3_errmsg(db));
		return;
	}

	// Prepare an SQL query for selecting doctors
	const char* sql = "SELECT id, name, gender, age FROM Patients";

	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	if (rc != SQLITE_OK)
	{
		AfxMessageBox(CString("Failed to execute query: ") + sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}

	// Populate the table with data from the database
	int row = 0;
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
	{
		int id = sqlite3_column_int(stmt, 0);
		const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		const char* gender = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		const char* age = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

		m_listCtrl.InsertItem(row, CString(std::to_string(id).c_str()));
		m_listCtrl.SetItemText(row, 1, CString(name));
		m_listCtrl.SetItemText(row, 2, CString(gender));
		m_listCtrl.SetItemText(row, 3, CString(age));
		row++;
	}

	// Free resources and close the database connection
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void CMFCAppRegistrationinaMedicalClinicDlg::fillDoctorsList()
{
	m_currentView = ViewType::Doctors;

	sqlite3* db;
	int rc = sqlite3_open("../../example.db", &db);
	if (rc)
	{
		AfxMessageBox(CString("Can't open database: ") + sqlite3_errmsg(db));
		return;
	}

	const char* sql = "SELECT id, name, position, specialization, gender, age, shedule FROM Doctors";

	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	if (rc != SQLITE_OK)
	{
		AfxMessageBox(CString("Failed to execute query: ") + sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}

	int row = 0;
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
	{
		int id = sqlite3_column_int(stmt, 0);
		const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		const char* position = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		const char* specialization = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
		const char* gender = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
		const char* age = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
		const char* shedule = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));

		m_listCtrl.InsertItem(row, CString(std::to_string(id).c_str()));
		m_listCtrl.SetItemText(row, 1, CString(name));
		m_listCtrl.SetItemText(row, 2, CString(position));
		m_listCtrl.SetItemText(row, 3, CString(specialization));
		m_listCtrl.SetItemText(row, 4, CString(gender));
		m_listCtrl.SetItemText(row, 5, CString(age));
		m_listCtrl.SetItemText(row, 6, CString(shedule));
		row++;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void CMFCAppRegistrationinaMedicalClinicDlg::ClearListCtrlColumns()
{
	// Get the number of columns in the list control
	int columnCount = m_listCtrl.GetHeaderCtrl()->GetItemCount();

	// Delete each column from the last to the first. this order is important
	if (columnCount > 0) {
		for (int8_t i = columnCount - 1; i >= 0; i--)
		{
			m_listCtrl.DeleteColumn(i);
		}
	}
}


void CMFCAppRegistrationinaMedicalClinicDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCAppRegistrationinaMedicalClinicDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CMFCAppRegistrationinaMedicalClinicDlg::OnBnClickedButton4()
{
	switch (m_currentView)
	{
	case ViewType::Visits:
		OpenAddVisitDialog();
		break;
	case ViewType::Doctors:
		OpenAddDoctorDialog();
		break;
	case ViewType::Patients:
		OpenAddPatientDialog();
		break;
	default:
		AfxMessageBox(_T("Unknown view type"));
		break;
	}
}

void CMFCAppRegistrationinaMedicalClinicDlg::OpenAddVisitDialog()
{
}

void CMFCAppRegistrationinaMedicalClinicDlg::OpenAddDoctorDialog()
{
}

void CMFCAppRegistrationinaMedicalClinicDlg::OpenAddPatientDialog()
{
}