#ifndef IOMAPINPUTDIALOG_H
#define IOMAPINPUTDIALOG_H

#include <QDialog>
#include <QtWidgets>

//参数设置 轴IO映射弹窗
class IOMapInputDialog : public QDialog
{
    Q_OBJECT
public:
    explicit IOMapInputDialog(QWidget *parent = nullptr);

    void setInitialData(const QString &txtType,const QString &txtIndex,const QString &time);
    QString getResult()const;

signals:
    void accepted(const QString &result);
private:
    QLabel *lblType;
    QLabel *lblIndex;
    QLabel *lblTime;
    QComboBox *comboType;
    QComboBox *comboIndex;
    QDoubleSpinBox *txtTime;
    QPushButton *btnOK;
    QPushButton *btnCancle;
};

#endif // IOMAPINPUTDIALOG_H
