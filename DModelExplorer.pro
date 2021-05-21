QT       += core gui 3dextras 3drender opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "3D Model Explorer"

LIBS += -lOpengl32
LIBS += -lGlU32

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += D:\Codes\Codes_Qt\DModelExplorer\DModelExplorer

HEADERS += \
    modelutils/myoopengl/baseopenglwidget.h \
    modelutils/myoopengl/imageopenglwidget.h \
    modelutils/utils/dmodelutils.h \
    mymodels/modelinfomodel.h \
    mymodels/mydircontentsmodel.h \
    mymodels/mydirsystemmodel.h \
    mywidgets/dialogs/dialogabout.h \
    mywidgets/docks/dockdirtreeview.h \
    mywidgets/docks/dockinfo.h \
    mywidgets/docks/dockpreview.h \
    mywidgets/docks/widgetcentre.h \
    mywidgets/mainwindow.h \
    sceneutils/sceneabstractcontainer.h \
    sceneutils/sceneopenglcontainer.h \
    sceneutils/sceneopenglwidget.h \
    sceneutils/sceneqt3dcontainer.h \
    settings/settings.h \
    viewutils/thumbnailunitdelegate.h

SOURCES += \
    main.cpp \
    modelutils/myoopengl/baseopenglwidget.cpp \
    modelutils/myoopengl/imageopenglwidget.cpp \
    modelutils/utils/dmodelutils.cpp \
    mymodels/modelinfomodel.cpp \
    mymodels/mydircontentsmodel.cpp \
    mymodels/mydirsystemmodel.cpp \
    mywidgets/dialogs/dialogabout.cpp \
    mywidgets/docks/dockdirtreeview.cpp \
    mywidgets/docks/dockinfo.cpp \
    mywidgets/docks/dockpreview.cpp \
    mywidgets/docks/widgetcentre.cpp \
    mywidgets/mainwindow.cpp \
    sceneutils/sceneabstractcontainer.cpp \
    sceneutils/sceneopenglcontainer.cpp \
    sceneutils/sceneopenglwidget.cpp \
    sceneutils/sceneqt3dcontainer.cpp \
    settings/settings.cpp \
    viewutils/thumbnailunitdelegate.cpp

RESOURCES += \
    resources/Icon.qrc

