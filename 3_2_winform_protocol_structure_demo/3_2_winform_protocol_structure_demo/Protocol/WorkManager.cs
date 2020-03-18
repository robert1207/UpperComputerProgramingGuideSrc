using System.Collections.Generic;

namespace HYKT
{
    class WorkManager
    {
        private List<Work> workList; 

        public WorkManager() {
            workList = new List<Work>();
        }

        public void AddWork(byte[] data)
        {
            Work work = new Work();
            work.Data = data;

            workList.Add(work);
        }

        public void CleanWorkList() {
            workList.Clear();
        }

        public void FinishAWork()
        {
            int count = workList.Count;
            if (count > 0)
            {
                workList.RemoveAt(0); //first work
            }
        }

        public Work GetCurrentWork() {
            int count = workList.Count;
            if (count > 0)
            {
                return workList[0]; //first work
            }
            return null;
        }

        public void markWorkFailed() {
            workList[0].FailedTimes += 1;

            if (workList[0].FailedTimes == 3) {
                //todo: call back for notice and abort all the work
            }
        }

        public Work GetWork() {
            Work work = null;
            //first in first out
            int count = workList.Count;
            if (count > 0) {
                work = workList[0];
            }

            return work;
        }

        public bool IsHasWork() {
            int count = workList.Count;

            if (count > 0) return true;
            else return false;
        }

    }
}
