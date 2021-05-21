#include "mainwindow.h"
#include "mywidgets/dialogs/dialogabout.h"
#include "mywidgets/docks/widgetcentre.h"
#include "mywidgets/docks/dockdirtreeview.h"
#include "mywidgets/docks/dockinfo.h"
#include "mymodels/modelinfomodel.h"
#include "mywidgets/docks/dockpreview.h"
#include <QObject>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /* 窗口属性 */
    setMinimumSize(750, 500);
//    setWindowState(Qt::WindowMaximized);
    setWindowIcon(QIcon("../DModelExplorer/icon/icon1.ico"));
    setWindowTitle("3D Model Explorer");

    /* 菜单栏 */
    QMenuBar *qmenubar = menuBar();
    setMenuBar(qmenubar);
    // 文件菜单
    QMenu *qmenu_file = qmenubar->addMenu("文件");
    QAction *qact_openFile = qmenu_file->addAction("打开...");
    connect(qact_openFile, &QAction::triggered, this, &MainWindow::createOpenFile);
    QMenu *qmenu_recentOpen = qmenu_file->addMenu("最近打开");
    qmenu_recentOpen->addSeparator();
    QAction *qact_clearRecentOpen = qmenu_recentOpen->addAction("清除");
    qmenu_file->addSeparator();
    QAction *qact_quit = qmenu_file->addAction("退出");
    connect(qact_quit, &QAction::triggered, this, &MainWindow::closeWindow);
    // 帮助菜单
    QMenu *qmenu_help = qmenubar->addMenu("帮助");
    QAction *qact_about = qmenu_help->addAction("关于");
    connect(qact_about, &QAction::triggered, this, &MainWindow::createAbout);

    /* 工具栏 */
    QToolBar *qToolBar = addToolBar("tool_bar");
    QPushButton *qpb_openFile = new QPushButton(this);
    qpb_openFile->setText("打开");
    qToolBar->addWidget(qpb_openFile);
    connect(qpb_openFile, &QPushButton::clicked, this, &MainWindow::createOpenFile);
    QPushButton *qpb_openTempPath = new QPushButton(this);
    qpb_openTempPath->setText("打开临时路径");
    qToolBar->addWidget(qpb_openTempPath);
    connect(qpb_openTempPath, &QPushButton::clicked, this, &MainWindow::openTempPath);

    /* 状态栏 */
    QStatusBar *qStatusBar = statusBar();
    QLabel *qlb_status = new QLabel(this);
    qlb_status->setText("正常");
    qStatusBar->addWidget(qlb_status);
    QLabel *qlb_loading = new QLabel(this);
    qlb_loading->setText("加载中...");
    qStatusBar->addPermanentWidget(qlb_loading);

    /* 核心浏览区 */
    WidgetCentre *widgetCentre = new WidgetCentre(this);
    setCentralWidget(widgetCentre);

    /* 浮动窗口 */
    // 路径层次树
    QDockWidget *qdw_dirTree = new QDockWidget(this);
    DockDirTreeView *dockDirTreeView = new DockDirTreeView(this);
    qdw_dirTree->setWindowTitle("文件夹");
    qdw_dirTree->setWidget(dockDirTreeView);
    addDockWidget(Qt::LeftDockWidgetArea, qdw_dirTree);
    // 信息
    QDockWidget *qdw_info = new QDockWidget(this);
    DockInfo *dockInfo = new DockInfo(qdw_info);
    qdw_info->setWindowTitle("信息");
    qdw_info->setWidget(dockInfo);
    addDockWidget(Qt::BottomDockWidgetArea, qdw_info);
    // 预览
    QDockWidget *qdw_preview = new QDockWidget(this);
    DockPreview *dockPreview = new DockPreview(qdw_preview);
    qdw_preview->setWindowTitle("预览");
    qdw_preview->setWidget(dockPreview);
    addDockWidget(Qt::BottomDockWidgetArea, qdw_preview);

    /* 实例化基本文件Model */
    baseFileModel = new QFileSystemModel(this);
    baseFileModel->setFilter(QDir::AllEntries | QDir::NoDot);
    baseFileModel->setRootPath(QDir::currentPath());

    /* 信号与槽 */
    QObject::connect(dockDirTreeView, &DockDirTreeView::emitSelectedDir, widgetCentre, &WidgetCentre::setSelectedPath);
    QObject::connect(widgetCentre, &WidgetCentre::emitAccessDir, dockDirTreeView, &DockDirTreeView::expandDir);
    QObject::connect(widgetCentre, &WidgetCentre::emitSelectedFile, dockPreview, &DockPreview::setSelectedFile);
    QObject::connect(widgetCentre, &WidgetCentre::emitSelectedFile, dockInfo->getInfoModel(), &ModelInfoModel::setSelectedFileInfo);
    QObject::connect(dockPreview->getScene_opengl(), &SceneOpenGLContainer::emitModelInfo, dockInfo->getInfoModel(), &ModelInfoModel::setSelectedModelInfo);
    emit baseFileModelConstructed(baseFileModel);
}

MainWindow::~MainWindow(){
}

/* private */
// 关闭窗口
void MainWindow::closeWindow(){
    close();
}

// 创建“打开文件”窗口
void MainWindow::createOpenFile(){
    QString path = QFileDialog::getOpenFileName(this, "打开文件", ".", "3D Model Files(*.off)");
    if(!path.isEmpty()){
        qDebug()<<path;
    }else{
        QMessageBox::warning(this, "选择文件", "未选择任何文件！");
    }
}

// 创建“关于”窗口
void MainWindow::createAbout(){
    DialogAbout *dialogabout = new DialogAbout(this);
    dialogabout->show();
}

// 使用系统资源管理器打开临时路径
void MainWindow::openTempPath(){
    QString local_path = QDir::tempPath() + "/3DModelExlorerTmp/";
    QString path = QString("file:///") + local_path;
    QDesktopServices::openUrl(QUrl(path, QUrl::TolerantMode));
}
