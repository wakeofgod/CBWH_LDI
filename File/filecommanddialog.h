#ifndef FILECOMMANDDIALOG_H
#define FILECOMMANDDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QProcess>
#include "frmmessagebox.h"

class FileCommandDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FileCommandDialog(QWidget *parent = nullptr);
    ~FileCommandDialog();

    void initWidget();

    void generateSuffix(const QString &fileName);

public slots:
    void btnExeSelectSlot();
    void btnTifSelectSlot();
    void btnGerberSlot();
    void btnOutputSlot();
    void btnPreviewGerberSlot();
    void btnPreviewTifSlot();
    void btnExecScaleSlot();
    void btnExecRotateSlot();
    void btnExprotTifSlot();

private:
    QGroupBox *fileGroup;
    QPushButton *btnExeSelect;
    QLineEdit *txtExePath;
    QString exePath = "C:/wcad/GBRVU64/artwork/gbrunmgr64.exe";
    //QString exePath = "D:/testCommand/test_02.exe";


    QPushButton *btnGerberSelect;
    QLineEdit *txtGerberPath;
    QString gerberPath = "D:/cam/board_cam350.gbr";

    QPushButton *btnOutputPath;
    QLineEdit *txtOutputPath;
    QString outputPath = "D:/cam/output";

    QPushButton *btnTifSelect;
    QLineEdit *txtTifPath;
    QString tifPath = "C:/WCAD/GBRIP64/gbr2tiff64.exe";

    QLabel *lblScaleSize;
    QLineEdit *txtScaleSize;
    QPushButton *btnExecScale;
    double scaleSize = 0;

    QLabel *lblRotationAngle;
    QLineEdit *txtRotationAngle;
    QPushButton *btnExecRotate;
    double rotateAngle = 0;

    QPushButton *btnPreviewGerber;
    QPushButton *btnPreviewTif;
    QPushButton *btnExportTif;

    QLabel *lblTifPic;

    QString fileName;
    QString ripName;
    QString zoomName;
    QString rotateName;
    QString tifName;


    QPushButton *btnClose;
    FrmMessageBox *msgBox;
};

#endif // FILECOMMANDDIALOG_H
