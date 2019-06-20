#ifndef PATHPLANNINGDLG_H
#define PATHPLANNINGDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QCloseEvent>
#include <QGridLayout>


class PathPlanningDlg : public QDialog
{
    Q_OBJECT
public:
    PathPlanningDlg( QWidget * parent = 0 );
    ~PathPlanningDlg();

private:
    QLabel *planningModeLabel;
    QLabel *point_a_Label;
    QLabel *point_b_Label;
    QLabel *point_c_Label;
    QLabel *point_d_Label;
    QLabel *intervalLabel;
    QLabel *gridSizeLabel;
    QLabel *decisionModeLabel;
    QLabel *mapTypeLabel;

    QLineEdit *point_a_lng_LineEdit;
    QLineEdit *point_a_lat_LineEdit;
    QLineEdit *point_b_lng_LineEdit;
    QLineEdit *point_b_lat_LineEdit;
    QLineEdit *point_c_lng_LineEdit;
    QLineEdit *point_c_lat_LineEdit;
    QLineEdit *point_d_lng_LineEdit;
    QLineEdit *point_d_lat_LineEdit;
    QLineEdit *intervalLineEdit;
    QLineEdit *gridSizeLineEdit;

    QComboBox *planningModeCombo;
    QComboBox *decisionModeCombo;
    QComboBox *mapTypeCombo;

    QPushButton *sendBtn;

    QGridLayout *pathPlanningDlgGrid;

private slots:
    void planningModeChanged();
    void decisionModeChanged();
    void mapTypeChanged();
    void sendBtnClicked();

public:
    void closeEvent( QCloseEvent * );

};

#endif // PATHPLANNINGDLG_H
