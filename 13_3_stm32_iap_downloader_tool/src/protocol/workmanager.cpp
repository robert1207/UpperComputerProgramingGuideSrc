

#include "workmanager.h"


WorkManager::WorkManager()
{


}

WorkManager::~WorkManager()
{

}

void WorkManager::AddWork(QByteArray &pkg) {
   Work *work = new Work();
   work->data = pkg;
   work_list_.append(work);
}

void WorkManager::InsertWorkAtHead(QByteArray &pkg) {
    Work *work = new Work();
    work->data = pkg;
    work_list_.insert(0, work);
}

void WorkManager::CleanWorkList() {
    for (int a = 0; a < work_list_.count(); ++a) {
        Work *work = work_list_.at(a);
        delete work;
    }
   work_list_.clear();
}

void WorkManager::FinishAWork()
{
   int count = work_list_.count();
   if (count > 0) {
       Work *work = work_list_.at(0);
       delete work;
       work_list_.removeAt(0); //first work
   }
}

Work* WorkManager::GetCurrentWork() {
   int count = work_list_.count();
   if (count > 0) {
       return work_list_.at(0); //first work
   }
   return nullptr;
}

bool WorkManager::IsHasWork() {
   int count = work_list_.count();

   if (count > 0) return true;
   else return false;
}

int WorkManager::GetWorkCount() {
    return work_list_.count();
}

