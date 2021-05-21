#include "dialogabout.h"

DialogAbout::DialogAbout(QWidget *parent) : QDialog(parent){
    // “关于”窗口属性
    setMinimumSize(800, 600);
    setMaximumSize(800, 600);
    setWindowTitle("关于3D Model Explorer");
}
