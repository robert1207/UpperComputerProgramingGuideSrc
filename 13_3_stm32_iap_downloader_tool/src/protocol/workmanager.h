
#ifndef WORKMANAGER_H
#define WORKMANAGER_H

#include <QList>
#include "work.h"


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
    int GetWorkCount();


private:
    QList<Work*> work_list_;

};

#endif // WORKMANAGER_H
