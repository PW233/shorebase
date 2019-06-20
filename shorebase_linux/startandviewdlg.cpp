#pragma execution_character_set("utf-8")
#include "startandviewdlg.h"

StartAndViewDlg::StartAndViewDlg( QWidget *parent )
    :QDialog( parent )
{
    setWindowTitle( tr( "起点及视野设置" ) );

    startLonLabel = new QLabel( tr( "起点经度:" ) );
    startLatLabel = new QLabel( tr( "起点纬度:" ) );

    startLonLineEdit = new QLineEdit();
    startLonLineEdit -> setText( tr( "0" ) );
    startLonLineEdit -> setEnabled( 0 );

    startLatLineEdit = new QLineEdit();
    startLatLineEdit -> setText( tr( "0" ) );
    startLatLineEdit -> setEnabled( 0 );

    gpsValidBox = new QCheckBox( tr( "使能GPS" ) );
    gpsValidBox -> setChecked( true );
    gpsValidBox -> setEnabled( 0 );

    checkBox_1 = new QCheckBox( tr( "起点选中" ) );
    checkBox_1 -> setChecked( false );

    northBoundaryLabel = new QLabel( tr( "北向边界(m)" ) );
    southBoundaryLabel = new QLabel( tr( "南向边界(m)" ) );
    westBoundaryLabel = new QLabel( tr( "西向边界(m)" ) );
    eastBoundaryLabel = new QLabel( tr( "东向边界(m)" ) );

    northBoundaryLineEdit = new QLineEdit();
    northBoundaryLineEdit -> setText( tr( "1000" ) );
    northBoundaryLineEdit -> setEnabled( 0 );

    southBoundaryLineEdit = new QLineEdit();
    southBoundaryLineEdit -> setText( tr( "1000" ) );
    southBoundaryLineEdit -> setEnabled( 0 );

    westBoundaryLineEdit = new QLineEdit();
    westBoundaryLineEdit -> setText( tr( "1000" ) );
    westBoundaryLineEdit -> setEnabled( 0 );

    eastBoundaryLineEdit = new QLineEdit();
    eastBoundaryLineEdit -> setText( tr( "1000" ) );
    eastBoundaryLineEdit -> setEnabled( 0 );

    checkBox_2 = new QCheckBox( tr( "视野选中" ) );
    checkBox_2 -> setChecked( false );

    sendBtn = new QPushButton( tr( "发送" ) );
//    sendBtn -> setEnabled( 0 );

    startAndViewGrid = new QGridLayout( this );
    startAndViewGrid -> addWidget( checkBox_1, 0, 0 );
    startAndViewGrid -> addWidget( startLonLabel, 1, 0 );
    startAndViewGrid -> addWidget( startLonLineEdit, 1, 1 );
    startAndViewGrid -> addWidget( startLatLabel, 1, 2 );
    startAndViewGrid -> addWidget( startLatLineEdit, 1, 3 );
    startAndViewGrid -> addWidget( gpsValidBox, 1, 4 );
    startAndViewGrid -> addWidget( checkBox_2, 2, 0 );
    startAndViewGrid -> addWidget( northBoundaryLabel, 3, 0 );
    startAndViewGrid -> addWidget( northBoundaryLineEdit, 3, 1 );
    startAndViewGrid -> addWidget( southBoundaryLabel, 3, 2 );
    startAndViewGrid -> addWidget( southBoundaryLineEdit, 3, 3 );
    startAndViewGrid -> addWidget( westBoundaryLabel, 4, 0 );
    startAndViewGrid -> addWidget( westBoundaryLineEdit, 4, 1 );
    startAndViewGrid -> addWidget( eastBoundaryLabel, 4, 2 );
    startAndViewGrid -> addWidget( eastBoundaryLineEdit, 4, 3 );
    startAndViewGrid -> addWidget( sendBtn, 5, 2 );

    connect( checkBox_1, SIGNAL( toggled(bool) ), this, SLOT( checkBox1Valid() ) );
    connect( checkBox_2, SIGNAL( toggled(bool) ), this, SLOT( checkBox2Valid() ) );
}

StartAndViewDlg::~StartAndViewDlg()
{
    delete startAndViewGrid;
}

void StartAndViewDlg::checkBox1Valid()
{
    if( checkBox_1 -> isChecked() )
    {
        startLonLineEdit -> setEnabled( 1 );
        startLatLineEdit -> setEnabled( 1 );
        gpsValidBox -> setEnabled( 1 );
    }
    else
    {
        startLonLineEdit -> setEnabled( 0 );
        startLatLineEdit -> setEnabled( 0 );
        gpsValidBox -> setEnabled( 0 );
    }
}

void StartAndViewDlg::checkBox2Valid()
{
    if( checkBox_2 -> isChecked() )
    {
        northBoundaryLineEdit -> setEnabled( 1 );
        southBoundaryLineEdit -> setEnabled( 1 );
        westBoundaryLineEdit -> setEnabled( 1 );
        eastBoundaryLineEdit -> setEnabled( 1 );
    }
    else
    {
        northBoundaryLineEdit -> setEnabled( 0 );
        southBoundaryLineEdit -> setEnabled( 0 );
        westBoundaryLineEdit -> setEnabled( 0 );
        eastBoundaryLineEdit -> setEnabled( 0 );
    }
}

void StartAndViewDlg::closeEvent( QCloseEvent *event )
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question( this, tr("退出起点及视野设置"), QString(tr("确认退出起点及视野设置")),
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
