#ifndef DOCKINFO_H
#define DOCKINFO_H

#include "mymodels/modelinfomodel.h"
#include <QWidget>
#include <QTreeView>

class DockInfo : public QTreeView
{
    Q_OBJECT
public:
    explicit DockInfo(QWidget *parent = nullptr);
    ModelInfoModel *getInfoModel() const;

private:
    QSize sizeHint() const Q_DECL_OVERRIDE;
    ModelInfoModel *infoModel;

signals:

};

#endif // DOCKINFO_H
