#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include "mymodels/mydircontentsmodel.h"
#include "viewutils/thumbnailunitdelegate.h"
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QListView>
#include <QFileSystemModel>

class WidgetCentre : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetCentre(QWidget *parent = nullptr);

private:
    QGridLayout *grid_layout;
    QLineEdit *qle_curpath;
    QListView *qlv_main;
    ThumbnailUnitDelegate *myDelegate;
    MyDirContentsModel *file_model;

signals:
    void emitSelectedFile(const QFileInfo qfi_selectedFile);
    void emitAccessDir(const QModelIndex &index);

public slots:
    void setSelectedPath(const QModelIndex &sourceIndex);

private slots:
    void selectedFile(const QModelIndex &index);
    void accessDir(const QModelIndex &index);
};

#endif // CENTRALWIDGET_H
