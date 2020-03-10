using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;


namespace Tetris_ScoreBoard
{
    public partial class ScoreBoard : Form
    {
        public ScoreBoard()
        {
            InitializeComponent();
            serialPort.DataReceived += new SerialDataReceivedEventHandler(serialPort_DataReceived);
        }

        Thread Serial_Received_Thread;

        private void ScoreBoard_Load(object sender, EventArgs e)
        {
            serialPort.Close();
            string[] ports = SerialPort.GetPortNames();

            foreach (string port in ports)
            {
                cbbox_COM.Items.Add(port);
            }

            serialPort.DataBits = (int)8;
            serialPort.Parity = Parity.None;
            serialPort.StopBits = StopBits.One;
            serialPort.ReadTimeout = (int)500;
            serialPort.WriteTimeout = (int)500;
        }

        private void ScoreBoard_FormClosing(object sender, FormClosingEventArgs e)
        {
            serialPort.Close();

            if (Serial_Received_Thread != null)
            {
                Serial_Received_Thread.Abort();
            }
        }

        private void cbbox_Baudrate_SelectedIndexChanged(object sender, EventArgs e)
        {
            serialPort.BaudRate = Convert.ToInt32(cbbox_Baudrate.SelectedItem);
        }

        private void cbbox_COM_SelectedIndexChanged(object sender, EventArgs e)
        {
            serialPort.PortName = cbbox_COM.SelectedItem.ToString();
        }

        private void btn_Connect_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort.Open();

                if (serialPort.IsOpen)
                {
                    MessageBox.Show("Serial connect Successfully!");
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK);
            }            
        }

        int score = 0;
        private void serialPort_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new MethodInvoker(delegate ()
                {
                    
                    score += 100;
                    lb_Score.Text = score.ToString();
                }));
            }
            else
            {
                score += 100;
                lb_Score.Text = score.ToString();
            }
            //MessageBox.Show("Serial Read!");
            //Console.WriteLine(serialPort.ReadLine());
            //lb_Score.Text = serialPort.ReadLine();
        }

        private void Serial_Received()
        {
            int score = 0;
            score += 100;
            lb_Score.Text = score.ToString();
        }


        private void btn_Disconnect_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort.Close();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK);
            }


            MessageBox.Show("Serial disconnect Successfully!");
        }
    }
}
