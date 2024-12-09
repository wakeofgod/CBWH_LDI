#include "camerasettingdialog.h"
#include <QDebug>

CameraSettingDialog::CameraSettingDialog(QWidget *parent):QDialog(parent)
{
    setWindowTitle(tr("相机初始化"));
    initWidget();
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(cameraGroup,0,0);
    setLayout(mainLayout);

    Qt::WindowFlags flags = windowFlags();
    flags &= ~Qt::WindowContextHelpButtonHint;
    flags |= Qt::MSWindowsFixedSizeDialogHint;
    setWindowFlags(flags);
    resize(600,400);

    setFocusPolicy(Qt::NoFocus);

    connect(btnClose,&QPushButton::clicked,this,&QDialog::reject);
}

CameraSettingDialog::~CameraSettingDialog()
{
}

void CameraSettingDialog::initWidget()
{
    QGridLayout *layout = new QGridLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(10);
    cameraGroup = new QGroupBox(tr("初始化"));
    cameraGroup->setStyleSheet("QGroupBox{border:none;}");
    btnConnect = new QPushButton(tr("查找并连接设备"));
    btnDisConnect = new QPushButton(tr("关闭设备"));
    btnStartRecord = new QPushButton(tr("开始录制"));
    btnStopRecord = new QPushButton(tr("停止录制"));
    btnCamera1Work = new QPushButton(tr("相机1拍照"));
    btnCamera2Work = new QPushButton(tr("相机2拍照"));
    btnMapRead = new QPushButton(tr("读图"));

    layout->addWidget(btnConnect,0,0);
    layout->addWidget(btnStartRecord,0,1);
    layout->addWidget(btnCamera1Work,0,2);
    layout->addWidget(btnMapRead,0,3);

    layout->addWidget(btnDisConnect,1,0);
    layout->addWidget(btnStopRecord,1,1);
    layout->addWidget(btnCamera2Work,1,2);

    btnClose = new QPushButton(tr("关闭"));
    btnClose->setStyleSheet("QPushButton { background-color: #87CEFA; color: white; font-size: 16px; }");
    layout->addWidget(btnClose,3,3);

    layout->setRowStretch(0,1);
    layout->setRowStretch(1,1);
    layout->setRowStretch(2,1);
    layout->setRowStretch(3,1);
    cameraGroup->setLayout(layout);

}
