#include "common_string.h"


//QString stringFileTbl[NUM_OF_COMMON_LANGAGE_TYPE]
//{
//    "./lng/StringCollection_VIE.csv",
//	"./lng/StringCollection_ENG.csv"
//};

static QString stringTbl[NUM_OF_STRING_ID]
{
    "Mặc định",
    "Lịch người Việt",
};

CommonStringMaster::CommonStringMaster(COMMON_LANGAGE_TYPE type)
{
    Q_UNUSED(type);
}

CommonStringMaster::~CommonStringMaster(void)
{
}

uint32_t CommonStringMaster::getStringLength(quint32 stringId)
{
    QString catchString = (stringId < NUM_OF_STRING_ID) ? stringTbl[stringId] : "";
    quint32 length = static_cast<quint32>(catchString.length());

    return length;
}

void CommonStringMaster::getString(quint32 stringId, QString &str)
{
    QString catchString = (stringId < NUM_OF_STRING_ID) ? stringTbl[stringId] : "";
    str = catchString;

    return;
}

