#include "missionparadlg.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QTableWidgetItem>
#include "MBUtils.h"
#include <QDebug>
#include <QMessageBox>


MissionParaDlg::MissionParaDlg( QWidget *parent )
    :QDialog( parent )
{
    setWindowTitle( tr( "使命参数设置" ) );


    tableWidget = new QTableWidget(8,6);
    tableWidget -> verticalHeader() -> setVisible( false );
    tableWidget -> resize( 160,600 );
    for( int i = 0; i < 8; i++ )
    {
        tableWidget -> setRowHeight( i, 24 );
    }

    for( int i = 0; i < 6; i++ )
    {
        if( i == 0 )
        {
            tableWidget -> setColumnWidth( i, 100 );
        }
        else if( i < 4 )
        {
            tableWidget -> setColumnWidth( i, 130 );
        }
        else
        {
            tableWidget -> setColumnWidth( i, 35 );
        }
    }
    QStringList header;
    header << "路径点  " << "  经度  " << "  纬度  " << "  深度  " << "  上浮  " << "  选择  ";
    tableWidget -> setHorizontalHeaderLabels( header );
    tableWidget -> setItem( 0, 0, new QTableWidgetItem( tr("路径点一") ) );
    tableWidget -> setItem( 1, 0, new QTableWidgetItem( tr("路径点二") ) );
    tableWidget -> setItem( 2, 0, new QTableWidgetItem( tr("路径点三") ) );
    tableWidget -> setItem( 3, 0, new QTableWidgetItem( tr("路径点四") ) );
    tableWidget -> setItem( 4, 0, new QTableWidgetItem( tr("路径点五") ) );
    tableWidget -> setItem( 5, 0, new QTableWidgetItem( tr("路径点六") ) );
    tableWidget -> setItem( 6, 0, new QTableWidgetItem( tr("路径点七") ) );
    tableWidget -> setItem( 7, 0, new QTableWidgetItem( tr("路径点八") ) );

    for( int i = 0; i < 8; i++ )
    {
        tableWidget -> item( i, 0 ) -> setFlags( tableWidget -> item( i, 0 )->flags() & (~Qt::ItemIsEditable));
        tableWidget -> item( i, 0 ) -> setTextAlignment( Qt::AlignHCenter );
    }

    for( int i = 0 ; i < 8; i ++ )
    {
        for( int j = 4; j < 6; j++ )
        {

            QTableWidgetItem *check = new QTableWidgetItem();
            check -> setCheckState( Qt::Unchecked );
            tableWidget->setItem( i, j, check );
            tableWidget -> item( i, j ) -> setFlags( tableWidget -> item( i, j )->flags() & (~Qt::ItemIsEditable));


            /*
            QWidget *widget = new QWidget();
            QCheckBox *check = new QCheckBox();;
            QHBoxLayout *hLayout = new QHBoxLayout();
            hLayout -> addWidget( check );
            hLayout -> setMargin( 0 );
            hLayout -> setAlignment( widget, Qt::AlignCenter );
            hLayout -> setContentsMargins( 24, 0, 20, 0 );
            widget -> setLayout( hLayout );
            tableWidget -> setCellWidget( i, j, widget );
            */

        }
    }

    depthModeLabel = new QLabel( tr( "深度模式" ) );
    depthModeLabel -> setFixedSize( 100, 20 );
    depthModeLabel -> setAlignment( Qt::AlignCenter );
    depthModeCombo = new QComboBox();
    depthModeCombo -> setFixedSize( 100, 20 );
    depthModeCombo -> addItem( tr( "" ) );
    depthModeCombo -> addItem( tr( "一次定深" ) );
    depthModeCombo -> addItem( tr( "分段定深" ) );
    depthModeCombo -> addItem( tr( "阶跃定深" ) );
    depthModeCombo -> addItem( tr( "连续定高" ) );
    depthModeCombo -> addItem( tr( "分段定高" ) );
    connect( depthModeCombo, SIGNAL( currentIndexChanged(int) ), this, SLOT( depthModeChanged() ) );

    speedLabel = new QLabel( tr( "速度(m/s)" ) );
    speedLabel -> setFixedSize( 100, 20 );
    speedLabel -> setAlignment( Qt::AlignCenter );
    speedLineEdit = new QLineEdit();
    speedLineEdit -> setFixedSize( 100, 20 );
    speedLineEdit -> setText( tr( "0" ) );

    depthLabel = new QLabel( tr( "深度(m)" ) );
    depthLabel -> setFixedSize( 100, 20 );
    depthLabel -> setAlignment( Qt::AlignCenter );
    depthLineEdit = new QLineEdit();
    depthLineEdit -> setFixedSize( 100, 20 );
    depthLineEdit -> setText( tr( "0" ) );
    depthLineEdit -> setEnabled( 0 );

    heightLabel = new QLabel( tr( "高度(m)" ) );
    heightLabel -> setFixedSize( 100, 20 );
    heightLabel -> setAlignment( Qt::AlignCenter );
    heightLineEdit = new QLineEdit();
    heightLineEdit -> setFixedSize( 100, 20 );
    heightLineEdit -> setEnabled( 0 );
    heightLineEdit -> setText( tr( "0" ) );

    roundsLabel = new QLabel( tr( "圈数" ) );
    roundsLabel -> setFixedSize( 100, 20 );
    roundsLabel -> setAlignment( Qt::AlignCenter );
    roundsLineEdit = new QLineEdit();
    roundsLineEdit -> setFixedSize( 100, 20 );
    roundsLineEdit -> setText( tr( "0" ) );
    roundsLineEdit -> setEnabled( 0 );

    radiusLabel = new QLabel( tr( "半径" ) );
    radiusLabel -> setFixedSize( 100, 20 );
    radiusLabel -> setAlignment( Qt::AlignCenter );
    radiusLineEdit = new QLineEdit();
    radiusLineEdit -> setFixedSize( 100, 20 );
    radiusLineEdit -> setEnabled( 0 );
    radiusLineEdit -> setText( tr( "0" ) );

    thresholdLabel = new QLabel( tr( "阈值" ) );
    thresholdLabel -> setFixedSize( 100, 20 );
    thresholdLabel -> setAlignment( Qt::AlignCenter );
    thresholdLineEdit = new QLineEdit();
    thresholdLineEdit -> setFixedSize( 100, 20 );
    thresholdLineEdit -> setEnabled( 0 );
    thresholdLineEdit -> setText( tr( "0" ) );

    steppingDepthLabel = new QLabel( tr( "步进深度" ) );
    steppingDepthLabel -> setFixedSize( 100, 20 );
    steppingDepthLabel -> setAlignment( Qt::AlignCenter );
    steppingDepthLineEdit = new QLineEdit();
    steppingDepthLineEdit -> setFixedSize( 100, 20 );
    steppingDepthLineEdit -> setEnabled( 0 );
    steppingDepthLineEdit -> setText( tr( "0" ) );

    helixCheckBox = new QCheckBox( tr( "螺旋下潜" ) );
    helixCheckBox -> setFixedSize( 100, 20 );
    helixCheckBox -> setChecked( 0 );
    connect( helixCheckBox, SIGNAL( stateChanged(int) ), this, SLOT( helixBoxChecked() ) );

    autoReturnCheckBox = new QCheckBox( tr( "自动返航" ) );
    autoReturnCheckBox -> setFixedSize( 100, 20 );
    autoReturnCheckBox -> setChecked( 0 );

    sendByIRICheckBox = new QCheckBox( tr( "铱星发送" ) );
    sendByIRICheckBox -> setFixedSize( 100, 20 );
    sendByIRICheckBox -> setChecked( 0 );

    leadModeLabel = new QLabel( tr( "前视模式" ) );
    leadModeLabel -> setFixedSize( 100, 20 );
    leadModeLabel -> setAlignment( Qt::AlignCenter );
    leadModeCombo = new QComboBox();
    leadModeCombo -> setFixedSize( 100, 20 );
    leadModeCombo -> addItem( tr( "" ) );
    leadModeCombo -> addItem( tr( "固定前视" ) );
    leadModeCombo -> addItem( tr( "可变前视" ) );
    connect( leadModeCombo, SIGNAL( currentIndexChanged(int) ), this, SLOT( leadModeChanged() ) );

    leadLabel_1 = new QLabel( tr( "前视距离１" ) );
    leadLabel_1 -> setFixedSize( 100, 20 );
    leadLabel_1 -> setAlignment( Qt::AlignCenter );
    leadLineEdit_1 = new QLineEdit();
    leadLineEdit_1 -> setFixedSize( 100, 20 );
    leadLineEdit_1 -> setText( tr( "0" ) );
    leadLineEdit_1 -> setEnabled( 0 );

    leadLabel_2 = new QLabel( tr( "前视距离２" ) );
    leadLabel_2 -> setFixedSize( 100, 20 );
    leadLabel_2 -> setAlignment( Qt::AlignCenter );
    leadLineEdit_2 = new QLineEdit();
    leadLineEdit_2 -> setFixedSize( 100, 20 );
    leadLineEdit_2 -> setText( tr( "0" ) );
    leadLineEdit_2 -> setEnabled( 0 );

    spdFactorLabel = new QLabel( tr( "速度因子" ) );
    spdFactorLabel -> setFixedSize( 100, 20 );
    spdFactorLabel -> setAlignment( Qt::AlignCenter );
    spdFactorLineEdit = new QLineEdit();
    spdFactorLineEdit -> setFixedSize( 100, 20 );
    spdFactorLineEdit -> setText( tr( "0" ) );
    spdFactorLineEdit -> setEnabled( 0 );

    intModeLabel = new QLabel( tr( "积分模式" ) );
    intModeLabel -> setFixedSize( 100, 20 );
    intModeLabel -> setAlignment( Qt::AlignCenter );
    intModeCombo = new QComboBox();
    intModeCombo -> setFixedSize( 100, 20 );
    intModeCombo -> addItem( tr( "" ) );
    intModeCombo -> addItem( tr( "新模式" ) );
    intModeCombo -> addItem( tr( "旧模式" ) );
    connect( intModeCombo, SIGNAL( currentIndexChanged(int) ), this, SLOT( intModeChanged() ) );

    maxIntLabel = new QLabel( tr( "积分最大项" ) );
    maxIntLabel -> setFixedSize( 100, 20 );
    maxIntLabel -> setAlignment( Qt::AlignCenter );
    maxIntLineEdit= new QLineEdit();
    maxIntLineEdit -> setFixedSize( 100, 20 );
    maxIntLineEdit -> setText( tr( "0" ) );
    maxIntLineEdit -> setEnabled( 0 );

    maxPitchLabel = new QLabel( tr( "俯仰最大项" ) );
    maxPitchLabel -> setFixedSize( 100, 20 );
    maxPitchLabel -> setAlignment( Qt::AlignCenter );
    maxPitchLineEdit = new QLineEdit();
    maxPitchLineEdit -> setFixedSize( 100, 20 );
    maxPitchLineEdit -> setText( tr( "0" ) );
    maxPitchLineEdit -> setEnabled( 0 );

    errDepthLabel = new QLabel( tr( "深度限制" ) );
    errDepthLabel -> setFixedSize( 100, 20 );
    errDepthLabel -> setAlignment( Qt::AlignCenter );
    errDepthLineEdit = new QLineEdit();
    errDepthLineEdit -> setFixedSize( 100, 20 );
    errDepthLineEdit -> setText( tr( "0" ) );
    errDepthLineEdit -> setEnabled( 0 );

    arrivalModeLabel = new QLabel( tr( "到点模式" ) );
    arrivalModeLabel -> setFixedSize( 100, 20 );
    arrivalModeLabel -> setAlignment( Qt::AlignCenter );
    arrivalModeCombo = new QComboBox();
    arrivalModeCombo -> setFixedSize( 100, 20 );
    arrivalModeCombo -> addItem( tr( "" ) );
    arrivalModeCombo -> addItem( tr( "wait" ) );
    arrivalModeCombo -> addItem( tr( "手动控制" ) );
    arrivalModeCombo -> addItem( tr( "自动控制" ) );
    connect( arrivalModeCombo, SIGNAL( currentIndexChanged(int) ), this, SLOT( arrivalModeChanged() ) );

    arrivalTimeLabel = new QLabel( tr( "到点时间" ) );
    arrivalTimeLabel -> setFixedSize( 100, 20 );
    arrivalTimeLabel -> setAlignment( Qt::AlignCenter );
    arrivalTimeLineEdit = new QLineEdit();
    arrivalTimeLineEdit -> setFixedSize( 100, 20 );
    arrivalTimeLineEdit -> setText( tr( "0" ) );
    arrivalTimeLineEdit -> setEnabled( 0 );

    radiusLabel_1 = new QLabel( tr( "大圆半径" ) );
    radiusLabel_1 -> setFixedSize( 100, 20 );
    radiusLabel_1 -> setAlignment( Qt::AlignCenter );
    radiusLineEdit_1 = new QLineEdit();
    radiusLineEdit_1 -> setFixedSize( 100, 20 );
    radiusLineEdit_1 -> setText( tr( "0" ) );
    radiusLineEdit_1 -> setEnabled( 0 );

    radiusLabel_2 = new QLabel( tr( "小圆半径" ) );
    radiusLabel_2 -> setFixedSize( 100, 20 );
    radiusLabel_2 -> setAlignment( Qt::AlignCenter );
    radiusLineEdit_2 = new QLineEdit();
    radiusLineEdit_2 -> setFixedSize( 100, 20 );
    radiusLineEdit_2 -> setText( tr( "0" ) );
    radiusLineEdit_2 -> setEnabled( 0 );

    spdRadiusLabel = new QLabel( tr( "速度半径" ) );
    spdRadiusLabel -> setFixedSize( 100, 20 );
    spdRadiusLabel -> setAlignment( Qt::AlignCenter );
    spdRadiusLineEdit = new QLineEdit();
    spdRadiusLineEdit -> setFixedSize( 100, 20 );
    spdRadiusLineEdit -> setText( tr( "0" ) );
    spdRadiusLineEdit -> setEnabled( 0 );

    sendBtn = new QPushButton( tr( "发送" ) );
    connect( sendBtn, SIGNAL( clicked(bool) ), this, SLOT( SendBtnClicked() ) );

    sendPoisToMap = new QPushButton( tr( "发送路径点到地图" ) );
    sendPoisToMap -> setFixedSize( 150, 20 );
    connect( sendPoisToMap, SIGNAL( clicked(bool) ), this, SLOT( SendToMapBtnClicked() ) );

    sendPoisToUWSim = new QPushButton( tr( "发送路径点到仿真器" ) );
    sendPoisToUWSim -> setFixedSize( 150, 20 );
    connect( sendPoisToUWSim, SIGNAL( clicked(bool) ), this, SLOT( SendToUWSimBtnClicked() ) );

    missionParaGrid = new QGridLayout( this );

    missionParaGrid -> addWidget( sendPoisToMap, 0, 0, 1, 2 );
    missionParaGrid -> addWidget( sendPoisToUWSim, 0, 2, 1, 2 );
    missionParaGrid -> addWidget( sendByIRICheckBox, 0, 5, 1, 1 );
    missionParaGrid -> addWidget( autoReturnCheckBox, 0, 6, 1, 1 );
    missionParaGrid -> addWidget( helixCheckBox, 0, 7, 1, 1 );
    missionParaGrid -> addWidget( tableWidget, 1, 0, 9, 6 );
    missionParaGrid -> addWidget( depthModeLabel, 1, 6, 1, 1 );
    missionParaGrid -> addWidget( depthModeCombo, 1, 7, 1, 1 );
    missionParaGrid -> addWidget( speedLabel, 2, 6, 1, 1 );
    missionParaGrid -> addWidget( speedLineEdit, 2, 7, 1, 1 );
    missionParaGrid -> addWidget( depthLabel, 3, 6, 1, 1 );
    missionParaGrid -> addWidget( depthLineEdit, 3, 7, 1, 1 );
    missionParaGrid -> addWidget( heightLabel, 4, 6, 1, 1 );
    missionParaGrid -> addWidget( heightLineEdit, 4, 7, 1, 1 );
    missionParaGrid -> addWidget( roundsLabel, 5, 6, 1, 1 );
    missionParaGrid -> addWidget( roundsLineEdit, 5, 7, 1, 1 );
    missionParaGrid -> addWidget( radiusLabel, 6, 6, 1, 1 );
    missionParaGrid -> addWidget( radiusLineEdit, 6, 7, 1, 1 );
    missionParaGrid -> addWidget( thresholdLabel, 7, 6, 1, 1 );
    missionParaGrid -> addWidget( thresholdLineEdit, 7, 7, 1, 1 );
    missionParaGrid -> addWidget( steppingDepthLabel, 8, 6, 1, 1 );
    missionParaGrid -> addWidget( steppingDepthLineEdit, 8, 7, 1, 1 );
    missionParaGrid -> addWidget( spdRadiusLabel, 9, 6, 1, 1 );
    missionParaGrid -> addWidget( spdRadiusLineEdit, 9, 7, 1, 1 );
    missionParaGrid -> addWidget( arrivalModeLabel, 10, 0, 1, 1 );
    missionParaGrid -> addWidget( arrivalModeCombo, 10, 1, 1, 1 );
    missionParaGrid -> addWidget( radiusLabel_1, 10, 2, 1, 1 );
    missionParaGrid -> addWidget( radiusLineEdit_1, 10, 3, 1, 1 );
    missionParaGrid -> addWidget( radiusLabel_2, 10, 4, 1, 1 );
    missionParaGrid -> addWidget( radiusLineEdit_2, 10, 5, 1, 1 );
    missionParaGrid -> addWidget( arrivalTimeLabel, 10, 6, 1, 1 );
    missionParaGrid -> addWidget( arrivalTimeLineEdit, 10, 7, 1, 1 );
    missionParaGrid -> addWidget( intModeLabel, 11, 0, 1, 1 );
    missionParaGrid -> addWidget( intModeCombo, 11, 1, 1, 1 );
    missionParaGrid -> addWidget( maxIntLabel, 11, 2, 1, 1 );
    missionParaGrid -> addWidget( maxIntLineEdit, 11, 3, 1, 1 );
    missionParaGrid -> addWidget( maxPitchLabel, 11, 4, 1, 1 );
    missionParaGrid -> addWidget( maxPitchLineEdit, 11, 5, 1, 1 );
    missionParaGrid -> addWidget( errDepthLabel, 11, 6, 1, 1 );
    missionParaGrid -> addWidget( errDepthLineEdit, 11, 7, 1, 1 );
    missionParaGrid -> addWidget( leadModeLabel, 12, 0, 1, 1 );
    missionParaGrid -> addWidget( leadModeCombo, 12, 1, 1, 1 );
    missionParaGrid -> addWidget( leadLabel_1, 12, 2, 1, 1 );
    missionParaGrid -> addWidget( leadLineEdit_1, 12, 3, 1, 1 );
    missionParaGrid -> addWidget( leadLabel_2, 12, 4, 1, 1 );
    missionParaGrid -> addWidget( leadLineEdit_2, 12, 5, 1, 1 );
    missionParaGrid -> addWidget( spdFactorLabel, 12, 6, 1, 1 );
    missionParaGrid -> addWidget( spdFactorLineEdit, 12, 7, 1, 1 );
    missionParaGrid -> addWidget( sendBtn, 13, 4, 1, 1 );
    missionParaGrid -> addWidget( sendBtn, 13, 4, 1, 1 );

    pressbutton_Mission = false;
    sendToMapBtnClicked = false;
    depthMode = "0";
    leadMode = "0";
    intMode = "0";
    arrivalMode = "0";

    mSocket = new QTcpSocket();
}

MissionParaDlg::~MissionParaDlg()
{
    delete missionParaGrid;
}

void MissionParaDlg::getPoisFromMap( std::string sval )
{    
    for( int i = 0; i < tableWidget -> rowCount(); i++ )
    {
        for( int j = 1; j < 4; j ++ )
        {
            tableWidget -> setItem( i, j, new QTableWidgetItem( "" ) );
        }
    }
    std::vector<std::string> s_points = parseString( sval, ":" );
   int n_size = s_points.size();
    if( n_size > 8 )
    {
        n_size = tableWidget -> rowCount();
    }
    std::string points_lon[ n_size ];
    std::string points_lat[ n_size ];
    for( int i=0; i < n_size; i++ )
    {
        points_lon[i] = biteString( s_points[i], ',' );
        points_lat[i] = s_points[i];
        tableWidget -> setItem( i, 1, new QTableWidgetItem( points_lon[i].c_str() ) );
        tableWidget -> setItem( i, 2, new QTableWidgetItem( points_lat[i].c_str() ) );
    }
}


//深度模式槽信号
void MissionParaDlg::depthModeChanged()
{
    QString currentText = depthModeCombo -> currentText();
    if( currentText == "一次定深" )
    {
        speedLineEdit -> setEnabled( 1 );
        depthLineEdit -> setEnabled( 1 );
        heightLineEdit -> setEnabled( 0 );
        roundsLineEdit -> setEnabled( 1 );
        depthMode = "1";
    }
    else if( currentText == "分段定深" )
    {
        speedLineEdit -> setEnabled( 1 );
        depthLineEdit -> setEnabled( 1 );
        heightLineEdit -> setEnabled( 0 );
        roundsLineEdit -> setEnabled( 1 );
        depthMode = "2";
    }
    else if( currentText == "阶跃定深" )
    {
        speedLineEdit -> setEnabled( 1 );
        depthLineEdit -> setEnabled( 1 );
        heightLineEdit -> setEnabled( 0 );
        roundsLineEdit -> setEnabled( 1 );
        depthMode = "3";
    }
    else if( currentText == "连续定高" )
    {
        speedLineEdit -> setEnabled( 1 );
        depthLineEdit -> setEnabled( 0 );
        heightLineEdit -> setEnabled( 1 );
        roundsLineEdit -> setEnabled( 1 );
        depthMode = "4";
    }
    else if( currentText == "分段定高" )
    {
        speedLineEdit -> setEnabled( 1 );
        depthLineEdit -> setEnabled( 0 );
        heightLineEdit -> setEnabled( 1 );
        roundsLineEdit -> setEnabled( 1 );
        depthMode = "5";
    }
    else
    {
        speedLineEdit -> setEnabled( 1 );
        depthLineEdit -> setEnabled( 0 );
        heightLineEdit -> setEnabled( 0 );
        roundsLineEdit -> setEnabled( 0 );
        depthMode = "0";
    }
}

//螺旋槽信号
void MissionParaDlg::helixBoxChecked()
{
    if( helixCheckBox -> isChecked() )
    {
        radiusLineEdit -> setEnabled( 1 );
        thresholdLineEdit -> setEnabled( 1 );
        steppingDepthLineEdit -> setEnabled( 1 );
    }
    else
    {
        radiusLineEdit -> setEnabled( 0 );
        thresholdLineEdit -> setEnabled( 0 );
        steppingDepthLineEdit -> setEnabled( 0 );
    }
}

void MissionParaDlg::arrivalModeChanged()
{
    QString currentText = arrivalModeCombo -> currentText();
    if( currentText == "wait" )
    {
        arrivalTimeLineEdit -> setEnabled( 0 );
        radiusLineEdit_1 -> setEnabled( 1 );
        radiusLineEdit_2 -> setEnabled( 1 );
        spdRadiusLineEdit -> setEnabled( 1 );
        arrivalMode = "1";

    }
    else if( currentText == "自动控制" )
    {
        arrivalTimeLineEdit -> setEnabled( 1 );
        radiusLineEdit_1 -> setEnabled( 1 );
        radiusLineEdit_2 -> setEnabled( 1 );
        spdRadiusLineEdit -> setEnabled( 1 );
        arrivalMode = "2";
    }
    else if( currentText == "手动控制" )
    {
        arrivalTimeLineEdit -> setEnabled( 0 );
        radiusLineEdit_1 -> setEnabled( 1 );
        radiusLineEdit_2 -> setEnabled( 1 );
        spdRadiusLineEdit -> setEnabled( 1 );
        arrivalMode = "3";
    }
    else
    {
        arrivalTimeLineEdit -> setEnabled( 0 );
        radiusLineEdit_1 -> setEnabled( 0 );
        radiusLineEdit_2 -> setEnabled( 0 );
        spdRadiusLineEdit -> setEnabled( 0 );
        arrivalMode = "0";
    }

}
void MissionParaDlg::leadModeChanged()
{
    QString currentText = leadModeCombo -> currentText();
    if( currentText == "固定前视" )
    {
        leadLineEdit_1 -> setEnabled( 1 );
        leadLineEdit_2 -> setEnabled( 0 );
        spdFactorLineEdit -> setEnabled( 1 );
        leadMode = "1";
    }
    else if( currentText == "可变前视" )
    {
        leadLineEdit_1 -> setEnabled( 1 );
        leadLineEdit_2 -> setEnabled( 1 );
        spdFactorLineEdit -> setEnabled( 1 );
        leadMode = "2";
    }
    else
    {
        leadLineEdit_1 -> setEnabled( 0 );
        leadLineEdit_2 -> setEnabled( 0 );
        spdFactorLineEdit -> setEnabled( 0 );
        leadMode = "0";
    }
}
void MissionParaDlg::intModeChanged()
{
    QString currentText = intModeCombo -> currentText();
    if( currentText == "新模式" )
    {
        maxIntLineEdit -> setEnabled( 1 );
        maxPitchLineEdit -> setEnabled( 1 );
        errDepthLineEdit -> setEnabled( 1 );
        intMode = "1";
    }
    else if( currentText == "旧模式" )
    {
        maxIntLineEdit -> setEnabled( 1 );
        maxPitchLineEdit -> setEnabled( 1 );
        errDepthLineEdit -> setEnabled( 0 );
        intMode = "2";
    }
    else
    {
        maxIntLineEdit -> setEnabled( 0 );
        maxPitchLineEdit -> setEnabled( 0 );
        errDepthLineEdit -> setEnabled( 0 );
        intMode = "0";
    }
}

std::string MissionParaDlg::getMissionParam()
{
    std::string missionStr = "";
    std::string pointsStr = "points=";
    std::string surfaceStr = "surface=";
    std::string Param = "";
    bool bHasFirst = false;

    QString qsVal_1 = "";
    std::string sVal_1 = "";
    QString qsVal_2 = "";
    std::string sVal_2 = "";
    QString qsVal_3 = "";
    std::string sVal_3 = "";

    for( int i = 0; i < 8; i++ )
    {
        if( tableWidget -> item( i, 5 ) ->checkState() == Qt::Checked )
        {
            qsVal_1 = tableWidget -> item( i, 1 )->text();
            qsVal_1 = qsVal_1.QString::remove( QRegExp( "\\s" ) );
            sVal_1 = qsVal_1.toStdString();
            qsVal_2 = tableWidget -> item( i, 2 )->text();
            qsVal_2 = qsVal_2.QString::remove( QRegExp( "\\s" ) );
            sVal_2 = qsVal_2.toStdString();
            qsVal_3 = tableWidget -> item( i, 3 )->text();
            qsVal_3 = qsVal_3.QString::remove( QRegExp( "\\s" ) );
            sVal_3 = qsVal_3.toStdString();
            if( sVal_1 != "" && sVal_2 != "" && sVal_3 != "" )
            {
                if( bHasFirst )
                {
                    pointsStr += ":" + sVal_1 + "," + sVal_2 + "," + sVal_3;
                    if(  tableWidget -> item( i, 4 ) ->checkState() == Qt::Checked  )
                    {
                        surfaceStr += ":true";
                    }
                    else
                    {
                        surfaceStr += ":false";
                    }
                }
                else
                {
                    pointsStr += sVal_1 + "," + sVal_2 + "," + sVal_3;
                    if(  tableWidget -> item( i, 4 ) ->checkState() == Qt::Checked  )
                    {
                        surfaceStr += "true";
                    }
                    else
                    {
                        surfaceStr += "false";
                    }
                    bHasFirst = true;
                }
            }
            else if( sVal_1 != "" && sVal_2 != "" )
            {
                if( bHasFirst )
                {
                    pointsStr += ":" + sVal_1 + "," + sVal_2;
                    if(  tableWidget -> item( i, 4 ) ->checkState() == Qt::Checked  )
                    {
                        surfaceStr += ":true";
                    }
                    else
                    {
                        surfaceStr += ":false";
                    }
                }
                else
                {
                    pointsStr += sVal_1 + "," + sVal_2;
                    if(  tableWidget -> item( i, 4 ) ->checkState() == Qt::Checked  )
                    {
                        surfaceStr += "true";
                    }
                    else
                    {
                        surfaceStr += "false";
                    }
                    bHasFirst = true;
                }
            }
        }
    }

    if( autoReturnCheckBox -> isChecked() )
    {
        Param += ";AUTORETURN=true";
    }
    else
    {
        Param += ";AUTORETURN=false";
    }

    QString qsVal = "";
    std::string sVal = "";
    if( depthMode != "0" )
    {
        Param += ";depth_mode=" + depthMode;
        if( speedLineEdit -> isEnabled() )
        {
            qsVal = speedLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";speed=" + sVal;
        }
        if( roundsLineEdit -> isEnabled() )
        {
            qsVal = roundsLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";round=" + sVal;
        }
        if( depthLineEdit -> isEnabled() )
        {
            qsVal = depthLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";depth=" + sVal;
        }
        if( heightLineEdit -> isEnabled() )
        {
            qsVal = heightLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";altitude=" + sVal;
        }
    }
    else
    {
        if( speedLineEdit -> isEnabled() )
        {
            qsVal = speedLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";speed=" + sVal;
        }
    }


    if( helixCheckBox -> isChecked() )
    {
        Param += ";helix=true";
        if( radiusLineEdit -> isEnabled() )
        {
            qsVal = radiusLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";helix_radius=" + sVal;
        }
        if( thresholdLineEdit -> isEnabled() )
        {
            qsVal = thresholdLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";helix_threshold=" + sVal;
        }
        if( steppingDepthLineEdit -> isEnabled() )
        {
            qsVal = steppingDepthLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";helix_depthstep=" + sVal;
        }
    }

    if( arrivalMode != "0" )
    {
        Param += ";DIVE_MODE=" + arrivalMode;
        if( radiusLineEdit_1 -> isEnabled() )
        {
            qsVal = radiusLineEdit_1 -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";MAXR=" + sVal;
        }
        if( radiusLineEdit_2 -> isEnabled() )
        {
            qsVal = radiusLineEdit_2 -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";MINR=" + sVal;
        }
        if( spdRadiusLineEdit -> isEnabled() )
        {
            qsVal = spdRadiusLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";SPDR=" + sVal;
        }
        if( arrivalTimeLineEdit -> isEnabled() )
        {
            qsVal = arrivalTimeLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";WAIT_TIME=" + sVal;
        }
    }

    if( leadMode != "0" )
    {
        Param += ";LEADMODE=" + leadMode;
        if( leadLineEdit_1 -> isEnabled() )
        {
            qsVal = leadLineEdit_1 -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";LEAD=" + sVal;
        }
        if( leadLineEdit_2 -> isEnabled() )
        {
            qsVal = leadLineEdit_2 -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";LEADMIN=" + sVal;
        }
        if( spdFactorLineEdit -> isEnabled() )
        {
            qsVal = spdFactorLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";SPDFACTOR=" + sVal;
        }
    }

    if( intMode != "0" )
    {
        Param += ";INT_MODE=" + intMode;
        if( maxIntLineEdit -> isEnabled() )
        {
            qsVal = maxIntLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";MAX_INT=" + sVal;
        }
        if( maxPitchLineEdit -> isEnabled() )
        {
            qsVal = maxPitchLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";MAX_PIT=" + sVal;
        }
        if( errDepthLineEdit -> isEnabled() )
        {
            qsVal = errDepthLineEdit -> text();
            qsVal = qsVal.QString::remove( QRegExp( "\\s" ) );
            sVal = qsVal.toStdString();
            Param += ";ERR_DEP=" + sVal;
        }
    }


    missionStr = pointsStr + ";" + surfaceStr + Param;
    return missionStr;
}

void MissionParaDlg::SendBtnClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr( "是否发送数据" ),  tr( "确认发送" ),
                                    QMessageBox::Yes | QMessageBox::No );
    if( reply == QMessageBox::Yes )
    {
        pressbutton_Mission = true;
    }
    else if( reply == QMessageBox::No )
    {
        pressbutton_Mission = false;
    }
}

void MissionParaDlg::SendToMapBtnClicked()
{
    sendToMapBtnClicked = true;
}

void MissionParaDlg::SendToUWSimBtnClicked()
{
    tcp_client();
}

void MissionParaDlg::tcp_client()
{
    mSocket -> connectToHost("127.0.0.1",8000);
    std::string pointsStr = getMissionParam();
    QString qsPointsStr = QString::fromStdString( pointsStr );
    mSocket -> write(qsPointsStr.toUtf8());
    //connect( mSocket, SIGNAL(connected()), this, SLOT(connect_suc()) );
    //connect(mSocket,SIGNAL(disconnected()),this,SLOT(client_dis()));
    //mSocket->close();
}

void MissionParaDlg::closeEvent( QCloseEvent *event )
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question( this, tr("退出使命参数设置"), QString(tr("确认退出设置")),
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
