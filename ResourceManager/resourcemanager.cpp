#include "resourcemanager.h"

ResourceManager *ResourceManager::_instance = nullptr;

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

ResourceManager *ResourceManager::GetInstance()
{
    if (!_instance) {
        _instance = new ResourceManager();
    }
    return _instance;
}

QImage ResourceManager::getImage(QString imgName)
{
    QImage img;
    QMap<QString, QImage>::iterator itr = _resourcrTable.find(imgName);
    if (itr != _resourcrTable.end()) {
        img = itr.value();
#ifdef DEBUG
        cout << "Load from Resource Table.\n";
#endif
    } else {
        img = loadFileImage(imgName);
//        if (!img.isNull()) {
            _resourcrTable[imgName] = img;
//        }
    }
    return img;
}

QImage ResourceManager::loadFileImage(QString name)
{
    QImage img;
    QString filePath = RESOURCE_FILE_PATH;
    filePath += name;
    filePath += RESOURCE_FILE_TYPE;

    filePath = QDir::toNativeSeparators(filePath);

    if (QFile::exists(filePath)) {
        img.load(filePath);
    }

    return img;
}
