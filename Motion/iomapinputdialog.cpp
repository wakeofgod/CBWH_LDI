#include "iomapinputdialog.h"

IOMapInputDialog::IOMapInputDialog(QWidget *parent)
    :QDialog(parent),
    lblType(new QLabel(tr("映射IO类型:"),this)),
    lblIndex(new QLabel(tr("映射IO索引:"),this)),
    lblTime(new QLabel(tr("滤波时间(s):"),this)),
    comboType(new QComboBox(this)),
    comboIndex(new QComboBox(this)),
    txtTime(new QDoubleSpinBox(this)),
    btnOK(new QPushButton(tr("确定"),this)),
    btnCancle(new QPushButton(tr("取消"),this))
{
    setWindowTitle(tr("轴IO映射"));
    comboType->addItems({"正限位","负限位","原点","伺服报警","伺服到位","通用输入"});
    for (int i = 0; i < 24; ++i)
    {
        comboIndex->addItem(QString::number(i));
    }
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(lblType,0,0);
    layout->addWidget(comboType,0,1);
    layout->addWidget(lblIndex,1,0);
    layout->addWidget(comboIndex,1,1);
    layout->addWidget(btnOK,1,2);
    layout->addWidget(lblTime,2,0);
    layout->addWidget(txtTime,2,1);
    layout->addWidget(btnCancle,2,2);

    setLayout(layout);

    connect(btnOK,&QPushButton::clicked,this,[=](){
        emit accepted(getResult());
        accept();
    });
    connect(btnCancle,&QPushButton::clicked,this,&QDialog::reject);

    resize(300,200);
}

void IOMapInputDialog::setInitialData(const QString &txtType, const QString &txtIndex, const QString &time)
{
    comboType->setCurrentText(txtType);
    comboIndex->setCurrentText(txtIndex);
    txtTime->setValue(time.toDouble());
}

QString IOMapInputDialog::getResult() const
{
    QString result;
    result.append(comboType->currentText());
    result.append(":");
    result.append(comboIndex->currentText());
    result.append(",滤波:");
    result.append(QString::number(txtTime->value()));
    return result;
}
