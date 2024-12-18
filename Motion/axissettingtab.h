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

signals:

private:
    QTableView *paraTableView;
    QStandardItemModel *paraModel;

    QTableWidget *paraTable;
};

#endif // AXISSETTINGTAB_H
