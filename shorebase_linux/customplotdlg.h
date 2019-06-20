#ifndef CUSTOMPLOTDLG_H
#define CUSTOMPLOTDLG_H

#include <QLabel>
#include <QMainWindow>
#include <QDialog>
#include <QGridLayout>
#include <QCloseEvent>
#include "qcustomplot.h"
#include <QTimer>
#include <QTime>

class customplotDlg : public QDialog
{
    Q_OBJECT
public:
    customplotDlg(QWidget *parent = 0);
    ~customplotDlg();
    void setupRealtimeDataDemo();

private:
    QGridLayout *mainLayout;

    QCustomPlot *courseCustomPlot;
    QCustomPlot *pitchCustomPlot;
    QCustomPlot *rollCustomPlot;
    QCustomPlot *speedCustomPlot;
    QCustomPlot *depthCustomPlot;
    QCustomPlot *heightCustomPlot;

    QTimer dataTimer;

    bool bSpeed;
    bool bHeading;
    bool bPitch;
    bool bRoll;
    bool bDepth;
    bool bHeight;

    float fSpeed;
    float fHeading;
    float fPitch;
    float fRoll;
    float fDepth;
    float fHeight;

public:
    void updateInChart( std::string sval );
    void closeEvent( QCloseEvent * );

private slots:
    void realtimeDataSlot();


};

#endif // CUSTOMPLOTDLG_H
