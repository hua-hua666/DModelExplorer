#include "sceneabstractcontainer.h"

SceneAbstractContainer::SceneAbstractContainer(QObject *parent) : QObject(parent){

}

/* public */
// 获取渲染窗口
QWidget *SceneAbstractContainer::getContainer() const{
    return container;
}
