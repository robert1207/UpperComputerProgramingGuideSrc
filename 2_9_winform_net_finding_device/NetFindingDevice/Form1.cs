using HYKT;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace NetFindingDevice
{
    public partial class Form1 : Form
    {

        private bool isSearchingDevice = false;

        private String SelectedNetDeviceIp;
        private String SN;

        private FoundNetDeviceList myfoundNetDeviceList;



        public Form1()
        {
            InitializeComponent();

            InitNetDeviceListUI();
        }

        /********************* founded net-device UI list *****************************/
        private void InitNetDeviceListUI()
        {
            //ImageList imgList = new ImageList();
            //Bitmap bmp = new Bitmap(typeof(GroupLightDoc), "bitmapstrip.bmp");
            //bmp.MakeTransparent(Color.Magenta);
            //imgList.Images.AddStrip(bmp);
            //this.listView1.SmallImageList = imgList;

            ColumnHeader ch = new ColumnHeader();
            ch.Text = "No";   //设置列标题
            ch.Width = 40;    //设置列宽度
            ch.TextAlign = HorizontalAlignment.Center;   //设置列的对齐方式
            this.listView1.Columns.Add(ch);    //将列头添加到ListView控件。

            ColumnHeader ch2 = new ColumnHeader();
            ch2.Text = "SN";   //设置列标题
            ch2.Width = 80;    //设置列宽度
            ch2.TextAlign = HorizontalAlignment.Center;   //设置列的对齐方式
            this.listView1.Columns.Add(ch2);    //将列头添加到ListView控件。

            ColumnHeader ch3 = new ColumnHeader();
            ch3.Text = "IP";   //设置列标题
            ch3.Width = 90;    //设置列宽度
            ch3.TextAlign = HorizontalAlignment.Center;   //设置列的对齐方式
            this.listView1.Columns.Add(ch3);    //将列头添加到ListView控件。

            ColumnHeader ch4 = new ColumnHeader();
            ch4.Text = "Version";   //设置列标题
            ch4.Width = 80;    //设置列宽度
            ch4.TextAlign = HorizontalAlignment.Center;   //设置列的对齐方式
            this.listView1.Columns.Add(ch4);    //将列头添加到ListView控件。
        }

        private void UpdateNetDeviceListUI()
        {
            this.listView1.BeginUpdate();   //数据更新，UI暂时挂起，直到EndUpdate绘制控件，可以有效避免闪烁并大大提高加载速度  

            List<NetDeviceInfo> netDeviceList = myfoundNetDeviceList.GetNetDeviceList();

            NetDeviceInfo device = null;
            int count = netDeviceList.Count;

            this.listView1.Items.Clear();

            for (int i = 0; i < count; i++)   //添加10行数据  
            {
                device = netDeviceList[i];
                ListViewItem lv = new ListViewItem();
                lv.Text = i.ToString();
                lv.SubItems.Add(device.SN);
                lv.SubItems.Add(device.Ip);
                lv.SubItems.Add(device.Version);
                this.listView1.Items.Add(lv);
            }

            this.listView1.EndUpdate();  //结束数据处理，UI界面一次性绘制。 
        }

        private void SelectLastItemOfNetDevice()
        {
            int count = listView1.Items.Count;
            if (count > 0)
            {
                int index = count - 1;
                if (index < 0) index = 0;
                listView1.Items[index].Selected = true;
            }
        }

        private void listView1_ItemSelectionChanged(object sender, ListViewItemSelectionChangedEventArgs e)
        {
            int selectedCount = listView1.SelectedIndices.Count;
            if (selectedCount > 0)
            {
                int index = listView1.SelectedIndices[0];

                List<NetDeviceInfo> netDeviceList = myfoundNetDeviceList.GetNetDeviceList();
                NetDeviceInfo selectedDevice = netDeviceList[index];

                SelectedNetDeviceIp = selectedDevice.Ip;
                SN = selectedDevice.SN;
            }
        }



        /********************* search net device ********************/
        private void SendWithoutProtecolStartFindDevice()
        {
            NetSearchingDeviceManager ch = NetSearchingDeviceManager.GetInstance();
            ch.SetOnUpdateDeviceListener(OnUpdateFoundedDeviceList);
            ch.SetOnFindDeviceErrorListener(OnFindDeviceHasUnexceptedProblemListener);
            ch.StartFind(Protocol.SearchNetDevice());
        }

        private void SendWithoutProtecolStopFindDevice()
        {
            NetSearchingDeviceManager ch = NetSearchingDeviceManager.GetInstance();
            ch.StopFind();
        }



        /********************** finding device callback functions *******************************/
        void OnUpdateFoundedDeviceList(FoundNetDeviceList foundNetDeviceList) {
            myfoundNetDeviceList = foundNetDeviceList;
            BeginInvoke(new MethodInvoker(delegate
            {
                UpdateNetDeviceListUI();
                SelectLastItemOfNetDevice();
            }));
        }

        private void OnFindDeviceHasUnexceptedProblemListener(string reason)
        {
            BeginInvoke(new MethodInvoker(delegate
            {
                SendWithoutProtecolStopFindDevice();
                buttonSearchNetDevice.Text = "Search";
                MessageBox.Show("PortNotAvaliable");
            }));
            isSearchingDevice = false;
        }


        /********************* ui button click callback ************************/
        private void ButtonSearchNetDevice_Click_1(object sender, EventArgs e)
        {
            if (isSearchingDevice == false)
            {
                //do search
                isSearchingDevice = true;
                SelectedNetDeviceIp = "";
                SendWithoutProtecolStartFindDevice();

                buttonSearchNetDevice.Text = "StopSearching";
            }
            else
            {
                // do stop search
                SendWithoutProtecolStopFindDevice();
                buttonSearchNetDevice.Text = "Search";
                isSearchingDevice = false;
            }
        }

        private void ButtonNetConnect_Click_1(object sender, EventArgs e)
        {
            if (listView1.SelectedIndices.Count <= 0 || SelectedNetDeviceIp == String.Empty)
            {
                MessageBox.Show("Please select One Of The Device To Connect");
                return;
            }

            if (isSearchingDevice == true)
            {
                MessageBox.Show("Please Stop Searching First");
                return;
            }

            string result = "select Ip: " + SelectedNetDeviceIp + "select SN: " + SN;
            Console.WriteLine(result);
            MessageBox.Show(result);
        }

        private void ButtonNetDeviceListClear_Click_1(object sender, EventArgs e)
        {
            NetSearchingDeviceManager ch = NetSearchingDeviceManager.GetInstance();
            ch.CleanFoundedDeviceList();
            UpdateNetDeviceListUI();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (isSearchingDevice == true)
            {
                MessageBox.Show("Please Stop Searching First");
                e.Cancel = true;
                return;
            }
        }



    }
}
