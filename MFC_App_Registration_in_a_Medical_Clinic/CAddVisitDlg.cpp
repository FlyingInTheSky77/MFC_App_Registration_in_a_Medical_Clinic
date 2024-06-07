// CAddVisitDlg.cpp : implementation file
//

#include "pch.h"
#include "MFC_App_Registration_in_a_Medical_Clinic.h"
#include "afxdialogex.h"

#include "sqlite3.h"

#include "CAddVisitDlg.h"

// CAddVisitDlg dialog

IMPLEMENT_DYNAMIC(CAddVisitDlg, CDialogEx)

CAddVisitDlg::CAddVisitDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_VISIT_DIALOG, pParent)
{
   //m_ComboBox.SubclassDlgItem(IDC_COMBO1, this);

   //m_ComboBox.AddString(_T("Doc1"));
   //m_ComboBox.AddString(_T("Doc2"));
}

CAddVisitDlg::~CAddVisitDlg()
{
}

void CAddVisitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    //DDX_Control(pDX, IDC_COMBO1, m_ComboBox1);

    //DDX_Control(pDX, IDC_COMBO1, m_ComboBox1);
    DDX_Control(pDX, IDC_COMBO2, m_ComboBox2);
    DDX_Control(pDX, IDC_EDIT1, m_Edit1);
    DDX_Control(pDX, IDC_EDIT2, m_Edit2);
}


BEGIN_MESSAGE_MAP(CAddVisitDlg, CDialogEx)
	//ON_CBN_SELCHANGE(IDC_COMBO1, &CAddVisitDlg::OnCbnSelchangeCombo1)
    ON_CBN_SELCHANGE(IDD_ADD_VISIT_DIALOG, &CAddVisitDlg::OnCbnSelchangeAddVisitDlg)
    ON_CBN_SELCHANGE(IDC_COMBO2, &CAddVisitDlg::OnCbnSelchangeCombo2)
    ON_EN_CHANGE(IDC_EDIT1, &CAddVisitDlg::OnEnChangeEdit1)
    ON_EN_CHANGE(IDC_EDIT2, &CAddVisitDlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CAddVisitDlg message handlers


//void CAddVisitDlg::OnCbnSelchangeCombo1()
//{
    /*//Открываем соединение с базой данных SQLite
    sqlite3* db;
    int rc = sqlite3_open("example.db", &db);
    if (rc)
    {
        // Обработка ошибки при открытии базы данных
        // Например, вывод сообщения об ошибке
        MessageBox(L"Ошибка при открытии базы данных!");
        return;
    }

    // Создаем SQL-запрос для выборки данных о докторах
    const char* sql = "SELECT name FROM Doctors;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        // Обработка ошибки при подготовке SQL-запроса
        // Например, вывод сообщения об ошибке
        MessageBox(L"Ошибка при подготовке SQL-запроса!");
        sqlite3_close(db);
        return;
    }

    // Очищаем комбо-бокс перед добавлением новых данных
    m_ComboBox.ResetContent();

    // Выполняем SQL-запрос и добавляем результаты в комбо-бокс
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char* doctorName = (const char*)sqlite3_column_text(stmt, 0);
        CString doctorNameStr(doctorName);
        m_ComboBox.AddString(doctorNameStr);
    }

    // Закрываем SQL-запрос и соединение с базой данных
    sqlite3_finalize(stmt);
    sqlite3_close(db);*/
//}


void CAddVisitDlg::OnCbnSelchangeAddVisitDlg()
{
    // TODO: Add your control notification handler code here
}


void CAddVisitDlg::OnCbnSelchangeCombo2()
{
    // TODO: Add your control notification handler code here
}


void CAddVisitDlg::OnEnChangeEdit1()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialogEx::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}

BOOL CAddVisitDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Инициализация комбо-бокса
    AfxMessageBox(_T("Перед вызовом SubclassDlgItem"));

    BOOL result;

    result = m_Edit2.SubclassDlgItem(IDC_EDIT2, this);
    if (!result)
    {
        AfxMessageBox(_T("Ошибка при SubclassDlgItem(IDC_EDIT2) в OnInitDialog"));
    }
    else
    {
        AfxMessageBox(_T("Успешно выполнен SubclassDlgItem(IDC_EDIT2) в OnInitDialog"));
    }


    result = m_ComboBox2.SubclassDlgItem(IDC_COMBO2, this);

    if (!result)
    {
        AfxMessageBox(_T("Ошибка при SubclassDlgItem(IDC_COMBO2) в OnInitDialog"));
    }
    else
    {
        AfxMessageBox(_T("Успешно выполнен SubclassDlgItem(IDC_COMBO2) в OnInitDialog"));
    }

    result = m_Edit1.SubclassDlgItem(IDC_EDIT1, this);
    if (!result)
    {
        AfxMessageBox(_T("Ошибка при SubclassDlgItem(IDC_EDIT1) в OnInitDialog"));
    }
    else
    {
        AfxMessageBox(_T("Успешно выполнен SubclassDlgItem(IDC_EDIT1) в OnInitDialog"));
    }


    /*
    result = m_ComboBox1.SubclassDlgItem(IDC_COMBO1, this);
    if (!result)
    {
        AfxMessageBox(_T("Ошибка при SubclassDlgItem в OnInitDialog"));
    }
    else
    {
        AfxMessageBox(_T("Успешно выполнен SubclassDlgItem в OnInitDialog"));
    }
    */
   


    AfxMessageBox(_T("Перед return в OnInitDialog"));
    return TRUE;  // return TRUE unless you set the focus to a control
}

/*
BEGIN_MESSAGE_MAP(CAddVisitDlg, CDialogEx)
    // Ваши сообщения
END_MESSAGE_MAP()
*/

void CAddVisitDlg::OnEnChangeEdit2()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialogEx::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}
