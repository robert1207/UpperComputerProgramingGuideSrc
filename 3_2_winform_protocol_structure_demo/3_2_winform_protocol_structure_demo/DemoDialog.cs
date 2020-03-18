using HYKT;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _3_2_winform_protocol_structure_demo
{
    public partial class DemoDialog : Form
    {
        private ProtocolManager netManager;

        private ProtocolManager.OnProtocolRecvListener recvHandler;
        private ProtocolManager.OnProtocolErrorListener errorHandler;

        public DemoDialog()
        {
            InitializeComponent();

            Init();
        }

        private void Init() {
            labelConnectStatus.Text = "设备未连接";

            netManager = ProtocolManager.GetInstance();
            recvHandler = new ProtocolManager.OnProtocolRecvListener(OnProtocolRecvListener);
            errorHandler = new ProtocolManager.OnProtocolErrorListener(OnProtocolErrorListener);
            netManager.eventProtocolRecvHandler += recvHandler;
            netManager.eventProtocolErrorHandler += errorHandler;

            netManager.SetOnGetMachineTemperatureListener(onGetMachinetemperature);
            netManager.SetOnReportValueListener(onReportValue);



        }

        private void OnProtocolRecvListener(byte[] pkg) {

        }
        private void OnProtocolErrorListener(int code, string reason) {

        }

        private void ButtonConnect_Click(object sender, EventArgs e)
        {
            Form1 form1 = new Form1();
            form1.ShowDialog(this);
            if (netManager.IsConnected()) {
                labelConnectStatus.Text = "设备已连接";
            }
        }

        private void ButtonSet_Click(object sender, EventArgs e)
        {
            int setValue = int.Parse(textBoxSetValue.Text);
            netManager.AddWork(Command.SendSetPositionValue(setValue));
        }

        private void ButtonGetTemperature_Click(object sender, EventArgs e)
        {
            netManager.AddWork(Command.SendGetMachinetemperature());
        }

        private void TextBoxSetValue_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != '\b' && !Char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        private void onGetMachinetemperature(int value) {
            BeginInvoke(new MethodInvoker(delegate
            {
                labelTemperature.Text = value.ToString();
            }));
        }
        private void onReportValue(int value) {
            BeginInvoke(new MethodInvoker(delegate
            {
                labelReportValue.Text = value.ToString();
            }));
        }

        private void DemoDialog_FormClosing(object sender, FormClosingEventArgs e)
        {
            netManager.DisConnect();
        }
    }
}
