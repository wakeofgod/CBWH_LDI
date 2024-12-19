#ifndef RUNINSETTINGTAB_H
#define RUNINSETTINGTAB_H

#include <QWidget>
#include <QtWidgets>

class RuninSettingTab : public QWidget
{
    Q_OBJECT
public:
    explicit RuninSettingTab(QWidget *parent = nullptr);

    void initView();
signals:

private:
    QTableView *runinTableView;
    QStandardItemModel *runinModel;
};

#endif // RUNINSETTINGTAB_H
