#ifndef FRMMESSAGEBOX_H
#define FRMMESSAGEBOX_H

#include <QWidget>
#include <QtWidgets>
#include <QPropertyAnimation>
#include <QTimer>
#include <QDebug>
//自定义控件,对话框提示，告警,自动关闭
class FrmMessageBox : public QWidget
{
    Q_OBJECT
public:
    explicit FrmMessageBox(QWidget *parent = nullptr);
    ~FrmMessageBox();

    void initFrm();
    void initTimer();
    void setMessage(const QString &msg,int type,int closeSec);
    void showFrm(const QString &msg,int type = 2,int closeSec = 10);
    void hideFrm();
signals:

private slots:
    void animationFinishSlot();
    void btnOkClickedSlot();
    void btnCancleClickedSlot();
    void checkSec();

private:
    QLabel *lblTime;
    QLabel *lblIcon;
    QLabel *lblTitle;
    QLabel *lblMessage;
    QPushButton *btnOk;
    QPushButton *btnCancle;

    int closeSec;       //总显示时间
    int currentSec;     //当前已显示时间
    QPropertyAnimation *animation;
    QTimer *timer;

    bool bIsHide;
};

#endif // FRMMESSAGEBOX_H
