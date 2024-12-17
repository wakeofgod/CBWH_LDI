#include "motionparadialog.h"

MotionParaDialog::MotionParaDialog(QWidget *parent):QDialog(parent)
{
    setWindowTitle(tr("参数设置"));
    //图标暂缺
    btnUpload = new QPushButton(tr("上传"));
    btnDownload = new QPushButton(tr("下载"));
    btnImport = new QPushButton(tr("导入配置文件"));
    btnExport = new QPushButton(tr("导出配置文件"));

    motionTabWidget = new QTabWidget();
    axisTab = new AxisSettingTab();
    runinTab = new RuninSettingTab();
    motionTabWidget->addTab(axisTab,tr("轴设置"));
    motionTabWidget->addTab(runinTab,tr("插补设置"));
    motionTabWidget->setTabPosition(QTabWidget::West);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(btnUpload,0,0);
    mainLayout->addWidget(btnDownload,0,1);
    mainLayout->addWidget(btnImport,0,2);
    mainLayout->addWidget(btnExport,0,3);
    mainLayout->addWidget(motionTabWidget, 1, 0,10,7);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    //mainLayout->setVerticalSpacing(10);  // 增加按钮之间的间距
    mainLayout->setRowMinimumHeight(0, 40);  // 设置第一行高度
    setLayout(mainLayout);

    Qt::WindowFlags flags = windowFlags();
    flags &= ~Qt::WindowContextHelpButtonHint;
    flags |= Qt::MSWindowsFixedSizeDialogHint;
    setWindowFlags(flags);
    resize(800,600);
}

MotionParaDialog::~MotionParaDialog()
{

}
