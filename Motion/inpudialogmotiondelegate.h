#ifndef INPUDIALOGMOTIONDELEGATE_H
#define INPUDIALOGMOTIONDELEGATE_H

#include <QItemDelegate>
#include <QtWidgets>
#include "iomapinputdialog.h"

//参数设置 单元格点击显示按钮的委托
class InpuDialogMotionDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit InpuDialogMotionDelegate(QObject *parent = nullptr);

    // QAbstractItemDelegate interface
public:
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

private:
    IOMapInputDialog *dialog;
};

#endif // INPUDIALOGMOTIONDELEGATE_H
