#ifndef CONFIGUREDLG_H
#define CONFIGUREDLG_H
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>
#include <QLineEdit>
#include <QCloseEvent>

class configureDlg : public QDialog
{
    Q_OBJECT
public:
    configureDlg(QWidget *parent = 0);
    ~configureDlg();
    bool pressbutton;

private:
    QLabel *environmentalConfigLabel;
    QLabel *currentSalinityLabel;
    QLabel *currentTemperatureLabel;
    QLabel *currentPressureLabel;
    QLabel *currentSoundSpeedLabel;
    QLabel *currentDensityLabel;
    QLabel *currentGravitationLabel;
    QLabel *excessiveMotorCurrentLabel;
    QLabel *samplingIntervalLabel;
    QLabel *samplingTimesLabel;
    QLabel *samplingValueLabel;

    QLineEdit *currentSalinityLineEdit;
    QLineEdit *currentTemperatureLineEdit;
    QLineEdit *currentPressureLineEdit;
    QLineEdit *currentSoundSpeedLineEdit;
    QLineEdit *currentDensityLineEdit;
    QLineEdit *currentGravitationLineEdit;
    QLineEdit *samplingIntervalLineEdit;
    QLineEdit *samplingTimesLineEdit;
    QLineEdit *samplingValueLineEdit;

    QPushButton *configureSendButton;

    QGridLayout *configureGrid;

public:
    void closeEvent( QCloseEvent * );

public slots:
    std::string sendMsg();
    void configSendBtnClicked();

};
#endif // CONFIGUREDLG_H
