#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGridLayout>
#include <QGroupBox>
#include <QAction>
#include <QToolBar>
#include <QLabel>
#include <QRadioButton>
#include <QTimer>
#include "filecommanddialog.h"
#include "camerasettingdialog.h"
#include "motionparadialog.h"
#include "motioninfodialog.h"
#include "motionconnecdialog.h"
#include "frmmessagebox.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initWidgets();
    void createMenu();
    void createCameraWidget();
    void createMotionEnable();
    void createMotionControl();
    void setSpeed(int aix,QDoubleSpinBox* lineedit);
    int Getlinkstatus();
    int getAixposition(int aixnum , double* x);

    QTimer *connectionCheckerTimer;
    FrmMessageBox *msgBox;
public slots:
    void fileActionSlot1();
    void fileActionSlot2();
    void fileActionSlot3();

    void cameraSlot1();
    void cameraSlot2();
    void cameraSlot3();

    void motionSlot1();
    void motionSlot2();
    void motionSlot3();

    void btnConnectSlot();
    void btnDisconnectSlot();
    void btnFullOpenSlot();
    void btnFullCloseSlot();

    void moveContinueSlot();
    void moveStopSlot();
    void moveRelaAndabsSlot();
    void axisStopSlot();
    void axisHomeSlot();
    void checkConnection();
    void checkEnableXSlot();
    void checkEnableYSlot();
    void checkEnableZSlot();
    void checkEnableRSlot();
    void checkEnableC1Slot();
    void checkEnableC2Slot();

private:
    Ui::MainWindow *ui;
    QMenuBar *menuBar;

    QGridLayout *layout;
    QMenu *fileMenu;
    QMenu *cameraMenu;
    QMenu *motionMenu;

    QToolBar *fileToolBar;
    QAction *fileAction1;
    QAction *fileAction2;
    QAction *fileAction3;

    QToolBar *cameraToolBar;
    QAction *cameraAction1;
    QAction *cameraAction2;
    QAction *cameraAction3;

    QToolBar *motionToolBar;
    QAction *motionAction1;
    QAction *motionAction2;
    QAction *motionAction3;

    QGroupBox *viewGroup;
    QGraphicsView *cameraView1;
    QGraphicsScene *cameraScene1;
    QGraphicsView *cameraView2;
    QGraphicsScene *cameraScene2;

    //弹窗
    FileCommandDialog *fileDialog;
    CameraSettingDialog *cameraDialog;
    MotionParaDialog *motionParaDialog;
    MotionInfoDialog *motionInfoDialog;
    MotionConnecDialog *motionConnectDialog;

    //使能
    QGroupBox *enableGroup;
    QLabel *lblIPAddress;
    QLineEdit *txtIPAddress;
    QPushButton *btnConnect;
    QRadioButton *radioState;
    QPushButton *btnDisconnect;
    QLabel *lblEnableX;
    QLabel *lblEnableY;
    QLabel *lblEnableZ;
    QLabel *lblEnableR;
    QLabel *lblEnableC1;
    QLabel *lblEnableC2;
    QCheckBox *cbxEnableX;
    QCheckBox *cbxEnableY;
    QCheckBox *cbxEnableZ;
    QCheckBox *cbxEnableR;
    QCheckBox *cbxEnableC1;
    QCheckBox *cbxEnableC2;
    QPushButton *btnFullOpen;
    QPushButton *btnFullClose;

    //运动
    QGroupBox *motionGroup;
    QLabel *lblAxis;
    QLabel *lblCoordinate;
    QLabel *lblState;
    QLabel *lblMovePosition;
    QLabel *lblMoveSpeed;
    QLabel *lblMovePattern;
    QRadioButton *radioContinuous;
    QRadioButton *radioRelative;
    QRadioButton *radioAbsolute;

    QLabel *lblXAxis;
    QDoubleSpinBox *txtXCoordinate;
    QLineEdit *txtXState;
    QDoubleSpinBox *txtXMovePosition;
    QDoubleSpinBox *txtXSpeed;
    QPushButton *btnXObverse;
    QPushButton *btnXReverse;
    QPushButton *btnXZero;
    QPushButton *btnXStop;

    QLabel *lblYAxis;
    QDoubleSpinBox *txtYCoordinate;
    QLineEdit *txtYState;
    QDoubleSpinBox *txtYMovePosition;
    QDoubleSpinBox *txtYSpeed;
    QPushButton *btnYObverse;
    QPushButton *btnYReverse;
    QPushButton *btnYZero;
    QPushButton *btnYStop;

    QLabel *lblZAxis;
    QDoubleSpinBox *txtZCoordinate;
    QLineEdit *txtZState;
    QDoubleSpinBox *txtZMovePosition;
    QDoubleSpinBox *txtZSpeed;
    QPushButton *btnZObverse;
    QPushButton *btnZReverse;
    QPushButton *btnZZero;
    QPushButton *btnZStop;

    QLabel *lblRAxis;
    QDoubleSpinBox *txtRCoordinate;
    QLineEdit *txtRState;
    QDoubleSpinBox *txtRMovePosition;
    QDoubleSpinBox *txtRSpeed;
    QPushButton *btnRObverse;
    QPushButton *btnRReverse;
    QPushButton *btnRZero;
    QPushButton *btnRStop;

    QLabel *lblC1Axis;
    QDoubleSpinBox *txtC1Coordinate;
    QLineEdit *txtC1State;
    QDoubleSpinBox *txtC1MovePosition;
    QDoubleSpinBox *txtC1Speed;
    QPushButton *btnC1Obverse;
    QPushButton *btnC1Reverse;
    QPushButton *btnC1Zero;
    QPushButton *btnC1Stop;

    QLabel *lblC2Axis;
    QDoubleSpinBox *txtC2Coordinate;
    QLineEdit *txtC2State;
    QDoubleSpinBox *txtC2MovePosition;
    QDoubleSpinBox *txtC2Speed;
    QPushButton *btnC2Obverse;
    QPushButton *btnC2Reverse;
    QPushButton *btnC2Zero;
    QPushButton *btnC2Stop;

};
#endif // MAINWINDOW_H
