#include "sceneqt3dcontainer.h"
#include <Qt3DExtras>

SceneQt3DContainer::SceneQt3DContainer(QObject *parent) : SceneAbstractContainer(parent){
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
//    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0xf0f0f0)));
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0xffffff)));
    container = QWidget::createWindowContainer(view);
    QSize screenSize = view->screen()->size();
    container->setMinimumSize(QSize(200, 100));
    container->setMaximumSize(screenSize);

    Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
    view->registerAspect(input);

    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    // Camera
    Qt3DRender::QCamera *cameraEntity = view->camera();
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 10000.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);

    // For camera controls
//    camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setCamera(cameraEntity);

    // Preview shape data
    //! [0]
    qm_preview = new Qt3DRender::QMesh();
//    qm_preview->setSource(QUrl::fromLocalFile("D:/Codes/Codes_Qt/DModelExplorer/DModelExplorer/example_models/皮卡丘_1/pikaqiu.obj"));
    qm_preview->setMeshName("MeshPreview");
    qm_preview->setEnabled(true);
    //! [0]

    // PreviewMesh Transform
    //! [1]
    Qt3DCore::QTransform *previewTransform = new Qt3DCore::QTransform();
    previewTransform->setScale(2.0f);
//    previewTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 25.0f));
//    previewTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));
    //! [1]

    //! [2]
    Qt3DExtras::QPhongMaterial *previewMaterial = new Qt3DExtras::QPhongMaterial();
    previewMaterial->setDiffuse(QColor(QRgb(0xbeb32b)));
    //! [2]

    // previewEntity
    //! [3]
    m_previewEntity = new Qt3DCore::QEntity(rootEntity);
    m_previewEntity->addComponent(qm_preview);
    m_previewEntity->addComponent(previewMaterial);
    m_previewEntity->addComponent(previewTransform);
    //! [3]

    // Set root object of the scene
    view->setRootEntity(rootEntity);
}

SceneQt3DContainer::~SceneQt3DContainer(){
    delete container;
}

/* public */
// 【重写】设置选中文件，以供渲染
void SceneQt3DContainer::setSelectedFile(QFileInfo qfi_selectedFile){
    QString str_suffix = qfi_selectedFile.suffix();
    if(QString::compare(str_suffix, "obj", Qt::CaseInsensitive) != 0
            && QString::compare(str_suffix, "ply", Qt::CaseInsensitive) != 0
            && QString::compare(str_suffix, "stl", Qt::CaseInsensitive) != 0){
        return;
    }
    m_previewEntity->removeComponent(qm_preview);
    delete qm_preview;
    qm_preview = new Qt3DRender::QMesh();
    qm_preview->setMeshName("MeshPreview");
    qm_preview->setEnabled(true);
    m_previewEntity->addComponent(qm_preview);
    QObject::connect(qm_preview, &Qt3DRender::QMesh::statusChanged, this, &SceneQt3DContainer::getSourceInfo);
    qm_preview->setSource(QUrl::fromLocalFile(qfi_selectedFile.absoluteFilePath()));
}

// 获取文件信息
void SceneQt3DContainer::getSourceInfo(Qt3DRender::QMesh::Status status){
    if(status == Qt3DRender::QMesh::Ready){
//        qDebug()<<qm_preview->firstInstance();
//        qDebug()<<qm_preview->firstVertex();
//        qDebug()<<qm_preview->geometry();
//        qDebug()<<qm_preview->geometry()->maxExtent();
//        qDebug()<<qm_preview->geometry()->minExtent();
//        qDebug()<<qm_preview->geometry()->boundingVolumePositionAttribute();
//        qDebug()<<qm_preview->indexBufferByteOffset();
//        qDebug()<<qm_preview->indexOffset();
//        qDebug()<<qm_preview->instanceCount();
//        qDebug()<<qm_preview->primitiveRestartEnabled();
//        qDebug()<<qm_preview->primitiveType();
//        qDebug()<<qm_preview->restartIndexValue();
//        qDebug()<<qm_preview->vertexCount();
//        qDebug()<<qm_preview->verticesPerPatch();
        qDebug()<<"---------------------------------";

        QVector<Qt3DRender::QAttribute *> tmp = qm_preview->geometry()->attributes();
        for(int i=0; i<tmp.size(); i++){
            Qt3DRender::QAttribute * tmpp = tmp[i];
//            qDebug()<<tmpp->attributeType();
//            qDebug()<<tmpp->count();
//            qDebug()<<tmpp->name();
//            qDebug()<<tmpp->divisor();
        }
    }
}
