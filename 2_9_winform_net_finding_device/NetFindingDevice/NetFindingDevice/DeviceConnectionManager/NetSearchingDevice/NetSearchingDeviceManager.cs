
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
    class NetSearchingDeviceManager
    {
        const string TAG = "NetSearchingDevice";
        List<Finder> finderList;
        private int udpBroadcastDesPort = 2009;
        private string deviceIp;


        private static NetSearchingDeviceManager mInstance = null;

        private Thread mythread;
        private static bool isRun = false;

        private FoundNetDeviceList foundNetDeviceList;

        private NetSearchingDeviceManager() {
            finderList = new List<Finder>();
            foundNetDeviceList = FoundNetDeviceList.GetInstance();
        }

        public static NetSearchingDeviceManager GetInstance() {
            if (mInstance == null) {
                mInstance = new NetSearchingDeviceManager();
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

        public void StartFind(byte[] data) {

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
                finder.SetUdpBroadcastDesPort(udpBroadcastDesPort);
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

            if (data[0] == Protocol.head[0] &&
                data[length - 1] == Protocol.tail[0])//a pkg is finished
            {
                //skip pkg's head and tail
                int head = 1;
                int tail = length - 1;
                int i = 0;
                byte[] pkg = new byte[length - 2];

                for (int a = head; a < tail; a++)
                {
                    pkg[i++] = data[a];
                }

                if (Protocol.CrcCheck(pkg) == true)
                {
                    byte[] data2 = pkg.Take(pkg.Length - 2).ToArray(); //remove crc data
                    ProcessFindingDevice(data2);
                }
            }
        }

        private void ProcessFindingDevice(byte[] pkg)
        {
            string message = Encoding.UTF8.GetString(pkg, 0, pkg.Length);
            //std_str = "myname;0002231;V1.2.3"

            if (message.Contains("myname"))
            {
                string[] strArray = message.Split(';');
                NetDeviceInfo ndi = new NetDeviceInfo();
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
                        ndi.Version = strArray[a]; ;
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
