namespace Tetris_ScoreBoard
{
    partial class ScoreBoard
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.lb_Score = new System.Windows.Forms.Label();
            this.cbbox_Baudrate = new System.Windows.Forms.ComboBox();
            this.cbbox_COM = new System.Windows.Forms.ComboBox();
            this.btn_Connect = new System.Windows.Forms.Button();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.btn_Disconnect = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lb_Score
            // 
            this.lb_Score.AutoSize = true;
            this.lb_Score.Font = new System.Drawing.Font("Microsoft Sans Serif", 13F);
            this.lb_Score.Location = new System.Drawing.Point(12, 11);
            this.lb_Score.Name = "lb_Score";
            this.lb_Score.Size = new System.Drawing.Size(72, 22);
            this.lb_Score.TabIndex = 0;
            this.lb_Score.Text = "Score : ";
            // 
            // cbbox_Baudrate
            // 
            this.cbbox_Baudrate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbbox_Baudrate.Font = new System.Drawing.Font("맑은 고딕", 11F);
            this.cbbox_Baudrate.FormattingEnabled = true;
            this.cbbox_Baudrate.Items.AddRange(new object[] {
            "4800",
            "9600",
            "19200",
            "38400",
            "57600",
            "74880",
            "115200"});
            this.cbbox_Baudrate.Location = new System.Drawing.Point(514, 460);
            this.cbbox_Baudrate.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.cbbox_Baudrate.Name = "cbbox_Baudrate";
            this.cbbox_Baudrate.Size = new System.Drawing.Size(100, 28);
            this.cbbox_Baudrate.TabIndex = 1;
            this.cbbox_Baudrate.SelectedIndexChanged += new System.EventHandler(this.cbbox_Baudrate_SelectedIndexChanged);
            // 
            // cbbox_COM
            // 
            this.cbbox_COM.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbbox_COM.Font = new System.Drawing.Font("맑은 고딕", 11F);
            this.cbbox_COM.FormattingEnabled = true;
            this.cbbox_COM.Location = new System.Drawing.Point(620, 460);
            this.cbbox_COM.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.cbbox_COM.Name = "cbbox_COM";
            this.cbbox_COM.Size = new System.Drawing.Size(100, 28);
            this.cbbox_COM.TabIndex = 2;
            this.cbbox_COM.SelectedIndexChanged += new System.EventHandler(this.cbbox_COM_SelectedIndexChanged);
            // 
            // btn_Connect
            // 
            this.btn_Connect.Font = new System.Drawing.Font("맑은 고딕", 11F);
            this.btn_Connect.Location = new System.Drawing.Point(726, 460);
            this.btn_Connect.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_Connect.Name = "btn_Connect";
            this.btn_Connect.Size = new System.Drawing.Size(100, 28);
            this.btn_Connect.TabIndex = 3;
            this.btn_Connect.Text = "Connect";
            this.btn_Connect.UseVisualStyleBackColor = true;
            this.btn_Connect.Click += new System.EventHandler(this.btn_Connect_Click);
            // 
            // btn_Disconnect
            // 
            this.btn_Disconnect.Font = new System.Drawing.Font("맑은 고딕", 11F);
            this.btn_Disconnect.Location = new System.Drawing.Point(832, 460);
            this.btn_Disconnect.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btn_Disconnect.Name = "btn_Disconnect";
            this.btn_Disconnect.Size = new System.Drawing.Size(100, 28);
            this.btn_Disconnect.TabIndex = 4;
            this.btn_Disconnect.Text = "Disconnect";
            this.btn_Disconnect.UseVisualStyleBackColor = true;
            this.btn_Disconnect.Click += new System.EventHandler(this.btn_Disconnect_Click);
            // 
            // ScoreBoard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(944, 501);
            this.Controls.Add(this.btn_Disconnect);
            this.Controls.Add(this.btn_Connect);
            this.Controls.Add(this.cbbox_COM);
            this.Controls.Add(this.cbbox_Baudrate);
            this.Controls.Add(this.lb_Score);
            this.Font = new System.Drawing.Font("맑은 고딕", 9F);
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "ScoreBoard";
            this.Text = "Score_Board";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ScoreBoard_FormClosing);
            this.Load += new System.EventHandler(this.ScoreBoard_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lb_Score;
        private System.Windows.Forms.ComboBox cbbox_Baudrate;
        private System.Windows.Forms.ComboBox cbbox_COM;
        private System.Windows.Forms.Button btn_Connect;
        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.Button btn_Disconnect;
    }
}

