#include "globalvariable.h"

GlobalVariable* GlobalVariable::instance = nullptr;

GlobalVariable::GlobalVariable()
{

}

GlobalVariable* GlobalVariable::getInstance()
{
    if (!instance) {
        instance = new GlobalVariable();
    }
    return instance;
}
