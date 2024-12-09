#ifndef MESSAGEBOXDLG_H
#define MESSAGEBOXDLG_H

#include <QDialog>
#include <QtWidgets>
#include <QTimer>

class MessageBoxDlg : public QDialog
{
    Q_OBJECT
public:
    MessageBoxDlg(QWidget *parent = 0);
    ~MessageBoxDlg();

    void initFrm();
    void initTimer();

    void setMessage(const QString &msg, int type, int closeSec);

private slots:
    void checkSec();

    void btnOkClickedSlot();
    void btnCancleClickedSlot();

private:
    QLabel *lblTime;
    QLabel *lblIcon;
    QLabel *lblTitle;
    QLabel *lblMessage;
    QPushButton *btnOk;
    QPushButton *btnCancle;

    int closeSec;                   //总显示时间
    int currentSec;                 //当前已显示时间
    QTimer *timer;
};

#endif // MESSAGEBOXDLG_H
