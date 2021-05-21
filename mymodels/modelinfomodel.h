#ifndef MODELINFOMODEL_H
#define MODELINFOMODEL_H

#include "modelutils/utils/dmodelutils.h"
#include <QStandardItemModel>
#include <QFileInfo>

class ModelInfoModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit ModelInfoModel(QObject *parent = nullptr);

signals:

public slots:
    void setSelectedFileInfo(const QFileInfo);
    void setSelectedModelInfo(const myMesh*);

};

#endif // MODELINFOMODEL_H
