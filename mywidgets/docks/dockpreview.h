#ifndef DOCKPREVIEW_H
#define DOCKPREVIEW_H

#include "sceneutils/sceneabstractcontainer.h"
#include "sceneutils/sceneqt3dcontainer.h"
#include "sceneutils/sceneopenglcontainer.h"
#include <QWidget>
#include <QToolBox>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>

// 以何种底层技术渲染三维场景
enum SceneMode{
    GL_CONTAINER, Qt3DCANVAS_CONTAINER, Qt3D_CONTAINER
};

class DockPreview : public QWidget
{
    Q_OBJECT
public:
    explicit DockPreview(QWidget *parent = nullptr);
    SceneOpenGLContainer *getScene_opengl() const;

private:
    QHBoxLayout *qHBoxLayout;
    SceneMode sceneMode;
    SceneQt3DContainer *scene_qt3d = nullptr;
    SceneOpenGLContainer *scene_opengl = nullptr;
    QToolBox *qtb_setSceneMode;

    QCheckBox* qcb_OpenGL_modeIsPoints;
    QCheckBox* qcb_OpenGL_modeIsLines;
    QCheckBox* qcb_OpenGL_modeIsFaces;
    QPushButton* qpb_OpenGL_clear;

signals:

public slots:
    void setSelectedFile(const QFileInfo);
    void getSourceInfo(Qt3DRender::QMesh::Status status);

private slots:
    void resetScene(int index);
};

#endif // DOCKPREVIEW_H
