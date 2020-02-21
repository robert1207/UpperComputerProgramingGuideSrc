namespace winform_serial_port_gui_tool
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
            this.buttonSerialSend = new System.Windows.Forms.Button();
            this.buttonSerialOpen = new System.Windows.Forms.Button();
            this.comboBoxSerialPort = new System.Windows.Forms.ComboBox();
            this.Recv = new System.Windows.Forms.Label();
            this.textBoxSerialRecv = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxSerialSend = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBoxSerialBaud = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.comboBoxSerialDataBits = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.comboBoxSerialParity = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.comboBoxSerialStopBits = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonSerialSend
            // 
            this.buttonSerialSend.Location = new System.Drawing.Point(738, 600);
            this.buttonSerialSend.Margin = new System.Windows.Forms.Padding(6);
            this.buttonSerialSend.Name = "buttonSerialSend";
            this.buttonSerialSend.Size = new System.Drawing.Size(150, 46);
            this.buttonSerialSend.TabIndex = 0;
            this.buttonSerialSend.Text = "Send";
            this.buttonSerialSend.UseVisualStyleBackColor = true;
            this.buttonSerialSend.Click += new System.EventHandler(this.buttonSerialSend_Click);
            // 
            // buttonSerialOpen
            // 
            this.buttonSerialOpen.Location = new System.Drawing.Point(738, 390);
            this.buttonSerialOpen.Margin = new System.Windows.Forms.Padding(6);
            this.buttonSerialOpen.Name = "buttonSerialOpen";
            this.buttonSerialOpen.Size = new System.Drawing.Size(150, 46);
            this.buttonSerialOpen.TabIndex = 1;
            this.buttonSerialOpen.Text = "open";
            this.buttonSerialOpen.UseVisualStyleBackColor = true;
            this.buttonSerialOpen.Click += new System.EventHandler(this.buttonSerialOpen_Click);
            // 
            // comboBoxSerialPort
            // 
            this.comboBoxSerialPort.FormattingEnabled = true;
            this.comboBoxSerialPort.Location = new System.Drawing.Point(782, 44);
            this.comboBoxSerialPort.Margin = new System.Windows.Forms.Padding(6);
            this.comboBoxSerialPort.Name = "comboBoxSerialPort";
            this.comboBoxSerialPort.Size = new System.Drawing.Size(150, 32);
            this.comboBoxSerialPort.TabIndex = 2;
            // 
            // Recv
            // 
            this.Recv.AutoSize = true;
            this.Recv.Location = new System.Drawing.Point(20, 14);
            this.Recv.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.Recv.Name = "Recv";
            this.Recv.Size = new System.Drawing.Size(154, 24);
            this.Recv.TabIndex = 3;
            this.Recv.Text = "Receive Area";
            // 
            // textBoxSerialRecv
            // 
            this.textBoxSerialRecv.Location = new System.Drawing.Point(24, 44);
            this.textBoxSerialRecv.Margin = new System.Windows.Forms.Padding(6);
            this.textBoxSerialRecv.Multiline = true;
            this.textBoxSerialRecv.Name = "textBoxSerialRecv";
            this.textBoxSerialRecv.Size = new System.Drawing.Size(610, 388);
            this.textBoxSerialRecv.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(24, 442);
            this.label1.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(154, 24);
            this.label1.TabIndex = 3;
            this.label1.Text = "Sending Area";
            // 
            // textBoxSerialSend
            // 
            this.textBoxSerialSend.Location = new System.Drawing.Point(24, 472);
            this.textBoxSerialSend.Margin = new System.Windows.Forms.Padding(6);
            this.textBoxSerialSend.Multiline = true;
            this.textBoxSerialSend.Name = "textBoxSerialSend";
            this.textBoxSerialSend.Size = new System.Drawing.Size(610, 178);
            this.textBoxSerialSend.TabIndex = 4;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(664, 50);
            this.label2.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(58, 24);
            this.label2.TabIndex = 3;
            this.label2.Text = "Port";
            // 
            // comboBoxSerialBaud
            // 
            this.comboBoxSerialBaud.FormattingEnabled = true;
            this.comboBoxSerialBaud.Location = new System.Drawing.Point(782, 100);
            this.comboBoxSerialBaud.Margin = new System.Windows.Forms.Padding(6);
            this.comboBoxSerialBaud.Name = "comboBoxSerialBaud";
            this.comboBoxSerialBaud.Size = new System.Drawing.Size(150, 32);
            this.comboBoxSerialBaud.TabIndex = 2;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(664, 106);
            this.label3.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(58, 24);
            this.label3.TabIndex = 3;
            this.label3.Text = "Baud";
            // 
            // comboBoxSerialDataBits
            // 
            this.comboBoxSerialDataBits.FormattingEnabled = true;
            this.comboBoxSerialDataBits.Location = new System.Drawing.Point(782, 156);
            this.comboBoxSerialDataBits.Margin = new System.Windows.Forms.Padding(6);
            this.comboBoxSerialDataBits.Name = "comboBoxSerialDataBits";
            this.comboBoxSerialDataBits.Size = new System.Drawing.Size(150, 32);
            this.comboBoxSerialDataBits.TabIndex = 2;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(664, 162);
            this.label4.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(106, 24);
            this.label4.TabIndex = 3;
            this.label4.Text = "DataBits";
            // 
            // comboBoxSerialParity
            // 
            this.comboBoxSerialParity.FormattingEnabled = true;
            this.comboBoxSerialParity.Location = new System.Drawing.Point(782, 212);
            this.comboBoxSerialParity.Margin = new System.Windows.Forms.Padding(6);
            this.comboBoxSerialParity.Name = "comboBoxSerialParity";
            this.comboBoxSerialParity.Size = new System.Drawing.Size(150, 32);
            this.comboBoxSerialParity.TabIndex = 2;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(664, 218);
            this.label5.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(82, 24);
            this.label5.TabIndex = 3;
            this.label5.Text = "Parity";
            // 
            // comboBoxSerialStopBits
            // 
            this.comboBoxSerialStopBits.FormattingEnabled = true;
            this.comboBoxSerialStopBits.Location = new System.Drawing.Point(782, 268);
            this.comboBoxSerialStopBits.Margin = new System.Windows.Forms.Padding(6);
            this.comboBoxSerialStopBits.Name = "comboBoxSerialStopBits";
            this.comboBoxSerialStopBits.Size = new System.Drawing.Size(150, 32);
            this.comboBoxSerialStopBits.TabIndex = 2;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(664, 274);
            this.label6.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(106, 24);
            this.label6.TabIndex = 3;
            this.label6.Text = "StopBits";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 24F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(958, 670);
            this.Controls.Add(this.textBoxSerialSend);
            this.Controls.Add(this.textBoxSerialRecv);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.comboBoxSerialStopBits);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.comboBoxSerialParity);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.comboBoxSerialDataBits);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.comboBoxSerialBaud);
            this.Controls.Add(this.Recv);
            this.Controls.Add(this.comboBoxSerialPort);
            this.Controls.Add(this.buttonSerialOpen);
            this.Controls.Add(this.buttonSerialSend);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Serial port gui tool";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonSerialSend;
        private System.Windows.Forms.Button buttonSerialOpen;
        private System.Windows.Forms.ComboBox comboBoxSerialPort;
        private System.Windows.Forms.Label Recv;
        private System.Windows.Forms.TextBox textBoxSerialRecv;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxSerialSend;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBoxSerialBaud;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboBoxSerialDataBits;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox comboBoxSerialParity;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox comboBoxSerialStopBits;
        private System.Windows.Forms.Label label6;
    }
}

