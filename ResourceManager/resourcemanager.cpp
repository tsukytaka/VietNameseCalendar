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
    if (_resourcrTable.contains(imgName)) {
        img = _resourcrTable[imgName];
#ifdef DEBUG
        cout << "Load from Resource Table.\n";
#endif
    } else {
        img = loadFileImage(imgName);
        _resourcrTable[imgName] = img;
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
