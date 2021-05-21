#ifndef BASEOPENGLWIDGET_H
#define BASEOPENGLWIDGET_H

#include "modelutils/utils/dmodelutils.h"
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class BaseOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit BaseOpenGLWidget(QWidget *parent = nullptr);
    void setMesh(myMesh *value);
    myMesh *getMesh() const;
    void setIsDrawPoints(bool value);
    void setIsDrawLines(bool value);
    void setIsDrawFaces(bool value);
    void clearArgs();

protected:
    myMesh* mesh = nullptr;

    float scale = 1.0;
    float center[3] = { 0.0, 0.0, 0.0 };
    float rotation[3] = { 0.0, 0.0, 0.0 };
    float translation[3] = { 0.0, 0.0, -4.0 };
    GLfloat my_set_material[4] = { 1.0, 1.0, 0.1, 0.8 };
    GLfloat light0_position[4] = { 4.0, 4.0, 4.0, 0.0 };
    GLfloat light1_position[4] = { -3.0, -3.0, -3.0, 0.0 };

    bool isDrawPoints = false;
    bool isDrawLines = false;
    bool isDrawFaces = false;

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

    void resetViewArgs();
    void prepareRedraw();
    void drawPoints();
    void drawLines();
    void drawFaces();

signals:

};

#endif // BASEOPENGLWIDGET_H
