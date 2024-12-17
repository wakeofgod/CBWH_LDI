#ifndef MOTIONCONNECDIALOG_H
#define MOTIONCONNECDIALOG_H

#include <QDialog>
#include <QtWidgets>

class MotionConnecDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MotionConnecDialog(QWidget *parent = nullptr);

    void initView();

private:
    QGroupBox *serialGroup;
    QLabel *lblSerialPort;
    QLineEdit *txtSerialPort;
    QLabel *lblBaudRate;
    QLineEdit *txtBaudRate;
    QLabel *lblDataBit;
    QLineEdit *txtDataBit;
    QLabel *lblStopBit;
    QLineEdit *txtStopBit;

    QPushButton *btnSet;
};

#endif // MOTIONCONNECDIALOG_H
