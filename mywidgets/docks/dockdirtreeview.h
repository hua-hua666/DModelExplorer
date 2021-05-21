#ifndef DOCKDIRTREEVIEW_H
#define DOCKDIRTREEVIEW_H

#include "mymodels/mydirsystemmodel.h"
#include "mywidgets/mainwindow.h"
#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>

class DockDirTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit DockDirTreeView(QWidget *parent = nullptr);

private:
    MyDirSystemModel *dir_model;
    void selectedDir(const QModelIndex &index);

signals:
    void emitSelectedDir(const QModelIndex &sourceIndex);

public slots:
    void expandDir(const QModelIndex &index);

private slots:
    void adjustTreeView();
};

#endif // DOCKDIRTREEVIEW_H
