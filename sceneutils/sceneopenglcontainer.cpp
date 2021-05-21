#include "sceneopenglcontainer.h"
#include "sceneopenglwidget.h"
#include <QOpenGLWidget>
#include <QDebug>

SceneOpenGLContainer::SceneOpenGLContainer(QObject *parent) : SceneAbstractContainer(parent){
    container = new SceneOpenGLWidget();
}

SceneOpenGLContainer::~SceneOpenGLContainer(){
    delete container;
}

/* public */
// 【重写】设置选中文件，以供渲染
void SceneOpenGLContainer::setSelectedFile(QFileInfo qfi_selectedFile){
    QString str_suffix = qfi_selectedFile.suffix();
    SceneOpenGLWidget* sceneOpenGLWidget;
    if(QString::compare(str_suffix, "obj", Qt::CaseInsensitive) == 0){
        sceneOpenGLWidget = static_cast<SceneOpenGLWidget*>(container);
        sceneOpenGLWidget->setMesh(DModelUtils::readObjFile(qfi_selectedFile.absoluteFilePath()));
    }else if(QString::compare(str_suffix, "off", Qt::CaseInsensitive) == 0){
        sceneOpenGLWidget = static_cast<SceneOpenGLWidget*>(container);
        sceneOpenGLWidget->setMesh(DModelUtils::readOffFile(qfi_selectedFile.absoluteFilePath()));
    }else if(QString::compare(str_suffix, "stl", Qt::CaseInsensitive) == 0){
        sceneOpenGLWidget = static_cast<SceneOpenGLWidget*>(container);
        sceneOpenGLWidget->setMesh(DModelUtils::readStlFile(qfi_selectedFile.absoluteFilePath()));
    }else{
        return;
    }
    emit emitModelInfo(sceneOpenGLWidget->getMesh());
}

/* public slots */
void SceneOpenGLContainer::modeIsPointsChanged(int state){
    static_cast<SceneOpenGLWidget*>(container)->setIsDrawPoints(state);
}

void SceneOpenGLContainer::modeIsLinesChanged(int state){
    static_cast<SceneOpenGLWidget*>(container)->setIsDrawLines(state);
}

void SceneOpenGLContainer::modeIsFacesChanged(int state){
    static_cast<SceneOpenGLWidget*>(container)->setIsDrawFaces(state);
}

void SceneOpenGLContainer::clearArgs(){
    static_cast<SceneOpenGLWidget*>(container)->clearArgs();
}
