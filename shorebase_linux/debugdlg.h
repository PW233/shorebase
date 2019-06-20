#ifndef DEBUGDLG_H
#define DEBUGDLG_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QTabWidget>
#include <QWidget>
#include <QComboBox>
#include <QCloseEvent>

class DebugDlg : public QDialog
{
    Q_OBJECT
public:
    DebugDlg( QWidget *parent = 0 );
    ~DebugDlg();

private:
    QTabWidget *tabWidget;

    //PID控制控件
    QWidget *pidControlWidget;
    QGridLayout *pidControlGrid;

    QLabel *depthControlModeLabel;
    QLabel *courseControlModeLabel;
    QLabel *expectedSpeedLabel;
    QLabel *expectedDepthLabel;
    QLabel *expectedCourseLabel;
    QLabel *expectedPitchLabel;
    QLabel *depthParaLabel;
    QLabel *speedParaLabel;
    QLabel *courseParaLabel;
    QLabel *pitchParaLabel;
    /*
    QLabel *helixVerticalRudderLabel;
    QLabel *helixHorizontalRudderLabel;
    QLabel *uExpectedPitchLabel;
    QLabel *uExpectedHRudderLabel;
    QLabel *uFixedDepthHRudderLabel;
    QLabel *uFirDepthLabel;
    QLabel *uSecDepthLabel;
    QLabel *antiSaturationDepthLabel;
    */
    QLabel *fractionalOrderLabel;
    QLabel *autoDisturbanceLabel;
    QLabel *modelFreeAdaptiveLabel;


    QLineEdit *expectedSpeedLineEdit;
    QLineEdit *expectedDepthLineEdit;
    QLineEdit *expectedCourseLineEdit;
    QLineEdit *expectedPitchLineEdit;
    QLineEdit *depthKpLineEdit;
    QLineEdit *depthKiLineEdit;
    QLineEdit *depthKdLineEdit;
    QLineEdit *speedKpLineEdit;
    QLineEdit *speedKiLineEdit;
    QLineEdit *speedKdLineEdit;
    QLineEdit *courseKpLineEdit;
    QLineEdit *courseKiLineEdit;
    QLineEdit *courseKdLineEdit;
    QLineEdit *pitchKpLineEdit;
    QLineEdit *pitchKiLineEdit;
    QLineEdit *pitchKdLineEdit;
    /*
    QLineEdit *helixVRudderLineEdit;
    QLineEdit *helixHRudderLineEdit;
    QLineEdit *uExpectedPitchLineEdit;
    QLineEdit *uExpectedHRudderLineEdit;
    QLineEdit *uFixedDepthHRudderLineEdit;
    QLineEdit *uFirDepthLineEdit;
    QLineEdit *uSecDepthLineEdit;
    QLineEdit *antiSaturationDepthLineEdit;
    */
    QLineEdit *FO_AlphaLineEdit;
    QLineEdit *FO_BetaLineEdit;
    QLineEdit *FO_Heading_KpLineEdit;
    QLineEdit *FO_Heading_KiLineEdit;
    QLineEdit *FO_Heading_KdLineEdit;
    QLineEdit *AD_l1LineEdit;
    QLineEdit *AD_l2LineEdit;
    QLineEdit *AD_l3LineEdit;
    QLineEdit *AD_b0LineEdit;
    QLineEdit *AD_Heading_KpLineEdit;
    QLineEdit *AD_Heading_KdLineEdit;
    QLineEdit *MFA_phiLineEdit;
    QLineEdit *MFA_lambdaLineEdit;
    QLineEdit *MFA_rhoLineEdit;
    QLineEdit *MFA_muLineEdit;
    QLineEdit *MFA_etaLineEdit;

    QCheckBox *fixedHorizontalRudderBox;  //固定水平舵

    QComboBox *depthControlModeCombo;
    QComboBox *courseControlModeCombo;
    QComboBox *FOCombo;

    QPushButton *pidSendBtn;

    //底层控制控件
    QWidget *underControlWidget;
    QGridLayout *underControlGrid;

    QLabel *expectedRotatingSpeedLabel;
    QLabel *horizontalAngleLabel;
    QLabel *verticalAngleLabel;

    QLineEdit *expectedRotatingSpeedLineEdit;
    QLineEdit *horizontalAngleLineEdit;
    QLineEdit *verticalAngleLineEdit;

    QRadioButton *openCellRadio;
    QRadioButton *closeCellRadio;
    QRadioButton *cellForwardRadio;
    QRadioButton *cellReverseRadio;

    QGroupBox *cellValidBox();
    QGroupBox *cellDirectionBox();

    QCheckBox *resetBox;
    QPushButton *underSendBtn;

    //验证测试控件
    QWidget *testVerificationWidget;
    QGridLayout *testVerificationGrid;

    QComboBox *fixDepthModeCombo;

    QLabel *fixDepthModeLabel;

    QLineEdit *saturationIntegralLineEdit;
    QLineEdit *maxHRudderLineEdit;

    QCheckBox *saturationIntegralBox;
    QCheckBox *maxHRudderBox;

    QPushButton *testSendBtn;

    int m_ctrl_mode;
    std::string m_FO_mode;
    std::string m_depth_mode;

public:
    void closeEvent( QCloseEvent * );
    std::string getPIDParam();
    std::string getUnderControlParam();
    std::string getTestParam();
    bool pressbutton_PID;
    bool pressbutton_UnderControl;
    bool pressbutton_Test;

private slots:
    void depthControlModeChanged();
    void courseControlModeChanged();
    void fixedHRudderChecked();
    void FOModeChanged();
    void pidSendBtnClicked();
    void resetChecked();
    void cellInvalidChecked();
    void cellValidChecked();
    void cellForwardChecked();
    void cellReverseChecked();
    void underSendBtnClicked();
    void fixDepthModeChanged();
    void saturationIntegralChecked();
    void maxHRudderChecked();
    void testSendBtnClicked();

};

#endif // DEBUGDLG_H
