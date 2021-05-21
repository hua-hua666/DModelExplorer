#ifndef SCENEOPENGLCONTAINER_H
#define SCENEOPENGLCONTAINER_H

#include "sceneabstractcontainer.h"
#include "modelutils/utils/dmodelutils.h"
#include <QObject>

class SceneOpenGLContainer : public SceneAbstractContainer
{
    Q_OBJECT
public:
    explicit SceneOpenGLContainer(QObject *parent = nullptr);
    ~SceneOpenGLContainer() Q_DECL_OVERRIDE;
    void setSelectedFile(QFileInfo qfi_selectedFile) Q_DECL_OVERRIDE;

signals:
    void emitModelInfo(myMesh*);

public slots:
    void modeIsPointsChanged(int state);
    void modeIsLinesChanged(int state);
    void modeIsFacesChanged(int state);
    void clearArgs();
};

#endif // SCENEOPENGLCONTAINER_H
