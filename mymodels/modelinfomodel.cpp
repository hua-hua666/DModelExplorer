#include "modelinfomodel.h"
#include <QDateTime>
#include <QDebug>

ModelInfoModel::ModelInfoModel(QObject *parent) : QStandardItemModel(parent){
    setHorizontalHeaderLabels(QStringList()<<QStringLiteral("属性名")<<QStringLiteral("值"));
    setItem(0, 0, new QStandardItem("文件"));
    item(0)->setChild(0, 0, new QStandardItem("文件名"));
    item(0)->setChild(0, 1, new QStandardItem(""));
    item(0)->setChild(1, 0, new QStandardItem("文件路径"));
    item(0)->setChild(1, 1, new QStandardItem(""));
    item(0)->setChild(2, 0, new QStandardItem("描述"));
    item(0)->setChild(2, 1, new QStandardItem(""));
    item(0)->setChild(3, 0, new QStandardItem("文件尺寸"));
    item(0)->setChild(3, 1, new QStandardItem(""));
    item(0)->setChild(4, 0, new QStandardItem("创建日期"));
    item(0)->setChild(4, 1, new QStandardItem(""));
    item(0)->setChild(5, 0, new QStandardItem("修改日期"));
    item(0)->setChild(5, 1, new QStandardItem(""));
    item(0)->setChild(6, 0, new QStandardItem("访问日期"));
    item(0)->setChild(6, 1, new QStandardItem(""));
    setItem(1, 0, new QStandardItem("模型"));
    item(1)->setChild(0, 0, new QStandardItem("点线面"));
    item(1)->setChild(0, 1, new QStandardItem(""));
    item(1)->child(0)->setChild(0, 0, new QStandardItem("点数量"));
    item(1)->child(0)->setChild(0, 1, new QStandardItem(""));
    item(1)->child(0)->setChild(1, 0, new QStandardItem("线数量"));
    item(1)->child(0)->setChild(1, 1, new QStandardItem(""));
    item(1)->child(0)->setChild(2, 0, new QStandardItem("面数量"));
    item(1)->child(0)->setChild(2, 1, new QStandardItem(""));
    item(1)->setChild(1, 0, new QStandardItem("包围盒"));
    item(1)->setChild(1, 1, new QStandardItem(""));
    item(1)->child(1)->setChild(0, 0, new QStandardItem("上盒面位置"));
    item(1)->child(1)->setChild(0, 1, new QStandardItem(""));
    item(1)->child(1)->setChild(1, 0, new QStandardItem("下盒面位置"));
    item(1)->child(1)->setChild(1, 1, new QStandardItem(""));
    item(1)->child(1)->setChild(2, 0, new QStandardItem("左盒面位置"));
    item(1)->child(1)->setChild(2, 1, new QStandardItem(""));
    item(1)->child(1)->setChild(3, 0, new QStandardItem("右盒面位置"));
    item(1)->child(1)->setChild(3, 1, new QStandardItem(""));
    item(1)->child(1)->setChild(4, 0, new QStandardItem("前盒面位置"));
    item(1)->child(1)->setChild(4, 1, new QStandardItem(""));
    item(1)->child(1)->setChild(5, 0, new QStandardItem("后盒面位置"));
    item(1)->child(1)->setChild(5, 1, new QStandardItem(""));
    item(1)->child(1)->setChild(6, 0, new QStandardItem("包围盒中心"));
    item(1)->child(1)->setChild(6, 1, new QStandardItem(""));
    item(1)->setChild(2, 0, new QStandardItem("模型尺寸"));
    item(1)->setChild(2, 1, new QStandardItem(""));
    item(1)->child(2)->setChild(0, 0, new QStandardItem("包围盒长"));
    item(1)->child(2)->setChild(0, 1, new QStandardItem(""));
    item(1)->child(2)->setChild(1, 0, new QStandardItem("包围盒宽"));
    item(1)->child(2)->setChild(1, 1, new QStandardItem(""));
    item(1)->child(2)->setChild(2, 0, new QStandardItem("包围盒高"));
    item(1)->child(2)->setChild(2, 1, new QStandardItem(""));
    item(1)->setChild(3, 0, new QStandardItem("初始参数"));
    item(1)->setChild(3, 1, new QStandardItem(""));
    item(1)->child(3)->setChild(0, 0, new QStandardItem("缩放系数"));
    item(1)->child(3)->setChild(0, 1, new QStandardItem(""));
}

void ModelInfoModel::setSelectedFileInfo(const QFileInfo qfi_selectedFile){
    item(0)->child(0, 1)->setData(qfi_selectedFile.fileName(), Qt::DisplayRole);
    item(0)->child(1, 1)->setData(qfi_selectedFile.absolutePath(), Qt::DisplayRole);
    item(0)->child(2, 1)->setData(qfi_selectedFile.suffix() + " 文件", Qt::DisplayRole);
    item(0)->child(3, 1)->setData(qfi_selectedFile.size(), Qt::DisplayRole);
    item(0)->child(4, 1)->setData(qfi_selectedFile.birthTime().toString("yyyy-MM-dd hh:mm:ss:z"), Qt::DisplayRole);
    item(0)->child(5, 1)->setData(qfi_selectedFile.lastModified().toString("yyyy-MM-dd hh:mm:ss:z"), Qt::DisplayRole);
    item(0)->child(6, 1)->setData(qfi_selectedFile.lastRead().toString("yyyy-MM-dd hh:mm:ss:z"), Qt::DisplayRole);
}

void ModelInfoModel::setSelectedModelInfo(const myMesh* mesh){
    item(1)->child(0)->child(0, 1)->setData(mesh->vert_number, Qt::DisplayRole);
    item(1)->child(0)->child(1, 1)->setData(0, Qt::DisplayRole);
    item(1)->child(0)->child(2, 1)->setData(mesh->original_face_number, Qt::DisplayRole);
    item(1)->child(1)->child(0, 1)->setData(mesh->bounding_box.zMax, Qt::DisplayRole);
    item(1)->child(1)->child(1, 1)->setData(mesh->bounding_box.zMin, Qt::DisplayRole);
    item(1)->child(1)->child(2, 1)->setData(mesh->bounding_box.yMin, Qt::DisplayRole);
    item(1)->child(1)->child(3, 1)->setData(mesh->bounding_box.yMax, Qt::DisplayRole);
    item(1)->child(1)->child(4, 1)->setData(mesh->bounding_box.xMax, Qt::DisplayRole);
    item(1)->child(1)->child(5, 1)->setData(mesh->bounding_box.xMin, Qt::DisplayRole);
    item(1)->child(1)->child(6, 1)->setData(QString("(%1, %2, %3)").arg(mesh->bounding_box.centre.x).arg(mesh->bounding_box.centre.y).arg(mesh->bounding_box.centre.z), Qt::DisplayRole);
    item(1)->child(2)->child(0, 1)->setData(mesh->bounding_box.dx, Qt::DisplayRole);
    item(1)->child(2)->child(1, 1)->setData(mesh->bounding_box.dy, Qt::DisplayRole);
    item(1)->child(2)->child(2, 1)->setData(mesh->bounding_box.dz, Qt::DisplayRole);
    item(1)->child(3)->child(0, 1)->setData(mesh->bounding_box.scale, Qt::DisplayRole);
}

