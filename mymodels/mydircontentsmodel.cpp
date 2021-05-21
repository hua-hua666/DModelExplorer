#include "mydircontentsmodel.h"
#include "modelutils/myoopengl/imageopenglwidget.h"
#include <QDebug>
#include <QFileInfo>
#include <QCryptographicHash>

MyDirContentsModel::MyDirContentsModel(QWidget *parent) : QSortFilterProxyModel(parent){
    // 存放
    tmpDir = QDir::tempPath() + "/3DModelExlorerTmp/";
    QFileInfo fi(tmpDir);
//    qDebug() << QDir::tempPath();
    if (! fi.isDir()){
        QDir folder = QDir();
        folder.mkdir(tmpDir);
    }
}

/* protected */
// 【重写】设定Data
QVariant MyDirContentsModel::data(const QModelIndex &index, int role = Qt::DisplayRole) const{
    if(role == QFileSystemModel::FileIconRole){
        QFileInfo qfi_selectedFile = static_cast<QFileSystemModel*>(sourceModel())->fileInfo(mapToSource(index));
        QString str_suffix = qfi_selectedFile.suffix();
        if(QString::compare(str_suffix, "obj", Qt::CaseInsensitive) == 0
                || QString::compare(str_suffix, "off", Qt::CaseInsensitive) == 0
                || QString::compare(str_suffix, "stl", Qt::CaseInsensitive) == 0){
//            qDebug() << qfi_selectedFile.absoluteFilePath();
            QFile theFile(qfi_selectedFile.absoluteFilePath());
            theFile.open(QIODevice::ReadOnly);
            QByteArray ba = QCryptographicHash::hash(theFile.readAll(), QCryptographicHash::Md5);
            theFile.close();
            QString fullMD5Name = tmpDir + ba.toHex().constData() + ".bmp";
            QFileInfo fi(fullMD5Name);
            if (! fi.isFile()){
                ImageOpenGLWidget iow_image(nullptr, qfi_selectedFile.absoluteFilePath(), fullMD5Name);
            }
//            return QIcon("../DModelExplorer/icon/icon1.ico");
            return QIcon(fullMD5Name);
        }
    }
    return QSortFilterProxyModel::data(index, role);
}

// 【重写】设定文件排序规则：文件夹在前，剩余按照本地语言规则依据文件名先后排序
bool MyDirContentsModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const{
    QFileInfo qfi_left = static_cast<QFileSystemModel*>(sourceModel())->fileInfo(source_left);
    QFileInfo qfi_Right = static_cast<QFileSystemModel*>(sourceModel())->fileInfo(source_right);
    bool isDirLeft = qfi_left.isDir();
    bool isDirRight = qfi_Right.isDir();
    QString fileNameLeft = qfi_left.fileName();
    QString fileNameRight = qfi_Right.fileName();
    if(isDirLeft){
        if(isDirRight){
            return QString::localeAwareCompare(fileNameLeft, fileNameRight) < 0;
        }else{
            return true;
        }
    }else{
        if(isDirRight){
            return false;
        }else{
            return QString::localeAwareCompare(fileNameLeft, fileNameRight) < 0;
        }
    }
}

/* public slots */
// 接收MainWindow::baseFileModelConstructed信号，为自定义文件夹内容MyDirContentsModel设置文件系统QFileSystemModel
void MyDirContentsModel::setBaseModel(QFileSystemModel *baseFileModel){
    setSourceModel(baseFileModel);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setSortLocaleAware(true);
    sort(0);
}
