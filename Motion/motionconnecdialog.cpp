#include "motionconnecdialog.h"

MotionConnecDialog::MotionConnecDialog(QWidget *parent):QDialog(parent)
{
    setWindowTitle(tr("通讯参数设置"));
    initView();
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(serialGroup,0,0);
    setLayout(mainLayout);

    Qt::WindowFlags flags = windowFlags();
    flags &= ~Qt::WindowContextHelpButtonHint;
    flags |= Qt::MSWindowsFixedSizeDialogHint;
    setWindowFlags(flags);
    resize(600,400);
}

void MotionConnecDialog::initView()
{
    QGridLayout *sLayout = new QGridLayout();
    serialGroup = new QGroupBox(tr("控制器串口"));
    lblSerialPort = new QLabel(tr("串口号"));
    txtSerialPort = new QLineEdit();
    lblBaudRate = new QLabel(tr("波特率"));
    txtBaudRate = new QLineEdit();
    lblDataBit = new QLabel(tr("数据位"));
    txtDataBit = new QLineEdit();
    lblStopBit = new QLabel(tr("停止位"));
    txtStopBit = new QLineEdit();

    btnSet = new QPushButton(tr("设置"));
    sLayout->addWidget(lblSerialPort,0,0);
    sLayout->addWidget(txtSerialPort,0,1);
    sLayout->addWidget(btnSet,0,2);
    sLayout->addWidget(lblBaudRate,1,0);
    sLayout->addWidget(txtBaudRate,1,1);
    sLayout->addWidget(lblDataBit,2,0);
    sLayout->addWidget(txtDataBit,2,1);
    sLayout->addWidget(lblStopBit,3,0);
    sLayout->addWidget(txtStopBit,3,1);

    sLayout->setColumnStretch(0,1);
    sLayout->setColumnStretch(1,1);
    sLayout->setColumnStretch(2,1);

    serialGroup->setLayout(sLayout);
}
