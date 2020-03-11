using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO.Ports;
using System.Threading;

namespace Tetris_ScoreBoard
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            serialPort.DataReceived += new SerialDataReceivedEventHandler(serialPort_DataReceived);
        }

        Thread Serial_Received_Thread;
        int score = 0;
        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            if (!Dispatcher.CheckAccess())
            {
                this.Dispatcher.Invoke(new Action(delegate
                {

                    score += 100;
                    lb_Score.Content = score.ToString();
                }));
            }
            else
            {
                score += 100;
                lb_Score.Content = score.ToString();
            }
        }

        private void Serial_Received()
        {
            int score = 0;
            score += 100;
            lb_Score.Content = score.ToString();
        }

        SerialPort serialPort = new SerialPort();

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            serialPort.Close();
            string[] ports = SerialPort.GetPortNames();

            foreach (string port in ports)
            {
                cbbox_COM.Items.Add(port);
            }

            serialPort.DataBits = 8;
            serialPort.Parity = Parity.None;
            serialPort.StopBits = StopBits.One;
            serialPort.ReadTimeout = 500;
            serialPort.WriteTimeout = 500;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            serialPort.Close();

            if (Serial_Received_Thread != null)
            {
                Serial_Received_Thread.Abort();
            }
        }

        private void cbbox_Baudrate_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string[] names = cbbox_Baudrate.SelectedItem.ToString().Split(':');
            serialPort.BaudRate = int.Parse(names[1].ToString().Trim());

            if (serialPort.IsOpen)
            {
                sbStrip1.Content = serialPort.PortName + " : " + serialPort.BaudRate + ", 8N1";
            }
        }

        private void cbbox_COM_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            serialPort.PortName = cbbox_COM.SelectedItem.ToString();
        }

        private void btn_Connect_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                serialPort.Open();

                if (serialPort.IsOpen)
                {
                    MessageBox.Show("Serial connect Successfully!", "Successfully", MessageBoxButton.OK, MessageBoxImage.Information);
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void btn_Disconnect_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                serialPort.Close();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }


            MessageBox.Show("Serial disconnect Successfully!", "Successfully", MessageBoxButton.OK, MessageBoxImage.Information);
        }
    }
}