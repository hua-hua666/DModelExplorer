#ifndef MYDIRCONTENTSMODEL_H
#define MYDIRCONTENTSMODEL_H

#include <QWidget>
#include <QSortFilterProxyModel>
#include <QFileSystemModel>

class MyDirContentsModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit MyDirContentsModel(QWidget *parent = nullptr);

protected:
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const Q_DECL_OVERRIDE;

private:
    QString tmpDir;

signals:

public slots:
    void setBaseModel(QFileSystemModel *baseFileModel);
};

#endif // MYDIRCONTENTSMODEL_H
