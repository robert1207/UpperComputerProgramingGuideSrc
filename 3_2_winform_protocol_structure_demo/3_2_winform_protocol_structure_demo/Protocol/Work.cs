using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace HYKT
{
    class Work
    {
        public Work() {
            FailedTimes = 0;
        }

        public int FailedTimes { get; set; }
        public byte[] Data { get; set; }

        public bool CheckResponse(byte[] returnData) {
            if (returnData[0] == Data[2] && returnData[1] == Data[3]) { return true; }
            return false;
        }

    }
}
