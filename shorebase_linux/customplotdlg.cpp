#pragma execution_character_set("utf-8")
#include "customplotdlg.h"
#include <QMessageBox>
#include <QString>
#include "MBUtils.h"

customplotDlg::customplotDlg( QWidget *parent )
    :QDialog(parent)
{
    setWindowTitle( tr( "实时图表监测" ) );

    setupRealtimeDataDemo();

    mainLayout = new QGridLayout( this );
    mainLayout -> addWidget( courseCustomPlot, 0, 0 );
    mainLayout -> addWidget( pitchCustomPlot, 0, 1 );
    mainLayout -> addWidget( rollCustomPlot, 0, 2 );
    mainLayout -> addWidget( speedCustomPlot, 1, 0 );
    mainLayout -> addWidget( depthCustomPlot, 1, 1 );
    mainLayout -> addWidget( heightCustomPlot, 1, 2 );

    bSpeed     	= false;
    bHeading	= false;
    bPitch		= false;
    bRoll		= false;
    bDepth		= false;
    bHeight		= false;

    fSpeed 		= 0.0;
    fHeading 	= 0.0;
    fPitch 		= 0.0;
    fRoll 		= 0.0;
    fDepth 		= 0.0;
    fHeight		= 0.0;
}

customplotDlg::~customplotDlg()
{
    delete mainLayout;
}


//画图初始化
void customplotDlg::setupRealtimeDataDemo()
{


    courseCustomPlot = new QCustomPlot();
    courseCustomPlot -> addGraph();
    courseCustomPlot -> graph( 0 ) -> setPen( QPen( Qt::blue ) );
    courseCustomPlot -> axisRect() -> setupFullAxesBox();
    courseCustomPlot -> yAxis -> setRange( 0, 360, Qt::AlignLeft );
    courseCustomPlot -> xAxis -> setLabel( "时间(s)" );
    courseCustomPlot -> yAxis -> setLabel( "航向(°)" );
    courseCustomPlot -> setInteractions( QCP::iRangeDrag | QCP::iRangeZoom );


    pitchCustomPlot = new QCustomPlot();
    pitchCustomPlot -> addGraph();
    pitchCustomPlot -> graph( 0 ) -> setPen( QPen( Qt::blue ) );
    pitchCustomPlot -> axisRect() -> setupFullAxesBox();
    pitchCustomPlot -> yAxis -> setRange( -90, 90 );
    pitchCustomPlot -> xAxis -> setLabel( "时间(s)" );
    pitchCustomPlot -> yAxis -> setLabel( "俯仰(°)" );
    pitchCustomPlot -> setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);;

    rollCustomPlot = new QCustomPlot();
    rollCustomPlot -> addGraph();
    rollCustomPlot -> graph( 0 ) -> setPen( QPen( Qt::blue ) );
    rollCustomPlot -> axisRect() -> setupFullAxesBox();
    rollCustomPlot -> yAxis -> setRange( -180, 180 );
    rollCustomPlot -> xAxis -> setLabel( "时间(s)" );
    rollCustomPlot -> yAxis -> setLabel( "横滚(°)" );
    rollCustomPlot -> setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    speedCustomPlot = new QCustomPlot();
    speedCustomPlot -> addGraph();
    speedCustomPlot -> graph( 0 ) -> setPen( QPen( Qt::blue ) );
    speedCustomPlot -> axisRect() -> setupFullAxesBox();
    speedCustomPlot -> yAxis -> setRange( 0, 4, Qt::AlignLeft );
    speedCustomPlot -> xAxis -> setLabel( "时间(s)" );
    speedCustomPlot -> yAxis -> setLabel( "速度(m/s)" );
    speedCustomPlot -> setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    depthCustomPlot = new QCustomPlot();
    depthCustomPlot -> addGraph();
    depthCustomPlot -> graph( 0 ) -> setPen( QPen( Qt::blue ) );
    depthCustomPlot -> axisRect() -> setupFullAxesBox();
    depthCustomPlot -> yAxis -> setRange( 0, 20, Qt::AlignLeft );
    depthCustomPlot -> xAxis -> setLabel( "时间(s)" );
    depthCustomPlot -> yAxis -> setLabel( "深度(m)" );
    depthCustomPlot -> setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    heightCustomPlot = new QCustomPlot();
    heightCustomPlot -> addGraph();
    heightCustomPlot -> graph( 0 ) -> setPen( QPen( Qt::blue ) );
    heightCustomPlot -> axisRect() -> setupFullAxesBox();
    heightCustomPlot -> yAxis -> setRange( 0, 20, Qt::AlignLeft );
    heightCustomPlot -> xAxis -> setLabel( "时间(s)" );
    heightCustomPlot -> yAxis -> setLabel( "高度(m)" );
    heightCustomPlot -> setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);


    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0);
}

void customplotDlg::realtimeDataSlot()
{
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;
    static double lastPointKey = 0;


    if (key-lastPointKey > 0.002)
    {
        if( bHeading )
        {
            courseCustomPlot->graph(0)->addData(key, fHeading);
            bHeading = false;
        }
        if( bPitch )
        {
            pitchCustomPlot->graph(0)->addData(key, fPitch);
            bPitch = false;
        }
        if( bRoll )
        {
            rollCustomPlot->graph(0)->addData(key, fRoll);
            bRoll = false;
        }
        if( bSpeed )
        {
            speedCustomPlot->graph(0)->addData(key, fSpeed);
            bSpeed = false;
        }
        if( bDepth )
        {
            depthCustomPlot->graph(0)->addData(key, fDepth);
            bDepth = false;
        }
        if( bHeight )
        {
            heightCustomPlot->graph(0)->addData(key, fHeight);
            bHeight = false;
        }

        lastPointKey = key;
    }


    courseCustomPlot->xAxis->setRange(key, 30, Qt::AlignRight);
    pitchCustomPlot->xAxis->setRange(key, 60, Qt::AlignRight);
    rollCustomPlot->xAxis->setRange(key, 60, Qt::AlignRight);
    speedCustomPlot->xAxis->setRange(key, 20, Qt::AlignRight);
    depthCustomPlot->xAxis->setRange(key, 60, Qt::AlignRight);
    heightCustomPlot->xAxis->setRange(key, 60, Qt::AlignRight);

    courseCustomPlot->replot();
    pitchCustomPlot->replot();
    rollCustomPlot->replot();
    speedCustomPlot->replot();
    depthCustomPlot->replot();
    heightCustomPlot->replot();

}

void customplotDlg::updateInChart( std::string sval )
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
            for( int i = 1; i < size; i++ )
            {
                std::string name = stripBlankEnds(biteString(svec[i], '='));
                std::string value = stripBlankEnds(svec[i]);
                if( name == "SPD" )
                {
                    fSpeed = atof( value.c_str() );
                    bSpeed = true;
                }
                if( name == "HDG" )
                {
                    fHeading = atof( value.c_str() );
                    bHeading = true;
                }
                if( name == "PTH" )
                {
                    fPitch = atof( value.c_str() );
                    bPitch = true;
                }
                if( name == "ROL" )
                {
                    fRoll = atof( value.c_str() );
                    bRoll = true;
                }
                if( name == "DEP" )
                {
                    fDepth = atof( value.c_str() );
                    bDepth = true;
                }
                if( name == "ALT" )
                {
                    fHeight = atof( value.c_str() );
                    bHeight = true;
                }
            }
        }
    }

}

void customplotDlg::closeEvent( QCloseEvent *event )
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question( this, tr("退出图表监测？"), QString(tr("确认退出")),
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
