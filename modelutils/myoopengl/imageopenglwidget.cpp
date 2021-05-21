#include "imageopenglwidget.h"
#include <QPixmap>
#include <QDebug>
#include <QDir>

ImageOpenGLWidget::ImageOpenGLWidget(QWidget *parent, QString meshFileName, QString fullMD5Name) : BaseOpenGLWidget(parent){
    if(meshFileName.length() == 0)
        return;
    setSelectedFile(QFileInfo(meshFileName));
    setIsDrawFaces(true);
//    resizeGL(300, 300);
    generateImage(fullMD5Name);
}

void ImageOpenGLWidget::setSelectedFile(QFileInfo qfi_selectedFile){
    QString str_suffix = qfi_selectedFile.suffix();
    if(QString::compare(str_suffix, "obj", Qt::CaseInsensitive) == 0){
        setMesh(DModelUtils::readObjFile(qfi_selectedFile.absoluteFilePath()));
    }else if(QString::compare(str_suffix, "off", Qt::CaseInsensitive) == 0){
        setMesh(DModelUtils::readOffFile(qfi_selectedFile.absoluteFilePath()));
    }else if(QString::compare(str_suffix, "stl", Qt::CaseInsensitive) == 0){
        setMesh(DModelUtils::readStlFile(qfi_selectedFile.absoluteFilePath()));
    }else{
        return;
    }
}

void ImageOpenGLWidget::generateImage(QString fullMD5Name){
    QPixmap pixmap = QWidget::grab();
    pixmap.save(fullMD5Name, "bmp");
}
