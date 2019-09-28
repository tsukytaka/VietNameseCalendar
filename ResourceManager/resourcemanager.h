#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "resourcemanager_global.h"
#include <QImage>
#include <QDir>
#include <QMap>

#ifndef RESOURCE_FILE_PATH
#define RESOURCE_FILE_PATH "qrc://";
#endif

#ifndef RESOURCE_FILE_TYPE
#define RESOURCE_FILE_TYPE ".png";
#endif

class RESOURCEMANAGERSHARED_EXPORT ResourceManager
{

public:
    static ResourceManager *GetInstance();
    QImage getImage(QString imageName);

private:
    static ResourceManager *_instance;
    QMap<QString, QImage> _resourcrTable;
    ResourceManager();
    ~ResourceManager();
    QImage loadFileImage(QString name);
};

#endif // RESOURCEMANAGER_H
