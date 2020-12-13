using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Windows.Forms;

namespace CSharp_Code
{
    public partial class Form1 : Form
    {
        private RadarDrawer _radarDrawer;
        private SerialPort _serialReader;
        private DataGenerator _dataGenerator;

        public Form1()
        {
            InitializeComponent();
            InitFields();
        }

        private void InitFields()
        {
            _radarDrawer = new RadarDrawer(RadarField_PictureBox);
            _dataGenerator = new DataGenerator();
            _serialReader = new SerialPort("COM3", 115200, Parity.None, 8, StopBits.One);
            _serialReader.DataReceived += _serialReader_DataReceived;
        }

        private void _serialReader_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            double dist = 0;
            double angle = 0;
            try
            {
                string line = _serialReader.ReadLine();
                textBox1.Text = line;
                string[] parseResult = line.Split(';');

                dist = double.Parse(parseResult[0]);
                angle = double.Parse(parseResult[1].Substring(0, parseResult[1].Length - 1));           
                _radarDrawer.RedrawRadar(dist, angle);
            }
            catch (Exception ex)
            {
                var message = ex.Message;
            }
        }

        private void GenerateData_Button_Click(object sender, EventArgs e)
        {
            GenerateData_Timer.Enabled = !GenerateData_Timer.Enabled;
        }

        private void GenerateData_Timer_Tick(object sender, EventArgs e)
        {
            //var data = _dataGenerator.GenerateNewData().ToArray();

            var data = _dataGenerator.GenerateSingleData();
            textBox1.Text = data;

            if (data == null)
                return;
            else
                _radarDrawer.TestRedrawRadar(data);
        }

        private void OpenPort_Button_Click(object sender, EventArgs e)
        {
            _serialReader.Open();
        }
    }
}
