#ifndef EMERGENCYPARADLG_H
#define EMERGENCYPARADLG_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QCloseEvent>

class EmergencyParaDlg : public QDialog
{
    Q_OBJECT
public:
    EmergencyParaDlg( QWidget * parent = 0 );
    ~EmergencyParaDlg();
    bool pressbutton;

private:
    QLabel *maxTaskTimeLabel;
    QLabel *maxTaskDepthLabel;
    QLabel *sustainTaskDepthLabel;
    QLabel *minAltitudeLabel;

    QLineEdit *maxTaskTimeLineEdit;
    QLineEdit *maxTaskDepthLineEdit;
    QLineEdit *sustainDepthTimeLineEdit;
    QLineEdit *sustainTaskDepthLineEdit;
    QLineEdit *sustainAltitudeLineEdit;
    QLineEdit *minAltitudeLineEdit;
    QLineEdit *maxTaskRadiusLineEdit;
    QLineEdit *pPhasestimeLineEdit;

    QCheckBox *sustainDepthTimeBox;
    QCheckBox *sustainAltitudeBox;
    QCheckBox *maxTaskRadiusBox;
    QCheckBox *pPhasestimeRadiusBox;

    QPushButton *sendBtn;

    QGridLayout *emergencyParaGrid;

private slots:
    void sustainBoxChecked();
    void altitudeBoxChecked();
    void RadiusBoxChecked();
    void pPhasestimeChecked();
    void sendBtnClicked();

public:
    void closeEvent( QCloseEvent * );
    std::string sendMsg();

};

#endif // EMERGENCYPARADLG_H
