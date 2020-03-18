
using System.Collections.Generic;

namespace HYKT
{
    class FoundNetDeviceList
    {

        private FoundNetDeviceList() {
            netDeviceInfoList = new List<DeviceInfo>();
        }


        private static FoundNetDeviceList mInstance = null;


        private List<DeviceInfo> netDeviceInfoList;


        public static FoundNetDeviceList GetInstance() {
            if(mInstance == null)
            {
                mInstance = new FoundNetDeviceList();
            }
            return mInstance;
        }

        public void AddNetDevice(DeviceInfo device) {
            netDeviceInfoList.Add(device);
        }

        public bool IsDeviceExist(DeviceInfo device) {
            foreach (DeviceInfo ins in netDeviceInfoList) {
                if (ins.Ip.Equals(device.Ip) && ins.SN.Equals(device.SN)) {
                    return true;
                }
            }

            return false;
        }


        public List<DeviceInfo> GetNetDeviceList() {
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
