#include "emergencyparadlg.h"

EmergencyParaDlg::EmergencyParaDlg( QWidget *parent )
    :QDialog( parent )
{
    setWindowTitle( tr( "应急参数设置" ) );
    maxTaskTimeLabel = new QLabel( tr( "最大任务时间(s)" ) );
    maxTaskTimeLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    maxTaskTimeLineEdit = new QLineEdit();
    maxTaskTimeLineEdit -> setText( tr( "0" ) );

    maxTaskDepthLabel = new QLabel( tr( "最大工作深度(m)" ) );
    maxTaskDepthLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    maxTaskDepthLineEdit = new QLineEdit();
    maxTaskDepthLineEdit -> setText( tr( "0" ) );

    sustainDepthTimeBox = new QCheckBox( tr( "持续深度时间(s)" ) );
    sustainDepthTimeBox -> setChecked( 0 );
    sustainDepthTimeLineEdit = new QLineEdit();
    sustainDepthTimeLineEdit -> setText( tr( "0" ) );
    sustainDepthTimeLineEdit -> setEnabled( 0 );
    connect( sustainDepthTimeBox, SIGNAL( toggled(bool) ), this, SLOT( sustainBoxChecked() ) );

    sustainTaskDepthLabel = new QLabel( tr( "持续工作深度(m)" ) );
    sustainTaskDepthLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    sustainTaskDepthLineEdit = new QLineEdit();
    sustainTaskDepthLineEdit -> setText( tr( "0" ) );
    sustainTaskDepthLineEdit -> setEnabled( 0 );

    sustainAltitudeBox = new QCheckBox( tr( "持续海拔时间(s)" ) );
    sustainAltitudeBox -> setChecked( 0 );
    sustainAltitudeLineEdit = new QLineEdit();
    sustainAltitudeLineEdit -> setText( tr( "0" ) );
    sustainAltitudeLineEdit -> setEnabled( 0 );
    connect( sustainAltitudeBox, SIGNAL( toggled(bool) ), this, SLOT( altitudeBoxChecked() ) );

    minAltitudeLabel = new QLabel( tr( "最小海拔高度(m)" ) );
    minAltitudeLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    minAltitudeLineEdit = new QLineEdit();
    minAltitudeLineEdit -> setText( tr( "0" ) );
    minAltitudeLineEdit -> setEnabled( 0 );

    maxTaskRadiusBox = new QCheckBox( tr( "最大工作半径(m)" ) );
    maxTaskRadiusBox -> setChecked( 0 );
    maxTaskRadiusLineEdit = new QLineEdit();
    maxTaskRadiusLineEdit -> setText( tr( "0" ) );
    maxTaskRadiusLineEdit -> setEnabled( 0 );
    connect( maxTaskRadiusBox, SIGNAL( toggled(bool) ), this, SLOT( RadiusBoxChecked() ) );

    pPhasestimeRadiusBox = new QCheckBox( tr( "分段下潜时间(s)" ) );
    pPhasestimeRadiusBox -> setChecked( 0 );
    pPhasestimeLineEdit = new QLineEdit();
    pPhasestimeLineEdit -> setText( tr( "0" ) );
    pPhasestimeLineEdit -> setEnabled( 0 );
    connect( pPhasestimeRadiusBox, SIGNAL( toggled(bool) ), this, SLOT( pPhasestimeChecked() ) );

    sendBtn = new QPushButton( tr( "发送" ) );
    connect( sendBtn, SIGNAL( clicked(bool) ), this, SLOT( sendBtnClicked() ) );

    emergencyParaGrid = new QGridLayout( this );
    emergencyParaGrid -> addWidget( maxTaskTimeLabel, 0, 0, 1, 2 );
    emergencyParaGrid -> addWidget( maxTaskTimeLineEdit, 0, 2, 1, 2 );
    emergencyParaGrid -> addWidget( maxTaskDepthLabel, 0, 4, 1, 2 );
    emergencyParaGrid -> addWidget( maxTaskDepthLineEdit, 0, 6, 1, 2 );
    emergencyParaGrid -> addWidget( sustainDepthTimeBox, 2, 0, 1, 2 );
    emergencyParaGrid -> addWidget( sustainDepthTimeLineEdit, 2, 2, 1, 2 );
    emergencyParaGrid -> addWidget( sustainTaskDepthLabel, 2, 4, 1, 2 );
    emergencyParaGrid -> addWidget( sustainTaskDepthLineEdit, 2, 6, 1, 2 );
    emergencyParaGrid -> addWidget( sustainAltitudeBox, 3, 0, 1, 2 );
    emergencyParaGrid -> addWidget( sustainAltitudeLineEdit, 3, 2, 1, 2 );
    emergencyParaGrid -> addWidget( minAltitudeLabel, 3, 4, 1, 2 );
    emergencyParaGrid -> addWidget( minAltitudeLineEdit, 3, 6, 1, 2 );
    emergencyParaGrid -> addWidget( maxTaskRadiusBox, 4, 0, 1, 2 );
    emergencyParaGrid -> addWidget( maxTaskRadiusLineEdit, 4, 2, 1, 2 );
    emergencyParaGrid -> addWidget( pPhasestimeRadiusBox, 4, 4, 1, 2 );
    emergencyParaGrid -> addWidget( pPhasestimeLineEdit, 4, 6, 1, 2 );
    emergencyParaGrid -> addWidget( sendBtn, 5, 3, 1, 2 );

    pressbutton = false;

}

EmergencyParaDlg::~EmergencyParaDlg()
{
    delete emergencyParaGrid;
}

std::string EmergencyParaDlg::sendMsg()
{
    std::string str = "MsgType=prov;paramtype=emergency;";
    std::string sVal = "";
    QString qsVal = "";
    bool bHasVal = false;

    if( maxTaskTimeLineEdit -> isEnabled() )
    {
        qsVal = maxTaskTimeLineEdit -> text();
        qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
        sVal = qsVal.toStdString();
        if( sVal.length() > 0 )
        {
            str += "MaxMisTime=" + sVal;
            bHasVal = true;
        }
    }
    if( maxTaskDepthLineEdit -> isEnabled() )
    {
        qsVal = maxTaskDepthLineEdit -> text();
        qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
        sVal = qsVal.toStdString();
        if( sVal.length() > 0 )
        {
            str += ";MaxDepth=" + sVal;
            bHasVal = true;
        }
    }
    if( sustainDepthTimeLineEdit -> isEnabled() )
    {
        qsVal = sustainDepthTimeLineEdit -> text();
        qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
        sVal = qsVal.toStdString();
        if( sVal.length() > 0 )
        {
            str += ";KeepingTime=" + sVal;
            bHasVal = true;
        }
    }
    if( sustainTaskDepthLineEdit -> isEnabled() )
    {
        qsVal = sustainTaskDepthLineEdit -> text();
        qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
        sVal = qsVal.toStdString();
        if( sVal.length() > 0 )
        {
            str += ";KeepingDepth=" + sVal;
            bHasVal = true;
        }
    }
    if( sustainAltitudeLineEdit -> isEnabled() )
    {
        qsVal = sustainAltitudeLineEdit -> text();
        qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
        sVal = qsVal.toStdString();
        if( sVal.length() > 0 )
        {
            str += ";AltitudeTime=" + sVal;
            bHasVal = true;
        }
    }
    if( minAltitudeLineEdit -> isEnabled() )
    {
        qsVal = minAltitudeLineEdit -> text();
        qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
        sVal = qsVal.toStdString();
        if( sVal.length() > 0 )
        {
            str += ";MINAltitude=" + sVal;
            bHasVal = true;
        }
    }
    if( maxTaskRadiusLineEdit -> isEnabled() )
    {
        qsVal = maxTaskRadiusLineEdit -> text();
        qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
        sVal = qsVal.toStdString();
        if( sVal.length() > 0 )
        {
            str += ";MAXWORKRADIUS=" + sVal;
            bHasVal = true;
        }
    }
    if( pPhasestimeLineEdit -> isEnabled() )
    {
        qsVal = pPhasestimeLineEdit -> text();
        qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
        sVal = qsVal.toStdString();
        if( sVal.length() > 0 )
        {
            str += ";GREATDEPTH_PHASESTIME=" + sVal;
            bHasVal = true;
        }
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

//持续深度时间槽信号
void EmergencyParaDlg::sustainBoxChecked()
{
    if( sustainDepthTimeBox -> isChecked() )
    {
        sustainDepthTimeLineEdit -> setEnabled( 1 );
        sustainTaskDepthLineEdit -> setEnabled( 1 );
    }
    else
    {
        sustainDepthTimeLineEdit -> setEnabled( 0 );
        sustainTaskDepthLineEdit -> setEnabled( 0 );
    }
}

//持续海拔时间槽信号
void EmergencyParaDlg::altitudeBoxChecked()
{
    if( sustainAltitudeBox -> isChecked() )
    {
        sustainAltitudeLineEdit -> setEnabled( 1 );
        minAltitudeLineEdit -> setEnabled( 1 );
    }
    else
    {
        sustainAltitudeLineEdit -> setEnabled( 0 );
        minAltitudeLineEdit -> setEnabled( 0 );
    }
}

//最小工作半径槽信号
void EmergencyParaDlg::RadiusBoxChecked()
{
    if( maxTaskRadiusBox -> isChecked() )
    {
        maxTaskRadiusLineEdit -> setEnabled( 1 );
    }
    else
    {
        maxTaskRadiusLineEdit -> setEnabled( 0 );
    }
}

void EmergencyParaDlg::pPhasestimeChecked()
{
    if( pPhasestimeRadiusBox -> isChecked() )
    {
        pPhasestimeLineEdit -> setEnabled( 1 );
    }
    else
    {
        pPhasestimeLineEdit -> setEnabled( 0 );
    }
}

//发送按钮槽信号
void EmergencyParaDlg::sendBtnClicked()
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

void EmergencyParaDlg::closeEvent( QCloseEvent *event )
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question( this, tr("退出应急参数设置"), QString(tr("确认退出设置")),
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
