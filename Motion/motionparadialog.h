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
