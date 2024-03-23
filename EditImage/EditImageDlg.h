
// EditImageDlg.h : header file

#pragma once


// CEditImageDlg dialog
class CEditImageDlg : public CDialogEx
{
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDITIMAGE_DIALOG };
#endif

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL	OnInitDialog();
	afx_msg void	OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void	OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	CImage	m_image;
	CImage	m_imageOrigin;
	int		m_iRotate;
	int		m_iWidthImage;
	int		m_iHeightImage;
	int		m_iXImage;
	int		m_iYImage;
	int		m_iXPointClick;
	float	m_fBrightness;
	float	m_fContrast;
	float	m_fZoom;
	bool	m_isFlip;
	bool	m_isDefaultView;

public:
	CEditImageDlg(CWnd* pParent = nullptr);

	afx_msg void OnBnClickedBtnSelect();
	afx_msg void OnBnClickedBtnView();
	afx_msg void OnBnClickedBtnInbri();
	afx_msg void OnBnClickedBtnDebri();
	afx_msg void OnBnClickedBtnIncon();
	afx_msg void OnBnClickedBtnDecon();
	afx_msg void OnBnClickedBtnZoomin();
	afx_msg void OnBnClickedBtnZoomout();
	afx_msg void OnBnClickedBtnRotate();
	afx_msg void OnBnClickedBtnFlip();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedBtnOk();

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	afx_msg void Initialize();
	afx_msg void EditImage();
	afx_msg void CEditImageDlg::GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	afx_msg void LogTimeline(CString func);
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	
};
