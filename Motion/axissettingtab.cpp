#include "axissettingtab.h"
#include "comboboxmotiondelegate.h"

AxisSettingTab::AxisSettingTab(QWidget *parent)
    : QWidget{parent}
{
    initView();
    loadMockData();
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(paraTableView,0,0);
    setLayout(mainLayout);
}

void AxisSettingTab::initView()
{
    paraTableView = new QTableView();
    paraModel = new QStandardItemModel();

    paraModel->setHorizontalHeaderItem(0,new QStandardItem(""));
    paraModel->setHorizontalHeaderItem(1,new QStandardItem("轴0"));
    paraModel->setHorizontalHeaderItem(2,new QStandardItem("轴1"));
    paraModel->setHorizontalHeaderItem(3,new QStandardItem("轴2"));
    paraModel->setHorizontalHeaderItem(4,new QStandardItem("轴3"));
    paraModel->setHorizontalHeaderItem(5,new QStandardItem("轴4"));
    paraModel->setHorizontalHeaderItem(6,new QStandardItem("轴5"));

    QStringList customLabels;
    customLabels <<"脉冲模式"
                 <<"脉冲当量(pluse/unit)"
                 <<"初始速度(unit/s)"
                 <<"定位速度(unit/s)"
                 <<"终止速度(unit/s)"
                 <<"加速时间(s)"
                 <<"减速时间(s)"
                 <<"S段时间(s)"
                 <<"反向间隙(unit)"
                 <<"减速停止时间(s)"
                 <<"回零低速(unit/s)"
                 <<"回零高速(unit/s)"
                 <<"加速时间(s)"
                 <<"减速时间(s)"
                 <<"回零模式"
                 <<"回零锁存源"
                 <<"回零方向"
                 <<"有效电平"
                 <<"零点IO映射"
                 <<"硬限位启用"
                 <<"停止模式"
                 <<"有效电平"
                 <<"正限位IO映射"
                 <<"负限位IO映射"
                 <<"限位启用"
                 <<"软限位正"
                 <<"软限位负"
                 <<"停止模式"
                 <<"编码器启用"
                 <<"编码器模式"
                 <<"输入脉冲反转"
                 <<"EZ有效电平"
                 <<"报警启用"
                 <<"有效电平"
                 <<"报警IO映射"
                 <<"到位启用"
                 <<"有效电平"
                 <<"到位IO映射"
                 <<"急停启用"
                 <<"有效电平"
                 <<"急停IO映射"
                 <<"信号启用"
                 <<"有效电平"
                 <<"减速停止IO映射";
    paraModel->setVerticalHeaderLabels(customLabels);

    paraTableView->setModel(paraModel);
    paraTableView->setSortingEnabled(false);
    paraTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    paraTableView->setShowGrid(true);
    paraTableView->setColumnHidden(0,true);
    //paraTableView->verticalHeader()->hide();
    paraTableView->setAlternatingRowColors(true);
    paraTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    paraTableView->horizontalHeader()->setHighlightSections(true);
}

void AxisSettingTab::loadMockData()
{
    //qDebug()<<paraModel->rowCount();
    QList<QStringList> mockData;
    mockData.append({"脉冲模式", "未知", "未知", "未知", "未知", "未知","未知"});
    mockData.append({"脉冲当量", "0", "0", "0", "0", "0","0"});
    mockData.append({"初始速度", "0", "0", "0", "0", "0","0"});
    mockData.append({"定位速度", "0", "0", "0", "0", "0","0"});
    mockData.append({"终止速度", "0", "0", "0", "0", "0","0"});
    mockData.append({"加速时间", "0", "0", "0", "0", "0","0"});
    mockData.append({"减速时间", "0", "0", "0", "0", "0","0"});
    mockData.append({"s段时间", "0", "0", "0", "0", "0","0"});
    mockData.append({"反向间隙", "0", "0", "0", "0", "0","0"});
    mockData.append({"减速停止时间", "0", "0", "0", "0", "0","0"});

    mockData.append({"回零低速", "0", "0", "0", "0", "0","0"});
    mockData.append({"回零高速", "0", "0", "0", "0", "0","0"});
    mockData.append({"加速时间", "0", "0", "0", "0", "0","0"});
    mockData.append({"减速时间", "0", "0", "0", "0", "0","0"});
    mockData.append({"回零模式", "无", "无", "无", "无", "无","无"});
    mockData.append({"回零所存源", "指令位置", "指令位置", "指令位置", "指令位置", "指令位置","指令位置"});
    mockData.append({"回零方向", "负方向", "负方向", "负方向", "负方向", "负方向","负方向"});
    mockData.append({"有效电平", "低", "低", "低", "低", "低","低"});
    mockData.append({"零点IO映射", "IO映射", "IO映射", "IO映射", "IO映射", "IO映射","IO映射"});

    mockData.append({"硬限位启用", "正负限位禁止", "正负限位禁止", "正负限位禁止", "正负限位禁止", "正负限位禁止","正负限位禁止"});
    mockData.append({"停止模式", "正负限位立即停止", "正负限位立即停止", "正负限位立即停止", "正负限位立即停止", "正负限位立即停止","正负限位立即停止"});
    mockData.append({"有效电平", "正负限位低电平", "正负限位低电平", "正负限位低电平", "正负限位低电平", "正负限位低电平","正负限位低电平"});
    mockData.append({"正限位IO映射", "IO映射", "IO映射", "IO映射", "IO映射", "IO映射","IO映射"});
    mockData.append({"负限位IO映射", "IO映射", "IO映射", "IO映射", "IO映射", "IO映射","IO映射"});

    mockData.append({"限位启用", "否", "否", "否", "否", "否","否"});
    mockData.append({"软限位正", "0", "0", "0", "0", "0","0"});
    mockData.append({"软限位负", "0", "0", "0", "0", "0","0"});
    mockData.append({"停止模式", "立即停止", "立即停止", "立即停止", "立即停止", "立即停止","立即停止"});
    mockData.append({"编码器启用", "否", "否", "否", "否", "否","否"});

    mockData.append({"编码器模式", "无", "无", "无", "无", "无","无"});
    mockData.append({"输入脉冲反转", "否", "否", "否", "否", "否","否"});
    mockData.append({"EZ有效电平", "低", "低", "低", "低", "低","低"});

    mockData.append({"报警启用", "否", "否", "否", "否", "否","否"});
    mockData.append({"有效电平", "低", "低", "低", "低", "低","低"});
    mockData.append({"报警IO映射", "IO映射", "IO映射", "IO映射", "IO映射", "IO映射","IO映射"});

    mockData.append({"到位启用", "否", "否", "否", "否", "否","否"});
    mockData.append({"有效电平", "低", "低", "低", "低", "低","低"});
    mockData.append({"到位IO映射", "IO映射", "IO映射", "IO映射", "IO映射", "IO映射","IO映射"});

    mockData.append({"急停启用", "否", "否", "否", "否", "否","否"});
    mockData.append({"有效电平", "低", "低", "低", "低", "低","低"});
    mockData.append({"急停IO映射", "IO映射", "IO映射", "IO映射", "IO映射", "IO映射","IO映射"});

    mockData.append({"信号启用", "否", "否", "否", "否", "否","否"});
    mockData.append({"有效电平", "低", "低", "低", "低", "低","低"});
    mockData.append({"减速停止IO映射", "IO映射", "IO映射", "IO映射", "IO映射", "IO映射","IO映射"});

    for (int row = 0; row < mockData.size(); ++row) {
        for (int col = 0; col < mockData[row].size(); ++col) {
            paraModel->setData(paraModel->index(row, col), mockData[row][col]);
        }
    }

    QStringList pulseStr = {"未知","脉冲高+方向高","脉冲低+方向高","脉冲高+方向低","脉冲低+方向低","双脉冲高","双脉冲低","AB相"};
    QString pulseDefault = QString(tr("未知"));
    ComboBoxMotionDelegate *pulseDelegate = new ComboBoxMotionDelegate(pulseStr,pulseDefault,paraTableView);
    paraTableView->setItemDelegateForRow(0,pulseDelegate);

    QStringList returnZeroStr = {"无","一次回零","一次回零+反找","两次回零","一次回零+EZ","EZ回零","一次回零+反找EZ","原点锁存","原点+EZ所存","EZ所存","原点+反向EZ所存"};
    QString returnZeroDefault = QString(tr("无"));
    ComboBoxMotionDelegate *returnZeroDelegate = new ComboBoxMotionDelegate(returnZeroStr,returnZeroDefault,paraTableView);
    paraTableView->setItemDelegateForRow(14,returnZeroDelegate);

    QStringList zeroLatchSoureStr = {"指令位置","反馈位置"};
    QString zeroLatchDefault = QString(tr("指令位置"));
    ComboBoxMotionDelegate *zeroLatchDelegate = new ComboBoxMotionDelegate(zeroLatchSoureStr,zeroLatchDefault,paraTableView);
    paraTableView->setItemDelegateForRow(15,zeroLatchDelegate);

    QStringList zeroDirectionStr = {"正方向","负方向"};
    QString zeroDirectionDefault = QString(tr("正方向"));
    ComboBoxMotionDelegate *zeroDirectionDelegate = new ComboBoxMotionDelegate(zeroDirectionStr,zeroDirectionDefault,paraTableView);
    paraTableView->setItemDelegateForRow(16,zeroDirectionDelegate);

    QStringList zeroLevelStr = {"低","高"};
    QString zeroLevelDefault = QString(tr("低"));
    ComboBoxMotionDelegate *zeroLevelDelegate = new ComboBoxMotionDelegate(zeroLevelStr,zeroLevelDefault,paraTableView);
    paraTableView->setItemDelegateForRow(17,zeroLevelDelegate);

    QStringList hardLimitStr = {"正负限位禁止","正负限位允许","正禁止，负允许","正允许，负禁止"};
    QString hardLimitDefault = QString(tr("正负限位禁止"));
    ComboBoxMotionDelegate *hardLimitDelegate = new ComboBoxMotionDelegate(hardLimitStr,hardLimitDefault,paraTableView);
    paraTableView->setItemDelegateForRow(19,hardLimitDelegate);

    QStringList hardStopStr = {"正负限位立即停止","正负限位减速","正立即，负减速","正减速，负立即"};
    QString hardStopDefault = QString(tr("正负限位立即停止"));
    ComboBoxMotionDelegate *hardStopDelegate = new ComboBoxMotionDelegate(hardStopStr,hardStopDefault,paraTableView);
    paraTableView->setItemDelegateForRow(20,hardStopDelegate);

    QStringList hardLevelStr = {"正负限位低电平","正负限位高电平","正低，负高","正高，负低"};
    QString hardLevelDefault = QString(tr("正负限位低电平"));
    ComboBoxMotionDelegate *hardLevelDelegate = new ComboBoxMotionDelegate(hardLevelStr,hardLevelDefault,paraTableView);
    paraTableView->setItemDelegateForRow(21,hardLevelDelegate);

    QStringList softLimitStr = {"是","否"};
    QString softLimitDefault = QString(tr("否"));
    ComboBoxMotionDelegate *softLimitDelegate = new ComboBoxMotionDelegate(softLimitStr,softLimitDefault,paraTableView);
    paraTableView->setItemDelegateForRow(24,softLimitDelegate);

    QStringList softStopStr = {"立即停止","减速停止"};
    QString softStopDefault = QString(tr("立即停止"));
    ComboBoxMotionDelegate *softStopDelegate = new ComboBoxMotionDelegate(softStopStr,softStopDefault,paraTableView);
    paraTableView->setItemDelegateForRow(27,softStopDelegate);

    QStringList encodeStr = {"是","否"};
    QString encodeDefault = QString(tr("否"));
    ComboBoxMotionDelegate *encodeDelegate = new ComboBoxMotionDelegate(encodeStr,encodeDefault,paraTableView);
    paraTableView->setItemDelegateForRow(28,encodeDelegate);

    QStringList encodeModeStr = {"无","非A/B相","A/B相1倍频","A/B相2倍频","A/B相4倍频"};
    QString encodeModeDefault = QString(tr("无"));
    ComboBoxMotionDelegate *encodeModeDelegate = new ComboBoxMotionDelegate(encodeModeStr,encodeModeDefault,paraTableView);
    paraTableView->setItemDelegateForRow(29,encodeModeDelegate);

    QStringList encodeReverseStr = {"是","否"};
    QString encodeReverseDefault = QString(tr("否"));
    ComboBoxMotionDelegate *encodeReverseDelegate = new ComboBoxMotionDelegate(encodeReverseStr,encodeReverseDefault,paraTableView);
    paraTableView->setItemDelegateForRow(30,encodeReverseDelegate);

    QStringList EZLevelStr = {"低","高"};
    QString EZLevelDefault = QString(tr("低"));
    ComboBoxMotionDelegate *EZLevelDelegate = new ComboBoxMotionDelegate(EZLevelStr,EZLevelDefault,paraTableView);
    paraTableView->setItemDelegateForRow(31,EZLevelDelegate);

    QStringList alarmStr = {"是","否"};
    QString alarmDefault = QString(tr("否"));
    ComboBoxMotionDelegate *alarmDelegate = new ComboBoxMotionDelegate(alarmStr,alarmDefault,paraTableView);
    paraTableView->setItemDelegateForRow(32,alarmDelegate);

    QStringList alarmLevelStr = {"高","低"};
    QString alarmLevelDefault = QString(tr("低"));
    ComboBoxMotionDelegate *alarmLevelDelegate = new ComboBoxMotionDelegate(alarmLevelStr,alarmLevelDefault,paraTableView);
    paraTableView->setItemDelegateForRow(33,alarmLevelDelegate);

    QStringList servoStr = {"是","否"};
    QString servoDefault = QString(tr("否"));
    ComboBoxMotionDelegate *servoDelegate = new ComboBoxMotionDelegate(servoStr,servoDefault,paraTableView);
    paraTableView->setItemDelegateForRow(35,servoDelegate);

    QStringList servoLevelStr = {"高","低"};
    QString servoLevelDefault = QString(tr("低"));
    ComboBoxMotionDelegate *servoLevelDelegate = new ComboBoxMotionDelegate(servoLevelStr,servoLevelDefault,paraTableView);
    paraTableView->setItemDelegateForRow(36,servoLevelDelegate);

    QStringList scramStr = {"是","否"};
    QString scramDefault = QString(tr("否"));
    ComboBoxMotionDelegate *scramDelegate = new ComboBoxMotionDelegate(scramStr,scramDefault,paraTableView);
    paraTableView->setItemDelegateForRow(38,scramDelegate);

    QStringList scramLevelStr = {"高","低"};
    QString scramLevelDefault = QString(tr("低"));
    ComboBoxMotionDelegate *scramLevelDelegate = new ComboBoxMotionDelegate(scramLevelStr,scramLevelDefault,paraTableView);
    paraTableView->setItemDelegateForRow(39,scramLevelDelegate);

    QStringList slowStr = {"是","否"};
    QString slowDefault = QString(tr("否"));
    ComboBoxMotionDelegate *slowDelegate = new ComboBoxMotionDelegate(slowStr,slowDefault,paraTableView);
    paraTableView->setItemDelegateForRow(41,scramDelegate);

    QStringList slowLevelStr = {"高","低"};
    QString slowLevelDefault = QString(tr("低"));
    ComboBoxMotionDelegate *slowLevelDelegate = new ComboBoxMotionDelegate(slowLevelStr,slowLevelDefault,paraTableView);
    paraTableView->setItemDelegateForRow(42,slowLevelDelegate);
}
