using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HYKT
{
    class HexFormatUtils
    {
        public static byte[] String2HexByte(string hexString)
        {
            try {
                hexString = hexString.Replace(" ", "");
                if ((hexString.Length % 2) != 0) hexString += " ";
                byte[] returnBytes = new byte[hexString.Length / 2];
                for (int i = 0; i < returnBytes.Length; i++)
                    returnBytes[i] = Convert.ToByte(hexString.Substring(i * 2, 2).Replace(" ", ""), 16);
                return returnBytes;
            } catch (System.FormatException ex) {
                byte[] returnBytes = null;
                return returnBytes;
            }
        }

        public static string HexByte2String(byte [] data) {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < data.Length; i++)
            {
                sb.AppendFormat("{0:x2}" + " ", data[i]);
            }

            return sb.ToString().ToUpper();
        }

       
   



    }
}
