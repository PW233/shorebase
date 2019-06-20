#pragma execution_character_set("utf-8")
#include "emergencyshow.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QTableWidgetItem>
#include "MBUtils.h"
#include <QDebug>
#include <QDateTime>

EmergencyShow::EmergencyShow( QWidget *parent )
    :QDialog( parent )
{
	setWindowTitle( tr( "应急显示" ) );    
     
    tableWidget = new QTableWidget();
    tableWidget -> setEditTriggers( QAbstractItemView::NoEditTriggers ); 
    tableWidget -> setColumnCount(7);  
    tableWidget -> setStyleSheet("selection-background-color:lightblue;");    
 
    QStringList header;
    header << "消息名称" << "告警名称" << "时间" << "类型" << "编号" << "等级" << "备注";
    tableWidget -> setHorizontalHeaderLabels( header );
    tableWidget -> verticalHeader() -> setDefaultSectionSize(20);
    
    for( int i = 0; i < 7; i++ )
    {
    	if( i == 0 )
    	{
    		tableWidget -> setColumnWidth( i, 150 );
    	}
		else if( i == 2 )
		{
			tableWidget -> setColumnWidth( i, 180);
		}
		else if( i == 6 )
		{
			tableWidget -> setColumnWidth( i, 200);
		}
    	else
    	{
    		tableWidget -> setColumnWidth( i, 100 );
    	}
    }
    
    beginBtn = new QPushButton( tr( "开始" ) );
    beginBtn -> setFixedSize( 100, 20 );
    connect( beginBtn, SIGNAL( clicked(bool) ), this, SLOT( beginClicked() ) );
    pauseBtn = new QPushButton( tr( "暂停" ) );
    pauseBtn -> setFixedSize( 100, 20 );
    connect( pauseBtn, SIGNAL( clicked(bool) ), this, SLOT( pauseClicked() ) );
	continueBtn = new QPushButton( tr( "继续" ) );
	continueBtn -> setFixedSize( 100, 20 );
    connect( continueBtn, SIGNAL( clicked(bool) ), this, SLOT( continueClicked() ) );	
	clearBtn = new QPushButton( tr( "清除" ) );
	clearBtn -> setFixedSize( 100, 20 );
    connect( clearBtn, SIGNAL( clicked(bool) ), this, SLOT( clearClicked() ) );
    
    msgTypeLabel = new QLabel( tr( "消息类型" ) );
    msgTypeLabel -> setFixedSize( 100, 20 );
    msgTypeLabel -> setAlignment( Qt::AlignCenter );
    msgTypeCombo = new QComboBox();
    msgTypeCombo -> setFixedSize( 100, 20 );
    msgTypeCombo -> addItem( tr( "ALL" ) );
    msgTypeCombo -> addItem( tr( "AUV_WARN_MSG" ) );
    msgTypeCombo -> addItem( tr( "SHORE_WARN_MSG" ) );
    msgTypeCombo -> addItem( tr( "CHANN_WARN_MSG" ) );
    msgTypeCombo -> addItem( tr( "AUV_EMERGENCY_MSG" ) );
    connect( msgTypeCombo, SIGNAL( currentIndexChanged(int) ), this, SLOT( msgTypeChoice() ) );
    
    
    emergencyShowGrid = new QGridLayout( this );
    
    emergencyShowGrid -> addWidget( beginBtn, 0, 0, 1, 1 );
    emergencyShowGrid -> addWidget( pauseBtn, 0, 1, 1, 1 );
    emergencyShowGrid -> addWidget( continueBtn, 0, 2, 1, 1 );
    emergencyShowGrid -> addWidget( clearBtn, 0, 3, 1, 1 );
    emergencyShowGrid -> addWidget( msgTypeLabel, 0, 5, 1, 1);
    emergencyShowGrid -> addWidget( msgTypeCombo, 0, 6, 1, 1);
    emergencyShowGrid -> addWidget( tableWidget, 1, 0, 10, 7);
    
    pauseEnable = true;
    nMsgType = 0;
}

EmergencyShow::~EmergencyShow()
{

}

void EmergencyShow::getWarnMsgShow( std::string key, std::string sval )
{
	std::string msg_name = key;
	std::string msg_sval = sval;
	tableWidget -> scrollToBottom( );
	if( nMsgType == 0 )
	{
		int row_count = tableWidget -> rowCount(); 
		if( row_count == 500 )
		{
			tableWidget -> clearContents();
			tableWidget -> setRowCount( 0 );
			row_count = tableWidget -> rowCount();
		}
	  	tableWidget -> insertRow( row_count );

	  	tableWidget -> setItem( row_count, 0, new QTableWidgetItem( msg_name.c_str() ) );
	  	QDateTime current_date_time = QDateTime::currentDateTime();
		QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
		tableWidget -> setItem( row_count, 2, new QTableWidgetItem( current_date ) );
	
		std::vector<std::string> svec = parseString( msg_sval, ';' );
		unsigned int size = svec.size();
		if( size == 0 )
		{
		    return;
		}
		for( int i = 0; i < svec.size(); i++ )
		{
		    std::string key_sval = stripBlankEnds( biteString(svec[i],'=') );
		    std::string value_sval = stripBlankEnds( svec[i] );
		    key_sval = toupper( key_sval );
		    value_sval = toupper( value_sval );
		    if( key_sval == "ID" )
		    {
		    	tableWidget -> setItem( row_count, 1, new QTableWidgetItem( value_sval.c_str() ) );
		    }
			if( key_sval == "TYPE" )
			{
				tableWidget -> setItem( row_count, 3, new QTableWidgetItem( value_sval.c_str() ) );
			} 
			if( key_sval == "CODE" )
			{
				tableWidget -> setItem( row_count, 4, new QTableWidgetItem( value_sval.c_str() ) );
			} 
			if( key_sval == "LEVEL" )
			{
				if( value_sval == "FATAL" )
				{
					QTableWidgetItem *item = new QTableWidgetItem( value_sval.c_str() );
					item -> setBackgroundColor(QColor(255,0,0));
					item -> setTextColor(QColor(0,0,0));
					item -> setFont(QFont("Helvetica"));
					tableWidget -> setItem( row_count, 5, item );
				}
				else if( value_sval == "WARN" )
				{
					QTableWidgetItem *item = new QTableWidgetItem( value_sval.c_str() );
					item -> setBackgroundColor(QColor(255,255,51));
					item -> setTextColor(QColor(0,0,0));
					item -> setFont(QFont("Helvetica"));
					tableWidget -> setItem( row_count, 5, item );
				}
			} 
			if( key_sval == "NOTE" )
			{
				tableWidget -> setItem( row_count, 6, new QTableWidgetItem( value_sval.c_str() ) );
			} 
		}		
	}
	else if( nMsgType == 1 )
	{
		if( msg_name == "AUV_WARN_MSG" )
		{
			int row_count = tableWidget -> rowCount(); 
			if( row_count == 500 )
			{
				tableWidget -> clearContents();
				tableWidget -> setRowCount( 0 );
				row_count = tableWidget -> rowCount();
			}
		  	tableWidget -> insertRow( row_count );

		  	tableWidget -> setItem( row_count, 0, new QTableWidgetItem( msg_name.c_str() ) );
		  	QDateTime current_date_time = QDateTime::currentDateTime();
			QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
			tableWidget -> setItem( row_count, 2, new QTableWidgetItem( current_date ) );
	
			std::vector<std::string> svec = parseString( msg_sval, ';' );
			unsigned int size = svec.size();
			if( size == 0 )
			{
				return;
			}
			for( int i = 0; i < svec.size(); i++ )
			{
				std::string key_sval = stripBlankEnds( biteString(svec[i],'=') );
				std::string value_sval = stripBlankEnds( svec[i] );
				key_sval = toupper( key_sval );
				value_sval = toupper( value_sval );
				if( key_sval == "ID" )
				{
					tableWidget -> setItem( row_count, 1, new QTableWidgetItem( value_sval.c_str() ) );
				}
				if( key_sval == "TYPE" )
				{
					tableWidget -> setItem( row_count, 3, new QTableWidgetItem( value_sval.c_str() ) );
				} 
				if( key_sval == "CODE" )
				{
					tableWidget -> setItem( row_count, 4, new QTableWidgetItem( value_sval.c_str() ) );
				} 
				if( key_sval == "LEVEL" )
				{
					if( value_sval == "FATAL" )
					{
						QTableWidgetItem *item = new QTableWidgetItem( value_sval.c_str() );
						item -> setBackgroundColor(QColor(255,0,0));
						item -> setTextColor(QColor(0,0,0));
						item -> setFont(QFont("Helvetica"));
						tableWidget -> setItem( row_count, 5, item );
					}
					else if( value_sval == "WARN" )
					{
						QTableWidgetItem *item = new QTableWidgetItem( value_sval.c_str() );
						item -> setBackgroundColor(QColor(255,255,51));
						item -> setTextColor(QColor(0,0,0));
						item -> setFont(QFont("Helvetica"));
						tableWidget -> setItem( row_count, 5, item );
					}
				} 
				if( key_sval == "NOTE" )
				{
					tableWidget -> setItem( row_count, 6, new QTableWidgetItem( value_sval.c_str() ) );
				} 
			}
		}
	}
	else if( nMsgType == 2 )
	{
		if( msg_name == "SHORE_WARN_MSG" )
		{
			int row_count = tableWidget -> rowCount(); 
			if( row_count == 500 )
			{
				tableWidget -> clearContents();
				tableWidget -> setRowCount( 0 );
				row_count = tableWidget -> rowCount();
			}
		  	tableWidget -> insertRow( row_count );

		  	tableWidget -> setItem( row_count, 0, new QTableWidgetItem( msg_name.c_str() ) );
		  	QDateTime current_date_time = QDateTime::currentDateTime();
			QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
			tableWidget -> setItem( row_count, 2, new QTableWidgetItem( current_date ) );
	
			std::vector<std::string> svec = parseString( msg_sval, ';' );
			unsigned int size = svec.size();
			if( size == 0 )
			{
				return;
			}
			for( int i = 0; i < svec.size(); i++ )
			{
				std::string key_sval = stripBlankEnds( biteString(svec[i],'=') );
				std::string value_sval = stripBlankEnds( svec[i] );
				key_sval = toupper( key_sval );
				value_sval = toupper( value_sval );
				if( key_sval == "ID" )
				{
					tableWidget -> setItem( row_count, 1, new QTableWidgetItem( value_sval.c_str() ) );
				}
				if( key_sval == "TYPE" )
				{
					tableWidget -> setItem( row_count, 3, new QTableWidgetItem( value_sval.c_str() ) );
				} 
				if( key_sval == "CODE" )
				{
					tableWidget -> setItem( row_count, 4, new QTableWidgetItem( value_sval.c_str() ) );
				} 
				if( key_sval == "LEVEL" )
				{
					if( value_sval == "FATAL" )
					{
						QTableWidgetItem *item = new QTableWidgetItem( value_sval.c_str() );
						item -> setBackgroundColor(QColor(255,0,0));
						item -> setTextColor(QColor(0,0,0));
						item -> setFont(QFont("Helvetica"));
						tableWidget -> setItem( row_count, 5, item );
					}
					else if( value_sval == "WARN" )
					{
						QTableWidgetItem *item = new QTableWidgetItem( value_sval.c_str() );
						item -> setBackgroundColor(QColor(255,255,51));
						item -> setTextColor(QColor(0,0,0));
						item -> setFont(QFont("Helvetica"));
						tableWidget -> setItem( row_count, 5, item );
					}
				} 
				if( key_sval == "NOTE" )
				{
					tableWidget -> setItem( row_count, 6, new QTableWidgetItem( value_sval.c_str() ) );
				} 
			}
		}
	}
	else if( nMsgType == 3 )
	{
		if( msg_name == "CHANN_WARN_MSG" )
		{
			int row_count = tableWidget -> rowCount(); 
			if( row_count == 500 )
			{
				tableWidget -> clearContents();
				tableWidget -> setRowCount( 0 );
				row_count = tableWidget -> rowCount();
			}
		  	tableWidget -> insertRow( row_count );

		  	tableWidget -> setItem( row_count, 0, new QTableWidgetItem( msg_name.c_str() ) );
		  	QDateTime current_date_time = QDateTime::currentDateTime();
			QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
			tableWidget -> setItem( row_count, 2, new QTableWidgetItem( current_date ) );
	
			std::vector<std::string> svec = parseString( msg_sval, ';' );
			unsigned int size = svec.size();
			if( size == 0 )
			{
				return;
			}
			for( int i = 0; i < svec.size(); i++ )
			{
				std::string key_sval = stripBlankEnds( biteString(svec[i],'=') );
				std::string value_sval = stripBlankEnds( svec[i] );
				key_sval = toupper( key_sval );
				value_sval = toupper( value_sval );
				if( key_sval == "ID" )
				{
					tableWidget -> setItem( row_count, 1, new QTableWidgetItem( value_sval.c_str() ) );
				}
				if( key_sval == "TYPE" )
				{
					tableWidget -> setItem( row_count, 3, new QTableWidgetItem( value_sval.c_str() ) );
				} 
				if( key_sval == "CODE" )
				{
					tableWidget -> setItem( row_count, 4, new QTableWidgetItem( value_sval.c_str() ) );
				} 
				if( key_sval == "LEVEL" )
				{
					if( value_sval == "FATAL" )
					{
						QTableWidgetItem *item = new QTableWidgetItem( value_sval.c_str() );
						item -> setBackgroundColor(QColor(255,0,0));
						item -> setTextColor(QColor(0,0,0));
						item -> setFont(QFont("Helvetica"));
						tableWidget -> setItem( row_count, 5, item );
					}
					else if( value_sval == "WARN" )
					{
						QTableWidgetItem *item = new QTableWidgetItem( value_sval.c_str() );
						item -> setBackgroundColor(QColor(255,255,51));
						item -> setTextColor(QColor(0,0,0));
						item -> setFont(QFont("Helvetica"));
						tableWidget -> setItem( row_count, 5, item );
					}
				} 
				if( key_sval == "NOTE" )
				{
					tableWidget -> setItem( row_count, 6, new QTableWidgetItem( value_sval.c_str() ) );
				} 
			}
		}
	}
	else if( nMsgType == 4 )
	{
		if( msg_name == "AUV_EMERGENCY_MSG" )
		{
			int row_count = tableWidget -> rowCount(); 
			if( row_count == 500 )
			{
				tableWidget -> clearContents();
				tableWidget -> setRowCount( 0 );
				row_count = tableWidget -> rowCount();
			}
		  	tableWidget -> insertRow( row_count );

		  	tableWidget -> setItem( row_count, 0, new QTableWidgetItem( msg_name.c_str() ) );
		  	QDateTime current_date_time = QDateTime::currentDateTime();
			QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
			tableWidget -> setItem( row_count, 2, new QTableWidgetItem( current_date ) );
	
			std::vector<std::string> svec = parseString( msg_sval, ';' );
			unsigned int size = svec.size();
			if( size == 0 )
			{
				return;
			}
			for( int i = 0; i < svec.size(); i++ )
			{
				std::string key_sval = stripBlankEnds( biteString(svec[i],'=') );
				std::string value_sval = stripBlankEnds( svec[i] );
				key_sval = toupper( key_sval );
				value_sval = toupper( value_sval );
				if( key_sval == "ID" )
				{
					tableWidget -> setItem( row_count, 1, new QTableWidgetItem( value_sval.c_str() ) );
				}
				if( key_sval == "TYPE" )
				{
					tableWidget -> setItem( row_count, 3, new QTableWidgetItem( value_sval.c_str() ) );
				} 
				if( key_sval == "CODE" )
				{
					tableWidget -> setItem( row_count, 4, new QTableWidgetItem( value_sval.c_str() ) );
				} 
				if( key_sval == "LEVEL" )
				{
					if( value_sval == "FATAL" )
					{
						QTableWidgetItem *item = new QTableWidgetItem( value_sval.c_str() );
						item -> setBackgroundColor(QColor(255,0,0));
						item -> setTextColor(QColor(0,0,0));
						item -> setFont(QFont("Helvetica"));
						tableWidget -> setItem( row_count, 5, item );
					}
					else if( value_sval == "WARN" )
					{
						QTableWidgetItem *item = new QTableWidgetItem( value_sval.c_str() );
						item -> setBackgroundColor(QColor(255,255,51));
						item -> setTextColor(QColor(0,0,0));
						item -> setFont(QFont("Helvetica"));
						tableWidget -> setItem( row_count, 5, item );
					}
				} 
				if( key_sval == "NOTE" )
				{
					tableWidget -> setItem( row_count, 6, new QTableWidgetItem( value_sval.c_str() ) );
				} 
			}
		}
	}


}

void EmergencyShow::msgTypeChoice()
{
	QString currentText = msgTypeCombo -> currentText();
    if( currentText == "ALL" )
    {
		nMsgType = 0;
    }
    else if( currentText == "AUV_WARN_MSG" )
    {
		nMsgType = 1;
    }
    else if( currentText == "SHORE_WARN_MSG" )
    {
		nMsgType = 2;
    }
    else if( currentText == "CHANN_WARN_MSG" )
    {
		nMsgType = 3;
    }
    else if( currentText == "AUV_EMERGENCY_MSG" )
    {
		nMsgType = 4;
    }
}

void EmergencyShow::beginClicked()
{
	pauseEnable = false;
}

void EmergencyShow::pauseClicked()
{
	pauseEnable = true;
}
void EmergencyShow::continueClicked()
{
	pauseEnable = false;
}
void EmergencyShow::clearClicked()
{
	tableWidget -> clearContents();
	tableWidget -> setRowCount( 0 );
}

void EmergencyShow::closeEvent( QCloseEvent *event )
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question( this, tr("退出应急显示"), QString(tr("确认退出")),
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
