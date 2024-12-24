#ifndef MOTIONPARADIALOG_H
#define MOTIONPARADIALOG_H

#include <QDialog>
#include <QtWidgets>

#include "axissettingtab.h"
#include "runinsettingtab.h"

class MotionParaDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MotionParaDialog(QWidget *parent = nullptr);
    ~MotionParaDialog();

public slots:
    void btnUploadSlot();
    void btnDownloadSlot();
    void btnImportSlot();
    void btnExportSlot();

signals:
    void uploadTab();
    void downloadTab();
    void importTab();
    void ExportTab();
private:
    QPushButton *btnUpload;
    QPushButton *btnDownload;
    QPushButton *btnImport;
    QPushButton *btnExport;

    QTabWidget *motionTabWidget;
    AxisSettingTab *axisTab;
    RuninSettingTab *runinTab;
};

#endif // MOTIONPARADIALOG_H
