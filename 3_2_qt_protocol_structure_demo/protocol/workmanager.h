
#ifndef WORKMANAGER_H
#define WORKMANAGER_H

#include <QList>
#include "work.h"

namespace HYKT {

class WorkManager
{
public:
    WorkManager();
    ~WorkManager();

    void AddWork(QByteArray &pkg);
    void InsertWorkAtHead(QByteArray &pkg);
    void CleanWorkList();
    void FinishAWork();
    Work* GetCurrentWork();
    bool IsHasWork();


private:
    QList<Work*> work_list_;

};

} //namespace HYKT
#endif // WORKMANAGER_H
