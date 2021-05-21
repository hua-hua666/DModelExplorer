#include "dockpreview.h"
#include <QDebug>
#include <QUrl>
#include <QGroupBox>
#include <QDebug>

DockPreview::DockPreview(QWidget *parent) : QWidget(parent){
//    sceneMode = SceneMode::Qt3D_CONTAINER;

//    qHBoxLayout = new QHBoxLayout();
//    scene_qt3d = new SceneQt3DContainer();
//    qHBoxLayout->addWidget(scene_qt3d->getContainer());

    // 设定初始绘制方式
    sceneMode = SceneMode::GL_CONTAINER;

    // 初始化布局与默认绘图模块
    qHBoxLayout = new QHBoxLayout();
    scene_opengl = new SceneOpenGLContainer();
    qHBoxLayout->addWidget(scene_opengl->getContainer());

    // 初始化切换绘制方式工具箱
    qtb_setSceneMode = new QToolBox();
    qtb_setSceneMode->addItem(new QWidget(qtb_setSceneMode), "OpenGL");
    QVBoxLayout *qvbl_OpenGL = new QVBoxLayout();
    // 切换点线面模式
    QGroupBox* qgb_OpenGL_mode = new QGroupBox();
    qgb_OpenGL_mode->setTitle("绘制模式");
    QVBoxLayout *qvbl_OpenGL_mode = new QVBoxLayout();
    qcb_OpenGL_modeIsPoints = new QCheckBox();
    qcb_OpenGL_modeIsPoints->setText("以点绘制");
    qvbl_OpenGL_mode->addWidget(qcb_OpenGL_modeIsPoints);
    qcb_OpenGL_modeIsLines = new QCheckBox();
    qcb_OpenGL_modeIsLines->setText("以线绘制");
    qvbl_OpenGL_mode->addWidget(qcb_OpenGL_modeIsLines);
    qcb_OpenGL_modeIsFaces = new QCheckBox();
    qcb_OpenGL_modeIsFaces->setText("以面绘制");
    qvbl_OpenGL_mode->addWidget(qcb_OpenGL_modeIsFaces);
    qgb_OpenGL_mode->setLayout(qvbl_OpenGL_mode);
    qvbl_OpenGL->addWidget(qgb_OpenGL_mode);
    // 恢复默认参数
    QGroupBox* qgb_OpenGL_clear = new QGroupBox();
    qgb_OpenGL_clear->setTitle("恢复默认");
    QVBoxLayout *qvbl_OpenGL_clear = new QVBoxLayout();
    qpb_OpenGL_clear = new QPushButton();
    qpb_OpenGL_clear->setText("恢复默认");
    qvbl_OpenGL_clear->addWidget(qpb_OpenGL_clear);
    qgb_OpenGL_clear->setLayout(qvbl_OpenGL_clear);
    qvbl_OpenGL->addWidget(qgb_OpenGL_clear);
    qtb_setSceneMode->widget(0)->setLayout(qvbl_OpenGL);

    qtb_setSceneMode->addItem(new QWidget(qtb_setSceneMode), "Qt3D Canvas");
    qtb_setSceneMode->addItem(new QWidget(qtb_setSceneMode), "Qt3D");
    qtb_setSceneMode->setMaximumWidth(120);
    qtb_setSceneMode->setMinimumWidth(120);
    qHBoxLayout->addWidget(qtb_setSceneMode);

    setLayout(qHBoxLayout);

    // 信号与槽
    QObject::connect(qtb_setSceneMode, &QToolBox::currentChanged, this, &DockPreview::resetScene);
    QObject::connect(qcb_OpenGL_modeIsPoints, &QCheckBox::stateChanged, scene_opengl, &SceneOpenGLContainer::modeIsPointsChanged);
    QObject::connect(qcb_OpenGL_modeIsLines, &QCheckBox::stateChanged, scene_opengl, &SceneOpenGLContainer::modeIsLinesChanged);
    QObject::connect(qcb_OpenGL_modeIsFaces, &QCheckBox::stateChanged, scene_opengl, &SceneOpenGLContainer::modeIsFacesChanged);
    QObject::connect(qpb_OpenGL_clear, &QAbstractButton::clicked, scene_opengl, &SceneOpenGLContainer::clearArgs);    
}

SceneOpenGLContainer *DockPreview::getScene_opengl() const
{
    return scene_opengl;
}

/* public slots */
// 接收WidgetCentre::emitSelectedFile信号，设定选中文件，开始解析渲染
void DockPreview::setSelectedFile(const QFileInfo qfi_selectedFile){
    switch(sceneMode){
        case SceneMode::GL_CONTAINER:{
            scene_opengl->setSelectedFile(qfi_selectedFile);
            break;
        }
        case SceneMode::Qt3DCANVAS_CONTAINER:{
            break;
        }
        case SceneMode::Qt3D_CONTAINER:{
            scene_qt3d->setSelectedFile(qfi_selectedFile);
            break;
        }
        default:{

        }
    }
}

// 接收Qt3DRender::QMesh::statusChanged信号，获取模型详细数据信息
void DockPreview::getSourceInfo(Qt3DRender::QMesh::Status status){
    switch(sceneMode){
        case SceneMode::GL_CONTAINER:{
            break;
        }
        case SceneMode::Qt3DCANVAS_CONTAINER:{
            break;
        }
        case SceneMode::Qt3D_CONTAINER:{
            scene_qt3d->getSourceInfo(status);
            break;
        }
        default:{

        }
    }
}

/* private slots */
// 接收QToolBox::currentChanged信号，切换渲染方式时重置预览窗口
void DockPreview::resetScene(int index){
    switch(index){
        case SceneMode::GL_CONTAINER:{
            if(scene_opengl == nullptr){
                scene_opengl = new SceneOpenGLContainer();
                QObject::connect(qcb_OpenGL_modeIsPoints, &QCheckBox::stateChanged, scene_opengl, &SceneOpenGLContainer::modeIsPointsChanged);
                QObject::connect(qcb_OpenGL_modeIsLines, &QCheckBox::stateChanged, scene_opengl, &SceneOpenGLContainer::modeIsLinesChanged);
                QObject::connect(qcb_OpenGL_modeIsFaces, &QCheckBox::stateChanged, scene_opengl, &SceneOpenGLContainer::modeIsFacesChanged);
                QObject::connect(qpb_OpenGL_clear, &QAbstractButton::clicked, scene_opengl, &SceneOpenGLContainer::clearArgs);
            }
            qHBoxLayout->replaceWidget(scene_qt3d->getContainer(), scene_opengl->getContainer(), Qt::FindDirectChildrenOnly);
            if(scene_qt3d != nullptr){
                delete scene_qt3d;
                scene_qt3d = nullptr;
            }
            sceneMode = SceneMode::GL_CONTAINER;
            update();
            break;
        }
        case SceneMode::Qt3DCANVAS_CONTAINER:{

            sceneMode = SceneMode::Qt3DCANVAS_CONTAINER;
            break;
        }
        case SceneMode::Qt3D_CONTAINER:{
            if(scene_qt3d == nullptr){
                scene_qt3d = new SceneQt3DContainer();
            }
            qHBoxLayout->replaceWidget(scene_opengl->getContainer(), scene_qt3d->getContainer(), Qt::FindDirectChildrenOnly);
            if(scene_opengl != nullptr){
                delete scene_opengl;
                scene_opengl = nullptr;
            }
            sceneMode = SceneMode::Qt3D_CONTAINER;
            break;
        }
        default:{

        }
    }
}
