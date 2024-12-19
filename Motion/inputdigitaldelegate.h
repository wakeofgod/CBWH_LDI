#ifndef INPUTDIGITALDELEGATE_H
#define INPUTDIGITALDELEGATE_H

#include <QItemDelegate>
#include <QtWidgets>

//限定单元格输入数字委托
class InputDigitalDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit InputDigitalDelegate(double minValue,double maxValue,double step,int decimals, QObject *parent = nullptr);

    // QAbstractItemDelegate interface
public:
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

private:
    double dMinValue;
    double dMaxValue;
    double dStep;
    int iDecimals;
};

#endif // INPUTDIGITALDELEGATE_H
