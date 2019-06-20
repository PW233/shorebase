#pragma execution_character_set("utf-8")
#pragma execution_character_set("utf-8")
#include "configuredlg.h"
#include <QMessageBox>
#include <QString>

configureDlg::configureDlg( QWidget *parent )
    :QDialog(parent)
{

    setWindowTitle( tr( "配置" ) );

    environmentalConfigLabel = new QLabel( tr( "环境参数配置" ) );
    environmentalConfigLabel -> setStyleSheet( "background-color:yellow" );
    currentSalinityLabel = new QLabel( tr( "盐度(%)" ) );
    currentTemperatureLabel = new QLabel( tr( "温度(°C)" ) );
    currentPressureLabel = new QLabel( tr( "气压(dBAR)" ) );
    currentSoundSpeedLabel = new QLabel( tr( "声速(m/s)" ) );
    currentDensityLabel = new QLabel( tr( "密度(kg/m³)" ) );
    currentGravitationLabel = new QLabel( tr( "引力(N/kg)" ) );
    excessiveMotorCurrentLabel = new QLabel( tr( "电机过流参数设置" ) );
    excessiveMotorCurrentLabel -> setStyleSheet( "background-color:yellow" );
    samplingIntervalLabel = new QLabel( tr( "采样间隔(s)" ) );
    samplingTimesLabel = new QLabel( tr( "采样次数(n)" ) );
    samplingValueLabel = new QLabel( tr( "采样值(A)" ) );

    currentSalinityLineEdit = new QLineEdit();
    currentTemperatureLineEdit = new QLineEdit();
    currentPressureLineEdit = new QLineEdit();
    currentSoundSpeedLineEdit = new QLineEdit();
    currentDensityLineEdit = new QLineEdit();
    currentGravitationLineEdit = new QLineEdit();
    samplingIntervalLineEdit = new QLineEdit();
    samplingTimesLineEdit = new QLineEdit();
    samplingValueLineEdit = new QLineEdit();

    configureSendButton = new QPushButton( tr( "发送" ) );

    configureGrid = new QGridLayout( this );
    configureGrid -> addWidget( environmentalConfigLabel, 0, 0, 1, 4 );
    configureGrid -> addWidget( currentSalinityLabel, 1, 0, 1, 3 );
    configureGrid -> addWidget( currentSalinityLineEdit, 1, 4, 1, 4 );
    configureGrid -> addWidget( currentTemperatureLabel, 1, 9, 1, 4 );
    configureGrid -> addWidget( currentTemperatureLineEdit, 1, 14, 1, 4 );
    configureGrid -> addWidget( currentPressureLabel, 1, 19, 1, 5 );
    configureGrid -> addWidget( currentPressureLineEdit, 1, 25, 1, 4 );
    configureGrid -> addWidget( currentSoundSpeedLabel, 2, 0, 1, 3 );
    configureGrid -> addWidget( currentSoundSpeedLineEdit, 2, 4, 1, 4 );
    configureGrid -> addWidget( currentDensityLabel, 2, 9, 1, 4);
    configureGrid -> addWidget( currentDensityLineEdit, 2, 14, 1, 4 );
    configureGrid -> addWidget( currentGravitationLabel, 2, 19, 1, 5 );
    configureGrid -> addWidget( currentGravitationLineEdit, 2, 25, 1, 4 );
    configureGrid -> addWidget( excessiveMotorCurrentLabel, 3, 0, 1, 5 );
    configureGrid -> addWidget( samplingIntervalLabel, 4, 0, 1, 3 );
    configureGrid -> addWidget( samplingIntervalLineEdit, 4, 4, 1, 4 );
    configureGrid -> addWidget( samplingTimesLabel, 4, 9, 1, 4 );
    configureGrid -> addWidget( samplingTimesLineEdit, 4, 14, 1, 4 );
    configureGrid -> addWidget( samplingValueLabel, 4, 19, 1, 5 );
    configureGrid -> addWidget( samplingValueLineEdit, 4, 25, 1, 4 );
    configureGrid -> addWidget( configureSendButton, 5, 13, 1, 4 );
    pressbutton = false;

    connect( configureSendButton, SIGNAL( clicked() ), this, SLOT( configSendBtnClicked() ) );
}

configureDlg::~configureDlg()
{
    delete configureGrid;
}

std::string configureDlg::sendMsg()
{
    std::string str = "MsgType=prov";
    std::string sVal = "";
    QString qsVal = "";
    bool bHasVal = false;

    qsVal = currentSalinityLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    if( sVal.length() > 0 )
    {
        str += ";sal=";
        str += sVal;
        bHasVal = true;
    }

    qsVal = currentTemperatureLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    if( sVal.length() > 0 )
    {
        str += ";temp=";
        str += sVal;
        bHasVal = true;
    }

    qsVal = currentSoundSpeedLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    if( sVal.length() > 0 )
    {
        str += ";soundSpd=";
        str += sVal;
        bHasVal = true;
    }

    qsVal = currentPressureLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    if( sVal.length() > 0 )
    {
        str += ";atomsPress=";
        str += sVal;
        bHasVal = true;
    }

    qsVal = currentDensityLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    if( sVal.length() > 0 )
    {
        str += ";density=";
        str += sVal;
        bHasVal = true;
    }

    qsVal = currentGravitationLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    if( sVal.length() > 0 )
    {
        str += ";gravity=";
        str += sVal;
        bHasVal = true;
    }

    qsVal = samplingIntervalLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    if( sVal.length() > 0 )
    {
        str += ";thruster_i_time=";
        str += sVal;
        bHasVal = true;
    }

    qsVal = samplingTimesLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    if( sVal.length() > 0 )
    {
        str += ";thruster_i_num=";
        str += sVal;
        bHasVal = true;
    }

    qsVal = samplingValueLineEdit -> text();
    qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
    sVal = qsVal.toStdString();
    if( sVal.length() > 0 )
    {
        str += ";thruster_i_val=";
        str += sVal;
        bHasVal = true;
    }

    if( bHasVal )
    {
        return str;
    }
    else
    {
        return "";
    }
}

void configureDlg::configSendBtnClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr( "是否发送数据" ),  tr( "确认发送" ),
                                    QMessageBox::Yes | QMessageBox::No );
    if( reply == QMessageBox::Yes )
    {
        pressbutton = true;
    }
    else if( reply == QMessageBox::No )
    {
        pressbutton = false;
    }
}

void configureDlg::closeEvent( QCloseEvent *event )
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question( this, tr("退出环境配置"), QString(tr("确认退出配置")),
                                    QMessageBox::Yes | QMessageBox::No );
    if(button == QMessageBox::No)
    {
        event -> ignore();
    }
    else if(button == QMessageBox::Yes)
    {
        event -> accept();
    }
}

