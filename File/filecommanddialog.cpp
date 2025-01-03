#include "filecommanddialog.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QIntValidator>
#include <QDebug>

FileCommandDialog::FileCommandDialog(QWidget *parent):QDialog(parent)
{
    setWindowTitle(tr("文件设置"));
    setObjectName("FileCommandDialog");
    initWidget();

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(fileGroup,0,0);
    setLayout(mainLayout);
    QList<QPushButton*> btnList = findChildren<QPushButton*>();
    foreach (QPushButton* btn, btnList) {
        btn->setFocusPolicy(Qt::NoFocus);
    }

    Qt::WindowFlags flags = windowFlags();
    flags &= ~Qt::WindowContextHelpButtonHint;
    flags |= Qt::MSWindowsFixedSizeDialogHint;
    setWindowFlags(flags);
    resize(800,600);
    //弹窗的焦点出现在按钮上，待解决
    //txtScaleSize->setFocus();

    if(!exePath.isEmpty())
    {
        txtExePath->setText(exePath);
    }
    if(!tifPath.isEmpty())
    {
        txtTifPath->setText(tifPath);
    }
    if(!gerberPath.isEmpty())
    {
        txtGerberPath->setText(gerberPath);
        generateSuffix(gerberPath);
    }
    if(!outputPath.isEmpty())
    {
        txtOutputPath->setText(outputPath);
    }

    connect(btnClose,&QPushButton::clicked,this,&QDialog::reject);
    connect(btnExeSelect,&QPushButton::clicked,this,&FileCommandDialog::btnExeSelectSlot);
    connect(btnTifSelect,&QPushButton::clicked,this,&FileCommandDialog::btnTifSelectSlot);
    connect(btnGerberSelect,&QPushButton::clicked,this,&FileCommandDialog::btnGerberSlot);
    connect(btnOutputPath,&QPushButton::clicked,this,&FileCommandDialog::btnOutputSlot);
    connect(btnPreviewGerber,&QPushButton::clicked,this,&FileCommandDialog::btnPreviewGerberSlot);
    connect(btnPreviewTif,&QPushButton::clicked,this,&FileCommandDialog::btnPreviewTifSlot);
    connect(btnExecScale,&QPushButton::clicked,this,&FileCommandDialog::btnExecScaleSlot);
    connect(btnExecRotate,&QPushButton::clicked,this,&FileCommandDialog::btnExecRotateSlot);
    connect(btnExportTif,&QPushButton::clicked,this,&FileCommandDialog::btnExprotTifSlot);
}

FileCommandDialog::~FileCommandDialog()
{

}

void FileCommandDialog::initWidget()
{
    QGridLayout *fLayout = new QGridLayout();
    fLayout->setContentsMargins(0,0,0,0);
    fLayout->setSpacing(10);
    fileGroup = new QGroupBox();
    fileGroup->setStyleSheet("QGroupBox{border:none;}");
    btnExeSelect = new QPushButton(tr("选择exe路径"));
    txtExePath = new QLineEdit();
    txtExePath->setReadOnly(true);

    btnTifSelect = new QPushButton(tr("选择导出TIF exe路径"));
    txtTifPath = new QLineEdit();
    txtTifPath->setReadOnly(true);

    btnGerberSelect = new QPushButton(tr("选择gerber文件路径"));
    txtGerberPath = new QLineEdit();
    txtGerberPath->setReadOnly(true);

    btnOutputPath = new QPushButton(tr("选择导出文件路径"));
    txtOutputPath = new QLineEdit();
    txtOutputPath->setReadOnly(true);

    lblScaleSize = new QLabel(tr("缩放大小"));
    txtScaleSize = new QLineEdit();
    //数字越界待解决
    QIntValidator *validator = new QIntValidator(0,100,this);
    txtScaleSize->setValidator(validator);
    btnExecScale = new QPushButton(tr("执行"));

    lblRotationAngle = new QLabel(tr("旋转角度"));
    txtRotationAngle = new QLineEdit();
    validator = new QIntValidator(0,360,this);
    txtRotationAngle->setValidator(validator);
    btnExecRotate = new QPushButton(tr("执行"));

    btnPreviewGerber = new QPushButton(tr("预览gerber"));
    btnPreviewTif = new QPushButton(tr("预览tif"));
    btnExportTif = new QPushButton(tr("导出TIF"));

    lblTifPic = new QLabel();


    btnClose = new QPushButton(tr("关闭"));
    //btnClose->setStyleSheet("QPushButton { background-color: #87CEFA; color: white; font-size: 16px; }");

    fLayout->addWidget(btnExeSelect,0,0);
    fLayout->addWidget(txtExePath,0,1);
    fLayout->addWidget(btnTifSelect,0,2);
    fLayout->addWidget(txtTifPath,0,3);

    fLayout->addWidget(btnGerberSelect,1,0);
    fLayout->addWidget(txtGerberPath,1,1);
    fLayout->addWidget(btnOutputPath,1,2);
    fLayout->addWidget(txtOutputPath,1,3);

    fLayout->addWidget(lblScaleSize,2,0);
    fLayout->addWidget(txtScaleSize,2,1);
    fLayout->addWidget(btnExecScale,2,2);

    fLayout->addWidget(lblRotationAngle,3,0);
    fLayout->addWidget(txtRotationAngle,3,1);
    fLayout->addWidget(btnExecRotate,3,2);

    fLayout->addWidget(btnPreviewGerber,4,0);
    fLayout->addWidget(btnPreviewTif,4,1);
    fLayout->addWidget(btnExportTif,4,2);

    fLayout->addWidget(lblTifPic,5,0,4,4);

    fLayout->addWidget(btnClose,9,3);

    fLayout->setRowStretch(0,1);
    fLayout->setRowStretch(1,1);
    fLayout->setRowStretch(2,1);
    fLayout->setRowStretch(3,1);
    fLayout->setRowStretch(4,1);
    fLayout->setRowStretch(5,1);

    fLayout->setColumnStretch(0,1);
    fLayout->setColumnStretch(1,1);
    fLayout->setColumnStretch(2,1);
    fLayout->setColumnStretch(3,1);
    fileGroup->setLayout(fLayout);
}

void FileCommandDialog::generateSuffix(const QString &folderPath)
{
    QString rootPath = QFileInfo(folderPath).absolutePath();
    QString fileName = QFileInfo(folderPath).fileName();
    QString baseName = fileName.section('.',0,0);
    ripName = baseName + "_gbr_rip_size.gbr";
    zoomName = baseName + "_gbr_rip_size+.gbr";
    rotateName = baseName + "_gbr_rip_size_rotate.gbr";
    tifName = baseName + "_gbr_rip_size_rotate.tif";
    qDebug()<<QString("ripName=%1 zoomName=%2 rotateName=%3 tifName=%4").arg(ripName,zoomName,rotateName,tifName);

}

void FileCommandDialog::btnExeSelectSlot()
{
    QString folderPath = QFileDialog::getOpenFileName(nullptr, "选择文件", QString(), "所有文件 (*.*)");
    if (!folderPath.isEmpty())
    {
        txtExePath->setText(folderPath);
        exePath = folderPath;
    }
    else
    {
        //qDebug()<<QString("文件为空");
        msgBox = new FrmMessageBox();
        msgBox->showFrm("文件为空",2);
    }
}

void FileCommandDialog::btnTifSelectSlot()
{
    QString folderPath = QFileDialog::getOpenFileName(nullptr, "选择文件", QString(), "所有文件 (*.*)");
    if (!folderPath.isEmpty())
    {
        txtTifPath->setText(folderPath);
        tifPath = folderPath;
    }
    else
    {
        msgBox = new FrmMessageBox();
        msgBox->showFrm("文件为空",2);
    }
}

void FileCommandDialog::btnGerberSlot()
{
    QString folderPath = QFileDialog::getOpenFileName(nullptr, "选择文件", QString(), "所有文件 (*.*)");
    if (!folderPath.isEmpty())
    {
        txtGerberPath->setText(folderPath);
        gerberPath = folderPath;
        generateSuffix(folderPath);
    }
    else
    {
        qDebug()<<QString("文件为空");
    }
}

void FileCommandDialog::btnOutputSlot()
{
    QString folderPath = QFileDialog::getExistingDirectory(this,"选择文件夹",QString(),QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!folderPath.isEmpty())
    {
        txtOutputPath->setText(folderPath);
        outputPath = folderPath;
    }
    else
    {

    }
}

//预览gerber需要调用第三方exe
void FileCommandDialog::btnPreviewGerberSlot()
{
    QProcess p(0);
    QString previewPath = "C:/wcad/GBRVU64/artwork/gbrvu64.exe";
    QString command = QDir::toNativeSeparators(previewPath) ;
    //QStringList args;
    p.execute(command);
}

//是否是16位图像待验证
void FileCommandDialog::btnPreviewTifSlot()
{
    QImageReader::setAllocationLimit(1024);


    // QDir dir(outputPath);
    // QString tifFilePath = dir.absoluteFilePath(tifName);
    //QString tifFilePath = "D:/16bpc.tiff";
    QString tifFilePath = "D:/board_cam350_gbr_rip_size_rotate.tiff";
    QImageReader reader(tifFilePath);
    QImage image = reader.read();
    if (image.isNull()) {
        qDebug()<<QString("FileCommandDialog::btnPreviewTifSlot %1").arg(tifFilePath);
    }
    else
    {
        QSize targetSize(1920, 1080);  // 缩放到适合屏幕的大小
        QImage scaledImage = image.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // 创建QPixmap并显示
        QPixmap qpixmap = QPixmap::fromImage(scaledImage);
        qpixmap = qpixmap.scaled(lblTifPic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        lblTifPic->setPixmap(qpixmap);
    }
}

void FileCommandDialog::btnExecScaleSlot()
{
#if 0
    QProcess p(0);
    p.start("cmd", QStringList()<<"/c"<<"ping www.baidu.com");
    p.waitForStarted();
    p.waitForFinished();
    QString strTemp=QString::fromLocal8Bit(p.readAllStandardOutput());
    qDebug()<<strTemp;
#endif
    //qDebug()<<QString("exe路径=%1 gerber路径=%2 缩放=%3 旋转=%4").arg(exePath,gerberPath,QString::number(scaleSize),QString::number(rotateAngle));
    QProcess p(0);
    QString command = QDir::toNativeSeparators(exePath) ;
    QStringList args;

    args.append(QDir::toNativeSeparators(gerberPath));
    QDir dir(outputPath);
    QString fullPath = dir.filePath(ripName);
    QString str1 = QString("-out:%1").arg(QDir::toNativeSeparators(fullPath));
    args.append(str1);
    str1 = QString("-wdir:%1\\").arg(QDir::toNativeSeparators(outputPath));
    if (!str1.endsWith(QDir::separator()))
    {
        str1.append(QDir::separator());
    }
    args.append(str1);

    args.append("-outputtype:rs274x");
    args.append("-arcsag:0.0001inch");
    args.append("-silent");
    args.append("-singledlg");
    args.append("-thrnum:4");
    args.append("-maxpoints:10000");
    bool bOk;
    scaleSize = txtScaleSize->text().toDouble(&bOk);
    if(!bOk)
    {
        qDebug()<<QString("转换失败");
    }
    str1 = QString("-sizingvalue:%1mm").arg(scaleSize/100);
    args.append(str1);

    //打印输出所有命令参数
    // for (const QString &arg : args)
    // {
    //     qDebug() << arg;
    // }
    //command是要执行的命令,args是参数
    p.execute(command,args);
    p.waitForFinished();
    int exitCode = p.exitCode();
    qDebug() << "Exit Code:" << exitCode;

}

void FileCommandDialog::btnExecRotateSlot()
{
    QProcess p(0);
    QString command = QDir::toNativeSeparators(exePath);
    QStringList args;

    //旋转文件需确认
    args.append(QDir::toNativeSeparators(gerberPath));
    QDir dir(outputPath);
    QString fullPath = dir.filePath(rotateName);
    QString str1 = QString("-out:%1").arg(QDir::toNativeSeparators(fullPath));
    args.append(str1);
    str1 = QString("-wdir:%1\\").arg(QDir::toNativeSeparators(outputPath));

    // 如果没有结尾的分隔符，添加一个
    if (!str1.endsWith(QDir::separator()))
    {
        str1.append(QDir::separator());
    }
    args.append(str1);

    args.append("-outputtype:rs274x");
    args.append("-arcsag:0.0001inch");
    args.append("-silent");
    args.append("-singledlg");
    args.append("-thrnum:4");
    args.append("-maxpoints:10000");
    bool bOk;
    rotateAngle = txtRotationAngle->text().toDouble(&bOk);
    if(!bOk)
    {
        qDebug()<<QString("转换失败");
    }
    str1 = QString("-xform:0,0,%1,0,0,1,1,0,0").arg(rotateAngle);
    args.append(str1);

    //打印输出所有命令参数
    for (const QString &arg : args)
    {
        qDebug() << arg;
    }
    p.execute(command,args);
    p.waitForFinished();
    int exitCode = p.exitCode();
    qDebug() << "Exit Code:" << exitCode;
}

void FileCommandDialog::btnExprotTifSlot()
{
    QProcess p(0);
    QString command = QDir::toNativeSeparators(tifPath);
    QStringList args;

    //导出文件需要确认
    //args.append(QDir::toNativeSeparators(gerberPath));
    QDir dir(outputPath);
    QString fullPath = dir.filePath(rotateName);
    args.append(QDir::toNativeSeparators(fullPath));

    args.append("-274x");
    args.append("-aw");
    args.append("-dpi:10656");
    args.append("-status");
    args.append("-logcalls");
    args.append("-ram:128");

    fullPath = dir.filePath(tifName);
    QString str1 = QString("-pack:%1").arg(QDir::toNativeSeparators(fullPath));
    args.append(str1);
    args.append("-units:inch");

    p.execute(command,args);
    p.waitForFinished();
    int exitCode = p.exitCode();
    qDebug() << "Exit Code:" << exitCode;
}
