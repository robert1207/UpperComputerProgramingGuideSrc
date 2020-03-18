using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HYKT
{
    class CommNetType
    {
        private readonly static String[] net_type_str_array = {
            "UDP broadcast",
            "UDP client",
            "UDP server",
            "TCP client",
            "TCP server"
        };

        public enum NetType
        {
            UDP_broadcast,
            UDP_client,
            UDP_server,
            TCP_client,
            TCP_server
        };

        /// <summary>
        /// 获取网络类型文字列表
        /// </summary>
        /// <returns></returns>
        public static String[] GetNetTypeStrList() {
            return net_type_str_array;
        }

        public static NetType GetNetTypeByIndex(int index) {
            switch (index) {
                case 0: return NetType.UDP_broadcast;
                case 1: return NetType.UDP_client;
                case 2: return NetType.UDP_server;
                case 3: return NetType.TCP_client;
                case 4: return NetType.TCP_server;
            }
            return NetType.UDP_broadcast;
        }

    }
}
