#include "settings.h"

settings::settings(QObject *parent) : QObject(parent)
{

}

QString settings::getDefaultPath() const
{
    return defaultPath;
}

void settings::setDefaultPath(const QString &value)
{
    defaultPath = value;
}
