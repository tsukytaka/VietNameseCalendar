#ifndef IMGPROVIDER_H
#define IMGPROVIDER_H

#include <QQuickImageProvider>
#include "afxstd.h"

#define IMAGE_EXT "*.png"

class ImgProvider : public QQuickImageProvider
{
private:
    QMap<QString, QImage> dictionary;
//    QList<QString> replaceItems;

public:
    static ImgProvider* GetInstance();
    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize);
public:
//    int UpdateReplaceFolder();
//    int CleanImgProvider();
    void insertImage(const QString& id, const QImage& img);
    QList<QImage> requestListImage(const QStringList& ids);
private:
    static ImgProvider* _instance;
    ImgProvider(ImageType type, Flags flags = 0);
//    int clearReplaceItems();
};

#endif // IMGPROVIDER_H
