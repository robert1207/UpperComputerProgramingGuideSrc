using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading;
using System.Timers;


namespace HYKT
{
    class ProtocolManager
    {
        private const string TAG = "ProtocolManager";
        private NetManager netManater;
        private static WorkManager wm;
        private static System.Timers.Timer aTimer = null;
        private const int DataTranferTimeoutTime = 4000;


        private Thread mythread;
        private static bool isRun = false;
        private static bool waitResponse = false;
        private Work work = null;

        private bool package_on = false;
        private byte[] cache;
        private int pos = 0;
        private static readonly int CACHE_LENGTH = 1024 * 5;

        private static readonly int ErrorCodeNetError = -1;
        private static readonly int ErrorCodeFailed3TimesError = -2;
        private static readonly int ErrorCodeCrcError = -3;

        public delegate void OnProtocolRecvListener(byte[] pkg);
        public delegate void OnProtocolErrorListener(int code, string reason);
        public event OnProtocolRecvListener eventProtocolRecvHandler;
        public event OnProtocolErrorListener eventProtocolErrorHandler;

        private void CallProtocolRecv(byte[] pkg) {
            if(eventProtocolRecvHandler != null)
            {
                eventProtocolRecvHandler.Invoke(pkg);
            }
        }

        private void CallProtocolError(int code, string reason)
        {
            if (eventProtocolErrorHandler != null)
            {
                eventProtocolErrorHandler.Invoke(code, reason);
            }
        }

        public delegate void onGetMachinetemperature(int value);
        public delegate void onReportValue(int value);

        private onGetMachinetemperature getMachinetemperatureListener = null;
        private onReportValue onReportValueListener = null;

        public void SetOnGetMachineTemperatureListener(onGetMachinetemperature l ) { getMachinetemperatureListener = l; }
        public void SetOnReportValueListener(onReportValue l) { onReportValueListener = l; }



        private ProtocolManager() {
            Init();
        }

        private static ProtocolManager instance = null;
        public static ProtocolManager GetInstance() {
            if (instance == null) {
                instance = new ProtocolManager();
            }
            return instance;
        }

        public static void CleanInstance()
        {
            if (wm != null) {
                wm.CleanWorkList();
            }
        }

        private void Init() {
            cache = new byte[CACHE_LENGTH];

            wm = new WorkManager();
            netManater = new NetManager();
            netManater.SetOnNetRecvListener(OnNetRecvListener);
            netManater.SetOnNetErrorListener(OnNetErrorListener);

            StartWorkThread();
        }

        /*********************************** work manager **********************************/
        public void AddWork(byte[] data)
        {
            wm.AddWork(data);
            if (IsThreadWorking() == false)
            {
                StartWorkThread();
            }
        }

        public void CleanWorkList()
        {
            wm.CleanWorkList();
        }
        public bool IsHasWork()
        {
            return wm.IsHasWork();
        }

        /********************************** timer *********************************/
        private void StartTimer() {
            if (aTimer != null && aTimer.Enabled == false)
            {
                aTimer.Enabled = true;
            }
            else
            {
                aTimer = new System.Timers.Timer(DataTranferTimeoutTime);
                aTimer.Elapsed += new ElapsedEventHandler(OnTimedEvent);
                aTimer.AutoReset = false;
            }
        }

        private void StopTimer() {
            aTimer.Enabled = false;
        }

        private void OnTimedEvent(object source, ElapsedEventArgs e)
        {
            ProcessResult(null);//send a empty pkg
        }

        /***************************** thread **************************************/
        private void StartWorkThread() {
            mythread = null;
            mythread = new Thread(ThreadWork);
            isRun = true;
            mythread.Start();
        }

        private static void StopWorkThread() {
            waitResponse = false;
            isRun = false;
        }

        private bool IsThreadWorking() {
            return isRun;
        }

        private void ThreadWork()
        {
            while (isRun) {
                work = wm.GetWork();
                if (work != null)
                {
                    Send(work.Data);
                    waitResponse = true;
                }
                else { //end of all work
                    StopWorkThread();
                }

                while (waitResponse) {
                    Thread.Sleep(1);
                }
            }
        }

        /******************************** connection functions *****************************/
        public bool Connect(string addr, int port) {
            return netManater.Open(CommNetType.NetType.UDP_client, addr, port);
        }

        public void DisConnect() {
            netManater.Close();
        }

        public bool IsConnected()
        {
            return netManater.IsOpen();
        }

        public void Send(byte[] data)
        {
            netManater.Send(data);
            StartTimer();//set a timer for response timeout
        }

        private void OnNetRecvListener(byte[] data, int length, IPEndPoint iped)
        {
            for (int a = 0; a < length; a++)
            {
                Process(data[a]);
            }
        }

        private void OnNetErrorListener(string reasonStr, Exception e)
        {
            CallProtocolError(ErrorCodeNetError, reasonStr);
        }

        private void Process(byte b) {
            if (package_on == true)
            {
                if (pos > CACHE_LENGTH) {
                    package_on = false;
                    pos = 0;
                    return;
                }

                cache[pos++] = b;
                if (pos > 4 &&
                    cache[pos - 4] == Command.tail[0] &&    //a pkg is finished
                    cache[pos - 3] == Command.tail[1] &&
                    cache[pos - 2] == Command.tail[2] &&
                    cache[pos - 1] == Command.tail[3] &&
                    cache[Command.head.Length] + Command.head.Length + Command.tail.Length == pos //check pkg len
                    ) {
                    package_on = false;

                    byte[] temp = cache.Take(pos - 4).ToArray();//remove tail' bytes
                    byte[] pkg = temp.Skip(2).ToArray();//remove head byte and pkg-len byte

                    if (CRC16.CheckCRC(pkg) == true)
                    {
                        ProcessResult(pkg.Take(pkg.Length - 2).ToArray());//remove crc's bytes
                    }
                    else
                    {
                        CleanWorkList();
                        CallProtocolError(ErrorCodeCrcError, "crc check error");
                    }
                }
            }
            else if (package_on == false && b == Command.head[0]) { //start a pkg
                package_on = true;
                pos = 0;
                cache[pos++] = b;
            }
        }


        static object _object = new object();// for locker
        private void ProcessResult(byte[] pkg)
        {
            lock (_object)
            {
                //根据指令类型码判断，如果是下位机主动反馈指令，在这里拦截判断，else 再执行以下判断
                if (Command.IsCommandIsReportingType(pkg))
                {
                    DispatchPackage(pkg);
                    return;
                }

                if (waitResponse == false) return;

                //检验下位机对上位机命令的反馈指令是否正确
                if (pkg != null && work.CheckResponse(pkg) == true)
                {
                    StopTimer();
                    wm.FinishAWork();
                    DispatchPackage(pkg);
                    CallProtocolRecv(pkg);
                    waitResponse = false;
                }
                else
                {
                    StopTimer();
                    //mark timeout
                    if (work != null)
                    {
                        work.FailedTimes++;
                        if (work.FailedTimes >= 3)
                        {
                            CleanWorkList();
                            netManater.Close();
                            CallProtocolError(ErrorCodeFailed3TimesError, "re-send 3 times error");
                        }
                    }
                    waitResponse = false;
                }
            }
        }

        //对于接收下位反馈给上位机数据的指令，在此函数中获取数据
        private void DispatchPackage(byte[] pkg)
        {
            if (pkg.Length < 2) return;

            if (Command.IsCommandReportValue(pkg))
            {
                netManater.Send(Command.ResponseForReportValue());//give response immediately
                if (onReportValueListener != null) {
                    onReportValueListener(Command.GetReportValue(pkg));
                }
            }

            //根据不同指令，调用对应的处理函数，并调用其回调函数，如果有必要的时候
            if (Command.IsCommandGetMachinetemperature(pkg))
            {
                if (getMachinetemperatureListener != null) {
                    getMachinetemperatureListener(Command.GetValueOfGetMachinetemperature(pkg));
                }
            }
        }


    }
}
