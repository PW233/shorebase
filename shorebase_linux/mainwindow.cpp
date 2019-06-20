#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
#include <QGridLayout>
#include <QTime>
#include <QTimer>
#include <QString>
#include <sstream>
#include "MBUtils.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi( this );
    setAttribute( Qt::WA_DeleteOnClose );
    setAttribute( Qt::WA_StyledBackground );
    //setFixedSize( 1600, 900 );
    init();

    bCalibStatus = false;
    bDvlStatus = false;
    bNavstart = false;
    bWarningBox = false;

    wiredEnable = true;
    wirelessEnable= false;
    usblEnable = false;
    iridiumEnable = false;

    pushPending("JOYSTICK_MODE", "mode=default");

    joystickMode = "默认手";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    createMenuBar();
    createWarningDock();
    createStatusMonitorDock();
    createDataMonitorDock();
    createMapDock();
    startCounter();
    startTime();
}

//生成菜单栏
void MainWindow::createMenuBar()
{
    //"文件"子菜单
    quitAction = new QAction( tr( "退出" ) );
    quitAction -> setShortcut( tr( "Ctrl+Q" ) );
    fileMenu = new QMenu( tr( "文件" ) );
    fileMenu = menuBar() -> addMenu( tr( "文件" ) );
    fileMenu -> addAction( quitAction );
    connect( quitAction, SIGNAL( triggered(bool) ), this, SLOT( quitMenuClicked() ) );

    //"配置"子菜单
    configureAction = new QAction( tr( "配置" ) );
    configureAction -> setShortcut( tr( "Ctrl+O" ) );
    configureMenu = menuBar() -> addMenu( tr( "配置" ) );
    configureMenu -> addAction( configureAction );
    connect( configureAction, SIGNAL( triggered(bool) ), this, SLOT( createConfigureDlg() ) );

    //"调试"子菜单
    debugAction = new QAction( tr( "调试" ) );
    debugAction -> setShortcut( tr( "Ctrl+S" ) );
    debugMenu = menuBar() -> addMenu( tr( "调试" ) );
    debugMenu -> addAction( debugAction );
    connect( debugAction, SIGNAL( triggered(bool) ), this, SLOT( createDebugDlg() ) );

    //"控制"子菜单
    controlMenu = menuBar() -> addMenu( tr( "控制" ) );
    navControlMenu = new QMenu( tr( "导航控制" ) );
    motionControlMenu = new QMenu( tr( "运动控制" ) );
    sideScanControlMenu = new QMenu( tr( "侧扫控制" ) );
    rectifyControlMenu = new QMenu( tr( "纠偏控制" ) );
    pc104ControlMenu = new QMenu( tr( "主控电脑" ) );

    navControlAction[0] = new QAction( tr( "开导航" ) );
    navControlAction[1] = new QAction( tr( "关导航" ) );
    motionControlAction[0] = new QAction( tr( "开始" ) );
    motionControlAction[1] = new QAction( tr( "启航" ) );
    motionControlAction[2] = new QAction( tr( "暂停" ) );
    motionControlAction[3] = new QAction( tr( "继续" ) );
    motionControlAction[4] = new QAction( tr( "上浮" ) );
    motionControlAction[5] = new QAction( tr( "返回" ) );
    motionControlAction[6] = new QAction( tr( "停止运动" ) );
    sideScanControlAction[0] = new QAction( tr( "打开侧扫" ) );
    sideScanControlAction[1] = new QAction( tr( "关闭侧扫" ) );
    rectifyControlAction[0] = new QAction( tr( "开始纠偏" ) );
    rectifyControlAction[1] = new QAction( tr( "完成纠偏" ) );
    rectifyControlAction[2] = new QAction( tr( "取消纠偏" ) );
    pc104ControlAction[0] = new QAction( tr( "关闭主控电脑" ) );
    pc104ControlAction[1] = new QAction( tr( "重启主控电脑" ) );

    controlMenu -> addMenu( navControlMenu );
    controlMenu -> addMenu( motionControlMenu );
    controlMenu -> addMenu( sideScanControlMenu );
    controlMenu -> addMenu( rectifyControlMenu );
    controlMenu -> addMenu( pc104ControlMenu );

    navControlMenu -> addAction( navControlAction[0] );
    navControlMenu -> addAction( navControlAction[1] );
    motionControlMenu -> addAction( motionControlAction[0] );
    motionControlMenu -> addAction( motionControlAction[1] );
    motionControlMenu -> addAction( motionControlAction[2] );
    motionControlMenu -> addAction( motionControlAction[3] );
    motionControlMenu -> addAction( motionControlAction[4] );
    motionControlMenu -> addAction( motionControlAction[5] );
    motionControlMenu -> addAction( motionControlAction[6] );
    sideScanControlMenu -> addAction( sideScanControlAction[0] );
    sideScanControlMenu -> addAction( sideScanControlAction[1] );
    rectifyControlMenu -> addAction( rectifyControlAction[0] );
    rectifyControlMenu -> addAction( rectifyControlAction[1] );
    rectifyControlMenu -> addAction( rectifyControlAction[2] );
    pc104ControlMenu -> addAction( pc104ControlAction[0] );
    pc104ControlMenu -> addAction( pc104ControlAction[1] );
    connect( controlMenu, SIGNAL( triggered(QAction*) ), this, SLOT( controlMenuClicked(QAction*) ) );

    //"传感器"子菜单
    sensorMenu = menuBar() -> addMenu( tr( "传感器" ) );
    usblManagerMenu = new QMenu( tr( "USBL管理" ) );
    dvlManagerMenu = new QMenu( tr( "DVL管理" ) );
    tossingManagerMenu = new QMenu( tr( "抛载管理" ) );
    ledManagerMenu = new QMenu( tr( "LED管理" ) );
    insManagerMenu = new QMenu( tr( "惯导管理" ) );
    thrusterManagerMenu = new QMenu( tr( "推进器管理" ) );
    ahrsManagerMenu = new QMenu( tr( "AHRS管理" ) );
    usblManagerAction[0] = new QAction( tr( "USBL上电" ) );
    //usblManagerAction[0] -> setCheckable( 1 );
    usblManagerAction[1] = new QAction( tr( "USBL下电" ) );
    //usblManagerAction[1] -> setCheckable( 1 );
    usblManagerAction[2] = new QAction( tr( "USBL自控" ) );
    //usblManagerAction[2] -> setCheckable( 1 );
    dvlManagerAction[0] = new QAction( tr( "DVL上电" ) );
    //dvlManagerAction[0] -> setCheckable( 1 );
    dvlManagerAction[1] = new QAction( tr( "DVL下电" ) );
    //dvlManagerAction[1] -> setCheckable( 1 );
    tossingManagerAction[0] = new QAction( tr( "抛载上电" ) );
    //tossingManagerAction[0] -> setCheckable( 1 );
    tossingManagerAction[1] = new QAction( tr( "抛载下电" ) );
    //tossingManagerAction[1] -> setCheckable( 1 );
    ledManagerAction[0] = new QAction( tr( "LED上电" ) );
    ledManagerAction[1] = new QAction( tr( "LED下电" ) );
    insManagerAction[0] = new QAction( tr( "惯导上电" ) );
    insManagerAction[1] = new QAction( tr( "惯导下电" ) );
    thrusterManagerAction[0] = new QAction( tr( "推进器电源上电" ) );
    thrusterManagerAction[1] = new QAction( tr( "推进器电源下电" ) );
    ahrsManagerAction[0] = new QAction( tr( "AHRS上电" ) );
    ahrsManagerAction[1] = new QAction( tr( "AHRS下电" ) );
    sensorMenu -> addMenu( usblManagerMenu );
    sensorMenu -> addMenu( dvlManagerMenu );
    sensorMenu -> addMenu( tossingManagerMenu );
    sensorMenu -> addMenu( ledManagerMenu );
    sensorMenu -> addMenu( insManagerMenu );
    sensorMenu -> addMenu( thrusterManagerMenu );
    sensorMenu -> addMenu( ahrsManagerMenu );
    usblManagerMenu -> addAction( usblManagerAction[0] );
    usblManagerMenu -> addAction( usblManagerAction[1] );
    usblManagerMenu -> addAction( usblManagerAction[2] );
    dvlManagerMenu -> addAction( dvlManagerAction[0] );
    dvlManagerMenu -> addAction( dvlManagerAction[1] );
    tossingManagerMenu -> addAction( tossingManagerAction[0] );
    tossingManagerMenu -> addAction( tossingManagerAction[1] );
    ledManagerMenu -> addAction( ledManagerAction[0] );
    ledManagerMenu -> addAction( ledManagerAction[1] );
    insManagerMenu -> addAction( insManagerAction[0] );
    insManagerMenu -> addAction( insManagerAction[1] );
    thrusterManagerMenu -> addAction( thrusterManagerAction[0] );
    thrusterManagerMenu -> addAction( thrusterManagerAction[1] );
    ahrsManagerMenu -> addAction( ahrsManagerAction[0] );
    ahrsManagerMenu -> addAction( ahrsManagerAction[1] );
    connect( sensorMenu, SIGNAL( triggered(QAction*) ), this, SLOT( sensorMenuClicked(QAction*) ) );

    //"使命规划"子菜单
    setStartAndViewAction = new QAction( tr( "起点视野设置" ) );
    setMissionParaAction = new QAction( tr( "使命参数设置" ) );
    setPathPlanningAction = new QAction( tr( "路径规划设置" ) );
    missionPlanningMenu = menuBar() -> addMenu( tr( "使命规划" ) );
    missionPlanningMenu -> addAction( setStartAndViewAction );
    missionPlanningMenu -> addAction( setMissionParaAction );
    missionPlanningMenu -> addAction( setPathPlanningAction );
    connect( missionPlanningMenu, SIGNAL( triggered(QAction*) ), this, SLOT( MissionMenuClicked(QAction*) ) );

    //"应急设置"子菜单
    setEmergencyParaAction = new QAction( tr( "应急参数设置" ) );
    startTaskCountAction = new QAction( tr( "任务计时开始" ) );
    endTaskCountAction = new QAction( tr( "任务计时结束" ) );
    emergencyShowAction = new QAction( tr( "应急告警显示" ) );
    clearEmergencyAction = new QAction( tr( "清除应急告警" ) );
    openEmergencyAction = new QAction( tr( "打开应急告警" ) );
    closeEmergencyAction = new QAction( tr( "关闭应急告警" ) );
    setEmergencyMenu = menuBar() -> addMenu( tr( "应急设置" ) );
    setEmergencyMenu -> addAction( setEmergencyParaAction );
    setEmergencyMenu -> addAction( startTaskCountAction );
    setEmergencyMenu -> addAction( endTaskCountAction );
    setEmergencyMenu -> addAction( emergencyShowAction );
    setEmergencyMenu -> addAction( clearEmergencyAction );
    setEmergencyMenu -> addAction( openEmergencyAction );
    setEmergencyMenu -> addAction( closeEmergencyAction );
    connect( setEmergencyMenu, SIGNAL( triggered(QAction*) ), this, SLOT( EmergencyMenuClicked(QAction*) ) );

    //"通信信道"子菜单
    wiredNetAction = new QAction( tr( "有线网络" ) );
    wiredNetAction -> setCheckable( true );
    wiredNetAction -> setChecked( true );
    wirelessNetAction = new QAction( tr( "无线网络" ) );
    wirelessNetAction -> setCheckable( true );
    iriSystemAction = new QAction( tr( "铱星系统" ) );
    iriSystemAction -> setCheckable( true );
    usblEquipmentAction = new QAction( tr( "USBL设备" ) );
    usblEquipmentAction -> setCheckable( true );
    comChannelGroup = new QActionGroup( this );
    comChannelGroup -> setExclusive( 0 );
    comChannelMenu = menuBar() -> addMenu( tr( "通信信道" ) );
    comChannelMenu -> addAction( comChannelGroup -> addAction( wiredNetAction ) );
    comChannelMenu -> addAction( comChannelGroup -> addAction( wirelessNetAction ) );
    comChannelMenu -> addAction( comChannelGroup -> addAction( iriSystemAction ) );
    comChannelMenu -> addAction( comChannelGroup -> addAction( usblEquipmentAction ) );
    connect( comChannelGroup, SIGNAL( triggered(QAction*) ), this, SLOT( comChannelMenuClicked(QAction*) ) );

    //"手柄控制"子菜单
    defaultAction = new QAction( tr( "默认模式" ) );
    defaultAction -> setCheckable( 1 );
    defaultAction -> setChecked( 1 );
    CourseCtrlAction = new QAction( tr( "航向控制" ) );
    CourseCtrlAction -> setCheckable( 1 );
    AmericaAction = new QAction( tr( "美国手柄" ) );
    AmericaAction -> setCheckable( 1 );
    JapanAction = new QAction( tr( "日本手柄" ) );
    JapanAction -> setCheckable( 1 );

    handleGroup = new QActionGroup( this );
    handleGroup -> setExclusive( 1 );

    handleControlMenu = menuBar() -> addMenu( tr( "手柄控制" ) );
    handleControlMenu -> addAction( handleGroup -> addAction( defaultAction ) );
    handleControlMenu -> addAction( handleGroup -> addAction( CourseCtrlAction ) );
    handleControlMenu -> addAction( handleGroup -> addAction( AmericaAction ) );
    handleControlMenu -> addAction( handleGroup -> addAction( JapanAction ) );

    connect( handleGroup, SIGNAL( triggered(QAction*) ), this, SLOT( handleMenuClicked(QAction*) ) );

    //"进程管理"子菜单
    processOnAction = new QAction( tr( "启动应用进程" ) );
    processOffAction = new QAction( tr( "关闭应用进程" ) );
    processShutdownAction = new QAction( tr( "关闭所有进程" ) );
    processPowerOffAction = new QAction( tr( "关进程并关机" ) );
    processManagerMenu = menuBar() -> addMenu( tr( "进程管理" ) );
    processManagerMenu -> addAction( processOnAction );
    processManagerMenu -> addAction( processOffAction );
    processManagerMenu -> addAction( processShutdownAction );
    processManagerMenu -> addAction( processPowerOffAction );
    connect( processManagerMenu, SIGNAL( triggered(QAction*) ), this, SLOT( processManagerClicked(QAction*) ) );

    //"视图管理"子菜单
    warningAction = new QAction( tr( "告警信息窗口" ) );
    warningAction -> setCheckable( 1 );
    warningAction -> setChecked( 1 );
    statusAction = new QAction( tr( "设备监测窗口" ) );
    statusAction -> setCheckable( 1 );
    statusAction -> setChecked( 1 );
    dataAction = new QAction( tr( "数据监测窗口" ) );
    dataAction -> setCheckable( 1 );
    dataAction -> setChecked( 1 );
    chartAction = new QAction( tr( "实时图表窗口" ) );
    chartAction -> setCheckable( 1 );
    chartAction -> setChecked( 0 );
    mapAction = new QAction( tr( "地图显示窗口" ) );
    mapAction -> setCheckable( 1 );
    mapAction -> setChecked( 1 );
    actionGroup = new QActionGroup( this );
    actionGroup -> setExclusive( 0 );
    userDefinedMenu = menuBar() -> addMenu( tr( "视图管理" ) );
    userDefinedMenu -> addAction( actionGroup -> addAction( warningAction ) );
    userDefinedMenu -> addAction( actionGroup -> addAction( statusAction ) );
    userDefinedMenu -> addAction( actionGroup -> addAction( dataAction ) );
    userDefinedMenu -> addAction( actionGroup -> addAction( chartAction ) );
    userDefinedMenu -> addAction( actionGroup -> addAction( mapAction ) );
    connect( actionGroup, SIGNAL( triggered(QAction*) ), this, SLOT( userDefinedMenuChecked(QAction*) ) );
}

//告警信息窗口
void MainWindow::createWarningDock()
{
    warningWidget = new QWidget();
    warningWidget -> setFixedSize( 430, 140 );
    warningGrid = new QGridLayout( warningWidget );

    ambientHightTempLabel = new QLabel( tr( "环境温度过高" ) );
    ambientHightTempLabel -> setStyleSheet( "background-color:#228B22;" );
    ambientHightTempLabel -> setFixedSize( 100, 20 );
    ambientHightTempLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    ambientHumidityLabel = new QLabel( tr( "环境湿度过高" ) );
    ambientHumidityLabel -> setStyleSheet( "background-color:#228B22;" );
    ambientHumidityLabel -> setFixedSize( 100, 20 );
    ambientHumidityLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    cellHightTempLabel = new QLabel( tr( "主推温度过高" ) );
    cellHightTempLabel -> setStyleSheet( "background-color:#228B22;" );
    cellHightTempLabel -> setFixedSize( 100, 20 );
    cellHightTempLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    cellHumidityLabel = new QLabel( tr( "主推湿度过高" ) );
    cellHumidityLabel -> setStyleSheet( "background-color:#228B22;" );
    cellHumidityLabel -> setFixedSize( 100, 20 );
    cellHumidityLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    pcHightTempLabel = new QLabel( tr( "主控温度过高" ) );
    pcHightTempLabel -> setStyleSheet( "background-color:#228B22;" );
    pcHightTempLabel -> setFixedSize( 100, 20 );
    pcHightTempLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    pcHumidityLabel = new QLabel( tr( "主控湿度过高" ) );
    pcHumidityLabel -> setStyleSheet( "background-color:#228B22;" );
    pcHumidityLabel -> setFixedSize( 100, 20 );
    pcHumidityLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    motorOverCurrentLabel = new QLabel( tr( "电机过流" ) );
    motorOverCurrentLabel -> setStyleSheet( "background-color:#228B22;" );
    motorOverCurrentLabel -> setFixedSize( 100, 20 );
    motorOverCurrentLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    motorOverVoltageLabel = new QLabel( tr( "电机过压" ) );
    motorOverVoltageLabel -> setStyleSheet( "background-color:#228B22;" );
    motorOverVoltageLabel -> setFixedSize( 100, 20 );
    motorOverVoltageLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    motorUnderVoltageLabel = new QLabel( tr( "电机欠压" ) );
    motorUnderVoltageLabel -> setStyleSheet( "background-color:#228B22;" );
    motorUnderVoltageLabel -> setFixedSize( 100, 20 );
    motorUnderVoltageLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    motorOverSpeedLabel = new QLabel( tr( "电机超速" ) );
    motorOverSpeedLabel -> setStyleSheet( "background-color:#228B22;" );
    motorOverSpeedLabel -> setFixedSize( 100, 20 );
    motorOverSpeedLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    motorDriveLabel = new QLabel( tr( "电机过热" ) );
    motorDriveLabel -> setStyleSheet( "background-color:#228B22;" );
    motorDriveLabel -> setFixedSize( 100, 20 );
    motorDriveLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    groundLabel = new QLabel( tr( "接地检测" ) );
    groundLabel -> setStyleSheet( "background-color:#228B22;" );
    groundLabel -> setFixedSize( 100, 20 );
    groundLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    overPressureLabel = new QLabel( tr( "气压过压" ) );
    overPressureLabel -> setStyleSheet( "background-color:#228B22;" );
    overPressureLabel -> setFixedSize( 100, 20 );
    overPressureLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    emergencyLabel = new QLabel( tr( "AUV应急" ) );
    emergencyLabel -> setStyleSheet( "background-color:#228B22;" );
    emergencyLabel -> setFixedSize( 100, 20 );
    emergencyLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    batteryOverCurrentLabel = new QLabel( tr( "电池过流" ) );
    batteryOverCurrentLabel -> setStyleSheet( "background-color:#228B22;" );
    batteryOverCurrentLabel -> setFixedSize( 100, 20 );
    batteryOverCurrentLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    batteryOverVoltageLabel = new QLabel( tr( "电池过压" ) );
    batteryOverVoltageLabel -> setStyleSheet( "background-color:#228B22;" );
    batteryOverVoltageLabel -> setFixedSize( 100, 20 );
    batteryOverVoltageLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    batteryUnderVoltageLabel = new QLabel( tr( "电池欠压" ) );
    batteryUnderVoltageLabel -> setStyleSheet( "background-color:#228B22;" );
    batteryUnderVoltageLabel -> setFixedSize( 100, 20 );
    batteryUnderVoltageLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    headLeakageLabel = new QLabel( tr( "前舱泄漏" ) );
    headLeakageLabel -> setStyleSheet( "background-color:#228B22;" );
    headLeakageLabel -> setFixedSize( 100, 20 );
    headLeakageLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    backLeakageLabel = new QLabel( tr( "后舱泄漏" ) );
    backLeakageLabel -> setStyleSheet( "background-color:#228B22;" );
    backLeakageLabel -> setFixedSize( 100, 20 );
    backLeakageLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    tailLeakageLabel = new QLabel( tr( "尾舱泄漏" ) );
    tailLeakageLabel -> setStyleSheet( "background-color:#228B22;" );
    tailLeakageLabel -> setFixedSize( 100, 20 );
    tailLeakageLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    iridiumLabel = new QLabel( tr( "铱星信道" ) );
    iridiumLabel -> setStyleSheet( "background-color:#228B22;" );
    iridiumLabel -> setFixedSize( 100, 20 );
    iridiumLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    wiredLabel = new QLabel( tr( "有线信道" ) );
    wiredLabel -> setStyleSheet( "background-color:#228B22;" );
    wiredLabel -> setFixedSize( 100, 20 );
    wiredLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    usblLabel = new QLabel( tr( "水声信道" ) );
    usblLabel -> setStyleSheet( "background-color:#228B22;" );
    usblLabel -> setFixedSize( 100, 20 );
    usblLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    wirelessLabel = new QLabel( tr( "无线电台" ) );
    wirelessLabel -> setStyleSheet( "background-color:#228B22;" );
    wirelessLabel -> setFixedSize( 100, 20 );
    wirelessLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    warningGrid -> addWidget( ambientHightTempLabel, 0, 0 );
    warningGrid -> addWidget( ambientHumidityLabel, 1, 0 );
    warningGrid -> addWidget( cellHightTempLabel, 2, 0 );
    warningGrid -> addWidget( cellHumidityLabel, 3, 0 );
    warningGrid -> addWidget( pcHightTempLabel, 4, 0 );
    warningGrid -> addWidget( pcHumidityLabel, 5, 0 );
    warningGrid -> addWidget( motorOverCurrentLabel, 0, 1 );
    warningGrid -> addWidget( motorOverVoltageLabel, 1, 1 );
    warningGrid -> addWidget( motorUnderVoltageLabel, 2, 1 );
    warningGrid -> addWidget( motorOverSpeedLabel, 3, 1 );
    warningGrid -> addWidget( motorDriveLabel, 4, 1 );
    warningGrid -> addWidget( groundLabel, 5, 1 );
    warningGrid -> addWidget( headLeakageLabel, 0, 2 );
    warningGrid -> addWidget( backLeakageLabel, 1, 2 );
    warningGrid -> addWidget( tailLeakageLabel, 2, 2 );
    warningGrid -> addWidget( batteryOverCurrentLabel, 3, 2 );
    warningGrid -> addWidget( batteryOverVoltageLabel, 4, 2 );
    warningGrid -> addWidget( batteryUnderVoltageLabel, 5, 2 );
    warningGrid -> addWidget( overPressureLabel, 0, 3 );
    warningGrid -> addWidget( emergencyLabel, 1, 3 );
    warningGrid -> addWidget( iridiumLabel, 2, 3 );
    warningGrid -> addWidget( wiredLabel, 3, 3 );
    warningGrid -> addWidget( usblLabel, 4, 3 );
    warningGrid -> addWidget( wirelessLabel, 5, 3 );

    warningDock = new QDockWidget( tr( "告警信息" ), this );
    /*
    QPalette pa_bg;
    pa_bg.setColor(QPalette::Background, QColor(217,217,217));
    warningDock -> setAutoFillBackground(true);
    warningDock -> setPalette(pa_bg);
    */
  //  warningDock -> setStyleSheet( "background-color:#d9d9d9;" );
    warningDock -> setFeatures( QDockWidget::AllDockWidgetFeatures );  //窗口可移动可关闭
    warningDock -> setAllowedAreas( Qt::LeftDockWidgetArea );
    warningDock -> setWidget( warningWidget );
    addDockWidget( Qt::LeftDockWidgetArea, warningDock );
}

//设备监测窗口
void MainWindow::createStatusMonitorDock()
{
    statusMonitorWidget = new QWidget();
    statusMonitorWidget -> setFixedSize( 430, 140 );
    statusMonitorGrid = new QGridLayout( statusMonitorWidget );

    ahrsLabel = new QLabel( tr( "AHRS" ) );
    ahrsLabel -> setStyleSheet( "background-color:#228B22;" );
    ahrsLabel -> setFixedSize( 100, 20 );
    ahrsLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    ahrsLineEdit = new QLineEdit();
    ahrsLineEdit -> setFont(QFont("Timers", 8));
    ahrsLineEdit -> setFixedSize( 100, 20 );
    ahrsLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    ahrsLineEdit -> setReadOnly( 1 );

    insLabel = new QLabel( tr( "INS" ) );
    insLabel -> setStyleSheet( "background-color:#228B22;" );
    insLabel -> setFixedSize( 100, 20 );
    insLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    insLineEdit = new QLineEdit();
    insLineEdit -> setFont(QFont("Timers", 8));
    insLineEdit -> setFixedSize( 100, 20 );
    insLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    insLineEdit -> setReadOnly( 1 );

    firNetLabel = new QLabel( tr(  "主控网络") );
    firNetLabel -> setStyleSheet( "background-color:#228B22;" );
    firNetLabel -> setFixedSize( 100, 20 );
    firNetLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    firNetLineEdit = new QLineEdit();
    firNetLineEdit -> setFont(QFont("Timers", 8));
    firNetLineEdit -> setFixedSize( 100, 20 );
    firNetLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    firNetLineEdit -> setReadOnly( 1 );

    canLabel = new QLabel( tr( "CAN盒" ) );
    canLabel -> setStyleSheet( "background-color:#228B22;" );
    canLabel -> setFixedSize( 100, 20 );
    canLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    canLineEdit = new QLineEdit();
    canLineEdit -> setFont(QFont("Timers", 8));
    canLineEdit -> setFixedSize( 100, 20 );
    canLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    canLineEdit -> setReadOnly( 1 );

    ipsLabel = new QLabel( tr( "深度计" ) );
    ipsLabel -> setStyleSheet( "background-color:#228B22;" );
    ipsLabel -> setFixedSize( 100, 20 );
    ipsLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    ipsLineEdit = new QLineEdit();
    ipsLineEdit -> setFont(QFont("Timers", 8));
    ipsLineEdit -> setFixedSize( 100, 20 );
    ipsLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    ipsLineEdit -> setReadOnly( 1 );

    gpsLabel = new QLabel( tr( "GPS" ) );
    gpsLabel -> setStyleSheet( "background-color:#228B22;" );
    gpsLabel -> setFixedSize( 100, 20 );
    gpsLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    gpsLineEdit = new QLineEdit();
    gpsLineEdit -> setFont(QFont("Timers", 8));
    gpsLineEdit -> setFixedSize( 100, 20 );
    gpsLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    gpsLineEdit -> setReadOnly( 1 );

    dvlLabel = new QLabel( tr( "DVL" ) );
    dvlLabel -> setStyleSheet( "background-color:#228B22;" );
    dvlLabel -> setFixedSize( 100, 20 );
    dvlLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    dvlLineEdit = new QLineEdit();
    dvlLineEdit -> setFont(QFont("Timers", 8));
    dvlLineEdit -> setFixedSize( 100, 20 );
    dvlLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    dvlLineEdit -> setReadOnly( 1 );

    sonarLabel = new QLabel( tr( "侧扫" ) );
    sonarLabel -> setStyleSheet( "background-color:#228B22;" );
    sonarLabel -> setFixedSize( 100, 20 );
    sonarLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    sonarLineEdit = new QLineEdit();
    sonarLineEdit -> setFont(QFont("Timers", 8));
    sonarLineEdit -> setFixedSize( 100, 20 );
    sonarLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    sonarLineEdit -> setReadOnly( 1 );

    secNetLabel = new QLabel( tr( "副控网络" ) );
    secNetLabel -> setStyleSheet( "background-color:#228B22;" );
    secNetLabel -> setFixedSize( 100, 20 );
    secNetLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    secNetLineEdit = new QLineEdit();
    secNetLineEdit -> setFixedSize( 100, 20 );
    secNetLineEdit -> setFont(QFont("Timers", 8));
    secNetLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    secNetLineEdit -> setReadOnly( 1 );

    handleLabel = new QLabel( tr( "手柄" ) );
    handleLabel -> setStyleSheet( "background-color:#228B22;" );
    handleLabel -> setFixedSize( 100, 20 );
    handleLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    handleLineEdit = new QLineEdit();
    handleLineEdit -> setFont(QFont("Timers", 8));
    handleLineEdit -> setFixedSize( 100, 20 );
    handleLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    handleLineEdit -> setReadOnly( 1 );

    refreshBtn = new QPushButton( tr( "刷新" ) );
    refreshBtn -> setStyleSheet( "background-color:#f1c232;" );
    refreshBtn -> setFixedSize( 100, 20 );
    connect( refreshBtn, SIGNAL( clicked(bool) ), this, SLOT( refreshBtnClicked() ) );

    statusMonitorGrid -> addWidget( firNetLabel, 0, 0 );
    statusMonitorGrid -> addWidget( firNetLineEdit, 0, 1 );
    statusMonitorGrid -> addWidget( insLabel, 0, 2 );
    statusMonitorGrid -> addWidget( insLineEdit, 0, 3 );
    statusMonitorGrid -> addWidget( secNetLabel, 1, 0 );
    statusMonitorGrid -> addWidget( secNetLineEdit, 1, 1 );
    statusMonitorGrid -> addWidget( gpsLabel, 1, 2 );
    statusMonitorGrid -> addWidget( gpsLineEdit, 1, 3 );
    statusMonitorGrid -> addWidget( ahrsLabel, 2, 0 );
    statusMonitorGrid -> addWidget( ahrsLineEdit, 2, 1 );
    statusMonitorGrid -> addWidget( ipsLabel, 2, 2 );
    statusMonitorGrid -> addWidget( ipsLineEdit, 2, 3 );
    statusMonitorGrid -> addWidget( dvlLabel, 3, 0 );
    statusMonitorGrid -> addWidget( dvlLineEdit, 3, 1 );
    statusMonitorGrid -> addWidget( canLabel, 3, 2 );
    statusMonitorGrid -> addWidget( canLineEdit, 3, 3 );
    statusMonitorGrid -> addWidget( sonarLabel, 4, 0 );
    statusMonitorGrid -> addWidget( sonarLineEdit, 4, 1 );
    statusMonitorGrid -> addWidget( handleLabel, 4, 2 );
    statusMonitorGrid -> addWidget( handleLineEdit, 4, 3 );
    statusMonitorGrid -> addWidget( refreshBtn, 5, 3 );

    statusMonitorDock = new QDockWidget( tr( "设备监测" ), this );
    /*
    QPalette pa_bg_1;
    pa_bg_1.setColor(QPalette::Background, QColor(217,217,217));
    statusMonitorDock -> setAutoFillBackground(true);
    statusMonitorDock -> setPalette(pa_bg_1);
    */
   // statusMonitorDock -> setStyleSheet( "background-color:#d9d9d9;" );
    statusMonitorDock -> setFeatures( QDockWidget::AllDockWidgetFeatures );
    statusMonitorDock -> setAllowedAreas( Qt::LeftDockWidgetArea );
    statusMonitorDock -> setWidget( statusMonitorWidget );
    addDockWidget( Qt::LeftDockWidgetArea, statusMonitorDock );

}

//数据监测窗口
void MainWindow::createDataMonitorDock()
{
    dataMonitorWidget = new QWidget();
    dataMonitorWidget -> setFixedSize( 430, 330 );
    dataMonitorGrid = new QGridLayout( dataMonitorWidget );

    robotLabel = new QLabel( tr( "机器人" ) );
    robotLabel -> setStyleSheet( "background-color:#228B22;" );
    robotLabel -> setFixedSize( 80, 20 );
    robotLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    robotLineEdit = new QLineEdit();
    robotLineEdit -> setFont(QFont("Timers", 8));
    robotLineEdit -> setFixedSize( 80, 20 );
    robotLineEdit -> setText( tr( "n/a" ) );
    robotLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    robotLineEdit -> setReadOnly( 1 );

    emergencyStatusLabel = new QLabel( tr( "应急情况" ) );
    emergencyStatusLabel -> setStyleSheet( "background-color:#228B22;" );
    emergencyStatusLabel -> setFixedSize( 80, 20 );
    emergencyStatusLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    emergencyStatusLineEdit = new QLineEdit();
    emergencyStatusLineEdit -> setFont(QFont("Timers", 8));
    emergencyStatusLineEdit -> setFixedSize( 80, 20 );
    emergencyStatusLineEdit -> setText( tr( "n/a" ) );
    emergencyStatusLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    emergencyStatusLineEdit -> setReadOnly( 1 );

    counterLabel = new QLabel( tr( "计时(s)" ) );
    counterLabel -> setStyleSheet( "background-color:#228B22;" );
    counterLabel -> setFixedSize( 80, 20 );
    counterLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    counterLineEdit = new QLineEdit();
    counterLineEdit -> setFont(QFont("Timers", 8));
    counterLineEdit -> setFixedSize( 80, 20 );
    counterLineEdit -> setText( tr( "n/a" ) );
    counterLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    counterLineEdit -> setReadOnly( 1 );

    timeLabel = new QLabel( tr( "时间" ) );
    timeLabel -> setStyleSheet( "background-color:#228B22;" );
    timeLabel -> setFixedSize( 80, 20 );
    timeLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    timeLineEdit = new QLineEdit();
    timeLineEdit -> setFont(QFont("Timers", 8));
    timeLineEdit -> setFixedSize( 80, 20 );
    timeLineEdit -> setText( tr( "n/a" ) );
    timeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    timeLineEdit -> setReadOnly( 1 );

    lngLatitudeLabel = new QLabel( tr( "当前经纬度" ) );
    lngLatitudeLabel -> setStyleSheet( "background-color:#228B22;" );
    lngLatitudeLabel -> setFixedSize( 100, 20 );
    lngLatitudeLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    longitudeLineEdit = new QLineEdit();
    longitudeLineEdit -> setFont(QFont("Timers", 8));
    longitudeLineEdit -> setFixedSize( 68, 20 );
    longitudeLineEdit -> setText( tr( "n/a" ) );
    longitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    longitudeLineEdit -> setReadOnly( 1 );
    latitudeLineEdit = new QLineEdit();
    latitudeLineEdit -> setFont(QFont("Timers", 8));
    latitudeLineEdit -> setFixedSize( 68, 20 );
    latitudeLineEdit -> setText( tr( "n/a" ) );
    latitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    latitudeLineEdit -> setReadOnly( 1 );

    xyCoordinateLabel = new QLabel( tr( "当前坐标(m)" ) );
    xyCoordinateLabel -> setStyleSheet( "background-color:#228B22;" );
    xyCoordinateLabel -> setFixedSize( 100, 20 );
    xyCoordinateLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    xCoordinateLineEdit = new QLineEdit();
    xCoordinateLineEdit -> setFont(QFont("Timers", 8));
    xCoordinateLineEdit -> setFixedSize( 68, 20 );
    xCoordinateLineEdit -> setText( tr( "n/a" ) );
    xCoordinateLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    xCoordinateLineEdit -> setReadOnly( 1 );
    yCoordinateLineEdit = new QLineEdit();
    yCoordinateLineEdit -> setFont(QFont("Timers", 8));
    yCoordinateLineEdit -> setFixedSize( 68, 20 );
    yCoordinateLineEdit -> setText( tr( "n/a" ) );
    yCoordinateLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    yCoordinateLineEdit -> setReadOnly( 1 );

    gpsLngLatitudeLabel = new QLabel( tr( "GPS经纬度" ) );
    gpsLngLatitudeLabel -> setStyleSheet( "background-color:#228B22;" );
    gpsLngLatitudeLabel -> setFixedSize( 100, 20 );
    gpsLngLatitudeLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    gpsLongitudeLineEdit = new QLineEdit();
    gpsLongitudeLineEdit -> setFont(QFont("Timers", 8));
    gpsLongitudeLineEdit -> setFixedSize( 68, 20 );
    gpsLongitudeLineEdit -> setText( tr( "n/a" ) );
    gpsLongitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    gpsLongitudeLineEdit -> setReadOnly( 1 );
    gpsLatitudeLineEdit = new QLineEdit();
    gpsLatitudeLineEdit -> setFont(QFont("Timers", 8));
    gpsLatitudeLineEdit -> setFixedSize( 68, 20 );
    gpsLatitudeLineEdit -> setText( tr( "n/a" ) );
    gpsLatitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    gpsLatitudeLineEdit -> setReadOnly( 1 );

    gpsSatelliteLabel = new QLabel( tr( "GPS卫星" ) );
    gpsSatelliteLabel -> setStyleSheet( "background-color:#228B22;" );
    gpsSatelliteLabel -> setFixedSize( 80, 20 );
    gpsSatelliteLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    gpsSatelliteLineEdit = new QLineEdit();
    gpsSatelliteLineEdit -> setFont(QFont("Timers", 8));
    gpsSatelliteLineEdit -> setFixedSize( 80, 20 );
    gpsSatelliteLineEdit -> setText( tr( "n/a" ) );
    gpsSatelliteLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    gpsSatelliteLineEdit -> setReadOnly( 1 );

    gpsSignalLabel = new QLabel( tr( "GPS信号" ) );
    gpsSignalLabel -> setStyleSheet( "background-color:#228B22;" );
    gpsSignalLabel -> setFixedSize( 80, 20 );
    gpsSignalLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    gpsSignalLineEdit = new QLineEdit();
    gpsSignalLineEdit -> setFont(QFont("Timers", 8));
    gpsSignalLineEdit -> setFixedSize( 80, 20 );
    gpsSignalLineEdit -> setText( tr( "n/a" ) );
    gpsSignalLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    gpsSignalLineEdit -> setReadOnly( 1 );

    batteryOneLabel = new QLabel( tr( "电池一(V|A)" ) );
    batteryOneLabel -> setStyleSheet( "background-color:#228B22;" );
    batteryOneLabel -> setFixedSize( 100, 20 );
    batteryOneLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    batteryOneVoltageLineEdit = new QLineEdit();
    batteryOneVoltageLineEdit -> setFont(QFont("Timers", 8));
    batteryOneVoltageLineEdit -> setFixedSize( 68, 20 );
    batteryOneVoltageLineEdit -> setText( tr( "n/a" ) );
    batteryOneVoltageLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    batteryOneVoltageLineEdit -> setReadOnly( 1 );
    batteryOneCurrentLineEdit = new QLineEdit();
    batteryOneCurrentLineEdit -> setFont(QFont("Timers", 8));
    batteryOneCurrentLineEdit -> setFixedSize( 68, 20 );
    batteryOneCurrentLineEdit -> setText( tr( "n/a" ) );
    batteryOneCurrentLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    batteryOneCurrentLineEdit -> setReadOnly( 1 );

    batteryTwoLabel = new QLabel( tr( "电池二(V|A)" ) );
    batteryTwoLabel -> setStyleSheet( "background-color:#228B22;" );
    batteryTwoLabel -> setFixedSize( 100, 20 );
    batteryTwoLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    batteryTwoVoltageLineEdit = new QLineEdit();
    batteryTwoVoltageLineEdit -> setFont(QFont("Timers", 8));
    batteryTwoVoltageLineEdit -> setFixedSize( 68, 20 );
    batteryTwoVoltageLineEdit -> setText( tr( "n/a" ) );
    batteryTwoVoltageLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    batteryTwoVoltageLineEdit -> setReadOnly( 1 );
    batteryTwoCurrentLineEdit = new QLineEdit();
    batteryTwoCurrentLineEdit -> setFont(QFont("Timers", 8));
    batteryTwoCurrentLineEdit -> setFixedSize( 68, 20 );
    batteryTwoCurrentLineEdit -> setText( tr( "n/a" ) );
    batteryTwoCurrentLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    batteryTwoCurrentLineEdit -> setReadOnly( 1 );

    cellTemperatureLabel = new QLabel( tr( "主推温度(°C)" ) );
    cellTemperatureLabel -> setStyleSheet( "background-color:#228B22;" );
    cellTemperatureLabel -> setFixedSize( 100, 20 );
    cellTemperatureLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    cellTemperatureLineEdit = new QLineEdit();
    cellTemperatureLineEdit -> setFont(QFont("Timers", 8));
    cellTemperatureLineEdit -> setFixedSize( 140, 20 );
    cellTemperatureLineEdit -> setText( tr( "n/a" ) );
    cellTemperatureLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    cellTemperatureLineEdit -> setReadOnly( 1 );

    pcTemperatureLabel = new QLabel( tr( "主控温度(°C)" ) );
    pcTemperatureLabel -> setStyleSheet( "background-color:#228B22;" );
    pcTemperatureLabel -> setFixedSize( 100, 20 );
    pcTemperatureLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    pcTemperatureLineEdit = new QLineEdit();
    pcTemperatureLineEdit -> setFont(QFont("Timers", 8));
    pcTemperatureLineEdit -> setFixedSize( 140, 20 );
    pcTemperatureLineEdit -> setText( tr( "n/a" ) );
    pcTemperatureLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    pcTemperatureLineEdit -> setReadOnly( 1 );

    cabinTemperatureLabel = new QLabel( tr( "舱内温度(°C)" ) );
    cabinTemperatureLabel -> setStyleSheet( "background-color:#228B22;" );
    cabinTemperatureLabel -> setFixedSize( 100, 20 );
    cabinTemperatureLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    cabinTemperatureLineEdit = new QLineEdit();
    cabinTemperatureLineEdit -> setFont(QFont("Timers", 8));
    cabinTemperatureLineEdit -> setFixedSize( 140, 20 );
    cabinTemperatureLineEdit -> setText( tr( "n/a" ) );
    cabinTemperatureLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    cabinTemperatureLineEdit -> setReadOnly( 1 );

    cabinHumidityLabel = new QLabel( tr( "舱内湿度" ) );
    cabinHumidityLabel -> setStyleSheet( "background-color:#228B22;" );
    cabinHumidityLabel -> setFixedSize( 100, 20 );
    cabinHumidityLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    cabinHumidityLineEdit = new QLineEdit();
    cabinHumidityLineEdit -> setFont(QFont("Timers", 8));
    cabinHumidityLineEdit -> setFixedSize( 140, 20 );
    cabinHumidityLineEdit -> setText( tr( "n/a" ) );
    cabinHumidityLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    cabinHumidityLineEdit -> setReadOnly( 1 );

    cabinDewPointLabel = new QLabel( tr( "舱内露点" ) );
    cabinDewPointLabel -> setStyleSheet( "background-color:#228B22;" );
    cabinDewPointLabel -> setFixedSize( 80, 20 );
    cabinDewPointLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    cabinDewPointLineEdit = new QLineEdit();
    cabinDewPointLineEdit -> setFont(QFont("Timers", 8));
    cabinDewPointLineEdit -> setFixedSize( 80, 20 );
    cabinDewPointLineEdit -> setText( tr( "n/a" ) );
    cabinDewPointLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    cabinDewPointLineEdit -> setReadOnly( 1 );

    cabinPressureLabel = new QLabel( tr( "舱内气压(hPa)" ) );
    cabinPressureLabel -> setStyleSheet( "background-color:#228B22;" );
    cabinPressureLabel -> setFixedSize( 100, 20 );
    cabinPressureLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    cabinPressureLineEdit = new QLineEdit();
    cabinPressureLineEdit -> setFont(QFont("Timers", 8));
    cabinPressureLineEdit -> setFixedSize( 140, 20 );
    cabinPressureLineEdit -> setText( tr( "n/a" ) );
    cabinPressureLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    cabinPressureLineEdit -> setReadOnly( 1 );

    motorLabel = new QLabel( tr( "电机(V|A)" ) );
    motorLabel -> setStyleSheet( "background-color:#228B22;" );
    motorLabel -> setFixedSize( 100, 20 );
    motorLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    motorVoltageLineEdit = new QLineEdit();
    motorVoltageLineEdit -> setFont(QFont("Timers", 8));
    motorVoltageLineEdit -> setFixedSize( 68, 20 );
    motorVoltageLineEdit -> setText( tr( "n/a" ) );
    motorVoltageLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    motorVoltageLineEdit -> setReadOnly( 1 );
    motorCurrentLineEdit = new QLineEdit();
    motorCurrentLineEdit -> setFont(QFont("Timers", 8));
    motorCurrentLineEdit -> setFixedSize( 68, 20 );
    motorCurrentLineEdit -> setText( tr( "n/a" ) );
    motorCurrentLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    motorCurrentLineEdit -> setReadOnly( 1 );

    motorSpeedLabel = new QLabel( tr( "电机转速(RPM)" ) );
    motorSpeedLabel -> setStyleSheet( "background-color:#228B22;" );
    motorSpeedLabel -> setFixedSize( 100, 20 );
    motorSpeedLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    motorSpeedLineEdit = new QLineEdit();
    motorSpeedLineEdit -> setFont(QFont("Timers", 8));
    motorSpeedLineEdit -> setFixedSize( 68, 20 );
    motorSpeedLineEdit -> setText( tr( "n/a" ) );
    motorSpeedLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    motorSpeedLineEdit -> setReadOnly( 1 );

    motorDirectionLabel = new QLabel( tr( "电机方向" ) );
    motorDirectionLabel -> setStyleSheet( "background-color:#228B22;" );
    motorDirectionLabel -> setFixedSize( 100, 20 );
    motorDirectionLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    motorDirectionLineEdit = new QLineEdit();
    motorDirectionLineEdit -> setFont(QFont("Timers", 8));
    motorDirectionLineEdit -> setFixedSize( 68, 20 );
    motorDirectionLineEdit -> setText( tr( "n/a" ) );
    motorDirectionLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    motorDirectionLineEdit -> setReadOnly( 1 );

    headLeakLabel = new QLabel( tr( "前舱泄漏" ) );
    headLeakLabel -> setStyleSheet( "background-color:#228B22;" );
    headLeakLabel -> setFixedSize( 80, 20 );
    headLeakLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    headLeakLineEdit = new QLineEdit();
    headLeakLineEdit -> setFont(QFont("Timers", 8));
    headLeakLineEdit -> setFixedSize( 80, 20 );
    headLeakLineEdit -> setText( tr( "n/a" ) );
    headLeakLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    headLeakLineEdit -> setReadOnly( 1 );

    backLeakLabel = new QLabel( tr( "后舱泄漏" ) );
    backLeakLabel -> setStyleSheet( "background-color:#228B22;" );
    backLeakLabel -> setFixedSize( 80, 20 );
    backLeakLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    backLeakLineEdit = new QLineEdit();
    backLeakLineEdit -> setFont(QFont("Timers", 8));
    backLeakLineEdit -> setFixedSize( 80, 20 );
    backLeakLineEdit -> setText( tr( "n/a" ) );
    backLeakLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    backLeakLineEdit -> setReadOnly( 1 );

    tailLeakLabel = new QLabel( tr( "尾舱泄漏" ) );
    tailLeakLabel -> setStyleSheet( "background-color:#228B22;" );
    tailLeakLabel -> setFixedSize( 80, 20 );
    tailLeakLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    tailLeakLineEdit = new QLineEdit();
    tailLeakLineEdit -> setFont(QFont("Timers", 8));
    tailLeakLineEdit -> setFixedSize( 80, 20 );
    tailLeakLineEdit -> setText( tr( "n/a" ) );
    tailLeakLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    tailLeakLineEdit -> setReadOnly( 1 );

    groundMonitorLabel = new QLabel( tr( "接地监测" ) );
    groundMonitorLabel -> setStyleSheet( "background-color:#228B22;" );
    groundMonitorLabel -> setFixedSize( 80, 20 );
    groundMonitorLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    groundMonitorLineEdit = new QLineEdit();
    groundMonitorLineEdit -> setFont(QFont("Timers", 8));
    groundMonitorLineEdit -> setFixedSize( 80, 20 );
    groundMonitorLineEdit -> setText( tr( "n/a" ) );
    groundMonitorLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    groundMonitorLineEdit -> setReadOnly( 1 );

    startLngLatitudeLabel = new QLabel( tr( "起点经纬度" ) );
    startLngLatitudeLabel -> setStyleSheet( "background-color:#228B22;" );
    startLngLatitudeLabel -> setFixedSize( 100, 20 );
    startLngLatitudeLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    startLongitudeLineEdit = new QLineEdit();
    startLongitudeLineEdit -> setFont(QFont("Timers", 8));
    startLongitudeLineEdit -> setFixedSize( 68, 20 );
    startLongitudeLineEdit -> setText( tr( "n/a" ) );
    startLongitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    startLongitudeLineEdit -> setReadOnly( 1 );
    startLatitudeLineEdit = new QLineEdit();
    startLatitudeLineEdit -> setFont(QFont("Timers", 8));
    startLatitudeLineEdit -> setFixedSize( 68, 20 );
    startLatitudeLineEdit -> setText( tr( "n/a" ) );
    startLatitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    startLatitudeLineEdit -> setReadOnly( 1 );

    iriLngLatitudeLabel = new QLabel( tr( "铱星经纬度" ) );
    iriLngLatitudeLabel -> setStyleSheet( "background-color:#228B22;" );
    iriLngLatitudeLabel -> setFixedSize( 100, 20 );
    iriLngLatitudeLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    iriLongitudeLineEdit = new QLineEdit();
    iriLongitudeLineEdit -> setFont(QFont("Timers", 8));
    iriLongitudeLineEdit -> setFixedSize( 68, 20 );
    iriLongitudeLineEdit -> setText( tr( "n/a" ) );
    iriLongitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    iriLongitudeLineEdit -> setReadOnly( 1 );
    iriLatitudeLineEdit = new QLineEdit();
    iriLatitudeLineEdit -> setFont(QFont("Timers", 8));
    iriLatitudeLineEdit -> setFixedSize( 68, 20 );
    iriLatitudeLineEdit -> setText( tr( "n/a" ) );
    iriLatitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    iriLatitudeLineEdit -> setReadOnly( 1 );

    currentChannelLabel = new QLabel( tr( "当前信道" ) );
    currentChannelLabel -> setStyleSheet( "background-color:#228B22;" );
    currentChannelLabel -> setFixedSize( 80, 20 );
    currentChannelLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    currentChannelLineEdit = new QLineEdit();
    currentChannelLineEdit -> setFont(QFont("Timers", 8));
    currentChannelLineEdit -> setFixedSize( 80, 20 );
    currentChannelLineEdit -> setText( tr( "n/a" ) );
    currentChannelLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    currentChannelLineEdit -> setReadOnly( 1 );

    workModeLabel = new QLabel( tr( "工作模式" ) );
    workModeLabel -> setStyleSheet( "background-color:#228B22;" );
    workModeLabel -> setFixedSize( 80, 20 );
    workModeLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    workModeLineEdit = new QLineEdit();
    workModeLineEdit -> setFont(QFont("Timers", 8));
    workModeLineEdit -> setFixedSize( 80, 20 );
    workModeLineEdit -> setText( tr( "n/a" ) );
    workModeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    workModeLineEdit -> setReadOnly( 1 );

    workStatusLabel = new QLabel( tr( "工作状态" ) );
    workStatusLabel -> setStyleSheet( "background-color:#228B22;" );
    workStatusLabel -> setFixedSize( 80, 20 );
    workStatusLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    workStatusLineEdit = new QLineEdit();
    workStatusLineEdit -> setFont(QFont("Timers", 8));
    workStatusLineEdit -> setFixedSize( 80, 20 );
    workStatusLineEdit -> setText( tr( "n/a" ) );
    workStatusLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    workStatusLineEdit -> setReadOnly( 1 );

    iriTimeLabel = new QLabel( tr( "铱星时间" ) );
    iriTimeLabel -> setStyleSheet( "background-color:#228B22;" );
    iriTimeLabel -> setFixedSize( 80, 20 );
    iriTimeLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    iriTimeLineEdit = new QLineEdit();
    iriTimeLineEdit -> setFont(QFont("Timers", 8));
    iriTimeLineEdit -> setFixedSize( 80, 20 );
    iriTimeLineEdit -> setText( tr( "n/a" ) );
    iriTimeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    iriTimeLineEdit -> setReadOnly( 1 );

    dataRefreshBtn = new QPushButton( tr( "刷新\n数据" ) );
    dataRefreshBtn -> setFixedSize( 68, 45 );
    dataRefreshBtn -> setStyleSheet( "background-color:#f1c232;" );
    connect( dataRefreshBtn, SIGNAL( clicked(bool) ), this, SLOT( dataRefreshBtnClicked() ) );

    dataMonitorGrid -> addWidget( robotLabel, 0, 0, 1, 2 );
    dataMonitorGrid -> addWidget( robotLineEdit, 0, 2, 1, 2 );
    dataMonitorGrid -> addWidget( lngLatitudeLabel, 0, 4, 1, 2 );
    dataMonitorGrid -> addWidget( longitudeLineEdit, 0, 6, 1, 1 );
    dataMonitorGrid -> addWidget( latitudeLineEdit, 0, 7, 1, 1 );

    dataMonitorGrid -> addWidget( emergencyStatusLabel, 1, 0, 1, 2 );
    dataMonitorGrid -> addWidget( emergencyStatusLineEdit, 1, 2, 1, 2 );
    dataMonitorGrid -> addWidget( gpsLngLatitudeLabel, 1, 4, 1, 2 );
    dataMonitorGrid -> addWidget( gpsLongitudeLineEdit, 1, 6, 1, 1 );
    dataMonitorGrid -> addWidget( gpsLatitudeLineEdit, 1, 7, 1, 1 );

    dataMonitorGrid -> addWidget( counterLabel, 2, 0, 1, 2 );
    dataMonitorGrid -> addWidget( counterLineEdit, 2, 2, 1, 2 );
    dataMonitorGrid -> addWidget( startLngLatitudeLabel, 2, 4, 1, 2 );
    dataMonitorGrid -> addWidget( startLongitudeLineEdit, 2, 6, 1, 1 );
    dataMonitorGrid -> addWidget( startLatitudeLineEdit, 2, 7, 1, 1 );

    dataMonitorGrid -> addWidget( timeLabel, 3, 0, 1, 2 );
    dataMonitorGrid -> addWidget( timeLineEdit, 3, 2, 1, 2 );
    dataMonitorGrid -> addWidget( iriLngLatitudeLabel, 3, 4, 1, 2 );
    dataMonitorGrid -> addWidget( iriLongitudeLineEdit, 3, 6, 1, 1 );
    dataMonitorGrid -> addWidget( iriLatitudeLineEdit, 3, 7, 1, 1 );

    dataMonitorGrid -> addWidget( iriTimeLabel, 4, 0, 1, 2 );
    dataMonitorGrid -> addWidget( iriTimeLineEdit, 4, 2, 1, 2 );
    dataMonitorGrid -> addWidget( xyCoordinateLabel, 4, 4, 1, 2 );
    dataMonitorGrid -> addWidget( xCoordinateLineEdit, 4, 6, 1, 1 );
    dataMonitorGrid -> addWidget( yCoordinateLineEdit, 4, 7, 1, 1 );

    dataMonitorGrid -> addWidget( gpsSatelliteLabel, 5, 0, 1, 2 );
    dataMonitorGrid -> addWidget( gpsSatelliteLineEdit, 5, 2, 1, 2 );
    dataMonitorGrid -> addWidget( cellTemperatureLabel, 5, 4, 1, 2 );
    dataMonitorGrid -> addWidget( cellTemperatureLineEdit, 5, 6, 1, 2 );

    dataMonitorGrid -> addWidget( gpsSignalLabel, 6, 0, 1, 2 );
    dataMonitorGrid -> addWidget( gpsSignalLineEdit, 6, 2, 1, 2 );
    dataMonitorGrid -> addWidget( pcTemperatureLabel, 6, 4, 1, 2 );
    dataMonitorGrid -> addWidget( pcTemperatureLineEdit, 6, 6, 1, 2 );

    dataMonitorGrid -> addWidget( workModeLabel, 7, 0, 1, 2 );
    dataMonitorGrid -> addWidget( workModeLineEdit, 7, 2, 1, 2 );
    dataMonitorGrid -> addWidget( cabinTemperatureLabel, 7, 4, 1, 2 );
    dataMonitorGrid -> addWidget( cabinTemperatureLineEdit, 7, 6, 1, 2 );

    dataMonitorGrid -> addWidget( workStatusLabel, 8, 0, 1, 2 );
    dataMonitorGrid -> addWidget( workStatusLineEdit, 8, 2, 1, 2 );
    dataMonitorGrid -> addWidget( cabinHumidityLabel, 8, 4, 1, 2 );
    dataMonitorGrid -> addWidget( cabinHumidityLineEdit, 8, 6, 1, 2 );

    dataMonitorGrid -> addWidget( currentChannelLabel, 9, 0, 1, 2 );
    dataMonitorGrid -> addWidget( currentChannelLineEdit, 9, 2, 1, 2 );
    dataMonitorGrid -> addWidget( cabinPressureLabel, 9, 4, 1, 2 );
    dataMonitorGrid -> addWidget( cabinPressureLineEdit, 9, 6, 1, 2 );

    dataMonitorGrid -> addWidget( headLeakLabel, 10, 0, 1, 2 );
    dataMonitorGrid -> addWidget( headLeakLineEdit, 10, 2, 1, 2 );
    dataMonitorGrid -> addWidget( batteryOneLabel, 10, 4, 1, 2 );
    dataMonitorGrid -> addWidget( batteryOneVoltageLineEdit, 10, 6, 1, 1 );
    dataMonitorGrid -> addWidget( batteryOneCurrentLineEdit, 10, 7, 1, 1 );

    dataMonitorGrid -> addWidget( backLeakLabel, 11, 0, 1, 2 );
    dataMonitorGrid -> addWidget( backLeakLineEdit, 11, 2, 1, 2 );
    dataMonitorGrid -> addWidget( batteryTwoLabel, 11, 4, 1, 2 );
    dataMonitorGrid -> addWidget( batteryTwoVoltageLineEdit, 11, 6, 1, 1 );
    dataMonitorGrid -> addWidget( batteryTwoCurrentLineEdit, 11, 7, 1, 1 );

    dataMonitorGrid -> addWidget( tailLeakLabel, 12, 0, 1, 2 );
    dataMonitorGrid -> addWidget( tailLeakLineEdit, 12, 2, 1, 2 );
    dataMonitorGrid -> addWidget( motorLabel, 12, 4, 1, 2 );
    dataMonitorGrid -> addWidget( motorVoltageLineEdit, 12, 6, 1, 1 );
    dataMonitorGrid -> addWidget( motorCurrentLineEdit, 12, 7, 1, 1 );

    dataMonitorGrid -> addWidget( cabinDewPointLabel, 13, 0, 1, 2 );
    dataMonitorGrid -> addWidget( cabinDewPointLineEdit, 13, 2, 1, 2 );
    dataMonitorGrid -> addWidget( motorSpeedLabel, 13, 4, 1, 2 );
    dataMonitorGrid -> addWidget( motorSpeedLineEdit, 13, 6, 1, 1 );
    dataMonitorGrid -> addWidget( dataRefreshBtn, 13, 7, 2, 1 );

    dataMonitorGrid -> addWidget( groundMonitorLabel, 14, 0, 1, 2 );
    dataMonitorGrid -> addWidget( groundMonitorLineEdit, 14, 2, 1, 2 );
    dataMonitorGrid -> addWidget( motorDirectionLabel, 14, 4, 1, 2 );
    dataMonitorGrid -> addWidget( motorDirectionLineEdit, 14, 6, 1, 1 );

    dataMonitorDock = new QDockWidget( tr( "数据监测" ), this );
    /*
    QPalette pa_bg_2;
    pa_bg_2.setColor(QPalette::Background, QColor(217,217,217));
    dataMonitorDock -> setAutoFillBackground(true);
    dataMonitorDock -> setPalette(pa_bg_2);
    */
   // dataMonitorDock -> setStyleSheet( "background-color:#d9d9d9;" );
    dataMonitorDock -> setFeatures( QDockWidget::AllDockWidgetFeatures );
    dataMonitorDock -> setAllowedAreas( Qt::LeftDockWidgetArea);
    dataMonitorDock -> setWidget( dataMonitorWidget );
    addDockWidget( Qt::LeftDockWidgetArea, dataMonitorDock );

}

//创建地图显示窗口
void MainWindow::createMapDock()
{
    mapDialog = new MapDialog();
    mapDialog -> setFixedSize( 900, 660 );
    mapDock = new QDockWidget( tr( "地图" ), this );
    /*
    QPalette pa_bg_3;
    pa_bg_3.setColor(QPalette::Background, QColor(217,217,217));
    mapDock -> setAutoFillBackground(true);
    mapDock -> setPalette(pa_bg_3);
    */
    mapDock -> setStyleSheet( "background-color:#d9d9d9;" );
    mapDock -> setFeatures( QDockWidget::AllDockWidgetFeatures );
//  mapDock -> setAllowedAreas( Qt::AllDockWidgetAreas );
    mapDock -> setWidget( mapDialog );
    setCentralWidget( mapDock );
//  addDockWidget( Qt::RightDockWidgetArea, mapDock );
}

void MainWindow::userDefinedMenuChecked( QAction *act )
{
    if( act -> text() == "告警信息窗口" )
    {
        if( warningAction -> isChecked() )
        {
            /*
            warningDock = new QDockWidget( tr( "告警信息" ), this );
            warningDock -> setStyleSheet( "background-color:#d9d9d9;" );
            warningDock -> setFeatures( QDockWidget::AllDockWidgetFeatures );  //窗口可移动可关闭
            warningDock -> setAllowedAreas( Qt::LeftDockWidgetArea );
            warningDock -> setWidget( warningWidget );
            addDockWidget( Qt::LeftDockWidgetArea, warningDock );
            */
            createWarningDock();
            warningAction -> setChecked( 1 );
        }
        else
        {
            warningDock -> close();
            warningAction -> setChecked( 0 );
        }
    }
    else if( act -> text() == "设备监测窗口" )
    {
        if( statusAction -> isChecked() )
        {
            /*
            statusMonitorDock = new QDockWidget( tr( "设备监测" ), this );
            statusMonitorDock -> setStyleSheet( "background-color:#d9d9d9;" );
            statusMonitorDock -> setFeatures( QDockWidget::AllDockWidgetFeatures );
            statusMonitorDock -> setAllowedAreas( Qt::LeftDockWidgetArea );
            statusMonitorDock -> setWidget( statusMonitorWidget );
            addDockWidget( Qt::LeftDockWidgetArea, statusMonitorDock );
            */
            createStatusMonitorDock();
            statusAction -> setChecked( 1 );
        }
        else
        {
            statusMonitorDock -> close();
            statusAction -> setChecked( 0 );
        }
    }
    else if( act -> text() == "数据监测窗口" )
    {
        if( dataAction -> isChecked() )
        {
            /*
            dataMonitorDock = new QDockWidget( tr( "数据监测" ), this );
            dataMonitorDock -> setStyleSheet( "background-color:#d9d9d9;" );
            dataMonitorDock -> setFeatures( QDockWidget::AllDockWidgetFeatures );
            dataMonitorDock -> setAllowedAreas( Qt::LeftDockWidgetArea);
            dataMonitorDock -> setWidget( dataMonitorWidget );
            addDockWidget( Qt::LeftDockWidgetArea, dataMonitorDock );
            */
            createDataMonitorDock();
            dataAction -> setChecked( 1 );
        }
        else
        {
            dataMonitorDock -> close();
            dataAction -> setChecked( 0 );
        }
    }
    else if( act -> text() == "实时图表窗口" )
    {
        if( chartAction -> isChecked() )
        {
            plotDlg = new customplotDlg( );
            plotDlg -> show();
            plotDlg -> setFixedSize( 1150, 500 );
            chartAction -> setChecked( 1 );
        }
        else
        {
            plotDlg -> setVisible( 0 );
            chartAction -> setChecked( 0 );
        }
    }
    else if( act -> text() == "地图显示窗口" )
    {
        if( mapAction -> isChecked() )
        {
            /*
            mapDock = new QDockWidget( tr( "地图" ), this );
            mapDock -> setStyleSheet( "background-color:#d9d9d9;" );
            mapDock -> setFeatures( QDockWidget::AllDockWidgetFeatures );
            mapDock -> setAllowedAreas( Qt::RightDockWidgetArea );
            mapDock -> setWidget( mapDialog );
            addDockWidget( Qt::RightDockWidgetArea, mapDock );
            */
            createMapDock();
            mapAction -> setChecked( 1 );
        }
        else
        {
            mapDock -> close();
            mapAction -> setChecked( 0 );
        }
    }
}

//"设备监测"刷新按钮槽信号
void MainWindow::refreshBtnClicked()
{
    ahrsLabel -> setStyleSheet( "background-color:#228B22;" );
    insLabel -> setStyleSheet( "background-color:#228B22;" );
    firNetLabel -> setStyleSheet( "background-color:#228B22;" );
    canLabel -> setStyleSheet( "background-color:#228B22;" );
    ipsLabel -> setStyleSheet( "background-color:#228B22;" );
    gpsLabel -> setStyleSheet( "background-color:#228B22;" );
    dvlLabel -> setStyleSheet( "background-color:#228B22;" );
    sonarLabel -> setStyleSheet( "background-color:#228B22;" );
    secNetLabel -> setStyleSheet( "background-color:#228B22;" );
    handleLabel -> setStyleSheet( "background-color:#228B22;" );
    ahrsLineEdit -> setText( tr( "n/a" ) );
    insLineEdit -> setText( tr( "n/a" ) );
    firNetLineEdit -> setText( tr( "n/a" ) );
    canLineEdit -> setText( tr( "n/a" ) );
    ipsLineEdit -> setText( tr( "n/a" ) );
    gpsLineEdit -> setText( tr( "n/a" ) );
    dvlLineEdit -> setText( tr( "n/a" ) );
    sonarLineEdit -> setText( tr( "n/a" ) );
    secNetLineEdit -> setText( tr( "n/a" ) );
    handleLineEdit -> setText( tr( "n/a" ) );

}

//"数据监测"刷新按钮槽信号
void MainWindow::dataRefreshBtnClicked()
{
    robotLineEdit -> setText( tr( "n/a" ) );
    emergencyStatusLineEdit -> setText( tr( "n/a" ) );
    latitudeLineEdit -> setText( tr( "n/a" ) );
    longitudeLineEdit -> setText( tr( "n/a" ) );
    xCoordinateLineEdit -> setText( tr( "n/a" ) );
    yCoordinateLineEdit -> setText( tr( "n/a" ) );
    gpsLatitudeLineEdit -> setText( tr( "n/a" ) );
    gpsLongitudeLineEdit -> setText( tr( "n/a" ) );
    gpsSatelliteLineEdit -> setText( tr( "n/a" ) );
    gpsSignalLineEdit -> setText( tr( "n/a" ) );
    batteryOneCurrentLineEdit -> setText( tr( "n/a" ) );
    batteryOneVoltageLineEdit -> setText( tr( "n/a" ) );
    batteryTwoCurrentLineEdit -> setText( tr( "n/a" ) );
    batteryTwoVoltageLineEdit -> setText( tr( "n/a" ) );
    cellTemperatureLineEdit -> setText( tr( "n/a" ) );
    pcTemperatureLineEdit -> setText( tr( "n/a" ) );
    cabinTemperatureLineEdit -> setText( tr( "n/a" ) );
    cabinHumidityLineEdit -> setText( tr( "n/a" ) );
    cabinDewPointLineEdit -> setText( tr( "n/a" ) );
    cabinPressureLineEdit -> setText( tr( "n/a" ) );
    motorVoltageLineEdit -> setText( tr( "n/a" ) );
    motorCurrentLineEdit -> setText( tr( "n/a" ) );
    motorSpeedLineEdit -> setText( tr( "n/a" ) );
    motorDirectionLineEdit -> setText( tr( "n/a" ) );
    headLeakLineEdit -> setText( tr( "n/a" ) );
    backLeakLineEdit -> setText( tr( "n/a" ) );
    tailLeakLineEdit -> setText( tr( "n/a" ) );
    groundMonitorLineEdit -> setText( tr( "n/a" ) );
    startLatitudeLineEdit -> setText( tr( "n/a" ) );
    startLongitudeLineEdit -> setText( tr( "n/a" ) );
    iriLatitudeLineEdit -> setText( tr( "n/a" ) );
    iriLongitudeLineEdit -> setText( tr( "n/a" ) );
    iriTimeLineEdit -> setText( tr( "n/a" ) );
    currentChannelLineEdit -> setText( tr( "n/a" ) );
    workModeLineEdit -> setText( tr( "n/a" ) );
    workStatusLineEdit -> setText( tr( "n/a" ) );

    robotLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    emergencyStatusLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    latitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    longitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    xCoordinateLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    yCoordinateLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    gpsLatitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    gpsLongitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    gpsSatelliteLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    gpsSignalLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    batteryOneCurrentLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    batteryOneVoltageLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    batteryTwoCurrentLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    batteryTwoVoltageLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    cellTemperatureLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    pcTemperatureLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    cabinTemperatureLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    cabinHumidityLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    cabinDewPointLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    cabinPressureLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    motorVoltageLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    motorCurrentLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    motorSpeedLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    motorDirectionLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    headLeakLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    backLeakLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    tailLeakLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    groundMonitorLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    startLatitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    startLongitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    iriLatitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    iriLongitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    iriTimeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    currentChannelLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    workModeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
    workStatusLineEdit -> setStyleSheet( "background-color:#fff2cc;" );

}

//开启时间显示
void MainWindow::startTime()
{

    QTimer *timer = new QTimer( this );
    timer -> start( 1000 );
    connect( timer, SIGNAL( timeout() ), this, SLOT( showTime() ) );

}

//开启计时器
void MainWindow::startCounter()
{
    countTemp = 0;
    secTemp = 0;
    minTemp = 0;
    hourTemp = 0;
    QTimer *count = new QTimer( this );
    count -> start( 100 );
    connect( count, SIGNAL( timeout() ), this, SLOT( counter() ) );
}

//时间显示槽信号
void MainWindow::showTime()
{
    timeLineEdit -> setText( QTime::currentTime().toString( "hh:mm:ss" ) );
}

//计数器槽信号
void MainWindow::counter()
{
    countTemp += 1;
    if( countTemp == 10 )
    {
        countTemp = 0;
        secTemp += 1;
        if( secTemp == 60 )
        {
            secTemp = 0;
            minTemp += 1;
            if( minTemp == 60 )
            {
                minTemp = 0;
                hourTemp += 1;
            }
        }
    }
    QString hourstr = QString::number( hourTemp );
    QString minstr = QString::number( minTemp );
    QString secstr = QString::number( secTemp );
    QString countstr = QString::number( countTemp );
    QString temp = hourstr + ":" + minstr + ":" + secstr + ":" + countstr;
    counterLineEdit -> setText( temp );
}

//创建配置窗口
void MainWindow::createConfigureDlg()
{
    //configuredlg = new configureDlg( this );
    configuredlg.show();
}

//创建调试窗口
void MainWindow::createDebugDlg()
{
    //debugdlg = new DebugDlg( this );
    debugdlg.show();
}

void MainWindow::MissionMenuClicked( QAction *act )
{
    if( act -> text() == "起点视野设置" )
    {
        startAndViewDlg.show();
    }
    else if( act -> text() == "使命参数设置" )
    {
        missionParaDlg.setFixedWidth( 800 );
        missionParaDlg.show();
    }
    else if( act -> text() == "路径规划设置" )
    {
        pathPlanningDlg.show();
    }
}

//"传感器"菜单栏槽信号
void MainWindow::sensorMenuClicked(QAction *act)
{
    if( act -> text() == "USBL上电" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "USBL" ),  tr( "确认USBL上电？" ),
                                            QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=sensor;Type=usbl;Power=on");
            pushPending("USBL_AUTO_FLAG","FALSE");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "USBL下电" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "USBL" ),  tr( "确认USBL下电？" ),
                                            QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=sensor;Type=usbl;Power=off");
            pushPending("USBL_AUTO_FLAG","FALSE");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "USBL自控" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "USBL" ),  tr( "确认USBL自控？" ),
                                            QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("USBL_AUTO_FLAG","TRUE");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "DVL上电" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "DVL" ),  tr( "确认DVL上电？" ),
                                            QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=sensor;Type=dvl;Power=on");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "DVL下电" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "DVL" ),  tr( "确认DVL下电？" ),
                                            QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=sensor;Type=dvl;Power=off");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "抛载上电" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "抛载" ),  tr( "确认抛载上电？" ),
                                            QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=sensor;Type=ballast;Power=on");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "抛载下电" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "抛载" ),  tr( "确认抛载下电？" ),
                                            QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=sensor;Type=ballast;Power=off");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "LED上电" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "LED" ),  tr( "确认LED上电？" ),
                                            QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=sensor;Type=led;Power=on");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "LED下电" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "LED" ),  tr( "确认LED下电？" ),
                                            QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=sensor;Type=led;Power=off");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "惯导上电" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "惯导" ),  tr( "确认惯导上电？" ),
                                            QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=sensor;Type=ins;Power=on");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "惯导下电" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "惯导" ),  tr( "确认惯导下电？" ),
                                            QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=sensor;Type=ins;Power=off");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "推进器电源上电" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "推进器电源" ),  tr( "确认推进器电源上电？" ),
                                            QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=sensor;Type=depth;Power=on");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
        else if( act -> text() == "推进器电源下电" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "推进器电源" ),  tr( "确认推进器电源下电？" ),
                                            QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=sensor;Type=depth;Power=off");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "AHRS上电" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "AHRS" ),  tr( "确认AHRS上电？" ),
                                            QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=sensor;Type=ahrs;Power=on");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "AHRS下电" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "AHRS" ),  tr( "确认AHRS下电？" ),
                                            QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=sensor;Type=ahrs;Power=off");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
}

//"控制"菜单栏槽信号
void MainWindow::controlMenuClicked(QAction *act)
{
    if( act -> text() == "开导航" )
    {
        if( bCalibStatus )
        {
            QMessageBox::about(NULL, "警告", "<font color='red'>纠偏中，请先取消纠偏</font>");
        }
        else if( !bDvlStatus )
        {
            QMessageBox::about(NULL, "警告", "<font color='red'>请先打开DVL</font>");
        }
        else
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, tr( "导航" ),  tr( "确认开导航？" ),
                                            QMessageBox::Yes | QMessageBox::No );
            if( reply == QMessageBox::Yes )
            {
                pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=navstart");
                bNavstart = true;
                bCalibStatus = false;
            }
            else if( reply == QMessageBox::No )
            {
                return;
            }
        }
    }
    else if( act -> text() == "关导航" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "导航" ),  tr( "确认关闭导航？" ),
                                        QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=navstop");
            bNavstart = false;
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "开始" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "开始" ),  tr( "确认开始？" ),
                                        QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=start");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "启航" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "启航" ),  tr( "确认启航？" ),
                                        QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=drive");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "暂停" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "暂停" ),  tr( "确认暂停？" ),
                                        QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=pause");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "继续" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "继续" ),  tr( "确认继续？" ),
                                        QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=continue");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "上浮" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "上浮" ),  tr( "确认上浮？" ),
                                        QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=float");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "返回" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "返回" ),  tr( "确认返回？" ),
                                        QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=return");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "停止运动" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "停止" ),  tr( "确认停止？" ),
                                        QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=stopall");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "打开侧扫" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "侧扫" ),  tr( "确认打开侧扫？" ),
                                        QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=SIDESCAN_WORK");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "关闭侧扫" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "侧扫" ),  tr( "确认关闭侧扫？" ),
                                        QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=SIDESCAN_CLOSE");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "开始纠偏" )
    {
        if( bNavstart )
        {
            QMessageBox::about(NULL, "警告", "<font color='red'>正在导航中，若要继续请先关闭导航</font>");
        }
        else if( bCalibStatus )
        {
            QMessageBox::about(NULL, "警告", "<font color='red'>正在纠偏中，重复的操作</font>");
        }
        else
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, tr( "纠偏" ),  tr( "确认开始纠偏？" ),
                                            QMessageBox::Yes | QMessageBox::No );
            if( reply == QMessageBox::Yes )
            {
                pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=YAW_CALIB_START");
            }
            else if( reply == QMessageBox::No )
            {
                return;
            }
        }
    }
    else if( act -> text() == "完成纠偏" )
    {
        if( !bCalibStatus )
        {
            QMessageBox::about(NULL, "警告", "<font color='red'>未纠偏，操作无效</font>");
        }
        else
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, tr( "纠偏" ),  tr( "确认完成纠偏？" ),
                                            QMessageBox::Yes | QMessageBox::No );
            if( reply == QMessageBox::Yes )
            {
                pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=YAW_CALIB_END");
                bCalibStatus = false;
            }
            else if( reply == QMessageBox::No )
            {
                return;
            }
        }
    }
    else if( act -> text() == "取消纠偏" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "纠偏" ),  tr( "确认取消纠偏？" ),
                                        QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=YAW_CALIB_CANCEL");
            bCalibStatus = false;
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "关闭主控电脑" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "主控电脑" ),  tr( "确认关闭主控电脑？" ),
                                        QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=poweroffpc");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
    else if( act -> text() == "重启主控电脑" )
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr( "主控电脑" ),  tr( "确认重启主控电脑？" ),
                                        QMessageBox::Yes | QMessageBox::No );
        if( reply == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONTROL_MESSAGE","MsgType=control;Act=rebootpc");
        }
        else if( reply == QMessageBox::No )
        {
            return;
        }
    }
}


//应急设置菜单槽信号
void MainWindow::EmergencyMenuClicked( QAction *act )
{
    if( act -> text() == "应急参数设置" )
    {
        emergencyParaDlg.show();
    }
    else if( act -> text() == "任务计时开始" )
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::question( this, tr("任务计时"), QString(tr("确认开始任务计时")),
                                        QMessageBox::Yes | QMessageBox::No );
        if( button == QMessageBox::No )
        {
            return;
        }
        else if( button == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONFIG_MESSAGE","MsgType=prov;Task_Timing=true");
        }
    }
    else if( act -> text() == "任务计时结束" )
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::question( this, tr("任务计时"), QString(tr("确认结束任务计时")),
                                        QMessageBox::Yes | QMessageBox::No );
        if( button == QMessageBox::No )
        {
            return;
        }
        else if( button == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONFIG_MESSAGE","MsgType=prov;Task_Timing=false");
        }
    }
    else if( act -> text() == "应急告警显示" )
    {
        emergencyShowDlg.show();
        emergencyShowDlg.setFixedWidth( 1000 );
    }
    else if( act -> text() == "清除应急告警" )
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::question( this, tr("应急告警"), QString(tr("确认清除应急告警")),
                                        QMessageBox::Yes | QMessageBox::No );
        if( button == QMessageBox::No )
        {
            return;
        }
        else if( button == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONFIG_MESSAGE","MsgType=prov;clear_emer_msg=true");
        }
    }
    else if( act -> text() == "打开应急告警" )
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::question( this, tr("应急告警"), QString(tr("确认打开应急告警")),
                                        QMessageBox::Yes | QMessageBox::No );
        if( button == QMessageBox::No )
        {
            return;
        }
        else if( button == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONFIG_MESSAGE","MsgType=prov;disable_emer=false");
        }
    }
    else if( act -> text() == "关闭应急告警" )
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::question( this, tr("应急告警"), QString(tr("确认关闭应急告警")),
                                        QMessageBox::Yes | QMessageBox::No );
        if( button == QMessageBox::No )
        {
            return;
        }
        else if( button == QMessageBox::Yes )
        {
            pushPending("UVL_SHORE_CONFIG_MESSAGE","MsgType=prov;disable_emer=true");
        }
    }
}

//通信通道菜单槽信号
void MainWindow::comChannelMenuClicked(QAction *act)
{
    bool bWiredOrWirdlessComms = false;
    bool bIridiumCommsChg = false;
    bool bUSBLCommsChg = false;
    std::string sValue = "";
    if( act -> text() == "有线网络" )
    {
        if( wiredEnable )
        {
            wiredNetAction -> setChecked( 0 );
            wirelessNetAction -> setChecked( 1 );
            sValue = "Wireless;";
            wiredEnable = false;
            wirelessEnable = true;
        }
        else
        {
            wiredNetAction -> setChecked( 1 );
            wirelessNetAction -> setChecked( 0 );
            sValue = "Wired;";
            wiredEnable = true;
            wirelessEnable = false;
        }
        bWiredOrWirdlessComms = true;
    }
    else if( act -> text() == "无线网络" )
    {
        if( wirelessEnable )
        {
            wiredNetAction -> setChecked( 1 );
            wirelessNetAction -> setChecked( 0 );
            sValue = "Wired;";
            wiredEnable = true;
            wirelessEnable = false;
        }
        else
        {
            wiredNetAction -> setChecked( 0 );
            wirelessNetAction -> setChecked( 1 );
            sValue = "Wireless;";
            wiredEnable = false;
            wirelessEnable = true;
        }
        bWiredOrWirdlessComms = true;
    }
    else if( act -> text() == "铱星系统" )
    {
        if( iridiumEnable )
        {
            iriSystemAction -> setChecked( 0 );
            iridiumEnable = false;
        }
        else
        {
            iriSystemAction -> setChecked( 1 );
            iridiumEnable = true;
        }
        bIridiumCommsChg = true;
    }
    else if( act -> text() == "USBL设备" )
    {
        if( usblEnable )
        {
            usblEquipmentAction -> setChecked( 0 );
            usblEnable = false;
        }
        else
        {
            usblEquipmentAction -> setChecked( 1 );
            usblEnable = true;
        }
        bUSBLCommsChg = true;
    }


    if( bWiredOrWirdlessComms )
    {
        pushPending( "SEL_CHANN_FROM_GUI", sValue );
    }
    if( bUSBLCommsChg )
    {
        if( usblEnable )
        {
            pushPending("USBLEnable", "true");
        }
        else
        {
            pushPending("USBLEnable", "false");
        }
    }
    if( bIridiumCommsChg )
    {
        if( iridiumEnable )
        {
            pushPending("IridiumEnable", "true");
        }
        else
        {
            pushPending("IridiumEnable", "false");
        }
    }
}

void MainWindow::channelshow()
{
    std::string sComms = "";
    if( wiredEnable )
    {
        sComms = "有线";
        pushPending("SEL_CHANN_FROM_GUI", "Wired;");
    }
    if( wirelessEnable )
    {
       if(sComms != "")
       {
           sComms = sComms + ",无线";
       }
       else
       {
           sComms = "无线";
       }
       pushPending("SEL_CHANN_FROM_GUI", "Wireless;");
    }

    if ( iridiumEnable )
    {
       if(sComms != "")
       {
           sComms = sComms + ",铱星";
       }
       else
       {
           sComms = "铱星";
       }
       pushPending("IridiumEnable", "true");
    }
    else
    {
       pushPending("IridiumEnable", "false");
    }

    if( usblEnable )
    {
       if(sComms != "")
       {
           sComms = sComms + ",USBL";
       }
       else
       {
           sComms = "USBL";
       }
       pushPending("USBLEnable", "true");
    }
    else
    {
        pushPending("USBLEnable", "false");
    }
    currentChannelLineEdit -> setText( sComms.c_str() );
}


//手柄控制菜单槽信号
void MainWindow::handleMenuClicked(QAction *act)
{
    if( act -> text() == "默认模式" )
    {
        pushPending("JOYSTICK_MODE", "mode=default");
        joystickMode = "默认手";
    }
    else if( act -> text() == "航向控制" )
    {
        pushPending("JOYSTICK_MODE", "mode=courseCtl");
        joystickMode = "航向手";
    }
    else if( act -> text() == "美国手柄" )
    {
        pushPending("JOYSTICK_MODE", "mode=america");
        joystickMode = "美国手";
    }
    else if( act -> text() == "日本手柄" )
    {
        pushPending("JOYSTICK_MODE", "mode=japan");
        joystickMode = "日本手";
    }
}

//进程管理菜单槽信号
void MainWindow::processManagerClicked( QAction *act )
{
    if( act -> text() == "启动应用进程" )
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::question( this, tr("进程管理"), QString(tr("确认启动应用进程？")),
                                        QMessageBox::Yes | QMessageBox::No );
        if( button == QMessageBox::No )
        {
            return;
        }
        else if( button == QMessageBox::Yes )
        {
            pushPending("PROCESS_MANAGEMENT", "flag=0");
        }
    }
    else if( act -> text() == "关闭应用进程" )
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::question( this, tr("进程管理"), QString(tr("确认关闭应用进程？")),
                                        QMessageBox::Yes | QMessageBox::No );
        if( button == QMessageBox::No )
        {
            return;
        }
        else if( button == QMessageBox::Yes )
        {
            pushPending("PROCESS_MANAGEMENT", "flag=1");
        }
    }
    else if( act -> text() == "关闭所有进程" )
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::question( this, tr("进程管理"), QString(tr("确认关闭所有进程?")),
                                        QMessageBox::Yes | QMessageBox::No );
        if( button == QMessageBox::No )
        {
            return;
        }
        else if( button == QMessageBox::Yes )
        {
            pushPending("PROCESS_MANAGEMENT", "flag=2");
        }
    }
    else if( act -> text() == "关进程并关机" )
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::question( this, tr("进程管理"), QString(tr("确认关进程并关机？")),
                                        QMessageBox::Yes | QMessageBox::No );
        if( button == QMessageBox::No )
        {
            return;
        }
        else if( button == QMessageBox::Yes )
        {
            pushPending("PROCESS_MANAGEMENT", "flag=3");
        }
    }
}

//-------------------------------------------------------------------
// Procedure: getPendingVar

std::string MainWindow::getPendingVar(unsigned int ix)
{
    if(ix < m_pending_vars.size())
    {
        return(m_pending_vars[ix]);
    }
    else
    {
        return("");
    }
}



//-------------------------------------------------------------------
// Procedure: getPendingVal

std::string MainWindow::getPendingVal(unsigned int ix)
{
    if(ix < m_pending_vals.size())
    {
        return(m_pending_vals[ix]);
    }
    else
    {
        return("");
    }
}



//-------------------------------------------------------------------
// Procedure: clearPending

void MainWindow::clearPending()
{
    m_pending_vars.clear();
    m_pending_vals.clear();
}


//-------------------------------------------------------------------
// Procedure: pushPending

void MainWindow::pushPending(std::string var, std::string val)
{
    m_pending_vars.push_back(var);
    m_pending_vals.push_back(val);
}


void MainWindow::calibStatus( std::string svalue )
{
    std::vector<std::string> svec = parseString(svalue, ';');
    unsigned int size = svec.size();
    if( size <= 0 )
    { return; }
    else if( size == 2 )
    {
       std::string temp = biteString( svec[0], '=' );
       std::string calib_status = svec[0];
       std::string tmp = biteString( svec[1], '=' );
       std::string calib_deflection = svec[1];
       if( calib_status == "START" )
       {
           bCalibStatus = true;
          QMessageBox::about(NULL, "提示", tr("纠偏开始\n偏角为 %1 度").arg( calib_deflection.c_str() ));
          return;
       }
       else if( calib_status == "END" )
       {
          bCalibStatus = false;
          QMessageBox::about(NULL, "提示", tr("纠偏结束\n偏角为 %1 度").arg( calib_deflection.c_str() ));
          return;
       }
       else if( calib_status == "CANCEL" )
       {
          bCalibStatus = false;
          QMessageBox::about(NULL, "提示", tr("纠偏取消\n偏角为 %1 度").arg( calib_deflection.c_str() ));
          return;
       }
       else if( calib_status == "GPSInvalid" )
       {
          bCalibStatus = false;
          QMessageBox::about(NULL, "警告", tr("<font color='red'>GPS无效</font>"));
          return;
       }
    }
    else
    {
         QMessageBox::about(NULL, "警告", "<font color='red'>纠偏数据异常</font>");
         return;
    }
}


void MainWindow::displayForSensor(std::string svalue)
{
    std::vector<std::string> svec = parseString(svalue, ';');
    unsigned int size = svec.size();
    if( size <= 0 )
    {
        return;
    }
    else
    {
        std::string type_name = stripBlankEnds(biteString(svec[0], '='));
        std::string type = stripBlankEnds(svec[0]);
        if( type == "dvl" )
        {
            std::string name = stripBlankEnds(biteString(svec[1], '='));
            std::string value = stripBlankEnds(svec[1]);
            if( name == "status" )
            {
                if( value == "0" )
                {
                    bDvlStatus = false;
                }
                else if( value == "1" )
                {
                    bDvlStatus = true;
                }
            }
        }
        else if( type == "ins" )
        {

            std::string name = stripBlankEnds(biteString(svec[1], '='));
            std::string value = stripBlankEnds(svec[1]);
            if( name == "status" )
            {
                if( value == "0" )
                {
                    insLineEdit -> setText( tr("等待对准") );
                }
                else if( value == "1" )
                {
                    insLineEdit -> setText( tr("粗对准") );
                }
                else if( value == "2" )
                {
                    insLineEdit -> setText( tr("精对准") );
                }
                else if( value == "3" )
                {
                    insLineEdit -> setText( tr("导航") );
                }
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }

    }
}


void MainWindow::warningBox( std::string svalue )
{
    bWarningBox = true;
    int size_type;
    std::vector<std::string> svec = parseString( svalue, ';' );
    unsigned int size = svec.size();
    if( size == 0 )
    {
        return;
    }

    size_type = svec.size();

    std::map<std::string,std::string> mapMsgItems;
    int v_index = 0;
    for( v_index = 0; v_index < svec.size(); v_index++ )
    {
        std::string key = stripBlankEnds( biteString(svec[v_index],'=') );
        std::string value = stripBlankEnds( svec[v_index] );
        if( key != "" )
        {
            key = toupper( key );
            mapMsgItems[key] = value;
        }
    }

    std::map<std::string,std::string>::iterator mapIter;
    mapIter = mapMsgItems.find( "ID" );
    if( mapIter == mapMsgItems.end() )
    {
        return;
    }

    std::string id_value = mapIter -> second;
    int Id_Value = atoi( id_value.c_str() );
    std::map<std::string,double>::iterator iter;

    if( isNumber( id_value,true ) )
    {
        switch( Id_Value )
        {
            case 80:
                if(size_type == 3)
                {
                    mapIter = mapMsgItems.find( "TYPE" );
                    if( mapIter == mapMsgItems.end() )
                    {
                        break;
                    }
                    std::string sTypeVal = mapIter -> second;
                    int Type_Value_temp = atoi( sTypeVal.c_str() );
                    unsigned int Type_Value = (unsigned int)Type_Value_temp;

                    switch( Type_Value )
                    {
                        case 1:
                             ambientHightTempLabel -> setStyleSheet( "background-color:#FF4500;" );
                             mapIter = mapMsgItems.find( "VALUE" );
                             if( mapIter == mapMsgItems.end() )
                             {
                                 break;
                             }
                             AmbientTempValue = ( mapIter -> second ).c_str();
                             break;
                        case 2:
                             cellHightTempLabel -> setStyleSheet( "background-color:#FF4500;" );
                             mapIter = mapMsgItems.find( "VALUE" );
                             if( mapIter == mapMsgItems.end() )
                             {
                                 break;
                             }
                             CellTempValue = ( mapIter -> second ).c_str();
                             break;
                        case 4:
                             pcHightTempLabel -> setStyleSheet( "background-color:#FF4500;" );
                             mapIter = mapMsgItems.find( "VALUE" );
                             if ( mapIter == mapMsgItems.end() )
                             {
                                 break;
                             }
                             Pc104TempValue = ( mapIter -> second ).c_str();
                             break;
                        case 8:
                             ambientHumidityLabel -> setStyleSheet( "background-color:#FF4500;" );
                             mapIter = mapMsgItems.find( "VALUE" );
                             if( mapIter == mapMsgItems.end() )
                             {
                                 break;
                             }
                             AmbientHumiValue = ( mapIter -> second ).c_str();
                             break;
                        case 16:
                             cellHumidityLabel -> setStyleSheet( "background-color:#FF4500;" );
                             break;
                        case 32:
                             pcHumidityLabel -> setStyleSheet( "background-color:#FF4500;" );
                             break;
                        default: break;
                    }

                }
                else
                {
                }
                break;
            case 88:
                if( size_type == 3 )
                {
                    mapIter = mapMsgItems.find( "TYPE" );
                    if( mapIter == mapMsgItems.end() )
                    {
                        break;
                    }
                    std::string sTypeVal = mapIter -> second;
                    int Type_Value_temp = atoi( sTypeVal.c_str() );
                    unsigned int Type_Value = (unsigned int)Type_Value_temp;
                    switch( Type_Value )
                    {
                        case 1:
                            motorOverCurrentLabel -> setStyleSheet( "background-color:#FF4500;" );
                            mapIter = mapMsgItems.find( "VALUE" );
                            if( mapIter == mapMsgItems.end() )
                            {
                                break;
                            }
                            OverCurrentValue =  ( mapIter -> second ).c_str();
                            break;
                        case 2:
                            motorOverVoltageLabel -> setStyleSheet( "background-color:#FF4500;" );
                            mapIter = mapMsgItems.find( "VALUE" );
                            if( mapIter == mapMsgItems.end() )
                            {
                                break;
                            }
                            OverVoltageValue = ( mapIter -> second ).c_str();
                            break;
                        case 3:
                            motorUnderVoltageLabel -> setStyleSheet( "background-color:#FF4500;" );
                            mapIter = mapMsgItems.find( "VALUE" );
                            if( mapIter == mapMsgItems.end() )
                            {
                                break;
                            }
                            UnderVoltageValue = ( mapIter -> second ).c_str();
                            break;
                        case 4:
                            motorOverSpeedLabel -> setStyleSheet( "background-color:#FF4500;" );
                            mapIter = mapMsgItems.find("VALUE");
                            if(mapIter == mapMsgItems.end())
                            {
                                break;
                            }
                            OverSpeedValue = ( mapIter -> second ).c_str();
                            break;
                        case 5:
                            motorDriveLabel -> setStyleSheet( "background-color:#FF4500;" );
                            mapIter = mapMsgItems.find("VALUE");
                            if( mapIter == mapMsgItems.end() )
                            {
                                break;
                            }
                            DriveTempValue = ( mapIter -> second ).c_str();
                            break;
                        default:  break;
                    }
                }
                else
                {
                }
                break;
            case 96:
                if ( size_type == 2 )
                {
                    mapIter = mapMsgItems.find( "TYPE" );
                    if( mapIter == mapMsgItems.end() )
                    {
                          break;
                    }
                    std::string sTypeVal = mapIter -> second;
                    int Type_Value_temp = atoi(sTypeVal.c_str());
                    unsigned int Type_Value = (unsigned int)Type_Value_temp;
                    switch(Type_Value)
                    {
                        case 65535:
                            headLeakageLabel -> setStyleSheet( "background-color:#FF4500;" );
                            break;
                        default:  break;
                    }
                }
                else
                {
                }
                break;

            case 104:
                if ( size_type == 2 )
                {
                    mapIter = mapMsgItems.find( "TYPE" );
                    if(mapIter == mapMsgItems.end())
                    {
                        break;
                    }
                    std::string sTypeVal = mapIter -> second;
                    int Type_Value_temp = atoi( sTypeVal.c_str() );
                    unsigned int Type_Value = (unsigned int)Type_Value_temp;
                    switch(Type_Value)
                    {
                        case 65535:
                            backLeakageLabel -> setStyleSheet( "background-color:#FF4500;" );
                            break;
                        default:  break;
                    }
                }
                else
                {
                }
                break;
            case 72:
                if( size_type == 2 )
                {
                    mapIter = mapMsgItems.find("TYPE");
                    if(	mapIter == mapMsgItems.end() )
                    {
                        break;
                    }
                    std::string sTypeVal = mapIter->second;
                    int Type_Value_temp = atoi(sTypeVal.c_str());
                    unsigned int Type_Value = (unsigned int)Type_Value_temp;
                    switch(Type_Value)
                    {
                        case 65535:
                        tailLeakageLabel -> setStyleSheet( "background-color:#FF4500;" );
                        break;
                        default:  break;
                    }
                }
                else
                {
                }
                break;
            case 112:
                if( size_type == 3 )
                {
                    mapIter = mapMsgItems.find("TYPE");
                    if(mapIter == mapMsgItems.end())
                    {
                        break;
                    }
                    std::string sTypeVal = mapIter->second;
                    int Type_Value_temp = atoi(sTypeVal.c_str());
                    unsigned int Type_Value = (unsigned int)Type_Value_temp;
                    switch(Type_Value)
                    {
                        case 65535:
                            overPressureLabel -> setStyleSheet( "background-color:#ffff33;" );
                            mapIter = mapMsgItems.find( "VALUE" );
                            if( mapIter == mapMsgItems.end() )
                            {
                                break;
                            }
                            PressureValue = ( mapIter -> second ).c_str();
                            break;
                        case 4294901760:
                            overPressureLabel -> setStyleSheet( "background-color:#FF4500;" );
                            mapIter = mapMsgItems.find( "VALUE" );
                            if(mapIter == mapMsgItems.end())
                            {
                                break;
                            }
                            PressureValue = (mapIter->second).c_str();
                            break;
                        default :break;
                    }
                }
                else
                {
                }
                break;
            case 120:
                if( size_type == 3 )
                {
                    mapIter = mapMsgItems.find( "TYPE" );
                    if(mapIter == mapMsgItems.end())
                    {
                        break;
                    }
                    std::string sTypeVal = mapIter->second;
                    int Type_Value_temp = atoi(sTypeVal.c_str());
                    unsigned int Type_Value = (unsigned int)Type_Value_temp;
                    switch(Type_Value)
                    {
                        case 13 :
                            batteryOverCurrentLabel -> setStyleSheet( "background-color:#ffff33;" );
                            mapIter = mapMsgItems.find( "VALUE" );
                            if( mapIter == mapMsgItems.end() )
                            {
                                break;
                            }
                            Current = (mapIter->second).c_str();
                            break;
                        case 14 :
                            batteryOverCurrentLabel -> setStyleSheet( "background-color:#FF4500;" );
                            mapIter = mapMsgItems.find( "VALUE" );
                            if( mapIter == mapMsgItems.end() )
                            {
                                break;
                            }
                            Current = (mapIter->second).c_str();
                            break;
                        case 208 :
                            batteryOverVoltageLabel -> setStyleSheet( "background-color:#ffff33;" );
                            mapIter = mapMsgItems.find("VALUE");
                            if(mapIter == mapMsgItems.end())
                            {
                                break;
                            }
                            HighVoltage = (mapIter->second).c_str();
                            break;
                        case 224 :
                            batteryOverVoltageLabel -> setStyleSheet( "background-color:#FF4500;" );
                            mapIter = mapMsgItems.find("VALUE");
                            if(mapIter == mapMsgItems.end())
                            {
                                break;
                            }
                            HighVoltage = (mapIter->second).c_str();
                            break;
                        case 3328 :
                            batteryUnderVoltageLabel -> setStyleSheet( "background-color:#ffff33;" );
                            mapIter = mapMsgItems.find("VALUE");
                            if(mapIter == mapMsgItems.end())
                            {
                                 break;
                            }
                            LowVoltage = (mapIter->second).c_str();
                            break;
                        case 3584 :
                            batteryUnderVoltageLabel -> setStyleSheet( "background-color:#FF4500;" );
                            mapIter = mapMsgItems.find("VALUE");
                            if(mapIter == mapMsgItems.end())
                            {
                                 break;
                            }
                            LowVoltage = (mapIter->second).c_str();
                            break;
                        default : break;
                    }
                }
                else
                {
                }
                break;
            case 124:
                if(size_type == 2)
                {
                    mapIter = mapMsgItems.find("TYPE");
                    if(mapIter == mapMsgItems.end())
                    {
                        break;
                    }
                    std::string sTypeVal = mapIter->second;
                    int Type_Value_temp = atoi(sTypeVal.c_str());
                    unsigned int Type_Value = (unsigned int)Type_Value_temp;
                    switch(Type_Value)
                    {
                        case 65535:
                            groundLabel -> setStyleSheet( "background-color:#FF4500;" );
                            break;
                        default:  break;
                    }
                }
                else
                {
                }
                break;
            default:  break;
        }
    }
    else
    {
        std::string Id_Value = toupper( id_value );
        mapIter = mapMsgItems.find( "TYPE" );
        if( mapIter != mapMsgItems.end() )
        {
            std::string Type_Value = mapIter -> second;
            if( Id_Value == "WIRED" )
            {
                if( Type_Value == "ON" )
                {
                    wiredLabel -> setStyleSheet( "background-color:#FF4500;" );
                }
                else if( Type_Value == "CLEAR" )
                {
                    wiredLabel -> setStyleSheet( "background-color:#228B22;" );
                }
                else
                {
                }
            }
            else if( Id_Value == "WIRELESS" )
            {
                if(Type_Value=="ON")
                {
                    wirelessLabel -> setStyleSheet( "background-color:#FF4500;" );
                }
                else if( Type_Value == "CLEAR" )
                {
                    wirelessLabel -> setStyleSheet( "background-color:#228B22;" );
                }
                else
                {
                }
            }
            else if( Id_Value == "IRIDIUM" )
            {
                if( Type_Value == "ON" )
                {
                    iridiumLabel -> setStyleSheet( "background-color:#FF4500;" );
                }
                else if( Type_Value == "CLEAR" )
                {
                    iridiumLabel -> setStyleSheet( "background-color:#228B22;" );
                }
                else
                {
                }
            }
            else if( Id_Value == "USBL" )
            {
                if( Type_Value == "ON" )
                {
                    usblLabel -> setStyleSheet( "background-color:#FF4500;" );
                }
                else if( Type_Value == "CLEAR" )
                {
                    usblLabel -> setStyleSheet( "background-color:#228B22;" );
                }
                else
                {
                }
            }
            else if( Id_Value == "CANET" )
            {
                if( Type_Value == "ON" )
                {
                    canLabel -> setStyleSheet( "background-color:#FF4500;" );
                }
                else if( Type_Value == "CLEAR" )
                {
                    canLabel -> setStyleSheet( "background-color:#228B22;" );
                }
                else
                {
                }
                mapIter = mapMsgItems.find( "NOTE" );
                if( mapIter != mapMsgItems.end() )
                {
                    std::string sTypeVal = mapIter -> second;
                    CANetNote = sTypeVal.c_str();
                    canLineEdit -> setText( CANetNote );
                }
            }
            else if( Id_Value == "AHRS" )
            {
                if( Type_Value == "ON" )
                {
                    ahrsLabel -> setStyleSheet( "background-color:#FF4500;" );
                }
                else if( Type_Value == "CLEAR" )
                {
                    ahrsLabel -> setStyleSheet( "background-color:#228B22;" );
                }
                else
                {
                }
                mapIter = mapMsgItems.find( "NOTE" );
                if( mapIter != mapMsgItems.end() )
                {
                    std::string sTypeVal = mapIter->second;
                    AHRSNote = sTypeVal.c_str();
                    ahrsLineEdit -> setText( AHRSNote );
                }
            }
            else if( Id_Value == "DVL" )
            {
                if( Type_Value == "ON" )
                {
                    dvlLabel -> setStyleSheet( "background-color:#FF4500;" );
                }
                else if( Type_Value=="CLEAR" )
                {
                    dvlLabel -> setStyleSheet( "background-color:#228B22;" );
                }
                else
                {
                }
                mapIter = mapMsgItems.find("NOTE");
                if( mapIter != mapMsgItems.end() )
                {
                   std::string sTypeVal = mapIter -> second;
                   DVLNote = sTypeVal.c_str();
                   dvlLineEdit -> setText( DVLNote );
                }
            }
            else if( Id_Value == "GPS" )
            {
                if( Type_Value == "ON" )
                {
                    gpsLabel -> setStyleSheet( "background-color:#FF4500;" );
                }
                else if( Type_Value == "CLEAR" )
                {
                    gpsLabel -> setStyleSheet( "background-color:#228B22;" );
                }
                else
                {
                }
                mapIter = mapMsgItems.find("NOTE");
                if(mapIter != mapMsgItems.end())
                {
                    std::string sTypeVal = mapIter->second;
                    GPSNote = sTypeVal.c_str();
                    gpsLineEdit -> setText(GPSNote);
                }
            }
            else if(Id_Value=="INS")
            {
                if(Type_Value=="ON")
                {
                    insLabel -> setStyleSheet( "background-color:#FF4500;" );
                }
                else if(Type_Value=="CLEAR")
                {
                    insLabel -> setStyleSheet( "background-color:#228B22;" );
                }
                else
                {
                }
                mapIter = mapMsgItems.find("NOTE");
                if(mapIter != mapMsgItems.end())
                {
                    std::string sTypeVal = mapIter->second;
                }
            }
            else if(Id_Value=="IPS")
            {
                if(Type_Value=="ON")
                {
                    ipsLabel -> setStyleSheet( "background-color:#FF4500;" );
                }
                else if(Type_Value=="CLEAR")
                {
                    ipsLabel -> setStyleSheet( "background-color:#228B22;" );
                }
                else
                {
                }
                mapIter = mapMsgItems.find("NOTE");
                if(mapIter != mapMsgItems.end())
                {
                    std::string sTypeVal = mapIter->second;
                    IPSNote = sTypeVal.c_str();
                    ipsLineEdit -> setText(IPSNote);
                }
            }
            else if(Id_Value=="SIDESCAN")
            {
                if(Type_Value=="ON")
                {
                    sonarLabel -> setStyleSheet( "background-color:#FF4500;" );
                }
                else if(Type_Value=="CLEAR")
                {
                    sonarLabel -> setStyleSheet( "background-color:#228B22;" );
                }
                else
                {
                }
                mapIter = mapMsgItems.find("NOTE");
                if(mapIter != mapMsgItems.end())
                {
                    std::string sTypeVal = mapIter->second;
                    SIDESCANNote = sTypeVal.c_str();
                    sonarLineEdit -> setText(SIDESCANNote);
                }
            }
            else if(Id_Value=="EMERGENCY")
            {
                if(Type_Value=="ON")
                {
                    emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                }
                else if(Type_Value=="CLEAR")
                {
                    emergencyLabel -> setStyleSheet( "background-color:#228B22;" );
                }
                mapIter = mapMsgItems.find("NOTE");
                if(mapIter != mapMsgItems.end())
                {
                    std::string sTypeVal = mapIter->second;
                    emergencyStatusLineEdit -> setText( sTypeVal.c_str() );
                }
            }
        }
    }
}

void MainWindow::cabinData( std::string sval )
{
    std::stringstream tempStream;
    std::vector<std::string> s_child = parseString( sval, ";" );
    unsigned int k, vsize_child = s_child.size();
    std::string id = stripBlankEnds( biteString( s_child[0], '=' ) );
    std::string id_value = stripBlankEnds( s_child[0] );
    int Id_Value = atoi( id_value.c_str() );
    std::string temp[ vsize_child-1 ];
    std::string temp_value[ vsize_child-1 ];
    int n = 0;

    for(k=1; k <vsize_child; k++,n++)
    {
        temp[ n ] = stripBlankEnds( biteString( s_child[k],'=' ) );
        temp_value[ n ] = stripBlankEnds( s_child[k] );
    }
    switch( Id_Value )
    {
        case 264:
        {
            int size = sizeof(temp_value) / sizeof(temp_value[0]);
            if( size == 5 )
            {
                const char* value0 = temp_value[0].c_str();
                const char* value1 = temp_value[1].c_str();
                const char* value2 = temp_value[2].c_str();
                const char* value3 = temp_value[3].c_str();
                const char* value4 = temp_value[4].c_str();

               motorCurrentLineEdit -> setText( value0 );
               motorVoltageLineEdit -> setText( value1 );
               motorSpeedLineEdit -> setText( value2 );
               if( temp_value[4] == "0" )
               {
                   motorDirectionLineEdit -> setText( tr("正向") );
               }
               else if( temp_value[4] == "1" )
               {
                   motorDirectionLineEdit -> setText( tr("反向") );
               }
            }
            else
            {
            }
            break;
        }
        case 384:
        {
            int size = sizeof(temp_value) / sizeof(temp_value[0]);
            if( size == 1 )
            {
                int Type_Value_temp = atoi( temp_value[0].c_str() );
                unsigned int Type_Value = (unsigned int)Type_Value_temp;
                tempStream << temp_value[0];
                tempStream >> Type_Value;
                switch( Type_Value )
                {
                    case 4294901760:
                        headLeakLineEdit -> setText( tr("无泄漏") );
                        break;
                    case 65535:
                        headLeakLineEdit -> setText( tr("泄漏") );
                        break;
                    default :break;
                }
            }
            else
            {
            }
            break;
        }
        case 392:
        {
            int size = sizeof(temp_value) / sizeof(temp_value[0]);
            if( size == 1 )
            {
                int Type_Value_temp = atoi(temp_value[0].c_str());
                unsigned int Type_Value = (unsigned int)Type_Value_temp;
                tempStream << temp_value[0];
                tempStream >> Type_Value;
                switch( Type_Value )
                {
                    case 4294901760:
                        backLeakLineEdit -> setText( tr("无泄漏") );
                        break;
                    case 65535:
                        backLeakLineEdit -> setText( tr("泄漏") );
                        break;
                    default :break;
               }
            }
            else
            {
            }
            break;
        }
        case 400:
        {
            int size = sizeof(temp_value) / sizeof(temp_value[0]);
            if( size == 1 )
            {
                int Type_Value_temp = atoi(temp_value[0].c_str());
                unsigned int Type_Value = (unsigned int)Type_Value_temp;
                tempStream<<temp_value[0];
                tempStream>>Type_Value;
               switch( Type_Value )
               {
                    case 4294901760:
                        tailLeakLineEdit -> setText( tr("无泄漏") );
                        break;
                    case 65535:
                        tailLeakLineEdit -> setText( tr("泄漏") );
                        break;
                    default :break;
               }
            }
            else
            {
            }
            break;
        }
        case 448:
        {
            int size = sizeof(temp_value) / sizeof(temp_value[0]);
            if(size ==1)
            {
                int Type_Value_temp = atoi(temp_value[0].c_str());
                unsigned int Type_Value = (unsigned int)Type_Value_temp;
                tempStream << temp_value[0];
                tempStream >> Type_Value;
                switch( Type_Value )
                {
                    case 4294901760:
                        groundMonitorLineEdit -> setText( tr("无故障") );
                        break;
                    case 65535:
                        groundMonitorLineEdit -> setText( tr("有故障") );
                        break;
                    default :break;
               }
            }
            else
            {
            }
            break;
        }
        case 512:
        {
            int size = sizeof(temp_value) / sizeof(temp_value[0]);
            if(size ==1)
            {
                const char* Pressure_Value = temp_value[0].c_str();
                cabinPressureLineEdit -> setText( Pressure_Value );
            }
            else
            {
            }
            break;
        }
        case 576:
        {
            int size = sizeof(temp_value) / sizeof(temp_value[0]);
            if(size ==2)
            {
                const char* Battery_Current_1 = temp_value[0].c_str();
                const char* Battery_Voltage_1 = temp_value[1].c_str();
                batteryOneCurrentLineEdit -> setText( Battery_Current_1 );
                batteryOneVoltageLineEdit -> setText( Battery_Voltage_1 );
            }
            else
            {
            }
            break;
        }
        case 592:
        {
            int size = sizeof(temp_value) / sizeof(temp_value[0]);
            if( size == 2 )
            {
                const char* Battery_Current_2 = temp_value[0].c_str();
                const char* Battery_Voltage_2 = temp_value[1].c_str();
                batteryTwoCurrentLineEdit -> setText( Battery_Current_2 );
                batteryTwoVoltageLineEdit -> setText( Battery_Voltage_2 );
            }
            else
            {
            }
            break;
        }
        case 640:
        {
            int size = sizeof(temp_value) / sizeof(temp_value[0]);
            if( size == 4 )
            {
                int Type_Value_temp = atoi( temp_value[0].c_str() );
                unsigned int Type_Value = (unsigned int)Type_Value_temp;
                switch( Type_Value )
                {
                    case 255:
                    {
                        const char* Ambient_humidity = temp_value[1].c_str();
                        const char* Ambient_Temperature = temp_value[2].c_str();
                        const char* Ambient_waterpoint = temp_value[3].c_str();
                        cabinHumidityLineEdit -> setText( Ambient_humidity );
                        cabinTemperatureLineEdit -> setText( Ambient_Temperature );
                        cabinDewPointLineEdit -> setText( Ambient_waterpoint );
                        break;
                    }
                    case 65280:
                    {
                        const char* Cell_Temperature = temp_value[2].c_str();
                        cellTemperatureLineEdit -> setText( Cell_Temperature );
                        break;
                    }
                    case 16711680:
                    {
                        const char* Pc_Temperature = temp_value[2].c_str();
                        pcTemperatureLineEdit -> setText( Pc_Temperature );
                        break;
                    }
                    default :break;
               }
            }
            else
            {
            }
            break;
        }
        default:break;
    }
}

void MainWindow::updateXY( std::string key, std::string sval )
{
    std::vector<std::string> svec = parseString( sval, ',' );
    unsigned int size = svec.size();
    if( size <= 0 )
    {
        return;
    }
    else
    {
        std::string name_temp = stripBlankEnds(biteString(svec[0], '='));
        std::string value_temp = stripBlankEnds(svec[0]);
        if( value_temp == "pc104" )
        {
            if( key == "NODE_REPORT_LOCAL" && ( wiredEnable == true || wirelessEnable == true ) )
            {
                for( int i = 1; i < size; i++ )
                {
                    std::string name = toupper( stripBlankEnds(biteString(svec[i], '=')).c_str() );
                    std::string value = stripBlankEnds(svec[i]);
                    if( name == "X" )
                    {
                        xCoordinateLineEdit -> setText( value.c_str() );
                        xCoordinateLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
                    }
                    if( name == "Y" )
                    {
                        yCoordinateLineEdit -> setText( value.c_str() );
                        yCoordinateLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
                    }
                    if( name == "GPSLAT" )
                    {
                        gpsLatitudeLineEdit -> setText( value.c_str() );
                        gpsLatitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
                    }
                    if( name == "GPSLON" )
                    {
                        gpsLongitudeLineEdit -> setText( value.c_str() );
                        gpsLongitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
                    }
                    if( name == "GPSSTATUS" )
                    {
                        gpsSignalLineEdit -> setText( value.c_str() );
                        gpsLongitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
                    }
                    if( name == "TIME" )
                    {

                    }
                    if( name == "LAT" )
                    {
                        latitudeLineEdit -> setText( value.c_str() );
                        latitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
                    }
                    if( name == "LON" )
                    {
                        longitudeLineEdit -> setText( value.c_str() );
                        longitudeLineEdit -> setStyleSheet( "background-color:#fff2cc;" );
                    }
                }
            }
            else if( key == "NODE_REPORT_FORIRI" && iridiumEnable == true )
            {
                for( int i = 1; i < size; i++ )
                {
                    std::string name = stripBlankEnds(biteString(svec[i], '='));
                    std::string value = stripBlankEnds(svec[i]);
                    if( name == "X" )
                    {
                        xCoordinateLineEdit -> setText( value.c_str() );
                        xCoordinateLineEdit -> setStyleSheet( "background-color:#ffff00;" );
                    }
                    if( name == "Y" )
                    {
                        yCoordinateLineEdit -> setText( value.c_str() );
                        yCoordinateLineEdit -> setStyleSheet( "background-color:#ffff00;" );
                    }
                    if( name == "TIME" )
                    {

                    }
                    if( name == "LAT" )
                    {
                        latitudeLineEdit -> setText( value.c_str() );
                        latitudeLineEdit -> setStyleSheet( "background-color:#ffff00;" );
                    }
                    if( name == "LON" )
                    {
                        longitudeLineEdit -> setText( value.c_str() );
                        longitudeLineEdit -> setStyleSheet( "background-color:#ffff00;" );
                    }
                    if( name == "GPSLAT" )
                    {
                        gpsLatitudeLineEdit -> setText( value.c_str() );
                        gpsLatitudeLineEdit -> setStyleSheet( "background-color:#ffff00;" );
                    }
                    if( name == "GPSLON" )
                    {
                        gpsLongitudeLineEdit -> setText( value.c_str() );
                        gpsLongitudeLineEdit -> setStyleSheet( "background-color:#ffff00;" );
                    }
                    if( name == "GPSSTATUS" )
                    {
                        gpsSignalLineEdit -> setText( value.c_str() );
                        gpsLongitudeLineEdit -> setStyleSheet( "background-color:#ffff00;" );
                    }
                    if( name == "BAT24" )
                    {
                        batteryOneVoltageLineEdit -> setText( value.c_str() );
                        batteryOneVoltageLineEdit -> setStyleSheet( "background-color:#ffff00;" );
                    }
                    if( name == "BAT48" )
                    {
                        batteryTwoVoltageLineEdit -> setText( value.c_str() );
                        batteryTwoVoltageLineEdit -> setStyleSheet( "background-color:#ffff00;" );
                    }
                    if( name == "EMS" )
                    {
                        if( value == "0" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#228B22;" );
                            emergencyStatusLineEdit -> setText( tr("正常") );
                        }
                        else if( value == "1" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("超时应急") );
                        }
                        else if( value == "2" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("深度保持应急") );
                        }
                        else if( value == "3" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("超低应急") );
                        }
                        else if( value == "4" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("超深应急") );
                        }
                        else if( value == "5" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("下潜失败") );
                        }
                        else if( value == "6" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("上浮失败") );
                        }
                        else if( value == "7" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("24V电压过低") );
                        }
                        else if( value == "8" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("48V电压过低") );
                        }
                        else if( value == "9" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("备用电池低压") );
                        }
                        else if( value == "10" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("电机温度过高") );
                        }
                        else if( value == "11" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("泄露应急") );
                        }
                        else if( value == "12" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("导航应急") );
                        }
                        else if( value == "13" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("导引应急") );
                        }
                        else if( value == "14" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("控制应急") );
                        }
                        else if( value == "15" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("传感器应急") );
                        }
                        else if( value == "16" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("通信应急") );
                        }
                        else if( value == "17" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("进程死亡") );
                        }
                        else if( value == "18" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("推进器异常") );
                        }
                        else if( value == "99" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("未知进程异常") );
                        }
                    }
                }
            }
            else if( key == "NODE_REPORT_FORUSBL" && usblEnable == true )
            {
                for( int i = 1; i < size; i++ )
                {
                    std::string name = stripBlankEnds(biteString(svec[i], '='));
                    std::string value = stripBlankEnds(svec[i]);
                    if( name == "X" )
                    {
                        xCoordinateLineEdit -> setText( value.c_str() );
                        xCoordinateLineEdit -> setStyleSheet( "background-color:#228B22;" );
                    }
                    if( name == "Y" )
                    {
                        yCoordinateLineEdit -> setText( value.c_str() );
                        yCoordinateLineEdit -> setStyleSheet( "background-color:#228B22;" );
                    }
                    if( name == "TIME" )
                    {

                    }
                    if( name == "BAT24" )
                    {
                        batteryOneVoltageLineEdit -> setText( value.c_str() );
                        batteryOneVoltageLineEdit -> setStyleSheet( "background-color:#228B22;" );
                    }
                    if( name == "BAT48" )
                    {
                        batteryTwoVoltageLineEdit -> setText( value.c_str() );
                        batteryTwoVoltageLineEdit -> setStyleSheet( "background-color:#228B22;" );
                    }
                    if( name == "EMS" )
                    {
                        if( value == "0" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#228B22;" );
                            emergencyStatusLineEdit -> setText( tr("正常") );
                        }
                        else if( value == "1" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("超时应急") );
                        }
                        else if( value == "2" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("深度保持应急") );
                        }
                        else if( value == "3" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("超低应急") );
                        }
                        else if( value == "4" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("超深应急") );
                        }
                        else if( value == "5" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("下潜失败") );
                        }
                        else if( value == "6" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("上浮失败") );
                        }
                        else if( value == "7" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("24V电压过低") );
                        }
                        else if( value == "8" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("48V电压过低") );
                        }
                        else if( value == "9" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("备用电池低压") );
                        }
                        else if( value == "10" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("电机温度过高") );
                        }
                        else if( value == "11" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("泄露应急") );
                        }
                        else if( value == "12" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("导航应急") );
                        }
                        else if( value == "13" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("导引应急") );
                        }
                        else if( value == "14" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("控制应急") );
                        }
                        else if( value == "15" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("传感器应急") );
                        }
                        else if( value == "16" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("通信应急") );
                        }
                        else if( value == "17" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("进程死亡") );
                        }
                        else if( value == "18" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("推进器异常") );
                        }
                        else if( value == "99" )
                        {
                            emergencyLabel -> setStyleSheet( "background-color:#FF4500;" );
                            emergencyStatusLineEdit -> setText( tr("未知进程异常") );
                        }
                    }
                }
            }
        }
    }

}


void MainWindow::auvModeState( std::string sval )
{
      const char* modeState = sval.c_str();
      workModeLineEdit -> setText( modeState );
}

void MainWindow::auvActState(std::string sval)
{
      const char* actState = sval.c_str();
      workStatusLineEdit -> setText( actState );
}

void MainWindow::auvStartLatlon(std::string sval)
{

    std::string strLat = biteString(sval,',');
    strLat = stripBlankEnds( strLat );

    std::string strLon = sval;
    strLon = stripBlankEnds( strLon );

    startLatitudeLineEdit -> setText( strLat.c_str() );
    startLongitudeLineEdit -> setText( strLon.c_str() );
}

void MainWindow::pingJoystick(int flag, int JsCtrl, int stall, int cur_stall)
{
    std::string stallShow;
    std::string joystickShow;
    std::string courseStallShow;
    if(flag == 1)
    {
        if(JsCtrl == 1)
        {
            handleLabel -> setStyleSheet( "background-color:#228B22;" );
            switch( stall )
            {
                case 1:
                {
                    stallShow = "1档";
                    break;
                }
                case 2:
                {
                    stallShow = "2档";
                    break;
                }
                case 3:
                {
                    stallShow = "3档";
                    break;
                }
                case 4:
                {
                    stallShow = "4档";
                    break;
                }
            }

            switch( cur_stall )
            {
                case 1:
                {
                    courseStallShow = "δ=1";
                    break;
                }
                case 2:
                {
                    courseStallShow = "δ=5";
                    break;
                }
                case 3:
                {
                    courseStallShow = "δ=10";
                    break;
                }
                case 4:
                {
                    courseStallShow = "δ=30";
                    break;
                }
            }

            if( joystickMode != "航向手" )
            {
                joystickShow = joystickMode + "," + stallShow;
            }
            else
            {
                joystickShow = joystickMode + "," + stallShow + "," + courseStallShow;
            }

            handleLineEdit -> setText( joystickShow.c_str() );
        }
        else
        {
            handleLabel -> setStyleSheet( "background-color:#ffff33;" );
            handleLineEdit -> setText( "连接" );
        }
    }
    else
    {
        handleLabel -> setStyleSheet( "background-color:#FF4500;" );
        handleLineEdit -> setText( "离线" );
    }
}

void MainWindow::pingPC104( int flag, std::string sval )
{
    firNetLineEdit -> setText( sval.c_str() );

    if(flag == 0)
    {
        firNetLabel -> setStyleSheet( "background-color:#228B22;" );
    }
    else
    {
        firNetLabel -> setStyleSheet( "background-color:#FF4500;" );
    }

}

void MainWindow::pingRemoteARM( int flag, std::string sval )
{
    secNetLineEdit -> setText( sval.c_str() );
    if(flag == 0)
    {
        secNetLabel -> setStyleSheet( "background-color:#228B22;" );
    }
    else
    {
        secNetLabel -> setStyleSheet( "background-color:#FF4500;" );
    }
}

// 重写closeEvent: 确认退出对话框
void MainWindow::closeEvent( QCloseEvent *event )
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question( this, tr("退出程序"), QString(tr("确认退出程序")),
                                    QMessageBox::Yes | QMessageBox::No );
    if( button == QMessageBox::No )
    {
        event -> ignore();
    }
    else if( button == QMessageBox::Yes )
    {
        event -> accept();
        QCoreApplication :: quit();
    }
}

//退出操作槽信号
void MainWindow::quitMenuClicked()
{
    this -> close();
}
