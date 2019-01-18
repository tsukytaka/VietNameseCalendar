#include "imgprovider.h"
#include <QDebug>
#include <QDir>

ImgProvider* ImgProvider::_instance = 0;

ImgProvider::ImgProvider(ImageType type, Flags flags) : QQuickImageProvider(type, flags)
{
}

ImgProvider* ImgProvider::GetInstance()
{
    if (!_instance) {
        _instance = new ImgProvider(QQmlImageProviderBase::Image, 0);
    }
    return _instance;
}

QImage ImgProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    Q_UNUSED(size)
    Q_UNUSED(requestedSize)
    QImage image;
    QMap<QString, QImage>::iterator i = dictionary.find(id);
    if (i != dictionary.end() && i.key() == id) {
        image = dictionary[id];
    } else {
        image.load(":/Images/1x/" + id);
        dictionary.insert(id, image);
    }
    return image;
}

void ImgProvider::insertImage(const QString& id, const QImage& img)
{
    QMap<QString, QImage>::iterator iter = dictionary.find(id);
    if (iter != dictionary.end()) {
        return;
    }
    dictionary.insert(id, img);
}

QList<QImage> ImgProvider::requestListImage(const QStringList& ids)
{
    QList<QImage> images{};
    foreach (const QString& id, ids) {
        QMap<QString, QImage>::iterator iter = dictionary.find(id);
        if (iter != dictionary.end()) {
            images.append(dictionary.value(id));
        }
    }
    return images;
}

//int ImgProvider::CleanImageProvider()
//{
//    dictionary.clear();
//    return 0;
//}

//int ImgProvider::clearReplaceItems()
//{
//    for (int i = 0; i < replaceItems.count(); i++) {
//        dictionary.remove(replaceItems[i]);
//    }
//    return 0;
//}
