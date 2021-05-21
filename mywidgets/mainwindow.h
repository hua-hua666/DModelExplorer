#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() Q_DECL_OVERRIDE;

private:
    QFileSystemModel *baseFileModel;
    void closeWindow();
    void createOpenFile();
    void createAbout();
    void openTempPath();

signals:
    void baseFileModelConstructed(QFileSystemModel *baseFileModel);
};
#endif // MAINWINDOW_H
