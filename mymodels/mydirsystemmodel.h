#ifndef MYDIRSYSTEMMODEL_H
#define MYDIRSYSTEMMODEL_H

#include <QWidget>
#include <QSortFilterProxyModel>
#include <QFileSystemModel>

class MyDirSystemModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit MyDirSystemModel(QWidget *parent = nullptr);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;

signals:

public slots:
    void setBaseModel(QFileSystemModel*);
};

#endif // MYDIRSYSTEMMODEL_H
