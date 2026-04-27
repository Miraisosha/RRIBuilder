#pragma once


// OutputSelectionDlg dialog

enum class ToolExeType {
	Radar = 0,
	NowCast
};

enum class DataType {
	Rainfall = 0,		//âJó 
	RainIntensity		//ç~êÖã≠ìx
};

class OutputSelectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(OutputSelectionDlg)

	bool create_rain;
	bool create_jmaj;
	bool create_jmay;
	ToolExeType	m_nToolExe;
	DataType	m_nDataType;

	CComboBox m_combToolExe;	// Tool Exe Controller
	CComboBox m_combDataType;	// data type controller

public:
	bool GetFlgRain() const { return create_rain; }
	bool GetFlgJmaJ() const { return create_jmaj; }
	bool GetFlgJmaY() const { return create_jmay; }
	ToolExeType		GetToolExeType() const { return m_nToolExe; }
	DataType		GetDataType() const { return m_nDataType; }
	OutputSelectionDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~OutputSelectionDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECT_OUTPUT };
#endif

private:
	void ResetCtrl(int srcID, int x_offset, int y_offset);
	void MoveCtrl(int srcID, int x_offset, int y_offset);
	void HideCtrl(int srcID);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeComboExe();
	afx_msg void OnSelchangeComboDataType();
};
