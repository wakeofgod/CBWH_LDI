#include "inpudialogmotiondelegate.h"
#include "iomapinputdialog.h"
#include <QRegularExpression>
#include <QDebug>

InpuDialogMotionDelegate::InpuDialogMotionDelegate(QObject *parent)
    : QItemDelegate{parent}
{

}

QWidget *InpuDialogMotionDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QWidget *editor = new QWidget(parent);
    QHBoxLayout *layout = new QHBoxLayout(editor);
    QLineEdit *lineEdit = new QLineEdit(editor);
    QPushButton *btn = new QPushButton("...",editor);
    lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lineEdit->setReadOnly(true);
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    layout->setContentsMargins(0,0,0,0);

    layout->addWidget(lineEdit);
    layout->addWidget(btn);
    editor->setLayout(layout);

    QString inputStr = index.data().toString();
    qDebug()<<inputStr;
    lineEdit->setText(inputStr);

    connect(btn,&QPushButton::clicked,this,[=](){
        QPointer<IOMapInputDialog> dialog = new IOMapInputDialog(lineEdit->parentWidget());
        if(!inputStr.isEmpty())
        {
            //拆分单元格字符串,字符串带中文，要用大S
            static QRegularExpression re("(\\S+):(\\d+)\\s*,\\S+:(\\d+)s?");
            QRegularExpressionMatch match = re.match(inputStr);
            if(match.hasMatch())
            {
                QString typeStr = match.captured(1);
                QString indexStr = match.captured(2);
                QString timeStr = match.captured(3);
                //对话框赋初值
                dialog->setInitialData(typeStr,indexStr,timeStr);
            }
            else
            {
                qDebug()<<QString("正则表达式捕获失败");
            }
        }

        connect(dialog,&IOMapInputDialog::accepted,this,[=](const QString &result)
                {
                    lineEdit->setText(result);
                    dialog->deleteLater();
                });
        dialog->exec();
    });

    return editor;
}

void InpuDialogMotionDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineEdit = editor->findChild<QLineEdit *>();
    if (lineEdit) {
        lineEdit->setText(index.data().toString());
    }
}

void InpuDialogMotionDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = editor->findChild<QLineEdit *>();
    if (lineEdit) {
        model->setData(index, lineEdit->text());
    }
}
