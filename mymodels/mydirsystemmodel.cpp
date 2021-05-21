#include "mydirsystemmodel.h"
#include "mywidgets/mainwindow.h"
#include <QDebug>
#include <QFlags>
#include <QModelIndex>

MyDirSystemModel::MyDirSystemModel(QWidget *parent) : QSortFilterProxyModel(parent){

}

/* protected */
// 【重写】设定过滤规则，只选取文件夹或驱动器
bool MyDirSystemModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const{
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex index2 = sourceModel()->index(sourceRow, 2, sourceParent);

    return ((sourceModel()->data(index2).toString()=="File Folder")
          || (sourceModel()->data(index2).toString()=="Drive"))
          && (sourceModel()->data(index0).toString()!="..");
}

/* public slots */
// 接收MainWindow::baseFileModelConstructed信号，为自定义文件夹系统MyDirSystemModel设置文件系统QFileSystemModel
void MyDirSystemModel::setBaseModel(QFileSystemModel *baseFileModel){
    setSourceModel(baseFileModel);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setSortLocaleAware(true);
    sort(0);

//    qDebug()<<baseFileModel->index("C:/Intel").parent();
//    qDebug()<<baseFileModel->index("D:").parent();
//    qDebug()<<baseFileModel->rowCount();
}
