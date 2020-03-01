
using System;
using System.Linq;

namespace HYKT
{
    class Protocol
    {
        public static readonly  byte[] head = { 0xee };
        public static readonly byte[] tail = { 0xbb };


        private static byte[] ProtocolPack(byte[] data) {
            byte[] ret = { };
            byte[] crc16 = { };

            crc16 = CRC16.GetCRC(data);

            ret = ret.Concat(head).ToArray();
            ret = ret.Concat(data).ToArray();
            ret = ret.Concat(crc16).ToArray();
            ret = ret.Concat(tail).ToArray();

            return ret;
        }

        //需要没有包头，没有包尾的数据
        public static bool CrcCheck(byte[] data) {
          
            return CRC16.CheckCRC(data) ;
        }

        /********************************************  search net device  *********************/
        public static byte[] SearchNetDevice()
        {
            byte[] data = { 0x01 }; 
            return ProtocolPack(data);
        }



    }
}
