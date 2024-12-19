#ifndef COMBOBOXMOTIONDELEGATE_H
#define COMBOBOXMOTIONDELEGATE_H

#include <QItemDelegate>
#include <QtWidgets>

class ComboBoxMotionDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit ComboBoxMotionDelegate(QStringList moptions,QString defaultText, QObject *parent = nullptr);
    ~ComboBoxMotionDelegate();

private:
    QStringList mOptions;
    QString mDefaultText;

    // QAbstractItemDelegate interface
public:
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // COMBOBOXMOTIONDELEGATE_H
