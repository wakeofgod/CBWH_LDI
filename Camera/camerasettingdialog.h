#ifndef CAMERASETTINGDIALOG_H
#define CAMERASETTINGDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>

class CameraSettingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CameraSettingDialog(QWidget *parent = nullptr);
    ~CameraSettingDialog();

    void initWidget();

private:
    QGroupBox *cameraGroup;
    QPushButton *btnConnect;
    QPushButton *btnDisConnect;
    QPushButton *btnStartRecord;
    QPushButton *btnStopRecord;
    QPushButton *btnCamera1Work;
    QPushButton *btnCamera2Work;
    QPushButton *btnMapRead;

    QPushButton *btnClose;
};

#endif // CAMERASETTINGDIALOG_H
