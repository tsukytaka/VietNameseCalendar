#ifndef COMMON_STRING_H
#define COMMON_STRING_H

#ifndef FILE_PATH_LENGTH
#define FILE_PATH_LENGTH 255
#endif

#include <QString>
#include <QVector>

typedef enum {
    COMMON_LANGAGE_TYPE_VIE,
	COMMON_LANGAGE_TYPE_ENG,
	NUM_OF_COMMON_LANGAGE_TYPE
}COMMON_LANGAGE_TYPE;

class CommonStringMaster
{
private:
    quint32 m_numOfStringId;
public:
    CommonStringMaster(COMMON_LANGAGE_TYPE type);
    ~CommonStringMaster(void);
    quint32 getStringLength(quint32 stringId);
    void getString(quint32 stringId, QString &str);
};

enum {
    STRING_ID_DEFAULT = 0,
    STRING_ID_NAME_APPLICATION,
	NUM_OF_STRING_ID,
};

#endif	// COMMON_STRING_H
