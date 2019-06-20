#pragma execution_character_set("utf-8")
#include "debugdlg.h"
#include <QMessageBox>
#include <QVBoxLayout>

DebugDlg::DebugDlg( QWidget *parent )
    :QDialog( parent )
{
    setWindowTitle( tr( "调试" ) );
    setFixedSize( 1220, 330 );

    //PID控制界面
    pidControlWidget = new QWidget();
    pidControlGrid = new QGridLayout( pidControlWidget );

    depthControlModeLabel = new QLabel( tr( "深度控制" ) );
    depthControlModeLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    courseControlModeLabel = new QLabel( tr( "航向控制" ) );
    courseControlModeLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    expectedSpeedLabel = new QLabel( tr( "期望速度" ) );
    expectedSpeedLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    expectedDepthLabel = new QLabel( tr( "期望深度" ) );
    expectedDepthLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    expectedCourseLabel = new QLabel( tr( "期望航向" ) );
    expectedCourseLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    expectedPitchLabel = new QLabel( tr( "期望俯仰" ) );
    expectedPitchLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    depthParaLabel = new QLabel( tr( "深度PID参数(kp,ki,kd)" ) );
    depthParaLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    speedParaLabel = new QLabel( tr( "速度PID参数(kp,ki,kd)" ) );
    speedParaLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    courseParaLabel = new QLabel( tr( "航向PID参数(kp,ki,kd)" ) );
    courseParaLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    pitchParaLabel = new QLabel( tr( "俯仰PID参数(kp,ki,kd)" ) );
    pitchParaLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    /*
    helixVerticalRudderLabel = new QLabel( tr( "螺旋垂直舵" ) );
    helixVerticalRudderLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    helixHorizontalRudderLabel = new QLabel( tr( "螺旋水平舵" ) );
    helixHorizontalRudderLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    uExpectedPitchLabel = new QLabel( tr( "U期望俯仰" ) );
    uExpectedPitchLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    uExpectedHRudderLabel = new QLabel( tr( "U期望水平舵" ) );
    uExpectedHRudderLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    uFixedDepthHRudderLabel = new QLabel( tr( "U定深水平舵" ) );
    uFixedDepthHRudderLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    uFirDepthLabel = new QLabel( tr( "U一阶段深度" ) );
    uFirDepthLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    uSecDepthLabel = new QLabel( tr( "U二阶段深度" ) );
    uSecDepthLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    antiSaturationDepthLabel = new QLabel( tr( "抗饱和深度" ) );
    antiSaturationDepthLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    */

    fractionalOrderLabel = new QLabel( tr( "分数阶 (α,β,Kp,Ki,Kd)" ) );
    fractionalOrderLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    autoDisturbanceLabel = new QLabel( tr( "自抗扰(l1,l2,l3,b0,Kp,Kd)" ) );
    autoDisturbanceLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    modelFreeAdaptiveLabel = new QLabel( tr( "无模型  (φ, λ, ρ, μ, η)" ) );
    modelFreeAdaptiveLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );


    expectedSpeedLineEdit = new QLineEdit();
    expectedSpeedLineEdit -> setText( tr( "0" ) );

    expectedDepthLineEdit = new QLineEdit();
    expectedDepthLineEdit -> setText( tr( "0" ) );

    expectedCourseLineEdit = new QLineEdit();
    expectedCourseLineEdit -> setText( tr( "0" ) );

    expectedPitchLineEdit = new QLineEdit();
    expectedPitchLineEdit -> setText( tr( "0" ) );
    expectedPitchLineEdit -> setEnabled( 0 );

    depthKpLineEdit = new QLineEdit();
    depthKpLineEdit -> setText( tr( "0" ) );

    depthKiLineEdit = new QLineEdit();
    depthKiLineEdit -> setText( tr( "0" ) );

    depthKdLineEdit = new QLineEdit();
    depthKdLineEdit -> setText( tr( "0" ) );

    speedKpLineEdit = new QLineEdit();
    speedKpLineEdit -> setText( tr( "0" ) );

    speedKiLineEdit = new QLineEdit();
    speedKiLineEdit -> setText( tr( "0" ) );

    speedKdLineEdit = new QLineEdit();
    speedKdLineEdit -> setText( tr( "0" ) );

    courseKpLineEdit = new QLineEdit();
    courseKpLineEdit -> setText( tr( "0" ) );

    courseKiLineEdit = new QLineEdit();
    courseKiLineEdit -> setText( tr( "0" ) );

    courseKdLineEdit = new QLineEdit();
    courseKdLineEdit -> setText( tr( "0" ) );

    pitchKpLineEdit = new QLineEdit();
    pitchKpLineEdit -> setText( tr( "0" ) );
    pitchKpLineEdit -> setEnabled( 0 );

    pitchKiLineEdit = new QLineEdit();
    pitchKiLineEdit -> setText( tr( "0" ) );
    pitchKiLineEdit -> setEnabled( 0 );

    pitchKdLineEdit = new QLineEdit();
    pitchKdLineEdit -> setText( tr( "0" ) );
    pitchKdLineEdit -> setEnabled( 0 );

    /*
    helixVRudderLineEdit = new QLineEdit();
    helixVRudderLineEdit -> setText( tr( "0" ) );
    helixVRudderLineEdit -> setEnabled( 0 );

    helixHRudderLineEdit = new QLineEdit();
    helixHRudderLineEdit -> setText( tr( "0" ) );
    helixHRudderLineEdit -> setEnabled( 0 );

    uExpectedPitchLineEdit = new QLineEdit();
    uExpectedPitchLineEdit -> setText( tr( "0" ) );
    uExpectedPitchLineEdit -> setEnabled( 0 );

    uExpectedHRudderLineEdit = new QLineEdit();
    uExpectedHRudderLineEdit -> setText( tr( "0" ) );
    uExpectedHRudderLineEdit -> setEnabled( 0 );

    uFixedDepthHRudderLineEdit = new QLineEdit();
    uFixedDepthHRudderLineEdit -> setText( tr( "0" ) );
    uFixedDepthHRudderLineEdit -> setEnabled( 0 );

    uFirDepthLineEdit = new QLineEdit();
    uFirDepthLineEdit -> setText( tr( "0" ) );
    uFirDepthLineEdit -> setEnabled( 0 );

    uSecDepthLineEdit = new QLineEdit();
    uSecDepthLineEdit -> setText( tr( "0" ) );
    uSecDepthLineEdit -> setEnabled( 0 );

    antiSaturationDepthLineEdit = new QLineEdit();
    antiSaturationDepthLineEdit -> setText( tr( "0" ) );
    antiSaturationDepthLineEdit -> setEnabled( 0 );
    */

    FO_AlphaLineEdit = new QLineEdit();
    FO_AlphaLineEdit -> setText( tr( "0" ) );
    FO_AlphaLineEdit -> setEnabled( 0 );

    FO_BetaLineEdit = new QLineEdit();
    FO_BetaLineEdit -> setText( tr( "0" ) );
    FO_BetaLineEdit -> setEnabled( 0 );

    FO_Heading_KpLineEdit = new QLineEdit();
    FO_Heading_KpLineEdit -> setText( tr( "0" ) );
    FO_Heading_KpLineEdit -> setEnabled( 0 );

    FO_Heading_KiLineEdit = new QLineEdit();
    FO_Heading_KiLineEdit -> setText( tr( "0" ) );
    FO_Heading_KiLineEdit -> setEnabled( 0 );

    FO_Heading_KdLineEdit = new QLineEdit();
    FO_Heading_KdLineEdit -> setText( tr( "0" ) );
    FO_Heading_KdLineEdit -> setEnabled( 0 );

    AD_l1LineEdit = new QLineEdit();
    AD_l1LineEdit -> setText( tr( "0" ) );
    AD_l1LineEdit -> setEnabled( 0 );

    AD_l2LineEdit = new QLineEdit();
    AD_l2LineEdit -> setText( tr( "0" ) );
    AD_l2LineEdit -> setEnabled( 0 );

    AD_l3LineEdit = new QLineEdit();
    AD_l3LineEdit -> setText( tr( "0" ) );
    AD_l3LineEdit -> setEnabled( 0 );

    AD_b0LineEdit = new QLineEdit();
    AD_b0LineEdit -> setText( tr( "0" ) );
    AD_b0LineEdit -> setEnabled( 0 );

    AD_Heading_KpLineEdit = new QLineEdit();
    AD_Heading_KpLineEdit -> setText( tr( "0" ) );
    AD_Heading_KpLineEdit -> setEnabled( 0 );

    AD_Heading_KdLineEdit = new QLineEdit();
    AD_Heading_KdLineEdit -> setText( tr( "0" ) );
    AD_Heading_KdLineEdit -> setEnabled( 0 );

    MFA_phiLineEdit = new QLineEdit();
    MFA_phiLineEdit -> setText( tr( "0" ) );
    MFA_phiLineEdit -> setEnabled( 0 );

    MFA_lambdaLineEdit = new QLineEdit();
    MFA_lambdaLineEdit -> setText( tr( "0" ) );
    MFA_lambdaLineEdit -> setEnabled( 0 );

    MFA_rhoLineEdit = new QLineEdit();
    MFA_rhoLineEdit -> setText( tr( "0" ) );
    MFA_rhoLineEdit -> setEnabled( 0 );

    MFA_muLineEdit = new QLineEdit();
    MFA_muLineEdit -> setText( tr( "0" ) );
    MFA_muLineEdit -> setEnabled( 0 );

    MFA_etaLineEdit = new QLineEdit();
    MFA_etaLineEdit -> setText( tr( "0" ) );
    MFA_etaLineEdit -> setEnabled( 0 );

    depthControlModeCombo = new QComboBox();
    depthControlModeCombo -> addItem( tr( "双闭环" ) );
    depthControlModeCombo -> addItem( tr( "分数阶" ) );
    depthControlModeCombo -> addItem( tr( "自抗扰" ) );
    //depthControlModeCombo -> addItem( tr( "螺旋下降" ) );
    //depthControlModeCombo -> addItem( tr( "U型深度" ) );
    //depthControlModeCombo -> addItem( tr( "模糊控制" ) );
    //depthControlModeCombo -> addItem( tr( "抗饱和积分" ) );
    depthControlModeCombo -> addItem( tr( "无模型" ) );
    depthControlModeCombo -> addItem( tr( "俯仰有效" ) );
    depthControlModeCombo -> addItem( tr( "模糊控制" ) );
    depthControlModeCombo -> addItem( tr( "自抗扰无模型" ) );
    connect( depthControlModeCombo, SIGNAL( currentIndexChanged(int) ), this, SLOT( depthControlModeChanged() ) );

    courseControlModeCombo = new QComboBox();
    courseControlModeCombo -> addItem( tr( "PID" ) );
    courseControlModeCombo -> addItem( tr( "分数阶" ) );
    courseControlModeCombo -> addItem( tr( "自抗扰" ) );
    //depthControlModeCombo -> addItem( tr( "螺旋下降" ) );
    //depthControlModeCombo -> addItem( tr( "U型深度" ) );
    //depthControlModeCombo -> addItem( tr( "模糊控制" ) );
    //depthControlModeCombo -> addItem( tr( "抗饱和积分" ) );
    courseControlModeCombo -> addItem( tr( "无模型" ) );
    courseControlModeCombo -> addItem( tr( "模糊控制" ) );
    courseControlModeCombo -> addItem( tr( "自抗扰无模型" ) );
    connect( courseControlModeCombo, SIGNAL( currentIndexChanged(int) ), this, SLOT( courseControlModeChanged() ) );

    FOCombo = new QComboBox();
    FOCombo -> setEnabled( 0 );
    FOCombo -> addItem( tr( "位置型" ) );
    FOCombo -> addItem( tr( "增量型" ) );
    connect( FOCombo, SIGNAL( currentIndexChanged(int) ), this, SLOT( FOModeChanged() ) );

    fixedHorizontalRudderBox = new QCheckBox( tr( "固定水平舵" ) );
    fixedHorizontalRudderBox -> setEnabled( 0 );
    connect( fixedHorizontalRudderBox, SIGNAL( stateChanged(int) ), this, SLOT( fixedHRudderChecked() ) );

    pidSendBtn = new QPushButton( tr( "发送" ) );
    connect( pidSendBtn, SIGNAL( clicked(bool) ), this, SLOT( pidSendBtnClicked() ) );

    pidControlGrid ->addWidget( depthControlModeLabel, 0, 0, 1, 4 );
    pidControlGrid ->addWidget( depthControlModeCombo, 0, 4, 1, 4 );
    pidControlGrid ->addWidget( courseControlModeLabel, 0, 8, 1, 4 );
    pidControlGrid ->addWidget( courseControlModeCombo, 0, 12, 1, 4 );
    pidControlGrid -> addWidget( expectedSpeedLabel, 1, 0, 1, 4 );
    pidControlGrid -> addWidget( expectedSpeedLineEdit, 1, 4, 1, 4 );
    pidControlGrid -> addWidget( speedParaLabel, 1, 8, 1, 4 );
    pidControlGrid -> addWidget( speedKpLineEdit, 1, 12, 1, 4 );
    pidControlGrid -> addWidget( speedKiLineEdit, 1, 16, 1, 4 );
    pidControlGrid -> addWidget( speedKdLineEdit, 1, 20, 1, 4 );

    pidControlGrid -> addWidget( expectedDepthLabel, 2, 0, 1, 4 );
    pidControlGrid -> addWidget( expectedDepthLineEdit, 2, 4, 1, 4 );
    pidControlGrid -> addWidget( depthParaLabel, 2, 8, 1, 4 );
    pidControlGrid -> addWidget( depthKpLineEdit, 2, 12, 1, 4 );
    pidControlGrid -> addWidget( depthKiLineEdit, 2, 16, 1, 4 );
    pidControlGrid -> addWidget( depthKdLineEdit, 2, 20, 1, 4 );

    pidControlGrid -> addWidget( expectedCourseLabel, 3, 0, 1, 4 ) ;
    pidControlGrid -> addWidget( expectedCourseLineEdit, 3, 4, 1, 4 );
    pidControlGrid -> addWidget( courseParaLabel, 3, 8, 1, 4 );
    pidControlGrid -> addWidget( courseKpLineEdit, 3, 12, 1, 4 );
    pidControlGrid -> addWidget( courseKiLineEdit, 3, 16, 1, 4 );
    pidControlGrid -> addWidget( courseKdLineEdit, 3, 20, 1, 4 );

    pidControlGrid -> addWidget( expectedPitchLabel, 4, 0, 1, 4 );
    pidControlGrid -> addWidget( expectedPitchLineEdit, 4, 4, 1, 4 );
    pidControlGrid -> addWidget( pitchParaLabel, 4, 8, 1, 4 );
    pidControlGrid -> addWidget( pitchKpLineEdit, 4, 12, 1, 4 );
    pidControlGrid -> addWidget( pitchKiLineEdit, 4, 16, 1, 4 );
    pidControlGrid -> addWidget( pitchKdLineEdit, 4, 20, 1, 4 );

    /*
    pidControlGrid -> addWidget( helixVerticalRudderLabel, 5, 0, 1, 4 );
    pidControlGrid -> addWidget( helixVRudderLineEdit, 5, 4, 1, 4 );
    pidControlGrid -> addWidget( helixHorizontalRudderLabel, 5, 8, 1, 4 );
    pidControlGrid -> addWidget( helixHRudderLineEdit, 5, 12, 1, 4 );
    pidControlGrid -> addWidget( fixedHorizontalRudderBox, 5, 19, 1, 4 );
    pidControlGrid -> addWidget( uExpectedPitchLabel, 6, 0, 1, 4 );
    pidControlGrid -> addWidget( uExpectedPitchLineEdit, 6, 4, 1, 4 );
    pidControlGrid -> addWidget( uExpectedHRudderLabel, 6, 8, 1, 4 );
    pidControlGrid -> addWidget( uExpectedHRudderLineEdit, 6, 12, 1, 4 );
    pidControlGrid -> addWidget( uFixedDepthHRudderLabel, 6, 16, 1, 4 );
    pidControlGrid -> addWidget( uFixedDepthHRudderLineEdit, 6, 20, 1, 4 );
    pidControlGrid -> addWidget( uFirDepthLabel, 7, 0, 1, 4 );
    pidControlGrid -> addWidget( uFirDepthLineEdit, 7, 4, 1, 4 );
    pidControlGrid -> addWidget( uSecDepthLabel, 7, 8, 1, 4 );
    pidControlGrid -> addWidget( uSecDepthLineEdit, 7, 12, 1, 4 );
    pidControlGrid -> addWidget( antiSaturationDepthLabel, 7, 16, 1, 4 );
    pidControlGrid -> addWidget( antiSaturationDepthLineEdit, 7, 20, 1, 4 );
    */
    pidControlGrid -> addWidget( modelFreeAdaptiveLabel, 5, 0, 1, 6 );
    pidControlGrid -> addWidget( MFA_phiLineEdit, 5, 6, 1, 3 );
    pidControlGrid -> addWidget( MFA_lambdaLineEdit, 5, 9, 1, 3 );
    pidControlGrid -> addWidget( MFA_rhoLineEdit, 5, 12, 1, 3 );
    pidControlGrid -> addWidget( MFA_muLineEdit, 5, 15, 1, 3 );
    pidControlGrid -> addWidget( MFA_etaLineEdit, 5, 18, 1, 3 );
    pidControlGrid -> addWidget( fixedHorizontalRudderBox, 5, 21, 1, 3 );

    pidControlGrid -> addWidget( autoDisturbanceLabel, 6, 0, 1, 6 );
    pidControlGrid -> addWidget( AD_l1LineEdit, 6, 6, 1, 3 );
    pidControlGrid -> addWidget( AD_l2LineEdit, 6, 9, 1, 3 );
    pidControlGrid -> addWidget( AD_l3LineEdit, 6, 12, 1, 3 );
    pidControlGrid -> addWidget( AD_b0LineEdit, 6, 15, 1, 3 );
    pidControlGrid -> addWidget( AD_Heading_KpLineEdit, 6, 18, 1, 3 );
    pidControlGrid -> addWidget( AD_Heading_KdLineEdit, 6, 21, 1, 3 );

    pidControlGrid -> addWidget( fractionalOrderLabel, 7, 0, 1, 6 );
    pidControlGrid -> addWidget( FO_AlphaLineEdit, 7, 6, 1, 3 );
    pidControlGrid -> addWidget( FO_BetaLineEdit, 7, 9, 1, 3 );
    pidControlGrid -> addWidget( FO_Heading_KpLineEdit, 7, 12, 1, 3 );
    pidControlGrid -> addWidget( FO_Heading_KiLineEdit, 7, 15, 1, 3 );
    pidControlGrid -> addWidget( FO_Heading_KdLineEdit, 7, 18, 1, 3 );
    pidControlGrid -> addWidget( FOCombo, 7, 21, 1, 3 );
    pidControlGrid -> addWidget( pidSendBtn, 8, 11, 1, 3 );

    //底层控制
    underControlWidget = new QWidget();
    underControlGrid = new QGridLayout( underControlWidget );

    expectedRotatingSpeedLabel = new QLabel( tr( "期望转速" ) );
    expectedRotatingSpeedLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    horizontalAngleLabel = new QLabel( tr( "水平舵角" ) );
    horizontalAngleLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    verticalAngleLabel = new QLabel( tr( "垂直舵角" ) );
    verticalAngleLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    expectedRotatingSpeedLineEdit = new QLineEdit();
    expectedRotatingSpeedLineEdit -> setText( tr( "0" ) );

    horizontalAngleLineEdit = new QLineEdit();
    horizontalAngleLineEdit -> setText( tr( "0" ) );

    verticalAngleLineEdit = new QLineEdit();
    verticalAngleLineEdit -> setText( tr( "0" ) );

    resetBox = new QCheckBox( tr( "重置" ) );
    connect( resetBox, SIGNAL( stateChanged(int) ), this, SLOT( resetChecked() ) );

    underSendBtn = new QPushButton( tr( "发送" ) );
    connect( underSendBtn, SIGNAL( clicked(bool) ), this, SLOT( underSendBtnClicked() ) );

    underControlGrid -> addWidget( expectedRotatingSpeedLabel, 0, 0, 1, 1 );
    underControlGrid -> addWidget( expectedRotatingSpeedLineEdit, 0, 1, 1, 2 );
    underControlGrid -> addWidget( horizontalAngleLabel, 0, 4, 1, 1 );
    underControlGrid -> addWidget( horizontalAngleLineEdit, 0, 5, 1, 2 );
    underControlGrid -> addWidget( verticalAngleLabel, 0, 8, 1, 1 );
    underControlGrid -> addWidget( verticalAngleLineEdit, 0, 9, 1, 2 );
    underControlGrid -> addWidget( cellValidBox(), 1, 2, 1, 3);
    underControlGrid -> addWidget( cellDirectionBox(), 1, 5, 1, 3 );
    underControlGrid -> addWidget( resetBox, 1, 8, 1, 1 );
    underControlGrid -> addWidget( underSendBtn, 2, 4, 1, 3 );

    //电机使能
    connect( openCellRadio, SIGNAL( toggled(bool) ), this, SLOT( cellValidChecked() ) );
    connect( closeCellRadio, SIGNAL( toggled(bool) ), this, SLOT( cellInvalidChecked() ) );

    //电机方向使能
    connect( cellForwardRadio, SIGNAL( toggled(bool) ), this, SLOT( cellForwardChecked() ) );
    connect( cellReverseRadio, SIGNAL( toggled(bool) ), this, SLOT( cellReverseChecked() ) );

    //测试验证
    testVerificationWidget = new QWidget();
    testVerificationGrid = new QGridLayout( testVerificationWidget );

    fixDepthModeLabel = new QLabel( "定深测试" );
    fixDepthModeLabel -> setAlignment(  Qt::AlignHCenter | Qt::AlignCenter  );

    fixDepthModeCombo = new QComboBox();
    fixDepthModeCombo -> addItem( tr( "NULL" ) );
    fixDepthModeCombo -> addItem( tr( "一次定深" ) );
    fixDepthModeCombo -> addItem( tr( "分段定深" ) );
    connect( fixDepthModeCombo, SIGNAL( currentIndexChanged(int) ), this, SLOT( fixDepthModeChanged() ) );

    saturationIntegralLineEdit = new QLineEdit();
    saturationIntegralLineEdit -> setEnabled( 0 );

    maxHRudderLineEdit = new QLineEdit();
    maxHRudderLineEdit -> setEnabled( 0 );

    saturationIntegralBox = new QCheckBox( tr( "饱和积分使能" ) );
    connect( saturationIntegralBox, SIGNAL( stateChanged(int) ), this, SLOT( saturationIntegralChecked() ) );

    maxHRudderBox = new QCheckBox( tr( "最大水平舵使能" ) );
    connect( maxHRudderBox, SIGNAL( stateChanged(int) ), this, SLOT( maxHRudderChecked() ) );

    testSendBtn = new QPushButton( tr( "发送" ) );
    connect( testSendBtn, SIGNAL( clicked(bool) ), this, SLOT( testSendBtnClicked() ) );

    testVerificationGrid -> addWidget( fixDepthModeLabel, 0, 0, 1, 1 );
    testVerificationGrid -> addWidget( fixDepthModeCombo, 0, 1, 1, 2 );
    testVerificationGrid -> addWidget( saturationIntegralBox, 0, 4, 1, 1 );
    testVerificationGrid -> addWidget( saturationIntegralLineEdit, 0, 5, 1, 2 );
    testVerificationGrid -> addWidget( maxHRudderBox, 0, 8, 1, 1 );
    testVerificationGrid -> addWidget( maxHRudderLineEdit, 0, 9, 1, 2 );
    testVerificationGrid -> addWidget(testSendBtn, 2, 5, 1, 2 );

    //整合
    tabWidget = new QTabWidget( this );
    tabWidget -> addTab( pidControlWidget, "PID控制" );
    tabWidget -> addTab( underControlWidget, "底层控制" );
    tabWidget -> addTab( testVerificationWidget, "测试验证" );

    m_ctrl_mode = 0;
    m_depth_mode = "NULL";
    m_FO_mode = "0";

    pressbutton_PID = false;
    pressbutton_UnderControl = false;
    pressbutton_Test = false;
}

DebugDlg::~DebugDlg()
{
    delete tabWidget;
}

//推进器使能radioBox
QGroupBox *DebugDlg::cellValidBox()
{
    QGroupBox *cellvalidbox = new QGroupBox( tr( "电机使能" ) );
    cellvalidbox -> setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    openCellRadio = new QRadioButton( tr( "开启推进器" ) );
    openCellRadio -> setChecked( 1 );
    closeCellRadio = new QRadioButton( tr( "关闭推进器" ) );
    QVBoxLayout *vbox = new QVBoxLayout();
    vbox -> addWidget( openCellRadio );
    vbox -> addWidget( closeCellRadio );
    cellvalidbox -> setLayout( vbox );
    return cellvalidbox;
}

//推进器方向radioBox
QGroupBox *DebugDlg::cellDirectionBox()
{
    QGroupBox *celldirectionbox = new QGroupBox( tr( "电机方向" ) );
    celldirectionbox -> setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    cellForwardRadio = new QRadioButton( tr( "推进器正转" ) );
    cellForwardRadio -> setChecked( 1 );
    cellReverseRadio = new QRadioButton( tr( "推进器反转" ) );
    QVBoxLayout *vbox = new QVBoxLayout();
    vbox -> addWidget( cellForwardRadio );
    vbox -> addWidget( cellReverseRadio );
    celldirectionbox -> setLayout( vbox );
    return celldirectionbox;
}

//退出操作
void DebugDlg::closeEvent( QCloseEvent *event )
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question( this, tr( "退出调试" ), QString( tr( "确认退出调试" ) ),
                                    QMessageBox::Yes | QMessageBox::No );
    if( button == QMessageBox::No )
    {
        event -> ignore();
    }
    else if( button == QMessageBox::Yes )
    {
        event -> accept();
    }
}

//模式选择槽信号
void DebugDlg::depthControlModeChanged()
{
    QString currentText = depthControlModeCombo -> currentText();
    if( currentText == "双闭环" )
    {
        expectedSpeedLineEdit -> setEnabled( 1 );
        expectedDepthLineEdit -> setEnabled( 1 );
        expectedCourseLineEdit -> setEnabled( 1 );
        expectedPitchLineEdit -> setEnabled( 0 );
        depthKpLineEdit -> setEnabled( 1 );
        depthKiLineEdit -> setEnabled( 1 );
        depthKdLineEdit -> setEnabled( 1 );
        speedKpLineEdit -> setEnabled( 1 );
        speedKiLineEdit -> setEnabled( 1 );
        speedKdLineEdit -> setEnabled( 1 );
        courseKpLineEdit -> setEnabled( 1 );
        courseKiLineEdit -> setEnabled( 1 );
        courseKdLineEdit -> setEnabled( 1 );
        pitchKpLineEdit -> setEnabled( 0 );
        pitchKiLineEdit -> setEnabled( 0 );
        pitchKdLineEdit -> setEnabled( 0 );

        /*
        helixVRudderLineEdit -> setEnabled( 0 );
        helixHRudderLineEdit -> setEnabled( 0 );
        uExpectedPitchLineEdit -> setEnabled( 0 );
        uExpectedHRudderLineEdit -> setEnabled( 0 );
        uFixedDepthHRudderLineEdit -> setEnabled( 0 );
        uFirDepthLineEdit -> setEnabled( 0 );
        uSecDepthLineEdit -> setEnabled( 0 );
        antiSaturationDepthLineEdit -> setEnabled( 0 );
        */

        FO_AlphaLineEdit -> setEnabled( 0 );
        FO_BetaLineEdit -> setEnabled( 0 );
        FO_Heading_KpLineEdit -> setEnabled( 0 );
        FO_Heading_KiLineEdit -> setEnabled( 0 );
        FO_Heading_KdLineEdit -> setEnabled( 0 );
        AD_l1LineEdit -> setEnabled( 0 );
        AD_l2LineEdit -> setEnabled( 0 );
        AD_l3LineEdit -> setEnabled( 0 );
        AD_b0LineEdit -> setEnabled( 0 );
        AD_Heading_KpLineEdit -> setEnabled( 0 );
        AD_Heading_KdLineEdit -> setEnabled( 0 );
        MFA_phiLineEdit -> setEnabled( 0 );
        MFA_lambdaLineEdit -> setEnabled( 0 );
        MFA_rhoLineEdit -> setEnabled( 0 );
        MFA_muLineEdit -> setEnabled( 0 );
        MFA_etaLineEdit -> setEnabled( 0 );
        fixedHorizontalRudderBox -> setEnabled( 0 );
        FOCombo -> setEnabled( 0 );

        m_ctrl_mode = 0;
    }
    else if( currentText == "自抗扰" )
    {
        expectedSpeedLineEdit -> setEnabled( 1 );
        expectedDepthLineEdit -> setEnabled( 1 );
        expectedCourseLineEdit -> setEnabled( 1 );
        expectedPitchLineEdit -> setEnabled( 0 );
        depthKpLineEdit -> setEnabled( 1 );
        depthKiLineEdit -> setEnabled( 1 );
        depthKdLineEdit -> setEnabled( 1 );
        speedKpLineEdit -> setEnabled( 1 );
        speedKiLineEdit -> setEnabled( 1 );
        speedKdLineEdit -> setEnabled( 1 );
        courseKpLineEdit -> setEnabled( 1 );
        courseKiLineEdit -> setEnabled( 1 );
        courseKdLineEdit -> setEnabled( 1 );
        pitchKpLineEdit -> setEnabled( 0 );
        pitchKiLineEdit -> setEnabled( 0 );
        pitchKdLineEdit -> setEnabled( 0 );

        /*
        helixVRudderLineEdit -> setEnabled( 0 );
        helixHRudderLineEdit -> setEnabled( 0 );
        uExpectedPitchLineEdit -> setEnabled( 0 );
        uExpectedHRudderLineEdit -> setEnabled( 0 );
        uFixedDepthHRudderLineEdit -> setEnabled( 0 );
        uFirDepthLineEdit -> setEnabled( 0 );
        uSecDepthLineEdit -> setEnabled( 0 );
        antiSaturationDepthLineEdit -> setEnabled( 0 );
        */

        FO_AlphaLineEdit -> setEnabled( 0 );
        FO_BetaLineEdit -> setEnabled( 0 );
        FO_Heading_KpLineEdit -> setEnabled( 0 );
        FO_Heading_KiLineEdit -> setEnabled( 0 );
        FO_Heading_KdLineEdit -> setEnabled( 0 );
        AD_l1LineEdit -> setEnabled( 1 );
        AD_l2LineEdit -> setEnabled( 1 );
        AD_l3LineEdit -> setEnabled( 1 );
        AD_b0LineEdit -> setEnabled( 1 );
        AD_Heading_KpLineEdit -> setEnabled( 1 );
        AD_Heading_KdLineEdit -> setEnabled( 1 );
        MFA_phiLineEdit -> setEnabled( 0 );
        MFA_lambdaLineEdit -> setEnabled( 0 );
        MFA_rhoLineEdit -> setEnabled( 0 );
        MFA_muLineEdit -> setEnabled( 0 );
        MFA_etaLineEdit -> setEnabled( 0 );
        fixedHorizontalRudderBox -> setEnabled( 0 );
        FOCombo -> setEnabled( 0 );

        m_ctrl_mode = 1;
    }
    else if( currentText == "分数阶" )
    {
        expectedSpeedLineEdit -> setEnabled( 1 );
        expectedDepthLineEdit -> setEnabled( 1 );
        expectedCourseLineEdit -> setEnabled( 1 );
        expectedPitchLineEdit -> setEnabled( 0 );
        depthKpLineEdit -> setEnabled( 1 );
        depthKiLineEdit -> setEnabled( 1 );
        depthKdLineEdit -> setEnabled( 1 );
        speedKpLineEdit -> setEnabled( 1 );
        speedKiLineEdit -> setEnabled( 1 );
        speedKdLineEdit -> setEnabled( 1 );
        courseKpLineEdit -> setEnabled( 1 );
        courseKiLineEdit -> setEnabled( 1 );
        courseKdLineEdit -> setEnabled( 1 );
        pitchKpLineEdit -> setEnabled( 0 );
        pitchKiLineEdit -> setEnabled( 0 );
        pitchKdLineEdit -> setEnabled( 0 );

        /*
        helixVRudderLineEdit -> setEnabled( 0 );
        helixHRudderLineEdit -> setEnabled( 0 );
        uExpectedPitchLineEdit -> setEnabled( 0 );
        uExpectedHRudderLineEdit -> setEnabled( 0 );
        uFixedDepthHRudderLineEdit -> setEnabled( 0 );
        uFirDepthLineEdit -> setEnabled( 0 );
        uSecDepthLineEdit -> setEnabled( 0 );
        antiSaturationDepthLineEdit -> setEnabled( 0 );
        */

        FO_AlphaLineEdit -> setEnabled( 1 );
        FO_BetaLineEdit -> setEnabled( 1 );
        FO_Heading_KpLineEdit -> setEnabled( 1 );
        FO_Heading_KiLineEdit -> setEnabled( 1 );
        FO_Heading_KdLineEdit -> setEnabled( 1 );
        AD_l1LineEdit -> setEnabled( 0 );
        AD_l2LineEdit -> setEnabled( 0 );
        AD_l3LineEdit -> setEnabled( 0 );
        AD_b0LineEdit -> setEnabled( 0 );
        AD_Heading_KpLineEdit -> setEnabled( 0 );
        AD_Heading_KdLineEdit -> setEnabled( 0 );
        MFA_phiLineEdit -> setEnabled( 0 );
        MFA_lambdaLineEdit -> setEnabled( 0 );
        MFA_rhoLineEdit -> setEnabled( 0 );
        MFA_muLineEdit -> setEnabled( 0 );
        MFA_etaLineEdit -> setEnabled( 0 );
        fixedHorizontalRudderBox -> setEnabled( 0 );
        FOCombo -> setEnabled( 1 );

        m_ctrl_mode = 2;
    }

    /*
    else if( currentText == "螺旋下降" )
    {
        expectedSpeedLineEdit -> setEnabled( 1 );
        expectedDepthLineEdit -> setEnabled( 1 );
        expectedCourseLineEdit -> setEnabled( 1 );
        expectedPitchLineEdit -> setEnabled( 0 );
        depthKpLineEdit -> setEnabled( 1 );
        depthKiLineEdit -> setEnabled( 1 );
        depthKdLineEdit -> setEnabled( 1 );
        speedKpLineEdit -> setEnabled( 1 );
        speedKiLineEdit -> setEnabled( 1 );
        speedKdLineEdit -> setEnabled( 1 );
        courseKpLineEdit -> setEnabled( 1 );
        courseKiLineEdit -> setEnabled( 1 );
        courseKdLineEdit -> setEnabled( 1 );
        pitchKpLineEdit -> setEnabled( 0 );
        pitchKiLineEdit -> setEnabled( 0 );
        pitchKdLineEdit -> setEnabled( 0 );

        helixVRudderLineEdit -> setEnabled( 1 );
        helixHRudderLineEdit -> setEnabled( 1 );
        uExpectedPitchLineEdit -> setEnabled( 0 );
        uExpectedHRudderLineEdit -> setEnabled( 0 );
        uFixedDepthHRudderLineEdit -> setEnabled( 0 );
        uFirDepthLineEdit -> setEnabled( 0 );
        uSecDepthLineEdit -> setEnabled( 0 );
        antiSaturationDepthLineEdit -> setEnabled( 0 );

        FO_AlphaLineEdit -> setEnabled( 0 );
        FO_BetaLineEdit -> setEnabled( 0 );
        FO_Heading_KpLineEdit -> setEnabled( 0 );
        FO_Heading_KiLineEdit -> setEnabled( 0 );
        FO_Heading_KdLineEdit -> setEnabled( 0 );
        AD_l1LineEdit -> setEnabled( 0 );
        AD_l2LineEdit -> setEnabled( 0 );
        AD_l3LineEdit -> setEnabled( 0 );
        AD_b0LineEdit -> setEnabled( 0 );
        AD_Heading_KpLineEdit -> setEnabled( 0 );
        AD_Heading_KdLineEdit -> setEnabled( 0 );
        MFA_phiLineEdit -> setEnabled( 0 );
        MFA_lambdaLineEdit -> setEnabled( 0 );
        MFA_rhoLineEdit -> setEnabled( 0 );
        MFA_muLineEdit -> setEnabled( 0 );
        MFA_etaLineEdit -> setEnabled( 0 );
        fixedHorizontalRudderBox -> setEnabled( 0 );
        FOCombo -> setEnabled( 0 );
    }
    */

    /*
    else if( currentText == "U型深度" )
    {
        expectedSpeedLineEdit -> setEnabled( 1 );
        expectedDepthLineEdit -> setEnabled( 1 );
        expectedCourseLineEdit -> setEnabled( 1 );
        expectedPitchLineEdit -> setEnabled( 0 );
        depthKpLineEdit -> setEnabled( 1 );
        depthKiLineEdit -> setEnabled( 1 );
        depthKdLineEdit -> setEnabled( 1 );
        speedKpLineEdit -> setEnabled( 1 );
        speedKiLineEdit -> setEnabled( 1 );
        speedKdLineEdit -> setEnabled( 1 );
        courseKpLineEdit -> setEnabled( 1 );
        courseKiLineEdit -> setEnabled( 1 );
        courseKdLineEdit -> setEnabled( 1 );
        pitchKpLineEdit -> setEnabled( 0 );
        pitchKiLineEdit -> setEnabled( 0 );
        pitchKdLineEdit -> setEnabled( 0 );

        helixVRudderLineEdit -> setEnabled( 0 );
        helixHRudderLineEdit -> setEnabled( 0 );
        uExpectedPitchLineEdit -> setEnabled( 1 );
        uExpectedHRudderLineEdit -> setEnabled( 1 );
        uFixedDepthHRudderLineEdit -> setEnabled( 1 );
        uFirDepthLineEdit -> setEnabled( 1 );
        uSecDepthLineEdit -> setEnabled( 1 );
        antiSaturationDepthLineEdit -> setEnabled( 0 );

        FO_AlphaLineEdit -> setEnabled( 0 );
        FO_BetaLineEdit -> setEnabled( 0 );
        FO_Heading_KpLineEdit -> setEnabled( 0 );
        FO_Heading_KiLineEdit -> setEnabled( 0 );
        FO_Heading_KdLineEdit -> setEnabled( 0 );
        AD_l1LineEdit -> setEnabled( 0 );
        AD_l2LineEdit -> setEnabled( 0 );
        AD_l3LineEdit -> setEnabled( 0 );
        AD_b0LineEdit -> setEnabled( 0 );
        AD_Heading_KpLineEdit -> setEnabled( 0 );
        AD_Heading_KdLineEdit -> setEnabled( 0 );
        MFA_phiLineEdit -> setEnabled( 0 );
        MFA_lambdaLineEdit -> setEnabled( 0 );
        MFA_rhoLineEdit -> setEnabled( 0 );
        MFA_muLineEdit -> setEnabled( 0 );
        MFA_etaLineEdit -> setEnabled( 0 );
        fixedHorizontalRudderBox -> setEnabled( 0 );
        FOCombo -> setEnabled( 0 );
    }
    */

    /*
    else if( currentText == "模糊控制" )
    {
        expectedSpeedLineEdit -> setEnabled( 1 );
        expectedDepthLineEdit -> setEnabled( 1 );
        expectedCourseLineEdit -> setEnabled( 1 );
        expectedPitchLineEdit -> setEnabled( 0 );
        depthKpLineEdit -> setEnabled( 1 );
        depthKiLineEdit -> setEnabled( 1 );
        depthKdLineEdit -> setEnabled( 1 );
        speedKpLineEdit -> setEnabled( 1 );
        speedKiLineEdit -> setEnabled( 1 );
        speedKdLineEdit -> setEnabled( 1 );
        courseKpLineEdit -> setEnabled( 1 );
        courseKiLineEdit -> setEnabled( 1 );
        courseKdLineEdit -> setEnabled( 1 );
        pitchKpLineEdit -> setEnabled( 0 );
        pitchKiLineEdit -> setEnabled( 0 );
        pitchKdLineEdit -> setEnabled( 0 );

        helixVRudderLineEdit -> setEnabled( 0 );
        helixHRudderLineEdit -> setEnabled( 0 );
        uExpectedPitchLineEdit -> setEnabled( 0 );
        uExpectedHRudderLineEdit -> setEnabled( 0 );
        uFixedDepthHRudderLineEdit -> setEnabled( 0 );
        uFirDepthLineEdit -> setEnabled( 0 );
        uSecDepthLineEdit -> setEnabled( 0 );
        antiSaturationDepthLineEdit -> setEnabled( 0 );

        FO_AlphaLineEdit -> setEnabled( 0 );
        FO_BetaLineEdit -> setEnabled( 0 );
        FO_Heading_KpLineEdit -> setEnabled( 0 );
        FO_Heading_KiLineEdit -> setEnabled( 0 );
        FO_Heading_KdLineEdit -> setEnabled( 0 );
        AD_l1LineEdit -> setEnabled( 0 );
        AD_l2LineEdit -> setEnabled( 0 );
        AD_l3LineEdit -> setEnabled( 0 );
        AD_b0LineEdit -> setEnabled( 0 );
        AD_Heading_KpLineEdit -> setEnabled( 0 );
        AD_Heading_KdLineEdit -> setEnabled( 0 );
        MFA_phiLineEdit -> setEnabled( 0 );
        MFA_lambdaLineEdit -> setEnabled( 0 );
        MFA_rhoLineEdit -> setEnabled( 0 );
        MFA_muLineEdit -> setEnabled( 0 );
        MFA_etaLineEdit -> setEnabled( 0 );
        fixedHorizontalRudderBox -> setEnabled( 0 );
        FOCombo -> setEnabled( 0 );
    }
    */

    /*
    else if( currentText == "抗饱和积分" )
    {
        expectedSpeedLineEdit -> setEnabled( 1 );
        expectedDepthLineEdit -> setEnabled( 1 );
        expectedCourseLineEdit -> setEnabled( 1 );
        expectedPitchLineEdit -> setEnabled( 0 );
        depthKpLineEdit -> setEnabled( 1 );
        depthKiLineEdit -> setEnabled( 1 );
        depthKdLineEdit -> setEnabled( 1 );
        speedKpLineEdit -> setEnabled( 1 );
        speedKiLineEdit -> setEnabled( 1 );
        speedKdLineEdit -> setEnabled( 1 );
        courseKpLineEdit -> setEnabled( 1 );
        courseKiLineEdit -> setEnabled( 1 );
        courseKdLineEdit -> setEnabled( 1 );
        pitchKpLineEdit -> setEnabled( 0 );
        pitchKiLineEdit -> setEnabled( 0 );
        pitchKdLineEdit -> setEnabled( 0 );

        helixVRudderLineEdit -> setEnabled( 0 );
        helixHRudderLineEdit -> setEnabled( 0 );
        uExpectedPitchLineEdit -> setEnabled( 0 );
        uExpectedHRudderLineEdit -> setEnabled( 0 );
        uFixedDepthHRudderLineEdit -> setEnabled( 0 );
        uFirDepthLineEdit -> setEnabled( 0 );
        uSecDepthLineEdit -> setEnabled( 0 );
        antiSaturationDepthLineEdit -> setEnabled( 1 );

        FO_AlphaLineEdit -> setEnabled( 0 );
        FO_BetaLineEdit -> setEnabled( 0 );
        FO_Heading_KpLineEdit -> setEnabled( 0 );
        FO_Heading_KiLineEdit -> setEnabled( 0 );
        FO_Heading_KdLineEdit -> setEnabled( 0 );
        AD_l1LineEdit -> setEnabled( 0 );
        AD_l2LineEdit -> setEnabled( 0 );
        AD_l3LineEdit -> setEnabled( 0 );
        AD_b0LineEdit -> setEnabled( 0 );
        AD_Heading_KpLineEdit -> setEnabled( 0 );
        AD_Heading_KdLineEdit -> setEnabled( 0 );
        MFA_phiLineEdit -> setEnabled( 0 );
        MFA_lambdaLineEdit -> setEnabled( 0 );
        MFA_rhoLineEdit -> setEnabled( 0 );
        MFA_muLineEdit -> setEnabled( 0 );
        MFA_etaLineEdit -> setEnabled( 0 );
        fixedHorizontalRudderBox -> setEnabled( 0 );
        FOCombo -> setEnabled( 0 );
    }
    */

    else if( currentText == "无模型" )
    {
        expectedSpeedLineEdit -> setEnabled( 1 );
        expectedDepthLineEdit -> setEnabled( 1 );
        expectedCourseLineEdit -> setEnabled( 1 );
        expectedPitchLineEdit -> setEnabled( 0 );
        depthKpLineEdit -> setEnabled( 1 );
        depthKiLineEdit -> setEnabled( 1 );
        depthKdLineEdit -> setEnabled( 1 );
        speedKpLineEdit -> setEnabled( 1 );
        speedKiLineEdit -> setEnabled( 1 );
        speedKdLineEdit -> setEnabled( 1 );
        courseKpLineEdit -> setEnabled( 1 );
        courseKiLineEdit -> setEnabled( 1 );
        courseKdLineEdit -> setEnabled( 1 );
        pitchKpLineEdit -> setEnabled( 0 );
        pitchKiLineEdit -> setEnabled( 0 );
        pitchKdLineEdit -> setEnabled( 0 );

        /*
        helixVRudderLineEdit -> setEnabled( 0 );
        helixHRudderLineEdit -> setEnabled( 0 );
        uExpectedPitchLineEdit -> setEnabled( 0 );
        uExpectedHRudderLineEdit -> setEnabled( 0 );
        uFixedDepthHRudderLineEdit -> setEnabled( 0 );
        uFirDepthLineEdit -> setEnabled( 0 );
        uSecDepthLineEdit -> setEnabled( 0 );
        antiSaturationDepthLineEdit -> setEnabled( 0 );
        */

        FO_AlphaLineEdit -> setEnabled( 0 );
        FO_BetaLineEdit -> setEnabled( 0 );
        FO_Heading_KpLineEdit -> setEnabled( 0 );
        FO_Heading_KiLineEdit -> setEnabled( 0 );
        FO_Heading_KdLineEdit -> setEnabled( 0 );
        AD_l1LineEdit -> setEnabled( 0 );
        AD_l2LineEdit -> setEnabled( 0 );
        AD_l3LineEdit -> setEnabled( 0 );
        AD_b0LineEdit -> setEnabled( 0 );
        AD_Heading_KpLineEdit -> setEnabled( 0 );
        AD_Heading_KdLineEdit -> setEnabled( 0 );
        MFA_phiLineEdit -> setEnabled( 1 );
        MFA_lambdaLineEdit -> setEnabled( 1 );
        MFA_rhoLineEdit -> setEnabled( 1 );
        MFA_muLineEdit -> setEnabled( 1 );
        MFA_etaLineEdit -> setEnabled( 1 );
        fixedHorizontalRudderBox -> setEnabled( 0 );
        FOCombo -> setEnabled( 0 );

        m_ctrl_mode = 3;
    }
    else if( currentText == "俯仰有效" )
    {
        expectedSpeedLineEdit -> setEnabled( 1 );
        expectedDepthLineEdit -> setEnabled( 0 );
        expectedCourseLineEdit -> setEnabled( 1 );
        expectedPitchLineEdit -> setEnabled( 1 );
        depthKpLineEdit -> setEnabled( 0 );
        depthKiLineEdit -> setEnabled( 0 );
        depthKdLineEdit -> setEnabled( 0 );
        speedKpLineEdit -> setEnabled( 1 );
        speedKiLineEdit -> setEnabled( 1 );
        speedKdLineEdit -> setEnabled( 1 );
        courseKpLineEdit -> setEnabled( 1 );
        courseKiLineEdit -> setEnabled( 1 );
        courseKdLineEdit -> setEnabled( 1 );
        pitchKpLineEdit -> setEnabled( 1 );
        pitchKiLineEdit -> setEnabled( 1 );
        pitchKdLineEdit -> setEnabled( 1 );

        /*
        helixVRudderLineEdit -> setEnabled( 0 );
        helixHRudderLineEdit -> setEnabled( 0 );
        uExpectedPitchLineEdit -> setEnabled( 0 );
        uExpectedHRudderLineEdit -> setEnabled( 0 );
        uFixedDepthHRudderLineEdit -> setEnabled( 0 );
        uFirDepthLineEdit -> setEnabled( 0 );
        uSecDepthLineEdit -> setEnabled( 0 );
        antiSaturationDepthLineEdit -> setEnabled( 0 );
        */

        FO_AlphaLineEdit -> setEnabled( 0 );
        FO_BetaLineEdit -> setEnabled( 0 );
        FO_Heading_KpLineEdit -> setEnabled( 0 );
        FO_Heading_KiLineEdit -> setEnabled( 0 );
        FO_Heading_KdLineEdit -> setEnabled( 0 );
        AD_l1LineEdit -> setEnabled( 0 );
        AD_l2LineEdit -> setEnabled( 0 );
        AD_l3LineEdit -> setEnabled( 0 );
        AD_b0LineEdit -> setEnabled( 0 );
        AD_Heading_KpLineEdit -> setEnabled( 0 );
        AD_Heading_KdLineEdit -> setEnabled( 0 );
        MFA_phiLineEdit -> setEnabled( 0 );
        MFA_lambdaLineEdit -> setEnabled( 0 );
        MFA_rhoLineEdit -> setEnabled( 0 );
        MFA_muLineEdit -> setEnabled( 0 );
        MFA_etaLineEdit -> setEnabled( 0 );
        fixedHorizontalRudderBox -> setEnabled( 1 );
        FOCombo -> setEnabled( 0 );

        m_ctrl_mode = 4;
    }
    else if( currentText == "自抗扰无模型" )
    {
        expectedSpeedLineEdit -> setEnabled( 1 );
        expectedDepthLineEdit -> setEnabled( 1 );
        expectedCourseLineEdit -> setEnabled( 1 );
        expectedPitchLineEdit -> setEnabled( 0 );
        depthKpLineEdit -> setEnabled( 1 );
        depthKiLineEdit -> setEnabled( 1 );
        depthKdLineEdit -> setEnabled( 1 );
        speedKpLineEdit -> setEnabled( 1 );
        speedKiLineEdit -> setEnabled( 1 );
        speedKdLineEdit -> setEnabled( 1 );
        courseKpLineEdit -> setEnabled( 1 );
        courseKiLineEdit -> setEnabled( 1 );
        courseKdLineEdit -> setEnabled( 1 );
        pitchKpLineEdit -> setEnabled( 0 );
        pitchKiLineEdit -> setEnabled( 0 );
        pitchKdLineEdit -> setEnabled( 0 );

        /*
        helixVRudderLineEdit -> setEnabled( 0 );
        helixHRudderLineEdit -> setEnabled( 0 );
        uExpectedPitchLineEdit -> setEnabled( 0 );
        uExpectedHRudderLineEdit -> setEnabled( 0 );
        uFixedDepthHRudderLineEdit -> setEnabled( 0 );
        uFirDepthLineEdit -> setEnabled( 0 );
        uSecDepthLineEdit -> setEnabled( 0 );
        antiSaturationDepthLineEdit -> setEnabled( 0 );
        */

        FO_AlphaLineEdit -> setEnabled( 0 );
        FO_BetaLineEdit -> setEnabled( 0 );
        FO_Heading_KpLineEdit -> setEnabled( 0 );
        FO_Heading_KiLineEdit -> setEnabled( 0 );
        FO_Heading_KdLineEdit -> setEnabled( 0 );
        AD_l1LineEdit -> setEnabled( 1 );
        AD_l2LineEdit -> setEnabled( 1 );
        AD_l3LineEdit -> setEnabled( 1 );
        AD_b0LineEdit -> setEnabled( 1 );
        AD_Heading_KpLineEdit -> setEnabled( 1 );
        AD_Heading_KdLineEdit -> setEnabled( 1 );
        MFA_phiLineEdit -> setEnabled( 1 );
        MFA_lambdaLineEdit -> setEnabled( 1 );
        MFA_rhoLineEdit -> setEnabled( 1 );
        MFA_muLineEdit -> setEnabled( 1 );
        MFA_etaLineEdit -> setEnabled( 1 );
        fixedHorizontalRudderBox -> setEnabled( 0 );
        FOCombo -> setEnabled( 0 );

        m_ctrl_mode = 5;
    }

}

void DebugDlg::courseControlModeChanged()
{

}

std::string DebugDlg::getPIDParam()
{
    std::string str = "MsgType=debug;Act=provision";
    int curTabIndex = tabWidget -> currentIndex();
    QString qsVal = "";
    std::string sVal = "";

    qsVal = expectedSpeedLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    str += ";spd=";
    str += sVal;

    qsVal = speedKpLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    str += ";spdPID=";
    str += sVal;

    qsVal = speedKiLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    str += ",";
    str += sVal;

    qsVal = speedKdLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    str += ",";
    str += sVal;

    qsVal = expectedCourseLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    str += ";hdg=";
    str += sVal;

    qsVal = courseKpLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    str += ";hdgPID=";
    str += sVal;

    qsVal = courseKiLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    str += ",";
    str += sVal;

    qsVal = courseKdLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    str += ",";
    str += sVal;

    switch( m_ctrl_mode )
    {
        case 0:
        {
            qsVal = expectedDepthLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ";dph=";
            str += sVal;

            qsVal = depthKpLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ";dphPID=";
            str += sVal;

            qsVal = depthKiLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = depthKdLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            break;
        }

        case 1:
        {
            qsVal = AD_l1LineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ";ARDC=";
            str += sVal;

            qsVal = AD_l2LineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = AD_l3LineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = AD_b0LineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = AD_Heading_KpLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = AD_Heading_KdLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            break;
        }

        case 2:
        {
            qsVal = FO_AlphaLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ";foPID=";
            str += sVal;

            qsVal = FO_BetaLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = FO_Heading_KpLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = FO_Heading_KiLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = FO_Heading_KdLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            str += ";FO_mode=";
            str += m_FO_mode;

            break;
        }

        case 3:
        {
            qsVal = MFA_phiLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ";MFA=";
            str += sVal;

            qsVal = MFA_lambdaLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = MFA_rhoLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = MFA_muLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = MFA_etaLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            break;
        }

        case 4:
        {
            qsVal = expectedPitchLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ";pth=";
            str += sVal;

            qsVal = pitchKpLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ";pthPID=";
            str += sVal;

            qsVal = pitchKiLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = pitchKdLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            str += ";dphPID=0,0,0";

            if( fixedHorizontalRudderBox -> isChecked() )
            {
                str +=";fixelev=true";
            }
            else
            {
                str +=";fixelev=false";
            }

            break;
        }

        case 5:
        {
            qsVal = AD_l1LineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ";ARDC+MFA=";
            str += sVal;

            qsVal = AD_l2LineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = AD_l3LineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = AD_b0LineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = AD_Heading_KpLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = AD_Heading_KdLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = MFA_phiLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = MFA_lambdaLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = MFA_rhoLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = MFA_muLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            qsVal = MFA_etaLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            str += ",";
            str += sVal;

            break;
        }
    }
    return str;
}

std::string DebugDlg::getUnderControlParam()
{
    std::string str = "MsgType=debug;Act=provision";
    int curTabIndex = tabWidget -> currentIndex();
    QString qsVal = "";
    std::string sVal = "";

    qsVal = expectedRotatingSpeedLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    str += ";rpm=";
    str += sVal;

    qsVal = verticalAngleLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    str += ";rud=";
    str += sVal;

    qsVal = horizontalAngleLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    str += ";elev=";
    str += sVal;

    str += ";thruswitch=";
    if( openCellRadio -> isChecked() )
    {
       str += "ON";
    }
    else if ( closeCellRadio -> isChecked() )
    {
       str += "OFF";
    }

    str += ";thrudir=";
    if( cellForwardRadio -> isChecked() )
    {
       str += "pos";
    }
    else if( cellReverseRadio -> isChecked() )
    {
       str += "neg";
    }

    str += ";sereset=";
    if( resetBox -> isChecked() )
    {
       str += "yes";
    }
    else
    {
       str += "no";
    }

    return str;
}

std::string DebugDlg::getTestParam()
{
    std::string str = "MsgType=debug;Act=provision";
    int curTabIndex = tabWidget -> currentIndex();
    QString qsVal = "";
    std::string sVal = "";

    if( m_depth_mode != "NULL" )
    {
        str += ";depth_mode=";
        str += m_depth_mode;
    }
    if( saturationIntegralBox -> isChecked() )
    {
        qsVal = saturationIntegralLineEdit -> text();
        qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
        sVal = qsVal.toStdString();
        str += ";integral_wu=";
        str += sVal;
    }
    if( maxHRudderBox -> isChecked() )
    {
        qsVal = maxHRudderLineEdit -> text();
        qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
        sVal = qsVal.toStdString();
        str += ";max_elev=";
        str += sVal;
    }

    return str;
}
//固定水平舵checkbox槽信号
void DebugDlg::fixedHRudderChecked()
{

}

//分数阶模式选择槽信号
void DebugDlg::FOModeChanged()
{
    QString currentText = FOCombo -> currentText();
    if( currentText == "位置型" )
    {
        m_FO_mode = "0";
    }
    else if( currentText == "增量型" )
    {
        m_FO_mode = "1";
    }
}

//重置槽信号
void DebugDlg::resetChecked()
{

}

//推进器开启槽函数
void DebugDlg::cellValidChecked()
{
    cellForwardRadio -> setEnabled( 1 );
    cellForwardRadio -> setChecked( 1 );
    cellReverseRadio -> setEnabled( 1 );
    cellReverseRadio -> setChecked( 0 );
}

//推进器关闭槽函数
void DebugDlg::cellInvalidChecked()
{
    cellForwardRadio -> setChecked( 0 );
    cellForwardRadio -> setEnabled( 0 );
    cellReverseRadio -> setChecked( 0 );
    cellReverseRadio -> setEnabled( 0 );
}

//推进器正向槽函数
void DebugDlg::cellForwardChecked()
{

}

//推进器反向槽函数
void DebugDlg::cellReverseChecked()
{

}

//定深模式选择槽函数
void DebugDlg::fixDepthModeChanged()
{
    QString currentText = fixDepthModeCombo -> currentText();
    if( currentText == "NULL" )
    {
        m_depth_mode = "NULL";
    }
    else if( currentText == "一次定深" )
    {
        m_depth_mode = "0";
    }
    else if( currentText == "分段定深" )
    {
        m_depth_mode = "1";
    }
}

//饱和积分使能槽信号
void DebugDlg::saturationIntegralChecked()
{
    if( saturationIntegralBox -> isChecked() )
    {
        saturationIntegralLineEdit -> setEnabled( 1 );
    }
    else
    {
        saturationIntegralLineEdit -> setEnabled( 0 );
    }

}

//最大水平舵使能槽信号
void DebugDlg::maxHRudderChecked()
{
    if( maxHRudderBox -> isChecked() )
    {
        maxHRudderLineEdit -> setEnabled( 1 );
    }
    else
    {
        maxHRudderLineEdit -> setEnabled( 0 );
    }

}

//PID发送按钮槽信号
void DebugDlg::pidSendBtnClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr( "是否发送数据" ),  tr( "确认发送" ),
                                    QMessageBox::Yes | QMessageBox::No );
    if( reply == QMessageBox::Yes )
    {
        pressbutton_PID = true;
    }
    else if( reply == QMessageBox::No )
    {
        pressbutton_PID = false;
    }
}

//底层控制发送按钮槽信号
void DebugDlg::underSendBtnClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr( "是否发送数据" ),  tr( "确认发送" ),
                                    QMessageBox::Yes | QMessageBox::No );
    if( reply == QMessageBox::Yes )
    {
        pressbutton_UnderControl = true;
    }
    else if( reply == QMessageBox::No )
    {
        pressbutton_UnderControl = false;
    }
}

//测试验证发送按钮槽信号
void DebugDlg::testSendBtnClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr( "是否发送数据" ),  tr( "确认发送" ),
                                    QMessageBox::Yes | QMessageBox::No );
    if( reply == QMessageBox::Yes )
    {
        pressbutton_Test = true;
    }
    else if( reply == QMessageBox::No )
    {
        pressbutton_Test = false;
    }
}
