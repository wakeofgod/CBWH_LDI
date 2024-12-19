#ifndef MOTIONINFODIALOG_H
#define MOTIONINFODIALOG_H
#include <QDialog>
#include <QtWidgets>

class MotionInfoDialog : public QDialog
{
    Q_OBJECT
public:
   explicit MotionInfoDialog(QWidget *parent = nullptr);

private:
   QLabel *lblType;

};

#endif // MOTIONINFODIALOG_H
