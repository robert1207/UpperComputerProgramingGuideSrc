
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace HYKT
{
    class SearchingDeviceManager
    {
        const string TAG = "NetSearchingDevice";
        List<Finder> finderList;
        private string deviceIp;

        private bool package_on = false;
        private byte[] cache;
        private int pos = 0;
        private static readonly int CACHE_LENGTH = 1024 * 5;


        private static SearchingDeviceManager mInstance = null;

        private Thread mythread;
        private static bool isRun = false;

        private FoundNetDeviceList foundNetDeviceList;

        private SearchingDeviceManager() {
            cache = new byte[CACHE_LENGTH];
            finderList = new List<Finder>();
            foundNetDeviceList = FoundNetDeviceList.GetInstance();
        }

        public static SearchingDeviceManager GetInstance() {
            if (mInstance == null) {
                mInstance = new SearchingDeviceManager();
            }
            return mInstance;
        }

        //finding device error listener
        public delegate void OnFindDeviceError(string reason);
        private OnFindDeviceError onFindDeviceErrorListener = null;
        public void SetOnFindDeviceErrorListener(OnFindDeviceError l)
        {
            onFindDeviceErrorListener = l;
        }
        private void CallOnFindDeviceErrorListener(string reason)
        {
            if (onFindDeviceErrorListener != null)
            {
                onFindDeviceErrorListener(reason);
            }
        }

        //finding device update device list
        public delegate void OnUpdateDeviceListener(FoundNetDeviceList foundNetDeviceList);
        private OnUpdateDeviceListener onUpdateDeviceListener = null;
        public void SetOnUpdateDeviceListener(OnUpdateDeviceListener l)
        {
            onUpdateDeviceListener = l;
        }
        private void CallOnUpdateDeviceListener(FoundNetDeviceList foundNetDeviceList)
        {
            if (onUpdateDeviceListener != null)
            {
                onUpdateDeviceListener(foundNetDeviceList);
            }
        }

        public void StartFind(byte[] data, int port = 2009) {

            //find ip of net card
            List<String> ipList = GetIpListOfTheNetInterface();
            if (ipList.Count == 0) {
                CallOnFindDeviceErrorListener("no net interface been found");
            }

            finderList.Clear();
            for (int a = 0; a < ipList.Count; a ++)
            {
                Finder finder = new Finder();
                //set ip
                String ip = ipList.ElementAt(a);
               // Log.i(TAG, "found device ip = "+ip);
                finder.SetNetCardIp(ip);
                finder.SetNetFindDeviceCommandPkg(data);
                finder.SetUdpBroadcastDesPort(port);
                //set listener
                finder.SetOnFindDeviceErrorListener(CallOnFindDeviceErrorListener);
                finder.SetOnRecvDeviceInfoListener(OnRecvDeviceInfoListener);
                finderList.Add(finder);
            }

            //start finder
            for(int b = 0; b < finderList.Count; b ++)
            {
                Finder f = finderList.ElementAt(b);
                f.StartFind();
            }

            StartWorkThread();
        }

        public void StopFind() {
            //stop finder
            for (int b = 0; b < finderList.Count; b++)
            {
                Finder f = finderList.ElementAt(b);
                f.StopFind();
            }

            //clear finder list
            finderList.Clear();
            StopWorkThread();
        }

        public void CleanFoundedDeviceList()
        {
            foundNetDeviceList.Clear();
        }

        private List<String> GetIpListOfTheNetInterface() {

            List<String> ipList = new List<string>();

            NetworkInterface[] NetworkInterfaces = NetworkInterface.GetAllNetworkInterfaces();
            foreach (NetworkInterface NetworkIntf in NetworkInterfaces)
            {
                IPInterfaceProperties IPInterfaceProperties = NetworkIntf.GetIPProperties();
                UnicastIPAddressInformationCollection UnicastIPAddressInformationCollection =
                                                                                        IPInterfaceProperties.UnicastAddresses;
                foreach (UnicastIPAddressInformation UnicastIPAddressInformation in UnicastIPAddressInformationCollection)
                {
                    if (UnicastIPAddressInformation.Address.AddressFamily == AddressFamily.InterNetwork)
                    {
                        String ip = UnicastIPAddressInformation.Address.ToString();
                        if (!ip.Equals("127.0.0.1")) {
                            ipList.Add(ip);
                        }
                    }
                }
            }
            return ipList;
        }

        //*********************** update founded device list thread
        private void StartWorkThread()
        {
            mythread = new Thread(ThreadWork);
            isRun = true;
            mythread.Start();
        }

        private static void StopWorkThread()
        {
            isRun = false;
        }

        private void ThreadWork()
        {
            while (isRun)
            {
                CallOnUpdateDeviceListener(foundNetDeviceList);
                Thread.Sleep(1000);
            }
        }

        private void OnRecvDeviceInfoListener(byte[] data, int length, IPEndPoint remoteIpep)
        {
            deviceIp = remoteIpep.Address.ToString();

            for (int a = 0; a < length; a++)
            {
                Process(data[a]);
            }
        }

        private void Process(byte b)
        {
            if (package_on == true)
            {
                if (pos > CACHE_LENGTH)
                {
                    package_on = false;
                    pos = 0;
                    return;
                }

                cache[pos++] = b;
                if (pos > 4 &&
                    cache[pos - 4] == Command.tail[0] &&    //a pkg is finished
                    cache[pos - 3] == Command.tail[1] &&
                    cache[pos - 2] == Command.tail[2] &&
                    cache[pos - 1] == Command.tail[3] &&
                    cache[Command.head.Length] + Command.head.Length + Command.tail.Length == pos //check pkg len
                    ) {
                    package_on = false;

                    byte[] temp = cache.Take(pos - 4).ToArray();//remove tail' bytes
                    byte[] pkg = temp.Skip(2).ToArray();//remove head byte and pkg-len byte

                    if (CRC16.CheckCRC(pkg) == true)
                    {
                        ProcessFindingDevice(pkg.Take(pkg.Length - 2).ToArray());//remove crc's bytes
                    }
                    else
                    {
                        CallOnFindDeviceErrorListener("crc check error");
                    }
                }
            }
            else if (package_on == false && b == Command.head[0])
            { //start a pkg
                package_on = true;
                pos = 0;
                cache[pos++] = b;
            }
        }

        private void ProcessFindingDevice(byte[] pkg)
        {

            string message = Encoding.UTF8.GetString(pkg, 0, pkg.Length);
            //std_str = "myname;0002231;V1.2.3"

            if (message.Contains("myname"))
            {
                string[] strArray = message.Split(';');
                DeviceInfo ndi = new DeviceInfo();
                ndi.Ip = deviceIp;

                for (int a = 0; a < strArray.Length; a++)
                {
                    //get sn
                    if (a == 1)
                    {
                        ndi.SN = strArray[a];
                    }

                    //get version
                    if (a == 2)
                    {
                        ndi.Version = strArray[a]; 
                    }
                }

                if (foundNetDeviceList != null)
                {
                    if (!foundNetDeviceList.IsDeviceExist(ndi))
                    {
                        foundNetDeviceList.AddNetDevice(ndi);
                    }
                }
            }
        }





    }
}
