using System;
using System.Linq;

namespace HYKT
{
    class Command
    {
        public static readonly  byte[] head = { 0xff };
        public static readonly byte[] tail = { 0xee, 0xfc, 0xff, 0xea };

        private static byte[] Pack(byte[] data) {
            byte[] ret = { };
            byte[] empty = { 0x00 };//for pkg-len
            byte[] crc16 = CRC16.GetCRC(data);

            ret = ret.Concat(head)
                .Concat(empty)
                .Concat(data)
                .Concat(crc16)
                .Concat(tail).ToArray();

            int pkg_len = ret.Length - head.Length - tail.Length;
            ret[head.Length] = (byte)pkg_len;
            return ret;
        }

        public enum CommandType {
            SetValue = 0x01,        //上位机给下位设置数据的命令类型
            GetValue = 0x02,        //上位机从下位机获取数据的命令类型
            ReportValue = 0x03      //下位机主动给上位机上报数据的命令类型
        }

        public static bool IsCommandIsReportingType(byte[] pkg)
        {
            return (int)CommandType.ReportValue == pkg[0];
        }
        /********************************************  Commands *****************************************/

        public static byte[] SearchNetDevice()
        {
            byte[] data = { (byte)CommandType.SetValue, 0x01 };
            return Pack(data);
        }

        //e.g. SetValue command type
        public static byte[] SendSetPositionValue(int value)
        {
            byte[] Data = { (byte)CommandType.SetValue, 0x01 };//commandTypeCode , commandCode
            int t1 = value / 100 + 48;
            int t2 = value % 100 / 10 + 48;
            int t3 = value % 10 + 48;

            byte[] dd = new byte[3];
            dd[0] = (byte)t1;
            dd[1] = (byte)t2;
            dd[2] = (byte)t3;
            Data = Data.Concat(dd).ToArray();

            return Pack(Data);
        }

        //e.g. GetValue command type
        public static byte[] SendGetMachinetemperature()
        {
            byte[] Data = { (byte)CommandType.GetValue, 0x01 };//commandTypeCode , commandCode
            return Pack(Data);
        }

        public static bool IsCommandGetMachinetemperature(byte[] pkg)
        {
            if (pkg[0] == (byte)CommandType.GetValue && pkg[1] == 0x01) return true; return false;
        }

        public static int GetValueOfGetMachinetemperature(byte[] pkg)
        {
            int value = (pkg[2] - 48) * 100 + (pkg[3] - 48) * 10 + (pkg[4] - 48);
            return value;
        }

        //e.g. ReportValue command type
        public static byte[] ResponseForReportValue()
        {
            byte[] Data = { (byte)CommandType.ReportValue, 0x01 };//commandTypeCode , commandCode
            return Pack(Data);
        }

        public static bool IsCommandReportValue(byte[] pkg)
        {
            if (pkg[0] == (byte)CommandType.ReportValue && pkg[1] == 0x01) return true; return false;
        }

        public static int GetReportValue(byte[] pkg)
        {
            int value = (pkg[2] - 48) * 100 + (pkg[3] - 48) * 10 + (pkg[4] - 48);
            return value;
        }



    }
}
