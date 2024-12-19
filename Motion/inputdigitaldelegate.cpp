#include "inputdigitaldelegate.h"

InputDigitalDelegate::InputDigitalDelegate(double minValue, double maxValue, double step, int decimals, QObject *parent)
    :QItemDelegate(parent),
    dMinValue(minValue),
    dMaxValue(maxValue),
    dStep(step),
    iDecimals(decimals)
{

}

QWidget *InputDigitalDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDoubleSpinBox* spinBox = new QDoubleSpinBox(parent);
    // 设置范围
    spinBox->setRange(dMinValue, dMaxValue);
    // 设置最多小数点 3 位
    spinBox->setDecimals(iDecimals);
    // 设置步长
    spinBox->setSingleStep(dStep);
    return spinBox;
}

void InputDigitalDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (QDoubleSpinBox* spinBox = qobject_cast<QDoubleSpinBox*>(editor))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        spinBox->setValue(value);
    }
    else
    {
        QItemDelegate::setEditorData(editor, index);
    }
}

void InputDigitalDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (QDoubleSpinBox* spinBox = qobject_cast<QDoubleSpinBox*>(editor))
    {
        model->setData(index, spinBox->value());
    }
    else
    {
        QItemDelegate::setModelData(editor, model, index);
    }
}
