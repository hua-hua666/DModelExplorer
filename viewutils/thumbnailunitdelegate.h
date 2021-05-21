#ifndef THUMBNAILUNITDELEGATE_H
#define THUMBNAILUNITDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class ThumbnailUnitDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ThumbnailUnitDelegate(QObject *parent = nullptr);

signals:

};

#endif // THUMBNAILUNITDELEGATE_H
