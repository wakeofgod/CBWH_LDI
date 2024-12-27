#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <LTSMC.h>

int linkStatus = -1;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    layout = new QGridLayout();
    initWidgets();

    ui->centralwidget->setLayout(layout);

    QList<QLabel*> labels = findChildren<QLabel*>();
    for (QLabel *label : labels)
    {
        label->setAlignment(Qt::AlignCenter);
    }
    setMinimumSize(800, 600);
    connect(btnConnect,&QPushButton::clicked,this,&MainWindow::btnConnectSlot);
    connect(btnDisconnect,&QPushButton::clicked,this,&MainWindow::btnDisconnectSlot);
    connect(btnFullOpen,&QPushButton::clicked,this,&MainWindow::btnFullOpenSlot);
    connect(btnFullClose,&QPushButton::clicked,this,&MainWindow::btnFullCloseSlot);

    // 定时器，获取状态
    connectionCheckerTimer = new QTimer(this);
    connectionCheckerTimer->setInterval(100); // 设置检查间隔，例如1000ms
    connect(connectionCheckerTimer, SIGNAL(timeout()), this, SLOT(checkConnection()));
    connectionCheckerTimer->start();

    //使能复选框
    connect(cbxEnableX,&QCheckBox::clicked,this,&MainWindow::checkEnableXSlot);
    connect(cbxEnableY,&QCheckBox::clicked,this,&MainWindow::checkEnableYSlot);
    connect(cbxEnableZ,&QCheckBox::clicked,this,&MainWindow::checkEnableZSlot);
    connect(cbxEnableR,&QCheckBox::clicked,this,&MainWindow::checkEnableRSlot);
    connect(cbxEnableC1,&QCheckBox::clicked,this,&MainWindow::checkEnableC1Slot);
    connect(cbxEnableC2,&QCheckBox::clicked,this,&MainWindow::checkEnableC2Slot);
    // 停止轴的connect
    connect(btnXStop,&QPushButton::clicked,this,&MainWindow::axisStopSlot);
    connect(btnYStop,&QPushButton::clicked,this,&MainWindow::axisStopSlot);
    connect(btnZStop,&QPushButton::clicked,this,&MainWindow::axisStopSlot);
    connect(btnRStop,&QPushButton::clicked,this,&MainWindow::axisStopSlot);
    connect(btnC1Stop,&QPushButton::clicked,this,&MainWindow::axisStopSlot);
    connect(btnC2Stop,&QPushButton::clicked,this,&MainWindow::axisStopSlot);
    //回零的connect
    connect(btnXZero,&QPushButton::clicked,this,&MainWindow::axisHomeSlot);
    connect(btnYZero,&QPushButton::clicked,this,&MainWindow::axisHomeSlot);
    connect(btnZZero,&QPushButton::clicked,this,&MainWindow::axisHomeSlot);
    connect(btnRZero,&QPushButton::clicked,this,&MainWindow::axisHomeSlot);
    connect(btnC1Zero,&QPushButton::clicked,this,&MainWindow::axisHomeSlot);
    connect(btnC2Zero,&QPushButton::clicked,this,&MainWindow::axisHomeSlot);
    //x轴正反移动
    connect(btnXObverse,&QPushButton::pressed,this,&MainWindow::moveContinueSlot);
    connect(btnXObverse,&QPushButton::released,this,&MainWindow::moveStopSlot);
    connect(btnXReverse,&QPushButton::pressed,this,&MainWindow::moveContinueSlot);
    connect(btnXReverse,&QPushButton::released,this,&MainWindow::moveStopSlot);
    //x轴相对或者绝对移动
    connect(btnXObverse,&QPushButton::clicked,this,&MainWindow::moveRelaAndabsSlot);
    connect(btnXReverse,&QPushButton::clicked,this,&MainWindow::moveRelaAndabsSlot);
    //y轴正反移动
    connect(btnYObverse,&QPushButton::pressed,this,&MainWindow::moveContinueSlot);
    connect(btnYObverse,&QPushButton::released,this,&MainWindow::moveStopSlot);
    connect(btnYReverse,&QPushButton::pressed,this,&MainWindow::moveContinueSlot);
    connect(btnYReverse,&QPushButton::released,this,&MainWindow::moveStopSlot);
    connect(btnYObverse,&QPushButton::clicked,this,&MainWindow::moveRelaAndabsSlot);
    connect(btnYReverse,&QPushButton::clicked,this,&MainWindow::moveRelaAndabsSlot);
    //z轴正反移动
    connect(btnZObverse,&QPushButton::pressed,this,&MainWindow::moveContinueSlot);
    connect(btnZObverse,&QPushButton::released,this,&MainWindow::moveStopSlot);
    connect(btnZReverse,&QPushButton::pressed,this,&MainWindow::moveContinueSlot);
    connect(btnZReverse,&QPushButton::released,this,&MainWindow::moveStopSlot);
    connect(btnZObverse,&QPushButton::clicked,this,&MainWindow::moveRelaAndabsSlot);
    connect(btnZReverse,&QPushButton::clicked,this,&MainWindow::moveRelaAndabsSlot);
    //r轴正反移动
    connect(btnRObverse,&QPushButton::pressed,this,&MainWindow::moveContinueSlot);
    connect(btnRObverse,&QPushButton::released,this,&MainWindow::moveStopSlot);
    connect(btnRReverse,&QPushButton::pressed,this,&MainWindow::moveContinueSlot);
    connect(btnRReverse,&QPushButton::released,this,&MainWindow::moveStopSlot);
    connect(btnRObverse,&QPushButton::clicked,this,&MainWindow::moveRelaAndabsSlot);
    connect(btnRReverse,&QPushButton::clicked,this,&MainWindow::moveRelaAndabsSlot);
    //c1轴正反移动
    connect(btnC1Obverse,&QPushButton::pressed,this,&MainWindow::moveContinueSlot);
    connect(btnC1Obverse,&QPushButton::released,this,&MainWindow::moveStopSlot);
    connect(btnC1Reverse,&QPushButton::pressed,this,&MainWindow::moveContinueSlot);
    connect(btnC1Reverse,&QPushButton::released,this,&MainWindow::moveStopSlot);
    connect(btnC1Obverse,&QPushButton::clicked,this,&MainWindow::moveRelaAndabsSlot);
    connect(btnC1Reverse,&QPushButton::clicked,this,&MainWindow::moveRelaAndabsSlot);
    //c2轴正反移动
    connect(btnC2Obverse,&QPushButton::pressed,this,&MainWindow::moveContinueSlot);
    connect(btnC2Obverse,&QPushButton::released,this,&MainWindow::moveStopSlot);
    connect(btnC2Reverse,&QPushButton::pressed,this,&MainWindow::moveContinueSlot);
    connect(btnC2Reverse,&QPushButton::released,this,&MainWindow::moveStopSlot);
    connect(btnC2Obverse,&QPushButton::clicked,this,&MainWindow::moveRelaAndabsSlot);
    connect(btnC2Reverse,&QPushButton::clicked,this,&MainWindow::moveRelaAndabsSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidgets()
{
    createMenu();
    createCameraWidget();
    createMotionEnable();
    createMotionControl();
}

void MainWindow::createMenu()
{
    menuBar = new QMenuBar(this);
    fileMenu = menuBar->addMenu(tr("文件"));
    cameraMenu = menuBar->addMenu(tr("相机"));
    motionMenu = menuBar->addMenu(tr("运动"));
    setMenuBar(menuBar);

    fileToolBar = addToolBar(tr("文件"));
    fileToolBar->setToolTip(tr("文件"));
    fileAction1 = fileToolBar->addAction(QIcon::fromTheme("project-development-new-template"),tr("文件操作1"),this,&MainWindow::fileActionSlot1);
    QAction *action = fileMenu->addAction(QIcon::fromTheme("project-development-new-template"),tr("文件操作1"),this,&MainWindow::fileActionSlot1);
    action->setToolTip(tr("文件操作1"));

    fileAction2 = fileToolBar->addAction(QIcon::fromTheme("project-development-new-template"),tr("文件操作2"),this,&MainWindow::fileActionSlot2);
    action = fileMenu->addAction(QIcon::fromTheme("project-development-new-template"),tr("文件操作2"),this,&MainWindow::fileActionSlot2);
    action->setToolTip(tr("文件操作2"));

    fileAction3 = fileToolBar->addAction(QIcon::fromTheme("project-development-new-template"),tr("文件操作3"),this,&MainWindow::fileActionSlot3);
    action = fileMenu->addAction(QIcon::fromTheme("project-development-new-template"),tr("文件操作3"),this,&MainWindow::fileActionSlot3);
    action->setToolTip(tr("文件操作3"));

    fileToolBar->addSeparator();

    cameraToolBar = addToolBar(tr("相机"));
    cameraToolBar->setToolTip(tr("相机"));
    cameraAction1 = cameraToolBar->addAction(QIcon::fromTheme("project-development-new-template"),tr("相机设置1"),this,&MainWindow::cameraSlot1);
    action = cameraMenu->addAction(QIcon::fromTheme("project-development-new-template"),tr("相机设置1"),this,&MainWindow::cameraSlot1);
    action->setToolTip(tr("相机设置1"));

    cameraAction2 = cameraToolBar->addAction(QIcon::fromTheme("project-development-new-template"),tr("相机设置2"),this,&MainWindow::cameraSlot2);
    action = cameraMenu->addAction(QIcon::fromTheme("project-development-new-template"),tr("相机设置2"),this,&MainWindow::cameraSlot2);
    action->setToolTip(tr("相机设置2"));

    cameraAction3 = cameraToolBar->addAction(QIcon::fromTheme("project-development-new-template"),tr("相机设置3"),this,&MainWindow::cameraSlot3);
    action = cameraMenu->addAction(QIcon::fromTheme("project-development-new-template"),tr("相机设置3"),this,&MainWindow::cameraSlot3);
    action->setToolTip(tr("相机设置3"));

    cameraToolBar->addSeparator();

    motionToolBar = addToolBar(tr("运动控制"));
    motionToolBar->setToolTip(tr("运动控制"));
    motionAction1 = motionToolBar->addAction(QIcon::fromTheme("project-development-new-template"),tr("参数设置"),this,&MainWindow::motionSlot1);
    action = motionMenu->addAction(QIcon::fromTheme("project-development-new-template"),tr("参数设置"),this,&MainWindow::motionSlot1);
    action->setToolTip(tr("参数设置"));

    // motionAction2 = motionToolBar->addAction(QIcon::fromTheme("project-development-new-template"),tr("控制器信息"),this,&MainWindow::motionSlot2);
    action = motionMenu->addAction(QIcon::fromTheme("project-development-new-template"),tr("控制器连接"),this,&MainWindow::motionSlot2);
    action->setToolTip(tr("控制器连接"));

    // motionAction3 = motionToolBar->addAction(QIcon::fromTheme("project-development-new-template"),tr("通讯参数设置"),this,&MainWindow::motionSlot3);
    // action = motionMenu->addAction(QIcon::fromTheme("project-development-new-template"),tr("通讯参数设置"),this,&MainWindow::motionSlot3);
    // action->setToolTip(tr("通讯参数设置"));

    motionToolBar->addSeparator();
}

void MainWindow::createCameraWidget()
{
    viewGroup = new QGroupBox();
    QGridLayout *viewLayout = new QGridLayout();
    cameraView1 = new QGraphicsView();
    cameraScene1 = new QGraphicsScene();
    cameraView2 = new QGraphicsView();
    cameraScene2 = new QGraphicsScene();

    cameraView1->setScene(cameraScene1);
    cameraView2->setScene(cameraScene2);

#if 0
    cameraView1->setStyleSheet("border: 2px solid red;");
    cameraView2->setStyleSheet("border: 2px dashed blue;");

    cameraScene1->addRect(10, 10, 100, 100, QPen(Qt::red));
    cameraScene2->addEllipse(50, 50, 100, 100, QPen(Qt::blue));
#endif
    cameraView1->setRenderHint(QPainter::Antialiasing);
    cameraView2->setRenderHint(QPainter::Antialiasing);

    viewLayout->addWidget(cameraView1,0,0,1,1);
    viewLayout->addWidget(cameraView2,0,1,1,1);

    viewGroup->setLayout(viewLayout);
    layout->addWidget(viewGroup,0,0,8,4);
}

void MainWindow::createMotionEnable()
{
    QGridLayout *eLayout = new QGridLayout();
    enableGroup = new QGroupBox();
    lblIPAddress = new QLabel(tr("IP:"));
    txtIPAddress = new QLineEdit();
    btnConnect = new QPushButton(tr("连接"));
    radioState = new QRadioButton();
    btnDisconnect = new QPushButton(tr("断开连接"));
    lblEnableX = new QLabel("X");
    lblEnableY = new QLabel("Y");
    lblEnableZ = new QLabel("Z");
    lblEnableR = new QLabel("R");
    lblEnableC1 = new QLabel("C1");
    lblEnableC2 = new QLabel("C2");
    cbxEnableX = new QCheckBox();
    cbxEnableY = new QCheckBox();
    cbxEnableZ = new QCheckBox();
    cbxEnableR = new QCheckBox();
    cbxEnableC1 = new QCheckBox();
    cbxEnableC2 = new QCheckBox();
    btnFullOpen = new QPushButton(tr("全开"));
    btnFullClose = new QPushButton(tr("全关"));
    eLayout->addWidget(lblIPAddress,0,0);
    eLayout->addWidget(txtIPAddress,0,1);
    eLayout->addWidget(btnConnect,0,2);
    eLayout->addWidget(radioState,0,3,Qt::AlignCenter);
    eLayout->addWidget(btnDisconnect,0,4);
    eLayout->addWidget(lblEnableX,1,0,Qt::AlignCenter);
    eLayout->addWidget(lblEnableY,1,1,Qt::AlignCenter);
    eLayout->addWidget(lblEnableZ,1,2,Qt::AlignCenter);
    eLayout->addWidget(lblEnableR,1,3,Qt::AlignCenter);
    eLayout->addWidget(lblEnableC1,1,4,Qt::AlignCenter);
    eLayout->addWidget(lblEnableC2,1,5,Qt::AlignCenter);
    eLayout->addWidget(cbxEnableX,2,0,Qt::AlignCenter);
    eLayout->addWidget(cbxEnableY,2,1,Qt::AlignCenter);
    eLayout->addWidget(cbxEnableZ,2,2,Qt::AlignCenter);
    eLayout->addWidget(cbxEnableR,2,3,Qt::AlignCenter);
    eLayout->addWidget(cbxEnableC1,2,4,Qt::AlignCenter);
    eLayout->addWidget(cbxEnableC2,2,5,Qt::AlignCenter);
    eLayout->addWidget(btnFullOpen,3,1);
    eLayout->addWidget(btnFullClose,3,3);

    eLayout->setRowStretch(0,1);
    eLayout->setRowStretch(1,1);
    eLayout->setRowStretch(1,1);
    eLayout->setColumnStretch(0,1);
    eLayout->setColumnStretch(1,1);
    eLayout->setColumnStretch(2,1);
    eLayout->setColumnStretch(3,1);
    eLayout->setColumnStretch(4,1);
    eLayout->setColumnStretch(5,1);
    enableGroup->setLayout(eLayout);
    layout->addWidget(enableGroup,8,0,4,4);
}

void MainWindow::createMotionControl()
{
    motionGroup = new QGroupBox(tr("轴运动"));
    QGridLayout *mLayout = new QGridLayout();
    lblAxis = new QLabel(tr("轴"));
    lblCoordinate = new QLabel(tr("坐标"));
    lblState = new QLabel(tr("状态"));
    lblMovePosition = new QLabel(tr("移动位置"));
    lblMoveSpeed = new QLabel(tr("移动速度"));
    lblMovePattern = new QLabel(tr("移动模式"));
    radioContinuous = new QRadioButton(tr("连续"));
    radioRelative = new QRadioButton(tr("相对"));
    radioAbsolute = new QRadioButton(tr("绝对"));

    mLayout->addWidget(lblAxis,0,0);
    mLayout->addWidget(lblCoordinate,0,1);
    mLayout->addWidget(lblState,0,2);
    mLayout->addWidget(lblMovePosition,0,3);
    mLayout->addWidget(lblMoveSpeed,0,4);
    mLayout->addWidget(lblMovePattern,0,5);
    mLayout->addWidget(radioContinuous,0,6);
    mLayout->addWidget(radioRelative,0,7);
    mLayout->addWidget(radioAbsolute,0,8);

    lblXAxis = new QLabel(tr("X"));
    txtXCoordinate = new QDoubleSpinBox();
    txtXState = new QLineEdit();
    txtXMovePosition = new QDoubleSpinBox();
    txtXSpeed = new QDoubleSpinBox();
    btnXObverse = new QPushButton(tr("正"));
    btnXReverse = new QPushButton(tr("反"));
    btnXZero = new QPushButton(tr("回零"));
    btnXStop = new QPushButton(tr("停止"));
    mLayout->addWidget(lblXAxis,1,0);
    mLayout->addWidget(txtXCoordinate,1,1);
    mLayout->addWidget(txtXState,1,2);
    mLayout->addWidget(txtXMovePosition,1,3);
    mLayout->addWidget(txtXSpeed,1,4);
    mLayout->addWidget(btnXObverse,1,5);
    mLayout->addWidget(btnXReverse,1,6);
    mLayout->addWidget(btnXZero,1,7);
    mLayout->addWidget(btnXStop,1,8);

    lblYAxis = new QLabel(tr("Y"));
    txtYCoordinate = new QDoubleSpinBox();
    txtYState = new QLineEdit();
    txtYMovePosition = new QDoubleSpinBox();
    txtYSpeed = new QDoubleSpinBox();
    btnYObverse = new QPushButton(tr("正"));
    btnYReverse = new QPushButton(tr("反"));
    btnYZero = new QPushButton(tr("回零"));
    btnYStop = new QPushButton(tr("停止"));
    mLayout->addWidget(lblYAxis,2,0);
    mLayout->addWidget(txtYCoordinate,2,1);
    mLayout->addWidget(txtYState,2,2);
    mLayout->addWidget(txtYMovePosition,2,3);
    mLayout->addWidget(txtYSpeed,2,4);
    mLayout->addWidget(btnYObverse,2,5);
    mLayout->addWidget(btnYReverse,2,6);
    mLayout->addWidget(btnYZero,2,7);
    mLayout->addWidget(btnYStop,2,8);

    lblZAxis = new QLabel(tr("Z"));
    txtZCoordinate = new QDoubleSpinBox();
    txtZState = new QLineEdit();
    txtZMovePosition = new QDoubleSpinBox();
    txtZSpeed = new QDoubleSpinBox();
    btnZObverse = new QPushButton(tr("正"));
    btnZReverse = new QPushButton(tr("反"));
    btnZZero = new QPushButton(tr("回零"));
    btnZStop = new QPushButton(tr("停止"));
    mLayout->addWidget(lblZAxis,3,0);
    mLayout->addWidget(txtZCoordinate,3,1);
    mLayout->addWidget(txtZState,3,2);
    mLayout->addWidget(txtZMovePosition,3,3);
    mLayout->addWidget(txtZSpeed,3,4);
    mLayout->addWidget(btnZObverse,3,5);
    mLayout->addWidget(btnZReverse,3,6);
    mLayout->addWidget(btnZZero,3,7);
    mLayout->addWidget(btnZStop,3,8);

    lblRAxis = new QLabel(tr("R"));
    txtRCoordinate = new QDoubleSpinBox();
    txtRState = new QLineEdit();
    txtRMovePosition = new QDoubleSpinBox();
    txtRSpeed = new QDoubleSpinBox();
    btnRObverse = new QPushButton(tr("正"));
    btnRReverse = new QPushButton(tr("反"));
    btnRZero = new QPushButton(tr("回零"));
    btnRStop = new QPushButton(tr("停止"));
    mLayout->addWidget(lblRAxis,4,0);
    mLayout->addWidget(txtRCoordinate,4,1);
    mLayout->addWidget(txtRState,4,2);
    mLayout->addWidget(txtRMovePosition,4,3);
    mLayout->addWidget(txtRSpeed,4,4);
    mLayout->addWidget(btnRObverse,4,5);
    mLayout->addWidget(btnRReverse,4,6);
    mLayout->addWidget(btnRZero,4,7);
    mLayout->addWidget(btnRStop,4,8);

    lblC1Axis = new QLabel(tr("C1"));
    txtC1Coordinate = new QDoubleSpinBox();
    txtC1State = new QLineEdit();
    txtC1MovePosition = new QDoubleSpinBox();
    txtC1Speed = new QDoubleSpinBox();
    btnC1Obverse = new QPushButton(tr("正"));
    btnC1Reverse = new QPushButton(tr("反"));
    btnC1Zero = new QPushButton(tr("回零"));
    btnC1Stop = new QPushButton(tr("停止"));
    mLayout->addWidget(lblC1Axis,5,0);
    mLayout->addWidget(txtC1Coordinate,5,1);
    mLayout->addWidget(txtC1State,5,2);
    mLayout->addWidget(txtC1MovePosition,5,3);
    mLayout->addWidget(txtC1Speed,5,4);
    mLayout->addWidget(btnC1Obverse,5,5);
    mLayout->addWidget(btnC1Reverse,5,6);
    mLayout->addWidget(btnC1Zero,5,7);
    mLayout->addWidget(btnC1Stop,5,8);

    lblC2Axis = new QLabel(tr("C2"));
    txtC2Coordinate = new QDoubleSpinBox();
    txtC2State = new QLineEdit();
    txtC2MovePosition = new QDoubleSpinBox();
    txtC2Speed = new QDoubleSpinBox();
    btnC2Obverse = new QPushButton(tr("正"));
    btnC2Reverse = new QPushButton(tr("反"));
    btnC2Zero = new QPushButton(tr("回零"));
    btnC2Stop = new QPushButton(tr("停止"));
    mLayout->addWidget(lblC2Axis,6,0);
    mLayout->addWidget(txtC2Coordinate,6,1);
    mLayout->addWidget(txtC2State,6,2);
    mLayout->addWidget(txtC2MovePosition,6,3);
    mLayout->addWidget(txtC2Speed,6,4);
    mLayout->addWidget(btnC2Obverse,6,5);
    mLayout->addWidget(btnC2Reverse,6,6);
    mLayout->addWidget(btnC2Zero,6,7);
    mLayout->addWidget(btnC2Stop,6,8);

    mLayout->setRowStretch(0,1);
    mLayout->setRowStretch(1,1);
    mLayout->setColumnStretch(0,1);
    mLayout->setColumnStretch(1,1);
    mLayout->setColumnStretch(2,1);
    mLayout->setColumnStretch(3,1);
    mLayout->setColumnStretch(4,1);
    mLayout->setColumnStretch(5,1);
    mLayout->setColumnStretch(6,1);
    mLayout->setColumnStretch(7,1);
    mLayout->setColumnStretch(8,1);

    motionGroup->setLayout(mLayout);
    layout->addWidget(motionGroup,12,0,7,4);
}

void MainWindow::setSpeed(int aix, QDoubleSpinBox *lineedit)
{
    double Min_Vel = 0,Max_Vel = 0,Tacc = 0,Tdec = 0,Stop_Vel = 0;

    smc_get_profile_unit(0,aix,&Min_Vel,&Max_Vel,&Tacc,&Tdec,&Stop_Vel);
    Max_Vel = lineedit->text().toDouble();
    smc_set_profile_unit(0,aix,Min_Vel,Max_Vel,Tacc,Tdec,Stop_Vel);

}

int MainWindow::Getlinkstatus()
{
    char ip[128];
    int ret = smc_get_ipaddr(0,ip);
    if(ret != 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int MainWindow::getAixposition(int aixnum, double *x)
{
    smc_get_position_unit(0,aixnum,x);
    int ret = smc_check_done(0,aixnum);
    return ret;
}

void MainWindow::fileActionSlot1()
{
    fileDialog = new FileCommandDialog(this);
    fileDialog->show();
    qDebug()<<QString("void MainWindow::fileActionSlot1");
}

void MainWindow::fileActionSlot2()
{
    qDebug()<<QString("void MainWindow::fileActionSlot2");
}

void MainWindow::fileActionSlot3()
{
    qDebug()<<QString("void MainWindow::fileActionSlot3");
}

void MainWindow::cameraSlot1()
{
    cameraDialog = new CameraSettingDialog(this);
    cameraDialog->show();
    qDebug()<<QString("void MainWindow::cameraSlot1");
}

void MainWindow::cameraSlot2()
{
    qDebug()<<QString("void MainWindow::cameraSlot2");
}

void MainWindow::cameraSlot3()
{
    qDebug()<<QString("void MainWindow::cameraSlot3");
}

void MainWindow::motionSlot1()
{
    motionParaDialog = new MotionParaDialog();
    motionParaDialog->show();
    //qDebug()<<QString("void MainWindow::motionSlot1");
}

void MainWindow::motionSlot2()
{
    // motionInfoDialog = new MotionInfoDialog();
    // motionInfoDialog->show();
    //qDebug()<<QString("void MainWindow::motionSlot2");
    QString ip = "192.168.5.11";
    QByteArray qb = ip.toLocal8Bit();
    char* ip_char = qb.data();
    int ret = smc_board_init(0,2,ip_char,0);
    if(ret == 0)
    {
        qDebug()<<"连接成功";
        linkStatus = 0;
    }
    else
    {
        linkStatus = -1;
        qDebug()<<"连接失败";
    }
}

void MainWindow::motionSlot3()
{
    motionConnectDialog = new MotionConnecDialog();
    motionConnectDialog->show();
    //qDebug()<<QString("void MainWindow::motionSlot3");
}

void MainWindow::btnConnectSlot()
{
    QString ip = txtIPAddress->text();
    QByteArray qb = ip.toLocal8Bit();
    char* ip_char = qb.data();
    int ret = smc_board_init(0,2,ip_char,0);
    if(ret == 0)
    {
        linkStatus = 0;
    }
    else
    {
        linkStatus = -1;
        qDebug()<<QString("连接失败");
    }
}

void MainWindow::btnDisconnectSlot()
{
    smc_board_close(0);
}

void MainWindow::btnFullOpenSlot()
{
    if(linkStatus == 0)
    {
        smc_write_sevon_pin( 0 , 0 , 0 ) ;
        smc_write_sevon_pin( 0 , 1 , 0 ) ;
        smc_write_sevon_pin( 0 , 2 , 0 ) ;
        smc_write_sevon_pin( 0 , 3 , 0 ) ;
        smc_write_sevon_pin( 0 , 4 , 0 ) ;
        smc_write_sevon_pin(0,5,0);
        cbxEnableX->setChecked(true);
        cbxEnableY->setChecked(true);
        cbxEnableZ->setChecked(true);
        cbxEnableR->setChecked(true);
        cbxEnableC1->setChecked(true);
        cbxEnableC2->setChecked(true);
    }
    else
    {

    }
}

void MainWindow::btnFullCloseSlot()
{
    if(linkStatus == 0)
    {
        smc_write_sevon_pin( 0 , 0 , 1 ) ;
        smc_write_sevon_pin( 0 , 1 , 1 ) ;
        smc_write_sevon_pin( 0 , 2 , 1 ) ;
        smc_write_sevon_pin( 0 , 3 , 1 ) ;
        smc_write_sevon_pin( 0 , 4 , 1 ) ;
        smc_write_sevon_pin(0,5,1);
        cbxEnableX->setChecked(false);
        cbxEnableY->setChecked(false);
        cbxEnableZ->setChecked(false);
        cbxEnableR->setChecked(false);
        cbxEnableC1->setChecked(false);
        cbxEnableC2->setChecked(false);
    }
    else
    {

    }
}

void MainWindow::moveContinueSlot()
{
    double Min_Vel = 0,Max_Vel = 0,Tacc = 0,Tdec = 0,Stop_Vel = 0;
    if(radioContinuous->isChecked())
    {
        // x轴
        if(sender() == btnXObverse)
        {
            smc_get_profile_unit(0,1,&Min_Vel,&Max_Vel,&Tacc,&Tdec,&Stop_Vel);
            Max_Vel = txtXSpeed->text().toDouble();
            smc_set_profile_unit(0,1,Min_Vel,Max_Vel,Tacc,Tdec,Stop_Vel);
            smc_vmove(0,1,1);
        }
        if(sender() == btnXReverse)
        {
            smc_get_profile_unit(0,1,&Min_Vel,&Max_Vel,&Tacc,&Tdec,&Stop_Vel);
            Max_Vel = txtXSpeed->text().toDouble();
            smc_set_profile_unit(0,1,Min_Vel,Max_Vel,Tacc,Tdec,Stop_Vel);
            smc_vmove(0,1,0);
        }
        // y轴
        if(sender() == btnYObverse)
        {
            smc_get_profile_unit(0,0,&Min_Vel,&Max_Vel,&Tacc,&Tdec,&Stop_Vel);
            Max_Vel = txtYSpeed->text().toDouble();
            smc_set_profile_unit(0,0,Min_Vel,Max_Vel,Tacc,Tdec,Stop_Vel);
            smc_vmove(0,0,1);
        }
        if(sender() == btnYReverse)
        {
            smc_get_profile_unit(0,0,&Min_Vel,&Max_Vel,&Tacc,&Tdec,&Stop_Vel);
            Max_Vel = txtYSpeed->text().toDouble();
            smc_set_profile_unit(0,0,Min_Vel,Max_Vel,Tacc,Tdec,Stop_Vel);
            smc_vmove(0,0,0);
        }
        // z轴
        if(sender() == btnZObverse)
        {
            smc_get_profile_unit(0,2,&Min_Vel,&Max_Vel,&Tacc,&Tdec,&Stop_Vel);
            Max_Vel = txtZSpeed->text().toDouble();
            smc_set_profile_unit(0,2,Min_Vel,Max_Vel,Tacc,Tdec,Stop_Vel);
            smc_vmove(0,2,1);
        }
        if(sender() == btnZReverse)
        {
            smc_get_profile_unit(0,2,&Min_Vel,&Max_Vel,&Tacc,&Tdec,&Stop_Vel);
            Max_Vel = txtZSpeed->text().toDouble();
            smc_set_profile_unit(0,2,Min_Vel,Max_Vel,Tacc,Tdec,Stop_Vel);
            smc_vmove(0,2,0);
        }
        // r轴
        if(sender() == btnRObverse)
        {
            smc_get_profile_unit(0,3,&Min_Vel,&Max_Vel,&Tacc,&Tdec,&Stop_Vel);
            Max_Vel = txtRSpeed->text().toDouble();
            smc_set_profile_unit(0,3,Min_Vel,Max_Vel,Tacc,Tdec,Stop_Vel);
            smc_vmove(0,3,1);
        }
        if(sender() == btnRReverse)
        {
            smc_get_profile_unit(0,3,&Min_Vel,&Max_Vel,&Tacc,&Tdec,&Stop_Vel);
            Max_Vel = txtRSpeed->text().toDouble();
            smc_set_profile_unit(0,3,Min_Vel,Max_Vel,Tacc,Tdec,Stop_Vel);
            smc_vmove(0,3,0);
        }
        //c1轴
        if(sender() == btnC1Obverse)
        {
            smc_get_profile_unit(0,4,&Min_Vel,&Max_Vel,&Tacc,&Tdec,&Stop_Vel);
            Max_Vel = txtC1Speed->text().toDouble();
            smc_set_profile_unit(0,4,Min_Vel,Max_Vel,Tacc,Tdec,Stop_Vel);
            smc_vmove(0,4,1);
        }
        if(sender() == btnC1Reverse)
        {
            smc_get_profile_unit(0,4,&Min_Vel,&Max_Vel,&Tacc,&Tdec,&Stop_Vel);
            Max_Vel = txtC1Speed->text().toDouble();
            smc_set_profile_unit(0,4,Min_Vel,Max_Vel,Tacc,Tdec,Stop_Vel);
            smc_vmove(0,4,0);
        }
        // c2 轴
        if(sender() == btnC2Obverse)
        {
            smc_get_profile_unit(0,5,&Min_Vel,&Max_Vel,&Tacc,&Tdec,&Stop_Vel);
            Max_Vel = txtC2Speed->text().toDouble();
            smc_set_profile_unit(0,5,Min_Vel,Max_Vel,Tacc,Tdec,Stop_Vel);
            smc_vmove(0,5,1);
        }
        if(sender() == btnC2Reverse)
        {
            smc_get_profile_unit(0,5,&Min_Vel,&Max_Vel,&Tacc,&Tdec,&Stop_Vel);
            Max_Vel = txtC2Speed->text().toDouble();
            smc_set_profile_unit(0,5,Min_Vel,Max_Vel,Tacc,Tdec,Stop_Vel);
            smc_vmove(0,5,0);
        }
    }

}

void MainWindow::moveStopSlot()
{
    if(radioContinuous->isChecked())
    {
        if(sender()== btnXObverse || sender() == btnXReverse)
        {
            smc_stop(0,1,0);
        }

        if(sender()== btnYObverse || sender() == btnYReverse)
        {
            smc_stop(0,0,0);
        }
        if(sender()== btnZObverse || sender() == btnZReverse)
        {
            smc_stop(0,2,0);
        }
        if(sender()== btnRObverse || sender() == btnRReverse)
        {
            smc_stop(0,3,0);
        }
        if(sender()== btnC1Obverse || sender() == btnC1Reverse)
        {
            smc_stop(0,4,0);
        }
        if(sender()== btnC2Obverse || sender() == btnC2Reverse)
        {
            smc_stop(0,5,0);
        }
    }

}

void MainWindow::moveRelaAndabsSlot()
{
    if(radioRelative->isChecked() || radioAbsolute->isChecked())
    {

        if(radioRelative->isChecked()) //相对
        {
            // x轴
            if(sender() == btnXObverse)
            {
                setSpeed(1, txtXSpeed);
                double movedis = txtXMovePosition->text().toDouble();
                smc_pmove_unit(0,1,movedis,0);
            }
            if(sender() == btnXReverse)
            {
                setSpeed(1, txtXSpeed);
                double movedis = txtXMovePosition->text().toDouble();
                smc_pmove_unit(0,1,-movedis,0);
            }
            // y轴
            if(sender() == btnYObverse)
            {
                setSpeed(0, txtYSpeed);
                double movedis = txtYMovePosition->text().toDouble();
                smc_pmove_unit(0,0,movedis,0);
            }
            if(sender() == btnYReverse)
            {
                setSpeed(0, txtYSpeed);
                double movedis = txtYMovePosition->text().toDouble();
                smc_pmove_unit(0,0,-movedis,0);
            }
            // z轴
            if(sender() == btnZObverse)
            {
                setSpeed(0, txtZSpeed);
                double movedis = txtZMovePosition->text().toDouble();
                smc_pmove_unit(0,2,movedis,0);
            }
            if(sender() == btnZReverse)
            {
                setSpeed(0, txtZSpeed);
                double movedis = txtZMovePosition->text().toDouble();
                smc_pmove_unit(0,2,-movedis,0);
            }
            // r轴
            if(sender() == btnRObverse)
            {
                setSpeed(0, txtRSpeed);
                double movedis = txtRMovePosition->text().toDouble();
                smc_pmove_unit(0,3,movedis,0);
            }
            if(sender() == btnRReverse)
            {
                setSpeed(0, txtRSpeed);
                double movedis = txtRMovePosition->text().toDouble();
                smc_pmove_unit(0,3,-movedis,0);
            }
            // c1轴
            if(sender() == btnC1Obverse)
            {
                setSpeed(0, txtC1Speed);
                double movedis = txtC1MovePosition->text().toDouble();
                smc_pmove_unit(0,4,movedis,0);
            }
            if(sender() == btnC1Reverse)
            {
                setSpeed(0, txtC1Speed);
                double movedis = txtC1MovePosition->text().toDouble();
                smc_pmove_unit(0,4,-movedis,0);
            }

            //c2轴
            if(sender() == btnC2Obverse)
            {
                setSpeed(0, txtC2Speed);
                double movedis = txtC2MovePosition->text().toDouble();
                smc_pmove_unit(0,5,movedis,0);
            }
            if(sender() == btnC2Reverse)
            {
                setSpeed(0, txtC2Speed);
                double movedis = txtC2MovePosition->text().toDouble();
                smc_pmove_unit(0,5,-movedis,0);
            }

        }
        if (radioAbsolute->isChecked())// 绝对
        {
            // x轴
            if(sender() == btnXReverse || sender() == btnXObverse)
            {
                double movedis = txtXMovePosition->text().toDouble();
                smc_pmove_unit(0,1,movedis,1);
            }
            // y轴
            if(sender() == btnYReverse || sender() == btnYObverse)
            {
                double movedis = txtYMovePosition->text().toDouble();
                smc_pmove_unit(0,0,movedis,1);
            }
            // z轴
            if(sender() == btnZReverse || sender() == btnZObverse)
            {
                double movedis = txtZMovePosition->text().toDouble();
                smc_pmove_unit(0,2,movedis,1);
            }
            // r轴
            if(sender() == btnRReverse || sender() == btnRObverse)
            {
                double movedis = txtRMovePosition->text().toDouble();
                smc_pmove_unit(0,3,movedis,1);
            }
            // c1轴
            if(sender() == btnC1Reverse || sender() == btnC1Obverse)
            {
                double movedis = txtC1MovePosition->text().toDouble();
                smc_pmove_unit(0,4,movedis,1);
            }
            //c2轴
            if(sender() == btnC2Reverse || sender() == btnC2Obverse)
            {
                double movedis = txtC2MovePosition->text().toDouble();
                smc_pmove_unit(0,5,movedis,1);
            }
        }
    }
}

void MainWindow::axisStopSlot()
{
    if(sender()== btnXStop)
    {
        smc_stop(0,1,0);
    }
    if(sender()==btnYStop)
    {
        smc_stop(0,0,0);
    }
    if(sender()==btnZStop)
    {
        smc_stop(0,2,0);
    }
    if(sender()==btnRStop)
    {
        smc_stop(0,3,0);
    }
    if(sender()==btnC1Stop)
    {
        smc_stop(0,4,0);
    }
    if(sender()==btnC2Stop)
    {
        smc_stop(0,5,0);
    }
}

void MainWindow::axisHomeSlot()
{
    double low = 0,hight = 0,tac = 0;
    if(sender()== btnXZero)
    {
        double low,hight,tac = 0;
        double homespeed = txtXSpeed->text().toDouble();
        smc_get_home_profile_unit(0,1,&low,&hight,&tac,0);
        smc_set_home_profile_unit(0,1,low,homespeed,tac,0);
        smc_home_move(0,1);
    }
    if(sender()== btnYZero)
    {
        double low,hight,tac = 0;
        double homespeed = txtYSpeed->text().toDouble();
        smc_get_home_profile_unit(0,0,&low,&hight,&tac,0);
        smc_set_home_profile_unit(0,0,low,homespeed,tac,0);
        smc_home_move(0,0);
    }
    if(sender()== btnZZero)
    {
        double low,hight,tac = 0;
        double homespeed = txtZSpeed->text().toDouble();
        smc_get_home_profile_unit(0,2,&low,&hight,&tac,0);
        smc_set_home_profile_unit(0,2,low,homespeed,tac,0);
        smc_home_move(0,2);
    }
    if(sender()== btnRZero)
    {
        double low,hight,tac = 0;
        double homespeed = txtRSpeed->text().toDouble();
        smc_get_home_profile_unit(0,3,&low,&hight,&tac,0);
        smc_set_home_profile_unit(0,3,low,homespeed,tac,0);
        smc_home_move(0,3);
    }
    if(sender()== btnC1Zero)
    {
        double low,hight,tac = 0;
        double homespeed = txtC1Speed->text().toDouble();
        smc_get_home_profile_unit(0,4,&low,&hight,&tac,0);
        smc_set_home_profile_unit(0,4,low,homespeed,tac,0);
        smc_home_move(0,4);
    }
    if(sender()== btnC2Zero)
    {
        double low,hight,tac = 0;
        double homespeed = txtC2Speed->text().toDouble();
        smc_get_home_profile_unit(0,5,&low,&hight,&tac,0);
        smc_set_home_profile_unit(0,5,low,homespeed,tac,0);
        smc_home_move(0,5);
    }

}

void MainWindow::checkConnection()
{
    int ret = Getlinkstatus();
    if(ret == 0)
    {
        linkStatus = 0;
        radioState->setChecked(true);
        double pos = 0;
        int ret = getAixposition(1,&pos);// x轴位置
        if(ret == 0)
        {
            txtXState->setText("运动");
        }
        else
        {
            txtXState->setText("停止");
        }
        txtXCoordinate->setValue(pos);

        ret = getAixposition(0,&pos);// y轴位置
        if(ret == 0)
        {
            txtYState->setText("运动");
        }
        else
        {
            txtYState->setText("停止");
        }
        txtYCoordinate->setValue(pos);

        ret = getAixposition(2,&pos);// z轴位置
        if(ret == 0)
        {
            txtZState->setText("运动");
        }
        else {
            txtZState->setText("停止");
        }
        txtZCoordinate->setValue(pos);

        ret = getAixposition(3,&pos);// r轴位置
        if(ret == 0)
        {
            txtRState->setText("运动");
        }
        else
        {
            txtRState->setText("停止");
        }
        txtRCoordinate->setValue(pos);

        ret = getAixposition(4,&pos);// c1轴位置
        if(ret == 0)
        {
            txtC1State->setText("运动");
        }
        else
        {
            txtC1State->setText("停止");
        }
        txtC1Coordinate->setValue(pos);

        ret = getAixposition(5,&pos);// c2轴位置
        if(ret == 0)
        {
            txtC2State->setText("运动");
        }
        else
        {
            txtC2State->setText("停止");
        }
        txtC2Coordinate->setValue(pos);
    }
    else
    {
        linkStatus = -1;
        radioState->setChecked(false);
    }
    if(linkStatus != 0)
    {
        cbxEnableX->setCheckable(false);
        cbxEnableY->setCheckable(false);
        cbxEnableZ->setCheckable(false);
        cbxEnableR->setCheckable(false);
        cbxEnableC1->setCheckable(false);
        cbxEnableC2->setCheckable(false);
    }
    else
    {
        cbxEnableX->setCheckable(true);
        cbxEnableY->setCheckable(true);
        cbxEnableZ->setCheckable(true);
        cbxEnableR->setCheckable(true);
        cbxEnableC1->setCheckable(true);
        cbxEnableC2->setCheckable(true);
        // 读取使能信号
        int ret  = smc_read_sevon_pin(0,0); //y
        if( ret == 0)
        {
            cbxEnableY->setChecked(true);
        }
        else
        {
            cbxEnableY->setChecked(false);
        }
        ret = smc_read_sevon_pin(0,1); //x
        if( ret == 0)
        {
            cbxEnableX->setChecked(true);
        }
        else
        {
            cbxEnableX->setChecked(false);
        }
        ret = smc_read_sevon_pin(0,2); // z
        if( ret == 0)
        {
            cbxEnableZ->setChecked(true);
        }
        else
        {
            cbxEnableZ->setChecked(false);
        }
        ret = smc_read_sevon_pin(0,3); //r
        if( ret == 0)
        {
            cbxEnableR->setChecked(true);
        }
        else
        {
            cbxEnableR->setChecked(false);
        }
        ret = smc_read_sevon_pin(0,4); //c1
        if( ret == 0)
        {
            cbxEnableC1->setChecked(true);
        }
        else
        {
            cbxEnableC1->setChecked(false);
        }
        ret =  smc_read_sevon_pin(0,5); // c2
        if( ret == 0)
        {
            cbxEnableC2->setChecked(true);
        }
        else
        {
            cbxEnableC2->setChecked(false);
        }
    }
}

void MainWindow::checkEnableXSlot()
{
    bool status = cbxEnableX->isCheckable();
    if(status == false)
    {
        msgBox = new FrmMessageBox();
        msgBox->showFrm("未连接板卡,使能失败",2);
        return;
    }

    bool check = cbxEnableX->isChecked(); // 点击按钮选中
    if(check == true)
    {
        smc_write_sevon_pin(0,1,0);
    }
    else {
        smc_write_sevon_pin(0,1,1);
    }
}

void MainWindow::checkEnableYSlot()
{
    bool status = cbxEnableY->isCheckable();
    if(status == false)
    {
        msgBox = new FrmMessageBox();
        msgBox->showFrm("未连接板卡,使能失败",2);
        return;
    }

    bool check = cbxEnableY->isChecked(); // 点击按钮选中
    if(check == true)
    {
        smc_write_sevon_pin(0,0,0);
    }
    else
    {
        smc_write_sevon_pin(0,0,1);
    }
}

void MainWindow::checkEnableZSlot()
{
    bool status = cbxEnableZ->isCheckable();
    if(status == false)
    {
        msgBox = new FrmMessageBox();
        msgBox->showFrm("未连接板卡,使能失败",2);
        return;
    }

    bool check = cbxEnableZ->isChecked(); // 点击按钮选中
    if(check == true)
    {
        smc_write_sevon_pin(0,2,0);
    }
    else
    {
        smc_write_sevon_pin(0,2,1);
    }
}

void MainWindow::checkEnableRSlot()
{
    bool status = cbxEnableR->isCheckable();
    if(status == false)
    {
        msgBox = new FrmMessageBox();
        msgBox->showFrm("未连接板卡,使能失败",2);
        return;
    }

    bool check = cbxEnableR->isChecked(); // 点击按钮选中
    if(check == true)
    {
        smc_write_sevon_pin(0,3,0);
    }
    else
    {
        smc_write_sevon_pin(0,3,1);
    }
}

void MainWindow::checkEnableC1Slot()
{
    bool status = cbxEnableC1->isCheckable();
    if(status == false)
    {
        msgBox = new FrmMessageBox();
        msgBox->showFrm("未连接板卡,使能失败",2);
        return;
    }

    bool check = cbxEnableC1->isChecked(); // 点击按钮选中
    if(check == true)
    {
        smc_write_sevon_pin(0,4,0);
    }
    else
    {
        smc_write_sevon_pin(0,4,1);
    }
}

void MainWindow::checkEnableC2Slot()
{
    bool status = cbxEnableC2->isCheckable();
    if(status == false)
    {
        msgBox = new FrmMessageBox();
        msgBox->showFrm("未连接板卡,使能失败",2);
        return;
    }

    bool check = cbxEnableC2->isChecked(); // 点击按钮选中
    if(check == true)
    {
        smc_write_sevon_pin(0,5,0);
    }
    else {
        smc_write_sevon_pin(0,5,1);
    }
}
