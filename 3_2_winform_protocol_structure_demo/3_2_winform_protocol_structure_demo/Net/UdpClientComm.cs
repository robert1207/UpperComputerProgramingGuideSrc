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
    class UdpClientComm : Comm
    {

        private OnNetRecvListener onNetRecvListener = null;
        private OnNetErrorListener onNetErrorListener = null;

        private UdpClient udpClient;
        private Thread thrRecv;

        private bool isOpen = false;
        private IPEndPoint sendDataRemoteInfo;

        public void SetOnNetErrorListener(OnNetErrorListener listener)
        {
            onNetErrorListener = listener;
        }

        public void SetOnNetRecvListener(OnNetRecvListener listener)
        {
            onNetRecvListener = listener;
        }

        public bool Open(string addr, int port)
        {
            sendDataRemoteInfo = new IPEndPoint(IPAddress.Parse(addr), port); // 发送到的IP地址和端口号
            udpClient = new UdpClient();

            thrRecv = new Thread(ReceiveMessageThread);
            thrRecv.Start();
            isOpen = true;

            return true;
        }

        public void Close()
        {
            isOpen = false;//this will kill the thread
            if (udpClient != null)
            {
                udpClient.Close();
            }
        }

        public bool Send(byte[] data)
        {
            //  byte[] sendbytes = data;// Encoding.UTF8.GetBytes("hahahaha222222222222");
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
                        onNetErrorListener("udp client send error", sockEx);
                    }
                }
            }
            catch (Exception e)
            {
                Close();
                if (onNetErrorListener != null)
                {
                    onNetErrorListener("udp client send error", e);
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
                        if (udpClient == null) {
                            Close();
                            if (onNetErrorListener != null)
                            {
                                onNetErrorListener("udp client recv error", new Exception("exception of null instance "));
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
                            onNetErrorListener("udp client recv error 1", sockEx);
                        }
                        break;
                    }
                }
                catch (Exception ex)
                {
                    Close();
                    if (onNetErrorListener != null)
                    {
                        onNetErrorListener("udp client recv error 2", ex);
                    }
                    break;
                }
            }
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
