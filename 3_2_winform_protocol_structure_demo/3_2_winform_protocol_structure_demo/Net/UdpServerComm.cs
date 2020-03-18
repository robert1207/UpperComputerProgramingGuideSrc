using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace HYKT
{
    class UdpServerComm : Comm
    {

        private OnNetRecvListener onNetRecvListener = null;
        private OnNetErrorListener onNetErrorListener = null;

        private UdpClient udpClient;
        private Thread thrRecv;

        private bool isOpen = false;
        private IPEndPoint sendDataRemoteInfo = null;

        public bool Open(string addr, int port)
        {
   
            if (NetUtil.IsPortInUse(port) == true)
            {
                if (onNetErrorListener != null)
                {
                    onNetErrorListener("udp server open error", new Exception("the port is in use"));
                }
                return false;
            }

            
            udpClient = new UdpClient(port); //listener port
            thrRecv = new Thread(ReceiveMessageThread);
            thrRecv.Start();
            isOpen = true;

            return true;
        }

        public void Close()
        {
            isOpen = false;//this will kill the thread
            sendDataRemoteInfo = null;
            if (udpClient != null)
            {
                udpClient.Close();
            }
        }

        public bool Send(byte[] data)
        {
            try
            {
                try
                {
                    int len = udpClient.Send(data, data.Length, sendDataRemoteInfo);
                    if (len > 0) return true;
                }
                catch (System.Net.Sockets.SocketException sockEx)
                {
                    Close();
                    if (onNetErrorListener != null)
                    {
                        onNetErrorListener("udp server send error", sockEx);
                    }
                }
            }
            catch (Exception e)
            {
                Close();
                if (onNetErrorListener != null)
                {
                    onNetErrorListener("udp server send error", e);
                }
            }
            return false;
        }

        private void ReceiveMessageThread(object obj)
        {
            IPEndPoint remoteIpep = new IPEndPoint(IPAddress.Any, 0);
            while (isOpen)
            {
                try
                {
                    try
                    {
                        if (udpClient == null)
                        {
                            Close();
                            if (onNetErrorListener != null)
                            {
                                onNetErrorListener("udp server recv error", new Exception("exception of null instance "));
                            }
                            break;
                        }
                        if (udpClient.Available <= 0)
                        {
                            Thread.Sleep(10);
                        }
                        else
                        {
                            byte[] bytRecv = udpClient.Receive(ref remoteIpep); //block recv

                            if (sendDataRemoteInfo == null)
                            {
                                sendDataRemoteInfo = new IPEndPoint(remoteIpep.Address, remoteIpep.Port); // 发送到的IP地址和端口号
                            }
                            else if (sendDataRemoteInfo.Address != remoteIpep.Address ||
                                                  sendDataRemoteInfo.Port != remoteIpep.Port)
                            {
                                sendDataRemoteInfo.Address = remoteIpep.Address;
                                sendDataRemoteInfo.Port = remoteIpep.Port;
                            }

                            if (onNetRecvListener != null)
                            {
                                onNetRecvListener(bytRecv, bytRecv.Length, remoteIpep);
                            }
                        }
                           
                    }
                    catch (System.Net.Sockets.SocketException sockEx)
                    {
                        Close();
                        if (onNetErrorListener != null)
                        {
                            onNetErrorListener("udp server recv error", sockEx);
                        }
                        break;
                    }
                }
                catch (Exception ex)
                {
                    Close();
                    if (onNetErrorListener != null)
                    {
                        onNetErrorListener("udp server recv error ", ex);
                    }
                    break;
                }
            }
        }

        public void SetOnNetErrorListener(OnNetErrorListener listener)
        {
            onNetErrorListener = listener;
        }

        public void SetOnNetRecvListener(OnNetRecvListener listener)
        {
            onNetRecvListener = listener;
        }

        public bool IsOpen()
        {
            return (isOpen);
        }

        public void SetOnNetTcpConnectedListener(OnNetTcpConnectedListener listener)
        {
            //do nothing
        }
    }
}
