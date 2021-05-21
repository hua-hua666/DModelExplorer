#include "dockdirtreeview.h"
#include "mywidgets/mainwindow.h"
#include <QCoreApplication>
#include <QDebug>
#include <QFileSystemModel>

DockDirTreeView::DockDirTreeView(QWidget *parent) : QTreeView(parent){
    // 定义并绑定文件夹结构model
    dir_model = new MyDirSystemModel(this);
    setModel(dir_model);

    // 设置DirTreeView属性
    setHeaderHidden(true);
    setAnimated(true);
    setRootIsDecorated(false);
    setUniformRowHeights(true);

    // 信号与槽
    QObject::connect(this, &DockDirTreeView::clicked, this, &DockDirTreeView::selectedDir);
    QObject::connect(static_cast<MainWindow *>(parent), &MainWindow::baseFileModelConstructed, dir_model, &MyDirSystemModel::setBaseModel);
    QObject::connect(static_cast<MainWindow *>(parent), &MainWindow::baseFileModelConstructed, this, &DockDirTreeView::adjustTreeView);
}

/* private */
// TreeView MyDirSystemModel(QSortFilterProxyModel) 转换为 Source QFileSystemModel
void DockDirTreeView::selectedDir(const QModelIndex &index){
    // 发送至WidgetCentre::setSelectedPath
    emit emitSelectedDir(dir_model->mapToSource(index));
}

/* public slots */
// 接收WidgetCentre::emitAccessDir信号，展开树中文件夹
void DockDirTreeView::expandDir(const QModelIndex& index){
    setCurrentIndex(dir_model->mapFromSource(index));
    setExpanded(dir_model->mapFromSource(index), true);
}

/* private slots */
// 接收MainWindow::baseFileModelConstructed信号，QFileSystemModel实例化后调整文件夹树
void DockDirTreeView::adjustTreeView(){
    setColumnHidden(1, true);
    setColumnHidden(2, true);
    setColumnHidden(3, true);
    resizeColumnToContents(0);
}
