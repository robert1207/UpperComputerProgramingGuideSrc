using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HYKT
{
    class NetManager
    {
        private Comm comm = null;

        private OnNetRecvListener onNetRecvListener = null;
        private OnNetErrorListener onNetErrorListener = null;
        private OnNetTcpConnectedListener onNetTcpConnectedListener = null;

        public NetManager() {

        }

        public static String[] GetNetTypeStrList() {
            return CommNetType.GetNetTypeStrList();
        }

        public static CommNetType.NetType GetNetTypeByIndex(int index) {
            return CommNetType.GetNetTypeByIndex(index);
        }

        public bool Open(CommNetType.NetType netType, string addr, int port)
        {
            if (netType == CommNetType.NetType.UDP_broadcast)
            {
                comm = new UdpBroadCastComm();
            }
            else if (netType == CommNetType.NetType.UDP_client)
            {
                comm = new UdpClientComm();
            }
            else if (netType == CommNetType.NetType.UDP_server)
            {
                comm = new UdpServerComm();
            }
            else if (netType == CommNetType.NetType.TCP_client)
            {
                comm = new TcpClientComm();
            }
            else if (netType == CommNetType.NetType.TCP_server)
            {
                comm = new TcpServerComm();
            }

            comm.SetOnNetRecvListener(onNetRecvListener);
            comm.SetOnNetErrorListener(onNetErrorListener);
            comm.SetOnNetTcpConnectedListener(onNetTcpConnectedListener);

            return comm.Open(addr, port);
        }

        public void Close() {
            if (comm != null) {
                comm.Close();
                comm = null;
            }
        }

        public bool IsOpen() {
            if (comm == null) return false;
            return comm.IsOpen();
        }

        public bool Send(byte[] data) {
            return comm.Send(data);
        }

        public void SetOnNetRecvListener(OnNetRecvListener listener) {
            onNetRecvListener = listener;
        }

        public void SetOnNetErrorListener(OnNetErrorListener listener) {
            onNetErrorListener = listener;
        }

        public void SetOnNetTcpConnectedListener(OnNetTcpConnectedListener listener)
        {
            onNetTcpConnectedListener = listener;
        }


    }
}
