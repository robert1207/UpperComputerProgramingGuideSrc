using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace HYKT
{
    //定义一个委托 : 相当于，c++的函数指针

    //接收到数据回调函数
    public delegate void OnNetRecvListener(byte[] data, int length, IPEndPoint iped); 

    //当通信连接意外中断回调函数
    public delegate void OnNetErrorListener(string reasonStr, Exception e);

    //tcp连接建立结果回调函数
    public delegate void OnNetTcpConnectedListener();

    interface Comm
    {
        /// <summary>
        /// 建立通讯
        /// </summary>
        /// <param name="addr"></param>
        /// <param name="port"></param>
        /// <returns></returns>
        bool Open(string addr, int port);

        /// <summary>
        /// 关闭通讯
        /// </summary>
        void Close();

        /// <summary>
        /// 是否打开
        /// </summary>
        /// <returns></returns>
        bool IsOpen();

        /// <summary>
        /// 发送数据
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        bool Send(byte[] data);

        /// <summary>
        /// 设置接收回调函数,用于正常数据接收并按照协议解析处理
        /// </summary>
        /// <param name="listener"></param>
        void SetOnNetRecvListener(OnNetRecvListener listener);

        /// <summary>
        ///  当通信连接意外中断
        /// </summary>
        void SetOnNetErrorListener(OnNetErrorListener listener);

        /// <summary>
        ///  tcp连接建立结果回调函数
        /// </summary>
        void SetOnNetTcpConnectedListener(OnNetTcpConnectedListener listener);


    }
}
