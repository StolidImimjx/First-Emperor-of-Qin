#ifndef REGEDITMANAGER_H
#define REGEDITMANAGER_H

#include <QObject>
#include <QSettings>
#include <QDebug>

class RegeditManager : public QObject
{
    Q_OBJECT
public:
    explicit  RegeditManager(QObject *parent = 0);
    ~RegeditManager();
    static  RegeditManager*  GetInstance();
    bool  AddToolToRightMenu(const QString keyName,
                             const QString iconPath,
                             const QString execPath);
    bool  DelToolFromRightMenu(const QString keyName);

signals:

public slots:

private:
    static RegeditManager* pRegManager;
};


#endif // REGEDITMANAGER_H
