#ifndef STARTANDVIEWDLG_H
#define STARTANDVIEWDLG_H
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QCloseEvent>


class StartAndViewDlg : public QDialog
{
    Q_OBJECT
public:
    StartAndViewDlg( QWidget * parent = 0 );
    ~StartAndViewDlg();

private:
    QLabel *startLonLabel;
    QLabel *startLatLabel;
    QLineEdit *startLonLineEdit;
    QLineEdit *startLatLineEdit;
    QCheckBox *gpsValidBox;
    QCheckBox *checkBox_1;

    QLabel *northBoundaryLabel;
    QLabel *southBoundaryLabel;
    QLabel *westBoundaryLabel;
    QLabel *eastBoundaryLabel;
    QLineEdit *northBoundaryLineEdit;
    QLineEdit *southBoundaryLineEdit;
    QLineEdit *westBoundaryLineEdit;
    QLineEdit *eastBoundaryLineEdit;
    QCheckBox *checkBox_2;

    QPushButton *sendBtn;

    QGridLayout *startAndViewGrid;

private slots:
    void checkBox1Valid();
    void checkBox2Valid();

public:
    void closeEvent( QCloseEvent * );
};

#endif // STARTANDVIEWDLG_H
