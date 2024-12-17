#include "messageboxdlg.h"

MessageBoxDlg::MessageBoxDlg(QWidget *parent):QDialog(parent)
{
    this->initFrm();
    this->initTimer();
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);
}

MessageBoxDlg::~MessageBoxDlg()
{
    if(this->timer!=nullptr)
    {
        this->timer->stop();
        delete this->timer;
    }
}

void MessageBoxDlg::initFrm()
{
    QGridLayout *mainLayout = new QGridLayout();
    lblTime = new QLabel();
    lblIcon = new QLabel();
    lblTitle = new QLabel();
    lblMessage = new QLabel();
    lblMessage->setAlignment(Qt::AlignCenter);
    btnOk = new QPushButton(tr("确定"));
    btnCancle = new QPushButton(tr("取消"));
    lblIcon->setFixedSize(36,36);
    mainLayout->addWidget(lblTime,0,4);
    mainLayout->addWidget(lblIcon,1,0);
    mainLayout->addWidget(lblTitle,1,1);
    mainLayout->addWidget(lblMessage,2,0,3,5);
    mainLayout->addWidget(btnOk,5,1);
    mainLayout->addWidget(btnCancle,5,3);
    mainLayout->setColumnStretch(0,1);
    mainLayout->setColumnStretch(1,1);
    mainLayout->setColumnStretch(2,1);
    mainLayout->setColumnStretch(3,1);
    mainLayout->setColumnStretch(4,1);
    setLayout(mainLayout);
    resize(480,320);

    connect(btnOk,&QPushButton::clicked,this,&MessageBoxDlg::btnOkClickedSlot);
    connect(btnCancle,&QPushButton::clicked,this,&MessageBoxDlg::btnCancleClickedSlot);
}

void MessageBoxDlg::initTimer()
{
    this->timer = new QTimer(this);
    this->timer->setInterval(1000);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(checkSec()));
    this->timer->start();
}

void MessageBoxDlg::setMessage(const QString &msg, int type, int closeSec)
{
    this->closeSec = closeSec;
    this->currentSec = 0;
    lblTime->clear();
    this->lblMessage->setText(msg);
    if(0 == type)
    {
        this->lblIcon->setStyleSheet("border-image:url(:/resource/images/msg_info.png)");
        this->lblTitle->setText(tr("提示"));
    }
    else if(1 == type)
    {
        this->lblIcon->setStyleSheet("border-image:url(:/resource/images/msg_question.png)");
        this->lblTitle->setText(tr("询问"));
    }
    else if(2 == type)
    {
        this->lblIcon->setStyleSheet("border-image:url(:/resource/images/msg_error.png)");
        this->lblTitle->setText(tr("错误"));
    }
}

void MessageBoxDlg::checkSec()
{
    if(0 == closeSec)
    {
        return;
    }
    if(currentSec < closeSec)
    {
        currentSec++;
    }
    else
    {
        reject();
    }
    QString str = tr("关闭倒计时")+ QString(" %1 ").arg(closeSec - currentSec + 1)+tr("秒");
    lblTime->setText(str);
}

void MessageBoxDlg::btnOkClickedSlot()
{
    accept();
}

void MessageBoxDlg::btnCancleClickedSlot()
{
    reject();
}
