#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class settings : public QObject
{
    Q_OBJECT
public:
    explicit settings(QObject *parent = nullptr);

    QString getDefaultPath() const;
    void setDefaultPath(const QString &value);

private:
    QString defaultPath = "D:/Codes/Codes_Qt/DModelExplorer/DModelExplorer/example_models";

signals:

};

#endif // SETTINGS_H
