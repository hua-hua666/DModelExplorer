#include "dockinfo.h"

DockInfo::DockInfo(QWidget *parent) : QTreeView(parent){
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setAlternatingRowColors(true);
    setAllColumnsShowFocus(true);
    setAnimated(true);
    setExpandsOnDoubleClick(true);
    setIndentation(18);
    infoModel = new ModelInfoModel(this);
    setModel(infoModel);
    expandAll();
    resizeColumnToContents(0);
}

ModelInfoModel *DockInfo::getInfoModel() const{
    return infoModel;
}

/* private */
// 调整初始大小
QSize DockInfo::sizeHint() const{
    return QSize(0, 350);
}

