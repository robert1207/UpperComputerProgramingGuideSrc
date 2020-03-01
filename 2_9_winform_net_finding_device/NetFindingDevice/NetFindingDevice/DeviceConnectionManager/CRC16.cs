using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace HYKT
{
    class CRC16
    {

        public static byte[] GetCRC(byte[] data) {

            UInt16 i,  j,  carry_flag,  a;
            UInt16 ret = 0xffff;

            int len = data.Length;

            for (i = 0; i < len; i++) {
                ret = (UInt16)( ret ^ data[i]);
                for (j = 0; j < 8; j++) {
                    a = ret;
                    carry_flag = (UInt16)(a & 0x0001);
                    ret = (UInt16)(ret >> 1);
                    if (carry_flag == 1) {
                        ret = (UInt16)(ret ^ 0xa001);
                    }
                }
            }

            byte[] rett = { 0,0 };
            rett[0] = (byte)((ret & 0xff00) >> 8);//high 8
            rett[1] = (byte)(ret & 0x00ff);//low 8

            return rett;
        }

        public static bool CheckCRC(byte[] data) {
            int len =  data.Length;
            if (len < 2) return false;

            byte crcLow = data[len - 1];
            byte crcHigh = data[len - 2];

            byte[] orgData = data.Take(len - 2).ToArray();//  2:crc
            byte[] crc = GetCRC(orgData);

            if (crc.Length < 2) {
                return false;
            }

            if (crcLow == crc[1] && crcHigh == crc[0]) {
                return true;
            }

            return false;
        }
    }
}
