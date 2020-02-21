using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace winform_serial_port_gui_tool
{
    public partial class Form1 : Form
    {

        private SerialComm serialComm;

        private string recvCache = "";

        public Form1()
        {
            InitializeComponent();

            serialComm = new SerialComm();
            serialComm.SetRecvListener(RecvListener);

            InitUI();
        }

        private void InitUI() {
            comboBoxSerialPort.Items.AddRange(serialComm.GetSerialDeviceStrList());
            comboBoxSerialBaud.Items.AddRange(serialComm.GetSerialBaudRateStrList());
            comboBoxSerialDataBits.Items.AddRange(serialComm.GetSerialDataBitsStrList());
            comboBoxSerialParity.Items.AddRange(serialComm.GetSerialParityStrList());
            comboBoxSerialStopBits.Items.AddRange(serialComm.GetSerialStopBitsStrList());

            if (comboBoxSerialPort.Items.Count > 0) {
                comboBoxSerialPort.SelectedIndex = 0;
            }
            comboBoxSerialBaud.SelectedIndex = 3;
            comboBoxSerialDataBits.SelectedIndex = 3;
            comboBoxSerialParity.SelectedIndex = 0;
            comboBoxSerialStopBits.SelectedIndex = 1;
        }

        private void DisableSettingsUI() {
            comboBoxSerialPort.Enabled = false;
            comboBoxSerialBaud.Enabled = false;
            comboBoxSerialDataBits.Enabled = false;
            comboBoxSerialParity.Enabled = false;
            comboBoxSerialStopBits.Enabled = false;
        }

        private void EnableSettingsUI() {
            comboBoxSerialPort.Enabled = true;
            comboBoxSerialBaud.Enabled = true;
            comboBoxSerialDataBits.Enabled = true;
            comboBoxSerialParity.Enabled = true;
            comboBoxSerialStopBits.Enabled = true;
        }

        private void SetSerialSettings() {
            serialComm.SetSerialPortName(comboBoxSerialPort.Text);
            serialComm.SetSerialBaudRate(SerialComm.GetBaudRateByIndex(comboBoxSerialBaud.SelectedIndex));
            serialComm.SetSerialDataBits(SerialComm.GetDataBitsByIndex(comboBoxSerialDataBits.SelectedIndex));
            serialComm.SetSerialParity(SerialComm.GetParityByIndex(comboBoxSerialParity.SelectedIndex));
            serialComm.SetSerialStopBits(SerialComm.GetStopBitsByIndex(comboBoxSerialStopBits.SelectedIndex));
        }

        private void buttonSerialOpen_Click(object sender, EventArgs e)
        {
            if (serialComm.IsOpen())
            {
                //do close
                serialComm.Close();
                EnableSettingsUI();
                buttonSerialOpen.Text = "open";
            }
            else
            {
                //do open
                SetSerialSettings();
                serialComm.Open();
                DisableSettingsUI();
                buttonSerialOpen.Text = "close";
            }
        }

        private void buttonSerialSend_Click(object sender, EventArgs e)
        {
            if (!serialComm.IsOpen()) {
                MessageBox.Show("Please open the serial port first !");
                return;
            }

            char[] data = textBoxSerialSend.Text.ToString().ToCharArray();
            serialComm.Send(data);
            textBoxSerialSend.Clear();
        }

        
        private void RecvListener(byte[] data, int length) {
            this.Invoke( (MethodInvoker)delegate ()
            {
                String temp = System.Text.Encoding.UTF8.GetString(data);
                Console.Out.WriteLine(temp);
                recvCache += temp;
                textBoxSerialRecv.Text = recvCache;
            });
        }




    }
}
