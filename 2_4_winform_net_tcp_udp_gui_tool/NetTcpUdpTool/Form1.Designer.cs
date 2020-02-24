namespace NetTcpUdpTool
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
            this.components = new System.ComponentModel.Container();
            this.buttonSend = new System.Windows.Forms.Button();
            this.comboBoxNetType = new System.Windows.Forms.ComboBox();
            this.labelNetIp = new System.Windows.Forms.Label();
            this.textBoxNetDesIp = new System.Windows.Forms.TextBox();
            this.textBoxNetRecv = new System.Windows.Forms.TextBox();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.textBoxNetSend = new System.Windows.Forms.TextBox();
            this.buttonOpen = new System.Windows.Forms.Button();
            this.textBoxNetDesPort = new System.Windows.Forms.TextBox();
            this.labelNetPort = new System.Windows.Forms.Label();
            this.checkBoxNetRecvHex = new System.Windows.Forms.CheckBox();
            this.checkBoxNetSendHex = new System.Windows.Forms.CheckBox();
            this.buttonNetRecvClear = new System.Windows.Forms.Button();
            this.buttonNetSendClear = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonSend
            // 
            this.buttonSend.Location = new System.Drawing.Point(313, 237);
            this.buttonSend.Name = "buttonSend";
            this.buttonSend.Size = new System.Drawing.Size(108, 23);
            this.buttonSend.TabIndex = 0;
            this.buttonSend.Text = "Send";
            this.buttonSend.UseVisualStyleBackColor = true;
            this.buttonSend.Click += new System.EventHandler(this.ButtonSend_Click);
            // 
            // comboBoxNetType
            // 
            this.comboBoxNetType.FormattingEnabled = true;
            this.comboBoxNetType.Location = new System.Drawing.Point(313, 12);
            this.comboBoxNetType.Name = "comboBoxNetType";
            this.comboBoxNetType.Size = new System.Drawing.Size(108, 20);
            this.comboBoxNetType.TabIndex = 1;
            this.comboBoxNetType.SelectedIndexChanged += new System.EventHandler(this.ComboBoxNetType_SelectedIndexChanged);
            // 
            // labelNetIp
            // 
            this.labelNetIp.AutoSize = true;
            this.labelNetIp.Location = new System.Drawing.Point(311, 43);
            this.labelNetIp.Name = "labelNetIp";
            this.labelNetIp.Size = new System.Drawing.Size(89, 12);
            this.labelNetIp.TabIndex = 2;
            this.labelNetIp.Text = "Destination Ip";
            // 
            // textBoxNetDesIp
            // 
            this.textBoxNetDesIp.Location = new System.Drawing.Point(313, 61);
            this.textBoxNetDesIp.Name = "textBoxNetDesIp";
            this.textBoxNetDesIp.Size = new System.Drawing.Size(108, 21);
            this.textBoxNetDesIp.TabIndex = 3;
            // 
            // textBoxNetRecv
            // 
            this.textBoxNetRecv.Location = new System.Drawing.Point(12, 12);
            this.textBoxNetRecv.Multiline = true;
            this.textBoxNetRecv.Name = "textBoxNetRecv";
            this.textBoxNetRecv.Size = new System.Drawing.Size(285, 144);
            this.textBoxNetRecv.TabIndex = 3;
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(61, 4);
            // 
            // textBoxNetSend
            // 
            this.textBoxNetSend.Location = new System.Drawing.Point(12, 192);
            this.textBoxNetSend.Multiline = true;
            this.textBoxNetSend.Name = "textBoxNetSend";
            this.textBoxNetSend.Size = new System.Drawing.Size(285, 95);
            this.textBoxNetSend.TabIndex = 3;
            // 
            // buttonOpen
            // 
            this.buttonOpen.Location = new System.Drawing.Point(313, 144);
            this.buttonOpen.Name = "buttonOpen";
            this.buttonOpen.Size = new System.Drawing.Size(108, 23);
            this.buttonOpen.TabIndex = 0;
            this.buttonOpen.Text = "Open";
            this.buttonOpen.UseVisualStyleBackColor = true;
            this.buttonOpen.Click += new System.EventHandler(this.ButtonOpen_Click);
            // 
            // textBoxNetDesPort
            // 
            this.textBoxNetDesPort.Location = new System.Drawing.Point(313, 106);
            this.textBoxNetDesPort.Name = "textBoxNetDesPort";
            this.textBoxNetDesPort.Size = new System.Drawing.Size(108, 21);
            this.textBoxNetDesPort.TabIndex = 3;
            // 
            // labelNetPort
            // 
            this.labelNetPort.AutoSize = true;
            this.labelNetPort.Location = new System.Drawing.Point(311, 90);
            this.labelNetPort.Name = "labelNetPort";
            this.labelNetPort.Size = new System.Drawing.Size(101, 12);
            this.labelNetPort.TabIndex = 2;
            this.labelNetPort.Text = "Destination Port";
            // 
            // checkBoxNetRecvHex
            // 
            this.checkBoxNetRecvHex.AutoSize = true;
            this.checkBoxNetRecvHex.Location = new System.Drawing.Point(138, 167);
            this.checkBoxNetRecvHex.Name = "checkBoxNetRecvHex";
            this.checkBoxNetRecvHex.Size = new System.Drawing.Size(42, 16);
            this.checkBoxNetRecvHex.TabIndex = 4;
            this.checkBoxNetRecvHex.Text = "Hex";
            this.checkBoxNetRecvHex.UseVisualStyleBackColor = true;
            // 
            // checkBoxNetSendHex
            // 
            this.checkBoxNetSendHex.AutoSize = true;
            this.checkBoxNetSendHex.Location = new System.Drawing.Point(138, 296);
            this.checkBoxNetSendHex.Name = "checkBoxNetSendHex";
            this.checkBoxNetSendHex.Size = new System.Drawing.Size(42, 16);
            this.checkBoxNetSendHex.TabIndex = 4;
            this.checkBoxNetSendHex.Text = "Hex";
            this.checkBoxNetSendHex.UseVisualStyleBackColor = true;
            // 
            // buttonNetRecvClear
            // 
            this.buttonNetRecvClear.Location = new System.Drawing.Point(221, 163);
            this.buttonNetRecvClear.Name = "buttonNetRecvClear";
            this.buttonNetRecvClear.Size = new System.Drawing.Size(75, 23);
            this.buttonNetRecvClear.TabIndex = 5;
            this.buttonNetRecvClear.Text = "Clear";
            this.buttonNetRecvClear.UseVisualStyleBackColor = true;
            this.buttonNetRecvClear.Click += new System.EventHandler(this.ButtonNetRecvClear_Click);
            // 
            // buttonNetSendClear
            // 
            this.buttonNetSendClear.Location = new System.Drawing.Point(222, 292);
            this.buttonNetSendClear.Name = "buttonNetSendClear";
            this.buttonNetSendClear.Size = new System.Drawing.Size(75, 23);
            this.buttonNetSendClear.TabIndex = 5;
            this.buttonNetSendClear.Text = "Clear";
            this.buttonNetSendClear.UseVisualStyleBackColor = true;
            this.buttonNetSendClear.Click += new System.EventHandler(this.ButtonNetSendClear_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(434, 327);
            this.Controls.Add(this.buttonNetSendClear);
            this.Controls.Add(this.buttonNetRecvClear);
            this.Controls.Add(this.checkBoxNetSendHex);
            this.Controls.Add(this.checkBoxNetRecvHex);
            this.Controls.Add(this.textBoxNetSend);
            this.Controls.Add(this.textBoxNetRecv);
            this.Controls.Add(this.textBoxNetDesPort);
            this.Controls.Add(this.textBoxNetDesIp);
            this.Controls.Add(this.labelNetPort);
            this.Controls.Add(this.labelNetIp);
            this.Controls.Add(this.comboBoxNetType);
            this.Controls.Add(this.buttonOpen);
            this.Controls.Add(this.buttonSend);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "NetToolDialog";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonSend;
        private System.Windows.Forms.ComboBox comboBoxNetType;
        private System.Windows.Forms.Label labelNetIp;
        private System.Windows.Forms.TextBox textBoxNetDesIp;
        private System.Windows.Forms.TextBox textBoxNetRecv;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.TextBox textBoxNetSend;
        private System.Windows.Forms.Button buttonOpen;
        private System.Windows.Forms.TextBox textBoxNetDesPort;
        private System.Windows.Forms.Label labelNetPort;
        private System.Windows.Forms.CheckBox checkBoxNetRecvHex;
        private System.Windows.Forms.CheckBox checkBoxNetSendHex;
        private System.Windows.Forms.Button buttonNetRecvClear;
        private System.Windows.Forms.Button buttonNetSendClear;
    }
}

