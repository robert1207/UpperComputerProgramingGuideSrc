using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.NetworkInformation;

namespace NetTcpUdpTool.Net
{
    class NetUtil
    {
        const string TAG = "NetUtil";

        public static bool IsPortInUse(IPAddress ipAddr, int port)
        {
            bool inUse = false;
            IPGlobalProperties ipProperties = IPGlobalProperties.GetIPGlobalProperties();
            // IPEndPoint[] ipEndPoints = ipProperties.GetActiveTcpListeners();
            IPEndPoint[] ipEndPointsUdp = ipProperties.GetActiveUdpListeners();

            foreach (IPEndPoint endPoint in ipEndPointsUdp)
            {
                if (ipAddr == endPoint.Address && endPoint.Port == port)
                {
                    inUse = true;
                    break;
                }
            }

           // LogUtil.Log.d(TAG, "ip=" + ipAddr.ToString() + "   port=" + port + "  inUse=" + inUse);


            return inUse;
        }

        public static bool IsPortInUse(int port)
        {
            bool inUse = false;
            IPGlobalProperties ipProperties = IPGlobalProperties.GetIPGlobalProperties();
            // IPEndPoint[] ipEndPoints = ipProperties.GetActiveTcpListeners();
            IPEndPoint[] ipEndPointsUdp = ipProperties.GetActiveUdpListeners();

            foreach (IPEndPoint endPoint in ipEndPointsUdp)
            {
                if (endPoint.Port == port)
                {
                    inUse = true;
                    break;
                }
            }

            //  LogUtil.Log.d(TAG, "jsut port  port=" + port + "  inUse=" + inUse);
            return inUse;
        }

    }
}
