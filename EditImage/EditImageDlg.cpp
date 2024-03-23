
// EditImageDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "EditImage.h"
#include "EditImageDlg.h"
#include "afxdialogex.h"
#include <windows.h>
#include <gdiplus.h>
#include <stdio.h>
using namespace Gdiplus;

#pragma comment(lib, "gdiplus.lib")

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


// CEditImageDlg dialog



CEditImageDlg::CEditImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDITIMAGE_DIALOG, pParent),
	m_fBrightness(0.0),
	m_fContrast(1.0),
	m_fZoom(1.0),
	m_iRotate(0),
	m_iXImage(0),
	m_iYImage(0),
	m_iWidthImage(0),
	m_iHeightImage(0),
	m_isFlip(false),
	m_isDefaultView(true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEditImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEditImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_SELECT, &CEditImageDlg::OnBnClickedBtnSelect)
	ON_BN_CLICKED(IDC_BTN_VIEW, &CEditImageDlg::OnBnClickedBtnView)
	ON_BN_CLICKED(IDC_BTN_INBRI, &CEditImageDlg::OnBnClickedBtnInbri)
	ON_BN_CLICKED(IDC_BTN_DEBRI, &CEditImageDlg::OnBnClickedBtnDebri)
	ON_BN_CLICKED(IDC_BTN_INCON, &CEditImageDlg::OnBnClickedBtnIncon)
	ON_BN_CLICKED(IDC_BTN_DECON, &CEditImageDlg::OnBnClickedBtnDecon)
	ON_BN_CLICKED(IDC_BTN_ZOOMIN, &CEditImageDlg::OnBnClickedBtnZoomin)
	ON_BN_CLICKED(IDC_BTN_ZOOMOUT, &CEditImageDlg::OnBnClickedBtnZoomout)
	ON_BN_CLICKED(IDC_BTN_ROTATE, &CEditImageDlg::OnBnClickedBtnRotate)
	ON_BN_CLICKED(IDC_BTN_FLIP, &CEditImageDlg::OnBnClickedBtnFlip)
	ON_BN_CLICKED(IDSAVE, &CEditImageDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDRESET, &CEditImageDlg::OnBnClickedReset)
	ON_BN_CLICKED(IDC_BTN_OK, &CEditImageDlg::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_PANUP, &CEditImageDlg::OnBnClickedBtnPanup)
	ON_BN_CLICKED(IDC_BTN_PANRIGHT, &CEditImageDlg::OnBnClickedBtnPanright)
	ON_BN_CLICKED(IDC_BTN_PANDOWN, &CEditImageDlg::OnBnClickedBtnPandown)
	ON_BN_CLICKED(IDC_BTN_PANLEFT, &CEditImageDlg::OnBnClickedBtnPanleft)
END_MESSAGE_MAP()


// CEditImageDlg message handlers

BOOL CEditImageDlg::OnInitDialog()
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

	// TODO: Add extra initialization here
	m_fBrightness = 0.0;
	m_fContrast = 1.0;
	m_fZoom = 1.0;
	m_iRotate = 0;
	m_iXImage = 0;
	m_iYImage = 0;
	m_isFlip = false;
	m_isDefaultView = true;

	CRect box;
	GetDlgItem(IDC_PICTURE_BOX)->GetClientRect(&box);
	m_iWidthImage = box.Width();
	m_iHeightImage = box.Height();
	
	((CButton*)GetDlgItem(IDC_BTN_SELECT))->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_OPEN), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR));
	((CButton*)GetDlgItem(IDC_BTN_SAVE))->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_SAVE), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR));
	((CButton*)GetDlgItem(IDC_BTN_RESET))->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_RESET), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR));
	((CButton*)GetDlgItem(IDC_BTN_ROTATE))->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_ROTATE), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR));
	((CButton*)GetDlgItem(IDC_BTN_FLIP))->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_FLIP), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR));
	((CButton*)GetDlgItem(IDC_BTN_VIEW))->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_VIEWD), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEditImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEditImageDlg::OnPaint()
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
HCURSOR CEditImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CEditImageDlg::OnBnClickedBtnSelect()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("Image Files (*.jpg;*.png)|*.jpg;*.png|JPG Files (*.jpg)|*.jpg|PNG Files (*.png)|*.png||"));
	if (dlg.DoModal() == IDOK)
	{
		CString path = dlg.GetPathName();
		if (!m_imageOrigin.IsNull()) {
			OnBnClickedReset();
			m_imageOrigin.Destroy();
			m_image.Destroy();
		}

		m_imageOrigin.Load(path);
		EditImage();
		GetDlgItem(IDC_PICTURE_0)->ShowWindow(SW_SHOW);
	}
}


void CEditImageDlg::OnBnClickedBtnView()
{
	if (m_imageOrigin.IsNull()) {
		return;
	}

	m_isDefaultView = !m_isDefaultView;

	((CButton*)GetDlgItem(IDC_BTN_VIEW))->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(m_isDefaultView ? IDI_ICON_VIEWD : IDI_ICON_VIEW2X2), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR));
	((CStatic*)GetDlgItem(IDC_PICTURE_0))->ShowWindow(m_isDefaultView ? SW_SHOW : SW_HIDE);
	((CStatic*)GetDlgItem(IDC_PICTURE_1))->ShowWindow(!m_isDefaultView ? SW_SHOW : SW_HIDE);
	((CStatic*)GetDlgItem(IDC_PICTURE_2))->ShowWindow(!m_isDefaultView ? SW_SHOW : SW_HIDE);
	((CStatic*)GetDlgItem(IDC_PICTURE_3))->ShowWindow(!m_isDefaultView ? SW_SHOW : SW_HIDE);
	((CStatic*)GetDlgItem(IDC_PICTURE_4))->ShowWindow(!m_isDefaultView ? SW_SHOW : SW_HIDE);
}


void CEditImageDlg::OnBnClickedBtnInbri()
{
	if (m_imageOrigin.IsNull()) {
		return;
	}

	LogTimeline(_T(" Increase Brightness - START"));
	m_fBrightness += float(0.1);
	EditImage();
	LogTimeline(_T("Increase Brightness - END"));
}



void CEditImageDlg::OnBnClickedBtnDebri()
{
	if (m_imageOrigin.IsNull()) {
		return;
	}
	LogTimeline(_T("Decrease Brightness - START"));
	m_fBrightness -= float(0.1);
	EditImage();
	LogTimeline(_T("Decrease Brightness - END"));
}


void CEditImageDlg::OnBnClickedBtnIncon()
{
	if (m_imageOrigin.IsNull()) {
		return;
	}

	LogTimeline(_T("Increase Contrast - START"));
	m_fContrast += float(0.1);
	EditImage();
	LogTimeline(_T("Increase Contrast - END"));
}


void CEditImageDlg::OnBnClickedBtnDecon()
{
	if (m_imageOrigin.IsNull()) {
		return;
	}

	LogTimeline(_T("Decrease Contrast - START"));	
	m_fContrast -= float(0.1);
	EditImage();
	LogTimeline(_T("Decrease Contrast - END"));
}


void CEditImageDlg::OnBnClickedBtnZoomin()
{
	if (m_imageOrigin.IsNull()) {
		return;
	}

	LogTimeline(_T("Zoom In - START"));
	m_fZoom += float(0.2);
	EditImage();
	LogTimeline(_T("Zoom In - END"));
}


void CEditImageDlg::OnBnClickedBtnZoomout()
{
	if (m_imageOrigin.IsNull()) {
		return;
	}

	LogTimeline(_T("Zoom Out - START"));
	m_fZoom += float(-0.2);
	EditImage();
	LogTimeline(_T("Zoom Out - END"));
}


void CEditImageDlg::OnBnClickedBtnRotate()
{
	if (m_imageOrigin.IsNull()) {
		return;
	}

	LogTimeline(_T("Rotate - START"));
	m_iRotate == 3 ? m_iRotate = 0 : m_iRotate++;
	EditImage();
	LogTimeline(_T("Rotate - END"));
}


void CEditImageDlg::OnBnClickedBtnFlip()
{
	if (m_imageOrigin.IsNull()) {
		return;
	}

	LogTimeline(_T("Flip - START"));
	m_isFlip = !m_isFlip;
	EditImage();
	LogTimeline(_T("Flip - END"));
}


void CEditImageDlg::OnBnClickedSave()
{
	if(m_imageOrigin.IsNull()) {
		AfxMessageBox(_T("Unable to save file"));
		return;
	}

	CFileDialog dlg(FALSE, _T(".jpg"), _T("image"), OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT, _T("Image Files (*.jpg;*.png)|*.jpg;*.png|JPG Files (*.jpg)|*.jpg|PNG Files (*.png)|*.png||"));
	if (dlg.DoModal() == IDOK)
	{
		CString path = dlg.GetPathName();

		CImage image = m_image;
		HBITMAP hBitmap = image.Detach();
		Gdiplus::Bitmap bitmap(hBitmap, NULL);
		Gdiplus::Graphics graphics(&bitmap);

		CDC dc;
		dc.CreateCompatibleDC(NULL);
		CBitmap bmp;
		bmp.CreateCompatibleBitmap(&dc, bitmap.GetWidth(), bitmap.GetHeight());
		CBitmap* pOldBmp = dc.SelectObject(&bmp);
		graphics.DrawImage(&bitmap, 0, 0, bitmap.GetWidth(), bitmap.GetHeight());

		CLSID clsid;
		if (dlg.GetFileExt() == "jpg")
			GetEncoderClsid(L"image/jpeg", &clsid);
		else
			GetEncoderClsid(L"image/png", &clsid);
		bitmap.Save(path, &clsid, NULL);

		AfxMessageBox(_T("Save file successfully!"));
	}
}


void CEditImageDlg::OnBnClickedReset()
{
	if (m_imageOrigin.IsNull()) {
		return;
	}
	LogTimeline(_T("Reset - START"));
	Initialize();
	EditImage();
	LogTimeline(_T("Reset - END"));
}



void CEditImageDlg::OnBnClickedBtnPanup()
{
	if (m_imageOrigin.IsNull()) {
		return;
	}
	LogTimeline(_T("Pan Up - START"));
	m_iYImage -= 10;
	EditImage();
	LogTimeline(_T("Pan Up - END"));
}


void CEditImageDlg::OnBnClickedBtnPanright()
{
	if (m_imageOrigin.IsNull()) {
		return;
	}

	LogTimeline(_T("Pan Right - START"));
	m_iXImage += 10;
	EditImage();
	LogTimeline(_T("Pan Right - END"));
}


void CEditImageDlg::OnBnClickedBtnPandown()
{
	if (m_imageOrigin.IsNull()) {
		return;
	}

	LogTimeline(_T("Pan Down - START"));
	m_iYImage += 10;
	EditImage();
	LogTimeline(_T("Pan Down - END"));
}


void CEditImageDlg::OnBnClickedBtnPanleft()
{
	if (m_imageOrigin.IsNull()) {
		return;
	}

	LogTimeline(_T("Pan Left - START"));
	m_iXImage -= 10;
	EditImage();
	LogTimeline(_T("Pan Left - END"));
}

void CEditImageDlg::OnLButtonUp(UINT nFlags, CPoint point) {
	m_mouseInfo.isLeftPress = false;
}

void CEditImageDlg::OnRButtonUp(UINT nFlags, CPoint point) {
	m_mouseInfo.isRightPress = false;
}

void CEditImageDlg::OnLButtonDown(UINT nFlags, CPoint point) {
	if (m_mouseInfo.isLeftPress || m_mouseInfo.isRightPress) {
		return;
	}

	m_mouseInfo.isLeftPress = true;
	m_mouseInfo.x = point.x;
}

void CEditImageDlg::OnRButtonDown(UINT nFlags, CPoint point) {
	if (m_mouseInfo.isLeftPress || m_mouseInfo.isRightPress) {
		return;
	}

	m_mouseInfo.isRightPress = true;
	m_mouseInfo.x = point.x;
}

void CEditImageDlg::OnMouseMove(UINT nFlags, CPoint point) {
	if (!m_mouseInfo.isLeftPress && !m_mouseInfo.isRightPress && m_imageOrigin.IsNull()) {
		return;
	}

	if ((point.x - m_mouseInfo.x) > 30) {
		m_mouseInfo.x = point.x;
		if(m_mouseInfo.isLeftPress)
			OnBnClickedBtnInbri();
		else if(m_mouseInfo.isRightPress)
			OnBnClickedBtnIncon();
	}
	else if ((m_mouseInfo.x - point.x) > 30) {
		m_mouseInfo.x = point.x;
		if (m_mouseInfo.isLeftPress)
			OnBnClickedBtnDebri();
		else if (m_mouseInfo.isRightPress)
			OnBnClickedBtnDecon();
	}
}

void CEditImageDlg::Initialize() {
	m_fBrightness = 0.0;
	m_fContrast = 1.0;
	m_fZoom = 1.0;
	m_iRotate = 0;
	m_iXImage = 0;
	m_iYImage = 0;
	m_isFlip = false;
	m_isDefaultView = true;

	int picture_id[5] = { IDC_PICTURE_0, IDC_PICTURE_1, IDC_PICTURE_2,IDC_PICTURE_3, IDC_PICTURE_4 };
	for each (int index in picture_id)
	{
		((CStatic*)GetDlgItem(index))->ShowWindow(index == IDC_PICTURE_0 ? SW_SHOW : SW_HIDE);
	}
}


void CEditImageDlg::EditImage() {
	m_image = m_imageOrigin;

	HBITMAP hBitmap = m_image.Detach();
	Gdiplus::Bitmap bitmap(hBitmap, NULL);

	bitmap.RotateFlip(Gdiplus::RotateFlipType(m_iRotate));

	if (m_isFlip) {
		bitmap.RotateFlip(Gdiplus::RotateNoneFlipX);
	}

	Gdiplus::ColorMatrix colorMatrix = {
		m_fContrast, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, m_fContrast, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, m_fContrast, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		m_fBrightness, m_fBrightness, m_fBrightness, 0.0f, 1.0f
	};

	Gdiplus::Bitmap bitmap_bp1(m_iWidthImage, m_iHeightImage, bitmap.GetPixelFormat());
	Gdiplus::Graphics graphics(&bitmap_bp1);
	Gdiplus::ImageAttributes imageAttributes;
	imageAttributes.SetColorMatrix(&colorMatrix, Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);
	graphics.DrawImage(&bitmap, Gdiplus::Rect(m_iXImage, m_iYImage, int(m_iWidthImage * m_fZoom), int(m_iHeightImage * m_fZoom)), 0, 0, bitmap.GetWidth(), bitmap.GetHeight(), Gdiplus::UnitPixel, &imageAttributes);
	bitmap_bp1.GetHBITMAP(NULL, &hBitmap);
	m_image.Attach(hBitmap);

	//Display to Default view
	((CStatic*)GetDlgItem(IDC_PICTURE_0))->SetBitmap(hBitmap);

	//Display to 2x2 View
	Gdiplus::Bitmap bitmap_bp2(m_iWidthImage / 2, m_iHeightImage / 2, bitmap_bp1.GetPixelFormat());
	Gdiplus::Graphics graphics_bp2(&bitmap_bp2);
	graphics_bp2.DrawImage(&bitmap_bp1, Gdiplus::Rect(0, 0, m_iWidthImage / 2, m_iHeightImage / 2),
		0, 0, bitmap_bp1.GetWidth(), bitmap_bp1.GetHeight(), Gdiplus::UnitPixel);
	bitmap_bp2.GetHBITMAP(NULL, &hBitmap);

	int picture_id[4] = {IDC_PICTURE_1, IDC_PICTURE_2,IDC_PICTURE_3, IDC_PICTURE_4 };
	for each (int index in picture_id)
	{
		((CStatic*)GetDlgItem(index))->SetBitmap(hBitmap);
	}
}


void CEditImageDlg::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0) {
		return;
	}

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL) {
		return;
	}

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		*pClsid = pImageCodecInfo[j].Clsid;
		free(pImageCodecInfo);
		return;
	}

	free(pImageCodecInfo);
}

BOOL CEditImageDlg::PreTranslateMessage(MSG* pMsg) {
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam)
		{
		case VK_UP:
			OnBnClickedBtnPanup();
			break;
		case VK_DOWN:
			OnBnClickedBtnPandown();
			break;
		case VK_LEFT:
			OnBnClickedBtnPanleft();
			break;
		case VK_RIGHT:
			OnBnClickedBtnPanright();
			break;
		default:
			break;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CEditImageDlg::OnBnClickedBtnOk()
{
	if (m_imageOrigin.IsNull()) {
		return;
	}

	CString str;
	((CStatic*)GetDlgItem(IDC_TEXT_X))->GetWindowText(str);
	int x = StrToInt(str);
	((CStatic*)GetDlgItem(IDC_TEXT_Y))->GetWindowText(str);
	int y = StrToInt(str);

	((CStatic*)GetDlgItem(IDC_TEXT))->GetWindowText(str);
	
	CClientDC dc(((CStatic*)GetDlgItem(IDC_PICTURE_0)));
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(((CMFCColorButton*)GetDlgItem(IDC_TEXT_COLOR))->GetColor());
	dc.TextOut(x, y, str);
}

void CEditImageDlg::LogTimeline(CString func) {
	SYSTEMTIME time;
	GetSystemTime(&time);

	CString str;
	str.Format(_T("%d:%d:%d.%d"), time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	str += (_T(": ") + func);
	((CListBox*)GetDlgItem(IDC_LIST_LOG))->AddString(str);
}
