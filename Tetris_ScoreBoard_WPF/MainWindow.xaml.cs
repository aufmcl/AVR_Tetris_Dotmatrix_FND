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
using System.ComponentModel;

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

        class ListData
        {
            public string user { get; set; }
            public int score { get; set; }
            public DateTime time { get; set; }

            private static List<ListData> instance;

            public static List<ListData> GetInstance()
            {
                if (instance == null)
                    instance = new List<ListData>();

                return instance;
            }
        }


        int score_value = 0;
        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int value = serialPort.ReadChar();


            //else if (value == 71)

            if (!Dispatcher.CheckAccess())
            {
                this.Dispatcher.Invoke(new Action(delegate
                {
                    if (value == 49)
                    {
                        score_value += 100;
                        lb_Score.Content = score_value.ToString();

                    }
                    else if (value == 71)
                    {
                        MessageBox.Show("Your score is " + score_value.ToString(), "Game over", MessageBoxButton.OK, MessageBoxImage.Warning);
                        Add_Item_Listview();
                        score_value = 0;
                    }
                }));
            }
            else
            {
                if (value == 49)
                {
                    score_value += 100;
                    lb_Score.Content = score_value.ToString();
                }
                else if (value == 71)
                {
                    MessageBox.Show("Your score is " + score_value.ToString(), "Game over", MessageBoxButton.OK, MessageBoxImage.Warning);
                    Add_Item_Listview();
                    score_value = 0;
                }
            }
        }

        void Add_Item_Listview()
        {
            ListData.GetInstance().Add(new ListData() { user = txtbox_Name.Text, score = score_value, time = DateTime.Today });
            lstView.ItemsSource = ListData.GetInstance();
            lstView.Items.Refresh();
        }

        GridViewColumnHeader _lastHeaderClicked = null;
        ListSortDirection _lastDirection = ListSortDirection.Ascending;

        private void GridViewColumnHeaderClickedHandler(object sender, RoutedEventArgs e)
        {
            var headerClicked = e.OriginalSource as GridViewColumnHeader;
            ListSortDirection direction;

            if (headerClicked != null)
            {
                if (headerClicked.Role != GridViewColumnHeaderRole.Padding)
                {
                    if (headerClicked != _lastHeaderClicked)
                    {
                        direction = ListSortDirection.Ascending;
                    }
                    else
                    {
                        if (_lastDirection == ListSortDirection.Ascending)
                        {
                            direction = ListSortDirection.Descending;
                        }
                        else
                        {
                            direction = ListSortDirection.Ascending;
                        }
                    }

                    var columnBinding = headerClicked.Column.DisplayMemberBinding as Binding;
                    var sortBy = columnBinding?.Path.Path ?? headerClicked.Column.Header as string;

                    Sort(sortBy, direction);

                    if (direction == ListSortDirection.Ascending)
                    {
                        headerClicked.Column.HeaderTemplate =
                          Resources["HeaderTemplateArrowUp"] as DataTemplate;
                    }
                    else
                    {
                        headerClicked.Column.HeaderTemplate =
                          Resources["HeaderTemplateArrowDown"] as DataTemplate;
                    }

                    // Remove arrow from previously sorted header
                    if (_lastHeaderClicked != null && _lastHeaderClicked != headerClicked)
                    {
                        _lastHeaderClicked.Column.HeaderTemplate = null;
                    }

                    _lastHeaderClicked = headerClicked;
                    _lastDirection = direction;
                }
            }
        }

        private void Sort(string sortBy, ListSortDirection direction)
        {
            ICollectionView dataView = CollectionViewSource.GetDefaultView(lstView.ItemsSource);

            dataView.SortDescriptions.Clear();
            SortDescription sd = new SortDescription(sortBy, direction);
            dataView.SortDescriptions.Add(sd);
            dataView.Refresh();
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
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            try
            {
                if (e.Key == Key.A)
                {
                    serialPort.Write("A");
                }
                else if (e.Key == Key.S)
                {
                    serialPort.Write("S");
                }
                else if (e.Key == Key.D)
                {
                    serialPort.Write("D");
                }
                else if (e.Key == Key.R)
                {
                    serialPort.Write("R");
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
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
            try
            {
                serialPort.PortName = cbbox_COM.SelectedItem.ToString();

                if (serialPort.IsOpen)
                {
                    sbStrip1.Content = serialPort.PortName + " : " + serialPort.BaudRate + ", 8N1";
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }

        }

        private void btn_Connect_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                serialPort.Open();

                if (serialPort.IsOpen)
                {
                    MessageBox.Show("Serial connect Successfully!", "Successfully", MessageBoxButton.OK, MessageBoxImage.Information);
                    sbStrip1.Content = serialPort.PortName + " : " + serialPort.BaudRate + ", 8N1";

                    btn_Pause.IsEnabled = true;
                    btn_Start.IsEnabled = true;
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

        private void btn_Start_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (txtbox_Name.Text == "User name" || txtbox_Name.Text == "")
                {
                    MessageBox.Show("Input your name!", "Warning!", MessageBoxButton.OK, MessageBoxImage.Warning);
                }
                else
                {
                    serialPort.Write("1");
                }

            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void btn_Pause_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                serialPort.Write("0");
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void btn_Search_Click(object sender, RoutedEventArgs e)
        {
            string[] ports = SerialPort.GetPortNames();

            foreach (string port in ports)
            {
                cbbox_COM.Items.Add(port);
            }
        }

        private void btn_Disconnect_MouseEnter(object sender, MouseEventArgs e)
        {
            btn_Disconnect.BorderThickness = new Thickness(1, 1, 1, 1);
            btn_Disconnect.BorderBrush = Brushes.CornflowerBlue;
        }

        private void btn_Connect_MouseEnter(object sender, MouseEventArgs e)
        {
            btn_Connect.BorderThickness = new Thickness(1, 1, 1, 1);
            btn_Connect.BorderBrush = Brushes.CornflowerBlue;
        }

        private void btn_Search_MouseEnter(object sender, MouseEventArgs e)
        {
            btn_Search.BorderThickness = new Thickness(1, 1, 1, 1);
            btn_Search.BorderBrush = Brushes.CornflowerBlue;
        }


        private void btn_Disconnect_MouseLeave(object sender, MouseEventArgs e)
        {
            btn_Disconnect.BorderThickness = new Thickness(0, 0, 0, 0);
        }

        private void btn_Connect_MouseLeave(object sender, MouseEventArgs e)
        {
            btn_Connect.BorderThickness = new Thickness(0, 0, 0, 0);
        }

        private void btn_Search_MouseLeave(object sender, MouseEventArgs e)
        {
            btn_Search.BorderThickness = new Thickness(0, 0, 0, 0);
        }

        private void txtbox_Name_GotMouseCapture(object sender, MouseEventArgs e)
        {
            txtbox_Name.Text = "";
        }
    }
}