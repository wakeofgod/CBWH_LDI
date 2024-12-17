#include "runinsettingtab.h"

RuninSettingTab::RuninSettingTab(QWidget *parent)
    : QWidget{parent}
{
    initView();
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(runinTableView,0,0);
    setLayout(mainLayout);
}

void RuninSettingTab::initView()
{
    runinTableView = new QTableView();
    runinModel = new QStandardItemModel();

    runinModel->setHorizontalHeaderItem(0,new QStandardItem(""));
    runinModel->setHorizontalHeaderItem(1,new QStandardItem("坐标系0"));
    runinModel->setHorizontalHeaderItem(2,new QStandardItem("坐标系1"));

    QStringList customLabels;
    customLabels <<"起始速度"
                 <<"插补速度"
                 <<"终止速度(unit/s)"
                 <<"加速时间"
                 <<"减速时间"
                 <<"S段时间";
    runinModel->setVerticalHeaderLabels(customLabels);

    runinTableView->setModel(runinModel);
    runinTableView->setSortingEnabled(false);
    runinTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    runinTableView->setShowGrid(true);
    runinTableView->setColumnHidden(0,true);
    runinTableView->setAlternatingRowColors(true);
    runinTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    runinTableView->horizontalHeader()->setHighlightSections(true);
}
