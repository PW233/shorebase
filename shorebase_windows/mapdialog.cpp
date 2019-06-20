#pragma execution_character_set("utf-8")
#include "mapdialog.h"
#include <QWebEngineView>
#include <QDebug>
#include <QDir>
#include <QLabel>
#include <QUrl>
#include <QCoreApplication>
#include <QFile>
#include "MBUtils.h"
#include <algorithm>
#include <sstream>
#include <QJsonArray>
#include <QJsonDocument>

using namespace std;

MapDialog::MapDialog(QWidget *parent) : QDialog(parent)
{
    viewLayout = new QGridLayout( this );
    m_view = new QWebEngineView( this );
    channel = new QWebChannel( this );
    channel -> registerObject( QString("person"), this );
    m_view -> page() -> setWebChannel( channel );

    QString appDirPath = QCoreApplication::applicationDirPath();
    int fileDirLength_1 = appDirPath.lastIndexOf ("/");
    QString fileDir_1 = appDirPath.right( appDirPath.length() - fileDirLength_1 - 1 );
    QString appUpDirPath_1 = appDirPath.left( appDirPath.length() - fileDir_1.length() - 1 );
    int fileDirLength_2 = appUpDirPath_1.lastIndexOf( "/" );
    QString fileDir_2 = appUpDirPath_1.right( appUpDirPath_1.length() - fileDirLength_2 - 1 );
    QString appUpDirPath_2 = appUpDirPath_1.left( appUpDirPath_1.length() - fileDir_2.length() - 1 );
    qDebug() << appUpDirPath_2;
    m_view -> page() -> load( QUrl(QString("file:///%1/%2")
                             .arg(appUpDirPath_2)
                             .arg("/shoreBase/google Map/GoogleMapAPIv3_offlinePack/index.html")) );

    lonLatLabel = new QLabel( tr( "鼠标位置" ) );
    lonLatLabel -> setFixedSize( 80, 20 );
    lonLatLabel -> setStyleSheet( "background-color:#6aa84f" );
    lonLatLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    lonLatendLabel = new QLabel( tr( "点击位置" ) );
    lonLatendLabel -> setFixedSize( 80, 20 );
    lonLatendLabel -> setStyleSheet( "background-color:#6aa84f" );
    lonLatendLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    inputLonLatLabel = new QLabel( tr( "查询位置" ) );
    inputLonLatLabel -> setFixedSize( 80, 20 );
    inputLonLatLabel -> setStyleSheet( "background-color:#6aa84f" );
    inputLonLatLabel -> setAlignment( Qt::AlignHCenter | Qt::AlignCenter );

    latLineEdit = new QLineEdit();
    latLineEdit -> setFixedSize( 80, 20 );
    latLineEdit -> setFont(QFont("Timers", 8));
    latLineEdit-> setStyleSheet( "background-color:#fff2cc" );
    latLineEdit -> setText( tr( "n/a" ) );
    latLineEdit -> setReadOnly( 1 );

    lonLineEdit = new QLineEdit();
    lonLineEdit -> setFixedSize( 80, 20 );
    lonLineEdit -> setFont(QFont("Timers", 8));
    lonLineEdit-> setStyleSheet( "background-color:#fff2cc" );
    lonLineEdit -> setText( tr( "n/a" ) );
    lonLineEdit -> setReadOnly( 1 );

    lonEndLineEdit = new QLineEdit();
    lonEndLineEdit -> setFixedSize( 80, 20 );
    lonEndLineEdit -> setFont(QFont("Timers", 8));
    lonEndLineEdit-> setStyleSheet( "background-color:#fff2cc" );
    lonEndLineEdit -> setText( tr( "n/a" ) );
    lonEndLineEdit -> setReadOnly( 1 );

    latEndLineEdit = new QLineEdit();
    latEndLineEdit -> setFixedSize( 80, 20 );
    latEndLineEdit -> setFont(QFont("Timers", 8));
    latEndLineEdit-> setStyleSheet( "background-color:#fff2cc" );
    latEndLineEdit -> setText( tr( "n/a" ) );
    latEndLineEdit -> setReadOnly( 1 );

    inputLonLineEdit = new QLineEdit();
    inputLonLineEdit -> setFixedSize( 80, 20 );
    inputLonLineEdit -> setFont(QFont("Timers", 8));
    inputLonLineEdit-> setStyleSheet( "background-color:#fff2cc" );

    inputLatLineEdit = new QLineEdit();
    inputLatLineEdit -> setFixedSize( 80, 20 );
    inputLatLineEdit -> setFont(QFont("Timers", 8));
    inputLatLineEdit-> setStyleSheet( "background-color:#fff2cc" );

    sendLonLatBtn = new QPushButton( tr( "查询" ) );
    sendLonLatBtn -> setFixedSize( 50, 20 );
   // connect( sendLonLatBtn, SIGNAL( clicked(bool) ), this, SLOT( sendLonLatToJS() ) );

    viewLayout -> addWidget( m_view, 0, 0, 8, 10 );
    viewLayout -> addWidget( lonLatLabel, 9, 0, 1, 1 );
    viewLayout -> addWidget( lonLineEdit, 9, 1, 1, 1 );
    viewLayout -> addWidget( latLineEdit, 9, 2, 1, 1 );
    viewLayout -> addWidget( lonLatendLabel, 9, 3, 1, 1 );
    viewLayout -> addWidget( lonEndLineEdit, 9, 4, 1, 1 );
    viewLayout -> addWidget( latEndLineEdit, 9, 5, 1, 1 );
    viewLayout -> addWidget( inputLonLatLabel, 9, 6, 1, 1 );
    viewLayout -> addWidget( inputLonLineEdit, 9, 7, 1, 1 );
    viewLayout -> addWidget( inputLatLineEdit, 9, 8, 1, 1 );
    viewLayout -> addWidget( sendLonLatBtn, 9, 9, 1, 1 );

    sPoisFromMap = "";
    bSendPois = false;
}

MapDialog::~MapDialog()
{
    channel -> deregisterObject(this);
    delete viewLayout;
}


void MapDialog::getCoordinates( QString lng, QString lat, int flag )
{
    if( flag )
    {
        QString tempLon = lng + "°";
        QString tempLat = lat + "°";
        this -> latLineEdit -> setText( tempLat );
        this -> lonLineEdit -> setText( tempLon );
    }
    else
    {
        QString tempEndLon = lng + "°";
        QString tempEndLat = lat + "°";
        this -> latEndLineEdit -> setText( tempEndLat );
        this -> lonEndLineEdit -> setText( tempEndLon );
    }
}

void MapDialog::getPointsFromMap( QString mapPointsStr )
{
    sPoisFromMap = mapPointsStr.toStdString();

    int pos = 0;
    while( ( pos = sPoisFromMap.find("\"") ) != -1)
    {
        sPoisFromMap.erase(pos, 1);
    }
    bSendPois = true;

    //missParaDlg -> getPointsFromBaidu( PointsFromMap );
    /*
    vector<string> s_points = parseString( getPoints, ":" );
    int n_size = s_points.size();

    string points_lon[ n_size ];
    string points_lat[ n_size ];
    vector<double> d_points_lon( n_size );
    vector<double> d_points_lat( n_size );

    for( int i=0; i < n_size; i++ )
    {
        points_lon[i] = biteString( s_points[i], ',' );
        points_lat[i] = s_points[i];
        stringstream lon_temp, lat_temp;
        lon_temp << points_lon[i];
        lon_temp >> d_points_lon[i];
        lat_temp << points_lat[i];
        lat_temp >> d_points_lat[i];
    }

    vector<double> distance( n_size-1 );
    for( int i = 0; i < n_size-1; i++ )
    {
        distance[i] = Distance( d_points_lon[i], d_points_lat[i], d_points_lon[i+1], d_points_lat[i+1] );
    }

    vector<double> d_time( n_size-1 );
    for( int i = 0; i < n_size-1; i++ )
    {
        d_time[i] = distance[i] / 10.0;
    }

    for( int i = 0; i < n_size; i++ )
    {
        qDebug() << d_points_lon[i] << d_points_lat[i] << endl;
    }

    vector<string> s_time( n_size-1 );
    for( int i = 0; i < n_size-1; i++ )
    {
        qDebug() << d_time[i] << endl;
        stringstream time_temp;
        time_temp << d_time[i];
        time_temp >> s_time[i];
        WriteLine( QString::fromStdString(s_time[i]) );
    }
    */

}

void MapDialog::resizeEvent(QResizeEvent *)
{
    m_view -> resize( this->size() );
}

void MapDialog::sendLonLatToJS()
{
    QString lng = inputLonLineEdit -> text();
    QString lat = inputLatLineEdit -> text();
    QString cmd=QString("theLocation(\"%1\",\"%2\")").arg(lng).arg(lat);
    m_view -> page() -> runJavaScript( cmd );
}

void MapDialog::sendDateToMap( std::string sval )
{
    float fSpeed = 0.0;
    float fHeading = 0.0;
    float fPitch = 0.0;
    float fRoll = 0.0;

    std::string gpsStatus;
    std::string gpsLat;
    std::string gpsLon;
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
                }
                if( name == "HDG" )
                {
                    fHeading = atof( value.c_str() );
                }
                if( name == "PTH" )
                {
                    fPitch = atof( value.c_str() );
                }
                if( name == "ROL" )
                {
                    fRoll = atof( value.c_str() );
                }
                if( name == "GPSSTATUS" )
                {
                    gpsStatus = value;
                }
                if( name == "GPSLAT" )
                {
                    gpsLat = value;
                }
                if( name == "GPSLON" )
                {
                    gpsLon = value;
                }

            }
        }
    }
    QString cmd = QString("getDateFromMoos(%1,%2,%3,%4)").arg(fSpeed).arg(fHeading).arg(fPitch).arg(fRoll);
    m_view -> page() -> runJavaScript( cmd );

    if( gpsStatus == "A" )
    {
        QString cmd_1=QString("auvLocation(\"%1\",\"%2\")").arg( gpsLon.c_str() ).arg( gpsLat.c_str() );
        m_view -> page() -> runJavaScript( cmd_1 );
    }
}

void MapDialog::trackShow( std::string sval )
{
    QJsonArray lng_json;
    QJsonArray lat_json;
    QJsonDocument lng_document;
    QJsonDocument lat_document;
    QByteArray lng_byteArray;
    QByteArray lat_byteArray;
    std::vector<std::string> svec = parseString( sval, ';' );
    unsigned int size = svec.size();
    if( size <= 0 )
    {
        return;
    }
    else
    {
        std::string name_temp = stripBlankEnds(biteString(svec[0], '='));
        std::string value_temp = stripBlankEnds(svec[0]);
        if( name_temp == "points" )
        {
            std::vector<std::string> svec_pois = parseString( value_temp, ':' );
            unsigned int size_pois = svec_pois.size();
            if( size_pois <= 0 )
            {
                return;
            }
            else
            {
                for( int i = 0; i < size_pois; i++ )
                {
                    lng_json.append( stripBlankEnds(biteString(svec_pois[i], ',')).c_str() );
                    lat_json.append( stripBlankEnds(svec_pois[i]).c_str() );
                }

            }
        }
    }

    lng_document.setArray(lng_json);
    lng_byteArray = lng_document.toJson(QJsonDocument::Compact);
    QString lngJson(lng_byteArray);

    lat_document.setArray(lat_json);
    lat_byteArray = lat_document.toJson(QJsonDocument::Compact);
    QString latJson(lat_byteArray);
    //qDebug() << lngJson;
    //qDebug() << latJson;
    QString cmd = QString( "showArray( %1, %2 )" ).arg(lngJson).arg(latJson);
    m_view -> page() -> runJavaScript( cmd );
}

void MapDialog::shipShow( std::string key, std::string sval )
{
    //MOOSTrace("key==%s\n",key.c_str());
    //MOOSTrace("sval==%s\n",sval.c_str());
    if( key == "SHIP_Lon" )
    {
        shipLng = sval;
        //shipLng = "120.293341";
    }
    if( key == "SHIP_Lat" )
    {
        shipLat = sval;
        //shipLat = "36.050522";
    }
    if( shipLat != "" && shipLng != "" )
    {
        QString cmd=QString("theLocation(\"%1\",\"%2\")").arg( shipLng.c_str() ).arg( shipLat.c_str() );
        m_view -> page() -> runJavaScript( cmd );
    }

}

/*
void MapDialog::gpsShow( std::string key, std::string sval )
{
    std::string gpsLat;
    std::string gpsLon;
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
            if( key == "NODE_REPORT_LOCAL" )
            {
                for( int i = 1; i < size; i++ )
                {
                    std::string name = toupper( stripBlankEnds(biteString(svec[i], '=')).c_str() );
                    std::string value = stripBlankEnds(svec[i]);
                    if( name == "GPSLAT" )
                    {
                        gpsLat = value;
                    }
                    if( name == "GPSLON" )
                    {
                        gpsLon = value;
                    }
                }
            }
        }
    }
    if( gpsLat != "" && gpsLon != "" )
    {
     //   QString cmd=QString("theLocation(\"%1\",\"%2\")").arg( gpsLon.c_str() ).arg( gpsLat.c_str() );
    //	m_view -> page() -> runJavaScript( cmd );
    }
}
*/

/*
void MapDialog::WriteLine(QString points)
{
    QFile file("/home/cm/UVLMiniAuv/moos-ivp-12.2/ivp/src/shoreBase/points.txt");
    if ( file.open( QIODevice::ReadWrite | QIODevice::Text ) )
    {
        QTextStream txtOutput(&file);
        QString s1(points);

        txtOutput << "type=" << "w" << endl;
        txtOutput << "time=" << s1 << endl;
    }
    file.close();
}

double MapDialog::Distance( double lon1,double lat1, double lon2,double lat2 )
{
    double lon_delta = ( lon1 - lon2 )*100000;
    double lat_delta = ( lat1 - lat2 )*100000;
    double distance = sqrt( lon_delta * lon_delta + lat_delta * lat_delta );
    return distance;
}
*/
