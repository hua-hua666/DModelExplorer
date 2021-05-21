#ifndef IMAGEOPENGLWIDGET_H
#define IMAGEOPENGLWIDGET_H

#include "baseopenglwidget.h"
#include <QWidget>
#include <QFileInfo>

class ImageOpenGLWidget : public BaseOpenGLWidget
{
    Q_OBJECT
public:
    explicit ImageOpenGLWidget(QWidget *parent = nullptr, QString meshFileName = "", QString fullMD5Name = "");
    void setSelectedFile(QFileInfo qfi_selectedFile);
    void generateImage(QString fullMD5Name);

signals:

};

#endif // IMAGEOPENGLWIDGET_H
