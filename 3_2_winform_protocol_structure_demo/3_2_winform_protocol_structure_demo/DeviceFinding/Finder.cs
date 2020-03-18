
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace HYKT
{
    class Finder
    {
        const string TAG = "Finder";

        private Thread findDeviceThread;    
        private bool isFindDevice = false;
        private Thread findDeviceRecvInfoThread;
        private UdpClient udpFindDeviceRecv;
        private int udpBroadcastDesPort = 2009;
        private IPAddress netCardIp = IPAddress.Parse("192.168.3.6");

        private byte[] findDeviceCommandPkg;

        public void SetNetCardIp(String ip) {
            netCardIp = IPAddress.Parse(ip);
        }

        public void SetUdpBroadcastDesPort(int port) {
            udpBroadcastDesPort = port;
        }

        public void SetNetFindDeviceCommandPkg(byte [] data) {
            findDeviceCommandPkg = data;
        }
        public void StartFind()
        {
            try
            {
                IPEndPoint ipe = new IPEndPoint(netCardIp, udpBroadcastDesPort);
                udpFindDeviceRecv = new UdpClient(ipe); //recv pkg
            }
            catch (System.Net.Sockets.SocketException sockEx)
            {
                return;

                //由于查找到的IP并不一定可以对应的网卡的指定端口
                //经测试发现了这样的问题。因此这里遇到打不开的，跳过这个即可
                //因为这里设计的是给每个网卡对应的网段发送广播，
                //因此打不开的就不打开，跳过即可
                /*
                if (onFindDeviceErrorListener != null)
                {
                    onFindDeviceErrorListener("StartFind: " + sockEx.ToString());
                }*/
            }

            isFindDevice = true;//set true before start thread
            //read device info thread
            findDeviceRecvInfoThread = new Thread(RecvDeviceInfo);
            findDeviceRecvInfoThread.Start();

            //broadcast thread
            findDeviceThread = new Thread(SendingBroadcast);
            findDeviceThread.Start();
        }

        public void StopFind()
        {
            isFindDevice = false;
        }

        private void SendingBroadcast(object obj)
        {
            while (isFindDevice)
            {
                try {
                    try
                    {
                        Thread.Sleep(500);
                        IPEndPoint iep = new IPEndPoint(IPAddress.Broadcast, udpBroadcastDesPort);
                       // byte[] bytes = { 0xee, 0x04, 0x01, 0xb0, 0xc2, 0xbb };
                        if (udpFindDeviceRecv == null) break;
                        udpFindDeviceRecv.Send(findDeviceCommandPkg, findDeviceCommandPkg.Length, iep);
                    }
                    catch (System.Net.Sockets.SocketException sockEx)
                    {
                        if (onFindDeviceErrorListener != null)
                        {
                            onFindDeviceErrorListener("SendingBroadcast: " + sockEx.ToString());
                        }
                        break;
                    }
                } catch (Exception ex) {
                    if (onFindDeviceErrorListener != null)
                    {
                        onFindDeviceErrorListener("SendingBroadcast: " + ex.ToString());
                    }
                    break;
                }
            }
        }

        private void RecvDeviceInfo(object obj)
        {
            IPEndPoint remoteIpep = new IPEndPoint(IPAddress.Any, 0);
            while (isFindDevice)
            {
                try {
                    try
                    {
                        lock (this)
                        {
                            if (udpFindDeviceRecv == null) break;
                            if (udpFindDeviceRecv != null && isFindDevice == true)
                            {
                                if (udpFindDeviceRecv.Available <= 0) continue;
                                byte[] bytRecv = udpFindDeviceRecv.Receive(ref remoteIpep);
                                if (onRecvDeviceInfoListener != null)
                                {
                                    onRecvDeviceInfoListener(bytRecv, bytRecv.Length, remoteIpep);
                                }
                            }
                        }
                    }
                    catch (System.Net.Sockets.SocketException sockEx)
                    {
                        if (onFindDeviceErrorListener != null)
                        {
                            onFindDeviceErrorListener("RecvDeviceInfo: " + sockEx.ToString());
                        }
                        break;
                    }
                } catch (Exception ex) {
                    if (onFindDeviceErrorListener != null)
                    {
                        onFindDeviceErrorListener("RecvDeviceInfo: " + ex.ToString());
                    }
                    break;
                }
            }

            if (udpFindDeviceRecv != null)
            {
                udpFindDeviceRecv.Close();
                udpFindDeviceRecv = null;
            }
        }


        public delegate void OnFindDeviceError(string reason);
        private OnFindDeviceError onFindDeviceErrorListener = null;
        public void SetOnFindDeviceErrorListener(OnFindDeviceError l)
        {
            onFindDeviceErrorListener = l;
        }

        public delegate void OnRecvDeviceInfoListener(byte[] data, int length, IPEndPoint remoteIpep);
        private OnRecvDeviceInfoListener onRecvDeviceInfoListener = null;
        public void SetOnRecvDeviceInfoListener(OnRecvDeviceInfoListener l) {
            onRecvDeviceInfoListener = l;
        }


    }
}
