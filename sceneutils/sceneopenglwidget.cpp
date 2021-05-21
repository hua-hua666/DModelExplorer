#include "sceneopenglwidget.h"
#include <math.h>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>

SceneOpenGLWidget::SceneOpenGLWidget(QWidget *parent) : BaseOpenGLWidget(parent){

}

void SceneOpenGLWidget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton ||
            event->button() == Qt::RightButton ||
            event->button() == Qt::MiddleButton){
        prePos = event->pos();
    }
}

void SceneOpenGLWidget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        rotation[0] += 0.5 * ((event->pos() - prePos).y());
        rotation[1] += 0.5 * ((event->pos() - prePos).x());
    }else if(event->buttons() == Qt::RightButton){
        translation[0] += 2.0 * (float)((event->pos() - prePos).x()) / (float)width();
        translation[1] -= 2.0 * (float)((event->pos() - prePos).y()) / (float)height();
    }else if(event->buttons() == Qt::MiddleButton){
        scale *= exp(2.0 * (float)((event->pos() - prePos).x()) / (float)width());
    }
    prePos = event->pos();
    update();
}

void SceneOpenGLWidget::wheelEvent(QWheelEvent *event){
    scale *= exp(event->angleDelta().y() / 480.0);
    update();
}
