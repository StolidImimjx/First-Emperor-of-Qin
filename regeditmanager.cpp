#include "regeditmanager.h"
const QString run_key = "HKEY_CLASSES_ROOT\\Directory\\Background\\shell";

RegeditManager::RegeditManager(QObject *parent) : QObject(parent)
{

}
RegeditManager::~RegeditManager()
{
    if(pRegManager != NULL)
        delete pRegManager;
}

/**
 * @brief 初始化注册表管理对象静态指针
 */
RegeditManager* RegeditManager::pRegManager = new RegeditManager();

/**
 * @brief  获取注册表管理对象静态指针的接口
 * @return 注册表管理对象指针
 */
RegeditManager* RegeditManager::GetInstance()
{
    return pRegManager;
}


bool RegeditManager::AddToolToRightMenu(const QString keyName,   //项(键)文件夹的名称
                                        const QString iconPath,  //图标文件路径
                                        const QString execPath)  //执行文件路径
{
    QString temp_key;

    //使用注册表的路径与QSettings::NativeFormat组合读写注册表.

    //在shell项下添加key为keyName的项
    temp_key = run_key + "\\" + keyName;
    qDebug() <<  temp_key << endl;
    QSettings *pSet = new QSettings(temp_key, QSettings::NativeFormat);
    pSet->setValue(".", keyName);         // 默认值设为keyName---QT对于默认值的处理,其key指定为"."
    if(!iconPath.isEmpty() && !iconPath.isNull())
        pSet->setValue("Icon", iconPath); // 为keyName项添加名称为Icon,值为iconPath的字符串值

    //在keyName项下添加key为command的项
    temp_key = temp_key + "\\command";
    qDebug() <<  temp_key << endl;
    pSet = new QSettings(temp_key, QSettings::NativeFormat);
    pSet->setValue(".",execPath);//默认值设为execPath

    delete pSet;
    pSet = NULL;
    return true;
}
bool  RegeditManager::DelToolFromRightMenu(const QString keyName)
{
    if(keyName.isEmpty() || keyName.isNull())
    {
        qDebug() << "keyName is not cunzai" <<endl;
        return false;
    }
    QSettings *pSet = new QSettings(run_key, QSettings::NativeFormat);
    pSet->remove(keyName);
    return true;
}
