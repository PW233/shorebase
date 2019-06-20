#ifndef MISSIONPARADLG_H
#define MISSIONPARADLG_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QCloseEvent>
#include <QGridLayout>
#include <QTableWidget>
#include <QTcpSocket>


class MissionParaDlg : public QDialog
{
    Q_OBJECT
public:
    MissionParaDlg( QWidget * parent = 0 );
    ~MissionParaDlg();
    QTableWidget *tableWidget;

private:

    QLabel *depthModeLabel;
    QLabel *speedLabel;
    QLabel *depthLabel;
    QLabel *heightLabel;
    QLabel *roundsLabel;
    QLabel *radiusLabel;
    QLabel *thresholdLabel;
    QLabel *steppingDepthLabel;

    QLineEdit *speedLineEdit;
    QLineEdit *depthLineEdit;
    QLineEdit *heightLineEdit;
    QLineEdit *roundsLineEdit;
    QLineEdit *radiusLineEdit;
    QLineEdit *thresholdLineEdit;
    QLineEdit *steppingDepthLineEdit;

    QComboBox *depthModeCombo;

    QCheckBox *helixCheckBox;
    QCheckBox *autoReturnCheckBox;
    QCheckBox *sendByIRICheckBox;

    QLabel *leadModeLabel;
    QLabel *leadLabel_1;
    QLabel *leadLabel_2;
    QLabel *spdFactorLabel;
    QComboBox *leadModeCombo;
    QLineEdit *leadLineEdit_1;
    QLineEdit *leadLineEdit_2;
    QLineEdit *spdFactorLineEdit;

    QLabel *intModeLabel;
    QLabel *maxIntLabel;
    QLabel *maxPitchLabel;
    QLabel *errDepthLabel;
    QComboBox *intModeCombo;
    QLineEdit *maxIntLineEdit;
    QLineEdit *maxPitchLineEdit;
    QLineEdit *errDepthLineEdit;

    QLabel *arrivalModeLabel;
    QLabel *arrivalTimeLabel;
    QLabel *radiusLabel_1;
    QLabel *radiusLabel_2;
    QLabel *spdRadiusLabel;
    QComboBox *arrivalModeCombo;
    QLineEdit *arrivalTimeLineEdit;
    QLineEdit *radiusLineEdit_1;
    QLineEdit *radiusLineEdit_2;
    QLineEdit *spdRadiusLineEdit;

    QPushButton *sendBtn;
    QPushButton *sendPoisToMap;
    QPushButton *sendPoisToUWSim;

    QGridLayout *missionParaGrid;

    std::string depthMode;
    std::string leadMode;
    std::string intMode;
    std::string arrivalMode;

    void tcp_client();
    QTcpSocket *mSocket;


private slots:
    void depthModeChanged();
    void arrivalModeChanged();
    void leadModeChanged();
    void intModeChanged();
    void helixBoxChecked();
    void SendBtnClicked();
    void SendToMapBtnClicked();
    void SendToUWSimBtnClicked();
public:
    void getPoisFromMap( std::string );
    void closeEvent( QCloseEvent * );
    std::string getMissionParam();

    bool pressbutton_Mission;
    bool sendToMapBtnClicked;

};

#endif // MISSIONPARADLG_H
