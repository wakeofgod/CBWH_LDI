#ifndef AXISSETTINGTAB_H
#define AXISSETTINGTAB_H

#include <QWidget>
#include <QtWidgets>
#include <QHeaderView>

class AxisSettingTab : public QWidget
{
    Q_OBJECT
public:
    explicit AxisSettingTab(QWidget *parent = nullptr);

    void initView();

    //要添加合并单元格，分段，该用qtablewidget
    void initTable();

    //加载虚拟数据,待修改后删除
    void loadMockData();

    int findMapKey(const QString &target,const QMap<int,QString> &map);

    void splitStringList(unsigned short &ioType,unsigned short &ioIndex,double &filterTime,QString &str);
signals:

public slots:
    void uploadslot();
    void downloadSlot();
    void importSlot();
    void exportSlot();

private:
    QTableView *paraTableView;
    QStandardItemModel *paraModel;

    QTableWidget *paraTable;
};

#endif // AXISSETTINGTAB_H
