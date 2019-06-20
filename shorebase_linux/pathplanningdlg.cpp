#include "pathplanningdlg.h"
#include <QString>

PathPlanningDlg::PathPlanningDlg( QWidget *parent )
    :QDialog( parent )
{
    setWindowTitle( tr( "路径规划" ) );
    planningModeLabel = new QLabel( tr( "规划模式" ) );
    planningModeLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    planningModeCombo = new QComboBox();
    planningModeCombo -> addItem( "间隔规划" );
    planningModeCombo -> addItem( "栅格规划" );
    connect( planningModeCombo, SIGNAL( currentIndexChanged(int) ), this, SLOT( planningModeChanged() ) );

    point_a_Label = new QLabel( tr( "A点经纬度" ) );
    point_a_Label -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    point_a_lng_LineEdit = new QLineEdit();
    point_a_lng_LineEdit -> setText( "0" );
    point_a_lat_LineEdit = new QLineEdit();
    point_a_lat_LineEdit -> setText( "0" );

    point_b_Label = new QLabel( tr( "B点经纬度" ) );
    point_b_Label -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    point_b_lng_LineEdit = new QLineEdit();
    point_b_lng_LineEdit -> setText( "0" );
    point_b_lat_LineEdit = new QLineEdit();
    point_b_lat_LineEdit -> setText( "0" );

    point_c_Label = new QLabel( tr( "C点经纬度" ) );
    point_c_Label -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    point_c_lng_LineEdit = new QLineEdit();
    point_c_lng_LineEdit -> setText( "0" );
    point_c_lat_LineEdit = new QLineEdit();
    point_c_lat_LineEdit -> setText( "0" );

    point_d_Label = new QLabel( tr( "D点经纬度" ) );
    point_d_Label -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    point_d_lng_LineEdit = new QLineEdit();
    point_d_lng_LineEdit -> setText( "0" );
    point_d_lat_LineEdit = new QLineEdit();
    point_d_lat_LineEdit -> setText( "0" );

    intervalLabel = new QLabel( tr( "间隔大小(m)" ) );
    intervalLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    intervalLineEdit = new QLineEdit();
    intervalLineEdit -> setText( "0" );

    gridSizeLabel = new QLabel( tr( "栅格大小(m)" ) );
    gridSizeLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    gridSizeLineEdit = new QLineEdit();
    gridSizeLineEdit -> setEnabled( 0 );
    gridSizeLineEdit -> setText( "0" );

    decisionModeLabel = new QLabel( tr( "遍历决策模式" ) );
    decisionModeLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    decisionModeCombo = new QComboBox();
    decisionModeCombo -> setEnabled( 0 );
    decisionModeCombo -> addItem( "通用型" );
    decisionModeCombo -> addItem( "改进型" );
    connect( decisionModeCombo, SIGNAL( currentIndexChanged(int) ), this, SLOT( decisionModeChanged() ) );

    mapTypeLabel = new QLabel( tr( "模拟地图选择" ) );
    mapTypeLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );
    mapTypeCombo = new QComboBox();
    mapTypeCombo -> setEnabled( 0 );
    mapTypeCombo -> addItem( "MapA" );
    mapTypeCombo -> addItem( "MapB" );
    connect( mapTypeCombo, SIGNAL( currentIndexChanged(int) ), this, SLOT( mapTypeChanged() ) );

    sendBtn = new QPushButton( tr( "发送" ) );
    connect( sendBtn, SIGNAL( clicked(bool) ), this, SLOT( sendBtnClicked() ) );

    pathPlanningDlgGrid = new QGridLayout( this );

    pathPlanningDlgGrid -> addWidget( planningModeLabel, 0, 0, 1, 2 );
    pathPlanningDlgGrid -> addWidget( planningModeCombo, 0, 2, 1, 2 );
    pathPlanningDlgGrid -> addWidget( point_a_Label, 1, 0, 1, 2 );
    pathPlanningDlgGrid -> addWidget( point_a_lng_LineEdit, 1, 2, 1, 2 );
    pathPlanningDlgGrid -> addWidget( point_a_lat_LineEdit, 1, 4, 1, 2 );
    pathPlanningDlgGrid -> addWidget( point_b_Label, 1, 6, 1, 2 );
    pathPlanningDlgGrid -> addWidget( point_b_lng_LineEdit, 1, 8, 1, 2 );
    pathPlanningDlgGrid -> addWidget( point_b_lat_LineEdit, 1, 10, 1, 2 );
    pathPlanningDlgGrid -> addWidget( point_c_Label, 2, 0, 1, 2 );
    pathPlanningDlgGrid -> addWidget( point_c_lng_LineEdit, 2, 2, 1, 2 );
    pathPlanningDlgGrid -> addWidget( point_c_lat_LineEdit, 2, 4, 1, 2 );
    pathPlanningDlgGrid -> addWidget( point_d_Label, 2, 6, 1, 2 );
    pathPlanningDlgGrid -> addWidget( point_d_lng_LineEdit, 2, 8, 1, 2 );
    pathPlanningDlgGrid -> addWidget( point_d_lat_LineEdit, 2, 10, 1, 2 );
    pathPlanningDlgGrid -> addWidget( intervalLabel, 3, 0, 1, 2 );
    pathPlanningDlgGrid -> addWidget( intervalLineEdit, 3, 2, 1, 2 );
    pathPlanningDlgGrid -> addWidget( gridSizeLabel, 4, 0, 1, 2 );
    pathPlanningDlgGrid -> addWidget( gridSizeLineEdit, 4, 2, 1, 2 );
    pathPlanningDlgGrid -> addWidget( decisionModeLabel, 4, 6, 1, 2 );
    pathPlanningDlgGrid -> addWidget( decisionModeCombo, 4, 8, 1, 2 );
    pathPlanningDlgGrid -> addWidget( mapTypeLabel, 3, 6, 1, 2 );
    pathPlanningDlgGrid -> addWidget( mapTypeCombo, 3, 8, 1, 2 );
    pathPlanningDlgGrid -> addWidget( sendBtn, 5, 6, 1, 2 );
}

PathPlanningDlg::~PathPlanningDlg()
{
    delete pathPlanningDlgGrid;
}

//规划模式选择槽信号
void PathPlanningDlg::planningModeChanged()
{
    QString currentText = planningModeCombo -> currentText();
    if( currentText == "间隔规划" )
    {
        intervalLineEdit -> setEnabled( 1 );
        gridSizeLineEdit -> setEnabled( 0 );
        decisionModeCombo -> setEnabled( 0 );
        mapTypeCombo -> setEnabled( 0 );
    }
    else if( currentText == "栅格规划" )
    {
        intervalLineEdit -> setEnabled( 0 );
        gridSizeLineEdit -> setEnabled( 1 );
        decisionModeCombo -> setEnabled( 1 );
        mapTypeCombo -> setEnabled( 1 );
    }
}

//遍历决策模式选择槽信号
void PathPlanningDlg::decisionModeChanged()
{
    QString currentText = decisionModeCombo -> currentText();
    if( currentText == "通用型" )
    {

    }
    else if( currentText == "改进型" )
    {

    }
}

//模拟地图选择槽信号
void PathPlanningDlg::mapTypeChanged()
{
    QString currentText = mapTypeCombo -> currentText();
    if( currentText == "MapA" )
    {

    }
    else if( currentText == "MapB" )
    {

    }
}

//发送按钮槽信号
void PathPlanningDlg::sendBtnClicked()
{

}

void PathPlanningDlg::closeEvent( QCloseEvent *event )
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question( this, tr("退出路径规划设置"), QString(tr("确认退出设置")),
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
