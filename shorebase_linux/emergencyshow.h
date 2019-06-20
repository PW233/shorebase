#ifndef EMERGENCYSHOW_H
#define EMERGENCYSHOW_H
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QCloseEvent>
#include <QGridLayout>
#include <QTableWidget>
#include <QComboBox>


class EmergencyShow : public QDialog
{
    Q_OBJECT
public:
    EmergencyShow( QWidget * parent = 0 );
    ~EmergencyShow();    
    QTableWidget *tableWidget;

private:
	QPushButton *pauseBtn;
	QPushButton *continueBtn;	
	QPushButton *clearBtn;
	QPushButton *beginBtn;
	QLabel *msgTypeLabel;
	QComboBox *msgTypeCombo;
	QGridLayout *emergencyShowGrid;
	
	int nMsgType;
    	
private slots:
	void beginClicked();
	void pauseClicked();
	void continueClicked();
	void clearClicked();
	void msgTypeChoice();


public:
    void closeEvent( QCloseEvent * );
    void getWarnMsgShow( std::string key, std::string sval );
    bool pauseEnable;


};

#endif // EMERGENCYSHOW_H
