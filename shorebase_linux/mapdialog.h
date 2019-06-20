#ifndef MAPDIALOG_H
#define MAPDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDockWidget>
#include <QWebChannel>
#include <QPushButton>


namespace Ui {
class Dialog;
}

class QWebEngineView;
class MapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MapDialog(QWidget *parent = 0);
    ~MapDialog();
    void resizeEvent(QResizeEvent *);
    std::string sPoisFromMap;
    bool bSendPois;

    void sendDateToMap( std::string sval );
    void trackShow( std::string sval );
    void shipShow( std::string key, std::string sval );
//    void gpsShow( std::string key, std::string sval );

private:
    QWebChannel *channel;
    QWebEngineView *m_view;
    QGridLayout *viewLayout;

    QLabel *lonLatLabel;
    QLabel *lonLatendLabel;
    QLabel *inputLonLatLabel;

    QLineEdit *latLineEdit;
    QLineEdit *lonLineEdit;
    QLineEdit *lonEndLineEdit;
    QLineEdit *latEndLineEdit;
    QLineEdit *inputLonLineEdit;
    QLineEdit *inputLatLineEdit;

    QPushButton *sendLonLatBtn;

    std::string shipLng;
    std::string shipLat;

public slots:
    void getCoordinates( QString lng, QString lat, int flag );
    void getPointsFromMap( QString points );
    void sendLonLatToJS();
//    void WriteLine(QString points);   //20181220
//    double Distance( double lat1,double lon1, double lat2,double lon2 );
};

#endif // MAPDIALOG_H
