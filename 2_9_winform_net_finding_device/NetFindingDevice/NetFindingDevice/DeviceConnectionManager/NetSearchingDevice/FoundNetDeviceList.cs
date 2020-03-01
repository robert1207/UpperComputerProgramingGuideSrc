
using System.Collections.Generic;

namespace HYKT
{
    class FoundNetDeviceList
    {

        private FoundNetDeviceList() {
            netDeviceInfoList = new List<NetDeviceInfo>();
        }


        private static FoundNetDeviceList mInstance = null;


        private List<NetDeviceInfo> netDeviceInfoList;


        public static FoundNetDeviceList GetInstance() {
            if(mInstance == null)
            {
                mInstance = new FoundNetDeviceList();
            }
            return mInstance;
        }

        public void AddNetDevice(NetDeviceInfo device) {
            netDeviceInfoList.Add(device);
        }

        public bool IsDeviceExist(NetDeviceInfo device) {
            foreach (NetDeviceInfo ins in netDeviceInfoList) {
                if (ins.Ip.Equals(device.Ip) && ins.SN.Equals(device.SN)) {
                    return true;
                }
            }

            return false;
        }


        public List<NetDeviceInfo> GetNetDeviceList() {
            return netDeviceInfoList;
        }

        public void Clear() {
            netDeviceInfoList.Clear();
        }


        private int SelectedIndex = 0;
        public void SetSelectedIndex(int index) {
            SelectedIndex = index;
        }

        public int GetSelectedIndex() {
            return SelectedIndex;
        }

    }
}
