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
#include "filecommanddialog.h"
#include "camerasettingdialog.h"
#include "motionparadialog.h"
#include "motioninfodialog.h"
#include "motionconnecdialog.h"

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
    void createMotionControl();

    void fileActionSlot1();
    void fileActionSlot2();
    void fileActionSlot3();

    void cameraSlot1();
    void cameraSlot2();
    void cameraSlot3();

    void motionSlot1();
    void motionSlot2();
    void motionSlot3();

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
    QLineEdit *txtXCoordinate;
    QLineEdit *txtXState;
    QLineEdit *txtXMovePosition;
    QLineEdit *txtXSpeed;
    QPushButton *btnXObverse;
    QPushButton *btnXReverse;
    QPushButton *btnXZero;
    QPushButton *btnXStop;

    QLabel *lblYAxis;
    QLineEdit *txtYCoordinate;
    QLineEdit *txtYState;
    QLineEdit *txtYMovePosition;
    QLineEdit *txtYSpeed;
    QPushButton *btnYObverse;
    QPushButton *btnYReverse;
    QPushButton *btnYZero;
    QPushButton *btnYStop;

    QLabel *lblZAxis;
    QLineEdit *txtZCoordinate;
    QLineEdit *txtZState;
    QLineEdit *txtZMovePosition;
    QLineEdit *txtZSpeed;
    QPushButton *btnZObverse;
    QPushButton *btnZReverse;
    QPushButton *btnZZero;
    QPushButton *btnZStop;

    QLabel *lblRAxis;
    QLineEdit *txtRCoordinate;
    QLineEdit *txtRState;
    QLineEdit *txtRMovePosition;
    QLineEdit *txtRSpeed;
    QPushButton *btnRObverse;
    QPushButton *btnRReverse;
    QPushButton *btnRZero;
    QPushButton *btnRStop;

    QLabel *lblC1Axis;
    QLineEdit *txtC1Coordinate;
    QLineEdit *txtC1State;
    QLineEdit *txtC1MovePosition;
    QLineEdit *txtC1Speed;
    QPushButton *btnC1Obverse;
    QPushButton *btnC1Reverse;
    QPushButton *btnC1Zero;
    QPushButton *btnC1Stop;

    QLabel *lblC2Axis;
    QLineEdit *txtC2Coordinate;
    QLineEdit *txtC2State;
    QLineEdit *txtC2MovePosition;
    QLineEdit *txtC2Speed;
    QPushButton *btnC2Obverse;
    QPushButton *btnC2Reverse;
    QPushButton *btnC2Zero;
    QPushButton *btnC2Stop;

};
#endif // MAINWINDOW_H
