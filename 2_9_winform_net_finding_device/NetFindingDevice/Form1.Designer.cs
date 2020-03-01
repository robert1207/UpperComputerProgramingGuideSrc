namespace NetFindingDevice
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.listView1 = new System.Windows.Forms.ListView();
            this.panel3 = new System.Windows.Forms.Panel();
            this.buttonNetDeviceListClear = new System.Windows.Forms.Button();
            this.label12 = new System.Windows.Forms.Label();
            this.buttonSearchNetDevice = new System.Windows.Forms.Button();
            this.buttonNetConnect = new System.Windows.Forms.Button();
            this.panel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // listView1
            // 
            this.listView1.FullRowSelect = true;
            this.listView1.HideSelection = false;
            this.listView1.Location = new System.Drawing.Point(12, 57);
            this.listView1.MultiSelect = false;
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(292, 123);
            this.listView1.TabIndex = 24;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            // 
            // panel3
            // 
            this.panel3.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.panel3.Controls.Add(this.buttonNetDeviceListClear);
            this.panel3.Controls.Add(this.label12);
            this.panel3.Location = new System.Drawing.Point(12, 33);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(292, 25);
            this.panel3.TabIndex = 23;
            // 
            // buttonNetDeviceListClear
            // 
            this.buttonNetDeviceListClear.Location = new System.Drawing.Point(241, 1);
            this.buttonNetDeviceListClear.Name = "buttonNetDeviceListClear";
            this.buttonNetDeviceListClear.Size = new System.Drawing.Size(43, 23);
            this.buttonNetDeviceListClear.TabIndex = 2;
            this.buttonNetDeviceListClear.Text = "清空";
            this.buttonNetDeviceListClear.UseVisualStyleBackColor = true;
            this.buttonNetDeviceListClear.Click += new System.EventHandler(this.ButtonNetDeviceListClear_Click_1);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(3, 6);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(77, 12);
            this.label12.TabIndex = 0;
            this.label12.Text = "设备查询结果";
            // 
            // buttonSearchNetDevice
            // 
            this.buttonSearchNetDevice.Location = new System.Drawing.Point(15, 201);
            this.buttonSearchNetDevice.Name = "buttonSearchNetDevice";
            this.buttonSearchNetDevice.Size = new System.Drawing.Size(104, 23);
            this.buttonSearchNetDevice.TabIndex = 21;
            this.buttonSearchNetDevice.Text = "查找设备";
            this.buttonSearchNetDevice.UseVisualStyleBackColor = true;
            this.buttonSearchNetDevice.Click += new System.EventHandler(this.ButtonSearchNetDevice_Click_1);
            // 
            // buttonNetConnect
            // 
            this.buttonNetConnect.Location = new System.Drawing.Point(192, 201);
            this.buttonNetConnect.Name = "buttonNetConnect";
            this.buttonNetConnect.Size = new System.Drawing.Size(104, 23);
            this.buttonNetConnect.TabIndex = 22;
            this.buttonNetConnect.Text = "连接网口";
            this.buttonNetConnect.UseVisualStyleBackColor = true;
            this.buttonNetConnect.Click += new System.EventHandler(this.ButtonNetConnect_Click_1);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(316, 241);
            this.Controls.Add(this.listView1);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.buttonSearchNetDevice);
            this.Controls.Add(this.buttonNetConnect);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Button buttonNetDeviceListClear;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Button buttonSearchNetDevice;
        private System.Windows.Forms.Button buttonNetConnect;
    }
}

