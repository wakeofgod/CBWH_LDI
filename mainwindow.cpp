#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidgets()
{
    createMenu();
    createCameraWidget();
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

    motionAction2 = motionToolBar->addAction(QIcon::fromTheme("project-development-new-template"),tr("控制器信息"),this,&MainWindow::motionSlot2);
    action = motionMenu->addAction(QIcon::fromTheme("project-development-new-template"),tr("控制器信息"),this,&MainWindow::motionSlot2);
    action->setToolTip(tr("控制器信息"));

    motionAction3 = motionToolBar->addAction(QIcon::fromTheme("project-development-new-template"),tr("通讯参数设置"),this,&MainWindow::motionSlot3);
    action = motionMenu->addAction(QIcon::fromTheme("project-development-new-template"),tr("通讯参数设置"),this,&MainWindow::motionSlot3);
    action->setToolTip(tr("通讯参数设置"));

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
    txtXCoordinate = new QLineEdit();
    txtXState = new QLineEdit();
    txtXMovePosition = new QLineEdit();
    txtXSpeed = new QLineEdit();
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
    txtYCoordinate = new QLineEdit();
    txtYState = new QLineEdit();
    txtYMovePosition = new QLineEdit();
    txtYSpeed = new QLineEdit();
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
    txtZCoordinate = new QLineEdit();
    txtZState = new QLineEdit();
    txtZMovePosition = new QLineEdit();
    txtZSpeed = new QLineEdit();
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
    txtRCoordinate = new QLineEdit();
    txtRState = new QLineEdit();
    txtRMovePosition = new QLineEdit();
    txtRSpeed = new QLineEdit();
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
    txtC1Coordinate = new QLineEdit();
    txtC1State = new QLineEdit();
    txtC1MovePosition = new QLineEdit();
    txtC1Speed = new QLineEdit();
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
    txtC2Coordinate = new QLineEdit();
    txtC2State = new QLineEdit();
    txtC2MovePosition = new QLineEdit();
    txtC2Speed = new QLineEdit();
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
    layout->addWidget(motionGroup,8,0,7,4);
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
    motionInfoDialog = new MotionInfoDialog();
    motionInfoDialog->show();
    //qDebug()<<QString("void MainWindow::motionSlot2");
}

void MainWindow::motionSlot3()
{
    motionConnectDialog = new MotionConnecDialog();
    motionConnectDialog->show();
    //qDebug()<<QString("void MainWindow::motionSlot3");
}
