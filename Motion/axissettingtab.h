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

    //加载虚拟数据,待修改后删除
    void loadMockData();

signals:

private:
    QTableView *paraTableView;
    QStandardItemModel *paraModel;
};

#endif // AXISSETTINGTAB_H
