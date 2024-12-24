#include "axissettingtab.h"
#include "comboboxmotiondelegate.h"
#include "inpudialogmotiondelegate.h"
#include "inputdigitaldelegate.h"
#include "basicsparameter.h"
#include <LTSMC.h>
#include <QDebug>

//脉冲模式
QMap<int,QString> plusMap ={
    {0,"脉冲高+方向高"},
    {1,"脉冲低+方向高"},
    {2,"脉冲高+方向低"},
    {3,"脉冲低+方向低"},
    {4,"双脉冲高"},
    {5,"双脉冲低"},
    {6,"AB相"}
};

//回零模式
QMap<int,QString> homeModeMap ={
    {0,"一次回零"},
    {1,"一次回零+反找"},
    {2,"两次回零"},
    {3,"一次回零+EZ"},
    {4,"EZ回零"},
    {5,"一次回零+反找EZ"},
    {6,"原点锁存"},
    {7,"原点+EZ所存"},
    {8,"EZ所存"},
    {9,"原点+反向EZ所存"}
};

//回零锁存源
QMap<int,QString> homeSourceMap ={
    {0,"指令位置"},
    {1,"反馈位置"}
};

//回零方向
QMap<int,QString> homeDirectMap = {
    {0,"负方向"},
    {1,"正方向"}
};

//有效电平
QMap<int,QString> homeOrgLogicMap ={
    {0,"低"},
    {1,"高"}
};

//硬限位启用
QMap<int,QString> hardElmodeMap ={
    {0,"正负限位禁止"},
    {1,"正负限位允许"},
    {2,"正禁止，负允许"},
    {3,"正允许，负禁止"}
};

//硬限位停止模式
QMap<int,QString> hardStopModeMap ={
    {0,"正负限位立即停止"},
    {1,"正负限位减速"},
    {2,"正立即，负减速"},
    {3,"正减速，负立即"}
};

//硬限位有效电平
QMap<int,QString> hardOrgLogicMap ={
    {0,"正负限位低电平"},
    {1,"正负限位高电平"},
    {2,"正低，负高"},
    {3,"正高，负低"}
};

//软限位启用
QMap<int,QString> softElmodeMap ={
    {0,"否"},
    {1,"是"}
};

//软限位停止模式
QMap<int,QString> softStopModeMap ={
    {0,"立即停止"},
    {1,"减速停止"}
};

//编码器模式
QMap<int,QString> counterModeMap ={
    {0,"非A/B相"},
    {1,"A/B相1倍频"},
    {2,"A/B相2倍频"},
    {3,"A/B相4倍频"}
};

//编码器有效电平
QMap<int,QString> counterOrgLogicMap ={
    {0,"低"},
    {1,"高"}
};

//映射IO类型，弹窗下拉框里不显示伺服准备和急停
QMap<int,QString> ioTypeMap ={
    {0,"正限位"},
    {1,"负限位"},
    {2,"原点"},
    {3,"伺服报警"},
    {4,"伺服准备"},
    {5,"伺服到位"},
    {6,"通用输入"},
    {7,"急停"}
};

AxisSettingTab::AxisSettingTab(QWidget *parent)
    : QWidget{parent}
{
    // initView();
    // loadMockData();
    initTable();
    QGridLayout *mainLayout = new QGridLayout();
    //mainLayout->addWidget(paraTableView,0,0);
    mainLayout->addWidget(paraTable,0,0);
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

void AxisSettingTab::initTable()
{
    paraTable = new QTableWidget();
    paraTable->setRowCount(53);
    paraTable->setColumnCount(6);

    //表头设置
    {
        paraTable->setHorizontalHeaderLabels({"轴0","轴1","轴2","轴3","轴4","轴5"});
        QStringList customLabels;
        customLabels <<"基本设置"
                     <<"脉冲模式"
                     <<"脉冲当量(pluse/unit)"
                     <<"初始速度(unit/s)"
                     <<"定位速度(unit/s)"
                     <<"终止速度(unit/s)"
                     <<"加速时间(s)"
                     <<"减速时间(s)"
                     <<"S段时间(s)"
                     <<"反向间隙(unit)"
                     <<"减速停止时间(s)"
                     <<"回零设置"
                     <<"回零低速(unit/s)"
                     <<"回零高速(unit/s)"
                     <<"加速时间(s)"
                     <<"减速时间(s)"
                     <<"回零模式"
                     <<"回零锁存源"
                     <<"回零方向"
                     <<"有效电平"
                     <<"零点IO映射"
                     <<"硬限位设置"
                     <<"硬限位启用"
                     <<"停止模式"
                     <<"有效电平"
                     <<"正限位IO映射"
                     <<"负限位IO映射"
                     <<"软限位设置"
                     <<"限位启用"
                     <<"软限位正"
                     <<"软限位负"
                     <<"停止模式"
                     <<"编码器启用"
                     <<"编码器设置"
                     <<"编码器模式"
                     <<"输入脉冲反转"
                     <<"EZ有效电平"
                     <<"伺服报警设置"
                     <<"报警启用"
                     <<"有效电平"
                     <<"报警IO映射"
                     <<"伺服到位设置"
                     <<"到位启用"
                     <<"有效电平"
                     <<"到位IO映射"
                     <<"急停设置"
                     <<"急停启用"
                     <<"有效电平"
                     <<"急停IO映射"
                     <<"减速停止设置"
                     <<"信号启用"
                     <<"有效电平"
                     <<"减速停止IO映射";
        paraTable->setVerticalHeaderLabels(customLabels);
    }

    //合并单元格
    {
        paraTable->setSpan(0,0,1,6);
        paraTable->setSpan(11,0,1,6);
        paraTable->setSpan(21,0,1,6);
        paraTable->setSpan(27,0,1,6);
        paraTable->setSpan(33,0,1,6);
        paraTable->setSpan(37,0,1,6);
        paraTable->setSpan(41,0,1,6);
        paraTable->setSpan(45,0,1,6);
        paraTable->setSpan(49,0,1,6);

        //单元格不能共用
        for (int row : {0, 11, 21, 27, 33, 37, 41, 45, 49}) {
            QTableWidgetItem *mergedItem = new QTableWidgetItem("");
            // 禁止编辑
            mergedItem->setFlags(mergedItem->flags() & ~Qt::ItemIsEditable);
            mergedItem->setBackground(QColor(102, 220, 220, 255));
            paraTable->setItem(row, 0, mergedItem);
        }
    }

    //数字委托 2-10 12-15 29,30
    {
        InputDigitalDelegate *digitalDelegate = new InputDigitalDelegate(0,10000,1,3,paraTable);
        paraTable->setItemDelegateForRow(2,digitalDelegate);
        paraTable->setItemDelegateForRow(3,digitalDelegate);
        paraTable->setItemDelegateForRow(4,digitalDelegate);
        paraTable->setItemDelegateForRow(5,digitalDelegate);
        paraTable->setItemDelegateForRow(6,digitalDelegate);
        paraTable->setItemDelegateForRow(7,digitalDelegate);
        paraTable->setItemDelegateForRow(8,digitalDelegate);
        paraTable->setItemDelegateForRow(9,digitalDelegate);
        paraTable->setItemDelegateForRow(10,digitalDelegate);
        paraTable->setItemDelegateForRow(12,digitalDelegate);
        paraTable->setItemDelegateForRow(13,digitalDelegate);
        paraTable->setItemDelegateForRow(14,digitalDelegate);
        paraTable->setItemDelegateForRow(15,digitalDelegate);
        paraTable->setItemDelegateForRow(29,digitalDelegate);
        paraTable->setItemDelegateForRow(30,digitalDelegate);
    }

    //下拉框委托  1 16-19 22-24 28 31 34-36 38 39 42 46 47 50 51
    {
        QStringList pulseStr = {"未知","脉冲高+方向高","脉冲低+方向高","脉冲高+方向低","脉冲低+方向低","双脉冲高","双脉冲低","AB相"};
        QString pulseDefault = QString(tr("未知"));
        ComboBoxMotionDelegate *pulseDelegate = new ComboBoxMotionDelegate(pulseStr,pulseDefault,paraTable);
        paraTable->setItemDelegateForRow(1,pulseDelegate);

        QStringList returnZeroStr = {"无","一次回零","一次回零+反找","两次回零","一次回零+EZ","EZ回零","一次回零+反找EZ","原点锁存","原点+EZ所存","EZ所存","原点+反向EZ所存"};
        QString returnZeroDefault = QString(tr("无"));
        ComboBoxMotionDelegate *returnZeroDelegate = new ComboBoxMotionDelegate(returnZeroStr,returnZeroDefault,paraTable);
        paraTable->setItemDelegateForRow(16,returnZeroDelegate);

        QStringList zeroLatchSoureStr = {"指令位置","反馈位置"};
        QString zeroLatchDefault = QString(tr("指令位置"));
        ComboBoxMotionDelegate *zeroLatchDelegate = new ComboBoxMotionDelegate(zeroLatchSoureStr,zeroLatchDefault,paraTable);
        paraTable->setItemDelegateForRow(17,zeroLatchDelegate);

        QStringList zeroDirectionStr = {"正方向","负方向"};
        QString zeroDirectionDefault = QString(tr("正方向"));
        ComboBoxMotionDelegate *zeroDirectionDelegate = new ComboBoxMotionDelegate(zeroDirectionStr,zeroDirectionDefault,paraTable);
        paraTable->setItemDelegateForRow(18,zeroDirectionDelegate);

        QStringList zeroLevelStr = {"低","高"};
        QString zeroLevelDefault = QString(tr("低"));
        ComboBoxMotionDelegate *zeroLevelDelegate = new ComboBoxMotionDelegate(zeroLevelStr,zeroLevelDefault,paraTable);
        paraTable->setItemDelegateForRow(19,zeroLevelDelegate);

        QStringList hardLimitStr = {"正负限位禁止","正负限位允许","正禁止，负允许","正允许，负禁止"};
        QString hardLimitDefault = QString(tr("正负限位禁止"));
        ComboBoxMotionDelegate *hardLimitDelegate = new ComboBoxMotionDelegate(hardLimitStr,hardLimitDefault,paraTable);
        paraTable->setItemDelegateForRow(22,hardLimitDelegate);

        QStringList hardStopStr = {"正负限位立即停止","正负限位减速","正立即，负减速","正减速，负立即"};
        QString hardStopDefault = QString(tr("正负限位立即停止"));
        ComboBoxMotionDelegate *hardStopDelegate = new ComboBoxMotionDelegate(hardStopStr,hardStopDefault,paraTable);
        paraTable->setItemDelegateForRow(23,hardStopDelegate);

        QStringList hardLevelStr = {"正负限位低电平","正负限位高电平","正低，负高","正高，负低"};
        QString hardLevelDefault = QString(tr("正负限位低电平"));
        ComboBoxMotionDelegate *hardLevelDelegate = new ComboBoxMotionDelegate(hardLevelStr,hardLevelDefault,paraTable);
        paraTable->setItemDelegateForRow(24,hardLevelDelegate);

        QStringList softLimitStr = {"是","否"};
        QString softLimitDefault = QString(tr("否"));
        ComboBoxMotionDelegate *softLimitDelegate = new ComboBoxMotionDelegate(softLimitStr,softLimitDefault,paraTable);
        paraTable->setItemDelegateForRow(28,softLimitDelegate);

        QStringList softStopStr = {"立即停止","减速停止"};
        QString softStopDefault = QString(tr("立即停止"));
        ComboBoxMotionDelegate *softStopDelegate = new ComboBoxMotionDelegate(softStopStr,softStopDefault,paraTable);
        paraTable->setItemDelegateForRow(31,softStopDelegate);

        QStringList encodeStr = {"是","否"};
        QString encodeDefault = QString(tr("否"));
        ComboBoxMotionDelegate *encodeDelegate = new ComboBoxMotionDelegate(encodeStr,encodeDefault,paraTable);
        paraTable->setItemDelegateForRow(32,encodeDelegate);

        QStringList encodeModeStr = {"无","非A/B相","A/B相1倍频","A/B相2倍频","A/B相4倍频"};
        QString encodeModeDefault = QString(tr("无"));
        ComboBoxMotionDelegate *encodeModeDelegate = new ComboBoxMotionDelegate(encodeModeStr,encodeModeDefault,paraTable);
        paraTable->setItemDelegateForRow(34,encodeModeDelegate);

        QStringList encodeReverseStr = {"是","否"};
        QString encodeReverseDefault = QString(tr("否"));
        ComboBoxMotionDelegate *encodeReverseDelegate = new ComboBoxMotionDelegate(encodeReverseStr,encodeReverseDefault,paraTable);
        paraTable->setItemDelegateForRow(35,encodeReverseDelegate);

        QStringList EZLevelStr = {"低","高"};
        QString EZLevelDefault = QString(tr("低"));
        ComboBoxMotionDelegate *EZLevelDelegate = new ComboBoxMotionDelegate(EZLevelStr,EZLevelDefault,paraTable);
        paraTable->setItemDelegateForRow(36,EZLevelDelegate);

        QStringList alarmStr = {"是","否"};
        QString alarmDefault = QString(tr("否"));
        ComboBoxMotionDelegate *alarmDelegate = new ComboBoxMotionDelegate(alarmStr,alarmDefault,paraTable);
        paraTable->setItemDelegateForRow(38,alarmDelegate);

        QStringList alarmLevelStr = {"高","低"};
        QString alarmLevelDefault = QString(tr("低"));
        ComboBoxMotionDelegate *alarmLevelDelegate = new ComboBoxMotionDelegate(alarmLevelStr,alarmLevelDefault,paraTable);
        paraTable->setItemDelegateForRow(39,alarmLevelDelegate);

        QStringList servoStr = {"是","否"};
        QString servoDefault = QString(tr("否"));
        ComboBoxMotionDelegate *servoDelegate = new ComboBoxMotionDelegate(servoStr,servoDefault,paraTable);
        paraTable->setItemDelegateForRow(42,servoDelegate);

        QStringList servoLevelStr = {"高","低"};
        QString servoLevelDefault = QString(tr("低"));
        ComboBoxMotionDelegate *servoLevelDelegate = new ComboBoxMotionDelegate(servoLevelStr,servoLevelDefault,paraTable);
        paraTable->setItemDelegateForRow(43,servoLevelDelegate);

        QStringList scramStr = {"是","否"};
        QString scramDefault = QString(tr("否"));
        ComboBoxMotionDelegate *scramDelegate = new ComboBoxMotionDelegate(scramStr,scramDefault,paraTable);
        paraTable->setItemDelegateForRow(46,scramDelegate);

        QStringList scramLevelStr = {"高","低"};
        QString scramLevelDefault = QString(tr("低"));
        ComboBoxMotionDelegate *scramLevelDelegate = new ComboBoxMotionDelegate(scramLevelStr,scramLevelDefault,paraTable);
        paraTable->setItemDelegateForRow(47,scramLevelDelegate);

        QStringList slowStr = {"是","否"};
        QString slowDefault = QString(tr("否"));
        ComboBoxMotionDelegate *slowDelegate = new ComboBoxMotionDelegate(slowStr,slowDefault,paraTable);
        paraTable->setItemDelegateForRow(50,slowDelegate);

        QStringList slowLevelStr = {"高","低"};
        QString slowLevelDefault = QString(tr("低"));
        ComboBoxMotionDelegate *slowLevelDelegate = new ComboBoxMotionDelegate(slowLevelStr,slowLevelDefault,paraTable);
        paraTable->setItemDelegateForRow(51,slowLevelDelegate);
    }

    //按钮弹窗委托 20 25 26 40 44 48 52
    {
        // QString tempStr("通用输入:0,滤波:0s");
        // paraTable->setItem(20,0,new QTableWidgetItem(tempStr));

        InpuDialogMotionDelegate *inputDailogDelegate = new InpuDialogMotionDelegate(paraTable);
        paraTable->setItemDelegateForRow(20,inputDailogDelegate);
        paraTable->setItemDelegateForRow(25,inputDailogDelegate);
        paraTable->setItemDelegateForRow(26,inputDailogDelegate);
        paraTable->setItemDelegateForRow(40,inputDailogDelegate);
        paraTable->setItemDelegateForRow(44,inputDailogDelegate);
        paraTable->setItemDelegateForRow(48,inputDailogDelegate);
        paraTable->setItemDelegateForRow(52,inputDailogDelegate);
    }

    paraTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    paraTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    paraTableView->setItemDelegateForRow(41,slowDelegate);

    QStringList slowLevelStr = {"高","低"};
    QString slowLevelDefault = QString(tr("低"));
    ComboBoxMotionDelegate *slowLevelDelegate = new ComboBoxMotionDelegate(slowLevelStr,slowLevelDefault,paraTableView);
    paraTableView->setItemDelegateForRow(42,slowLevelDelegate);
}

void AxisSettingTab::uploadslot()
{
    qDebug()<<QString("AxisSettingTab::uploadslot()");
}

void AxisSettingTab::downloadSlot()
{
    qDebug()<<QString("AxisSettingTab::downloadSlot()");
    //_ConnectNo指定连接号的作用，以及什么时候发生变化？？？
    unsigned short _ConnectNo = 0;

    for (int i = 0; i < 6; ++i)
    {
        //基本设置
        BasicsParameter basic;
        //qDebug()<<basic.TdecStopTime;
        smc_get_pulse_outmode(_ConnectNo, i,  &basic.PulseModel);
        smc_get_equiv(_ConnectNo, i,  &basic.PulseEquiv);
        smc_get_profile_unit(_ConnectNo, i, &basic.Min_Vel, &basic.Max_Vel, &basic.Tacc, &basic.Tdec, &basic.Stop_Vel);//获取基础参数
        smc_get_s_profile(_ConnectNo, i, 0, &basic.S_para);
        smc_get_backlash_unit(_ConnectNo, i, &basic.Backlash);
        smc_get_dec_stop_time(_ConnectNo, i, &basic.TdecStopTime);
        //qDebug()<<basic.TdecStopTime;

        GoHomeParameter gohome;
        smc_get_home_profile_unit(_ConnectNo,i,&gohome.Low_Vel,&gohome.High_Vel,&gohome.Tacc,&gohome.Tdec);
        smc_get_homemode(_ConnectNo,i,&gohome.home_dir, &gohome.vel_mode,  &gohome.home_mode,  &gohome.pos_source);
        smc_get_home_pin_logic(_ConnectNo,i,&gohome.org_logic, &gohome.filter);
        smc_get_axis_io_map(_ConnectNo,i,gohome.SeifIOType,&gohome.MapIOType,&gohome.MapIOIndex,&gohome.Filter_time);
        smc_get_home_position_unit(_ConnectNo,i,&gohome.Enable,&gohome.Position);
        //qDebug()<<QString("axix=%1 pos_source=%2 home_dir=%3 ").arg(i).arg(gohome.pos_source).arg(gohome.home_dir);
        //qDebug()<<QString("gohome  type=%1 index=%2 Filter_time=%3").arg(gohome.MapIOType).arg(gohome.MapIOIndex).arg(gohome.Filter_time);

        HardLimitParameter harder;
        smc_get_el_mode(_ConnectNo, i, &harder.El_enable, &harder.El_logic, &harder.El_mode);
        smc_get_axis_io_map(_ConnectNo, i, harder.El_PlusSeifIOType, &harder.El_PlusMapIOType, &harder.El_PlusMapIOIndex, &harder.El_PlusFilter_time);
        smc_get_axis_io_map(_ConnectNo, i, harder.El_MinusSeifIOType, &harder.El_MinusMapIOType, &harder.El_MinusMapIOIndex, &harder.El_MinusFilter_time);
        //qDebug()<<QString("harder minus=%1 plus=%2").arg(harder.El_MinusSeifIOType).arg(harder.El_PlusMapIOType);

        SoftLimitParameter soft;
        smc_get_softlimit_unit(_ConnectNo, i, &soft.Enable, &soft.Source_sel, &soft.SL_action, &soft.N_limit, &soft.P_limit);

        CounterInParameter couter;
        //两个不需要显示的参数？？？
        unsigned short ez_mode = 0;
        double filter = 0;
        smc_get_counter_inmode(_ConnectNo, i, &couter.Model);
        smc_get_counter_reverse(_ConnectNo, i, &couter.Reverse);
        smc_get_ez_mode(_ConnectNo, i, &couter.Ez_logic,&ez_mode,&filter);

        //伺服报警和伺服到位？？？
        ServoAlarmParameter servo;
        smc_get_alm_mode(_ConnectNo, i, &servo.Enable, &servo.Alm_logic, &servo.Alm_action);
        smc_get_axis_io_map(_ConnectNo, i, servo.SeifIOType, &servo.MapIOType, &servo.MapIOIndex, &servo.Filter_time);

        EMGParameter emg;
        smc_get_emg_mode(_ConnectNo, i, &emg.Enable, &emg. Emg_logic);
        smc_get_axis_io_map(_ConnectNo, i, emg.SeifIOType, &emg.MapIOType, &emg.MapIOIndex, &emg.Filter_time);
        //qDebug()<<QString("emg SeifIOType=%1 MapIOType=%2").arg(emg.SeifIOType).arg(emg.MapIOType);

        DstpModelParameter dstp;
        smc_get_io_dstp_mode(_ConnectNo, i, &dstp.Enable, &dstp.Dstp_logic);
        smc_get_axis_io_map(_ConnectNo, i, dstp.SeifIOType, &dstp.MapIOType, &dstp.MapIOIndex, &dstp.Filter_time);
        //qDebug()<<QString("dstp SeifIOType=%1 MapIOType=%2").arg(dstp.SeifIOType).arg(dstp.MapIOType);

        paraTable->setItem(1,i,new QTableWidgetItem(plusMap[basic.PulseModel]));
        paraTable->setItem(2,i,new QTableWidgetItem(QString::number(basic.PulseEquiv)));
        paraTable->setItem(3,i,new QTableWidgetItem(QString::number(basic.Min_Vel)));
        paraTable->setItem(4,i,new QTableWidgetItem(QString::number(basic.Max_Vel)));
        paraTable->setItem(5,i,new QTableWidgetItem(QString::number(basic.Stop_Vel)));
        paraTable->setItem(6,i,new QTableWidgetItem(QString::number(basic.Tacc)));
        paraTable->setItem(7,i,new QTableWidgetItem(QString::number(basic.Tdec)));
        paraTable->setItem(8,i,new QTableWidgetItem(QString::number(basic.S_para)));
        paraTable->setItem(9,i,new QTableWidgetItem(QString::number(basic.Backlash)));
        paraTable->setItem(10,i,new QTableWidgetItem(QString::number(basic.TdecStopTime)));

        paraTable->setItem(12,i,new QTableWidgetItem(QString::number(gohome.Low_Vel)));
        paraTable->setItem(13,i,new QTableWidgetItem(QString::number(gohome.High_Vel)));
        paraTable->setItem(14,i,new QTableWidgetItem(QString::number(gohome.Tacc)));
        paraTable->setItem(15,i,new QTableWidgetItem(QString::number(gohome.Tdec)));
        //回零四个下拉框委托，一个弹窗
        paraTable->setItem(16,i,new QTableWidgetItem(homeModeMap[gohome.home_mode]));
        paraTable->setItem(17,i,new QTableWidgetItem(homeSourceMap[gohome.pos_source]));
        paraTable->setItem(18,i,new QTableWidgetItem(homeDirectMap[gohome.home_dir]));
        paraTable->setItem(19,i,new QTableWidgetItem(homeOrgLogicMap[gohome.org_logic]));
        QString tempStr = QString("%1:%2,滤波:%3s").arg(ioTypeMap[gohome.MapIOType],QString::number(gohome.MapIOIndex),QString::number(gohome.Filter_time));
        paraTable->setItem(20,i,new QTableWidgetItem(tempStr));
        //硬限位三个下拉框，两个弹窗 22-26
        paraTable->setItem(22,i,new QTableWidgetItem(hardElmodeMap[harder.El_enable]));
        paraTable->setItem(23,i,new QTableWidgetItem(hardStopModeMap[harder.El_mode]));
        paraTable->setItem(24,i,new QTableWidgetItem(hardOrgLogicMap[harder.El_logic]));
        //正限位和负限位的字段待确认！！！
        tempStr = QString("%1:%2,滤波:%3s").arg(ioTypeMap[harder.El_PlusMapIOType],QString::number(harder.El_PlusMapIOIndex),QString::number(harder.El_PlusFilter_time));
        paraTable->setItem(25,i,new QTableWidgetItem(tempStr));
        tempStr = QString("%1:%2,滤波:%3s").arg(ioTypeMap[harder.El_MinusMapIOType],QString::number(harder.El_MinusMapIOIndex),QString::number(harder.El_MinusFilter_time));
        paraTable->setItem(26,i,new QTableWidgetItem(tempStr));
        //软限位三个下拉框
        paraTable->setItem(28,i,new QTableWidgetItem(softElmodeMap[soft.Enable]));
        paraTable->setItem(29,i,new QTableWidgetItem(QString::number(soft.P_limit)));
        paraTable->setItem(30,i,new QTableWidgetItem(QString::number(soft.N_limit)));
        paraTable->setItem(31,i,new QTableWidgetItem(softStopModeMap[soft.SL_action]));
        paraTable->setItem(32,i,new QTableWidgetItem(softElmodeMap[soft.Source_sel]));
        //编码器三个下拉框委托 34-36
        paraTable->setItem(34,i,new QTableWidgetItem(counterModeMap[couter.Model]));
        paraTable->setItem(35,i,new QTableWidgetItem(softElmodeMap[couter.Reverse]));
        paraTable->setItem(36,i,new QTableWidgetItem(counterOrgLogicMap[couter.Ez_logic]));
        //伺服报警两国下拉框委托，一个弹窗 38-40
        paraTable->setItem(38,i,new QTableWidgetItem(softElmodeMap[servo.Enable]));
        paraTable->setItem(39,i,new QTableWidgetItem(counterOrgLogicMap[servo.Alm_logic]));
        tempStr = QString("%1:%2,滤波:%3s").arg(ioTypeMap[servo.MapIOType],QString::number(servo.MapIOIndex),QString::number(servo.Filter_time));
        paraTable->setItem(40,i,new QTableWidgetItem(tempStr));
        //伺服到位字段不明确 42-44

        //急停设置两个下拉框，一个弹窗   46-48
        //Map中没有急停,文本框里硬加上去，弹窗里的下拉框不选择
        paraTable->setItem(46,i,new QTableWidgetItem(softElmodeMap[emg.Enable]));
        paraTable->setItem(47,i,new QTableWidgetItem(counterOrgLogicMap[emg.Emg_logic]));
        tempStr = QString("%1:%2,滤波:%3s").arg(ioTypeMap[emg.MapIOType],QString::number(emg.MapIOIndex),QString::number(emg.Filter_time));
        paraTable->setItem(48,i,new QTableWidgetItem(tempStr));
        //减速停止设置两个下拉框，一个弹窗   50-52
        paraTable->setItem(50,i,new QTableWidgetItem(softElmodeMap[dstp.Enable]));
        paraTable->setItem(51,i,new QTableWidgetItem(counterOrgLogicMap[dstp.Dstp_logic]));
        tempStr = QString("%1:%2,滤波:%3s").arg(ioTypeMap[dstp.MapIOType],QString::number(dstp.MapIOIndex),QString::number(dstp.Filter_time));
        paraTable->setItem(52,i,new QTableWidgetItem(tempStr));
    }

}

void AxisSettingTab::importSlot()
{
    qDebug()<<QString("AxisSettingTab::importSlot()");
}

void AxisSettingTab::exportSlot()
{
    qDebug()<<QString("AxisSettingTab::exportSlot()");
    unsigned short _ConnectNo = 0;
    QMap<int,QVariantMap> axisConfigs;
    QString appPath = qApp->applicationDirPath();
    QString configFileName = QDir(appPath).filePath("config.ini");
    for (int i = 0; i < 6; ++i)
    {
        QVariantMap axis;

        //基本设置
        BasicsParameter basic;
        smc_get_pulse_outmode(_ConnectNo, i,  &basic.PulseModel);
        smc_get_equiv(_ConnectNo, i,  &basic.PulseEquiv);
        smc_get_profile_unit(_ConnectNo, i, &basic.Min_Vel, &basic.Max_Vel, &basic.Tacc, &basic.Tdec, &basic.Stop_Vel);//获取基础参数
        smc_get_s_profile(_ConnectNo, i, 0, &basic.S_para);
        smc_get_backlash_unit(_ConnectNo, i, &basic.Backlash);
        smc_get_dec_stop_time(_ConnectNo, i, &basic.TdecStopTime);

        GoHomeParameter gohome;
        smc_get_home_profile_unit(_ConnectNo,i,&gohome.Low_Vel,&gohome.High_Vel,&gohome.Tacc,&gohome.Tdec);
        smc_get_homemode(_ConnectNo,i,&gohome.home_dir, &gohome.vel_mode,  &gohome.home_mode,  &gohome.pos_source);
        smc_get_home_pin_logic(_ConnectNo,i,&gohome.org_logic, &gohome.filter);
        smc_get_axis_io_map(_ConnectNo,i,gohome.SeifIOType,&gohome.MapIOType,&gohome.MapIOIndex,&gohome.Filter_time);
        smc_get_home_position_unit(_ConnectNo,i,&gohome.Enable,&gohome.Position);

        HardLimitParameter harder;
        smc_get_el_mode(_ConnectNo, i, &harder.El_enable, &harder.El_logic, &harder.El_mode);
        smc_get_axis_io_map(_ConnectNo, i, harder.El_PlusSeifIOType, &harder.El_PlusMapIOType, &harder.El_PlusMapIOIndex, &harder.El_PlusFilter_time);
        smc_get_axis_io_map(_ConnectNo, i, harder.El_MinusSeifIOType, &harder.El_MinusMapIOType, &harder.El_MinusMapIOIndex, &harder.El_MinusFilter_time);

        SoftLimitParameter soft;
        smc_get_softlimit_unit(_ConnectNo, i, &soft.Enable, &soft.Source_sel, &soft.SL_action, &soft.N_limit, &soft.P_limit);

        CounterInParameter couter;
        unsigned short ez_mode = 0;
        double filter = 0;
        smc_get_counter_inmode(_ConnectNo, i, &couter.Model);
        smc_get_counter_reverse(_ConnectNo, i, &couter.Reverse);
        smc_get_ez_mode(_ConnectNo, i, &couter.Ez_logic,&ez_mode,&filter);

        //伺服报警和伺服到位？？？
        ServoAlarmParameter servo;
        smc_get_alm_mode(_ConnectNo, i, &servo.Enable, &servo.Alm_logic, &servo.Alm_action);
        smc_get_axis_io_map(_ConnectNo, i, servo.SeifIOType, &servo.MapIOType, &servo.MapIOIndex, &servo.Filter_time);

        EMGParameter emg;
        smc_get_emg_mode(_ConnectNo, i, &emg.Enable, &emg. Emg_logic);
        smc_get_axis_io_map(_ConnectNo, i, emg.SeifIOType, &emg.MapIOType, &emg.MapIOIndex, &emg.Filter_time);

        DstpModelParameter dstp;
        smc_get_io_dstp_mode(_ConnectNo, i, &dstp.Enable, &dstp.Dstp_logic);
        smc_get_axis_io_map(_ConnectNo, i, dstp.SeifIOType, &dstp.MapIOType, &dstp.MapIOIndex, &dstp.Filter_time);

        axis.insert("PulseMode",basic.PulseModel);
        axis.insert("PulseUnit",basic.PulseEquiv);
        axis.insert("BackLash",basic.Backlash);

        axisConfigs.insert(i,axis);
    }
    QSettings settings(configFileName,QSettings::IniFormat);
    for (auto it = axisConfigs.constBegin(); it != axisConfigs.constEnd(); ++it)
    {
        QString section = QString("ParaAxis%1").arg(it.key());

        // 设置当前段落
        settings.beginGroup(section);

        // 遍历该段落中的所有键值对并写入
        for (auto fieldIt = it.value().constBegin(); fieldIt != it.value().constEnd(); ++fieldIt)
        {
            settings.setValue(fieldIt.key(), fieldIt.value());
        }

        // 结束当前段落的写入
        settings.endGroup();
    }

}
