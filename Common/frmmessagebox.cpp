#include "frmmessagebox.h"

FrmMessageBox::FrmMessageBox(QWidget *parent) : QWidget(parent)
{
    initFrm();
    initTimer();
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);
    this->animation = new QPropertyAnimation(this,"windowOpacity");
    this->animation->setDuration(500);
    this->animation->setEasingCurve(QEasingCurve::Linear);
    connect(this->animation,&QPropertyAnimation::finished,this,&FrmMessageBox::animationFinishSlot);
}

FrmMessageBox::~FrmMessageBox()
{
    if(this->timer!=nullptr)
    {
        this->timer->stop();
        delete this->timer;
    }
}

void FrmMessageBox::initFrm()
{
    //qDebug()<<QString("initFrm");
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

    connect(btnOk,&QPushButton::clicked,this,&FrmMessageBox::btnOkClickedSlot);
    connect(btnCancle,&QPushButton::clicked,this,&FrmMessageBox::btnCancleClickedSlot);
}

void FrmMessageBox::initTimer()
{
    //qDebug()<<QString("initTimer");
    this->timer = new QTimer(this);
    this->timer->setInterval(1000);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(checkSec()));
    this->timer->start();
}

void FrmMessageBox::setMessage(const QString &msg, int type, int closeSec)
{
    //qDebug()<<QString("setMessage");
    this->closeSec = closeSec;
    this->currentSec = 0;
    lblTime->clear();
    this->lblMessage->setText(msg);
    if(0 == type)
    {
        this->lblIcon->setStyleSheet("border-image:url(:/resource/images/msg_error.png)");
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

void FrmMessageBox::showFrm(const QString &msg, int type, int closeSec)
{
    this->setMessage(msg,type,closeSec);
    this->show();
    this->bIsHide = false;
    this->animation->setStartValue(0);
    this->animation->setEndValue(1);
    this->animation->start();
}

void FrmMessageBox::hideFrm()
{
    animation->setStartValue(1);
    animation->setEndValue(0);
    this->animation->start();
    this->bIsHide = true;
}

void FrmMessageBox::animationFinishSlot()
{
    if(this->bIsHide)
    {
        this->hide();
    }
}

void FrmMessageBox::btnOkClickedSlot()
{
    this->hideFrm();
}

void FrmMessageBox::btnCancleClickedSlot()
{
    this->hideFrm();
}

void FrmMessageBox::checkSec()
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
        this->hideFrm();
    }
    QString str = tr("关闭倒计时")+ QString(" %1 ").arg(closeSec - currentSec + 1)+tr("秒");
    lblTime->setText(str);
}
