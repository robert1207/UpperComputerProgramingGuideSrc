using System;
using System.Collections.Generic;
using System.IO.Ports;

namespace winform_serial_port_gui_tool
{
    //用于自己调用回调函数使用，在namespace下定义，可作为函数参数类型使用。
    //相当于，c++的函数指针
    public delegate void RecvListener(byte[] data, int length); //定义一个委托

    class SerialComm
    {
        private SerialPort ComDevice;
        private static SerialComm mInstance = null;
        private RecvListener recvListener = null;

        private readonly static String[] baudRateStrList = { "1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200" };
        private readonly static String[] dataBitsStrList = { "5", "6", "7", "8" };
        private readonly static String[] parityStrList = { "None", "Odd", "Even", "Mark", "Space" };
        private readonly static String[] stopBitsStrList = { "0", "1", "2", "1.5" };

        public SerialComm()
        {
            ComDevice = new SerialPort();
        }

        public void SetRecvListener(RecvListener listener)
        {
            recvListener = listener;
        }

        public bool Open()
        {
            try
            {
                Console.WriteLine("##### open serial port");
                ComDevice.DataReceived += new SerialDataReceivedEventHandler(Com_DataReceived);
                ComDevice.Open();
                if (ComDevice.IsOpen == true)
                {
                    return true;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("未能成功开启串口" + ex.Message);
                //MessageBox.Show(ex.Message, "未能成功开启串口", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            return false;
        }

        public void Close()
        {
            try
            {
                Console.WriteLine("##### close serial port");
                if (ComDevice.IsOpen)
                {
                    ComDevice.DataReceived -= new SerialDataReceivedEventHandler(Com_DataReceived);
                    ComDevice.Dispose();
                    ComDevice.Close();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("串口关闭错误" + ex.Message);
            }
        }

        public bool IsOpen() {
            return ComDevice.IsOpen;
        }

        public bool Send(byte[] data)
        {
            if (ComDevice.IsOpen)
            {
                try
                {
                    ComDevice.Write(data, 0, data.Length);
                    return true;
                }
                catch (Exception ex)
                {
                    Console.WriteLine("发送失败" + ex.Message);
                }
            }
            else
            {
                Console.WriteLine("串口未开启");
            }
            return false;
        }

        public bool Send(char[] data)
        {
            if (ComDevice.IsOpen)
            {
                try
                {
                    ComDevice.Write(data, 0, data.Length);
                    return true;
                }
                catch (Exception ex)
                {
                    Console.WriteLine("发送失败" + ex.Message);
                }
            }
            else
            {
                Console.WriteLine("串口未开启");
            }
            return false;
        }

        private void Com_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int length = ComDevice.BytesToRead;
            byte[] ReDatas = new byte[length];
            ComDevice.Read(ReDatas, 0, ReDatas.Length);

            if (recvListener != null)
            {
                recvListener(ReDatas, length);
            }
        }

        //*************************** serial property settings ***************************/
        public void SetSerialPortName(string portName) {
            ComDevice.PortName = portName;
        }

        public void SetSerialBaudRate(int rate) {
            ComDevice.BaudRate = rate;
        }

        public void SetSerialDataBits(int dataBits) {
            ComDevice.DataBits = dataBits;
        }

        public void SetSerialParity(Parity parity) {
            ComDevice.Parity = parity;
        }

        public void SetSerialStopBits(StopBits stopBits) {
            ComDevice.StopBits = stopBits;
        }

        //*************************** get str list for show on ui ***************************/
        public string[] GetSerialDeviceStrList()
        {
            return SerialPort.GetPortNames();
        }

        public String[] GetSerialBaudRateStrList()
        {
            return baudRateStrList;
        }

        public String[] GetSerialDataBitsStrList()
        {
            return dataBitsStrList;
        }

        public String[] GetSerialParityStrList()
        {
            return parityStrList;
        }

        public String[] GetSerialStopBitsStrList()
        {
            return stopBitsStrList;
        }

        //*************************** get read serial property from index ***************************/
        public static int GetBaudRateByIndex(int index) {
            return Convert.ToInt32(baudRateStrList[index]);
        }

        public static int GetDataBitsByIndex(int index) {
            return Convert.ToInt32(dataBitsStrList[index]);
        }

        public static Parity GetParityByIndex(int index) {
            // "None", "Odd", "Even", "Mark", "Space" };
            switch (index) {
                case 0: return Parity.None;
                case 1: return Parity.Odd;
                case 2: return Parity.Even;
                case 3: return Parity.Mark;
                case 4: return Parity.Space;
                default: return Parity.None;
            }
        }

        public static StopBits GetStopBitsByIndex(int index) {
            // "0", "1", "2", "1.5"
            switch (index)
            {
                case 0: return StopBits.None;
                case 1: return StopBits.One;
                case 2: return StopBits.Two;
                case 3: return StopBits.OnePointFive;
                default: return StopBits.None;
            }
        }






    }
}
