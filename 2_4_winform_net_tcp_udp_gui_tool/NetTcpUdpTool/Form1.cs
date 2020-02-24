using NetTcpUdpTool.Net;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NetTcpUdpTool
{
    public partial class Form1 : Form
    {

        private NetManager netManager = null;
        public Form1()
        {
            InitializeComponent();

            netManager = NetManager.GetInstance();
            netManager.SetOnNetErrorListener(OnNetErrorListener);
            netManager.SetOnNetRecvListener(OnNetRecvListener);
            netManager.SetOnNetTcpConnectedListener(OnNetTcpConnectedListener);

            InitUI();
        }

        private void InitUI() {
            comboBoxNetType.Items.AddRange(NetManager.GetNetTypeStrList());
            comboBoxNetType.SelectedIndex = 0;
            textBoxNetDesIp.Text  = "127.0.0.1";
            textBoxNetDesPort.Text = "2009";
            buttonSend.Enabled = false;
        }

        private void SetNetTypeStatus(bool is_enable)
        {
            comboBoxNetType.Enabled = is_enable;
            textBoxNetDesIp.Enabled = is_enable;
            textBoxNetDesPort.Enabled = is_enable;
        }

        private void SetOpenBtnStatus(bool is_open)
        {
            if (is_open)
            {
                buttonOpen.Text = "Open";
            }
            else
            {
                buttonOpen.Text = "Close";
            }
        }

        private void ShowEditDesIp(bool is_show)
        {
            if (is_show)
            {
                textBoxNetDesIp.Show();
                labelNetIp.Show();
            }
            else
            {
                textBoxNetDesIp.Hide();
                labelNetIp.Hide();
            }
        }

        private void SetEditPortTextInListen(bool is_listen)
        {
            if (is_listen)
            {
                labelNetPort.Text = "Listen Port:";
            }
            else
            {
                labelNetPort.Text = "Destination Port:";
            }
        }

        private void ComboBoxNetType_SelectedIndexChanged(object sender, EventArgs e)
        {
            int index = comboBoxNetType.SelectedIndex;
            CommNetType.NetType type = NetManager.GetNetTypeByIndex(index);

            switch (type)
            {
                case CommNetType.NetType.UDP_broadcast:
                    ShowEditDesIp(false);
                    SetEditPortTextInListen(false);
                    break;
                case CommNetType.NetType.UDP_client:
                    ShowEditDesIp(true);
                    SetEditPortTextInListen(false);
                    break;
                case CommNetType.NetType.UDP_server:
                    ShowEditDesIp(false);
                    SetEditPortTextInListen(true);
                    break;
                case CommNetType.NetType.TCP_client:
                    ShowEditDesIp(true);
                    SetEditPortTextInListen(false);
                    break;
                case CommNetType.NetType.TCP_server:
                    ShowEditDesIp(false);
                    SetEditPortTextInListen(true);
                    break;
            }
        }

        private void ButtonOpen_Click(object sender, EventArgs e)
        {
            if (netManager.IsOpen()) //IsOPen
            { //do close
                netManager.Close();
                SetOpenBtnStatus(true);
                SetNetTypeStatus(true);

                buttonSend.Enabled = false;
            }
            else
            { //do open

                string des_ip = textBoxNetDesIp.Text;
                string des_port = textBoxNetDesPort.Text;

                if (des_ip == String.Empty)
                {
                    MessageBox.Show("Please set destination IP !", "Warning");
                    return;
                }

                if (des_port == String.Empty)
                {
                    MessageBox.Show("Please set destination port !", "Warning");
                    return;
                }

                //net type
                int index = comboBoxNetType.SelectedIndex;
                CommNetType.NetType netType = NetManager.GetNetTypeByIndex(index);

                int port = int.Parse(des_port);
                if (netManager.Open(netType, des_ip, port)) {
                    SetOpenBtnStatus(false);
                    SetNetTypeStatus(false);
                    if (netType == CommNetType.NetType.UDP_broadcast ||
                        netType == CommNetType.NetType.UDP_client ||
                        netType == CommNetType.NetType.UDP_server)
                    {
                        buttonSend.Enabled = true;
                    }
                }
            }
        }

        private void ButtonSend_Click(object sender, EventArgs e)
        {

            if (!netManager.IsOpen())
            {
                MessageBox.Show("Please click 'open' button first !");
                return;
            }

            string send_str = textBoxNetSend.Text;

            if (send_str == String.Empty)
            {
                MessageBox.Show("Please input sending string !");
                return;
            }

            if (checkBoxNetSendHex.Checked)
            {
                byte[] data = HexFormatUtils.String2HexByte(send_str);
                if (data != null)
                {
                    netManager.Send(data);
                }
                else {
                    MessageBox.Show("Please input just hex strings. e.g. 1A ff 06");
                }
            }
            else
            {
                Encoding encodingGB2312 = Encoding.GetEncoding("gb2312");
                Byte[] byte_array = encodingGB2312.GetBytes(send_str.ToCharArray()); //Encoding.Default.GetBytes(send_str.ToCharArray());
                netManager.Send(byte_array);
            }
        }

        private void OnNetRecvListener(byte[] data, int length, IPEndPoint iped) {
            if (checkBoxNetRecvHex.Checked)
            {
                BeginInvoke(new MethodInvoker(delegate
                {
                    AddRecvMsg(HexFormatUtils.HexByte2String(data));
                }));
            }
            else
            {
                BeginInvoke(new MethodInvoker(delegate
                {
                    Encoding encodingGB2312 = Encoding.GetEncoding("gb2312");
                    Char[] c_data = encodingGB2312.GetChars(data); //Encoding.ASCII.GetChars(data);
                    string str = new String(c_data);
                    AddRecvMsg(str);
                }));
            }
        }

        private void OnNetErrorListener(string reasonStr, Exception e) {
            MessageBox.Show(reasonStr +"-" +e.Message, "error");

            BeginInvoke(new MethodInvoker(delegate
            {
                SetOpenBtnStatus(true);
                SetNetTypeStatus(true);
                buttonSend.Enabled = false;
            }));
        }

        private void OnNetTcpConnectedListener() {
            int index = comboBoxNetType.SelectedIndex;
            CommNetType.NetType type = NetManager.GetNetTypeByIndex(index);
            if (type == CommNetType.NetType.TCP_client ||
                type == CommNetType.NetType.TCP_server) {
                buttonSend.Enabled = true;
            }
        }

        private void AddRecvMsg(string line)
        {
            textBoxNetRecv.AppendText(line);     // 追加文本，并且使得光标定位到插入地方。
            textBoxNetRecv.ScrollToCaret();

            this.textBoxNetRecv.Focus();//获取焦点
            this.textBoxNetRecv.Select(this.textBoxNetRecv.TextLength, 0);//光标定位到文本最后
            this.textBoxNetRecv.ScrollToCaret();//滚动到光标处
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (netManager.IsOpen()) {
                netManager.Close(); //close before program exit
            }
        }

        private void ButtonNetRecvClear_Click(object sender, EventArgs e)
        {
            textBoxNetRecv.Text = "";
        }

        private void ButtonNetSendClear_Click(object sender, EventArgs e)
        {
            textBoxNetSend.Text = "";
        }
    }
}
