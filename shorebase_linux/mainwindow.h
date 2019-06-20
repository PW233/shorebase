#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QDockWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QWidget>
#include <QActionGroup>
#include <QCloseEvent>
#include <QPalette>
#include "configuredlg.h"
#include "debugdlg.h"
#include "startandviewdlg.h"
#include "emergencyparadlg.h"
#include "missionparadlg.h"
#include "mapdialog.h"
#include "pathplanningdlg.h"
#include "customplotdlg.h"
#include "emergencyshow.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //"文件"菜单
    QMenu *fileMenu;
    QAction *quitAction;

     //"配置"菜单
    QMenu *configureMenu;
    QAction *configureAction;
    //configureDlg *configuredlg;
    configureDlg configuredlg;

    //"调试"菜单
    QMenu *debugMenu;
    QAction *debugAction;
    //DebugDlg *debugdlg;
    DebugDlg debugdlg;

    //"控制"菜单
    QMenu *controlMenu;
    QMenu *navControlMenu;
    QMenu *motionControlMenu;
    QMenu *sideScanControlMenu;
    QMenu *rectifyControlMenu;
    QMenu *pc104ControlMenu;
    QAction *navControlAction[2];
    QAction *motionControlAction[7];
    QAction *sideScanControlAction[2];
    QAction *rectifyControlAction[3];
    QAction *pc104ControlAction[2];

    //"传感器"菜单
    QMenu *sensorMenu;
    QMenu *usblManagerMenu;
    QMenu *dvlManagerMenu;
    QMenu *tossingManagerMenu;
    QMenu *ledManagerMenu;
    QMenu *insManagerMenu;
    QMenu *thrusterManagerMenu;
    QMenu *ahrsManagerMenu;
    QAction *usblManagerAction[3];
    QAction *dvlManagerAction[2];
    QAction *tossingManagerAction[2];
    QAction *ledManagerAction[2];
    QAction *insManagerAction[2];
    QAction *thrusterManagerAction[2];
    QAction *ahrsManagerAction[2];



    //"使命计划"菜单
    QMenu *missionPlanningMenu;
    QAction *setStartAndViewAction;
    StartAndViewDlg startAndViewDlg;
    QAction *setMissionParaAction;
    MissionParaDlg missionParaDlg;
    QAction *setPathPlanningAction;
    PathPlanningDlg pathPlanningDlg;

    //"应急设置"菜单
    QMenu *setEmergencyMenu;
    QAction *setEmergencyParaAction;
    EmergencyParaDlg emergencyParaDlg;
    EmergencyShow emergencyShowDlg;
    QAction *startTaskCountAction;
    QAction *endTaskCountAction;
    QAction *emergencyShowAction;
    QAction *clearEmergencyAction;
    QAction *openEmergencyAction;
    QAction *closeEmergencyAction;

    //"通信信道"菜单
    QMenu *comChannelMenu;
    QAction *wiredNetAction;
    QAction *wirelessNetAction;
    QAction *iriSystemAction;
    QAction *usblEquipmentAction;
    QActionGroup *comChannelGroup;

    //"手柄控制"菜单
    QMenu *handleControlMenu;
    QAction *defaultAction;
    QAction *AmericaAction;
    QAction *JapanAction;
    QAction *CourseCtrlAction;
    QActionGroup *handleGroup;

    //"进程管理"菜单
    QMenu *processManagerMenu;
    QAction *processOnAction;
    QAction *processOffAction;
    QAction *processShutdownAction;
    QAction *processPowerOffAction;

    //"视图管理"菜单
    QMenu *userDefinedMenu;
    QAction *warningAction;
    QAction *statusAction;
    QAction *dataAction;
    QAction *chartAction;
    QAction *mapAction;
    QActionGroup *actionGroup;


    //停靠窗口定义
    QDockWidget *warningDock;        //"告警信息"窗口
    QGridLayout *warningGrid;
    QWidget *warningWidget;

    QDockWidget *statusMonitorDock;  //"状态监测"窗口
    QGridLayout *statusMonitorGrid;
    QWidget *statusMonitorWidget;

    QDockWidget *dataMonitorDock;    //"数据监测"窗口
    QGridLayout *dataMonitorGrid;
    QWidget *dataMonitorWidget;

   // QDockWidget *chartDock;          //"图表"窗口
   // QGridLayout *chartGrid;
   // QWidget *chartWidget;
    customplotDlg *plotDlg;

    QDockWidget *mapDock;            //"地图"窗口
    QGridLayout *mapGrid;
    MapDialog *mapDialog;

    //“告警信息”窗口部件
    QLabel *ambientHightTempLabel;
    QLabel *ambientHumidityLabel;
    QLabel *cellHightTempLabel;
    QLabel *cellHumidityLabel;
    QLabel *pcHightTempLabel;
    QLabel *pcHumidityLabel;
    QLabel *motorOverCurrentLabel;
    QLabel *motorOverVoltageLabel;
    QLabel *motorUnderVoltageLabel;
    QLabel *motorOverSpeedLabel;
    QLabel *motorDriveLabel;
    QLabel *groundLabel;
    QLabel *overPressureLabel;
    QLabel *emergencyLabel;
    QLabel *batteryOverCurrentLabel;
    QLabel *batteryOverVoltageLabel;
    QLabel *batteryUnderVoltageLabel;
    QLabel *headLeakageLabel;
    QLabel *backLeakageLabel;
    QLabel *tailLeakageLabel;
    QLabel *iridiumLabel;
    QLabel *wiredLabel;
    QLabel *usblLabel;
    QLabel *wirelessLabel;

    //"状态监测"窗口部件
    QLabel *ahrsLabel;
    QLabel *insLabel;
    QLabel *firNetLabel;
    QLabel *canLabel;
    QLabel *ipsLabel;
    QLabel *gpsLabel;
    QLabel *dvlLabel;
    QLabel *sonarLabel;
    QLabel *secNetLabel;
    QLabel *handleLabel;
    QLineEdit *ahrsLineEdit;
    QLineEdit *insLineEdit;
    QLineEdit *firNetLineEdit;
    QLineEdit *canLineEdit;
    QLineEdit *ipsLineEdit;
    QLineEdit *gpsLineEdit;
    QLineEdit *dvlLineEdit;
    QLineEdit *sonarLineEdit;
    QLineEdit *secNetLineEdit;
    QLineEdit *handleLineEdit;
    QPushButton *refreshBtn;

    //"参数监测"窗口部件
    QLabel *robotLabel;
    QLabel *emergencyStatusLabel;
    QLabel *counterLabel;
    QLabel *timeLabel;
    QLabel *lngLatitudeLabel;
    QLabel *xyCoordinateLabel;
    QLabel *gpsLngLatitudeLabel;
    QLabel *gpsSatelliteLabel;
    QLabel *gpsSignalLabel;
    QLabel *batteryOneLabel;
    QLabel *batteryTwoLabel;
    QLabel *cellTemperatureLabel;
    QLabel *pcTemperatureLabel;
    QLabel *cabinTemperatureLabel;
    QLabel *cabinHumidityLabel;
    QLabel *cabinDewPointLabel;
    QLabel *cabinPressureLabel;
    QLabel *motorLabel;
    QLabel *motorSpeedLabel;
    QLabel *motorDirectionLabel;
    QLabel *headLeakLabel;
    QLabel *backLeakLabel;
    QLabel *tailLeakLabel;
    QLabel *groundMonitorLabel;
    QLabel *startLngLatitudeLabel;
    QLabel *iriLngLatitudeLabel;
    QLabel *iriTimeLabel;
    QLabel *currentChannelLabel;
    QLabel *workModeLabel;
    QLabel *workStatusLabel;
    QLineEdit *robotLineEdit;
    QLineEdit *emergencyStatusLineEdit;
    QLineEdit *counterLineEdit;
    QLineEdit *timeLineEdit;
    QLineEdit *latitudeLineEdit;
    QLineEdit *longitudeLineEdit;
    QLineEdit *xCoordinateLineEdit;
    QLineEdit *yCoordinateLineEdit;
    QLineEdit *gpsLatitudeLineEdit;
    QLineEdit *gpsLongitudeLineEdit;
    QLineEdit *gpsSatelliteLineEdit;
    QLineEdit *gpsSignalLineEdit;
    QLineEdit *batteryOneCurrentLineEdit;
    QLineEdit *batteryOneVoltageLineEdit;
    QLineEdit *batteryTwoCurrentLineEdit;
    QLineEdit *batteryTwoVoltageLineEdit;
    QLineEdit *cellTemperatureLineEdit;
    QLineEdit *pcTemperatureLineEdit;
    QLineEdit *cabinTemperatureLineEdit;
    QLineEdit *cabinHumidityLineEdit;
    QLineEdit *cabinDewPointLineEdit;
    QLineEdit *cabinPressureLineEdit;
    QLineEdit *motorVoltageLineEdit;
    QLineEdit *motorCurrentLineEdit;
    QLineEdit *motorSpeedLineEdit;
    QLineEdit *motorDirectionLineEdit;
    QLineEdit *headLeakLineEdit;
    QLineEdit *backLeakLineEdit;
    QLineEdit *tailLeakLineEdit;
    QLineEdit *groundMonitorLineEdit;
    QLineEdit *startLatitudeLineEdit;
    QLineEdit *startLongitudeLineEdit;
    QLineEdit *iriLatitudeLineEdit;
    QLineEdit *iriLongitudeLineEdit;
    QLineEdit *iriTimeLineEdit;
    QLineEdit *currentChannelLineEdit;
    QLineEdit *workModeLineEdit;
    QLineEdit *workStatusLineEdit;

    QPushButton *dataRefreshBtn;

    std::string  getPendingVar( unsigned int index );
    std::string  getPendingVal( unsigned int index );
    void         clearPending();
    void         pushPending( std::string, std::string );
    unsigned int getPendingSize() { return( m_pending_vars.size() ); };

    void calibStatus( std::string svalue );
    void displayForSensor(std::string svalue);
    void warningBox(std::string svalue);
    void cabinData(std::string sval);
    void updateXY( std::string key, std::string sval );
    void auvStartLatlon(std::string sval);
    void pingPC104(int, std::string);
    void pingRemoteARM(int flag, std::string sval);
    void pingJoystick(int flag, int JsCtrl, int stall, int cur_stall);

    void auvModeState(std::string sval);
    void auvActState(std::string sval);

    void channelshow();

    bool bCalibStatus;
    bool bDvlStatus;
    bool bNavstart;
    bool bWarningBox;

    bool wiredEnable;
    bool wirelessEnable;
    bool usblEnable;
    bool iridiumEnable;

    const char* AmbientTempValue;
    const char* AmbientHumiValue;
    const char* CellTempValue;
    const char* Pc104TempValue;
    const char* PressureValue;
    const char* OverCurrentValue;
    const char* OverVoltageValue;
    const char* UnderVoltageValue;
    const char* OverSpeedValue;
    const char* DriveTempValue;
    const char* Current;
    const char* HighVoltage;
    const char* LowVoltage;
    const char* CANetNote;
    const char* AHRSNote;
    const char* GPSNote;
    const char* IPSNote;
    const char* TCMNote;
    const char* DVLNote;
    const char* SIDESCANNote;

private slots:
    void quitMenuClicked();

    void createWarningDock();
    void createStatusMonitorDock();
    void createDataMonitorDock();
    void createMapDock();

    void createConfigureDlg();
    void createDebugDlg();

    void sensorMenuClicked(QAction*);
    void controlMenuClicked(QAction*);
    void MissionMenuClicked(QAction*);
    void EmergencyMenuClicked(QAction*);
    void comChannelMenuClicked(QAction*);
    void handleMenuClicked(QAction*);
    void processManagerClicked(QAction*);
    void userDefinedMenuChecked(QAction*);

    void refreshBtnClicked();
    void dataRefreshBtnClicked();

public slots:
    void showTime();
    void counter();

private:
    Ui::MainWindow *ui;

    int hourTemp;
    int minTemp;
    int secTemp;
    int countTemp;

    void init();
    void createMenuBar();
    void startTime();
    void startCounter();
    void closeEvent( QCloseEvent * );

    void getValueFromMap( );
    std::string sendValueToDlg( std::string );
    std::string joystickMode;

protected:
    std::vector<std::string> m_pending_vars;
    std::vector<std::string> m_pending_vals;



};

#endif // MAINWINDOW_H
