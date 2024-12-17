#include "comboboxmotiondelegate.h"
ComboBoxMotionDelegate::ComboBoxMotionDelegate(QStringList moptions, QString defaultText, QObject *parent)
    :QItemDelegate(parent),mOptions(moptions),mDefaultText(defaultText)
{

}

ComboBoxMotionDelegate::~ComboBoxMotionDelegate()
{

}

QWidget *ComboBoxMotionDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItems(mOptions);
    return editor;
}

void ComboBoxMotionDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
    if (comboBox) {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        comboBox->setCurrentText(value);
    }
}

void ComboBoxMotionDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
    if (comboBox) {
        model->setData(index, comboBox->currentText(), Qt::EditRole);
    }
}

void ComboBoxMotionDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    }

    // 非编辑状态下绘制自定义文本
    if (!(index.model()->flags(index) & Qt::ItemIsEditable)) {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();

        // 如果没有选中项，则显示默认文本
        if (value.isEmpty()) {
            value = mDefaultText;  // 使用构造函数传入的默认文本
        }

        // 绘制文本
        painter->drawText(option.rect, Qt::AlignCenter, value);
    } else {
        // 如果处于编辑模式，不需要做绘制，因为下拉框已经会自动绘制
        QItemDelegate::paint(painter, option, index);
    }
}
