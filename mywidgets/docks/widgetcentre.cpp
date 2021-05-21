#include "widgetcentre.h"
#include "mywidgets/mainwindow.h"
#include <QDebug>

WidgetCentre::WidgetCentre(QWidget *parent) : QWidget(parent){
    grid_layout = new QGridLayout(this);
    grid_layout->setSpacing(5);
    grid_layout->setContentsMargins(0, 0, 3, 0);

    qle_curpath = new QLineEdit(this);
    grid_layout->addWidget(qle_curpath, 0, 0, 1, 1);

    myDelegate = new ThumbnailUnitDelegate(this);
    qlv_main = new QListView(this);
    qlv_main->setItemDelegate(myDelegate);
    qlv_main->setViewMode(QListView::IconMode);
    qlv_main->setIconSize(QSize(128, 128));
    qlv_main->setSelectionMode(QAbstractItemView::ExtendedSelection);
    qlv_main->setFlow(QListView::LeftToRight);
    qlv_main->setGridSize(QSize(150, 200));
    qlv_main->setMovement(QListView::Static);
    qlv_main->setResizeMode(QListView::Adjust);
    qlv_main->setSelectionRectVisible(true);
    qlv_main->setWordWrap(true);
    grid_layout->addWidget(qlv_main, 1, 0, -1, -1);

    file_model = new MyDirContentsModel(this);
    qlv_main->setModel(file_model);

    QObject::connect(static_cast<MainWindow *>(parent), &MainWindow::baseFileModelConstructed, file_model, &MyDirContentsModel::setBaseModel);
    QObject::connect(qlv_main, &QAbstractItemView::clicked, this, &WidgetCentre::selectedFile);
    QObject::connect(qlv_main, &QAbstractItemView::doubleClicked, this, &WidgetCentre::accessDir);
}

/* public slots */
// 接收DockDirTreeView::emitSelectedDir信号，设置主文件浏览区当前文件夹路径
void WidgetCentre::setSelectedPath(const QModelIndex &sourceIndex){
    qlv_main->setRootIndex(file_model->mapFromSource(sourceIndex));
}

/* private slots */
// 接收QAbstractItemView::clicked信号，选中文件，从Base Model取出QFileInfo，准备渲染预览
void WidgetCentre::selectedFile(const QModelIndex &index){
    QFileInfo qfi_selectedFile = static_cast<QFileSystemModel*>(file_model->sourceModel())->fileInfo(file_model->mapToSource(index));
    emit emitSelectedFile(qfi_selectedFile);
}

// 接收QAbstractItemView::doubleClicked信号，选中文件夹，进入文件夹
void WidgetCentre::accessDir(const QModelIndex &index){
    QFileInfo qfi_selectedFile = static_cast<QFileSystemModel*>(file_model->sourceModel())->fileInfo(file_model->mapToSource(index));
    if(qfi_selectedFile.isDir()){
        qlv_main->setRootIndex(index);
        emit emitAccessDir(file_model->mapToSource(index));
    }
}
