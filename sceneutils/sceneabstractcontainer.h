#ifndef SCENEABSTRACTCONTAINER_H
#define SCENEABSTRACTCONTAINER_H

#include <QObject>
#include <QFileInfo>

class SceneAbstractContainer : public QObject
{
    Q_OBJECT
public:
    explicit SceneAbstractContainer(QObject *parent = nullptr);
    virtual void setSelectedFile(QFileInfo qfi_selectedFile) = 0;
    QWidget *getContainer() const;

protected:
    QWidget *container;

signals:

};

#endif // SCENEABSTRACTCONTAINER_H
