using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace NetTcpUdpTool.Net
{
    class TcpClientComm : Comm
    {
        private OnNetRecvListener onNetRecvListener = null;
        private OnNetErrorListener onNetErrorListener = null;
        private OnNetTcpConnectedListener onNetTcpConnectedListener = null;

        private TcpClient tcpClient;
        private Thread thrRecv;

        private bool isOpen = false;

        NetworkStream stream = null;
        IPEndPoint remoteIpep = null;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="addr">need: des ip</param>
        /// <param name="port">need: des port</param>
        /// <returns></returns>
        public bool Open(string addr, int port)
        {
            remoteIpep = new IPEndPoint(IPAddress.Any, 0);

            tcpClient = new TcpClient();//bing port at the param if needed
            try {
                tcpClient.Connect(IPAddress.Parse(addr), port);

            } catch (System.Net.Sockets.SocketException ex) {
                if (onNetErrorListener != null)
                {
                    onNetErrorListener("tcp client open error ", ex);
                }
                return false;
            }

            stream = tcpClient.GetStream();

            thrRecv = new Thread(ReceiveMessageThread);
            thrRecv.Start();
            isOpen = true;

            if (onNetTcpConnectedListener != null)
            {
                onNetTcpConnectedListener();
            }

            return true;
        }

        public void Close()
        {
            isOpen = false;//this will kill the thread
            if (stream != null) stream.Close();
            if (tcpClient != null) tcpClient.Close();
        }

        public bool Send(byte[] data)
        {
            try
            {
                try
                {
                    if (tcpClient.Connected)
                    {
                        stream.Write(data, 0, data.Length);
                        return true;
                    }
                    else {
                        Close();
                        if (onNetErrorListener != null)
                        {
                            onNetErrorListener("tcp client send error ", new Exception("none"));
                        }
                    }
                }
                catch (System.Net.Sockets.SocketException sockEx)
                {
                    Close();
                    if (onNetErrorListener != null)
                    {
                        onNetErrorListener("tcp client send error ", sockEx);
                    }
                }
            }
            catch (Exception e)
            {
                Close();
                if (onNetErrorListener != null)
                {
                    onNetErrorListener("tcp client send error " , e);
                }
            }
            return false;
        }

        private void ReceiveMessageThread(object obj)
        {
           
            while (isOpen)
            {
                try
                {
                    try
                    {

                        if (tcpClient == null)
                        {
                            Close();
                            if (onNetErrorListener != null)
                            {
                                onNetErrorListener("tcp client recv error", new Exception("exception of null instance "));
                            }
                            break;
                        }
                        if (tcpClient.Available <= 0)
                        {
                            Thread.Sleep(10);
                        }
                        else
                        {
                            int stdBufferSize = tcpClient.ReceiveBufferSize;

                            Byte[] buffer = new Byte[stdBufferSize];
                            Int32 readLen = stream.Read(buffer, 0, buffer.Length);

                            if (onNetRecvListener != null)
                            {
                                onNetRecvListener(buffer, readLen, remoteIpep);
                            }
                        }
                       
                    }
                    catch (System.Net.Sockets.SocketException sockEx)
                    {
                        Close();
                        if (onNetErrorListener != null)
                        {
                            onNetErrorListener("tcp client recv error " , sockEx);
                        }
                        break;
                    }
                }
                catch (Exception ex)
                {
                    Close();
                    if (onNetErrorListener != null)
                    {
                        onNetErrorListener("tcp client recv error ", ex);
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
            return (isOpen && tcpClient.Connected);
        }

        public void SetOnNetTcpConnectedListener(OnNetTcpConnectedListener listener)
        {
            onNetTcpConnectedListener = listener;
        }
    }
}
