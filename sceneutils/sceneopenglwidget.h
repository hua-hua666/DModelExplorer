#ifndef SCENEOPENGLWIDGET_H
#define SCENEOPENGLWIDGET_H

#include "modelutils/myoopengl/baseopenglwidget.h"
#include <QWidget>

class SceneOpenGLWidget : public BaseOpenGLWidget
{
    Q_OBJECT
public:
    explicit SceneOpenGLWidget(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

private:
    QPoint prePos;

signals:

};

#endif // SCENEOPENGLWIDGET_H
