#ifndef SCENEQT3DCONTAINER_H
#define SCENEQT3DCONTAINER_H

#include "sceneabstractcontainer.h"
#include <QWidget>
#include <Qt3DRender>

class SceneQt3DContainer : public SceneAbstractContainer
{
public:
    SceneQt3DContainer(QObject *parent = nullptr);
    ~SceneQt3DContainer() Q_DECL_OVERRIDE;
    void setSelectedFile(QFileInfo qfi_selectedFile) Q_DECL_OVERRIDE;
    void getSourceInfo(Qt3DRender::QMesh::Status status);

private:
//    QWidget *container;
    Qt3DCore::QEntity *m_previewEntity;
    Qt3DRender::QMesh *qm_preview;
};

#endif // SCENEQT3DCONTAINER_H
