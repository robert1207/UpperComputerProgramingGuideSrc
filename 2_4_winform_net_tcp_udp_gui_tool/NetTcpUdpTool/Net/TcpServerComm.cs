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
    class TcpServerComm : Comm
    {
        private OnNetRecvListener onNetRecvListener = null;
        private OnNetErrorListener onNetErrorListener = null;
        private OnNetTcpConnectedListener onNetTcpConnectedListener = null;


        private TcpListener tcpListener;
        private TcpClient tcpClient;

        private Thread thrRecv;

        private bool isOpen = false;

        private NetworkStream stream = null;
        private IPEndPoint remoteIpep = null;




        /// <summary>
        /// 
        /// </summary>
        /// <param name="addr">none</param>
        /// <param name="port">need : listen port</param>
        /// <returns></returns>
        public bool Open(string addr, int port)
        {
            remoteIpep = new IPEndPoint(IPAddress.Any, 0);

            //listen the port
            IPEndPoint ipLocalEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), port);
            tcpListener = new TcpListener(ipLocalEndPoint);
            tcpListener.Start();

            tcpListener.BeginAcceptTcpClient(new AsyncCallback(DoAcceptTcpclient), tcpListener);//异步接收 递归循环接收多个客户端

            isOpen = true;
            return true;
        }

        //异步回调方法
        private void DoAcceptTcpclient(IAsyncResult ar)
        {
            TcpListener listener = (TcpListener)ar.AsyncState;
            tcpClient = listener.EndAcceptTcpClient(ar);

            stream = tcpClient.GetStream();
            thrRecv = new Thread(ReceiveMessageThread);
            thrRecv.Start();

            if (onNetTcpConnectedListener != null) {
                onNetTcpConnectedListener();
            }
            // server.BeginAcceptTcpClient(new AsyncCallback(DoAcceptTcpclient), server);
        }

        public void Close()
        {
            isOpen = false;//this will kill the thread
            if (stream != null) stream.Close();
            if (tcpClient != null) tcpClient.Close();
        }

        public bool Send(byte[] data)
        {
           // Char[] c_data = Encoding.ASCII.GetChars(data);
          // Console.WriteLine("----1"+ new string(c_data));
            try
            {
                try
                {
                    if (tcpClient.Connected)
                    {
                   //     Char[] c_data2 = Encoding.ASCII.GetChars(data);
                     //   Console.WriteLine("----2" + new string(c_data2));

                        stream.Write(data, 0, data.Length);
                        return true;
                    }
                    else
                    {
                        Close();
                        if (onNetErrorListener != null)
                        {
                            onNetErrorListener("tcp server send error", new Exception("none"));
                        }
                    }
                }
                catch (System.Net.Sockets.SocketException sockEx)
                {
                    Close();
                    if (onNetErrorListener != null)
                    {
                        onNetErrorListener("tcp server send error", sockEx);
                    }
                }
            }
            catch (Exception e)
            {
                Close();
                if (onNetErrorListener != null)
                {
                    onNetErrorListener("tcp server send error", e);
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
                                onNetErrorListener("tcp server recv error", new Exception("exception of null instance "));
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
                            onNetErrorListener("tcp server recv error", sockEx);
                        }
                        break;
                    }
                }
                catch (Exception ex)
                {
                    Close();
                    if (onNetErrorListener != null)
                    {
                        onNetErrorListener("tcp server recv error", ex);
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
